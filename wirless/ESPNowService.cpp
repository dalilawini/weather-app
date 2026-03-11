#include "ESPNowService.h"

uint8_t peerAddress[] = {0x24,0x6F,0x28,0xAA,0xBB,0xCC};

struct SensorPacket {
    float temperature;
    float humidity;
};

void ESPNowService::begin() {

    WiFi.mode(WIFI_STA);

    if (esp_now_init() != 0) {

        Serial.println("ESP-NOW Init Failed");
        return;

    }

    esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
    esp_now_add_peer(peerAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);

    Serial.println("ESP-NOW Ready");
}

void ESPNowService::scan() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
  
    Serial.println("Scanning...");
    int n = WiFi.scanNetworks();

    for (int i = 0; i < n; ++i) {
        String name = WiFi.SSID(i);
      
        if (name.startsWith("ESP-NOW")) {
            WiFi.begin(name, password); // 3. Attempt to connect to the specified network
          Serial.printf("%d: %s MAC:%s Ch:%d RSSI:%d\n",
                        i,
                        name.c_str(),
                        WiFi.BSSIDstr(i).c_str(),
                        WiFi.channel(i),
                        WiFi.RSSI(i));
        }
      }
}

void ESPNowService::onSensor(float temp, float hum) {

    SensorPacket packet;

    packet.temperature = temp;
    packet.humidity = hum;

    esp_now_send(peerAddress, (uint8_t*)&packet, sizeof(packet));

    Serial.println("ESP-NOW Data Sent");
}