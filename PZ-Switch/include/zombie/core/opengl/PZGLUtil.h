#pragma once
#include "org/joml/Matrix4f.h"
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjglx/opengl/OpenGLException.h"
#include "org/lwjglx/opengl/Util.h"
#include "zombie/core/skinnedmodel/model/Model.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZGLUtil {
public:
 static int test = 0;

 static void checkGLErrorThrow(std::string_view string, Object... objects) {
 int int0 = GL11.glGetError();
 if (int0 != 0) {
 test++;
 throw OpenGLException(createErrorMessage(int0, string, objects);
 }
 }

 static std::string createErrorMessage(int int0, std::string_view string1,
 Object... objects) {
 std::string string0 = System.lineSeparator();
 return " GL Error code (" + int0 + ") encountered." + string0 +
 " Error translation: " + createErrorMessage(int0) + string0 +
 " While performing: " + String.format(string1, objects);
 }

 static std::string createErrorMessage(int int0) {
 std::string string = Util.translateGLErrorString(int0);
 return string + " (" + int0 + ")";
 }

 static bool checkGLError(bool boolean0) {
 try {
 Util.checkGLError();
 return true;
 } catch (OpenGLException openGLException) {
 RenderThread.logGLException(openGLException, boolean0);
 return false;
 }
 }

 static void printGLState(PrintStream printStream) {
 int int0 = GL11.glGetInteger(2979);
 printStream.println("DEBUG: GL_MODELVIEW_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(2980);
 printStream.println("DEBUG: GL_PROJECTION_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(2981);
 printStream.println("DEBUG: GL_TEXTURE_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(2992);
 printStream.println("DEBUG: GL_ATTRIB_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(2993);
 printStream.println("DEBUG: GL_CLIENT_ATTRIB_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3381);
 printStream.println("DEBUG: GL_MAX_ATTRIB_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3382);
 printStream.println("DEBUG: GL_MAX_MODELVIEW_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3383);
 printStream.println("DEBUG: GL_MAX_NAME_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3384);
 printStream.println("DEBUG: GL_MAX_PROJECTION_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3385);
 printStream.println("DEBUG: GL_MAX_TEXTURE_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3387);
 printStream.println("DEBUG: GL_MAX_CLIENT_ATTRIB_STACK_DEPTH= " + int0);
 int0 = GL11.glGetInteger(3440);
 printStream.println("DEBUG: GL_NAME_STACK_DEPTH= " + int0);
 }

 static void loadMatrix(Matrix4f matrix4f) {
 matrix4f.get(Model.m_staticReusableFloatBuffer);
 Model.m_staticReusableFloatBuffer.position(16);
 Model.m_staticReusableFloatBuffer.flip();
 GL11.glLoadMatrixf(Model.m_staticReusableFloatBuffer);
 }

 static void multMatrix(Matrix4f matrix4f) {
 matrix4f.get(Model.m_staticReusableFloatBuffer);
 Model.m_staticReusableFloatBuffer.position(16);
 Model.m_staticReusableFloatBuffer.flip();
 GL11.glMultMatrixf(Model.m_staticReusableFloatBuffer);
 }

 static void loadMatrix(int int0, Matrix4f matrix4f) {
 GL11.glMatrixMode(int0);
 loadMatrix(matrix4f);
 }

 static void multMatrix(int int0, Matrix4f matrix4f) {
 GL11.glMatrixMode(int0);
 multMatrix(matrix4f);
 }

 static void pushAndLoadMatrix(int int0, Matrix4f matrix4f) {
 GL11.glMatrixMode(int0);
 GL11.glPushMatrix();
 loadMatrix(matrix4f);
 }

 static void pushAndMultMatrix(int int0, Matrix4f matrix4f) {
 GL11.glMatrixMode(int0);
 GL11.glPushMatrix();
 multMatrix(matrix4f);
 }

 static void popMatrix(int int0) {
 GL11.glMatrixMode(int0);
 GL11.glPopMatrix();
 }
}
} // namespace opengl
} // namespace core
} // namespace zombie
