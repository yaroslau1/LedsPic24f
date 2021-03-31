#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h>

#include "p24FJ128GC010.h" // include processor files - each processor file is guarded.  

#define     ANS_FLASH1_RESET    ANSDbits.ANSD1        //RESET pin 76
#define     ANS_FLASH1_CLK      ANSDbits.ANSD2        //CLK pin 77
#define     ANS_FLASH1_SDO      ANSDbits.ANSD3        //SDO pin 78
#define     ANS_FLASH1_WP       ANSDbits.ANSD13       //WP pin 80
#define     ANS_FLASH1_SDI      ANSDbits.ANSD4        //SDI pin 81
#define     ANS_FLASH1_CS       ANSDbits.ANSD5        //CS pin 82

#define     PIN_FLASH1_RESET    TRISDbits.TRISD1      //RESET pin 76
#define     PIN_FLASH1_CLK      TRISDbits.TRISD2      //CLK pin 77
#define     PIN_FLASH1_SDO      TRISDbits.TRISD3      //SDO pin 78
#define     PIN_FLASH1_WP       TRISDbits.TRISD13     //WP pin 80
#define     PIN_FLASH1_SDI      TRISDbits.TRISD4      //SDI pin 81
#define     PIN_FLASH1_CS       TRISDbits.TRISD5      //CS pin 82

#define     FLASH1_RESET        PORTDbits.RD1         //RESET pin 76
#define     FLASH1_CLK          PORTDbits.RD2         //CLK pin 77
#define     FLASH1_SDO          PORTDbits.RD3         //SDO pin 78
#define     FLASH1_WP           PORTDbits.RD13        //WP pin 80
#define     FLASH1_SDI          PORTDbits.RD4         //SDI pin 81
#define     FLASH1_CS           PORTDbits.RD5         //CS pin 82

#define     TFT_BUFFER_FLASH    256

extern unsigned char dataSpi[TFT_BUFFER_FLASH];
extern uint8_t lastByte;
extern uint8_t prevByte;

void spiInit();
void spiStart();
void spiTransmit(uint8_t *command, uint16_t size, uint8_t status);

void clearData();

#endif	/* XC_HEADER_TEMPLATE_H */