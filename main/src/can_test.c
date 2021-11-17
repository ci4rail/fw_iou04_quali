/*
Copyright © 2021 Ci4Rail GmbH
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
#include <stdio.h>
#include <stdlib.h>

#include "quali_can_test.h"
#include "test_status_report.h"

#define TX_GPIO_NUM 21
#define RX_GPIO_NUM 33
#define MSG_ID 0x0A3

static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_1MBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
static const twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);

void can_test_start(void)
{
    quali_can_test_handle_t *hdl;
    test_status_report_handle_t *sr_handle;

    test_status_report_config_t config = {.instance = "iou04-usb-ext-can", .instance_idx = 0, .port = 10002};

    ESP_ERROR_CHECK(new_test_status_report_instance(&sr_handle, &config));

    ESP_ERROR_CHECK(new_quali_can_instance(&hdl, sr_handle, &t_config, &f_config, &g_config, MSG_ID));
}
