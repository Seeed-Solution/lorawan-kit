#ifndef __GROVE_SOIL_SENSOR_H
#define __GROVE_SOIL_SENSOR_H

#include "sensor.h"
#include "utils.h"
#include "Arduino.h"

#define SOILPIN D1
#define READ_NUM 10
#define SOIL_DATA_MAX 1000
#define DATA_VARIANCE_MAX 20

#define SOFTWRIE_SOIL_SDAPIN SDA
#define SOFTWRIE_SOIL_SCLPIN SCL

class grove_soil_sensor : public sensor_base {
  public:
    grove_soil_sensor();
    void        init();
    const char *get_name();
    bool        read(struct sensor_data *data);
    bool        is_available;

  private:
    const char *name = "Soil";
    const char *data_unit = " ";
    int         soil_value;
};

#endif