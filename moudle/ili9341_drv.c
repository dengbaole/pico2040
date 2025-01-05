#include "ili9341_drv.h"



stftdevice tftdevice = {
	.width = ILI9341_TFTWIDTH,
	.height = ILI9341_TFTHEIGHT,
};


void tft_init(void) {
	spi_init(SPI_PORT, SPI_BAUDRATE);
}

void tft_set_window(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {

}

void tft_set_direction(etftdirection direction) {

}

void tft_clear(uint16_t color) {

}

void tft_draw_point(uint16_t x, uint16_t y, uint16_t color) {

}

void tft_draw_array(uint16_t* src, size_t len) {

}
