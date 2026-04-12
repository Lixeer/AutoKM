#pragma once
#include "p_hal.h"


p_hal_err_t esp32_system_init(void);
p_hal_err_t esp32_wifi_begin(const char *ssid, const char *password);
p_hal_err_t esp32_wifi_init(p_hal_wifi_mode_t mode);
p_hal_err_t esp32_wifi_disconnect(void);