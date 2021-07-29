#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "quali_uart_test.h"
#include "test_status_report.h"

#define RX_BUF_SIZE (1024)
#define TX_BUF_SIZE (1024)

#define INTR_ALLOC_FLAGS (0)  // or ESP_INTR_FLAG_IRAM

/* Configure parameters of UARTs */
static const uart_config_t s_uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity    = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
};


quali_uart_test_handle_t *com1_test_start(test_status_report_handle_t *reporter)
{
    uart_port_t uart_num = 1;
    quali_uart_test_handle_t *hdl;

    ESP_ERROR_CHECK(uart_driver_install(uart_num, RX_BUF_SIZE, TX_BUF_SIZE, 0, NULL, INTR_ALLOC_FLAGS));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &s_uart_config));
                                        /* TX, RX, RTS, CTS */
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 11, 13, 10, 12));

    ESP_ERROR_CHECK(new_uart_test(&hdl, uart_num, reporter ));
    return hdl;
}

