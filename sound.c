/*
 * File:   sound.c
 * Author: Yaraslau
 *
 * Created on 19 февраля 2021 г., 8:56
 */


#include "xc.h"
#include "sound.h"
#include "flash.h"
#include "dac.h"
#include "delays_and_timers.h"
#include "spi.h"

uint32_t count = 0;
uint8_t arrOneInUse = 1;
uint8_t arrTwoInUse = 0;
uint8_t volume = 1;
uint16_t sound1[140];
uint16_t sound2[140];
uint32_t lastAdress = 0;
uint16_t arrReadyForWrite;
uint8_t state = 0;
uint8_t state1 = 0;

void SOUND_Init(){
    //Clock and frequency initialization
    
    //Timer initialization
    TMR_SetTimer2_Voice();
    ANSDbits.ANSD14 = 0;
    TRISDbits.TRISD14 = 0;
    PORTDbits.RD14 = 1;
//    ANSFbits.ANSF5 = 0;
//    TRISFbits.TRISF5 = 0;
//    PORTFbits.RF5 = 0;
    //DAC1 initialization
    DAC1_Init();
    //DAC2 initialization
    DAC2_Init();
    //SPI Initialization
    spiInit();
    //Pin Initialization
    FLASH_resetPinSetup();
    initLowFrequencyAmplifier();
    //DAC set zero
    DAC1_SetDiscretes(DAC_CENTRAL_VALUE);
    DAC2_SetDiscretes(DAC_CENTRAL_VALUE);
    
}

void initLowFrequencyAmplifier(){
    ANSBbits.ANSB14 = 0;
    TRISBbits.TRISB14 = 0;
    PORTBbits.RB14 = 1;
}

void SOUND_disable(){
    FLASH_resetPinOff();
    PORTBbits.RB14 = 0;
}


void SOUND_setVolume(uint8_t setedVolume){
    //Проверка, чтобы значение громкости звука было в диапазоне 1..10
    if(setedVolume > MAX_VOLUME){
        setedVolume = MAX_VOLUME;
    }
    if(setedVolume < MIN_VOLUME){
        setedVolume = MIN_VOLUME;
    }
    
    //установка делителя. На переменную volume делятся считанные значения звука
    volume = MAX_VOLUME - setedVolume;
}

void SOUND_playFragment(uint32_t adressBegin, uint32_t adressEnd){
    //DAC1_OutputSet(0);
    count = 0;
    uint32_t i = adressBegin;
    uint8_t thisByte = 0;
    uint8_t nextByte = 0;
    uint8_t timerStart = 0;
    uint16_t value = 0;
    uint32_t arrayChecker = 0 ;
//    uint16_t play = 0;
//    uint16_t firstBit = 0;
    uint16_t j = 5;
    arrOneInUse = 1;
    arrTwoInUse = 0;
    while(1){
        flashReadArray(i, 260);
        j = 4; // 4 - число служебных байт в считанном массиве
        while(j < 264){
            //склейка двух байт из памяти в один
            thisByte = cmdFlash[j];
            nextByte = cmdFlash[j+1];
            value = (nextByte << 8) | thisByte;
            
            //определение значения старшего бита
            if( (value >> 15) == 1) {  
                //если первый бит - 1, следовательно число отрицательно. Поэтому
                //число инвертируется
                value = ~value;
                //и сдвигается на 6, т.к. чилсо 16-ти битное, а ЦАП - 10-ти битный
                value = value >> 6;//6 is true value
                //устанавливается громкость
                value /= volume;
                //от установленного "нуля" ЦАП отнимается "отрицательное" значение
                value = DAC_CENTRAL_VALUE - value;//380
            } else {
                //если первый бит - 0, следовательно число положительно. Поэтому
                //число сдвигается на 6, т.к. чилсо 16-ти битное, а ЦАП - 10-ти битный
                value = value >> 6;//6 is true value
                //устанавливается громкость
                value /= volume;
                //к установленному "нуля" ЦАП прибавляется "положительное" значение
                value = DAC_CENTRAL_VALUE + value;
            }
            //Определение в какой из буфферов заносить полученное значение
            if(arrOneInUse == 1){
                sound1[arrayChecker] = value;
            }
            if(arrOneInUse == 0){
                sound2[arrayChecker] = value;
            }
            arrayChecker++;
            j += 2;
            i += 2;
        }
        if( i > adressEnd ){
            count = 0;
//            lastAdress = 0;
            // stop the voice timer
            TMR_Timer2_Voice_Stop();
            timerStart = 0;
            //DAC set zero
            DAC1_SetDiscretes(DAC_CENTRAL_VALUE);
            DAC2_SetDiscretes(DAC_CENTRAL_VALUE);
            break;
        }
        if(!timerStart){
            count = 0;
//            lastAdress = 0;
            // start the voice timer
            TMR_Timer2_Voice_Start();
            timerStart = 1;
        }
        arrayChecker = 0;
        waitForOk();
    }   
}


void wait(){
    uint32_t i = 0;
    for(i = 0; i < 50000; i++);
}

void SOUND_playGluco(uint16_t value){
    uint8_t secondPart = value % 100;
    uint8_t firstPart = value / 100;
    playDigit(firstPart);
    if(firstPart % 10 == 1){
        SOUND_playFragment(TSELAYA_B, TSELAYA_E);
        wait();
    } else {
        SOUND_playFragment(TSELIH_B, TSELIH_E);
        wait();
    }
    playDigit(secondPart);
    if(secondPart < 10){
        if(secondPart % 10 == 1){
            SOUND_playFragment(DESYATAYA_B, DESYATAYA_E);
            wait();
        } else {
            SOUND_playFragment(DESYATIH_B, DESYATIH_E);
            wait();
        }
    } else {
        if(secondPart % 10 == 1){
            SOUND_playFragment(SOTAYA_B, SOTAYA_E);
            wait();
        } else {
            SOUND_playFragment(SOTIH_B, SOTIH_E);
            wait();
        }
    }
    SOUND_playFragment(MMOLPerLITER_B, MMOLPerLITER_E);
    wait();    
}

void playDigit(uint8_t digit){
    if(digit < 10){
        playUnit(digit);
    } else if(digit >= 10 && digit < 20){
      switch(digit){
        case 10:
            SOUND_playFragment(TEN_B, TEN_E);
            wait();
            break;
        case 11:
            SOUND_playFragment(ELEVEN_B, ELEVEN_E);
            wait();
            break;
        case 12:
            SOUND_playFragment(TWELVE_B, TWELVE_E);
            wait();
            break;
        case 13:
            SOUND_playFragment(THIRTEEN_B, THIRTEEN_E);
            wait();
            break;
        case 14:
            SOUND_playFragment(FOURTEEN_B, FOURTEEN_E);
            wait();
            break;
        case 15:
            SOUND_playFragment(FIFTEEN_B, FIFTEEN_E);
            wait();
            break;
        case 16:
            SOUND_playFragment(SIXTEEN_B, SIXTEEN_E);
            wait();
            break;
        case 17:
            SOUND_playFragment(SEVENTEEN_B, SEVENTEEN_E);
            wait();
            break;
        case 18:
            SOUND_playFragment(EIGHTEEN_B, EIGHTEEN_E);
            wait();
            break;
        case 19:
            SOUND_playFragment(NINETEEN_B, NINETEEN_E);
            wait();
            break;
      }
    } else if(digit >= 20 && digit < 30){
        SOUND_playFragment(TWENTY_B, TWENTY_E);
        wait();
        playUnit(digit % 10);        
    } else if(digit >= 30 && digit < 40){
        SOUND_playFragment(TIRTY_B, TIRTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 40 && digit < 50){
        SOUND_playFragment(FOURTY_B, FOURTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 50 && digit < 60){
        SOUND_playFragment(FIFTY_B, FIFTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 60 && digit < 70){
        SOUND_playFragment(SIXTY_B, SIXTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 70 && digit < 80){
        SOUND_playFragment(SEVENTY_B, SEVENTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 80 && digit < 90){
        SOUND_playFragment(EIGHTY_B, EIGHTY_E);
        wait();
        playUnit(digit % 10);
    } else if(digit >= 90 && digit < 100){
        SOUND_playFragment(NINETY_B, NINETY_E);
        wait();
        playUnit(digit % 10);
    }
}

void playUnit(uint8_t digit){
    switch(digit){
        case 1:
            SOUND_playFragment(ODNA_B, ODNA_E);
            wait();
            break;
        case 2:
            SOUND_playFragment(DVE_B, DVE_E);
            wait();
            break;
        case 3:
            SOUND_playFragment(THREE_B, THREE_E);
            wait();
            break;
        case 4:
            SOUND_playFragment(FOUR_B, FOUR_E);
            wait();
            break;
        case 5:
            SOUND_playFragment(FIVE_B, FIVE_E);
            wait();
            break;
        case 6:
            SOUND_playFragment(SIX_B, SIX_E);
            wait();
            break;
        case 7:
            SOUND_playFragment(SEVEN_B, SEVEN_E);
            wait();
            break;
        case 8:
            SOUND_playFragment(EIGHT_B, EIGHT_E);
            wait();
            break;
        case 9:
            SOUND_playFragment(NINE_B, NINE_E);
            wait();
            break;
    }
}

void Tmr2_ISR(void)                    
  {  
    state = !state;
    PORTDbits.RD14 = state;
     if(count == 130){
        count = 0;
        arrTwoInUse = !arrTwoInUse;
    }
    if(count == 67){        
        arrOneInUse = !arrOneInUse;
        arrReadyForWrite = 1;
    }
    if(arrTwoInUse == 0){
      DAC1_SetDiscretes(sound1[count]);
      DAC2_SetDiscretes(1023-sound1[count]);
    }
    if(arrTwoInUse == 1){
      DAC1_SetDiscretes(sound2[count]); 
      DAC2_SetDiscretes(1023-sound2[count]);
    }
    
    count++;
//    lastAdress++;
   }

void waitForOk(){
    while(1){
       if(arrReadyForWrite){
           arrReadyForWrite = 0;
           break;
       } 
    }
}

void SOUND_playGlucoD(uint16_t value){
    uint8_t secondPart = value % 100;
    uint8_t firstPart = value / 100;
    playDigitD(firstPart);
    if(firstPart % 10 == 1){
        SOUND_playFragment(TSELAYA_B_D, TSELAYA_E_D);
        wait();
    } else {
        SOUND_playFragment(TSELIH_B_D, TSELIH_E_D);
        wait();
    }
    playDigitD(secondPart);
    if(secondPart < 10){
        if(secondPart % 10 == 1){
            SOUND_playFragment(DESYATAYA_B_D, DESYATAYA_E_D);
            wait();
        } else {
            SOUND_playFragment(DESYATIH_B_D, DESYATIH_E_D);
            wait();
        }
    } else {
        if(secondPart % 10 == 1){
            SOUND_playFragment(SOTAYA_B_D, SOTAYA_E_D);
            wait();
        } else {
            SOUND_playFragment(SOTIH_B_D, SOTIH_E_D);
            wait();
        }
    }
    SOUND_playFragment(MMOLPerLITER_B_D, MMOLPerLITER_E_D);
    wait();    
}

void playDigitD(uint8_t digit){
    if(digit < 10){
        playUnitD(digit);
    } else if(digit >= 10 && digit < 20){
      switch(digit){
        case 10:
            SOUND_playFragment(TEN_B_D, TEN_E_D);
            wait();
            break;
        case 11:
            SOUND_playFragment(ELEVEN_B_D, ELEVEN_E_D);
            wait();
            break;
        case 12:
            SOUND_playFragment(TWELVE_B_D, TWELVE_E_D);
            wait();
            break;
        case 13:
            SOUND_playFragment(THIRTEEN_B_D, THIRTEEN_E_D);
            wait();
            break;
        case 14:
            SOUND_playFragment(FOURTEEN_B_D, FOURTEEN_E_D);
            wait();
            break;
        case 15:
            SOUND_playFragment(FIFTEEN_B_D, FIFTEEN_E_D);
            wait();
            break;
        case 16:
            SOUND_playFragment(SIXTEEN_B_D, SIXTEEN_E_D);
            wait();
            break;
        case 17:
            SOUND_playFragment(SEVENTEEN_B_D, SEVENTEEN_E_D);
            wait();
            break;
        case 18:
            SOUND_playFragment(EIGHTEEN_B_D, EIGHTEEN_E_D);
            wait();
            break;
        case 19:
            SOUND_playFragment(NINETEEN_B_D, NINETEEN_E_D);
            wait();
            break;
      }
    } else if(digit >= 20 && digit < 30){
        SOUND_playFragment(TWENTY_B_D, TWENTY_E_D);
        wait();
        playUnitD(digit % 10);        
    } else if(digit >= 30 && digit < 40){
        SOUND_playFragment(TIRTY_B_D, TIRTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 40 && digit < 50){
        SOUND_playFragment(FOURTY_B_D, FOURTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 50 && digit < 60){
        SOUND_playFragment(FIFTY_B_D, FIFTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 60 && digit < 70){
        SOUND_playFragment(SIXTY_B_D, SIXTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 70 && digit < 80){
        SOUND_playFragment(SEVENTY_B_D, SEVENTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 80 && digit < 90){
        SOUND_playFragment(EIGHTY_B_D, EIGHTY_E_D);
        wait();
        playUnitD(digit % 10);
    } else if(digit >= 90 && digit < 100){
        SOUND_playFragment(NINETY_B_D, NINETY_E_D);
        wait();
        playUnitD(digit % 10);
    }
}

void playUnitD(uint8_t digit){
    switch(digit){
        case 1:
            SOUND_playFragment(ODNA_B_D, ODNA_E_D);
            wait();
            break;
        case 2:
            SOUND_playFragment(DVE_B_D, DVE_E_D);
            wait();
            break;
        case 3:
            SOUND_playFragment(THREE_B_D, THREE_E_D);
            wait();
            break;
        case 4:
            SOUND_playFragment(FOUR_B_D, FOUR_E_D);
            wait();
            break;
        case 5:
            SOUND_playFragment(FIVE_B_D, FIVE_E_D);
            wait();
            break;
        case 6:
            SOUND_playFragment(SIX_B_D, SIX_E_D);
            wait();
            break;
        case 7:
            SOUND_playFragment(SEVEN_B_D, SEVEN_E_D);
            wait();
            break;
        case 8:
            SOUND_playFragment(EIGHT_B_D, EIGHT_E_D);
            wait();
            break;
        case 9:
            SOUND_playFragment(NINE_B_D, NINE_E_D);
            wait();
            break;
    }
}
    
void SOUND_playGlucoR(uint16_t value){
    uint8_t secondPart = value % 100;
    uint8_t firstPart = value / 100;
    playDigitR(firstPart);
    if(firstPart % 10 == 1){
        SOUND_playFragment(TSELAYA_B_R, TSELAYA_E_R);
        wait();
    } else {
        SOUND_playFragment(TSELIH_B_R, TSELIH_E_R);
        wait();
    }
    playDigitR(secondPart);
    if(secondPart < 10){
        if(secondPart % 10 == 1){
            SOUND_playFragment(DESYATAYA_B_R, DESYATAYA_E_R);
            wait();
        } else {
            SOUND_playFragment(DESYATIH_B_R, DESYATIH_E_R);
            wait();
        }
    } else {
        if(secondPart % 10 == 1){
            SOUND_playFragment(SOTAYA_B_R, SOTAYA_E_R);
            wait();
        } else {
            SOUND_playFragment(SOTIH_B_R, SOTIH_E_R);
            wait();
        }
    }
    SOUND_playFragment(MMOLPerLITER_B_R, MMOLPerLITER_E_R);
    wait();    
}

void playDigitR(uint8_t digit){
    if(digit < 10){
        playUnitR(digit);
    } else if(digit >= 10 && digit < 20){
      switch(digit){
        case 10:
            SOUND_playFragment(TEN_B_R, TEN_E_R);
            wait();
            break;
        case 11:
            SOUND_playFragment(ELEVEN_B_R, ELEVEN_E_R);
            wait();
            break;
        case 12:
            SOUND_playFragment(TWELVE_B_R, TWELVE_E_R);
            wait();
            break;
        case 13:
            SOUND_playFragment(THIRTEEN_B_R, THIRTEEN_E_R);
            wait();
            break;
        case 14:
            SOUND_playFragment(FOURTEEN_B_R, FOURTEEN_E_R);
            wait();
            break;
        case 15:
            SOUND_playFragment(FIFTEEN_B_R, FIFTEEN_E_R);
            wait();
            break;
        case 16:
            SOUND_playFragment(SIXTEEN_B_R, SIXTEEN_E_R);
            wait();
            break;
        case 17:
            SOUND_playFragment(SEVENTEEN_B_R, SEVENTEEN_E_R);
            wait();
            break;
        case 18:
            SOUND_playFragment(EIGHTEEN_B_R, EIGHTEEN_E_R);
            wait();
            break;
        case 19:
            SOUND_playFragment(NINETEEN_B_R, NINETEEN_E_R);
            wait();
            break;
      }
    } else if(digit >= 20 && digit < 30){
        SOUND_playFragment(TWENTY_B_R, TWENTY_E_R);
        wait();
        playUnitR(digit % 10);        
    } else if(digit >= 30 && digit < 40){
        SOUND_playFragment(TIRTY_B_R, TIRTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 40 && digit < 50){
        SOUND_playFragment(FOURTY_B_R, FOURTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 50 && digit < 60){
        SOUND_playFragment(FIFTY_B_R, FIFTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 60 && digit < 70){
        SOUND_playFragment(SIXTY_B_R, SIXTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 70 && digit < 80){
        SOUND_playFragment(SEVENTY_B_R, SEVENTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 80 && digit < 90){
        SOUND_playFragment(EIGHTY_B_R, EIGHTY_E_R);
        wait();
        playUnitR(digit % 10);
    } else if(digit >= 90 && digit < 100){
        SOUND_playFragment(NINETY_B_R, NINETY_E_R);
        wait();
        playUnitR(digit % 10);
    }
}

void playUnitR(uint8_t digit){
    switch(digit){
        case 1:
            SOUND_playFragment(ODNA_B_R, ODNA_E_R);
            wait();
            break;
        case 2:
            SOUND_playFragment(DVE_B_R, DVE_E_R);
            wait();
            break;
        case 3:
            SOUND_playFragment(THREE_B_R, THREE_E_R);
            wait();
            break;
        case 4:
            SOUND_playFragment(FOUR_B_R, FOUR_E_R);
            wait();
            break;
        case 5:
            SOUND_playFragment(FIVE_B_R, FIVE_E_R);
            wait();
            break;
        case 6:
            SOUND_playFragment(SIX_B_R, SIX_E_R);
            wait();
            break;
        case 7:
            SOUND_playFragment(SEVEN_B_R, SEVEN_E_R);
            wait();
            break;
        case 8:
            SOUND_playFragment(EIGHT_B_R, EIGHT_E_R);
            wait();
            break;
        case 9:
            SOUND_playFragment(NINE_B_R, NINE_E_R);
            wait();
            break;
    }
}


void SOUND_playGlucoRN(uint16_t value){
    uint8_t secondPart = value % 100;
    uint8_t firstPart = value / 100;
    playDigitRN(firstPart);
    if(firstPart % 10 == 1){
        SOUND_playFragment(TSELAYA_B_RN, TSELAYA_E_RN);
        wait();
    } else {
        SOUND_playFragment(TSELIH_B_RN, TSELIH_E_RN);
        wait();
    }
    playDigitRN(secondPart);
    if(secondPart < 10){
        if(secondPart % 10 == 1){
            SOUND_playFragment(DESYATAYA_B_R, DESYATAYA_E_R);
            wait();
        } else {
            SOUND_playFragment(DESYATIH_B_R, DESYATIH_E_R);
            wait();
        }
    }
    SOUND_playFragment(MMOLPerLITER_B_RN, MMOLPerLITER_E_RN);
    wait();    
}

void playDigitRN(uint8_t digit){
    if(digit < 10){
        playUnitRN(digit);
    } else if(digit >= 10 && digit < 20){
      switch(digit){
        case 10:
            SOUND_playFragment(TEN_B_RN, TEN_E_RN);
            wait();
            break;
        case 11:
            SOUND_playFragment(ELEVEN_B_RN, ELEVEN_E_RN);
            wait();
            break;
        case 12:
            SOUND_playFragment(TWELVE_B_RN, TWELVE_E_RN);
            wait();
            break;
        case 13:
            SOUND_playFragment(THIRTEEN_B_RN, THIRTEEN_E_RN);
            wait();
            break;
        case 14:
            SOUND_playFragment(FOURTEEN_B_RN, FOURTEEN_E_RN);
            wait();
            break;
        case 15:
            SOUND_playFragment(FIFTEEN_B_RN, FIFTEEN_E_RN);
            wait();
            break;
        case 16:
            SOUND_playFragment(SIXTEEN_B_RN, SIXTEEN_E_RN);
            wait();
            break;
        case 17:
            SOUND_playFragment(SEVENTEEN_B_RN, SEVENTEEN_E_RN);
            wait();
            break;
        case 18:
            SOUND_playFragment(EIGHTEEN_B_RN, EIGHTEEN_E_RN);
            wait();
            break;
        case 19:
            SOUND_playFragment(NINETEEN_B_RN, NINETEEN_E_RN);
            wait();
            break;
      }
    } else if(digit >= 20 && digit < 30){
        SOUND_playFragment(TWENTY_B_RN, TWENTY_E_RN);
        wait();
        playUnitRN(digit % 10);        
    } else if(digit >= 30 && digit < 40){
        SOUND_playFragment(TIRTY_B_RN, TIRTY_E_RN);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 40 && digit < 50){
        SOUND_playFragment(FOURTY_B_R, FOURTY_E_R);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 50 && digit < 60){
        SOUND_playFragment(FIFTY_B_R, FIFTY_E_R);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 60 && digit < 70){
        SOUND_playFragment(SIXTY_B_R, SIXTY_E_R);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 70 && digit < 80){
        SOUND_playFragment(SEVENTY_B_R, SEVENTY_E_R);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 80 && digit < 90){
        SOUND_playFragment(EIGHTY_B_R, EIGHTY_E_R);
        wait();
        playUnitRN(digit % 10);
    } else if(digit >= 90 && digit < 100){
        SOUND_playFragment(NINETY_B_R, NINETY_E_R);
        wait();
        playUnitRN(digit % 10);
    }
}

void playUnitRN(uint8_t digit){
    switch(digit){
        case 1:
            SOUND_playFragment(ODNA_B_RN, ODNA_E_RN);
            wait();
            break;
        case 2:
            SOUND_playFragment(DVE_B_RN, DVE_E_RN);
            wait();
            break;
        case 3:
            SOUND_playFragment(THREE_B_RN, THREE_E_RN);
            wait();
            break;
        case 4:
            SOUND_playFragment(FOUR_B_RN, FOUR_E_RN);
            wait();
            break;
        case 5:
            SOUND_playFragment(FIVE_B_RN, FIVE_E_RN);
            wait();
            break;
        case 6:
            SOUND_playFragment(SIX_B_RN, SIX_E_RN);
            wait();
            break;
        case 7:
            SOUND_playFragment(SEVEN_B_RN, SEVEN_E_RN);
            wait();
            break;
        case 8:
            SOUND_playFragment(EIGHT_B_RN, EIGHT_E_RN);
            wait();
            break;
        case 9:
            SOUND_playFragment(NINE_B_RN, NINE_E_RN);
            wait();
            break;
    }
}



