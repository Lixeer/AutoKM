#pragma once
/*
HAL(hardware abstraction layer)硬件抽象层
抽象和屏蔽硬件,当你切换不同的设备时候，一样可以使用同样的业务代码
p_hal 的意思是project hal 项目自建的 HAL,不需要完全兼容各平台的所有驱动，仅仅需要必要的兼容，保证功能的进行即可，并且为了和硬件厂商的HAL区分开，故取名p_hal

所有向外暴露的函数和类型都以p_hal开头，例如p_hal_printf,是为了在业务清楚知道来自哪个依赖
*/

#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

typedef int p_hal_err_t;


#define P_HAL_OK 0
#define P_HAL_FAIL -1


/**平台选择**/
#define PLF_ESP32 0
// unsupport 以下宏未支持
#define PLF_STM32 1
#define PLF_GD32 2
#define PLF_RV32 3
#define PLFORM_TARGET PLF_ESP32
/**平台选择end**/

/**平台相关**/
#if PLFORM_TARGET == PLF_ESP32
#include "esp_http_server.h"
typedef httpd_req_t p_hal_http_req_t;
typedef httpd_handle_t p_hal_http_server_core;
typedef httpd_uri_t p_hal_http_uri_t;

typedef struct {
    uint8_t port;

}p_hal_http_config_t;

#endif



/**构建参数**/

typedef uint8_t p_hal_wifi_mode_t;
#define P_HAL_WIFI_MODE_STA 0
#define P_HAL_WIFI_MODE_AP 1
/****/


typedef struct {
    // 必须实现的接口
    p_hal_err_t (*init)(p_hal_wifi_mode_t mode);
    p_hal_err_t (*deinit)(void);
    p_hal_err_t (*begin)(const char *ssid, const char *password);
    
    
} p_hal_wifi_driver_t;

typedef struct{
    p_hal_err_t (*system_init)(void); // 设备初始化 会在所有业务代码开始前执行

}p_hal_device_initializer;
/////////////////

/*http服务器相关*/
#define P_HAL_HTTP_METHOD_GET 0
#define P_HAL_HTTP_METHOD_POST 1
#define P_HAL_HTTP_METHOD_PUT 2
#define P_HAL_HTTP_METHOD_DELETE 3
typedef uint8_t p_hal_http_method_t;





typedef struct{
    p_hal_err_t (*init_server)(void);
    p_hal_err_t (*start)(p_hal_http_server_core *server,p_hal_http_config_t *config);
    p_hal_err_t (*stop)(void);
    p_hal_err_t (*add_handler)(p_hal_http_uri_t *uri)
}p_hal_http_provider;

typedef struct{
    QueueHandle_t *xQueue;
    
}hid_controller_t;


typedef struct{
    p_hal_err_t (*ble_hid_init)(void);
    p_hal_err_t (*get_hid_controller)(hid_controller_t *hid_controller);

}p_hal_hid_provider;

/////////
int p_hal_printf(void *fmt, ...);
const p_hal_wifi_driver_t* p_hal_get_wifi_driver(void);
const p_hal_device_initializer* p_hal_get_device_initializer(void);
const p_hal_http_provider* p_hal_creat_http_provider(void);
const p_hal_hid_provider* p_hal_creat_hid_provider(void);


#if PLFORM_TARGET == PLF_ESP32
#include <stdio.h>
#define p_hal_printf(...) printf(__VA_ARGS__)

#endif
