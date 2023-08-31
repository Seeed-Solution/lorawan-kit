
#ifndef __LORATHREAD_H__
#define __LORATHREAD_H__

#include "Arduino.h"
#include "SysConfig.h"
#include "disk91_LoRaE5.h"
#include "utils.h"
#include <vector>
#include <freeRTOS.h>

// create a buttion class use ooFreeRTOS task

class LoRaThread{
  public:
    LoRaThread(SysConfig &config);
    void LoRaPushData(std::vector<sensor_data *> d);
    void Run();
  private:
    void Init();
    void Join();
    bool SendDeviceInfo();
    bool SendVisionAIInfo();
    bool SendBuildinSensorData();
    bool SendGroveSensorData();
    bool SendAiVisionData();
    bool SendData(uint8_t *data, uint8_t len, uint8_t ver);

  protected:
    // virtual void Run();

  private:
    SysConfig     &cfg;
    Disk91_LoRaE5 *lorae5;
    const uint8_t  v1 = 2;
    const uint8_t  v2 = 3;
    uint8_t        downlink_rxBuff[16];
    uint8_t        downlink_rxSize = 16;
    uint8_t        downlink_rxPort;
    uint8_t        frequency;

    std::vector<sensor_data> lora_data;
    bool                     lora_data_ready = true;
};

#endif // __LORATHREAD_H__