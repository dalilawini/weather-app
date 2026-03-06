#ifndef DHTSERVICE_H
#define DHTSERVICE_H
#include <DHTesp.h>
#include <Arduino.h>
#include "Event.h"

class DHTService {

public:
    void begin();
    void update();
private:
DHTesp dhtSensor;

};

#endif