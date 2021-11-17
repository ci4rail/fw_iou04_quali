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
    quali_uart_test_handle_t *hdl;
    test_status_report_handle_t *sr_handle;

    test_status_report_config_t config = {.instance = "iou04-usb-ext-com", .instance_idx = 1, .port = 10000};

    ESP_ERROR_CHECK(new_test_status_report_instance(&sr_handle, &config));

    quali_uart_test_config_t test_config = {
        .uart_num = UART_NUM_0, // requires CONFIG_ESP_CONSOLE_NONE=y
        .uart_config = &s_uart_config,
        .rx_buf_size = RX_BUF_SIZE,
        .tx_buf_size = TX_BUF_SIZE,
        .gpio_tx = 11,
        .gpio_rx = 13,
        .gpio_rts = 10,
        .gpio_cts = 12,
        .reporter = sr_handle
    };

    ESP_ERROR_CHECK(new_uart_test(&hdl, &test_config));
}

void com2_test_start(void)
{
    quali_uart_test_handle_t *hdl;
    test_status_report_handle_t *sr_handle;

    test_status_report_config_t config = {.instance = "iou04-usb-ext-com", .instance_idx = 2, .port = 10001};

    ESP_ERROR_CHECK(new_test_status_report_instance(&sr_handle, &config));

    quali_uart_test_config_t test_config = {
        .uart_num = UART_NUM_1,
        .uart_config = &s_uart_config,
        .rx_buf_size = RX_BUF_SIZE,
        .tx_buf_size = TX_BUF_SIZE,
        .gpio_tx = 15,
        .gpio_rx = 17,
        .gpio_rts = 14,
        .gpio_cts = 16,
        .reporter = sr_handle
    };

    ESP_ERROR_CHECK(new_uart_test(&hdl, &test_config));
}
