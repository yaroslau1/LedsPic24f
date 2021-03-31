#include "global.h"
//#include "bufcon.h"
//#include "dac.h"
//#include "adc12.h"
#include "p24fj128gc010.h"
//#include "lcd.h"
//#include "operational_amp.h"
#include "delays_and_timers.h"

void AllPinsToInput() 
{
    ANSA = 0x0000, ANSB = 0x0000, ANSC = 0x0000, ANSD = 0x0000, ANSE = 0x0000, ANSF = 0x0000, ANSG = 0x0000;
    TRISA = 0xFFFF, TRISB = 0xFFFF, TRISC = 0xFFFF, TRISD = 0xFFFF, TRISE = 0xFFFF, TRISF = 0xFFFF, TRISG = 0xFFFF;
}
