#include "SysConfig.h"

extern "C" {
void cm_printf(const char *format, ...)
{
    char print_buf[1024] = {0};

    va_list args;
    va_start(args, format);
    int r = vsnprintf(print_buf, sizeof(print_buf), format, args);
    va_end(args);

    if (r > 0) {
        LOGSS.write(print_buf);
    }
}
}

SysConfig::SysConfig(/* args */)
{
    xMutex = xSemaphoreCreateMutex();
    if (xMutex == NULL) {
        LOGSS.println("SysConfig: Mutex was not created");
        // Mutex was not created.
        // Handle the error here.
    }
}

SysConfig::~SysConfig()
{
}

void SysConfig::init()
{

    // store.begin("SysConfig");

    // ReadAllConfig();

    // 挂载文件系统
    // if (SysConfig::lock == NULL) {
    //     SysConfig::lock = xSemaphoreCreateMutex();
    // }
    // spi_flash_mount = SFUD.begin();

    // // 如果flash挂载成功 则映射改空间
    // if (spi_flash_mount) {
    //     const sfud_flash *_flash = sfud_get_device_table() + 0;
    //     // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters
    //     // respectively
    //     usb_msc.setID("K1101", "Mass Storage", "1.0");
    //     // Set disk size
    //     usb_msc.setCapacity((_flash->chip.capacity / _flash->chip.erase_gran),
    //                         _flash->chip.erase_gran);
    //     // Set callback
    //     usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);
    //     // Set Lun ready (RAM disk is always ready)
    //     usb_msc.setUnitReady(true);
    //     usb_msc.begin();
    //     ReadAllConfig();
    // }
    // pinMode(SDCARD_DET_PIN, INPUT);
    // if (digitalRead(SDCARD_DET_PIN) == LOW) {
    //     sd_mount = SD.begin(SDCARD_SS_PIN, SDCARD_SPI, 4000000UL);
    // }else
    // 	LOGSS.println("sd card not insert");
}

// void SysConfig::set_lora_freq(uint8_t frequency)
// {
// 	this->lora_frequency = frequency;
// }

// uint8_t SysConfig::get_lora_freq()
// {
// 	return this->lora_frequency;
// }


void SysConfig::ReadAllConfig()
{
    cfg_available  = true;
    String DevAddr = String(NVS.getString(store_keys_str[ENUM_DevAddr]));
    String DevEui  = String(NVS.getString(store_keys_str[ENUM_DevEui]));
    String AppEui  = String(NVS.getString(store_keys_str[ENUM_AppEui]));

    if (DevAddr != "") {
        LOGSS.printf("Read DevAddr: %s\r\n", DevAddr);
    } else {
        LOGSS.println("NVS is empty");
    }
    if (DevEui != "") {
        LOGSS.printf("Read DevEui: %s\r\n", DevEui);
    } else {
        LOGSS.println("NVS is empty");
    }
    if (AppEui != "") {
        LOGSS.printf("Read AppEui: %s\r\n", AppEui);
    } else {
        LOGSS.println("NVS is empty");
    }
}

// void SysConfig::ResetAllConfig() {
//     cfg_available = true;
//     if(NVS.getString(store_keys_str[DevAddr]) != ""){
//         LOGSS.printf("Read DevAddr: %s\r\n",);
//     }
//     else{
//         LOGSS.println("NVS is empty");
//     }
// }

// void SysConfig::ReadConfig(store_keys key)
// {
//     cfg_available = true;
//     if(NVS.getString(store_keys_str[key]) != ""){
//         LOGSS.printf("Read DevAddr: %s\r\n",);
//     }
//     else{
//         LOGSS.println("NVS is empty");
//     }
// }

// Lock/Take the mutex
bool SysConfig::lock(TickType_t xTicksToWait)
{
    return xSemaphoreTake(xMutex, xTicksToWait) == pdTRUE;
}

// Unlock/Give the mutex
void SysConfig::unlock()
{
    xSemaphoreGive(xMutex);
}