#ifndef GLOBAL_H
#define	GLOBAL_H

#include "p24FJ128GC010.h"


#define     uchar         unsigned char
#define     uint          unsigned int
#define     ulong         unsigned long

#define     IN         1
#define     OUT        0

#define     ON         1
#define     OFF        0

//===========================FREQUENCES=========================================

#define     CURRENT_FREQ_SOURCE     OSCCONbits.COSC

#define     DIV_FRC           CLKDIVbits.RCDIV
#define     DIV_CP            CLKDIVbits.CPDIV

#define     FREQ_32_KHZ       7
#define     FREQ_125_KHZ      6
#define     FREQ_250_KHZ      5
#define     FREQ_500_KHZ      4
#define     FREQ_1000_KHZ     3
#define     FREQ_2000_KHZ     2
#define     FREQ_4000_KHZ     1
#define     FREQ_8000_KHZ     0

//===========================ANSbits============================================

#define     ANSA_6      ANSAbits.ANSA6

#define     ANSB_0      ANSBbits.ANSB0
#define     ANSB_2      ANSBbits.ANSB2
#define     ANSB_3      ANSBbits.ANSB3
#define     ANSB_4      ANSBbits.ANSB4
#define     ANSB_13     ANSBbits.ANSB13
#define     ANSB_14     ANSBbits.ANSB14

#define     ANSC_1      ANSCbits.ANSC1
#define     ANSC_3      ANSCbits.ANSC3

#define     ANSD_2      ANSDbits.ANSD2
#define     ANSD_5      ANSDbits.ANSD5
#define     ANSD_11     ANSDbits.ANSD11

#define     ANSE_9      ANSEbits.ANSE9

#define     ANSF_4      ANSFbits.ANSELF4
#define     ANSF_13     ANSFbits.ANSELF13

#define     ANSG_9      ANSGbits.ANSELG9
#define     ANSG_15     ANSGbits.ANSELG15

//===========================PULL-DOWN==========================================

#define     RB2_PULL_DOWN   CNPD1bits.CN4PDE
#define     RB3_PULL_DOWN   CNPD1bits.CN5PDE
#define     RB4_PULL_DOWN   CNPD1bits.CN6PDE
#define     RB14_PULL_DOWN  CNPD3bits.CN32PDE

#define     RC2_PULL_DOWN   CNPD3bits.CN46PDE
#define     RC3_PULL_DOWN   CNPD3bits.CN47PDE

#define     RD2_PULL_DOWN   CNPD4bits.CN51PDE
#define     RD5_PULL_DOWN   CNPD1bits.CN14PDE
#define     RD11_PULL_DOWN  CNPD4bits.CN56PDE

#define     RE8_PULL_DOWN   CNPD5bits.CN66PDE
#define     RE9_PULL_DOWN   CNPD5bits.CN67PDE

//===========================PULL-UP============================================

#define     RD11_PULL_UP    CNPU4bits.CN56PUE

#define     RB2_PULL_UP     CNPU1bits.CN4PUE
#define     RB14_PULL_UP    CNPU3bits.CN32PUE

//===========================TRISbits===========================================


#define     TRISA_6    TRISAbits.TRISA6        //91 pin
#define     TRISB_0    TRISBbits.TRISB0        //25 pin
#define     TRISB_1    TRISBbits.TRISB1        //24 pin (input ню2 - OA2P1)
#define     TRISB_2    TRISBbits.TRISB2        //23 pin
#define     TRISB_3    TRISBbits.TRISB3        //22 pin
#define     TRISB_4    TRISBbits.TRISB4        //21 pin
#define     TRISB_5    TRISBbits.TRISB5        //20 pin (OA1OUT)
#define     TRISB_12   TRISBbits.TRISB12       //41 pin
#define     TRISB_13   TRISBbits.TRISB13       //42 pin (output DAC 2)
#define     TRISB_14   TRISBbits.TRISB14       //43 pin
#define     TRISC_1    TRISCbits.TRISC1        //6 pin
#define     TRISC_2    TRISCbits.TRISC2        //7 pin
#define     TRISC_3    TRISCbits.TRISC3        //8 pin
#define     TRISD_0    TRISDbits.TRISD0        //72 pin
#define     TRISD_1    TRISDbits.TRISD1        //76 pin (transistor base)
#define     TRISD_2    TRISDbits.TRISD2        //77 pin (input OA2 - OA2N1)
#define     TRISD_5    TRISDbits.TRISD5        //82 pin
#define     TRISD_6    TRISDbits.TRISD6        //83 pin (input OA1 - OA1P2)
#define     TRISD_11   TRISDbits.TRISD11       //71 pin
#define     TRISE_4    TRISEbits.TRISE4        //100 pin
#define     TRISE_8    TRISEbits.TRISE8        //18 pin
#define     TRISE_9    TRISEbits.TRISE9        //19 pin
#define     TRISF_4    TRISFbits.TRISF4        //49 pin
#define     TRISF_13   TRISFbits.TRISF13       //39 pin  
#define     TRISG_9    TRISGbits.TRISG9        //14 pin
#define     TRISG_13   TRISGbits.TRISG13       //97 pin
#define     TRISG_15   TRISGbits.TRISG15       //1 pin

//===========================PORTbits===========================================

#define     PORTA_6    PORTAbits.RA6           //91 pin
#define     PORTB_2    PORTBbits.RB2           //23 pin
#define     PORTB_3    PORTBbits.RB3           //22 pin
#define     PORTB_4    PORTBbits.RB4           //21 pin
#define     PORTB_5    PORTBbits.RB5           //20 pin
#define     PORTB_14   PORTBbits.RB14          //43 pin
#define     PORTC_2    PORTCbits.RC2           //7 pin
#define     PORTC_3    PORTCbits.RC3           //8 pin
#define     PORTD_1    PORTDbits.RD1           //76 pin (transistor base)
#define     PORTD_2    PORTDbits.RD2           //77 pin
#define     PORTD_5    PORTDbits.RD5           //82 pin
#define     PORTD_11    PORTDbits.RD11         //71 pin
#define     PORTE_4    PORTEbits.RE4           //100 pin
#define     PORTE_8    PORTEbits.RE8           //18 pin
#define     PORTE_9    PORTEbits.RE9           //19 pin
#define     PORTF_4    PORTFbits.RF4           //49 pin
#define     PORTG_13    PORTGbits.RG13         //97 pin
#define     PORTG_15   PORTGbits.RG15          //1 pin

#define     BASE_TR_TRIS    TRISDbits.TRISD1   //pin 76
#define     BASE_TR_PORT    PORTDbits.RD1      //pin 76

#define     DEV_MODES       4

#define     POLARITY                    0
#define     FAST_REVERSE_POLARITY       1
#define     PULSE_DURATION              2
#define     NUMBER_PULSES               3

//===========================ERRORS=============================================

#define     ERROR_UNKNOWN_TYPE_STRIP    0   
#define     ERROR_NOT_SLEAKING          11

void AllPinsToInput();


#endif	/* GLOBAL_H */

