#include "App.h"

void App::setup() {
    Serial.begin(115200);

    dht.begin();
    espNow.begin();
    oled.begin();
    io.begin();
    storage.begin();

    Event::subscribe(Logger::onSensor);
    Event::subscribe(ESPNowService::onSensor);
    Event::subscribe(OLEDService::onSensor);

    state = APP_INIT;
    scanStarted = false;
    lastTrigger = 0;
}

void App::loop() {
    handleState();
}

void App::handleState() {

    switch(state) {

        case APP_INIT:
            Serial.println("System Init");
            if(storage.loadMAC(peerMAC)){
                espNow.setMacAddress(peerMAC);
                state = APP_CONNECT;
            }else{
                state = APP_SCAN;
            }
        break;

        case APP_SCAN:
            if (!scanStarted) {
                espNow.startScan();
            }

            scanStarted = espNow.handleScan();

            if (espNow.isConnected()) {
                storage.saveMAC(espNow.getMacAddress());
                scanStarted = false;
                state = APP_CONNECT;
            }
        break;

        case APP_CONNECT:
            Serial.println("[APP] CONNECT");

            espNow.start();

            state = APP_IDLE;
        break;

        case APP_IDLE:
            if(io.isHoldDetected()){
                state = APP_SCAN;
            }
            if (millis() - lastTrigger > 2000) {
                lastTrigger = millis();
                state = APP_READ_SENSOR;
            }

        break;

        case APP_READ_SENSOR:

            dht.update();
            state = APP_IDLE;

        break;

    }
}