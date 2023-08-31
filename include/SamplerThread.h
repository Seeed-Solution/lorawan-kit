
#ifndef __SAMPLER_H
#define __SAMPLER_H
#include "utils.h"
#include "SysConfig.h"
#include "LoRaThread.h"
#include "sensor.h"
#include <Arduino.h>

class SamplerThread{
  public:
    // SamplerThread(SysConfig &config, UI &ui);
    SamplerThread(SysConfig &config);
    void Run();
    LoRaThread *lora;
  protected:
    // virtual void Run();

  private:
    int          DelayInMs;
    sensor_base *sensor;

  private:
    struct sensor_data sdata;

    // UI   &display;
    SysConfig &cfg;

  private:
    // WiFiThread *wifi;
    // LoRaThread *lora;
    // SDThread   *sd;
};

#endif