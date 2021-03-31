/*
 * File:   capacitanceTouch.c
 * Author: User
 *
 * Created on 22 июля 2020 г., 14:31
 */


#include "xc.h"
#include <p24FJ128GC010.h>
#include "capacitanceTouch.h"

#define    CTMU_MODE_EDGE 0
#define    RANGE_0_550uA 1    // .550uA
#define    CTMU_TOUCH_THRESHHOLD_OFFSET 100


void    CtmuCapTouchConfig(unsigned int mode, unsigned int range, signed int trim){
    
    // step 1 Configure the CTMU
    CTMUCON1 = 0x0000;                   // Disable CTMU
    CTMUCON1bits.TGEN = mode;            // Enable/Disable Time Generation mode
    CTMUCON1bits.EDGEN = 0;              // Edges are disabled
    CTMUICONbits.ITRIM = trim;           // Set trim
    CTMUCON1bits.CTTRIG = 0;             // Trigger output disabled
//    CTMUICONbits.IRNG = (range & 3);     // Set range
    
    CTMUCON1 = 0;                        // Edges are disabled, edge controls ignored
    // This line does not apply to all devices
//    CTMUICONbits.IRNG = (range>>2);     // set high bit of range
    
//    CTMUCON2Lbits.IRSTEN = 0;             // Current source reset disabled
//    CTMUCON1bits.IDISSEN = 1;              // Discharge source disabled
    
    // Step 2 Configure the port Ports
//    TRISB = TRISB | (1<<2);               // Set channel 2
//    ANSBbits.ANSB2 = 1;                   // Make AN2 as analog   
//    
//    // Step 3 configure the ADC
//    ADCHSbits.CH0SA = 2;                 // Select the analog channel(2)
    ADTBL6bits.UCTMU = 1;
    
//    ADCON1 = 0x8000;                     // Turn On A/D Converter,
//    // Unsigned fractional format, Clear SAMP bit to
//    // start conversion, Sample when SAMP bit is set
//    ADCON2 = 0x0000;                     // VR+ = AVDD, V- = AVSS, Don't scan,
//    ADCON3 = 0x0000;                     // ADC uses system clock
//    ADCON3bits.ADCS = 0;                 // conversion clock = 1xTcy
}

unsigned   int     CtmuReturnSample(void){
    unsigned   int     result, x;
    
//    ADTBL6bits.UCTMU = 1;    
    
    //  Step 4 - 7 Enable the current source and start sampling
    CTMUCON1bits.CTMUEN = 1;             // Enable the CTMU
    CTMUCON2bits.EDG1STAT = 1;           // Enable current source
    CTMUCON1bits.IDISSEN = 1;            // Enable discharge
//    ADL0CONLbits.SAMP = 1;                 // Manual sampling start
    
    // step 8  1500us delay to discharge sample cap
    for (x = 0; x < 2000; x++);           // ~6 cycles * 2000 
    
    // step 9 Disable the discharge circuit
    CTMUCON1bits.IDISSEN = 0;            // Disable discharge (start charging)
    
    // step 10 allow the sample cap to partially charge
    for (x = 0; x < 250; x++);            // ~6 cycles * 250 ~ 670 cnts
    // step 11 Convert the analog sample
//    ADL0CONLbits.SAMP = 0;                 // Begin A/D conversion 
//    while(ADSTATHbits.ADBUSY == 1);         // Wait for A/D convert complete

    // Step 12 Disable the current source
    CTMUCON2bits.EDG1STAT = 0;           // Disable current source
//    IFS0bits.AD1IF = 0;                   // Clear ADC interrupt flag
    CTMUCON1bits.CTMUEN = 0;             // Disable the CTMU
    
    IFS0bits.AD1IF = 0;                //Clear flag of interrupt
    ADL0CONLbits.SAMP = 0;             //Stop conversion 
    while(IFS0bits.AD1IF == 0);        //Checking flag of interrupt (if it "1" -> start conversion)
    ADL0CONLbits.SAMP = 1;             //Begin conversion
    
    result = ADRES6;
    return (result);
}

int gain(void){
    
    unsigned   int     untouched, sample;
    CtmuCapTouchConfig(CTMU_MODE_EDGE, RANGE_0_550uA, 0);
    untouched = CtmuReturnSample();       // get reference value
    while(1){
        sample = CtmuReturnSample(); 
        // step 14-15 subtract the threshold and test
        if (sample < untouched - CTMU_TOUCH_THRESHHOLD_OFFSET){
            // button was pressed
        }    
        // user code
    }
}
