/*
 * File:   i2c.c
 * Author: User
 *
 * Created on March 2, 2020, 11:32 AM
 */


#include "xc.h"
#include "i2c.h"

/*********************************************************************
 * Function:        StartI2C()
 *
 * Input:		None.
 *
 * Output:		None.
 *
 * Overview:		Generates an I2C Start Condition
 *
 * Note:    After a bus Idle state, a high-to-low transition of the SDA1 line while the clock (SCL1) is high,
            determines a Start condition. All data transfers must be preceded by a Start condition.
 ********************************************************************/

unsigned int StartI2C(void) {
    // <editor-fold defaultstate="collapsed" desc="Function generate start condition on I2C bus">
    /*
     * This function generates an I2C start condition and returns status of the Start.
     * To initiate a Start event, the software sets the Start Enable bit, SEN (I2CxCON<0>).
     * Prior to setting the Start bit, the software can check the P status bit (I2CxSTAT<4>) to ensure that the
     * bus is in an Idle state.
    */
    I2C2CONbits.SEN = 1;        //Generate Start Condition
    while (I2C2CONbits.SEN);    //Wait for Start Condition
    return (I2C2STATbits.S);    //Optionally return status
    //</editor-fold>
} 	

/*********************************************************************
 * Function:    RestartI2C()
 *
 * Input:	None.
 *
 * Output:	None.
 *
 * Overview:	Generates a restart condition and optionally returns status
 *
 * Note: After a wait state, a high-to-low transition of the SDAx line while the clock (SCLx) is high,
        determines a Repeated Start condition. Repeated Starts allow a master to change bus direction
        or addressed slave device without relinquishing control of the bus.
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Function generate I2C restart">

unsigned int RestartI2C(void) {
    //This function generates an I2C Restart condition and returns status
    //of the Restart.

    I2C2CONbits.RSEN = 1; //Generate Restart
    while (I2C2CONbits.RSEN); //Wait for the restart
    return (I2C2STATbits.S); //Optional - return status
}// </editor-fold>


/* Function:    StopI2C()
 *
 * Input:	None.
 *
 * Output:	None.
 *
 * Overview:	Generates a bus stop condition
 *
 * Note:    A low-to-high transition of the SDAx line while the clock (SCLx) is high determines a Stop
            condition. All data transfers must end with a Stop condition.
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Function generate stop condition on I2C bus">

unsigned int StopI2C(void) {
    //This function generates an I2C stop condition and returns status
    //of the Stop.

    I2C2CONbits.PEN = 1; //Generate Stop Condition
    while (I2C2CONbits.PEN); //Wait for Stop
    return (I2C2STATbits.P); //Optional - return status
}// </editor-fold> 

/*********************************************************************
* Function:        WriteI2C()
*
* Input:		Byte to write.
*
* Output:		None.
*
* Overview:		Writes a byte out to the bus
*
* Note:			None
********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Function WriteI2C">

unsigned int WriteI2C(unsigned char byte) {
    //This function transmits the byte passed to the function
    //while (I2C1STATbits.TRSTAT);	//Wait for bus to be idle
    I2C2TRN = byte; //Load byte to I2C1 Transmit buffer
    while (I2C2STATbits.TBF); //wait for data transmission
    return (I2C2STATbits.P); //Optional - return status
}// </editor-fold>

/*********************************************************************
* Function:        IdleI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Waits for bus to become Idle
*
* Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Wait for bus to turn idle">

void IdleI2C(void) {
    //Prior to setting the Start bit, the software can check the P status bit (I2CxSTAT<4>) to ensure that the
    //bus is in an Idle state.
    while (I2C2STATbits.TRSTAT); //Wait for bus Idle
}// </editor-fold>

/*********************************************************************
 * Function:        ACKStatus()
 *
 * Input:           None.
 *
 * Output:          Acknowledge Status.
 *
 * Overview:        Return the Acknowledge status on the bus
 *
 * Note:            ACKSTAT: Acknowledge Status bit (I2C Master/Slave mode transmit operation)
 *                  1 = NACK received from slave
 *                  0 = ACK! received from slave
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Return the Acknowledge status on the bus. Changed this function to return a non-inveted data bit. 0 = ACK! received from slave">

unsigned int ACKStatus(void) {
    return (I2C2STATbits.ACKSTAT); //Return Ack Status. If ACKStatus()returns zero ACK has been received.
}// </editor-fold>

/*********************************************************************
* Function:        NotAckI2C()
*
* Input:		None.
*
* Output:		None.
*
* Overview:		Generates a NO Acknowledge on the Bus
*
* Note:			None
********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Generates a NO Acknowledge on the Bus">

void NotAckI2C(void) {
    I2C2CONbits.ACKDT = 1; //Set for NotACk
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN); //wait for ACK to complete
    I2C2CONbits.ACKDT = 0; //Set for NotACk
}// </editor-fold>

/*********************************************************************
 * Function:     AckI2C()
 *
 * Input:	None.
 *
 * Output:	None.
 *
 * Overview:	Generates an Acknowledge.
 *
 * Note:	All data byte transmissions must be Acknowledged (ACK!) or Not Acknowledged (NACK) by the
        receiver. The receiver will pull the SDAx line low for an ACK or release the SDAx line for a NACK.
        The Acknowledge is a one-bit period using one SCLx clock.
 ********************************************************************/
//  <editor-fold defaultstate="collapsed" desc="Generates an Acknowledge">

void AckI2C(void) {
    I2C2CONbits.ACKDT = 0; //Set for ACk
    I2C2CONbits.ACKEN = 1;
    while (I2C2CONbits.ACKEN); //wait for ACK to complete
}//  </editor-fold>

/*********************************************************************
 * Function:        getI2C()
 *
 * Input:		None.
 *
 * Output:		contents of I2C1 receive buffer.
 *
 * Overview:		Read a single byte from Bus
 *
 * Note:			None
 ********************************************************************/
//  <editor-fold defaultstate="collapsed" desc="Read a single byte from Bus">

unsigned int getI2C(void) {
    I2C2CONbits.RCEN = 1; //Enable Master receive
    Nop();
    while (!I2C2STATbits.RBF); //Wait for receive bufer to be full
    return (I2C2RCV); //Return data in buffer
}//  </editor-fold>

/*********************************************************************
 * Function:       getsI2C()
 *
 * Input:		array pointer, Length.
 *
 * Output:		None.
 *
 * Overview:		read Length number of Bytes into array
 *
 * Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="read Length number of Bytes into array">

unsigned int getsI2C(unsigned char *rdptr, unsigned char Length) {
    while (Length--) {
        *rdptr++ = getI2C(); //get a single byte

        if (I2C2STATbits.BCL) //Test for Bus collision
        {
            return (-1);
        }

        if (Length) {
            AckI2C(); //Acknowledge until all read
        }
    }
    return (0);
}// </editor-fold>

/*********************************************************************
 * Function:             EEAckPolling()
 *
 * Input:		Control byte.
 *
 * Output:		error state.
 *
 * Overview:		polls the bus for an Acknowledge from device
 *
 * Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="polls the bus for an Acknowledge from device">

unsigned int EEAckPolling(unsigned char control) {
    IdleI2C(); //wait for bus Idle
    StartI2C(); //Generate Start condition

    if (I2C2STATbits.BCL) {
        return (-1); //Bus collision, return
    }
    else {
        if (WriteI2C(control)) {
            return (-3); //error return
        }

        IdleI2C(); //wait for bus idle
        if (I2C2STATbits.BCL) {
            return (-1); //error return
        }

        while (ACKStatus()) {
            RestartI2C(); //generate restart
            if (I2C2STATbits.BCL) {
                return (-1); //error return
            }

            if (WriteI2C(control)) {
                return (-3);
            }

            IdleI2C();
        }
    }
    StopI2C(); //send stop condition
    if (I2C2STATbits.BCL) {
        return (-1);
    }
    return (0);
}// </editor-fold>

void AckPolling (void){
/*24.5.2.3 RECEIVING ACKNOWLEDGE FROM THE SLAVE
On the falling edge of the eighth SCLx clock, the TBF bit is cleared and the master will deassert
the SDAx pin, allowing the slave to respond with an Acknowledge. The master will then generate
a ninth SCLx clock.
This allows the slave device being addressed to respond with an ACK bit during the ninth bit time,
if an address match occurs, or if data was received properly. A slave sends an Acknowledge
when it has recognized its device address (including a general call) or when the slave has
properly received its data.
The status of ACK is written into the Acknowledge Status bit, ACKSTAT (I2CxSTAT<15>), on the
falling edge of the ninth SCLx clock. After the ninth SCLx clock, the module generates the
MI2CxIF interrupt and enters an Idle state until the next data byte is loaded into I2CxTRN.
*/
}

// <editor-fold defaultstate="collapsed" desc="Write a byte to low density device at address LowAdd with control byte">

/*********************************************************************
 * Function:        LDByteWriteI2C()
 *
 * Input:		Control Byte, 8 - bit address, data.
 *
 * Output:		None.
 *
 * Overview:		Write a byte to low density device at address LowAdd with control byte
 *
 * Note:			None
 ********************************************************************/
unsigned int LDByteWriteI2C(unsigned char ControlByte, unsigned char LowAdd, unsigned char data) {
    unsigned int ErrorCode;

    IdleI2C(); //Ensure Module is Idle
    StartI2C(); //Generate Start COndition
    //WriteI2C(ControlByte); //Write Control byte
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(LowAdd); //Write Low Address
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(data); //Write Data
    IdleI2C();
    StopI2C(); //Initiate Stop Condition
    EEAckPolling(ControlByte); //Perform ACK polling
    return (ErrorCode);
}// </editor-fold>

/*********************************************************************
 * Function:        LDByteReadI2C()
 *
 * Input:		Control Byte, Address, *Data, Length.
 *
 * Output:		None.
 *
 * Overview:		Performs a low density read of Length bytes and stores in *Data array
 *				starting at Address.
 *
 * Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="Performs a low density read of Length bytes and stores in *Data array starting at the address">

unsigned int LDByteReadI2C(unsigned char ControlByte, unsigned char Address, unsigned char *Data, unsigned char Length) {
    IdleI2C(); //wait for bus Idle
    StartI2C(); //Generate Start Condition
    WriteI2C(ControlByte); //Write Control Byte
    IdleI2C(); //wait for bus Idle
    WriteI2C(Address); //Write start address
    IdleI2C(); //wait for bus Idle

    RestartI2C(); //Generate restart condition
    WriteI2C(ControlByte | 0x01); //Write control byte for read
    IdleI2C(); //wait for bus Idle

    getsI2C(Data, Length); //read Length number of bytes
    NotAckI2C(); //Send Not Ack
    StopI2C(); //Generate Stop
    return 0;
}// </editor-fold>

/*********************************************************************
 * Function:        HDByteWriteI2C()
 *
 * Input:		ControlByte, HighAddr, LowAddr, Data.
 *
 * Output:		None.
 *
 * Overview:		perform a high density byte write of data byte, Data.
 *				starting at the address formed from HighAdd and LowAdd
 *
 * Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="HDByteWriteI2C is the function called in the main while(1) loop in the example code">

unsigned int HDByteWriteI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char data) {
    unsigned int ErrorCode;

    IdleI2C(); //Ensure Module is Idle
    StartI2C(); //Generate Start COndition
    WriteI2C(ControlByte); //Write Control byte
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(HighAdd);
    IdleI2C(); //Write High Address
    WriteI2C(LowAdd); //Write Low Address
    IdleI2C();

    ErrorCode = ACKStatus(); //Return ACK Status

    WriteI2C(data); //Write Data
    IdleI2C();
    StopI2C(); //Initiate Stop Condition
    EEAckPolling(ControlByte); //perform Ack Polling
    return (ErrorCode);
}// </editor-fold>

/*********************************************************************
 * Function:        HDByteReadI2C()
 *
 * Input:		Control Byte, HighAdd, LowAdd, *Data, Length.
 *
 * Output:		None.
 *
 * Overview:		Performs a low density read of Length bytes and stores in *Data array
 *				starting at Address formed from HighAdd and LowAdd.
 *
 * Note:			None
 ********************************************************************/
// <editor-fold defaultstate="collapsed" desc="HDByteReadI2C()">

unsigned int HDByteReadI2C(unsigned char ControlByte, unsigned char HighAdd, unsigned char LowAdd, unsigned char *Data, unsigned char Length) {
    IdleI2C(); //Wait for bus Idle
    StartI2C(); //Generate Start condition
    WriteI2C(ControlByte); //send control byte for write
    IdleI2C(); //Wait for bus Idle

    WriteI2C(HighAdd); //Send High Address
    IdleI2C(); //Wait for bus Idle
    WriteI2C(LowAdd); //Send Low Address
    IdleI2C(); //Wait for bus Idle

    RestartI2C(); //Generate Restart
    WriteI2C(ControlByte | 0x01); //send control byte for Read
    IdleI2C(); //Wait for bus Idle

    getsI2C(Data, Length); //Read Length number of bytes to Data
    NotAckI2C(); //send Not Ack
    StopI2C(); //Send Stop Condition
    return (0);
}// </editor-fold>