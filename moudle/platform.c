#include "platform.h"



void oled_handle(uevt_t* evt) {
	static uint16_t t_10ms = 0;
	// 是否在刷新屏幕
	switch(evt->evt_id) {
		case UEVT_SYS_BOOT:
			i2c_init(i2c0, SSD1306_I2C_CLK * 1000);
			gpio_set_function(SSD1306_SDA_PIN, GPIO_FUNC_I2C);
			gpio_set_function(SSD1306_SCL_PIN, GPIO_FUNC_I2C);
			gpio_pull_up(SSD1306_SDA_PIN);
			gpio_pull_up(SSD1306_SCL_PIN);
			gpio_init(SSD1306_GED_PIN);
			gpio_set_dir(SSD1306_GED_PIN, GPIO_OUT);
			gpio_put(SSD1306_GED_PIN, 0);
			gpio_init(SSD1306_VCC_PIN);
			gpio_set_dir(SSD1306_VCC_PIN, GPIO_OUT);
			gpio_put(SSD1306_VCC_PIN, 1);
			SSD1306_init();

			oled_clean_buff();
			
			oled_update();
			uevt_bc_e(UEVT_APP_NEWSTATE);
			break;
		case UEVT_TIMER_10MS:
			t_10ms++;
			if(t_10ms % 20 == 0){
				oled_clean_buff();
				oled_draw(25, 0,&ad1_bmp);
				oled_draw(90, 0,&dino_front_leg_bmp);
				oled_update();
			}
			if(t_10ms % 20 == 10){
				oled_clean_buff();
				oled_draw(25, 0,&ad2_bmp);
				oled_draw(90, 0,&dino_back_leg_bmp);
				oled_update();
			}
			break;
		case UEVT_TIMER_100MS:

			break;
	}
}


void lcd_handle(uevt_t* evt) {
	static uint16_t t_10ms = 0;
	// 是否在刷新屏幕
	switch(evt->evt_id) {
		case UEVT_SYS_BOOT:
			tftInit();
			break;
		case UEVT_TIMER_10MS:
			// t_10ms++;
			// if(t_10ms % 100 == 0) {
			// 	for(int i = 0; i < 100; i++) {
			// 		for(int j = 0; j < 100; j++) {
			// 			tftplot(i, j, COLOR_RED);
			// 		}
			// 	}
			// }
			break;
		case UEVT_TIMER_100MS:
			t_10ms++;
			if(t_10ms % 100 == 0) {
				for(int i = 0; i < 100; i++) {
					for(int j = 0; j < 100; j++) {
						tftplot(i, j, COLOR_RED);
					}
				}
			}
			break;
	}
}


void timer_handle(uevt_t* evt) {
	// 是否在刷新屏幕
	static struct repeating_timer timer_10ms;
	static struct repeating_timer timer_100ms;
	switch(evt->evt_id) {
		case UEVT_SYS_BOOT:
			add_repeating_timer_ms(10, timer_10ms_callback, NULL, &timer_10ms);
			add_repeating_timer_ms(100, timer_100ms_callback, NULL, &timer_100ms);
			break;
		case UEVT_APP_NEWSTATE:

			// uevt_bc_e(UEVT_APP_NEWSTATE);
			break;
	}
}





void moudle_init(void) {
	user_event_handler_regist(oled_handle);
	// user_event_handler_regist(lcd_handle);
	user_event_handler_regist(timer_handle);

}

