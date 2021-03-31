#ifndef XC_FLASH_H
#define	XC_FLASH_H

#include <xc.h> // include processor files - each processor file is guarded.  

// ******* VARIABLES *****************//
#define FLASH_READ_ARR_85MHz        0x0B
#define FLASH_READ_ARR              0x03
#define FLASH_READ_STATUS           0x05
#define FLASH_READ_STATUS2          0x35
#define FLASH_READ_STATUS3          0x15
#define DONT_CARE_BYTE              0x00
#define FLSH_READ_ID                0x9F
#define FLASH_WRITE_EN              0x06
#define FLASH_WRITE_BYTE            0x02
#define FLASH_CHIP_ERASE            0x60
#define FLASH_BLOCK_ERASE           0xD8

extern uint8_t cmdFlash[300];

// ******* FUNCTIONS *****************//

void FLASH_resetPinSetup();
void FLASH_resetPinOn();
void FLASH_resetPinOff();
void FLASH_wpPinSetup();
void FLASH_wpPinOn();
void FLASH_wpPinOff();
void flashReadArray85MHz(uint32_t adress, uint16_t quantity);
void flashReadArray(uint32_t adress, uint16_t quantity);
void flashReadStatus();
void flashReadStatus2();
void flashReadStatus3();
void flashReadId();
void flashWriteEnable();
void flashWriteByte(uint32_t adress, uint8_t byte);
void flashWritePage(uint32_t adress,uint8_t *arr, uint8_t bytes);
void flashChipErase();
void flashReadOne(uint32_t adress);
void flashReadTwo(uint32_t adress);
void flashEraseBlock(uint32_t adress);
void flashWriteTwoBytes(uint32_t adress, uint16_t byte);

#endif	/* XC_HEADER_TEMPLATE_H */