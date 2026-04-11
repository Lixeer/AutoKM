



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


/**esp32 platform end**/
////////////////////////

/**rv32 platform begin**/
#elif PLFORM_TARGET == PLF_RV32


/**rv32 platform end**/
#endif


