#pragma once
#include <Arduino.h>
#include <NimBLEDevice.h>
#include "../core/EventBus.hpp"

namespace Service {
  namespace BLE {
    class ServerCallbacks: public NimBLEServerCallbacks {
      public:
        Core::EventBus *eventBus;
        bool *connectedFlag;
        bool  *needAdvertiseFlag;

        void onConnect(NimBLEServer *bleServer, NimBLEConnInfo &connInfo) override;
        void onDisconnect(NimBLEServer *bleServer, NimBLEConnInfo &connInfo, int reason) override;
        uint32_t onPassKeyDisplay() override;
        void onConfirmPassKey(NimBLEConnInfo &connInfo, uint32_t pass_key) override;
        void onAuthenticationComplete(NimBLEConnInfo &connInfo) override;
    };

    class CharacteristicCallbacks: public NimBLECharacteristicCallbacks {
      void onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo) override;
    };

    class Ble {
    public:
      Ble(Core::EventBus *bus);
      void begin();
      void stop();
      void bleSetup();
      void startAdvertising();
      void stopAdvertising();
      void handleConnect();
      void handleDisconnect();

    private:
      Core::EventBus *eventBus;
      static NimBLEServer *bleServer;

      ServerCallbacks serverCallbacks;
      NimBLEService *httpService = nullptr;
      NimBLECharacteristic *httpCmdChar = nullptr;
      NimBLECharacteristic *httpNotifyChar = nullptr;
      NimBLEAdvertising *bleAdvertising = nullptr;
      TaskHandle_t bleTaskHandle = nullptr;

      bool isConnected = false;
      bool needAdvertise = false;

      static void bleTaskEntry(void *pv);
      void bleTask(Ble *self);
    };
  }
}