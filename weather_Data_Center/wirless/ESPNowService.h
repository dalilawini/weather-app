#ifndef ESPNOWSERVICE_H
#define ESPNOWSERVICE_H
#include <Arduino.h>
#include <ESP8266WiFi.h>

extern "C" {
#include <espnow.h>
}

class ESPNowService {

public:
    void begin();
    static void onSensor(float temp, float hum);


};

#endif
