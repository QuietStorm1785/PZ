#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "GLUSException.h"
// Use new SDL2/GLUS Display implementation
#include "org/lwjglx/opengl/Display.h"
#include "zombie/GameWindow.h"
#include "zombie/core/Rand.h"
#include "zombie/input/KeyboardState.h"
#include "zombie/input/MouseState.h"
#include <fstream>
#include <iostream>

namespace N3D {


class EngineTestbed {
public:
    static MouseState mouse = std::make_shared<MouseState>();
    static KeyboardState keyboard = std::make_shared<KeyboardState>();

    static void main(std::string[] var0) {
      Rand.init();

      try {
         GameWindow.InitDisplay();
      } catch (std::ios_base::failure& var2) {
         std::cerr << var2.what() << std::endl;
      } catch (GLUSException& var3) {
         std::cerr << var3.what() << std::endl;
      }

      while (!lwjglx::opengl::Display::isCloseRequested()) {
         mouse.poll();
         keyboard.poll();
         lwjglx::opengl::Display::update(true);
      }
   }
}
} // namespace N3D
