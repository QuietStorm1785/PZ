#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Matrix4f.h"
#include <GL/glew.h>
#include "org/lwjglx/opengl/OpenGLException.h"
#include "org/lwjglx/opengl/Util.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace opengl {


class PZGLUtil {
public:
    static int test = 0;

    static void checkGLErrorThrow(const std::string& var0, Object... var1) {
    int var2 = GL11.glGetError();
      if (var2 != 0) {
         test++;
         throw OpenGLException(createErrorMessage(var2, var0, var1));
      }
   }

    static std::string createErrorMessage(int var0, const std::string& var1, Object... var2) {
    std::string var3 = System.lineSeparator();
      return "  GL Error code ("
         + var0
         + ") encountered."
         + var3
         + "  Error translation: "
         + createErrorMessage(var0)
         + var3
         + "  While performing: "
         + std::string.format(var1, var2);
   }

    static std::string createErrorMessage(int var0) {
    std::string var1 = Util.translateGLErrorString(var0);
      return var1 + " (" + var0 + ")";
   }

    static bool checkGLError(bool var0) {
      try {
         Util.checkGLError();
    return true;
      } catch (OpenGLException var2) {
         RenderThread.logGLException(var2, var0);
    return false;
      }
   }

    static void printGLState(PrintStream var0) {
    int var1 = GL11.glGetInteger(2979);
      var0.println("DEBUG: GL_MODELVIEW_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(2980);
      var0.println("DEBUG: GL_PROJECTION_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(2981);
      var0.println("DEBUG: GL_TEXTURE_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(2992);
      var0.println("DEBUG: GL_ATTRIB_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(2993);
      var0.println("DEBUG: GL_CLIENT_ATTRIB_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3381);
      var0.println("DEBUG: GL_MAX_ATTRIB_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3382);
      var0.println("DEBUG: GL_MAX_MODELVIEW_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3383);
      var0.println("DEBUG: GL_MAX_NAME_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3384);
      var0.println("DEBUG: GL_MAX_PROJECTION_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3385);
      var0.println("DEBUG: GL_MAX_TEXTURE_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3387);
      var0.println("DEBUG: GL_MAX_CLIENT_ATTRIB_STACK_DEPTH= " + var1);
      var1 = GL11.glGetInteger(3440);
      var0.println("DEBUG: GL_NAME_STACK_DEPTH= " + var1);
   }

    static void loadMatrix(Matrix4f var0) {
      var0.get(Model.m_staticReusableFloatBuffer);
      Model.m_staticReusableFloatBuffer.position(16);
      Model.m_staticReusableFloatBuffer.flip();
      GL11.glLoadMatrixf(Model.m_staticReusableFloatBuffer);
   }

    static void multMatrix(Matrix4f var0) {
      var0.get(Model.m_staticReusableFloatBuffer);
      Model.m_staticReusableFloatBuffer.position(16);
      Model.m_staticReusableFloatBuffer.flip();
      GL11.glMultMatrixf(Model.m_staticReusableFloatBuffer);
   }

    static void loadMatrix(int var0, Matrix4f var1) {
      GL11.glMatrixMode(var0);
      loadMatrix(var1);
   }

    static void multMatrix(int var0, Matrix4f var1) {
      GL11.glMatrixMode(var0);
      multMatrix(var1);
   }

    static void pushAndLoadMatrix(int var0, Matrix4f var1) {
      GL11.glMatrixMode(var0);
      GL11.glPushMatrix();
      loadMatrix(var1);
   }

    static void pushAndMultMatrix(int var0, Matrix4f var1) {
      GL11.glMatrixMode(var0);
      GL11.glPushMatrix();
      multMatrix(var1);
   }

    static void popMatrix(int var0) {
      GL11.glMatrixMode(var0);
      GL11.glPopMatrix();
   }
}
} // namespace opengl
} // namespace core
} // namespace zombie
