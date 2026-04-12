#pragma once
#include "p_hal.h"
#include <stdint.h>


p_hal_err_t esp32_system_init(void);
p_hal_err_t esp32_wifi_begin(const char *ssid, const char *password);
p_hal_err_t esp32_wifi_init(p_hal_wifi_mode_t mode);
p_hal_err_t esp32_wifi_disconnect(void);


p_hal_err_t esp32_http_server_init(uint8_t port,httpd_handle_t *server);
p_hal_err_t esp32_http_server_start(void);
p_hal_err_t esp32_http_server_stop(void);
p_hal_err_t esp32_http_server_add_handler(p_hal_http_uri_t *uri);


