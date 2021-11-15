#include <stdio.h>
#include <string.h>

#include "driver/gpio.h"
#include "driver/uart.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "quali_uart_test.h"
#include "sdkconfig.h"
#include "test_status_report.h"

#define RX_BUF_SIZE (1024)
#define TX_BUF_SIZE (1024)

#define INTR_ALLOC_FLAGS (0)  // or ESP_INTR_FLAG_IRAM

/* Configure parameters of UARTs */
static const uart_config_t s_uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .source_clk = UART_SCLK_APB,
};

void com1_test_start(void)
{
    uart_port_t uart_num = 0;  // requires CONFIG_ESP_CONSOLE_NONE=y
    quali_uart_test_handle_t *hdl;
    test_status_report_handle_t *sr_handle;

    ESP_ERROR_CHECK(new_test_status_report_instance(&sr_handle, 10000));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, RX_BUF_SIZE, TX_BUF_SIZE, 0, NULL, INTR_ALLOC_FLAGS));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &s_uart_config));
    /* TX, RX, RTS, CTS */
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 11, 13, 10, 12));

    ESP_ERROR_CHECK(new_uart_test(&hdl, uart_num, sr_handle));
}

void com2_test_start(void)
{
    uart_port_t uart_num = 1;
    quali_uart_test_handle_t *hdl;
    test_status_report_handle_t *sr_handle;

    ESP_ERROR_CHECK(new_test_status_report_instance(&sr_handle, 10001));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, RX_BUF_SIZE, TX_BUF_SIZE, 0, NULL, INTR_ALLOC_FLAGS));
    ESP_ERROR_CHECK(uart_param_config(uart_num, &s_uart_config));
    /* TX, RX, RTS, CTS */
    ESP_ERROR_CHECK(uart_set_pin(uart_num, 15, 17, 14, 16));

    ESP_ERROR_CHECK(new_uart_test(&hdl, uart_num, sr_handle));
}
