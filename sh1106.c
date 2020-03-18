/*
 * File:   sh1106.c
 * Author: User
 *
 * Created on 10 марта 2020 г., 15:06
 */


#include "xc.h"
#include "i2c.h"
#include "sh1106.h"
#include "ssd_1306.h"
#include "work.h"

void sh1106_Command(uint8_t cmd){
    i2cBeginTransaction(0x78);
    i2cWrite(0x80); // or 0x80
    i2cWrite(cmd);
    i2cEndTransaction();
}

void sh1106_Init(){
    
    sh1106_Command(0xAE);
    //sh1106_Command(0xA6); //normal display
    
    sh1106_Command(0xD5); //set display clock div
    sh1106_Command(0xA0);
    
    sh1106_Command(0xA8); //set multiplex
    sh1106_Command(0x3F);
    
    sh1106_Command(0xD3); //set display offset
    sh1106_Command(0x00);
    
    sh1106_Command(0x00); //Lower column ardess
    sh1106_Command(0x10); //Higher column adress
    
    sh1106_Command(0x40); //set start line
    
//    sh1106_Command(0x8D); //charge pump
//    sh1106_Command(0x14);
//    sh1106_Command(0x20); //memory mode
//    sh1106_Command(0x00);
    sh1106_Command(0xA1); //seg remap
    sh1106_Command(0xC0);
    
    sh1106_Command(0xC8); //com scam dec
    
    sh1106_Command(0xDA); //set com pins
    sh1106_Command(0x12);
    
    sh1106_Command(0x81); //set contrast
    sh1106_Command(0x80);
    
    sh1106_Command(0xD9); //set precharge
    sh1106_Command(0x22);
    
    sh1106_Command(0xDB);
    sh1106_Command(0x35);
    
    sh1106_Command(0xA4);
    
    sh1106_Command(0xA6); //normal display
    
    sh1106_Command(0x2E); 
    
    sh1106_Command(0xAF); //display on
    
}

void sh1106_Data(uint8_t cmd){
    i2cBeginTransaction(0x78);
    i2cWrite(0x40);
    i2cWrite(cmd);
    i2cEndTransaction();
}

void sh1106_Clear(){
    uint16_t b;
    uint8_t pageAdress = 0xB0;
    for(pageAdress = 0xB0; pageAdress < 0xB8; pageAdress++){
        sh1106_Command(pageAdress);
        for (b = 0; b < 132; b++){ 
            sh1106_Data(0x00);
        }
    }
}

void sh1106_PrintLogo(uint8_t *logo){
    uint16_t b;
    uint16_t arrayCounter = 0;
    uint8_t pageAdress = 0xB0;
    for(pageAdress = 0xB0; pageAdress < 0xB8; pageAdress++){
        sh1106_Command(pageAdress);
        for (b = 0; b <= 131; b++){ 
            sh1106_Data(logo[arrayCounter]);
            if(b < 128)
            arrayCounter++;
        }
        
    }
}

void sh1106_PrintAll(){
    uint16_t b;
    uint16_t arrayCounter = 0;
    uint8_t pageAdress = 0xB0;
    for(pageAdress = 0xB0; pageAdress < 0xB2; pageAdress++){
        sh1106_Command(pageAdress);
        for (b = 0; b <= 131; b++){             
            if(b < 128){
                sh1106_Data(all[arrayCounter]);
                arrayCounter++;
            } else {
                sh1106_Data(0x00);
            }
        }
        
    }
}

void sh1106_SetCursor(uint8_t x, uint8_t y){
    sh1106_Command(0xB0 | y);
    uint8_t xLow = (x << 4) >> 4;
    uint8_t xHigh = x >> 4;
    sh1106_Command(0x00 | xLow); //Lower column ardess
    sh1106_Command(0x10 | xHigh); //Higher column adress
}

void sh1106_SetCursorX(uint8_t x){
    uint8_t xHigh = x >> 4;
    uint8_t xLow = x;
    xLow &= ~(1<<7);
    xLow &= ~(1<<6);
    xLow &= ~(1<<5);
    xLow &= ~(1<<4);
    
    sh1106_Command(0x00 | xLow); //Lower column ardess
    sh1106_Command(0x10 | xHigh); //Higher column adress
}

void sh1106_PrintDigit(uint16_t digit, uint8_t x, uint8_t y){
    //sh1106_SetCursor( x, y );
    uint16_t arrayCounter = 0;
    uint8_t pageAdress = 0xB0 | y;
    uint8_t pAI;
    uint16_t b;
    for (pAI = pageAdress; pAI < pageAdress + 4; pAI++){
        sh1106_Command(pAI);
        sh1106_SetCursorX(x);
        for (b = 0; b <= 19; b++){
            sh1106_Data(numbers[digit][arrayCounter]);
            arrayCounter++;
        }
    } 
}

void sh1106_PrintTest(uint16_t digit, uint8_t x, uint8_t y){
    uint16_t arrayCounter = 0;
    uint8_t pageAdress = 0xB0 | y;
    uint8_t pAI;
    uint16_t b;
     //printNumber(pageAdress);
    for (pAI = pageAdress; pAI <= pageAdress + 4; pAI++){
        sh1106_Command(pAI);
        sh1106_SetCursorX(x);
        for (b = 0; b <= 19; b++){
            sh1106_Data(numbers[digit][arrayCounter]);
            arrayCounter++;
        }
    } 
}
