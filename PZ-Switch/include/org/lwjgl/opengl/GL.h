#pragma once

namespace org {
namespace lwjgl {
namespace opengl {

class GL {
public:
 static void glClear(int mask);
 static void glClearColor(float r, float g, float b, float a);
 static void glViewport(int x, int y, int width, int height);
 static void glEnable(int cap);
 static void glDisable(int cap);
 
 static const int GL_COLOR_BUFFER_BIT = 0x4000;
 static const int GL_DEPTH_BUFFER_BIT = 0x0100;
 static const int GL_DEPTH_TEST = 0x0B71;
 static const int GL_BLEND = 0x0BE2;
};

} // namespace opengl
} // namespace lwjgl
} // namespace org
