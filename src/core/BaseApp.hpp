#pragma once
#include <functional>
#include "../services/ButtonService.hpp"
#include "../ui/UiButton.hpp"


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


    Ui::UIButton *uiButtons[5];
    size_t selectedIndex = 0;
    size_t uiButtonCount = 0;
  };
}