#include "platform.h"

int main(void) {
	stdio_init_all();

	i2c_init(i2c0, SSD1306_I2C_CLK * 1000);
	gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
	gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
	gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
	gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

	// run through the complete initialization process
	SSD1306_init();

	// Initialize render area for entire frame (SSD1306_WIDTH pixels by SSD1306_NUM_PAGES pages)
	render_area frame_area = {
		.start_col = 0,
		.end_col = SSD1306_WIDTH - 1,
		.start_page = 0,
		.end_page = SSD1306_NUM_PAGES - 1
	};

	calc_render_area_buflen(&frame_area);

	// zero the entire display
	uint8_t buf[SSD1306_BUF_LEN];
	memset(buf, 0, SSD1306_BUF_LEN);
	render(buf, &frame_area);

	// intro sequence: flash the screen 3 times
	for (int i = 0; i < 3; i++) {
		SSD1306_send_cmd(SSD1306_SET_ALL_ON);    // Set all pixels on
		sleep_ms(100);
		SSD1306_send_cmd(SSD1306_SET_ENTIRE_ON); // go back to following RAM for pixel state
		sleep_ms(100);
	}

	// render 3 cute little raspberries
	render_area area = {
		.start_page = 0,
		.end_page = (IMG_HEIGHT / SSD1306_PAGE_HEIGHT)  - 1
	};


restart:

	area.start_col = 0;
	area.end_col = IMG_WIDTH - 1;

	calc_render_area_buflen(&area);

	uint8_t offset = 5 + IMG_WIDTH; // 5px padding

	for (int i = 0; i < 4; i++) {
		render(raspberry26x32, &area);
		area.start_col += offset;
		area.end_col += offset;
	}

	SSD1306_scroll(true);
	sleep_ms(5000);
	// SSD1306_scroll(false);

	char* text[] = {
		"ssd1306 test",
		"2025_01_05"
	};

	int y = 0;
	for (int i = 0 ; i < count_of(text); i++) {
		WriteString(buf, 5, y, text[i]);
		y += 8;
	}
	render(buf, &frame_area);
	SSD1306_scroll(false);
	// Test the display invert function
	sleep_ms(3000);
	SSD1306_send_cmd(SSD1306_SET_INV_DISP);
	sleep_ms(3000);
	SSD1306_send_cmd(SSD1306_SET_NORM_DISP);

	bool pix = true;
	for (int i = 0; i < 2; i++) {
		for (int x = 0; x < SSD1306_WIDTH; x++) {
			DrawLine(buf, x, 0,  SSD1306_WIDTH - 1 - x, SSD1306_HEIGHT - 1, pix);
			render(buf, &frame_area);
		}

		for (int y = SSD1306_HEIGHT - 1; y >= 0 ; y--) {
			DrawLine(buf, 0, y, SSD1306_WIDTH - 1, SSD1306_HEIGHT - 1 - y, pix);
			render(buf, &frame_area);
		}
		pix = false;
	}

	goto restart;

	return 0;
}
