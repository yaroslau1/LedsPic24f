#include "p24fj128gc010.h"
#include "delays_and_timers.h"
#include "global.h"

uint timer3_Pr;
uint timer2_Pr;
//char timerReady;

//void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) {
////        _T2IE = 0;
//    _T2IF = 0;
//    PORTEbits.RE4 = ~PORTEbits.RE4;
////        _T2IE = 1;
//}

void (*TMR2_InterruptHandler)(void);

void __attribute__((interrupt(auto_psv))) _T3Interrupt(void) 
{
//    _T3IE = 0;
    _T3IF = 0;
//    _T3IE = 1;
}

void TMR2_SetInterruptHandler(void* handler) 
{
//         _T2IE = 0;
    TMR2_InterruptHandler = handler;
//         _T2IE = 1;
}

void __attribute__((interrupt(auto_psv))) _T2Interrupt(void) 
{
//     _T2IE = 0;
//    _T2IF = 0;
    (*TMR2_InterruptHandler)();
    IFS0bits.T2IF = 0;
//     _T2IE = 1;
}

void TMR_Timer1_InitializationDefault() 
{
    //Timer1 On bit
    TIMER1_ENABLE = 0;
    
    //Timer1 Stop in Idle Mode bit
    T1CONbits.TSIDL = 0;
    
    //Timer1 Extended Clock Source Select bits (selected when TCS = 1)
    T1CONbits.T1ECS = 0b00;
    
    //Timer1 Gated Time Accumulation Enable bit
    T1CONbits.TGATE = 0;
    
    //Timer1 Input Clock Prescale Select bits
    T1CONbits.TCKPS = 0b11;
    
    //Timer1 External Clock Input Synchronization Select bit
    T1CONbits.TSYNC = 0;
    
    //Timer1 Clock Source Select bit
    T1CONbits.TCS = 0;
}

void TMR_Timer2_InitializationDefault() 
{
    //Timerx On bit
    TIMER2_ENABLE = 0;
    
    //Timerx Stop in Idle Mode bit
    T2CONbits.TSIDL = 0;
    
    //Timerx Extended Clock Source Select bits (selected when TCS = 1)
    T2CONbits.TIECS = 0b00;
    
    //Timerx Gated Time Accumulation Enable bit
    T2CONbits.TGATE = 0;
    
    //Timerx Input Clock Prescale Select bits
    T2CONbits.TCKPS = 0b11;
    
    //32-Bit Timer Mode Select bit
    T2CONbits.T32 = 0;
    
    //Timerx Clock Source Select bit
    T2CONbits.TCS = 0;
}

void TMR_Timer3_InitializationDefault() 
{
    //Timerx On bit
    TIMER3_ENABLE = 0;

    //Timerx Stop in Idle Mode bit
    T3CONbits.TSIDL = 0;

    //Timerx Extended Clock Source Select bits (selected when TCS = 1)
    T3CONbits.TIECS = 0b00;

    //Timerx Gated Time Accumulation Enable bit
    T3CONbits.TGATE = 0;

    //Timerx Input Clock Prescale Select bits
    T3CONbits.TCKPS = 0b11;

    //Timerx Clock Source Select bit
    T3CONbits.TCS = 0;
}

void TMR_Timer4_InitializationDefault() 
{
    //Timerx On bit
    TIMER4_ENABLE = 0;

    //Timerx Stop in Idle Mode bit
    T4CONbits.TSIDL = 0;

    //Timerx Extended Clock Source Select bits (selected when TCS = 1)
    T4CONbits.TIECS = 0b00;

    //Timerx Gated Time Accumulation Enable bit
    T4CONbits.TGATE = 0;

    //Timerx Input Clock Prescale Select bits
    T4CONbits.TCKPS = 0b11;

    //32-Bit Timer Mode Select bit
    T4CONbits.T32 = 0;

    //Timerx Clock Source Select bit
    T4CONbits.TCS = 1;
}

void TMR_Timer5_InitializationDefault() 
{
    //Timerx On bit
    TIMER5_ENABLE = 0;

    //Timerx Stop in Idle Mode bit
    T5CONbits.TSIDL = 0;

    //Timerx Extended Clock Source Select bits (selected when TCS = 1)
    T5CONbits.TIECS = 0b00;

    //Timerx Gated Time Accumulation Enable bit
    T5CONbits.TGATE = 0;

    //Timerx Input Clock Prescale Select bits
    T5CONbits.TCKPS = 0b11;

    //Timerx Clock Source Select bit
    T5CONbits.TCS = 0;
}

void DEL_delay(float time) 
{
    uint freqOscillator, timerPrescaler;
    uint numberCompleteTimerCycles = 0;
    uint remainingTimerTicks = 0;
    uint32_t functionExecutionTime = 0; //in timer ticks
    long int totalTimerTicks;
    
    //Check Current Frequence Source
    if(CURRENT_FREQ_SOURCE == FRCPLL_SOURCE) 
    {
        //In mode FRCPLL, only two divider values are available: 0 (8 MHz) and 1 (4 MHz). 
        if(DIV_FRC <= 1) 
        {
            freqOscillator = 32000 / (DIV_FRC + 1);
        }
        
        //Reading the current value of the system frequency divider 
        switch(DIV_CP) 
        {
            case 1: freqOscillator /= 2; break;
            case 2: freqOscillator /= 4; break;
            case 3: freqOscillator /= 8; break;
        }
        
        //Reading the current value of the timer prescaler
        //Note: Don't use a prescaler = 1! (It doesn't work)
        switch (TIMER1_DIVIDER) 
        {
            case 1: timerPrescaler = 8; functionExecutionTime = 86400; break;
            case 2: timerPrescaler = 64; functionExecutionTime = 10800; break;
            case 3: timerPrescaler = 256; functionExecutionTime = 0; break;
        }
    }
    
    else if(CURRENT_FREQ_SOURCE == FRCDIV_SOURCE)
    {
        //Reading the current value of the FRC frequency divider 
        switch (DIV_FRC) 
        {
            case 0: freqOscillator = 8000; break;        //CPU frequency in kHz
            case 1: freqOscillator = 4000; break;
            case 2: freqOscillator = 2000; break;
            case 3: freqOscillator = 1000; break;
            case 4: freqOscillator = 500; break;
            case 5: freqOscillator = 250; break;
            case 6: freqOscillator = 125; break;
            case 7: freqOscillator = 32; break;
        }
        
        //Reading the current value of the timer prescaler
        switch (TIMER1_DIVIDER) 
        {
            case 0: timerPrescaler = 1; functionExecutionTime = 1400; break;
            case 1: timerPrescaler = 8; functionExecutionTime = 175; break;
            case 2: timerPrescaler = 64; functionExecutionTime = 21; break;
            case 3: timerPrescaler = 256; functionExecutionTime = 5; break;
        }
    }
    
    //Calculating the number of timer ticks for the delay in "time" ms 
    totalTimerTicks = (time * (double) freqOscillator) / (2.0 * (double) timerPrescaler);
    totalTimerTicks = totalTimerTicks - (double) functionExecutionTime;
    
    if (CURRENT_FREQ_SOURCE == FRCPLL_SOURCE) 
    {
        //for FRCPLL no need to take Fosc/2 (need Fosc)
        totalTimerTicks *= 2;
    }

    //For delays over 65535 clock cycles, the number of complete timer cycles (countMaxDelay) is calculated, 
    //then the remaining number of timer clock cycles is entered into the counter. 
    if(totalTimerTicks > MAX_DELAY_COUNTER) 
    {
        numberCompleteTimerCycles = totalTimerTicks / MAX_DELAY_COUNTER;
        if(totalTimerTicks != numberCompleteTimerCycles * MAX_DELAY_COUNTER) 
        {
            remainingTimerTicks = totalTimerTicks - (numberCompleteTimerCycles * MAX_DELAY_COUNTER);
        }
        
        //cycle variable
        int i; 
        
        //number of complete timer cycles 
        for(i = 0; i < numberCompleteTimerCycles; i++) 
        {
            TMR1 = 0;
            while (TMR1 < MAX_DELAY_COUNTER);
        }
    }
    else {
        remainingTimerTicks = (uint) totalTimerTicks;
    }
    
    //Remaining value of timer counter 
    TMR1 = 0;
    while (TMR1 < remainingTimerTicks);
}

void HCT_DelayVoltageMeasurements(int delayCount) 
{
    int i;
    for(i = 0; i < delayCount; i++) 
    {
        Nop();
    }
}

void DEL_DelayBeforeMeasurements(uint fastPulseEnable) 
{
    if(fastPulseEnable) 
    {
        DEL_delay(DELAY_BEFORE_MEAS_WITH_FASTPULSE);
    } else 
    {
        DEL_delay(DELAY_BEFORE_MEAS_WITHOUT_FASTPULSE);
    }
}

void DEL_delay_100_uS ()
{
    TMR1 = 0; 
    while(TMR1 < d_100_us)
        {        }
}

void DEL_delay_500_uS() {
    TMR1 = 0;
    while (TMR1 < d_500_us) {
    }
}

void DEL_delay_for (uint64_t cycle) 
{
    uint64_t i;
    for(i = 0; i < cycle; i++) 
    {
        Nop();
    }
}

void TMR_SetTimer2_Voice() 
{
    _T2IF = 0;
    _T2IP = 1;
    _T2IE = 1;
    
    PR2 = 500;
    TMR2 = 0;
 
    TMR_Timer2_InitializationDefault();
    TIMER2_DIVIDER = 0;
//    TIMER2_ENABLE = 1;
}

void TMR_Timer2_Voice_Start(){
     /*Enable the interrupt*/
    IEC0bits.T2IE = 1;
    _T2IF = 1;
     /* Start the Timer */
    TIMER2_ENABLE = 1;
}

void TMR_Timer2_Voice_Stop() 
{
    _T2IE = 0;
    _T2IF = 0;
    TIMER2_ENABLE = 0;
}

void TMR_SetTimer2_30sec()
{
    PR2 = 29297;
    TMR2 = 0;
    _T2IF = 0;
    _T2IP = 7;
    _T2IE = 1;
    TMR_Timer2_InitializationDefault();
    TIMER2_ENABLE = 1;
}

void TMR_SetTimer4_5min()
{
    PR4 = 38400;
    TMR4 = 0;
    _T4IF = 0;
    _T4IP = 5;
    _T4IE = 1;
    TMR_Timer4_InitializationDefault();
    TIMER4_ENABLE = 1;
}

void TMR_SetTimer2_FlowDrop ()
{
    PR2 = 29300;//4883
    TMR2 = 0;
    _T2IF = 0;
    _T2IP = 7;
    _T2IE = 1;
    TMR_Timer2_InitializationDefault();
    TIMER2_ENABLE = 1;
}

void TMR_SetTimers3_And_5() 
{
    PR3 = 9765;
    TMR3 = 0;
    PR5 = 9765;
    TMR5 = 0;

    _T3IF = 0;
    _T3IP = 7;
    _T3IE = 1;
    _T5IF = 0;
    _T5IP = 5;
    _T5IE = 1;
    TMR_Timer3_InitializationDefault();
    TIMER3_ENABLE = 1;
    TMR_Timer5_InitializationDefault();
    TIMER5_ENABLE = 1;
}

void TMR_SetTimer3_5ms() 
{
    PR3 = 2500;
    TMR3 = 0;
    _T3IF = 0;
    _T3IP = 7;
    _T3IE = 1;

    TMR_Timer3_InitializationDefault();
    TIMER3_DIVIDER = 1;
    TIMER3_ENABLE = 1;
}

void TMR_SetTimer2_CheckStripExtract() 
{
    PR2 = 300;
    TMR2 = 0;
    _T2IF = 0;
    _T2IP = 7;
    _T2IE = 1;
    TMR_Timer2_InitializationDefault();
    TIMER2_ENABLE = 1;
}

void TMR_SetTimer5_WaitAfterIndicationResults() 
{
    PR5 = 10986; //3 min
    TMR5 = 0;
    _T5IF = 0;
    _T5IP = 5;
    _T5IE = 1;
    TMR_Timer5_InitializationDefault();
    TIMER5_ENABLE = 1;
}

void TMR_SetTimer_32bit(uint32_t time, uint16_t timerPrescaler) {
    
    uchar koef = 2;
    float Fosc = 8000;
    
    //PLL Mode - 32 Mhz; PLLDIV = NODIV
    if(CURRENT_FREQ_SOURCE == FRCPLL_SOURCE) 
    {
        Fosc = 16000;
        koef = 1;
        if (DIV_FRC == 1) {
            Fosc /= 2;
        }
    }
    
    //FRCDIV Mode - 8 Mhz
    else if(CURRENT_FREQ_SOURCE == FRCDIV_SOURCE) 
    {
        switch (DIV_FRC) 
        {
            case 0: Fosc = 8000; break;
            case 1: Fosc = 4000; break;
            case 2: Fosc = 2000; break;
            case 3: Fosc = 1000; break;
            case 4: Fosc = 500; break;
            case 5: Fosc = 250; break;
            case 6: Fosc = 125; break;
            case 7: Fosc = 31.25; break;
        }
    }

    //32-bit word for timer
    uint32_t prValue = (uint32_t) (time * Fosc / koef / timerPrescaler);
    
    timer3_Pr = (prValue >> 16); //High word of PR
    timer2_Pr = prValue; //Low Word of PR

//    //global variable indicating timer expiration status 
//    timerReady = 0;

    T2CON = 0x00;
    T3CON = 0x00;

    switch (timerPrescaler) {
        case 1: TIMER2_DIVIDER = 0; break;
        case 8: TIMER2_DIVIDER = 1; break;
        case 64: TIMER2_DIVIDER = 2; break;
        case 256: TIMER2_DIVIDER = 3; break;
    }

    TMR2 = 0x00;
    TMR3HLD = 0x00;

    PR2 = timer2_Pr;
    PR3 = timer3_Pr;

    _T3IP = 7;
    _T3IF = 0;
    _T3IE = 1;

    T2CONbits.T32 = 1;
    TIMER2_ENABLE = 1;
}