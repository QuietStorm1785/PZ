#ifndef ORG_LWJGL_GLFW_GLFWERRORCALLBACK_H
#define ORG_LWJGL_GLFW_GLFWERRORCALLBACK_H

namespace org::lwjgl::glfw {
class GLFWErrorCallback {
public:
 static GLFWErrorCallback createPrint(void* /*stream*/) { return GLFWErrorCallback(); }
};
}

#endif // ORG_LWJGL_GLFW_GLFWERRORCALLBACK_H
