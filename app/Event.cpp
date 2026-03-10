#include "Event.h"

SensorCallback Event::subscribers[5];
int Event::count = 0;

void Event::subscribe(SensorCallback cb) {

    if(count < 5) {
        subscribers[count++] = cb;
    }
}

void Event::publish(float temp, float hum) {

    for(int i=0;i<count;i++) {
        subscribers[i](temp, hum);
    }
}