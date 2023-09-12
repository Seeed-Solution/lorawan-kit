
#ifndef __SAMPLER_H
#define __SAMPLER_H
#include "LoRaThread.h"
#include "SysConfig.h"
#include "sensor.h"
#include "utils.h"
#include <Arduino.h>


class SamplerThread
{
  public:
    // SamplerThread(SysConfig &config, UI &ui);
    SamplerThread(SysConfig &config);
    ~SamplerThread()
    {
        // if (mutex) {
        //     vSemaphoreDelete(mutex);
        // }
    }
    void Run();

    // LoRaThread *lora;

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
    // SemaphoreHandle_t mutex;
    // WiFiThread *wifi;
    LoRaThread *lora;
    // SDThread   *sd;
};

#endif