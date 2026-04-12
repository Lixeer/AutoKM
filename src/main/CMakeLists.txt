idf_component_register(SRCS "auto_km_main.c"
                            "esp_hidd_prf_api.c"
                            "hid_dev.c"
                            "hid_device_le_prf.c"
                            "project_hal/p_hal.c"
                            "project_hal/esp32_p_hal.c"
                    PRIV_REQUIRES bt nvs_flash esp_driver_gpio esp_wifi
                    INCLUDE_DIRS "." "./project_hal")

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-unused-const-variable)
