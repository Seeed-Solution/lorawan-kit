#include "ArduinoNvs.h"
// #include "ESP32Console.h"
#include "SysConfig.h"
#include "argtable3/argtable3.h"
#include "disk91_LoRaE5.h"
#include "esp_console.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "utils.h"
#include <Arduino.h>
#include <SoftwareSerial.h>

#include "LoRaThread.h"
#include "SysConfig.h"


#include "sensor.h"
#include <Wire.h>
// #include "grove_soil_sensor.h"
// #include "grove_dht11_sensor.h"
#include "SamplerThread.h"
#include "Sensors/SensorsUtils.h"
// static void LoRaThreadWrapper(void *param)
// {
//     // SamplerThread *sampler = static_cast<SamplerThread *>(param);
//     LoRaThread *lora = static_cast<LoRaThread *>(param);
//     lora->Run();
// }


TaskHandle_t   LoRataskHandle    = NULL;
TaskHandle_t   SamplertaskHandle = NULL;
SamplerThread *sampler;

void _config()
{
    LOGSS.begin(9600);
    Wire.begin();

    // uint32_t start = millis();
    // while (!LOGSS && (millis() - start) < 1500)
    ; // Open the Serial Monitor to get started or wait for 1.5"

    /*Shared Configuration | System status*/
    SysConfig *cfg      = new SysConfig();
    // cfg->lora_frequency = DSKLORAE5_ZONE_EU868;
    cfg->lora_frequency = DSKLORAE5_ZONE_US915;
    cfg->init();

    delay(1000);
    // LOGSS.println("Sampler Thread Created");
    /*Create LoRa Thread for Communication*/
    // LoRaThread *lora = new LoRaThread(*cfg);

    // LoRaThread *lora = new LoRaThread(*cfg);

    // sampler->lora = new LoRaThread(*cfg);

    // sampler->lora = lora;
    // xTaskCreate(LoRaThreadWrapper, "lora", 4098, lora, 1, NULL);

    sampler          = new SamplerThread(*cfg);

    // xTaskCreate(LoRaThreadWrapper, "lora", 1024 * 20, lora, 2, &LoRataskHandle);
    // xTaskCreate(SamplerThreadWrapper, "sample", 1024 * 20, sampler, 1, &SamplertaskHandle);
    // xTaskCreate(LoRaThreadWrapper, "lora", 1024 * 20, sampler->lora, 2, &LoRataskHandle);
    

    if (cfg->lora_frequency == DSKLORAE5_ZONE_EU868) {
        LOGSS.println("Current Frequency: EU868");
    } else if (cfg->lora_frequency == DSKLORAE5_ZONE_US915) {
        LOGSS.println("Current Frequency: US915");
    } else {
        LOGSS.println("Current Frequency: UNKNOWN");
    }
    // LOGSS.println("LoRa Thread Created");
    // xTaskCreate(TestThread, "test", 4098, NULL, 1, NULL);

    // cmd_init();
}

// #endif
void setup()
{
    // test();
    LOGSS.begin(9600);
    Wire.begin();
    _config();
}

void loop()
{
    // LOGSS.println("Hello World");
    // delay(5000);
    // cmd.poll();
    // using I2C_Detect to deteck I2C device
}
