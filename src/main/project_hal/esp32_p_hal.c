
#include "nvs_flash.h"
#include "p_hal.h"

p_hal_err_t esp32_system_init(void){

    //p_hal_printf("esp32_system_init\n");

    p_hal_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    return ret;
}
p_hal_err_t esp32_wifi_init(void){
    
}
p_hal_err_t esp32_wifi_begin(const char *ssid, const char *password){ 
}