#include "driver/gpio.h"

void dcdc_converter_enable(void)
{
    /* enable ENDC_DC */
    gpio_set_direction(GPIO_NUM_34, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_34, 1);
}