#pragma once
#include "org/lwjglx/LWJGLException.h"
#include "org/lwjglx/opengl/Display.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Rand.h"
#include "zombie/input/KeyboardState.h"
#include "zombie/input/MouseState.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace N3D {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class EngineTestbed {
public:
  static MouseState mouse = std::make_unique<MouseState>();
  static KeyboardState keyboard = std::make_unique<KeyboardState>();

  static void main(String[] var0) {
    Rand.init();

    try {
      GameWindow.InitDisplay();
    } catch (IOException iOException) {
      iOException.printStackTrace();
    } catch (LWJGLException lWJGLException) {
      lWJGLException.printStackTrace();
    }

    while (!Display.isCloseRequested()) {
      mouse.poll();
      keyboard.poll();
      Display.update(true);
    }
  }
}
} // namespace N3D
