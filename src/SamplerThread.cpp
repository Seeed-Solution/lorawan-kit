
#include "SamplerThread.h"
#include "sensor.h"
// #include "sensors/FakeSensor.h"
// #include "sensors/LIS3DHTRSensor.h"
// #include "sensors/buildin_light_sensor.h"
// #include "sensors/buildin_mic.h"
// #include "sensors/grove_sgp30_sensor.h"
// #include "sensors/grove_sht4x_sensor.h"
// #include "sensors/grove_vl53l0x_sensor.h"
#include "sensors/grove_soil_sensor.h"
// #include "sensors/grove_visionai_sensor.h"
#include "sensors/SensorsUtils.h"
#include "sensors/grove_dht_sensor.h"

// #include "SensorsUtils.h"
// #include "grove_dht11_sensor.h"
// #include "grove_soil_sensor.h"
#include <vector>

SamplerThread::SamplerThread(SysConfig &config)
    : cfg(config)
{
}

void SamplerThread::Run()
{
    // wifi = new WiFiThread(cfg);
    // lora = new LoRaThread(cfg); // Extern
    // sd   = new SDThread(cfg);

    std::vector<sensor_base *> sensors;
    // sensors.push_back(new buildin_light_sensor());
    // sensors.push_back(new buildin_mic());
    // sensors.push_back(new LIS3DHTRSensor()); // buildin-imu
    // sensors.push_back(new grove_sht4x_sensor());
    // sensors.push_back(new grove_sgp30_sensor());
    // sensors.push_back(new grove_vl53l0x_sensor());
    // sensors.push_back(new grove_visionai_sensor());
    // sensors.push_back(new FakeSensor());
    sensors.push_back(new grove_soil_sensor());
    sensors.push_back(new grove_dht_sensor());
    for (auto sensor : sensors) {
        sensor->init();
    }

    while (true) {
        if (cfg.lock()) {
            if ((this->cfg.lora_status != LORA_JOIN_SUCCESS && this->cfg.lora_status != LORA_SEND_SUCCESS)) {
                LOGSS.println("Sampler: Wait for LoRa To Join");
                delay(5000);
                continue;
            }
            cfg.unlock();
        }
        std::vector<sensor_data *> datas;
        for (auto sensor : sensors) {
            if (sensor->read(&sdata)) {
                // LOGSS.printf("Sampling %s\r\n", sdata.name);
                //  for (size_t i = 0; i < sdata.size; i++) {
                //    LOGSS.printf("%02x ", ((uint8_t *)sdata.data)[i]);
                //  }
                //  for (auto sensor : sensors) {
                //    LOGSS.printf("Sampling %s\n", sensor->get_name());
                //  }
                //  LOGSS.println(sensors.size());
                // sensorMail.Send((void *)&sdata, sizeof(sdata));
                // deep Copy data into datas vector
                datas.push_back(new sensor_data(sdata)); // 才进入 datas
            }
            // LOGSS.println("SamplerThread");
        }
        lora->LoRaPushData(datas);
        // wifi->WiFiPushData(datas);
        // sd->SDPushData(datas);
        // display.UIPushData(datas);
        // display.UIPushLog(sensor_base::slog);
        for (auto data : datas) {
            delete data;
        }
        datas.clear();
        datas.shrink_to_fit();
        delay(SENSOR_READ_DELAY);
        // Delay(Ticks::MsToTicks(SENSOR_READ_DELAY));
        // LOGSS.printf("SamplerThread Stacks Free Bytes Remaining %d\r\n",
        // uxTaskGetStackHighWaterMark(GetHandle()));
    }
}
