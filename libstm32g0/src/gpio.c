#include "stm32g0xx.h"
#include "gpio.h"

int add(int a, int b) {
	return a + b;
}

void gpio_open(gpio_config_t *config) {
    /* Enable GPIOA clock */
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    /* FIXME: Add delay here after an RCC peripheral clock enabling
     * by reading (that's what the HAL does) */
    /* Configure PA5 as output */
}
