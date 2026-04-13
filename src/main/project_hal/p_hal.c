



#include "p_hal.h"
//////////////////////////
/**esp32 platform begin**/
#if PLFORM_TARGET == PLF_ESP32
#include "esp32_p_hal.h"




const p_hal_device_initializer* p_hal_get_device_initializer(void){
    static const p_hal_device_initializer initializer = {
        .system_init = esp32_system_init
    };
    return &initializer;
}


const p_hal_wifi_driver_t* p_hal_get_wifi_driver(void){
    static const p_hal_wifi_driver_t wifi_driver = {
        .begin = esp32_wifi_begin,
        .init = esp32_wifi_init,
        .deinit = esp32_wifi_disconnect
    };
    return &wifi_driver;
}
const p_hal_http_provider* p_hal_creat_http_provider(void){
    static const p_hal_http_provider http_server = {
        .init_server = esp32_http_server_init,
        .start = esp32_http_server_start,
        .stop = esp32_http_server_stop,
        .add_handler = esp32_http_server_add_handler
    };
    return &http_server;
}

const p_hal_hid_provider* p_hal_creat_hid_provider(void){
    static const p_hal_hid_provider hid_provider = {
        .ble_hid_init = esp32_ble_hid_init,
        .get_hid_controller = esp32_get_hid_controller,
        
    };
    return &hid_provider;
}

/**esp32 platform end**/
////////////////////////

/**rv32 platform begin**/
#elif PLFORM_TARGET == PLF_RV32


/**rv32 platform end**/
#endif


