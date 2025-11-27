#pragma once
#include <functional>

namespace Core {
  class BaseApp {
  public:
      virtual ~BaseApp() {}
  
      virtual void onEnter() {}
      virtual void onExit() {} 
      virtual void render() = 0;
      virtual void onEvent(EventType type, void* data) {} 
  };
}