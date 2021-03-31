/*
 * File:   i2c.c
 * Author: User
 *
 * Created on March 2, 2020, 11:32 AM
 */


#include "xc.h"
#include "i2c.h"

//uint8_t AddrW = 0x78;
//
//void i2cBeginTransaction(uint8_t deviceAdr){
//    
//    I2C2CONbits.I2CEN = 1;
//    I2C2CONbits.SEN = 1;
//    while (I2C2CONbits.SEN != 0);
//    I2C2TRN = AddrW;
//}
//
//void i2cEndTransaction(){
//    
//    while (I2C2STATbits.TRSTAT == 1);
//    I2C2CONbits.PEN = 1;
//    I2C2CONbits.I2CEN = 0;
//}
//
//void i2cWrite(uint8_t cmd){
//    while (I2C2STATbits.TRSTAT == 1);
//    I2C2TRN = cmd;
//}
//
//void i2cWriteTest(uint8_t cmd){
//    I2C2CONbits.I2CEN = 1;
//    I2C2CONbits.SEN = 1;
//    while (I2C2CONbits.SEN != 0);
//    I2C2TRN = AddrW;
//    while (I2C2STATbits.TRSTAT == 1);
//    I2C2TRN = cmd;
//    while (I2C2STATbits.TRSTAT == 1);
//    I2C2CONbits.PEN = 1;
//    I2C2CONbits.I2CEN = 0;
//}

void i2cInitialize(void)
{
    
//    i2c2_object.pTrHead = i2c2_tr_queue;
//    i2c2_object.pTrTail = i2c2_tr_queue;
//    i2c2_object.trStatus.s.empty = true;
//    i2c2_object.trStatus.s.full = false;
//
//    i2c2_object.i2cErrors = 0;
    
    // initialize the hardware
    // Baud Rate Generator Value: I2CBRG 39;   
    I2C2BRG = 0x27;
    // ACKEN disabled; STREN disabled; GCEN disabled; SMEN disabled; DISSLW enabled; I2CSIDL disabled; ACKDT Sends ACK; SCLREL Holds; RSEN disabled; IPMIEN disabled; A10M 7 Bit; PEN disabled; RCEN disabled; SEN disabled; I2CEN enabled; 
    I2C2CON = 0x8000;
    // BCL disabled; P disabled; S disabled; I2COV disabled; IWCOL disabled; 
    I2C2STAT = 0x00;

    /* MI2C2 - I2C2 Master Events */
    // clear the master interrupt flag
    IFS3bits.MI2C2IF = 0;
    // enable the master interrupt
    IEC3bits.MI2C2IE = 1;

}