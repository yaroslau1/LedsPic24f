#include "xc.h"
//#include "mcc_generated_files/system.h"
//#include "mcc_generated_files/mcc.h"
#include "flash.h"
#include "spi.h"

uint8_t cmdFlash[300] = {0};

void clearArrayData(){
    uint16_t i;
    for(i = 0; i < 300; i++){
        cmdFlash[i] = 0;
    }
}

void FLASH_resetPinSetup(){
    ANSDbits.ANSD1 = 0;
    TRISDbits.TRISD1 = 0;
    FLASH_resetPinOn();
}

void FLASH_resetPinOn(){
    PORTDbits.RD1 = 1;
}

void FLASH_resetPinOff(){
    PORTDbits.RD1 = 0;
}

void FLASH_wpPinSetup(){
    ANSDbits.ANSD13 = 0;
    TRISDbits.TRISD13 = 0;
    FLASH_wpPinOn();
}

void FLASH_wpPinOn(){
    PORTDbits.RD13 = 1;
}

void FLASH_wpPinOff(){
    PORTDbits.RD13 = 0;
}

void flashReadArray85MHz(uint32_t adress, uint16_t quantity){
    //clearArrayData();
    cmdFlash[0] = FLASH_READ_ARR_85MHz;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    cmdFlash[4] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, quantity+5, 1);    
}

void flashReadArray(uint32_t adress, uint16_t quantity){
    //clearArrayData();
    cmdFlash[0] = FLASH_READ_ARR;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    //cmdFlash[4] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, quantity+4, 1);    
}

void flashReadOne(uint32_t adress){
    cmdFlash[0] = FLASH_READ_ARR;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    cmdFlash[4] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 5, 1);
    //UART1_Write(lastByte);
}

void flashReadTwo(uint32_t adress){
    cmdFlash[0] = FLASH_READ_ARR;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    cmdFlash[4] = DONT_CARE_BYTE;
    cmdFlash[5] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 6, 0);
    //UART1_Write(lastByte);
}

void flashReadStatus(){
    cmdFlash[0] = FLASH_READ_STATUS;
    cmdFlash[1] = DONT_CARE_BYTE;
    cmdFlash[2] = DONT_CARE_BYTE;
    cmdFlash[3] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 3, 1);
}

void flashReadStatus2(){
    cmdFlash[0] = FLASH_READ_STATUS2;
    cmdFlash[1] = DONT_CARE_BYTE;
    cmdFlash[2] = DONT_CARE_BYTE;
    cmdFlash[3] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 2, 1);
}

void flashReadStatus3(){
    cmdFlash[0] = FLASH_READ_STATUS3;
    cmdFlash[1] = DONT_CARE_BYTE;
    cmdFlash[2] = DONT_CARE_BYTE;
    cmdFlash[3] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 2, 1);
}

void flashReadId(){
    cmdFlash[0] = FLSH_READ_ID;
    cmdFlash[1] = DONT_CARE_BYTE;
    cmdFlash[2] = DONT_CARE_BYTE;
    cmdFlash[3] = DONT_CARE_BYTE;
    spiTransmit(cmdFlash, 4, 1);
}

void flashWriteEnable(){
    cmdFlash[0] = FLASH_WRITE_EN;
    spiTransmit(cmdFlash, 1, 0);
}

void flashWriteByte(uint32_t adress, uint8_t byte){
    cmdFlash[0] = FLASH_WRITE_BYTE;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    cmdFlash[4] = byte;
    spiTransmit(cmdFlash, 5, 0);
}

void flashWriteTwoBytes(uint32_t adress, uint16_t byte){
    cmdFlash[0] = FLASH_WRITE_BYTE;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    cmdFlash[4] = byte >> 8;
    cmdFlash[5] = byte;
    spiTransmit(cmdFlash, 6, 0);
}

void flashWritePage(uint32_t adress, uint8_t *arr, uint8_t bytes){
    cmdFlash[0] = FLASH_WRITE_BYTE;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    uint16_t i = 0;
    for(i = 4; i < bytes+4; i++){
        cmdFlash[i] = arr[i-4];
    }
    spiTransmit(cmdFlash, bytes+4, 0);
}

void flashChipErase(){
    cmdFlash[0] = FLASH_CHIP_ERASE;
    spiTransmit(cmdFlash, 1, 0);
}

void flashEraseBlock(uint32_t adress){
    cmdFlash[0] = FLASH_BLOCK_ERASE;
    cmdFlash[1] = adress >> 16;
    cmdFlash[2] = adress >> 8;
    cmdFlash[3] = adress;
    spiTransmit(cmdFlash, 4, 0);
}


