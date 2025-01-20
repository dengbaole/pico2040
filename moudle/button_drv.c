#include "button_drv.h"


void button1_callback(uint gpio, uint32_t events) {
	if (events & GPIO_IRQ_EDGE_FALL) {
		//按键1按下
		uevt_bc_e(BUTTON1_ON);
	}
}


void button2_callback(uint gpio, uint32_t events) {
	if (events & GPIO_IRQ_EDGE_FALL) {
		//按键1按下
		uevt_bc_e(BUTTON2_ON);
	}
}

void button_init(void) {
	gpio_init(KEY1_PIN);
	gpio_set_dir(KEY1_PIN, GPIO_IN);
	gpio_pull_up(KEY1_PIN);
	gpio_init(KEY1_GND_PIN);
	gpio_set_dir(KEY1_GND_PIN, GPIO_OUT);
	gpio_put(KEY1_GND_PIN, 0);

	// 设置中断
	gpio_set_irq_enabled_with_callback(KEY1_PIN, GPIO_IRQ_EDGE_FALL, true, &button1_callback);



	gpio_init(KEY2_PIN);
	gpio_set_dir(KEY2_PIN, GPIO_IN);
	gpio_pull_up(KEY2_PIN);
	gpio_init(KEY2_GND_PIN);
	gpio_set_dir(KEY2_GND_PIN, GPIO_OUT);
	gpio_put(KEY2_GND_PIN, 0);

	// 设置中断
	gpio_set_irq_enabled_with_callback(KEY2_PIN, GPIO_IRQ_EDGE_FALL, true, &button2_callback);
}
