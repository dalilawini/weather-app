#ifndef ESPNOWSERVICE_H
#define ESPNOWSERVICE_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>

extern "C" {
    #include <espnow.h>
    #include <user_interface.h>
}

class ESPNowService {
public:
    static ESPNowService* instance;

    ESPNowService();

    void begin();

    void startScan();
    bool handleScan();

    bool isConnected();
    void start(); // init ESP-NOW
    uint8_t* getMacAddress();
    void setMacAddress(uint8_t* );

    static void onSensor(float temp, float hum);
    static void send_cb(uint8_t *mac, uint8_t status);

    const char* WIFI_SSID = "MyESP_AP";
    const char* WIFI_PASSWORD = "12345678";
private:
    void connect( const char* SSID ,const char* PASSWORD);

    static uint8_t peerMAC[6];  // MAC of AP / ESP-NOW peer
    bool connected;
    bool espNowReady;

};

#endif