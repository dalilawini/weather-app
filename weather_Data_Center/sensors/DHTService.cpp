#include "DHTService.h"

void DHTService::begin() {
    dhtSensor.setup(12, DHTesp::DHT11); // Connect DHT sensor to GPIO 17
}

void DHTService::update() {

    delay(dhtSensor.getMinimumSamplingPeriod());
    float h = dhtSensor.getHumidity();
    float t = dhtSensor.getTemperature();

    if (!isnan(h) && !isnan(t)) {

        Event::publish(t, h);

    } else {

        Serial.println("DHT read failed");
        Event::publish(25.0,60.0);

    }
}