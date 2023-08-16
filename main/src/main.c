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
#include "io4edge_debug.h"

#include "projdefs.h"
#include "twaiL2.h"

#include "com_test.h"

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

    // enable dcdc converter
    gpio_set_direction(GPIO_NUM_34, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_34, 1);

    io4edge_config_t io4edge_config = {
        .log_config =
            {
                .min_buffered_lines = 30,
                .enable_deferred_console_logging = true,
            },
    };
    ESP_ERROR_CHECK(io4edge_init(&io4edge_config));

    static io4edge_core_config_t io4edge_core_config = {
        .core_server_priority = 5,
        .application_is_working = application_is_working,
    };
    ESP_ERROR_CHECK(io4edge_core_start(&io4edge_core_config));

    // Start dedicated com quali test component for com1 and com2
    com1_test_start();
    com2_test_start();

    //
    // disable CAN_SILENT
    // it is not necessary to enable CAN_SILENT in listen only mode, as the TWAI doesn't send anyway
    //
    gpio_set_direction(GPIO_NUM_18, GPIO_MODE_OUTPUT);
    gpio_set_level(GPIO_NUM_18, 0);

    twaiL2_config_t can_config = {
        .generic =
            {
                .instance_num = 0,
                .port = 10002,

                .server =
                    {
                        9,
                        3072,
                    },
                .connection =
                    {
                        10,
                        10000,  // must fit to CONFIG_FUNCTIONBLOCK_MAX_CMD_MSG_SIZE,
                                // CONFIG_FUNCTIONBLOCK_MAX_DESERIAL_MSG_SIZE, CONFIG_FUNCTIONBLOCK_MAX_CMD_MSG_SIZE
                    },
                .stream =
                    {
                        11,
                        4096,
                    },
                .recording =
                    {
                        23,
                        4096,
                    },
            },
        .tx_gpio = 21,
        .rx_gpio = 33,
        .bus_config = {},
        .rx_queue_len = 300,
        .tx_queue_len = 300,
    };
    // read persistent configuration from "can-config" parameter
    twaiL2_init_persistent_config(&can_config.bus_config);

    ESP_ERROR_CHECK(twaiL2_new(&can_config));

#if 0
    for (;;) {
        io4edge_show_tasks(false);
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
#endif
}
