#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/EXTFramebufferObject.h"

namespace zombie {
namespace core {
namespace textures {


class GLFramebufferObjectEXT {
public:
    int GL_FRAMEBUFFER() {
    return 36160;
   }

    int GL_RENDERBUFFER() {
    return 36161;
   }

    int GL_COLOR_ATTACHMENT0() {
    return 36064;
   }

    int GL_DEPTH_ATTACHMENT() {
    return 36096;
   }

    int GL_STENCIL_ATTACHMENT() {
    return 36128;
   }

    int GL_DEPTH_STENCIL() {
    return 34041;
   }

    int GL_DEPTH24_STENCIL8() {
    return 35056;
   }

    int GL_FRAMEBUFFER_COMPLETE() {
    return 36053;
   }

    int GL_FRAMEBUFFER_UNDEFINED() {
    return 0;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT() {
    return 36054;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT() {
    return 36055;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS() {
    return 36057;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_FORMATS() {
    return 36058;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER() {
    return 36059;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER() {
    return 36060;
   }

    int GL_FRAMEBUFFER_UNSUPPORTED() {
    return 36061;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE() {
    return 0;
   }

    int glGenFramebuffers() {
      return EXTFramebufferObject.glGenFramebuffersEXT();
   }

    void glBindFramebuffer(int var1, int var2) {
      EXTFramebufferObject.glBindFramebufferEXT(var1, var2);
   }

    void glFramebufferTexture2D(int var1, int var2, int var3, int var4, int var5) {
      EXTFramebufferObject.glFramebufferTexture2DEXT(var1, var2, var3, var4, var5);
   }

    int glGenRenderbuffers() {
      return EXTFramebufferObject.glGenRenderbuffersEXT();
   }

    void glBindRenderbuffer(int var1, int var2) {
      EXTFramebufferObject.glBindRenderbufferEXT(var1, var2);
   }

    void glRenderbufferStorage(int var1, int var2, int var3, int var4) {
      EXTFramebufferObject.glRenderbufferStorageEXT(var1, var2, var3, var4);
   }

    void glFramebufferRenderbuffer(int var1, int var2, int var3, int var4) {
      EXTFramebufferObject.glFramebufferRenderbufferEXT(var1, var2, var3, var4);
   }

    int glCheckFramebufferStatus(int var1) {
      return EXTFramebufferObject.glCheckFramebufferStatusEXT(var1);
   }

    void glDeleteFramebuffers(int var1) {
      EXTFramebufferObject.glDeleteFramebuffersEXT(var1);
   }

    void glDeleteRenderbuffers(int var1) {
      EXTFramebufferObject.glDeleteRenderbuffersEXT(var1);
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
