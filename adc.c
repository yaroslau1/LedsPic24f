/*
 * File:   adc.c
 * Author: User
 *
 * Created on January 21, 2020, 3:20 PM
 */


#include <p24FJ128GC010.h>
#include <stdint.h>

#include "xc.h"


uint16_t chanel_21;
uint16_t chanel_23;

void ADC_Init(){
//    ADCON1 = 0;
//    ADCON2 = 0;
//    ADCON3 = 0;
//    
//    ADCON1bits.FORM = 0;
//    ADCON1bits.
//    
//    ADCON2bits.PVCFG = 0;
//    ADCON2bits.NVCFG = 0;
//    ADCON2bits.BUFORG = 1;
//    
//    //ADCON3bits.ADRC = 1;
//    //ADCON3bits.ADCS = 15;
//    
//    ADL0CONL = 0;
//    ADL0CONH = 0;
//    
//    ADL0CONHbits.ASEN = 1;
//    ADL0CONHbits.SLINT = 0x02;
//    
//    ADL0CONL = (0x8000 & 0x7FFF) | 0x4000;
//    
// //   ADTBL0bits.ADCH = 21;
// //   ADTBL1bits.ADCH = 42;
//    
//    ADTBL0 = 21;
//    ADTBL1 = 42;
//    
//    ADCON1bits.ADON = 1;               //Enable ADC 12-bit module   
//    while (ADSTATHbits.ADREADY == 0);  //Wait for ready ADC
//            
//    ADCON1bits.ADCAL = 1;              //Internal calibration ADC 12-bit
//    while (ADSTATHbits.ADREADY == 0);  //Wait for ready ADC
//    
//    ADL0CONLbits.SLEN = 1;
//    ADL0CONLbits.SAMP = 1;             //Begin conversion
//    
    
    ADCON1bits.ADON = 0;
    ADCON1bits.ADSIDL = 1;
    ADCON1bits.ADSLP = 1;
    ADCON1bits.FORM = 0b0100;
    ADCON1bits.PUMPEN = 0;    
    ADCON1bits.ADCAL = 0;
    ADCON1bits.PWRLVL = 0;

    ADCON2bits.PVCFG = 0b00;
    ADCON2bits.NVCFG = 0;
    ADCON2bits.BUFORG = 1;
    ADCON2bits.RFPUMP = 0;
    
    ADCON3bits.ADRC = 1;
    ADCON3bits.SLEN3 = 0;
    ADCON3bits.SLEN2 = 0;
    ADCON3bits.SLEN1 = 0;
    ADCON3bits.SLEN0 = 1;
    ADCON3bits.ADCS = 0b00000100;
    
    ADL0CONHbits.ASEN = 1;    
    ADL0CONHbits.SLINT = 0b01;
    ADL0CONHbits.WM = 0b00;
    ADL0CONHbits.CM = 0b000;
    ADL0CONHbits.CTMEN = 0;
    ADL0CONHbits.MULCHEN = 0;
    ADL0CONHbits.SAMC = 0b01000;
    
    ADL0CONLbits.SLEN = 0;
    ADL0CONLbits.SAMP = 0;
    ADL0CONLbits.SLENCLR = 0;
    ADL0CONLbits.SLTSRC = 0b00000;
    ADL0CONLbits.THSRC = 1;
    ADL0CONLbits.SLSIZE = 0b11111;
    
    //Set channels for ADC 12-bit (ADTBLn = ANx)
    ADTBL1 = 21;
    ADTBL2 = 23;
    ADTBL3 = 3;
    ADTBL4 = 8;
    ADTBL5 = 9;
 
    ADCON1bits.ADON = 1;               //Enable ADC 12-bit module   
    while (ADSTATHbits.ADREADY == 0);  //Wait for ready ADC

    ADCON1bits.ADCAL = 1;              //Internal calibration ADC 12-bit
    while (ADSTATHbits.ADREADY == 0);  //Wait for ready ADC

    ADL0CONLbits.SAMP = 1;             //Begin conversion
    ADL0CONLbits.SLEN = 1;             //Enable sampling

}

void ADC_getDataFromChanel(){
    IFS0bits.AD1IF = 0;                //Clear flag of interrupt
    ADL0CONLbits.SAMP = 0;             //Stop conversion 
    while(IFS0bits.AD1IF == 0);        //Checking flag of interrupt (if it "1" -> start conversion)
    ADL0CONLbits.SAMP = 1;             //Begin conversion
    chanel_21 = ADRES1;
    chanel_23 = ADRES2;
}
