#ifndef _DHT11_H
#define _DHT11_H

#include "Arduino.h"
#include "DHT.h"
#include "sensor.h"
#include "utils.h"

// #define SOFTWRIE_SDAPIN D0
// #define SOFTWRIE_SCLPIN D1

// #define DHTTYPE         DHT11 // DHT 11
// #define DHTTYPE DHT22   // DHT 22  (AM2302)
// #define DHTTYPE DHT21   // DHT 21 (AM2301)
// #define DHTTYPE DHT10   // DHT 10
#define DHTTYPE DHT11 // DHT 20
#define DHTPIN  D0    // what pin we're connected to（DHT10 and DHT20 don't need define it）
class grove_dht_sensor : public sensor_base
{
  public:
    grove_dht_sensor();
    void        init();
    const char *get_name();
    bool        read(struct sensor_data *data);
    // bool        is_connected;
    bool is_available;

  private:
    const char *name      = "DHT";
    const char *data_unit = " ";
    float       temp_hum_val[2];
    int         data[2];
    DHT        *dht;
};


#endif