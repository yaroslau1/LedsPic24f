#ifndef DELAYS_AND_TIMERS_H
#define	DELAYS_AND_TIMERS_H

#include    "global.h"
#include    "p24FJ128GC010.h"

#define     d_100_us     1    //T1CON   1:1
#define     d_500_us     110    //T1CON   1:1

#define     TIMER1_ENABLE   T1CONbits.TON
#define     TIMER2_ENABLE   T2CONbits.TON
#define     TIMER3_ENABLE   T3CONbits.TON
#define     TIMER4_ENABLE   T4CONbits.TON
#define     TIMER5_ENABLE   T5CONbits.TON

#define     TIMER5_TCS        T5CONbits.TCS

#define     TIMER1_DIVIDER    T1CONbits.TCKPS
#define     TIMER2_DIVIDER    T2CONbits.TCKPS
#define     TIMER3_DIVIDER    T3CONbits.TCKPS
#define     TIMER4_DIVIDER    T4CONbits.TCKPS

#define     FRC_SOURCE                0x00
#define     FRCPLL_SOURCE             0x01
#define     XT_HS_EC_SOURCE           0x02
#define     XTPLL_HSPLL_ECPLL_SOURCE  0x03
#define     SOSC_SOURCE               0x04
#define     LPRC_SOURCE               0x05
#define     FRCDIV_SOURCE             0x07

#define     DIV_256     3
#define     DIV_64      2
#define     DIV_8       1
#define     DIV_1       0

#define     DELAY_BEFORE_MEAS_WITH_FASTPULSE        1750
#define     DELAY_BEFORE_MEAS_WITHOUT_FASTPULSE     2750

#define     DELAY_FAST_REVERSE_POLARITY_PULSE1      100
#define     DELAY_FAST_REVERSE_POLARITY_PULSE2      100

#define     DELAY_AFTER_SETTING                      50
#define     DELAY_BETWEEN_MEASUREMENTS_GLUCOSE      183

#define     DELAY_HCT_MEASUREMENT_2                 4
#define     DELAY_HCT_MEASUREMENT_3                 29
#define     DELAY_HCT_MEASUREMENT_4                 37
#define     DELAY_HCT_MEASUREMENT_5                 81
#define     DELAY_HCT_MEASUREMENT_6                 250
#define     DELAY_HCT_MEASUREMENT_7                 750

#define     MAX_DELAY_COUNTER                       65535

extern uint timer3_Pr;
extern uint timer2_Pr;
extern char timerReady;

//---------------------------Delays (Timer 1)-----------------------------------
void DEL_delay(float time);
void DEL_delay_100_uS ();
void DEL_delay_500_uS();
void DEL_delay_for (uint64_t cycle);
void DEL_DelayBeforeMeasurements(uint fastPulseEnable);

void HCT_DelayVoltageMeasurements(int delayCount);

//---------------------------------Timers---------------------------------------

void TMR2_SetInterruptHandler(void* handler);
void __attribute__((interrupt, no_auto_psv)) _T2Interrupt(void);

void TMR_Timer1_InitializationDefault();
void TMR_Timer2_InitializationDefault();
void TMR_Timer3_InitializationDefault();
void TMR_Timer4_InitializationDefault();
void TMR_Timer5_InitializationDefault();

void TMR_SetTimer2_Voice();
void TMR_Timer2_Voice_Start();
void TMR_Timer2_Voice_Stop();

void TMR_SetTimer2_30sec ();
void TMR_SetTimer4_5min();
void TMR_SetTimer2_FlowDrop();

void TMR_SetTimer2_CheckStripExtract();
void TMR_SetTimer5_WaitAfterIndicationResults();
                       
void TMR_SetTimers3_And_5();

void TMR_SetTimer3_5ms();

void TMR_SetTimer_32bit(uint32_t time, uint16_t timerPrescaler);

#endif	/* DELAYS_AND_TIMERS_H */

