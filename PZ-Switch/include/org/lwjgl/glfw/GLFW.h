#pragma once

namespace org {
namespace lwjgl {
namespace glfw {

class GLFW {
public:
 static const int KEY_ESCAPE = 256;
 static const int KEY_ENTER = 257;
 static const int KEY_SPACE = 32;
 static const int KEY_A = 65;
 static const int KEY_D = 68;
 static const int KEY_W = 87;
 static const int KEY_S = 83;
 
 static const int PRESS = 1;
 static const int RELEASE = 0;
 
 static bool glfwWindowShouldClose(void* window);
 static void glfwPollEvents();
 static void glfwSwapBuffers(void* window);
};

} // namespace glfw
} // namespace lwjgl
} // namespace org
