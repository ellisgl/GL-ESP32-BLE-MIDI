#ifndef BLE_MIDI_SERVER_H
#define BLE_MIDI_SERVER_H

#include "GLBLEMidiBase.h"

class CharacteristicCallback: public BLECharacteristicCallbacks {
public:
    CharacteristicCallback(std::function<void(uint8_t*, uint8_t)> onWriteCallback);
private:
    void onWrite(BLECharacteristic *pCharacteristic);
    std::function<void(uint8_t*, uint8_t)> onWriteCallback = nullptr;
};

class GLBLEMidiServerClass : public GLBLEMidi, public BLEServerCallbacks {
public:
    void begin(const std::string deviceName);
    void begin(const std::string deviceName, CharacteristicCallback *pCharacteristicCallback);
    void setOnConnectCallback(void (*const onConnectCallback)());
    void setOnDisconnectCallback(void (*const onDisconnectCallback)());



private:
    virtual void sendPacket(uint8_t *packet, uint8_t packetSize) override;
    void onConnect(BLEServer* pServer) override;
    void onDisconnect(BLEServer* pServer) override;

    void (*onConnectCallback)() = nullptr;
    void (*onDisconnectCallback)() = nullptr;
    BLECharacteristic* pCharacteristic = nullptr;
};


extern GLBLEMidiServerClass GLBLEMidiServer;

#endif