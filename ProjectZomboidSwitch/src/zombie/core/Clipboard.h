#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/glfw/GLFW.h"
#include "org/lwjgl/glfw/GLFWErrorCallback.h"

namespace zombie {
namespace core {


class Clipboard {
public:
    static Thread MainThread = nullptr;
    static std::string PreviousKnownValue = nullptr;
    static std::string DelaySetMainThread = nullptr;

    static void initMainThread() {
      MainThread = Thread.currentThread();
      PreviousKnownValue = getClipboard();
   }

    static void rememberCurrentValue() {
      if (Thread.currentThread() == MainThread) {
    GLFWErrorCallback var0 = GLFW.glfwSetErrorCallback(nullptr);

         try {
            PreviousKnownValue = new std::string(GLFW.glfwGetClipboardString(0L));
         } catch (Throwable var5) {
            PreviousKnownValue = "";
         } finally {
            GLFW.glfwSetErrorCallback(var0);
         }
      }
   }

   public static /* synchronized - TODO: add std::mutex */ std::string getClipboard() {
      if (Thread.currentThread() == MainThread) {
    GLFWErrorCallback var0 = GLFW.glfwSetErrorCallback(nullptr);

    std::string var2;
         try {
    return PreviousKnownValue = new std::string(GLFW.glfwGetClipboardString(0L));
         } catch (Throwable var6) {
            PreviousKnownValue = "";
            var2 = "";
         } finally {
            GLFW.glfwSetErrorCallback(var0);
         }

    return var2;
      } else {
    return PreviousKnownValue;
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void setClipboard(std::string var0) {
      PreviousKnownValue = var0;
      if (Thread.currentThread() == MainThread) {
         GLFW.glfwSetClipboardString(0L, var0);
      } else {
         DelaySetMainThread = var0;
      }
   }

   public static /* synchronized - TODO: add std::mutex */ void updateMainThread() {
      if (DelaySetMainThread != nullptr) {
         setClipboard(DelaySetMainThread);
         DelaySetMainThread = nullptr;
      }
   }
}
} // namespace core
} // namespace zombie
