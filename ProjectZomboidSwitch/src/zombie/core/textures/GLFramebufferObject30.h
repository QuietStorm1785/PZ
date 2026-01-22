#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL30.h"

namespace zombie {
namespace core {
namespace textures {


class GLFramebufferObject30 {
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
    return 33305;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT() {
    return 36054;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT() {
    return 36055;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS() {
    return 0;
   }

    int GL_FRAMEBUFFER_INCOMPLETE_FORMATS() {
    return 0;
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
    return 36182;
   }

    int glGenFramebuffers() {
      return GL30.glGenFramebuffers();
   }

    void glBindFramebuffer(int var1, int var2) {
      GL30.glBindFramebuffer(var1, var2);
   }

    void glFramebufferTexture2D(int var1, int var2, int var3, int var4, int var5) {
      GL30.glFramebufferTexture2D(var1, var2, var3, var4, var5);
   }

    int glGenRenderbuffers() {
      return GL30.glGenRenderbuffers();
   }

    void glBindRenderbuffer(int var1, int var2) {
      GL30.glBindRenderbuffer(var1, var2);
   }

    void glRenderbufferStorage(int var1, int var2, int var3, int var4) {
      GL30.glRenderbufferStorage(var1, var2, var3, var4);
   }

    void glFramebufferRenderbuffer(int var1, int var2, int var3, int var4) {
      GL30.glFramebufferRenderbuffer(var1, var2, var3, var4);
   }

    int glCheckFramebufferStatus(int var1) {
      return GL30.glCheckFramebufferStatus(var1);
   }

    void glDeleteFramebuffers(int var1) {
      GL30.glDeleteFramebuffers(var1);
   }

    void glDeleteRenderbuffers(int var1) {
      GL30.glDeleteRenderbuffers(var1);
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
