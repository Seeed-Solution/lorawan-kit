
#ifndef __SENSORSUTILS_H__
#define __SENSORSUTILS_H__
#include "Arduino.h"
#include "Wire.h"
#include "SoftwareI2C.h"
#include "SysConfig.h"

#define SOFT_I2C_SCL D1
#define SOFT_I2C_SDA D2
// #define SOFT_I2C_SDA SDA
// #define SOFT_I2C_SCL SCL
// #define I2C_ADD_AIVISION (0x62)
// #define I2C_ADDR_SGP30   (0x58)
// #define I2C_ADDR_SHT4X   (0x44) // Type B = 0x45
// #define IIC_ADDR_VL53LX0 (0x29)
enum grove_i2c_index{S_VISION, S_SGP30, S_SHT4X, S_VL53LX0, S_DHT, S_ALL};
#define SENSOR_I2C_MAX S_ALL
const uint8_t grove_i2c_addr[S_ALL] = { 0x62, 0x58, 0x44, 0x29, 0x38};
extern SoftwareI2C softwarei2c;

template <typename T> 
inline bool I2C_Detect(uint8_t address, T& wire) { // Don't use SoftWare
    wire.beginTransmission(address);
    return ( wire.endTransmission()== 0 );
}

bool Grove_I2C_Check(TwoWire& wire);
bool Grove_I2C_Check(SoftwareI2C& wire);
//Scan the specified address I2C device to determine whether it is connected.
template <typename T> bool I2CScanner(uint8_t address, T wire);
template <typename T> bool I2CScanner(T wire);
#endif // __SENSORSUTILS_H__