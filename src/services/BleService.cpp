#include "BleService.hpp"
#include "config.h"
#include <NimBLEDevice.h>

namespace Service {
  namespace BLE {
    NimBLEServer *Ble::bleServer = nullptr;

    void ServerCallbacks::onConnect(NimBLEServer *bleServer, NimBLEConnInfo &connInfo){
      eventBus->publish(Core::EventType::BLE_ON_CONNECT, (void*)&connInfo);
    }

    void ServerCallbacks::onDisconnect(NimBLEServer *bleServer, NimBLEConnInfo &connInfo, int reason) {
      eventBus->publish(Core::EventType::BLE_ON_DISCONNECT, nullptr);
    }

    uint32_t ServerCallbacks::onPassKeyDisplay() {
      uint32_t randomNumber = (esp_random() % 90000000) + 10000000;
      eventBus->publish(Core::EventType::BLE_ON_PASSKEY, (void*)&randomNumber);

      Serial.printf("[BLE SEC] passkey: %d", randomNumber);
      return randomNumber;
    }

    void ServerCallbacks::onConfirmPassKey(NimBLEConnInfo &connInfo, uint32_t pass_key) {

    }

    void ServerCallbacks::onAuthenticationComplete(NimBLEConnInfo &connInfo) {
      eventBus->publish(Core::EventType::BLE_ON_AUTH_COMP, nullptr);
      Serial.println("[BLE SEC] Auth Complete, Device Conntected.");
    }

    void CharacteristicCallbacks::onWrite(NimBLECharacteristic *pCharacteristic, NimBLEConnInfo &connInfo) {

    }


    Ble::Ble(Core::EventBus *bus): eventBus(bus) {
    }

    void Ble::bleSetup() {
      NimBLEDevice::init(DEVICE_NAME);
      Serial.println("Starting BLE Server...");

      NimBLEDevice::setSecurityAuth(true, true, true);
      NimBLEDevice::setSecurityIOCap(BLE_HS_IO_DISPLAY_ONLY);

      this->bleServer = NimBLEDevice::createServer();
      serverCallbacks.eventBus = this->eventBus;
      bleServer->setCallbacks(&serverCallbacks);

      this->httpService = bleServer->createService(HTTP_SERVICE_UUID);
      this->httpCmdChar = httpService->createCharacteristic(HTTP_CMD_CHAR_UUID, NIMBLE_PROPERTY::WRITE | NIMBLE_PROPERTY::WRITE_ENC);

      httpCmdChar->setCallbacks(new CharacteristicCallbacks());

      this->httpNotifyChar = httpService->createCharacteristic(HTTP_NOTIFY_CHAR_UUID, NIMBLE_PROPERTY::NOTIFY);

      httpService->start();

      this->bleAdvertising = NimBLEDevice::getAdvertising();
    }

    void Ble::begin() {
      xTaskCreatePinnedToCore(
        bleTaskEntry,
        "BLE_TASK",
        4096,
        this,
        5,
        &bleTaskHandle,
        0
      );
    }

    void Ble::bleTaskEntry(void *param) {
      Ble *self = static_cast<Ble*>(param);
      self->bleTask(self);
    }

    void Ble::bleTask(Ble* self) {
      bleSetup();
      
      eventBus->subscribe(Core::EventType::BLE_ON_CONNECT, [self](void *data){ self->handleConnect(data); });
      eventBus->subscribe(Core::EventType::BLE_ON_DISCONNECT, [self](void *data){ self->handleDisconnect(data); });
      eventBus->subscribe(Core::EventType::BLE_ON_AUTH_COMP, [self](void *data) { self->handleAuthComplete(data); });

      for (;;) {

        vTaskDelay(50 / portTICK_PERIOD_MS);
      }
    }

    void Ble::stop() {
      if (!bleTaskHandle) return;

      vTaskDelete(bleTaskHandle);
      this->bleTaskHandle = nullptr;
    }

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

    void Ble::handleConnect(void *data) {
      Serial.println("[BLE] Connect to device..");

      NimBLEConnInfo *connInfo = static_cast<NimBLEConnInfo *>(data);
      this->connectedDevice = connInfo->getConnHandle();
      this->stopAdvertising();
    }

    void Ble::handleDisconnect(void *data) {
      this->startAdvertising();
      this->connectedDevice = NULL;
      Serial.println("[BLE] Device Disconnected..");
    }
    
    void Ble::handleAuthComplete(void *data) {
      NimBLEConnInfo *connInfo = static_cast<NimBLEConnInfo *>(data);

      if(!connInfo->isEncrypted()) {
        bleServer->disconnect(connectedDevice);

        Serial.printf("[BLE SEC] Encrypt connection failed, Diconnect device..\n");
        return;
      }
    }
  }
}