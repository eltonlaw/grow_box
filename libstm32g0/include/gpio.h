#pragma once

#define GPIO_MODE_Pos 0u
#define GPIO_MODE     (0x3uL << GPIO_MODE_Pos)
#define MODE_INPUT    (0x0uL << GPIO_MODE_Pos)
#define MODE_OUTPUT   (0x1uL << GPIO_MODE_Pos)

int add(int a, int b);

typedef struct {
} gpio_config_t;
void gpio_open(gpio_config_t *config);
