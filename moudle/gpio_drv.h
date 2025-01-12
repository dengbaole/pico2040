#ifndef _GPIO_DRV_H
#define _GPIO_DRV_H

#include "platform.h"





//SPI
#define SPI_PORT  spi1
#define SPI_BAUDRATE 24000000
#define TFT_PIN_MISO 12
#define TFT_PIN_CS 13
#define TFT_PIN_RESET 11
#define TFT_PIN_DC 14
#define TFT_PIN_MOSI 15
#define TFT_PIN_SCK 10
#define TFT_PIN_BL 9

//屏幕尺寸
#define ILI9341_TFTWIDTH  240
#define ILI9341_TFTHEIGHT 320
#define ILI9341_SIZE  (ILI9341_TFTWIDTH*ILI9341_TFTHEIGHT)

//颜色
#define RGB565(r,g,b)  (((r&0xF8)<<8)|((g&0xFC)<<3)|((b&0xF8)>>3))
#define COLOR_BLACK 0x0000
#define COLOR_BLUE 0x001F
#define COLOR_RED 0xF800
#define COLOR_GREEN 0x07E0
#define COLOR_CYAN 0x07FF
#define COLOR_MAGENTA 0xF81F
#define COLOR_YELLOW 0xFFE0
#define COLOR_WHITE 0xFFFF




#endif // !1