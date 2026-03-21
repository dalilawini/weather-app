#ifndef EEPROM_STORAGE_H
#define EEPROM_STORAGE_H

#include <Arduino.h>
#include <EEPROM.h>

class EEPROMStorage {
public:
    EEPROMStorage(size_t size = 64);

    void begin();

    void saveMAC(const uint8_t* mac);
    bool loadMAC(uint8_t* mac);
    bool isValidMAC(const uint8_t* mac);

private:
    size_t _size;
    const int _macStart = 0;
};

#endif