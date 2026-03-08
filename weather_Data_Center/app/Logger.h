#ifndef LOGGER_H
#define LOGGER_H

#include <Arduino.h>

class Logger {

public:
    static void onSensor(float temp, float hum);

};

#endif