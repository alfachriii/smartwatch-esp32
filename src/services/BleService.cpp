#include "BleService.hpp"
#include "config.h"
#include <NimBLEDevice.h>

namespace Service {
  namespace BLE {
    void ServerCallbacks::onConnect(NimBLEServer* bleServer, NimBLEConnInfo &connInfo){
    };

    uint32_t ServerCallbacks::onPassKeyDisplay() {
      uint32_t randomNumber = (esp_random() % 90000000) + 10000000;

      Serial.printf("[BLE SEC] passkey: %d", randomNumber);
      return randomNumber;
    }

    Ble::Ble(NimBLEServer* server): bleServer(server) {};

    void Ble::init() {
      NimBLEDevice::init(DEVICE_NAME);
      Serial.println("Starting BLE Server...");

      NimBLEDevice::setSecurityAuth(true, true, true);
      NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);

      this->bleServer = NimBLEDevice::createServer();
      bleServer->setCallbacks(new ServerCallbacks());

      this->httpService = bleServer->createService(HTTP_SERVICE_UUID);
      this->httpCmdChar = httpService->createCharacteristic(HTTP_CMD_CHAR_UUID, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC);

      httpCmdChar->setCallbacks(new CharacteriscticCallbacks());

      this->httpNotifyChar = httpService->createCharacteristic(HTTP_NOTIFY_CHAR_UUID, NIMBLE_PROPERTY::NOTIFY);

      httpService->start();

      this->bleAdvertising = NimBLEDevice::getAdvertising();
    };

    void Ble::startAdvertising() {
      bleAdvertising->addServiceUUID(httpService->getUUID());
      bleAdvertising->enableScanResponse(true);
      bleAdvertising->setName(DEVICE_NAME);
      bleAdvertising->start();

      Serial.println("[BLE] Start Advertising...");
    }

    void Ble::stopAdvertising() {
      bleAdvertising->stop();
      Serial.println("[BLE] Stop Advertising...");
    }
  }
}