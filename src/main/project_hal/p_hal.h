#pragma once
/*
HAL(hardware abstraction layer)硬件抽象层
抽象和屏蔽硬件,当你切换不同的设备时候，一样可以使用同样的业务代码
p_hal 的意思是project hal 项目自建的 HAL,不需要完全兼容各平台的所有驱动，仅仅需要必要的兼容，保证功能的进行即可，并且为了和硬件厂商的HAL区分开，故取名p_hal

所有向外暴露的函数和类型都以p_hal开头，例如p_hal_printf,是为了在业务清楚知道来自哪个依赖
*/

typedef int p_hal_err_t;


#define P_HAL_OK 1
#define P_HAL_FAIL 0


/**平台选择**/
#define PLF_ESP32 0
// unsupport 以下宏未支持
#define PLF_STM32 1
#define PLF_GD32 2
#define PLF_RV32 3
#define PLFORM_TARGET PLF_ESP32
/**平台选择end**/

typedef struct {
    // 必须实现的接口
    p_hal_err_t (*init)(void);
    p_hal_err_t (*deinit)(void);
    p_hal_err_t (*begin)(const char *ssid, const char *password);
    
    
} p_hal_wifi_driver_t;

typedef struct{
    p_hal_err_t (*system_init)(void); // 设备初始化 会在所有业务代码开始前执行

}p_hal_device_initializer;

int p_hal_printf(void *fmt, ...);
const p_hal_wifi_driver_t* p_hal_get_wifi_driver(void);
const p_hal_device_initializer* p_hal_get_device_initializer(void);


/**平台相关**/
#if PLFORM_TARGET == PLF_ESP32
#include <stdio.h>
#define p_hal_printf(...) printf(__VA_ARGS__)
#endif