#include "./app/App.cpp"
#include "./app/Event.cpp"
#include "./app/Logger.cpp"
#include "./display/OLEDService.cpp"
#include "./sensors/DHTService.cpp"
#include "./wirless/ESPNowService.cpp"


#include "App.h"

App app;

void setup() {
    app.setup();
    delay(1000);
}

void loop() {
    app.loop();
}