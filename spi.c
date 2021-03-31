#include "xc.h"
#include "flash.h"
#include "spi.h"
#include "uart.h"
#include "delays_and_timers.h"

unsigned char dataSpi[TFT_BUFFER_FLASH];
uint8_t lastByte;
uint8_t prevByte;

void spiInit()
{    
    ANS_FLASH1_SDO = 0, PIN_FLASH1_SDO = 0;
    ANS_FLASH1_SDI = 0, PIN_FLASH1_SDI = 1;
    ANS_FLASH1_CLK = 0, PIN_FLASH1_CLK = 1;
    ANS_FLASH1_CS = 0, PIN_FLASH1_CS = 0;
    
    __builtin_write_OSCCONL(OSCCON & 0xbf);

    RPOR11bits.RP22R = 0x0007;      //RD3 -> pin 78 -> SPI1 -> SDO1
    RPINR20bits.SDI1R = 0x0019;     //RD4 -> pin 81 -> SPI1 -> SDI1
    RPOR10bits.RP20R = 0x0009;      //RD5 -> pin 82 -> SPI1 -> SSOUT1
    RPOR11bits.RP23R = 0x0008;      //RD2 -> pin 77 -> SPI1 -> SCK1OUT

    __builtin_write_OSCCONL(OSCCON | 0x40);
    
    // initialize the device
    SPI1CON1 = 0x0000;
    // SPIFSD disabled; SPIBEN disabled; FRMPOL disabled; FRMDLY disabled; FRMEN disabled; 
    SPI1CON2 = 0x0000;
    // SISEL SPI_INT_SPIRBF; SPIROV disabled; SPIEN enabled; SRXMPT disabled; SPISIDL disabled; SPIBEC disabled; 
    SPI1STAT = 0x0000;
    
    FLASH1_CS = 1;
    
    IFS0bits.SPI1IF = 0;
    IEC0bits.SPI1IE = 0; 
    
    SPI1CON1bits.DISSCK = 0;
    SPI1CON1bits.DISSDO = 0;
    SPI1CON1bits.MODE16 = 0;
    SPI1CON1bits.SMP = 0;
    SPI1CON1bits.CKE = 0; 
    SPI1CON1bits.SSEN = 0;
    SPI1CON1bits.CKP = 1;
    SPI1CON1bits.MSTEN = 1;
    SPI1CON1bits.PPRE = 0b11;
    SPI1CON1bits.SPRE = 0b110;
    
    SPI1CON2 = 0x00;
    
    SPI1STATbits.SPIEN = 0;
    SPI1STATbits.SPISIDL = 0;
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SISEL = 0;      
    
    spiStart();
    
    IFS0bits.SPI1IF = 0;   
}

void spiStart()
{
    SPI1STATbits.SPIEN = 1;
}

void spiTransmit(uint8_t *command, uint16_t size, uint8_t status)
{
    FLASH1_CS = 0;

    uint16_t count;
    for(count = 0; count < size; count++ ){
        IFS0bits.SPI1IF = 0;
        SPI1BUF = command[count];
        while(IFS0bits.SPI1IF == 0);
        IFS0bits.SPI1IF = 0;
        dataSpi[count] = SPI1BUF;
        if(status) {
            //UART_Write(0x43);
            //UART_Write(dataSpi[count]);
        }
        //lastByte = dataSpi[count];
        cmdFlash[count] = dataSpi[count];
//        if(count > 1) 
//        {
//            prevByte = dataSpi[count - 1];
//        }
    }  

    FLASH1_CS = 1;
}

void clearData()
{
    uint8_t count;
    for(count = 0; count < 50; count++){
        dataSpi[count] = 0;
    }
}
