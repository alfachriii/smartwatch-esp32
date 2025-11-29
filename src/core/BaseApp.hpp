#pragma once
#include <functional>
#include "../services/ButtonService.hpp"

namespace Core {
  class UIManager;
  class DisplayDriver;

  class BaseApp {
  public:
    virtual ~BaseApp() = default;

    virtual void render() = 0;
    virtual void onEnter() {}
    virtual void onExit() {}
    virtual void onButton(Service::ButtonPayload payload) {}
    void setUi(Core::UIManager *ui) {
        this->ui = ui;
    }
  protected:
    UIManager* ui = nullptr;
    DisplayDriver* display;
  };
}