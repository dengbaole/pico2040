#ifndef _ILL9341_DRV_H
#define _ILL9341_DRV_H

#include "platform.h"


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