#include "p24fj128gc010.h"
#include "dac.h"
#include "global.h"
//#include "bufcon.h"

void DAC1_Init()
{
    TRISG_9 = IN, ANSG_9 = 1;
    
//    Bufcon0_Init();
        
    //DACEN: DAC Enable bit
    DAC1CONbits.DACEN = 0;
    
    //DAC Peripheral Stop in Idle mode
    DAC1CONbits.DACSIDL = 1;  
    
    //DAC Enable Peripheral During Sleep bit
    DAC1CONbits.DACSLP = 0;
    
    //DAC Data Format Select bit
    DAC1CONbits.DACFM = 0;
    
    //DAC Trigger Input Enable bit
    DAC1CONbits.DACTRIG = 0;
    
    //DAC Trigger Source Select bits
    DAC1CONbits.DACTSEL = 0b11111;
    
    //DAC Reference Source Select bits
    DAC1CONbits.DACREF = 0b10;
    
    //Enable module DAC 1
    DAC1CONbits.DACEN = 1;
}

void DAC2_Init()
{
    TRISB_13 = IN, ANSB_13 = 1;
    
//    Bufcon0_Init();
        
    //DACEN: DAC Enable bit
    DAC2CONbits.DACEN = 0;
    
    //DAC Peripheral Stop in Idle mode
    DAC2CONbits.DACSIDL = 1;  
    
    //DAC Enable Peripheral During Sleep bit
    DAC2CONbits.DACSLP = 0;
    
    //DAC Data Format Select bit
    DAC2CONbits.DACFM = 0;
    
    //DAC Trigger Input Enable bit
    DAC2CONbits.DACTRIG = 0;
    
    //DAC Trigger Source Select bits
    DAC2CONbits.DACTSEL = 0b11111;
    
    //DAC Reference Source Select bits
    DAC2CONbits.DACREF = 0b10;
    
    //Enable module DAC 1
    DAC2CONbits.DACEN = 1;
}

void DAC1_Disable () 
{
   DAC1DAT = 0;
   DAC1CONbits.DACEN = 0;
}

void DAC2_Disable () 
{
   DAC2DAT = 0;
   DAC2CONbits.DACEN = 0;
}

void DAC1_SetDiscretes(uint16_t discretes) 
{
    DAC1DAT = discretes;
}

void DAC2_SetDiscretes(uint16_t discretes) 
{
    DAC2DAT = discretes;
}