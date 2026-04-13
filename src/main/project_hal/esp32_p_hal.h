#pragma once
#include "p_hal.h"
#include <stdint.h>
#include "esp_http_server.h"



p_hal_err_t esp32_system_init(void);
p_hal_err_t esp32_wifi_begin(const char *ssid, const char *password);
p_hal_err_t esp32_wifi_init(p_hal_wifi_mode_t mode);
p_hal_err_t esp32_wifi_disconnect(void);


p_hal_err_t esp32_http_server_init(void);
p_hal_err_t esp32_http_server_start(p_hal_http_server_core *server,p_hal_http_config_t *config);
p_hal_err_t esp32_http_server_stop(void);
p_hal_err_t esp32_http_server_add_handler(p_hal_http_uri_t *uri);

p_hal_err_t esp32_ble_hid_init(void);
p_hal_err_t esp32_get_hid_controller(hid_controller_t *hid_controller);