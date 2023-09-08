#include "grove_dht_sensor.h"
#include "SensorsUtils.h"

grove_dht_sensor::grove_dht_sensor()
{
}
void grove_dht_sensor::init()
{
    is_available = true;
    if (is_available) {
        this->dht = new DHT(DHTPIN, DHTTYPE);;
        dht->begin();
    }
}

bool grove_dht_sensor::read(struct sensor_data *sdata)
{
    // if (!I2C_Detect(grove_i2c_addr[S_DHT], Wire)) {
    //     is_available = false;
    //     return false;
    // } else if (!is_connected) { // first connect
    //     is_connected = true;
    //     if (dht != NULL)
    //         delete dht;
    //     // if (SOFTWRIE_SDAPIN != SDA || SOFTWRIE_SCLPIN != SCL) {
    //     //     softwarei2c.begin(SOFTWRIE_SDAPIN, SOFTWRIE_SCLPIN);
    //     // }
    //     Wire.begin(SOFT_I2C_SDA1, SOFT_I2C_SCL1);
    //     init();
    //     return false; // waiting for next read
    // }
    if(!is_available){
        return false;
    }
    // float temp_hum_val[2] = {0};
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


    if (dht->readTempAndHumidity(temp_hum_val) != 0) {
        sdata->status = false;
    } else {
        LOGSS.print("Temperature: ");
        LOGSS.print(temp_hum_val[1]);
        LOGSS.print(" *C\t");
        LOGSS.print("Humidity: ");
        LOGSS.print(temp_hum_val[0]);
        LOGSS.println(" %");

        data[0]     = (int)(temp_hum_val[1] * 100);
        data[1]     = (int)(temp_hum_val[0] * 100);

        sdata->data      = &data[0];
        sdata->data_type = SENSOR_DATA_TYPE_FLOAT;
        sdata->size      = sizeof(data);
        sdata->id        = GROVE_DHT;
        sdata->name      = name;
        sdata->ui_type   = SENSOR_UI_TYPE_NORMAL;
        sdata->data_unit = data_unit;
        sdata->status = true;
    }
    return true;
}


// bool grove_dht_sensor::read_bk(struct sensor_data *sdata)
// {

//     if (!I2C_Detect(grove_i2c_addr[S_DHT], Wire)) {
//         is_connected = false;
//         return false;
//     } else if (!is_connected) { // first connect
//         is_connected = true;
//         if (dht != NULL)
//             delete dht;
//         // if (SOFTWRIE_SDAPIN != SDA || SOFTWRIE_SCLPIN != SCL) {
//         //     softwarei2c.begin(SOFTWRIE_SDAPIN, SOFTWRIE_SCLPIN);
//         // }
//         Wire.begin(SOFT_I2C_SDA1, SOFT_I2C_SCL1);
//         init();
//         return false; // waiting for next read
//     }

//     // float temp_hum_val[2] = {0};
//     // Reading temperature or humidity takes about 250 milliseconds!
//     // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)


//     if (dht->readTempAndHumidity(temp_hum_val) != 0) {
//         sdata->status = false;
//     } else {
//         sdata->status = true;
//         LOGSS.print("Temperature: ");
//         LOGSS.print(temp_hum_val[1]);
//         LOGSS.print(" *C\t");
//         LOGSS.print("Humidity: ");
//         LOGSS.print(temp_hum_val[0]);
//         LOGSS.println(" %");

//         trans_val[0]     = (temp_hum_val[1] * 100);
//         trans_val[1]     = (temp_hum_val[0] * 100);

//         sdata->data      = &trans_val[0];
//         sdata->data_type = SENSOR_DATA_TYPE_FLOAT;
//         sdata->size      = sizeof(trans_val);
//         sdata->id        = GROVE_DHT;
//         sdata->name      = name;
//         sdata->ui_type   = SENSOR_UI_TYPE_NORMAL;
//         sdata->data_unit = data_unit;
//     }
//     return true;
// }

const char *grove_dht_sensor::get_name()
{
    return this->name;
}

// grove_dht_sensor  buildin_soil;       // Serial.println("Measurement failed!");