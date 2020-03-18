/*
 * File:   work.c
 * Author: User
 *
 * Created on 27 ??????? 2020 ?., 10:59
 */


#include "xc.h"
#include "ssd_1306.h"
#include "sh1106.h"
#include "work.h"

void printNumber (uint16_t digit){
    if(digit < 10){
        
#ifdef SSD1306
        ssdPrintDigit(digit, 89, 2);        
        ssdPrintDigit(0, 66, 2);
        ssdPrintDigit(0, 43, 2);
        ssdPrintDigit(0, 20, 2);
#endif
        
#ifdef  SH1106
        sh1106_PrintDigit(digit, 89, 2);        
        sh1106_PrintDigit(0, 66, 2);
        sh1106_PrintDigit(0, 43, 2);
        sh1106_PrintDigit(0, 20, 2);
#endif
        
    } else if(digit >= 10 && digit < 100){
        
#ifdef SSD1306
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit / 10, 66, 2);
        ssdPrintDigit(0, 43, 2);
        ssdPrintDigit(0, 20, 2);
#endif
        
#ifdef  SH1106
        sh1106_PrintDigit(digit % 10, 89, 2);
        sh1106_PrintDigit(digit / 10, 66, 2);
        sh1106_PrintDigit(0, 43, 2);
        sh1106_PrintDigit(0, 20, 2);
#endif
        
    } else if(digit >= 100 && digit < 1000){
        
#ifdef SSD1306
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit % 100 / 10, 66, 2);
        ssdPrintDigit(digit / 100, 43, 2);
        ssdPrintDigit(0, 20, 2);
#endif
        
#ifdef SH1106
        sh1106_PrintDigit(digit % 10, 89, 2);
        sh1106_PrintDigit(digit % 100 / 10, 66, 2);
        sh1106_PrintDigit(digit / 100, 43, 2);
        sh1106_PrintDigit(0, 20, 2);
#endif
        
    } else if(digit >= 1000 && digit < 10000){
#ifdef SSD1306       
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit % 100 / 10, 66, 2);
        ssdPrintDigit(digit % 1000 / 100, 43, 2);
        ssdPrintDigit(digit / 1000, 20, 2);
#endif
        
#ifdef SH1106
        sh1106_PrintDigit(digit % 10, 89, 2);
        sh1106_PrintDigit(digit % 100 / 10, 66, 2);
        sh1106_PrintDigit(digit % 1000 / 100, 43, 2);
        sh1106_PrintDigit(digit / 1000, 20, 2);
#endif
        
    }
}

void wait(uint32_t time){
    uint32_t waitingTime;
    for(waitingTime = 0; waitingTime < time; waitingTime++){
        Nop();
    }
}
