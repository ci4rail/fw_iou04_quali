/*
Copyright © 2022 Ci4Rail GmbH
Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
 http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "io4edge.h"
#include "io4edge_core.h"
#include "driver/gpio.h"
#include "driver/uart.h"
#include "io4edge_ttynvt.h"

static char* TAG = "main";

extern void net_init(void);

static bool application_is_working(void)
{
    ESP_LOGI(TAG, "application_is_working called");
    return true;
}

void app_main(void)
{
    ESP_LOGI(TAG, "Start");

    gpio_set_direction(GPIO_NUM_34, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_34, 1);

    io4edge_config_t io4edge_config = {
        .log_config =
            {
                .min_buffered_lines = 5,
            },
    };
    ESP_ERROR_CHECK(io4edge_init(&io4edge_config));


    io4edge_ttynvt_config_t ttynvt_config = {.instance = "iou04-com",
        .instance_idx = 0,
        .port = 10000,
        .socket_listen_task_prio = 5,
        .socket_rx_task_prio = 10,
        .uart_num = UART_NUM_1,
        .rx_buf_size = 1024,
        .tx_buf_size = 1024,
        .gpio_tx = 11,
        .gpio_rx = 13,
        .gpio_rts = 10,
        .gpio_cts = 12,
        .uart_task_prio = 11};

    ESP_ERROR_CHECK(io4edge_ttynvt_new_instance(&ttynvt_config));

    static io4edge_core_config_t io4edge_core_config = {
        .core_server_priority = 5,
        .application_is_working = application_is_working,
    };

    ESP_ERROR_CHECK(io4edge_core_start(&io4edge_core_config));
}
