#ifndef UART_H
#define	UART_H

#include "p24FJ128GC010.h"

#define    TRUE             1
#define    FALSE            0

#define     DEVICE_NUMBER    7
#define     COUNT_COMMAND_BYTES 6

#define     PC_COMMAND       0x43
#define     DEV_DATA         0x44

#define     DEV_NUM          0x49
#define     DEV_NUM1         0x44
#define     DEV_NUM2         0x00

#define     IS_READY_PC     0x69
#define     IS_READY_PC1     0x64
#define     IS_READY_PC2     0x72
#define     IS_READY_PC3     0x74

#define     IS_READY          0x72
#define     NOT_READY         0x6E

#define     IS_READY_DEV1     0x66
#define     IS_READY_DEV2     0x74
#define     IS_READY_DEV3     0x64



#define     DEV_TR_ALLOW     0x61
#define     DEV_TR_ALLOW1     0x64
#define     DEV_TR_ALLOW2     0x74
#define     DEV_TR_ALLOW3     0x74

#define     DEV_TR_RESULT       0x64
#define     DEV_TR_RESULT1      0x72
#define     DEV_TR_RESULT2      0x74
#define     DEV_TR_RESULT_GOOD  0x67
#define     DEV_TR_RESULT_BAD   0x62

#define     GO_IND_RESULT       0x67
#define     GO_IND_RESULT1      0x74
#define     GO_IND_RESULT2      0x69
#define     GO_IND_RESULT3      0x72

#define     ERROR               0x45
#define     ERROR_COMMAND       0x01
#define     ERROR_READY         0x02
#define     ERROR_ALLOW         0x03
#define     ERROR_RESULT         0x04
#define     ERROR_GOOD_BAD       0x05
#define     ERROR_TR_DATA       0x06

#define     ALLOW_DISPLAY_RESULT    0x6F
#define     ALLOW_DISPLAY_RESULT1    0x6B
#define     ALLOW_DISPLAY_RESULT2    0x6F
#define     ALLOW_DISPLAY_RESULT3    0x6B

#define     UART1_TX_TRIS    TRISFbits.TRISF13 
#define     UART1_TX_ANS     ANSFbits.ANSF13
#define     UART1_RX_TRIS    TRISEbits.TRISE8

#define     SYSCLK           8000000
#define     BAUDRATE1        9600
#define     BAUDRATEREG1     SYSCLK/8/BAUDRATE1-1

extern uint8_t status, IsConnectedDevice;

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void);
void UART1_SetRxInterruptHandler(void* handler);

void Pins_UART1();
void Initialize_UART1_RxMode(); 
void Write_UART1(uint8_t byte);
void Receive_UART1();

void DisableTX_UART1();
void EnableTX_UART1();


uint8_t CheckValidationCommand(uint8_t receiveData[]);
void CheckDeviceID(uint8_t receiveData[]);
void SendDeviceNumberToPC(uint8_t receiveData[]);
void CheckDeviceIsReadyToTransmit(uint8_t receiveData[]);
void SendReadyStatusToPC();
void GetCommandAllowTransmitData(uint8_t receiveData[]);
void GetTransmitResult(uint8_t receiveData[]);
void SendStatusIndicationResult();
void SendError(uint8_t error);
void LetDeviceDisplayResult(uint8_t receiveData[]);

void TransmitDataToPC(uint16_t polarity, uint16_t highWordID, uint16_t lowWordID, long int Z_first[], long int Z_second[], long int Z_third[],
        uint16_t glucoseValue, uint16_t hctValue, int currents[]);

#endif	/* UART_H */

