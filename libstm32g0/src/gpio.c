#include "stm32g0xx.h"
#include "gpio.h"

int add(int a, int b) {
	return a + b;
}

void gpio_open(gpio_config_t *config) {
    uint32_t tmp;
    volatile uint32_t tmpreg;
    /* Enable GPIOA clock */
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN;
    /* Ensure clock is enabled by read op */
    tmpreg = RCC->IOPENR & RCC_IOPENR_GPIOAEN;
    (void) tmpreg;

    /* Configure PA5 as output */
    GPIOA->MODER &= ~GPIO_MODER_MODE5;
    GPIOA->MODER |= GPIO_MODER_MODE5_0;
    GPIOA->OTYPER &= ~GPIO_OTYPER_OT5;
    GPIOA->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED5;
    GPIOA->OSPEEDR |= GPIO_OSPEEDR_OSPEED5_0;
    GPIOA->PUPDR &= ~GPIO_PUPDR_PUPD5;

    tmp = config->gpiox->MODER;
}
