#include "App.h"

OLEDService oled;
DHTService dht;
ESPNowService espNow;
Logger Logger;

void App::setup() {

    Serial.begin(115200);

    dht.begin();
    espNow.begin();
    oled.begin();

    Event::subscribe(Logger::onSensor);
    Event::subscribe(ESPNowService::onSensor);
    Event::subscribe(OLEDService::onSensor);

    state = APP_INIT;
    lastTrigger = 0;
}

void App::loop() {
    handleState();
}

void App::handleState() {

    switch(state) {

        case APP_INIT:
            Serial.println("System Init");
            state = APP_IDLE;
        break;

        case APP_IDLE:

            if (millis() - lastTrigger > 2000) {
                lastTrigger = millis();
                state = APP_READ_SENSOR;
            }

        break;

        case APP_READ_SENSOR:

            dht.update();
            state = APP_IDLE;

        break;

        case APP_ERROR:
            Serial.println("Error State");
        break;
    }
}