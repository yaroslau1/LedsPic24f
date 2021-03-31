/* 
 * File:  sound.h 
 * Author: Yaraslau
 * Comments:
 * Revision history: 
 * Created on 19 февраля 2021 г., 8:56
 */

/**
  @Company
    Delfidia ltd.

  @File Name
    sound.h

  @Summary
    This is the header for sound using.

  @Description
*/


#include <xc.h> // include processor files - each processor file is guarded.  

/**
  @Summary
    This function sets volume of sound.

  @Description
    This function sets volume of sound. The maximum volume is related to MAX_VOLUME.
    This function sets volume variable which uses as devider for change volume of all aplication.

  @Param
    setedVolume - Input value to be seted as aplication volume

  @Returns 
    None
 
  @Comment
 
  @Example
    <code>
        int setVolume = 8;
        SOUND_setVolume(setVolume);
    </code>
  
*/
void SOUND_setVolume(uint8_t setedVolume);

/**
  @Summary
    This function initializes all periphirial for work with sound.

  @Description
    This function includes TMR2, DAC1, DAC2, SPI inits and
    turns on 43(RB14) and 76(RD1) pins.\n
 * 43(RB14) - for SD pin in PAM8302A\n
 * 76(RD1) - for RESET pin in FLASH W25Q...

  @Param
    none

  @Returns 
    None
 
  @Comment
 
  @Example
    <code>
        int measuredValue = 103;\n
        SOUND_Init(); \n
        playGlucoD(measuredValue);\n
        SOUND_disable();
    </code>
  
*/
void SOUND_Init();
/**
  @Summary
    This function turn off all periphirial for work with sound.

  @Description
    This function turns off 43(RB14) and 76(RD1) pins.\n
 * 43(RB14) - for SD pin in PAM8302A\n
 * 76(RD1) - for RESET pin in FLASH W25Q...

  @Param
    none

  @Returns 
    None
 
  @Comment
 
  @Example
    <code>
        int measuredValue = 103;\n
        SOUND_Init(); \n
        SOUND_playGlucoD(measuredValue);\n
        SOUND_disable();
    </code>
  
*/
void SOUND_disable();
void initLowFrequencyAmplifier();


void SOUND_playFragment(uint32_t adressBegin, uint32_t adressEnd);
void SOUND_playGluco(uint16_t value);
void playDigit(uint8_t digit);
void playUnit(uint8_t digit);
void wait();
void Tmr2_ISR(void);
void waitForOk();

void SOUND_playGlucoD(uint16_t value);
void playDigitD(uint8_t digit);
void playUnitD(uint8_t digit);
void SOUND_playGlucoR(uint16_t value);
void playDigitR(uint8_t digit);
void playUnitR(uint8_t digit);
void SOUND_playGlucoRN(uint16_t value);
void playDigitRN(uint8_t digit);
void playUnitRN(uint8_t digit);

extern uint8_t state1;

#define MAX_VOLUME 10
#define MIN_VOLUME 1

#define DAC_CENTRAL_VALUE 512

#define ODIN_B 0x28
#define ODIN_E 0x259F

#define DVA_B 0x28B0
#define DVA_E 0x481F

#define DVE_B 0x494A
#define DVE_E 0x692F

#define ODNA_B 0x6AC0
#define ODNA_E 0x923F

#define THREE_B 0x9326
#define THREE_E 0xA82B

#define FOUR_B 0xA918
#define FOUR_E 0xDBCF

#define FIVE_B 0xDD30
#define FIVE_E 0xF31F

#define SIX_B 0xF470
#define SIX_E 0x1227F

#define SEVEN_B 0x123D6
#define SEVEN_E 0x143DF

#define EIGHT_B 0x14550
#define EIGHT_E 0x16A1F

#define NINE_B 0x16D60
#define NINE_E 0x1973F

#define TEN_B 0x19890
#define TEN_E 0x1C69F

#define ELEVEN_B 0x1C7F0
#define ELEVEN_E 0x1FDEF

#define TWELVE_B 0x1FF40
#define TWELVE_E 0x2358F

#define THIRTEEN_B 0x236F0
#define THIRTEEN_E 0x26A4F

#define FOURTEEN_B 0x26BB0
#define FOURTEEN_E 0x2B25F

#define FIFTEEN_B 0x2B3B8
#define FIFTEEN_E 0x2E63F

#define SIXTEEN_B 0x2E7A0
#define SIXTEEN_E 0x325EF

#define SEVENTEEN_B 0x32740
#define SEVENTEEN_E 0x358AF

#define EIGHTEEN_B 0x35A00
#define EIGHTEEN_E 0x3977F

#define NINETEEN_B 0x398D0
#define NINETEEN_E 0x3D4EF

#define TWENTY_B 0x3D640
#define TWENTY_E 0x4045F

#define TIRTY_B 0x405A0
#define TIRTY_E 0x4298F

#define FOURTY_B 0x424D0
#define FOURTY_E 0x4468F

#define FIFTY_B 0x447D0
#define FIFTY_E 0x474FF

#define SIXTY_B 0x47650
#define SIXTY_E 0x4B1DF

#define SEVENTY_B 0x4B330
#define SEVENTY_E 0x4E13F

#define EIGHTY_B 0x4E280
#define EIGHTY_E 0x5190F

#define NINETY_B 0x51A60
#define NINETY_E 0x54D9F

#define TSELAYA_B 0x54EF0
#define TSELAYA_E 0x5819F

#define TSELIH_B 0x582F0
#define TSELIH_E 0x5A30F

#define SOTAYA_B 0x5A460
#define SOTAYA_E 0x5CB1F

#define SOTIH_B 0x5CC70
#define SOTIH_E 0x5F05F

#define DESYATAYA_B 0x5F1B0
#define DESYATAYA_E 0x62B0F

#define DESYATIH_B 0x62C60
#define DESYATIH_E 0x6607F

#define MMOLPerLITER_B 0x661D0
#define MMOLPerLITER_E 0x6C64F


//*********************************

#define ODIN_B_D 0x71190
#define ODIN_E_D 0x7385F

#define DVA_B_D 0x7B740
#define DVA_E_D 0x7D7CE

#define DVE_B_D 0x80BE0
#define DVE_E_D 0x82B5F

#define ODNA_B_D 0x76730
#define ODNA_E_D 0x789EF

#define THREE_B_D 0x86080
#define THREE_E_D 0x8784F

#define FOUR_B_D 0x8A2D0
#define FOUR_E_D 0x8CD2F

#define FIVE_B_D 0x8F8F0
#define FIVE_E_D 0x9177F

#define SIX_B_D 0x946F0
#define SIX_E_D 0x971DF

#define SEVEN_B_D 0x9B4D0
#define SEVEN_E_D 0x9D7BF

#define EIGHT_B_D 0xA1CE0
#define EIGHT_E_D 0xA491F

#define NINE_B_D 0xA7EB0
#define NINE_E_D 0xAAB4F

#define TEN_B_D 0xAEDA0
#define TEN_E_D 0xB1BAF

#define ELEVEN_B_D 0xB4380
#define ELEVEN_E_D 0xB7C3F

#define TWELVE_B_D 0xB8E40
#define TWELVE_E_D 0xBC84F

#define THIRTEEN_B_D 0xBE690
#define THIRTEEN_E_D 0xC1A9F

#define FOURTEEN_B_D 0xC4230
#define FOURTEEN_E_D 0xC801F

#define FIFTEEN_B_D 0xC9F70
#define FIFTEEN_E_D 0xCD55F

#define SIXTEEN_B_D 0xCE850
#define SIXTEEN_E_D 0xD280F

#define SEVENTEEN_B_D 0xD4BF0
#define SEVENTEEN_E_D 0xD875F

#define EIGHTEEN_B_D 0xDAE50
#define EIGHTEEN_E_D 0xDEFDF

#define NINETEEN_B_D 0xE1D60
#define NINETEEN_E_D 0xE61CF

#define TWENTY_B_D 0xE95A0
#define TWENTY_E_D 0xECACF

#define TIRTY_B_D 0xEEF80
#define TIRTY_E_D 0xF193F

#define FOURTY_B_D 0xF3380
#define FOURTY_E_D 0xF603F

#define FIFTY_B_D 0xF9930
#define FIFTY_E_D 0xFCADF

#define SIXTY_B_D 0xFF8D0
#define SIXTY_E_D 0x10314F

#define SEVENTY_B_D 0x106510
#define SEVENTY_E_D 0x1099EF

#define EIGHTY_B_D 0x10C530
#define EIGHTY_E_D 0x11019F

#define NINETY_B_D 0x112750
#define NINETY_E_D 0x115F4F

#define TSELAYA_B_D 0x11B530
#define TSELAYA_E_D 0x11DFFF

#define TSELIH_B_D 0x120B90
#define TSELIH_E_D 0x1236DF

#define SOTAYA_B_D 0x125400
#define SOTAYA_E_D 0x12801F

#define SOTIH_B_D 0x12BB00
#define SOTIH_E_D 0x12E6BF

#define DESYATAYA_B_D 0x131640
#define DESYATAYA_E_D 0x134C4F

#define DESYATIH_B_D 0x136810
#define DESYATIH_E_D 0x13A13F

#define MMOLPerLITER_B_D 0x13DFC0
#define MMOLPerLITER_E_D 0x143EFF


//*********************************

#define ODIN_B_R 0x1493F0
#define ODIN_E_R 0x14FE6F

#define DVA_B_R 0x159010
#define DVA_E_R 0x15B84F

#define DVE_B_R 0x15CB40
#define DVE_E_R 0x15F75F

#define ODNA_B_R 0x1534F0
#define ODNA_E_R 0x156B3F

#define THREE_B_R 0x1604B0
#define THREE_E_R 0x16277F

#define FOUR_B_R 0x163E00
#define FOUR_E_R 0x16706F

#define FIVE_B_R 0x1688F0
#define FIVE_E_R 0x16ACDF

#define SIX_B_R 0x16BF40
#define SIX_E_R 0x16F2FF

#define SEVEN_B_R 0x16FC00
#define SEVEN_E_R 0x1728CF

#define EIGHT_B_R 0x174670
#define EIGHT_E_R 0x17706F

#define NINE_B_R 0x177B80
#define NINE_E_R 0x17A8BF

#define TEN_B_R 0x17B5F0
#define TEN_E_R 0x17E54F

#define ELEVEN_B_R 0x17EE30
#define ELEVEN_E_R 0x182ECF

#define TWELVE_B_R 0x183500
#define TWELVE_E_R 0x18916F

#define THIRTEEN_B_R 0x189950
#define THIRTEEN_E_R 0x18DE0F

#define FOURTEEN_B_R 0x18EAA0
#define FOURTEEN_E_R 0x19326F

#define FIFTEEN_B_R 0x194030
#define FIFTEEN_E_R 0x19755F

#define SIXTEEN_B_R 0x1977B90
#define SIXTEEN_E_R 0x19BF3F

#define SEVENTEEN_B_R 0x19C7D0
#define SEVENTEEN_E_R 0x1A077F

#define EIGHTEEN_B_R 0x1A1610
#define EIGHTEEN_E_R 0x1A5A0F

#define NINETEEN_B_R 0x1A66A0
#define NINETEEN_E_R 0x1AAB7F

#define TWENTY_B_R 0x1AB730
#define TWENTY_E_R 0x1AEFFF

#define TIRTY_B_R 0x1B0040
#define TIRTY_E_R 0x1B349F

#define FOURTY_B_R 0x1B42A0
#define FOURTY_E_R 0x1B738F

#define FIFTY_B_R 0x1B7C30
#define FIFTY_E_R 0x1BB16F

#define SIXTY_B_R 0x1BB910
#define SIXTY_E_R 0x1BEEFF

#define SEVENTY_B_R 0x1BF970
#define SEVENTY_E_R 0x1C2D5F

#define EIGHTY_B_R 0x1C33A0
#define EIGHTY_E_R 0x1C720F

#define NINETY_B_R 0x1C7AD0
#define NINETY_E_R 0x1CBB1F

#define TSELAYA_B_R 0x1CF7A0
#define TSELAYA_E_R 0x1D2AEF

#define TSELIH_B_R 0x1D3560
#define TSELIH_E_R 0x1D67AF

#define SOTAYA_B_R 0x1D6EF0
#define SOTAYA_E_R 0x1DA89F

#define SOTIH_B_R 0x1DAE40
#define SOTIH_E_R 0x1DE41F

#define DESYATAYA_B_R 0x1DECD0
#define DESYATAYA_E_R 0x1E276F

#define DESYATIH_B_R 0x1E2E20
#define DESYATIH_E_R 0x1E6A1F

#define MMOLPerLITER_B_R 0x1E70A0
#define MMOLPerLITER_E_R 0x1EC90F




//*********************************

#define ODIN_B_RN 0x1
#define ODIN_E_RN 0x1

#define DVA_B_RN 0x1
#define DVA_E_RN 0x1

#define DVE_B_RN 0x2841F0
#define DVE_E_RN 0x287FAF

#define ODNA_B_RN 0x2800A0
#define ODNA_E_RN 0x28400F

#define THREE_B_RN 0x287FF0
#define THREE_E_RN 0x28B48F

#define FOUR_B_RN 0x28B550
#define FOUR_E_RN 0x28EB8F

#define FIVE_B_RN 0x28EC40
#define FIVE_E_RN 0x292A3F

#define SIX_B_RN 0x292AF0
#define SIX_E_RN 0x2968EF

#define SEVEN_B_RN 0x2969F0
#define SEVEN_E_RN 0x298B0F

#define EIGHT_B_RN 0x298BF0
#define EIGHT_E_RN 0x29C9BF

#define NINE_B_RN 0x29C9F0
#define NINE_E_RN 0x2A086F

#define TEN_B_RN 0x2A08F0
#define TEN_E_RN 0x2A471F

#define ELEVEN_B_RN 0x2A47F0
#define ELEVEN_E_RN 0x2A956F

#define TWELVE_B_RN 0x2A95F0
#define TWELVE_E_RN 0x2AE3BF

#define THIRTEEN_B_RN 0x2AE3F0
#define THIRTEEN_E_RN 0x2B39DF

#define FOURTEEN_B_RN 0x2B31F0
#define FOURTEEN_E_RN 0x2B9F9F

#define FIFTEEN_B_RN 0x2B9FF0
#define FIFTEEN_E_RN 0x2BE9FF

#define SIXTEEN_B_RN 0x2BEAF0
#define SIXTEEN_E_RN 0x2C47EF

#define SEVENTEEN_B_RN 0x2C48F0
#define SEVENTEEN_E_RN 0x2C9E0F

#define EIGHTEEN_B_RN 0x2C9EF0
#define EIGHTEEN_E_RN 0x2CF44F

#define NINETEEN_B_RN 0x2CF4F0
#define NINETEEN_E_RN 0x2D427F

#define TWENTY_B_RN 0x2D42F0
#define TWENTY_E_RN 0x2D795F

#define TIRTY_B_RN 0x2D79F0
#define TIRTY_E_RN 0x2DB03F

#define FOURTY_B_RN 0x1
#define FOURTY_E_RN 0x1

#define FIFTY_B_RN 0x1
#define FIFTY_E_RN 0x1

#define SIXTY_B_RN 0x1
#define SIXTY_E_RN 0x1

#define SEVENTY_B_RN 0x1
#define SEVENTY_E_RN 0x1

#define EIGHTY_B_RN 0x1
#define EIGHTY_E_RN 0x1

#define NINETY_B_RN 0x1
#define NINETY_E_RN 0x1

#define TSELAYA_B_RN 0x2DB0F0
#define TSELAYA_E_RN 0x2DEE0F

#define TSELIH_B_RN 0x2DEFF0
#define TSELIH_E_RN 0x2E2FDF

#define DESYATAYA_B_RN 0x1
#define DESYATAYA_E_RN 0x1

#define DESYATIH_B_RN 0x1
#define DESYATIH_E_RN 0x1

#define MMOLPerLITER_B_RN 0x2E3120
#define MMOLPerLITER_E_RN 0x2E900F

