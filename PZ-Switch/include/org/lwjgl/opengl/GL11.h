#pragma once

namespace org {
namespace lwjgl {
namespace opengl {

class GL11 {
public:
 static void glClear(int mask);
 static void glClearColor(float r, float g, float b, float a);
 static void glViewport(int x, int y, int width, int height);
 static void glEnable(int cap);
 static void glDisable(int cap);
 static void glDrawArrays(int mode, int first, int count);
 static void glBindTexture(int target, int texture);
 
 static const int GL_TRIANGLES = 0x0004;
 static const int GL_QUADS = 0x0007;
 static const int GL_COLOR_BUFFER_BIT = 0x4000;
 static const int GL_DEPTH_TEST = 0x0B71;
 static const int GL_BLEND = 0x0BE2;
 static const int GL_TEXTURE_2D = 0x0DE1;
};

} // namespace opengl
} // namespace lwjgl
} // namespace org
