///*
// * File:   st7789.c
// * Author: User
// *
// * Created on March 13, 2020, 3:55 PM
// */
//
//
//#include "xc.h"
//#include "st7789.h"
//#include "mcc_generated_files/pin_manager.h"
//#include "spi.h"
//#include "work.h"
//#include "mcc_generated_files/i2c2.h"
//
//uint8_t
//  _width = 240,     ///< Display width as modified by current rotation
//  _height = 240,    ///< Display height as modified by current rotation
//  _xstart = 0,    ///< Internal framebuffer X offset
//  _ystart = 80,    ///< Internal framebuffer Y offset
//  _colstart = 0,  ///< Some displays need this changed to offset
//  _rowstart = 80,  ///< Some displays need this changed to offset
//  rotation;   ///< Display rotation (0 thru 3)
//
//const uint8_t
//  cmd_240x240[] =  {                // Init commands for 7789 screens
//    9,                              //  9 commands in list:
//    ST77XX_SWRESET,   ST_CMD_DELAY, //  1: Software reset, no args, w/delay
//      150,                          //    150 ms delay
//    ST77XX_SLPOUT ,   ST_CMD_DELAY, //  2: Out of sleep mode, no args, w/delay
//      255,                          //     255 = 500 ms delay
//    ST77XX_COLMOD , 1+ST_CMD_DELAY, //  3: Set color mode, 1 arg + delay:
//      0x55,                         //     16-bit color
//      10,                           //     10 ms delay
//    ST77XX_MADCTL , 1,              //  4: Mem access ctrl (directions), 1 arg:
//      0x08,                         //     Row/col addr, bottom-top refresh
//    ST77XX_CASET  , 4,              //  5: Column addr set, 4 args, no delay:
//      0x00,
//      ST7789_240x240_XSTART,        //     XSTART = 0
//      (240+ST7789_240x240_XSTART)>>8,
//      (240+ST7789_240x240_XSTART)&0xFF,  //     XEND = 240
//    ST77XX_RASET  , 4,              //  6: Row addr set, 4 args, no delay:
//      0x00,
//      ST7789_240x240_YSTART,             //     YSTART = 0
//      (240+ST7789_240x240_YSTART)>>8,
//      (240+ST7789_240x240_YSTART)&0xFF,  //     YEND = 240
//    ST77XX_INVON  ,   ST_CMD_DELAY,  //  7: hack
//      10,
//    ST77XX_NORON  ,   ST_CMD_DELAY, //  8: Normal display on, no args, w/delay
//      10,                           //     10 ms delay
//    ST77XX_DISPON ,   ST_CMD_DELAY, //  9: Main screen turn on, no args, delay
//    255 };                          //     255 = max (500 ms) delay
//
//
//
//void st7789_SPI_Write(uint8_t d) {
//    IO_SDA_SetLow();
//    Nop();
//  uint8_t bit_n;
////  for (bit_n = 0x80; bit_n; bit_n >>= 1) {
////    IO_SCL_SetHigh();
////    Nop();
////    if (d & bit_n){
////        IO_SDA_SetHigh();
////        Nop();
////    }
////    else {
////        IO_SDA_SetLow();
////        Nop();
////    }
////    IO_SCL_SetLow();
////    Nop();
////  }
//  uint8_t i;
//      for(i = 0; i < 8; i++)
//    {
//         wait1(100); PORTDbits.RD10 = 1;wait1(100);
////       IO_SCL_SetHigh();
//        if(((d>>(7-i))&1) == 1)
//        {
//           wait1(100); PORTDbits.RD9 = 1;wait1(100);
//            
////            Nop();IO_SCL_SetHigh();IO_SDA_SetHigh();Nop();
//        }
//        else
//        {
////            PORTDbits.RD10 = 1;
//            wait1(100);PORTDbits.RD9 = 0;wait1(100);
////            Nop();IO_SCL_SetHigh();IO_SDA_SetLow();Nop();
//        }
//        wait1(100);PORTDbits.RD10 = 0;wait1(100);
////        Nop();IO_SCL_SetLow();IO_SDA_SetLow();Nop();
//        //delay_us(1);
////        PIN_1(SCL);
//    }
//  
//  IO_SDA_SetLow();
//}
//
//void st7789_Init(){
////    st7789_Reset();
////    IO_LED_SetHigh();
////    st7789_BacklightON();
//    st7789_SPI_Write(0x11);
////    displayInit(cmd_240x240);
////    st7789_Command(ST77XX_MADCTL);
////    spiTransmitOne(ST77XX_MADCTL_RGB);
//    
//}
//
//void displayInit(const uint8_t *addr){
//  
//    st7789_Command(0x11);              
//wait1(1200); 
//
//    st7789_Command (0x36);			
//    st7789_Data(0x00);
//
//    st7789_Command(0x3A);			
//    st7789_Data(0x05);
//
//    st7789_Command(0xB2);			
//    st7789_Data(0x0C);
//    st7789_Data(0x0C); 
//    st7789_Data(0x00); 
//    st7789_Data(0x33); 
//    st7789_Data(0x33); 			
//
//    st7789_Command(0xB7);			
//    st7789_Data(0x00);
//
//    st7789_Command(0xBB);			
//    st7789_Data(0x36); //Vcom=1.45V
//
//    st7789_Command(0xC0);			
//    st7789_Data(0x2C);
//				
//    st7789_Command(0xC2);			
//    st7789_Data(0x01);
//
//    st7789_Command(0xC3);			
//    st7789_Data(0x13); //GVDD=4.8V  颜色深度
//			
//    st7789_Command(0xC4);			
//    st7789_Data(0x20); //VDV, 0x20:0v
//
//    st7789_Command(0xC6);			
//    st7789_Data(0x0F); //0x0F:60Hz        	
//
//    st7789_Command(0xD0);			
//    st7789_Data(0xA4);
//    st7789_Data(0xA1); 
//
//    st7789_Command(0xD6);			
//    st7789_Data(0xA1);
//
//    st7789_Command( 0xE0);     
//    st7789_Data( 0xF0);   
//    st7789_Data( 0x08);   
//    st7789_Data( 0x0E);   
//    st7789_Data( 0x09);   
//    st7789_Data( 0x08);   
//    st7789_Data( 0x04);   
//    st7789_Data( 0x2F);   
//    st7789_Data( 0x33);   
//    st7789_Data( 0x45);   
//    st7789_Data( 0x36);   
//    st7789_Data( 0x13);   
//    st7789_Data( 0x12);   
//    st7789_Data( 0x2A);   
//    st7789_Data( 0x2D);   
//
//    st7789_Command( 0xE1);     
//    st7789_Data( 0xF0);   
//    st7789_Data( 0x0E);   
//    st7789_Data( 0x12);   
//    st7789_Data( 0x0C);   
//    st7789_Data( 0x0A);   
//    st7789_Data( 0x15);   
//    st7789_Data( 0x2E);   
//    st7789_Data( 0x32);   
//    st7789_Data( 0x44);   
//    st7789_Data( 0x39);   
//    st7789_Data( 0x17);   
//    st7789_Data( 0x18);   
//    st7789_Data( 0x2B);   
//    st7789_Data( 0x2F);   
//
//    st7789_Command(0x21);
//
//    st7789_Command(0x29);
//    
////  st7789_Command(ST77XX_SWRESET); //  1: Software reset
////  wait(20000);
////  IO_DC_SetLow();
////  st7789_Command(ST77XX_SLPOUT); //  2: Out of sleep mode
////  wait(35000);
////  st7789_Command(ST77XX_COLMOD); //  3: Set color mode
////  st7789_Command(0x55);          //     16-bit color
////  wait(10000);
////  st7789_Command(ST77XX_MADCTL); //  4: Mem access ctrl (directions)
////  st7789_Command(0x08);          //     Row/col addr, bottom-top refresh
////  
////  st7789_Command(ST77XX_CASET);  //  5: Column addr set
////  st7789_Command(0x00);
////  st7789_Command(ST7789_240x240_XSTART); //     XSTART = 0
////  st7789_Command((240+ST7789_240x240_XSTART)>>8);
////  st7789_Command((240+ST7789_240x240_XSTART)&0xFF); //     XEND = 240
////  
////  st7789_Command(ST77XX_RASET);    //  6: Row addr set, 4 args
////  st7789_Command(0x00);
////  st7789_Command(ST7789_240x240_YSTART); //     YSTART = 0
////  st7789_Command((240+ST7789_240x240_YSTART)>>8);
////  st7789_Command((240+ST7789_240x240_YSTART)&0xFF); //     YEND = 240
////  
////  st7789_Command(ST77XX_INVON); //  7: hack
////  wait(10000);
////  
////  st7789_Command(ST77XX_NORON); //  8: Normal display on
////  wait(10000);
////  
////  st7789_Command(ST77XX_DISPON); //  9: Main screen turn on
////  wait(35000);
//  
//}
//
//void st7789_Data(uint8_t data){
//    IO_RS_SetHigh();
//    st7789_SPI_Write(data);
//}
//
//void st7789_Command(uint8_t cmd){
//    IO_RS_SetLow();
//    st7789_SPI_Write(cmd);
//    IO_RS_SetHigh();
//    
//}
//
//void st7789_start(){
//    IO_CS_SetLow();
//}
//
//void st7789_end(){
//    IO_CS_SetHigh();
//}
//
//void st7789_Clear(){
//}
//
//void st7789_BacklightON(){
//    IO_BLK_SetHigh();
//}
//
//void st7789_BacklightOFF(){
//    IO_BLK_SetLow();
//}
//
//void st7789_Reset(){
//    IO_Reset_SetHigh();
//    wait1(80000);
//    IO_Reset_SetLow();
//    wait1(40000);
//    IO_Reset_SetHigh();
//    wait1(40000);
//    IO_Reset_SetLow();
//    wait1(80000);
//    
//    IO_Reset_SetHigh();
//    wait1(40000);
//}
//
//void setAddrWindow(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
//  x += _xstart;
//  y += _ystart;
//
//  st7789_Command(ST77XX_CASET); // Column addr set
//  st7789_Data(0);
//  st7789_Data(x);
//  st7789_Data(0);
//  st7789_Data(x+w-1);
//
//  st7789_Command(ST77XX_RASET); // Row addr set
//  st7789_Data(0);
//  st7789_Data(y);
//  st7789_Data(0);
//  st7789_Data(y+h-1);
//
//  st7789_Command(ST77XX_RAMWR); // write to RAM
//}
//
//void st7789_DrawPixel(uint8_t x, uint8_t y, uint16_t color) {
//  if((x < _width) && (y < _height)) {
//    #ifdef TFT_CS
//      TFT_CS = 0;
//    #endif
//    setAddrWindow(x, y, 1, 1);
//    st7789_Data(color >> 8);
//    st7789_Data(color & 0xFF);
//    #ifdef TFT_CS
//      TFT_CS = 1;
//    #endif
//  }
//}
//
//void drawHLine(uint8_t x, uint8_t y, uint8_t w, uint16_t color) {
//  if( (x < _width) && (y < _height) && w) {   
//    uint8_t hi = color >> 8, lo = color;
//
//    if((x + w - 1) >= _width)  
//      w = _width  - x;
//    #ifdef TFT_CS
//      TFT_CS = 0;
//    #endif
//    setAddrWindow(x, y, w, 1);
//    while (w--) {
//    st7789_Data(hi);
//    st7789_Data(lo);
//    }
//    #ifdef TFT_CS
//      TFT_CS = 1;
//    #endif
//  }
//}
//
//void fillRect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t color) {
//  if( (x < _width) && (y < _height) && w && h) {                            // Nonzero width and height?
//    uint8_t hi = color >> 8, lo = color;
//    uint16_t px;
//    if((x + w - 1) >= _width)  
//      w = _width  - x;
//    if((y + h - 1) >= _height) 
//      h = _height - y;
//    #ifdef TFT_CS
//      TFT_CS = 0;
//    #endif
//    setAddrWindow(x, y, w, h);
//    px = (uint16_t)w * h;
//    while (px--) {
//      st7789_Command(hi);
//      st7789_Command(lo);
//    }
//    #ifdef TFT_CS
//      TFT_CS = 1;
//    #endif
//  }
//}
//
//void fillScreen(uint16_t color) {
//    fillRect(0, 0, _width, _height, color);
//}
