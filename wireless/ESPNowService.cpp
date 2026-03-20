#include "ESPNowService.h"
ESPNowService *ESPNowService::instance = nullptr;
uint8_t ESPNowService::peerMAC[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

ESPNowService::ESPNowService()
    : connected(false), espNowReady(false)
{
    instance = this; 
}

void ESPNowService::begin()
{
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
}

void ESPNowService::startScan()
{
    Serial.println("[ESPNow] Starting WiFi scan...");
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    WiFi.scanNetworks(true); // async scan
}

bool ESPNowService::handleScan()
{
    int n = WiFi.scanComplete();
    bool noEspFound = true;
    switch (n){
        case WIFI_SCAN_RUNNING:
        return true;

        case WIFI_SCAN_FAILED:
            Serial.println("Scan failed");
        return false;

        case 0:
            Serial.println("No networks found.");
            WiFi.scanDelete();
        return false;
    }

    Serial.println("[ESPNow] Scan complete.");

    for (int i = 0; i < n; i++)
    {
        String ssid = WiFi.SSID(i);

        if (ssid.startsWith("ESP-NOW"))
        {
            WIFI_SSID = ssid.c_str();
            Serial.printf("%d: %s MAC:%s Ch:%d RSSI:%d\n",
                          i,
                          ssid.c_str(),
                          WiFi.BSSIDstr(i).c_str(),
                          WiFi.channel(i),
                          WiFi.RSSI(i));
            memcpy(peerMAC, WiFi.BSSID(i), 6);

            // FORCE OR LOGIC HERE
            peerMAC[0] &= 0xFD;
            connect(WIFI_SSID,WIFI_PASSWORD);
            connected = true;
            noEspFound = false;
        }
        WiFi.scanDelete();
      
    }
    if(noEspFound){
        Serial.println("[ESPNow] No ESP-NOW AP found.");
    }
    return false;
}

void ESPNowService::connect( const char* SSID ,const char* PASSWORD)
{
    WiFi.begin(SSID, PASSWORD);
    unsigned long startTime = millis();
    unsigned long timeout = 5000; // 10 seconds timeout
    
    Serial.print("Connecting to Wi-Fi");
    while (WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    
        if (millis() - startTime > timeout) {
            Serial.println("\nWi-Fi connection timed out!");
            return;
        }
    }

} 

bool ESPNowService::isConnected()
{
    return connected;
}

void ESPNowService::start()
{
    if (espNowReady)
        return;

    Serial.println("[ESPNow] Initializing ESP-NOW...");

    WiFi.disconnect(); // 1. Disconnect from Wi-Fi
    delay(200);
    WiFi.mode(WIFI_STA); // 2. Ensure STA mode (important for ESP-NOW)
    delay(200);

    if (esp_now_init() != 0)
    {
        Serial.println("[ESPNow] Init failed!");
        return;
    }

    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

    if (esp_now_add_peer(peerMAC, ESP_NOW_ROLE_CONTROLLER, 1, NULL, 0) != 0)
    {
        Serial.println("[ESPNow] Failed to add peer!");
        return;
    }

    esp_now_register_send_cb(send_cb);

    espNowReady = true;

    Serial.println("[ESPNow] Ready.");
}

void ESPNowService::onSensor(float temp, float hum)
{
    if ( instance && !instance->espNowReady )
        return;

    StaticJsonDocument<64> doc;
    doc["key"] = 12345;
    doc["Tmp"] = temp;
    doc["Hum"] = hum;
    
    char jsonBuffer[64];
    serializeJson(doc, jsonBuffer);
    
    esp_now_send(peerMAC, (uint8_t*)jsonBuffer, strlen(jsonBuffer));

    Serial.println("ESP-NOW Data Sent");
}

void ESPNowService::send_cb(uint8_t *mac, uint8_t status)
{    Serial.printf("MAC:%02X:%02X:%02X:%02X:%02X:%02X status: %s\n",
    mac[0], mac[1], mac[2],mac[3], mac[4], mac[5],
    status == 0 ? "Success" : "Fail");
}

uint8_t* ESPNowService::getMacAddress(){
    return peerMAC;
}

void ESPNowService::setMacAddress(uint8_t* mac){
    memcpy(peerMAC, mac, 6);
}