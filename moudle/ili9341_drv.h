#ifndef _ILL9341_DRV_H
#define _ILI9341_DRV_H

#include <stddef.h>
#include <stdint.h>

//SPI
#define SPI_PORT  spi1
#define SPI_BAUDRATE 24000000
#define PIN_CS 9
#define PIN_RESET 8
#define PIN_DC 7
#define PIN_MOSI 6
#define PIN_SCK 5
#define PIN_BL 4

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

//屏幕状态
typedef struct {
	uint16_t width;
	uint16_t height;
} stftdevice;

extern stftdevice tftdevice;

//屏幕方向
typedef enum {
	ILI9341_DIRECTION_0,
	ILI9341_DIRECTION_90,
	ILI9341_DIRECTION_180,
	ILI9341_DIRECTION_270
} etftdirection;

void tft_init(void);
void tft_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void tft_set_direction(etftdirection direction);
void tft_clear(uint16_t color);
void tft_draw_point(uint16_t x, uint16_t y, uint16_t color);
void tft_draw_array(uint16_t* src, size_t len);

#endif // !1