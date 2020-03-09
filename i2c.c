/*
 * File:   i2c.c
 * Author: User
 *
 * Created on March 2, 2020, 11:32 AM
 */


#include "xc.h"
#include "i2c.h"

uint8_t AddrW = 0x78;

void i2cBeginTransaction(uint8_t deviceAdr){
    
    I2C2CONbits.I2CEN = 1;
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN != 0);
    I2C2TRN = AddrW;
}

void i2cEndTransaction(){
    
    while (I2C2STATbits.TRSTAT == 1);
    I2C2CONbits.PEN = 1;
    I2C2CONbits.I2CEN = 0;
}

void i2cWrite(uint8_t cmd){
    while (I2C2STATbits.TRSTAT == 1);
    I2C2TRN = cmd;
}

void i2cWriteTest(uint8_t cmd){
    I2C2CONbits.I2CEN = 1;
    I2C2CONbits.SEN = 1;
    while (I2C2CONbits.SEN != 0);
    I2C2TRN = AddrW;
    while (I2C2STATbits.TRSTAT == 1);
    I2C2TRN = cmd;
    while (I2C2STATbits.TRSTAT == 1);
    I2C2CONbits.PEN = 1;
    I2C2CONbits.I2CEN = 0;
}