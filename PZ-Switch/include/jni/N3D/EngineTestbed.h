#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/opengl/Display.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Rand.h"
#include "zombie/input/KeyboardState.h"
#include "zombie/input/MouseState.h"
#include <fstream>
#include <iostream>

namespace N3D {


class EngineTestbed {
:
    static MouseState mouse = new MouseState();
    static KeyboardState keyboard = new KeyboardState();

    static void main(String[] var0) {
      Rand.init();

      try {
         GameWindow.InitDisplay();
      } catch (IOException var2) {
         var2.printStackTrace();
      } catch (LWJGLException var3) {
         var3.printStackTrace();
      }

      while (!Display.isCloseRequested()) {
         mouse.poll();
         keyboard.poll();
         Display.update(true);
      }
   }
}
} // namespace N3D
