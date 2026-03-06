#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "OLEDService.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OLEDService::begin() {
    if(!display.begin(I2C_ADDRESS, true)) {
        Serial.println("OLED init failed");
        return;
    }

    display.clearDisplay();
    display.setTextSize(1);

    display.setCursor(0,0);
    display.println("System Start...");
    display.display();
}

void OLEDService::onSensor(float temp, float hum) {

    display.clearDisplay();

    display.setTextSize(1);
    display.setCursor(0,0);
    display.println("ESP8266 Sensor Node");

    display.setCursor(0,20);
    display.print("Temp: ");
    display.print(temp);
    display.println(" C");

    display.setCursor(0,40);
    display.print("Humidity: ");
    display.print(hum);
    display.println(" %");

    display.display();
}