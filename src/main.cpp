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

static void LoRaThreadWrapper(void *param)
{
    // SamplerThread *sampler = static_cast<SamplerThread *>(param);
    LoRaThread *lora = static_cast<LoRaThread *>(param);
    lora->Run();
}

static void SamplerThreadWrapper(void *param)
{
    SamplerThread *sampler = static_cast<SamplerThread *>(param);
    sampler->Run();
}
#include "Sensors/SensorsUtils.h"

static void TestThread(void *param)
{

    for (;;) {
        Serial.println("------I2C Scanner start-----");
        byte error, address;
        int  nDevices;

        Serial.println("Scanning...");

        nDevices = 0;
        for (address = 1; address < 127; address++) {
            // The i2c_scanner uses the return value of the Write.endTransmisstion to see if
            // a device did acknowledge to the address.
            Wire.beginTransmission(address);
            error = Wire.endTransmission();

            if (error == 0) {
                Serial.print("I2C device found at address 0x");
                if (address < 16)
                    Serial.print("0");
                Serial.print(address, HEX);
                Serial.println(" !");
                nDevices++;
            } else if (error == 4) {
                Serial.print("Unknown error at address 0x");
                if (address < 16)
                    Serial.print("0");
                Serial.println(address, HEX);
            }
        }
        if (nDevices == 0)
            Serial.println("No I2C devices found\n");
        else
            Serial.println("done\n");

        Serial.println("-----I2C Scanner end-----");
        delay(5000); // Wait 5 seconds for the next scan
    }
}

void setup()
{
    LOGSS.begin(9600);
    Wire.begin();
    softwarei2c.begin(SOFT_I2C_SDA, SOFT_I2C_SCL);
    uint32_t start = millis();
    while (!LOGSS && (millis() - start) < 1500)
        ; // Open the Serial Monitor to get started or wait for 1.5"

    /*Shared Configuration | System status*/
    SysConfig *cfg      = new SysConfig();
    cfg->lora_frequency = DSKLORAE5_ZONE_EU868;
    // cfg->lora_frequency = DSKLORAE5_ZONE_US915;
    cfg->init();
    Serial.println("------Wire I2C Scanner start-----");
    for (int i = 0; i < SENSOR_I2C_MAX; i++) {
        if (I2C_Detect(grove_i2c_addr[i], Wire)) {
            LOGSS.printf("detected sensor 0x");
            LOGSS.println(grove_i2c_addr[i], HEX);
        }
    }
    Serial.println("-----Wire I2C Scanner end-----");
    Serial.println("------softwarei2c Scanner start-----");
    for (int i = 0; i < SENSOR_I2C_MAX; i++) {
        if (I2C_Detect(grove_i2c_addr[i], softwarei2c)) {
            LOGSS.printf("detected sensor 0x");
            LOGSS.println(grove_i2c_addr[i], HEX);
        }
    }
    Serial.println("-----softwarei2c Scanner end-----");
    delay(1000);
    SamplerThread *sampler = new SamplerThread(*cfg);
    /*Create Sampler Thread for Senor data measuring*/
    xTaskCreate(SamplerThreadWrapper, "sample", 4098, sampler, 1, NULL);

    /*Create LoRa Thread for Communication*/
    // LoRaThread *lora = new LoRaThread(*cfg);
    sampler->lora = new LoRaThread(*cfg);
    // sampler->lora = lora;
    // xTaskCreate(LoRaThreadWrapper, "lora", 4098, lora, 1, NULL);
    xTaskCreate(LoRaThreadWrapper, "lora", 4098, sampler->lora, 1, NULL);

    // xTaskCreate(TestThread, "test", 4098, NULL, 1, NULL);

    // cmd_init();
}

void loop()
{
    // cmd.poll();
    // using I2C_Detect to deteck I2C device
}
