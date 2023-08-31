/*
 * File: utils.h
 *
 * Created on:  28 August 2023
 *     Author: Spencer Yan
 *
 * Description: Description of the file
 *
 * Copyright: © 2023, Seeed Studio
 */

#ifndef utils_H
#define utils_H
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <vector>

#define LOGSS Serial
#define DelayMinutes(x) delay(x * 60 * 1000)
#define PRINT(...) LOGSS.print(__VA_ARGS__)
#define PRINTLN(...) LOGSS.println(__VA_ARGS__)
#define PRINTF(...) LOGSS.printf(__VA_ARGS__)
#define DEBUG(...)                  \
    {                               \
        LOGSS.print(__FUNCTION__); \
        LOGSS.print("() [");       \
        LOGSS.print(__FILE__);     \
        LOGSS.print(":");          \
        LOGSS.print(__LINE__);     \
        LOGSS.print("]:\t");       \
        LOGSS.printf(__VA_ARGS__); \
        LOGSS.println();           \
    }

void printHex(uint8_t *data, size_t len, String startLine = "\n", String endLine = "\n");
void printHex(std::vector<uint8_t> &data, String startLine = "\n", String endLine = "\n");

enum lora_status_type {
    LORA_INIT_START,
    LORA_INIT_FAILED,
    LORA_INIT_SUCCESS,
    LORA_JOIN_FAILED,
    LORA_JOIN_SUCCESS,
    LORA_SEND_FAILED,
    LORA_SEND_SUCCESS,
};

struct sensor_data {
    const char   *name;
    const char   *data_unit;
    const void   *data;
    unsigned char size;
    uint16_t       id;
    bool          status;        // 0: normal, 1: error
    uint8_t       data_type = 0; // 0: int32_t, 1: float(*100)
    uint8_t       ui_type   = 0; // 0: normal, 1: average value
};
enum sensor_data_type {
    SENSOR_DATA_TYPE_INT32 = 0,
    SENSOR_DATA_TYPE_FLOAT,
};

enum sensor_ui_type {
    SENSOR_UI_TYPE_NORMAL = 0,
    SENSOR_UI_TYPE_AVERAGE,
};
enum sensor_type {
    /* buildin sensor */
    // BUILDIN_LIGHT = 1,
    // BUILDIN_MIC,
    // LIS3DHTRSENSOR,
    /* grove i2c sensor */
    // GROVE_VISIONAI,
    // GROVE_SHT4X,
    // GROVE_SGP30,
    // GROVE_VL53L0X,
    GROVE_DHT,
    /* grove analog sensor */
    GROVE_SOIL,

};

enum lora_freq {
    UNDEFINED,
    EU868,
    US915,
    AS923_1,
    AS923_2,
    AS923_3,
    AS923_4,
    KR920,
    IN865,
    AU915,
};

struct log_data {
    char     data[64];
    uint32_t time;
};


int clean_serial(Stream &serial);
int ATCommand(SoftwareSerial * swSerial, const char *expected_response, int timeout, const char *command_format, const char *command_args);

#endif // utils_H