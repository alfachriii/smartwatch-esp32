#include "WeatherService.hpp"


namespace Service {
  Weather::Weather(Core::EventBus *bus) : eventBus(bus) {
    this->weatherState = WeatherState::IDLE;
    this->wifiState = WifiState::DISCONNECTED;
  }

  void Weather::init() {
    eventBus->subscribe(Core::EventType::WIFI_CONNECTED, this, [this](void *data) {
      if(weatherState == WeatherState::WAIT_WIFI) {
        this->startFetchWifi();
      }
    });

    eventBus->subscribe(Core::EventType::WIFI_FAILED, this, [this](void *data) {
      if(weatherState == WeatherState::WAIT_WIFI) {
        this->weatherState = WeatherState::FAILED;

        // TODO = retry fetching
      }
    });

  }

  void Weather::reqFetchWifi() {
    if(wifiState == WifiState::CONNECTED) {
      this->startFetchWifi();
      return;
    }

    this->weatherState = WeatherState::WAIT_WIFI;
    eventBus->publish(Core::EventType::CONNECT_TO_WIFI);
  }

  void Weather::startFetchWifi() {
    this->weatherState = WeatherState::FETCHING;

    eventBus->publish(Core::EventType::WEATHER_FETCH_WIFI);
  }
}