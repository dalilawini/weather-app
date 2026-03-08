#include "Logger.h"

void Logger::onSensor(float temp, float hum) {

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" C  Humidity: ");
    Serial.println(hum);

}