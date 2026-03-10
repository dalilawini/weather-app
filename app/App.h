#ifndef APP_H
#define APP_H

#include "OLEDService.h"
#include "ESPNowService.h"
#include "DHTService.h"
#include "Logger.h"
#include "Event.h"

enum AppState {
    APP_INIT,
    APP_IDLE,
    APP_READ_SENSOR,
    APP_ERROR
};

class App {

public:
    void setup();
    void loop();

private:
    void handleState();

    AppState state;
    unsigned long lastTrigger;

    DHTService dht;
};

#endif