/*
 * File:   spi.c
 * Author: User
 *
 * Created on 26 декабря 2019 г., 15:57
 */


#include "xc.h"
#include "spi.h"

uint8_t dataSpi[1040];
uint8_t lastByte;
uint8_t prevByte;

void spiInit(){
    // initialize the device
    SPI1CON1 = 0x0000;
    // SPIFSD disabled; SPIBEN disabled; FRMPOL disabled; FRMDLY disabled; FRMEN disabled; 
    SPI1CON2 = 0x0000;
    // SISEL SPI_INT_SPIRBF; SPIROV disabled; SPIEN enabled; SRXMPT disabled; SPISIDL disabled; SPIBEC disabled; 
    SPI1STAT = 0x0000;
   
    
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
    SPI1CON1bits.SPRE = 0b111;
    
    SPI1CON2 = 0x00;
    
    SPI1STATbits.SPIEN = 0;
    SPI1STATbits.SPISIDL = 0;
    SPI1STATbits.SPIROV = 0;
    SPI1STATbits.SISEL = 0;      
    
    spiStart();
    
    IFS0bits.SPI1IF = 0;    
}


void spiStart(){
    SPI1STATbits.SPIEN = 1;
}


void spiTransmit(uint8_t *command, uint16_t size){
    
    uint16_t count;
    for(count = 0; count < size; count++ ){
        IFS0bits.SPI1IF = 0;
        SPI1BUF = command[count];
        while(IFS0bits.SPI1IF == 0);
        IFS0bits.SPI1IF = 0;
        dataSpi[count] = SPI1BUF;
    }      
    
    
}

void spiTransmitOne(uint8_t command){
    while( SPI1STATbits.SPITBF == 1 )
    {

    }

    SPI1BUF = command;

    while ( SPI1STATbits.SRXMPT == 1);
    
}

void clearData(){
    uint8_t count;
    for(count = 0; count < 50; count++){
        dataSpi[count] = 0;
    }
}
