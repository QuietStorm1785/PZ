#pragma once
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/glfw/GLFWErrorCallback.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Clipboard {
public:
  static Thread MainThread = null;
  static std::string PreviousKnownValue = null;
  static std::string DelaySetMainThread = null;

  static void initMainThread() {
    MainThread = Thread.currentThread();
    PreviousKnownValue = getClipboard();
  }

  static void rememberCurrentValue() {
    if (Thread.currentThread() == MainThread) {
      GLFWErrorCallback gLFWErrorCallback = GLFW.glfwSetErrorCallback(null);

      try {
        PreviousKnownValue = new String(GLFW.glfwGetClipboardString(0L));
      } catch (Throwable throwable) {
        PreviousKnownValue = "";
      } finally {
        GLFW.glfwSetErrorCallback(gLFWErrorCallback);
      }
    }
  }

public
  static synchronized String getClipboard() {
    if (Thread.currentThread() == MainThread) {
      GLFWErrorCallback gLFWErrorCallback = GLFW.glfwSetErrorCallback(null);

      std::string string;
      try {
        return PreviousKnownValue = new String(GLFW.glfwGetClipboardString(0L));
      } catch (Throwable throwable) {
        PreviousKnownValue = "";
        string = "";
      } finally {
        GLFW.glfwSetErrorCallback(gLFWErrorCallback);
      }

      return string;
    } else {
      return PreviousKnownValue;
    }
  }

public
  static synchronized void setClipboard(String str) {
    PreviousKnownValue = str;
    if (Thread.currentThread() == MainThread) {
      GLFW.glfwSetClipboardString(0L, str);
    } else {
      DelaySetMainThread = str;
    }
  }

public
  static synchronized void updateMainThread() {
    if (DelaySetMainThread != nullptr) {
      setClipboard(DelaySetMainThread);
      DelaySetMainThread = nullptr;
    }
  }
}
} // namespace core
} // namespace zombie
