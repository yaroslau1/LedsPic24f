/*
 * File:   work.c
 * Author: User
 *
 * Created on 27 ??????? 2020 ?., 10:59
 */


#include "xc.h"
#include "ssd_1306.h"

void printNumber (uint16_t digit){
    if(digit < 10){
        ssdPrintDigit(digit, 89, 2);        
        ssdPrintDigit(0, 66, 2);
        ssdPrintDigit(0, 43, 2);
        ssdPrintDigit(0, 20, 2);
    } else if(digit >= 10 && digit < 100){
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit / 10, 66, 2);
        ssdPrintDigit(0, 43, 2);
        ssdPrintDigit(0, 20, 2);
    } else if(digit >= 100 && digit < 1000){
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit % 100 / 10, 66, 2);
        ssdPrintDigit(digit / 100, 43, 2);
        ssdPrintDigit(0, 20, 2);
    } else if(digit >= 1000 && digit < 10000){
        ssdPrintDigit(digit % 10, 89, 2);
        ssdPrintDigit(digit % 100 / 10, 66, 2);
        ssdPrintDigit(digit % 1000 / 100, 43, 2);
        ssdPrintDigit(digit / 1000, 20, 2);
    }
}
