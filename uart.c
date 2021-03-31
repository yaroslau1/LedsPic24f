#include "p24FJ128GC010.h"
#include "uart.h"

uint8_t status, IsConnectedDevice;

void (*UART1_RxDefaultInterruptHandler)(void);

void Pins_UART1() 
{
    __builtin_write_OSCCONL(OSCCON & 0xbf);

//    RPOR15bits.RP31R = 3; //transmit U1TX - pin 39
//    RPINR18bits.U1RXR = 33; //receive U1RX - pin 18
    
    RPOR5bits.RP10R = 3; //transmit U1TX - pin 49
    
    __builtin_write_OSCCONL(OSCCON | 0x40);

//    UART1_TX_ANS = 0;
//    
//    UART1_TX_TRIS = 1;
//    UART1_RX_TRIS = 1;
    
    //49 out
    ANSFbits.ANSF4 = 0;
    TRISFbits.TRISF4 = 1;
}

void Initialize_UART1_RxMode() 
{
    IEC0bits.U1TXIE = 0;
    IEC0bits.U1RXIE = 0;
    
    Pins_UART1();
    
    U1MODE = 0x0008;
    U1STA = 0x0000;
    
    U1BRG = BAUDRATEREG1;
    
    IEC0bits.U1RXIE = 1;

    U1MODEbits.UARTEN = 1; // enabling UART ON bit
    U1STAbits.UTXEN = 0;
}

void Write_UART1(uint8_t byte) 
{
    while (U1STAbits.UTXBF == 1);
    U1TXREG = byte;
    while (U1STAbits.TRMT == 0);
    Nop(); Nop(); Nop();
}

void DisableTX_UART1() 
{
    U1STAbits.UTXEN = 0;
    UART1_TX_TRIS = 1;
}

void EnableTX_UART1() 
{
    TRISFbits.TRISF4 = 0;
//    UART1_TX_TRIS = 0;
    U1STAbits.UTXEN = 1;
}

void UART1_SetRxInterruptHandler(void* handler) 
{
    UART1_RxDefaultInterruptHandler = handler;
}

void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void) 
{
    (*UART1_RxDefaultInterruptHandler)();
}

void Receive_UART1(void) 
{
    uint8_t receiveData[COUNT_COMMAND_BYTES];
    uint8_t i = 1;

    if (U1STAbits.URXDA > 0) {
        receiveData[0] = U1RXREG;
    }

    //Checking the first element of the array
    //Setting the number of array elements
    if(receiveData[0] == PC_COMMAND) 
    {
        //Command from PC
        while (i < COUNT_COMMAND_BYTES) 
        {
            if (U1STAbits.URXDA > 0) 
            {
                receiveData[i] = U1RXREG;
                i++;
            }
        }
        
        if(receiveData[1] == DEV_NUM) 
        {
            CheckDeviceID(receiveData);
        }
        
        if(IsConnectedDevice) 
        {
            switch (receiveData[1]) {
                case IS_READY_PC: CheckDeviceIsReadyToTransmit(receiveData);
                    break;
                case DEV_TR_ALLOW: GetCommandAllowTransmitData(receiveData);
                    break;
                case DEV_TR_RESULT: GetTransmitResult(receiveData);
                    break;
                case ALLOW_DISPLAY_RESULT: LetDeviceDisplayResult(receiveData);
                    break;
            }
        }
    }

    else {
        //Unknown command
    }

    IFS0bits.U1RXIF = 0;
}

uint8_t CheckValidationCommand(uint8_t receiveData[]) 
{
    uint8_t commandIsValid = FALSE;
    if (receiveData[0] == receiveData[5]) 
    {
        commandIsValid = TRUE;
    } 
    
    return commandIsValid;
}

void CheckDeviceID (uint8_t receiveData[])
{
    if(CheckValidationCommand(receiveData)) 
    {
        if ((receiveData[2] == DEV_NUM1)&&
            (receiveData[3] == DEV_NUM2)&&
            (receiveData[4] == DEVICE_NUMBER)) 
        {
            EnableTX_UART1();
            SendDeviceNumberToPC(receiveData);
            IsConnectedDevice = TRUE;
            status = 1;
        }
        else 
        {
            IsConnectedDevice = FALSE;
        //The ID of the requested device does not match the ID of this device 
        }
    }
    else 
    {
        //Command is wrong;
    }
}

void CheckDeviceIsReadyToTransmit(uint8_t receiveData[])
{
    if (CheckValidationCommand(receiveData)) 
    {
        if ((receiveData[2] == IS_READY_PC1)&&
            (receiveData[3] == IS_READY_PC2)&&
            (receiveData[4] == IS_READY_PC3)) 
        {
            SendReadyStatusToPC();
            status = 2;
        } 
        else 
        {
            SendError(ERROR_READY);
            //Ready status command error  
        }
    } else 
    {
        SendError(ERROR_COMMAND);
        //Command is wrong;
    }
}

void GetCommandAllowTransmitData(uint8_t receiveData[]) 
{
    if (CheckValidationCommand(receiveData)) 
    {
        if ((receiveData[2] == DEV_TR_ALLOW1)&&
                (receiveData[3] == DEV_TR_ALLOW2)&&
                (receiveData[4] == DEV_TR_ALLOW3)) 
        {
                status = 3;
        }
        else 
        {
            SendError(ERROR_ALLOW);
            //Ready status command error  
        }
    } 
    else 
    {
        SendError(ERROR_COMMAND);
        //Command is wrong;
    }
}

void SendDeviceNumberToPC(uint8_t receiveData[]) 
{
    uint8_t i;
    
    for(i = 0; i < COUNT_COMMAND_BYTES; i++) 
    {
        Write_UART1(receiveData[i]);
    }
}

void SendReadyStatusToPC() {
    uint8_t i;
    uint8_t isReadyDevice[COUNT_COMMAND_BYTES];
    
    isReadyDevice[0] = isReadyDevice[5] = PC_COMMAND;
    isReadyDevice[1] = IS_READY;
    isReadyDevice[2] = IS_READY_DEV1;
    isReadyDevice[3] = IS_READY_DEV2;
    isReadyDevice[4] = IS_READY_DEV3;
    
    for (i = 0; i < COUNT_COMMAND_BYTES; i++) {
        Write_UART1(isReadyDevice[i]);
    }
}

void GetTransmitResult(uint8_t receiveData[]) 
{
    if (CheckValidationCommand(receiveData)) 
    {
        if ((receiveData[2] == DEV_TR_RESULT1)&&
            (receiveData[3] == DEV_TR_RESULT2)) 
        {
             if(receiveData[4] == DEV_TR_RESULT_GOOD) 
             {
                 status = 4;
             }   
             else if(receiveData[4] == DEV_TR_RESULT_BAD) 
             {
                    status = 5;
             }
             else {
                 SendError(ERROR_GOOD_BAD);
             }
        }
        else {
            SendError(ERROR_RESULT);
        }
    } else {
        SendError(ERROR_COMMAND);
        //Command is wrong;
    }
}

void LetDeviceDisplayResult(uint8_t receiveData[]) {
    if (CheckValidationCommand(receiveData)) {
        if ((receiveData[2] == ALLOW_DISPLAY_RESULT1)&&
                (receiveData[3] == ALLOW_DISPLAY_RESULT2)&&
                (receiveData[4] == ALLOW_DISPLAY_RESULT3)) {
            
                IsConnectedDevice = 0;
                DisableTX_UART1();
                status = 0;

        } else {
            //error Allow display
        }
    } else {
        SendError(ERROR_COMMAND);
        //Command is wrong;
    }
}

void SendStatusIndicationResult() 
{
    uint8_t i;
    uint8_t statusIndResult[COUNT_COMMAND_BYTES];

    statusIndResult[0] = statusIndResult[5] = PC_COMMAND;
    statusIndResult[1] = GO_IND_RESULT;
    statusIndResult[2] = GO_IND_RESULT1;
    statusIndResult[3] = GO_IND_RESULT2;
    statusIndResult[4] = GO_IND_RESULT3;

    for (i = 0; i < COUNT_COMMAND_BYTES; i++) {
        Write_UART1(statusIndResult[i]);
    }
    
    status = 6;
}

void SendError(uint8_t error) 
{
    uint8_t i;
    uint8_t sendError[COUNT_COMMAND_BYTES];

    sendError[0] = sendError[5] = ERROR;
    sendError[1] = 0x6C;
    sendError[2] = 0x6C;
    sendError[3] = 0x00;
    sendError[4] = error;

    for (i = 0; i < COUNT_COMMAND_BYTES; i++) {
        Write_UART1(sendError[i]);
    }
}

void TransmitDataToPC(uint16_t polarity, uint16_t highWordID, uint16_t lowWordID, long int Z_first[], long int Z_second[], long int Z_third[],
        uint16_t glucoseValue, uint16_t hctValue, int currents[]) 
{
    long int combineBytes = 0;

    char count = 0;
    char m = 0;

    uint8_t sumAllBytes = 0;

    for (m = 0; m < 31; m++) 
    {
        switch (m) 
        {
            case 0:
            {
                Write_UART1(DEV_DATA);
                combineBytes = highWordID;
                break;
            }
            case 1: combineBytes = lowWordID;
                break;
            case 2: combineBytes = DEVICE_NUMBER;
                break;
            case 3: 
            {
                combineBytes = 50;
                if(!polarity) 
                {
                    combineBytes += 1;
                }
                else 
                {
                    combineBytes += 2;
                }
                break;
            }
            case 4: combineBytes = Z_first[0];
                break;
            case 5: combineBytes = Z_first[2];
                break;
            case 6: combineBytes = Z_first[4];
                break;
            case 7: combineBytes = Z_first[6];
                break;
            case 8: combineBytes = Z_second[0];
                break;
            case 9: combineBytes = Z_second[2];
                break;
            case 10: combineBytes = Z_second[4];
                break;
            case 11: combineBytes = Z_second[6];
                break;
            case 12: combineBytes = Z_third[0];
                break;
            case 13: combineBytes = Z_third[2];
                break;
            case 14: combineBytes = Z_third[4];
                break;
            case 15: combineBytes = Z_third[6];
                break;
            case 16: combineBytes = glucoseValue;
                break;
            case 17: combineBytes = hctValue;
                break;
            case 18: combineBytes = currents[1];
                break;
            case 19: combineBytes = currents[2];
                break;
            case 20: combineBytes = currents[3];
                break;
            case 21: combineBytes = currents[4];
                break;
            case 22: combineBytes = currents[5];
                break;
            case 23: combineBytes = currents[6];
                break;
            case 24: combineBytes = currents[7];
                break;
            case 25: combineBytes = currents[8];
                break;
            case 26: combineBytes = currents[9];
                break;
            case 27: combineBytes = currents[10];
                break;
            case 28: combineBytes = currents[11];
                break;
            case 29: combineBytes = currents[12];
                break;
            case 30: combineBytes = currents[13];
                break;
        }
        
        Write_UART1(combineBytes);
        Write_UART1(combineBytes >> 8);
        Write_UART1(combineBytes >> 16);
        sumAllBytes += (combineBytes + (combineBytes >> 8) + (combineBytes >> 16));
        count += 3;
    }

    Write_UART1((long int)count);
    Write_UART1((long int) count >> 8);
    Write_UART1((long int) count >> 16);
    Write_UART1((long int) sumAllBytes);
    Write_UART1((long int) sumAllBytes >> 8);
    Write_UART1((long int) sumAllBytes >> 16);

    Write_UART1(DEV_DATA);

//    LCD_AllSegmentsOff();
//    LCD_IndicationSymbols('*', '*', 't');
//    LCD_AllSegmentsOff();
}
