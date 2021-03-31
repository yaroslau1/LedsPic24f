/*
 * File:   sensor.c
 * Author: User
 *
 * Created on July 16, 2020, 2:18 PM
 */


#include "xc.h"
#include <p24FJ128GC010.h>
#include "sensor.h"

void sensorInit(void) {
    //setup CTMU 
    //CTMUCON
    CTMUCON1bits.CTMUEN =   0;      //make sure CTMU is disabled
    CTMUCON1bits.CTMUSIDL = 0;      //CTMU continues to run in idle mode
    CTMUCON1bits.TGEN =     0;      //disable edge delay generation mode of the CTMU
    CTMUCON1bits.EDGEN =    0;      //edges are blocked
    CTMUCON1bits.EDGSEQEN = 0;      //edge sequence not needed
    CTMUCON1bits.IDISSEN =  0;      //Do not ground the current source
    CTMUCON1bits.CTTRIG =   0;      //Trigger Output is disabled
    CTMUCON2bits.EDG2POL =  0;
    CTMUCON2bits.EDG2SEL =  0x3;    //Edge2 Src = OC1 (don’t care)
    CTMUCON2bits.EDG1POL =  1;
    CTMUCON2bits.EDG1SEL =  0x3;    //Edge1 Src = Timer1 (don’t care)
    //CTMUICON
    CTMUICON = 0x300;             //55uA
    CTMUICONbits.ITRIM = 0;           //Nominal - No Adjustment
    
    //setup A/D converter
    ADTBL6bits.UCTMU = 1;
   // ADCON2bits.PVCFG = 0b00;
//    AD1PCFG = 0x0000;
    //ADCON1 =  0x0000;
    //ADCHS =   0x0000;
    //ADTBL6bits.ADCH = 22;//select the analog channel 0
  //  ADCSSL=0x0000;
//    ADCON1bits.FORM = 0x0;       //Unsigned fractional format
//    ADCON3 = 0x0000;             //bits.ADRC=0;
//    ADCON2 = 0x0000;
//    ADCON1bits.ADON = 1;         //Turn On A/D
    CTMUCON1bits.CTMUEN = 1;       //Enable CTMU
}

float sensorRead(void) {
    //Read CTMU (Get the raw sensor reading)
   // AD1PCFGL= 0xFFFF;                            //set all A/D channels to digital I/O pins
    TRISA = 0x0000;
    LATA  = 0x0000;
    PORTA = 0x0000;                              //set all channels to logical 0 outputs
    Nop(); Nop(); Nop(); Nop();Nop(); Nop(); Nop(); Nop();
    //Wait for charge to drain
    TRISA = 0x20;                     //set selected channel to input
 //   AD1PCFGL = ~ADSELECT[Index];                 //set selected channel to analog A/D input
    Nop(); Nop(); Nop(); Nop();Nop(); Nop(); Nop(); Nop();
    //wait for A/D to connect to channel
    ADTBL6 = 22;
 //   AD1CHS = Index;                              //select A/D channel
    CTMUCON1bits.IDISSEN  = 1;                    //Drain any charge on the A/D circuit
    Nop(); Nop(); Nop(); Nop(); Nop();
    //Wait for charge to drain
    CTMUCON1bits.IDISSEN = 0;                     //Stop discharge of A/D circuit
    IFS0bits.AD1IF          = 0;                 //Make sure A/D interrupt flag = 0
    ADL0CONLbits.SAMP = 1;                 //Manually start sampling
    CTMUCON2bits.EDG2STAT    = 0;                 // Make sure edge2 is 0
    CTMUCON2bits.EDG1STAT    = 1;                 // Set edge1 - Start Charge
    int count;
    int loopCount = 65000;
    for (count = 0; count < loopCount; count++);   // Delay for CTMU charge time
    CTMUCON2bits.EDG1STAT    = 0;                 //Clear edge1 - Stop Charge
    IFS0bits.AD1IF          = 0;                
    ADL0CONLbits.SAMP = 0;                      //Clear SAMP bit to begin manual A/D conversion
    while(!IFS0bits.AD1IF);                      //Wait for the A/D conversion to finishimmediate
    float chanel_22 = ADRES6;
   // Value = ADC1BUF0;                   //Read the value from the A/D conversion
    ADL0CONLbits.SAMP = 0;
    IFS0bits.AD1IF          = 0;
//    ADCON1bits.DONE        = 0;                 //Make sure A/D bits are cleared
    //End of CTMU read
    ADL0CONLbits.SAMP = 1;
    return chanel_22;
}
