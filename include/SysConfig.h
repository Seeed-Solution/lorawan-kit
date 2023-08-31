
#ifndef __SYSCONFIG_H__
#define __SYSCONFIG_H__
#include "ArduinoNvs.h"
#include "utils.h"
#include <Arduino.h>
#include <FreeRTOS.h>
#include <nvs.h>
#include <task.h>

#include <stdint.h>

// X Macro
#define STORE_KEYS               \
    X(ENUM_SSID, "SSID")         \
    X(ENUM_PASSWORD, "PASSWORD") \
    X(ENUM_DevAddr, "DevAddr")   \
    X(ENUM_DevEui, "DevEui")     \
    X(ENUM_AppEui, "AppEui")

#define X(ENUM, STR) ENUM,
enum store_keys { STORE_KEYS };
#undef X

#define X(ENUM, STR) STR,
static const char *store_keys_str[] = {STORE_KEYS};
#undef X

struct LoRaBandInfo {
    char   *type;
    char   *frequency;
    char   *country;
    uint8_t band;
};

// struct LoRaBandInfo lora_band_info[3] = {
//     {"US", "915", "North America", 2},
//     {"EU", "868", "European Region", 1},
//     {"AU", "915", "Australia", 9},
// };


class SysConfig
{
  public:
    /* wifi */
    // String ssid;
    // String password;
    // mqtt_server cloud = CLOUD_AZURE;
    /* ubidots */
    // String mqtt_client_name;
    // String token;
    // String device_label;
    /* azure */
    // String id_scope;
    // String registration_id;
    // String symmetric_key;

    uint8_t lora_frequency;
    bool    lora_on                  = true;
    // bool             wifi_on         = false;
    // bool             wificonnected   = false;
    // int16_t          wifi_rssi       = 0;
    lora_status_type lora_status     = LORA_INIT_START;
    int16_t          lora_rssi       = 0;
    int16_t          lora_fcnt       = 0;
    int16_t          lora_sucess_cnt = 0;
    // uint8_t          sd_status       = 0; // 0- not init, 1-  connected, 2- sd full
    uint16_t sensor_save_flag        = 0;

    // static SemaphoreHandle_t lock;

  public:
    SysConfig(/* args */);
    ~SysConfig();
    void init();

    void ReadAllConfig();
    void ResetAllConfig();
    void ReadConfig(store_keys key);


  private:
    /* data */
    bool       spi_flash_mount;
    bool       cfg_available;
    ArduinoNvs store;
    // Adafruit_USBD_MSC usb_msc;
};

#endif // __SYSCONFIG_H__