#pragma once
#include <Arduino.h>
#include <NimBLEDevice.h>

namespace Service {
  namespace BLE {
    class ServerCallbacks: public NimBLEServerCallbacks {
      void onConnect(NimBLEServer* bleServer, NimBLEConnInfo &connInfo) override;
      void onDisconnect(NimBLEServer *bleServer, NimBLEConnInfo &connInfo, int reason) override;
      uint32_t onPassKeyDisplay() override;
      void onConfirmPassKey(NimBLEConnInfo &connInfo, uint32_t pass_key) override;
      void onAuthenticationComplete(NimBLEConnInfo& connInfo) override;
    };

    class CharacteriscticCallbacks: public NimBLECharacteristicCallbacks {
      void onWrite(NimBLECharacteristic* pCharacteristic, NimBLEConnInfo& connInfo) override;
    };

    class Ble
    {
    public:
      Ble(NimBLEServer *server);
      void init();
      void startAdvertising();
      void stopAdvertising();

    private:
      NimBLEServer *bleServer;
      NimBLEService *httpService = nullptr;
      NimBLECharacteristic *httpCmdChar = nullptr;
      NimBLECharacteristic *httpNotifyChar = nullptr;
      NimBLEAdvertising *bleAdvertising = nullptr;
    };
  }
}