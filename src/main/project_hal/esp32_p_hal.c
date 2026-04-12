
#include "esp_err.h"
#include "esp_netif.h"
#include "esp_wifi_types_generic.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "p_hal.h"
#include "esp_wifi.h"

#include <string.h>
#define TAG "[esp32_p_hal]"

#define _ERROR_CHECK(code) if(code != P_HAL_OK){return code;}
#define println(x) printf(x);printf("\n");

static bool ready = false;
static void wifi_event_handler_STA(void *arg, esp_event_base_t event_base,int32_t event_id, void *event_data) {
    // 处理WIFI事件
    if (event_base == WIFI_EVENT) {
        switch (event_id) {
            case WIFI_EVENT_STA_START:
                // 记录WIFI驱动就绪日志
                p_hal_printf("%s wifi driver ready\n",TAG);
                ready = true;
                break;
            case WIFI_EVENT_STA_CONNECTED:
                // 记录成功连接到热点日志
                p_hal_printf("%s wifi connect success\n",TAG);
                break;
            case WIFI_EVENT_STA_DISCONNECTED:
                // 记录热点断开日志并启用自动重连
                p_hal_printf("%s wifi disconnected\n",TAG);
                esp_wifi_connect();
                break;
        }
    // 处理IP事件
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        // 获取IP事件数据
        ip_event_got_ip_t *event = (ip_event_got_ip_t*) event_data;
        // 记录成功获取IP日志
        p_hal_printf( "%s成功获取IP:%d.%d.%d.%d\n",TAG,IP2STR(&event->ip_info.ip));
    }
}





p_hal_err_t esp32_system_init(void){

    //p_hal_printf("esp32_system_init\n");

    p_hal_err_t ret;
    ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        _ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    _ERROR_CHECK( ret );
    return ret;
}

p_hal_err_t esp32_wifi_init(p_hal_wifi_mode_t mode){
    /*
    暂时支持sta模式
    */
    p_hal_printf("wifi init ss1\n");
    ESP_ERROR_CHECK( esp_netif_init() );

    ESP_ERROR_CHECK( esp_event_loop_create_default() );
    
    esp_netif_create_default_wifi_sta();

    // 第5步：初始化WiFi驱动
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    
    esp_event_handler_instance_t wifi_event_handle, ip_event_handle;
    esp_event_handler_instance_register(WIFI_EVENT,ESP_EVENT_ANY_ID, &wifi_event_handler_STA,NULL,&wifi_event_handle);
    esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP,&wifi_event_handler_STA, NULL, &ip_event_handle);
    p_hal_printf("wifi init ss2\n");



    return P_HAL_OK;
}
p_hal_err_t esp32_wifi_begin(const char *ssid, const char *password){ 
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "empty",
            .password = "empty",
            //.threshold.authmode = WIFI_AUTH_WPA2_PSK
        },
        
    };
    strncpy((char *)wifi_config.sta.ssid, ssid, sizeof(wifi_config.sta.ssid) - 1);
    strncpy((char *)wifi_config.sta.password, password, sizeof(wifi_config.sta.password) - 1);
    
    // 确保字符串终止
    wifi_config.sta.ssid[sizeof(wifi_config.sta.ssid) - 1] = '\0';
    wifi_config.sta.password[sizeof(wifi_config.sta.password) - 1] = '\0';
   
    
    
    _ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    _ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    if(esp_wifi_start() == ESP_OK){
        
        _ERROR_CHECK( esp_wifi_connect() );
    }
    return P_HAL_OK;
}

p_hal_err_t esp32_wifi_disconnect(void){ 
    return P_HAL_OK;
}