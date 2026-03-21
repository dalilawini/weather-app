#ifndef APP_H
#define APP_H

#include "OLEDService.h"
#include "ESPNowService.h"
#include "DHTService.h"
#include "Logger.h"
#include "Event.h"
#include "IO.h"
#include "EEPROMStorage.h"

enum AppState {
    APP_INIT,
    APP_SCAN,
    APP_CONNECT,
    APP_IDLE,
    APP_READ_SENSOR,
};

class App {

public:
    void setup();
    void loop();

private:
    void handleState();

    AppState state;
    unsigned long lastTrigger;

    unsigned long lastAction;
    bool scanStarted;

    OLEDService oled;
    DHTService dht;
    ESPNowService espNow;
    IO io;
    EEPROMStorage storage;

    uint8_t peerMAC[6];

};

#endif