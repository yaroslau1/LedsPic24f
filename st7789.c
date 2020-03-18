/*
 * File:   st7789.c
 * Author: User
 *
 * Created on March 13, 2020, 3:55 PM
 */


#include "xc.h"
#include "st7789.h"
#include "mcc_generated_files/pin_manager.h"
#include "spi.h"
#include "work.h"
#include "mcc_generated_files/i2c2.h"
#include "mcc_generated_files/spi1.h"

uint8_t
  _width = 240,     ///< Display width as modified by current rotation
  _height = 240,    ///< Display height as modified by current rotation
  _xstart = 0,    ///< Internal framebuffer X offset
  _ystart = 80,    ///< Internal framebuffer Y offset
  _colstart = 0,  ///< Some displays need this changed to offset
  _rowstart = 80,  ///< Some displays need this changed to offset
  rotation;   ///< Display rotation (0 thru 3)

const uint8_t
  cmd_240x240[] =  {                // Init commands for 7789 screens
    9,                              //  9 commands in list:
    ST77XX_SWRESET,   ST_CMD_DELAY, //  1: Software reset, no args, w/delay
      150,                          //    150 ms delay
    ST77XX_SLPOUT ,   ST_CMD_DELAY, //  2: Out of sleep mode, no args, w/delay
      255,                          //     255 = 500 ms delay
    ST77XX_COLMOD , 1+ST_CMD_DELAY, //  3: Set color mode, 1 arg + delay:
      0x55,                         //     16-bit color
      10,                           //     10 ms delay
    ST77XX_MADCTL , 1,              //  4: Mem access ctrl (directions), 1 arg:
      0x08,                         //     Row/col addr, bottom-top refresh
    ST77XX_CASET  , 4,              //  5: Column addr set, 4 args, no delay:
      0x00,
      ST7789_240x240_XSTART,        //     XSTART = 0
      (240+ST7789_240x240_XSTART)>>8,
      (240+ST7789_240x240_XSTART)&0xFF,  //     XEND = 240
    ST77XX_RASET  , 4,              //  6: Row addr set, 4 args, no delay:
      0x00,
      ST7789_240x240_YSTART,             //     YSTART = 0
      (240+ST7789_240x240_YSTART)>>8,
      (240+ST7789_240x240_YSTART)&0xFF,  //     YEND = 240
    ST77XX_INVON  ,   ST_CMD_DELAY,  //  7: hack
      10,
    ST77XX_NORON  ,   ST_CMD_DELAY, //  8: Normal display on, no args, w/delay
      10,                           //     10 ms delay
    ST77XX_DISPON ,   ST_CMD_DELAY, //  9: Main screen turn on, no args, delay
    255 };                          //     255 = max (500 ms) delay



void st7789_Command(uint8_t cmd){
    IO_DC_SetLow();
    //spiTransmitOne(cmd);
    SPI1_Exchange8bit(cmd);
    IO_DC_SetHigh();
    
}

void st7789_Init(){
    st7789_Reset();
    IO_LED_SetHigh();
    st7789_BacklightON();
    displayInit(cmd_240x240);
    st7789_Command(ST77XX_MADCTL);
    spiTransmitOne(ST77XX_MADCTL_RGB);
    
}

void displayInit(const uint8_t *addr){
  
  #ifdef TFT_CS
    TFT_CS = 0;
  #endif
  
  st7789_Command(ST77XX_SWRESET); //  1: Software reset
  wait(20000);
  IO_DC_SetLow();
  st7789_Command(ST77XX_SLPOUT); //  2: Out of sleep mode
  wait(35000);
  st7789_Command(ST77XX_COLMOD); //  3: Set color mode
  st7789_Command(0x55);          //     16-bit color
  wait(10000);
  st7789_Command(ST77XX_MADCTL); //  4: Mem access ctrl (directions)
  st7789_Command(0x08);          //     Row/col addr, bottom-top refresh
  
  st7789_Command(ST77XX_CASET);  //  5: Column addr set
  st7789_Command(0x00);
  st7789_Command(ST7789_240x240_XSTART); //     XSTART = 0
  st7789_Command((240+ST7789_240x240_XSTART)>>8);
  st7789_Command((240+ST7789_240x240_XSTART)&0xFF); //     XEND = 240
  
  st7789_Command(ST77XX_RASET);    //  6: Row addr set, 4 args
  st7789_Command(0x00);
  st7789_Command(ST7789_240x240_YSTART); //     YSTART = 0
  st7789_Command((240+ST7789_240x240_YSTART)>>8);
  st7789_Command((240+ST7789_240x240_YSTART)&0xFF); //     YEND = 240
  
  st7789_Command(ST77XX_INVON); //  7: hack
  wait(10000);
  
  st7789_Command(ST77XX_NORON); //  8: Normal display on
  wait(10000);
  
  st7789_Command(ST77XX_DISPON); //  9: Main screen turn on
  wait(35000);
  
  #ifdef TFT_CS
    TFT_CS = 1;
  #endif
}

void st7789_Data(uint8_t data){
    IO_DC_SetHigh();
    SPI1_Exchange8bit(data);
}

void st7789_Clear(){
}

void st7789_BacklightON(){
    IO_BLK_SetHigh();
}

void st7789_BacklightOFF(){
    IO_BLK_SetLow();
}

void st7789_Reset(){
    IO_RES_SetHigh();
    wait(80000);
    IO_RES_SetLow();
    wait(40000);
    IO_RES_SetHigh();
    wait(40000);
    IO_RES_SetLow();
    wait(80000);
    
    IO_RES_SetHigh();
    wait(40000);
}

void setAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
  x += _xstart;
  y += _ystart;

  st7789_Command(ST77XX_CASET); // Column addr set
  st7789_Data(0);
  st7789_Data(x);
  st7789_Data(0);
  st7789_Data(x+w-1);

  st7789_Command(ST77XX_RASET); // Row addr set
  st7789_Data(0);
  st7789_Data(y);
  st7789_Data(0);
  st7789_Data(y+h-1);

  st7789_Command(ST77XX_RAMWR); // write to RAM
}

void st7789_DrawPixel(uint8_t x, uint8_t y, uint16_t color) {
  if((x < _width) && (y < _height)) {
    #ifdef TFT_CS
      TFT_CS = 0;
    #endif
    setAddrWindow(x, y, 1, 1);
    st7789_Data(color >> 8);
    st7789_Data(color & 0xFF);
    #ifdef TFT_CS
      TFT_CS = 1;
    #endif
  }
}

void drawHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color) {
  if( (x < _width) && (y < _height) && w) {   
    uint8_t hi = color >> 8, lo = color;

    if((x + w - 1) >= _width)  
      w = _width  - x;
    #ifdef TFT_CS
      TFT_CS = 0;
    #endif
    setAddrWindow(x, y, w, 1);
    while (w--) {
    st7789_Data(hi);
    st7789_Data(lo);
    }
    #ifdef TFT_CS
      TFT_CS = 1;
    #endif
  }
}

void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
  if( (x < _width) && (y < _height) && w && h) {                            // Nonzero width and height?
    uint8_t hi = color >> 8, lo = color;
    uint16_t px;
    if((x + w - 1) >= _width)  
      w = _width  - x;
    if((y + h - 1) >= _height) 
      h = _height - y;
    #ifdef TFT_CS
      TFT_CS = 0;
    #endif
    setAddrWindow(x, y, w, h);
    px = (uint16_t)w * h;
    while (px--) {
      st7789_Command(hi);
      st7789_Command(lo);
    }
    #ifdef TFT_CS
      TFT_CS = 1;
    #endif
  }
}

void fillScreen(uint16_t color) {
    fillRect(0, 0, _width, _height, color);
}
