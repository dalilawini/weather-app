#ifndef OLEDSERVICE_H
#define OLEDSERVICE_H

class OLEDService {
#define I2C_ADDRESS 0x3C

public:
    void begin();
    static void onSensor(float temp, float hum);

};

#endif