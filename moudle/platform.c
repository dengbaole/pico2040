#include "platform.h"



void oled_handle(uevt_t* evt) {
	// 是否在刷新屏幕
	switch(evt->evt_id) {
		case UEVT_SYS_BOOT:
			i2c_init(i2c0, SSD1306_I2C_CLK * 1000);
			gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
			gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
			gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
			gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
			SSD1306_init();
			uevt_bc_e(UEVT_APP_NEWSTATE);
			break;
		case UEVT_APP_NEWSTATE:

			// run through the complete initialization process


			// Initialize render area for entire frame (SSD1306_WIDTH pixels by SSD1306_NUM_PAGES pages)
			frame_area_init();
			calc_render_area_buflen(&frame_area);
			// zero the entire display

			memset(oled_displaybuff, 0, SSD1306_BUF_LEN);

			render(oled_displaybuff, &frame_area);
			SSD1306_send_cmd(SSD1306_SET_ENTIRE_ON);
			// oled_draw(0,0,IMG_WIDTH,IMG_HEIGHT,raspberry26x32);
			// render(oled_displaybuff, &frame_area);
			// // intro sequence: flash the screen 3 times
			// for (int i = 0; i < 3; i++) {
			// 	SSD1306_send_cmd(SSD1306_SET_ALL_ON);    // Set all pixels on
			// 	sleep_ms(100);
			// 	SSD1306_send_cmd(SSD1306_SET_ENTIRE_ON); // go back to following RAM for pixel state
			// 	sleep_ms(100);
			// }

			// render 3 cute little raspberries
			oled_Buffer_clear();
            oled_draw(0,0,IMG_WIDTH,IMG_HEIGHT,raspberry26x32);
            update_display();
			// uint8_t buff[1] = {oled_displaybuff2[0][1]};
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			// SSD1306_send_buf(buff, 1);
			while (1) {
				/* code */
			}

			render_area area = {
				.start_page = 0,
				.end_page = (IMG_HEIGHT / SSD1306_PAGE_HEIGHT)  - 1
			};



			area.start_col = 0;
			area.end_col = IMG_WIDTH - 1;

			calc_render_area_buflen(&area);
			uint8_t offset =  IMG_WIDTH + 5; // 5px padding
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
				WriteString(oled_displaybuff, 5, y, text[i]);
				y += 8;
			}
			render(oled_displaybuff, &frame_area);
			SSD1306_scroll(false);
			// Test the display invert function
			sleep_ms(3000);
			SSD1306_send_cmd(SSD1306_SET_INV_DISP);
			sleep_ms(3000);
			SSD1306_send_cmd(SSD1306_SET_NORM_DISP);

			bool pix = true;
			for (int i = 0; i < 2; i++) {
				for (int x = 0; x < SSD1306_WIDTH; x++) {
					DrawLine(oled_displaybuff, x, 0,  SSD1306_WIDTH - 1 - x, SSD1306_HEIGHT - 1, pix);
					render(oled_displaybuff, &frame_area);
				}

				for (int y = SSD1306_HEIGHT - 1; y >= 0 ; y--) {
					DrawLine(oled_displaybuff, 0, y, SSD1306_WIDTH - 1, SSD1306_HEIGHT - 1 - y, pix);
					render(oled_displaybuff, &frame_area);
				}
				pix = false;
			}

			uevt_bc_e(UEVT_APP_NEWSTATE);
			break;
	}
}





void moudle_init(void) {
	user_event_handler_regist(oled_handle);

}

