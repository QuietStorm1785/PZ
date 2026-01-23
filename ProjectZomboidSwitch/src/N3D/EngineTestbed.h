#pragma once
#include "GraphicsWrapper/GraphicsExceptions.h"
#include "GraphicsWrapper/Display.h"
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
	static std::unique_ptr<MouseState> mouse;
	static std::unique_ptr<KeyboardState> keyboard;

	static void main(int argc, char* argv[]) {
		Rand::init();
		try {
			GameWindow::InitDisplay();
		} catch (const std::exception& e) {
			std::cerr << "Exception: " << e.what() << std::endl;
		}

		while (!Display::isCloseRequested()) {
			mouse->poll();
			keyboard->poll();
			Display::update(true);
		}
	}
};
} // namespace N3D
