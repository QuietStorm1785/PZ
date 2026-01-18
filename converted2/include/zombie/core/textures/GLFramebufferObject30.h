#pragma once
#include "org/lwjgl/opengl/GL30.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLFramebufferObject30 {
public:
  int GL_FRAMEBUFFER() { return 36160; }

  int GL_RENDERBUFFER() { return 36161; }

  int GL_COLOR_ATTACHMENT0() { return 36064; }

  int GL_DEPTH_ATTACHMENT() { return 36096; }

  int GL_STENCIL_ATTACHMENT() { return 36128; }

  int GL_DEPTH_STENCIL() { return 34041; }

  int GL_DEPTH24_STENCIL8() { return 35056; }

  int GL_FRAMEBUFFER_COMPLETE() { return 36053; }

  int GL_FRAMEBUFFER_UNDEFINED() { return 33305; }

  int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT() { return 36054; }

  int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT() { return 36055; }

  int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS() { return 0; }

  int GL_FRAMEBUFFER_INCOMPLETE_FORMATS() { return 0; }

  int GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER() { return 36059; }

  int GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER() { return 36060; }

  int GL_FRAMEBUFFER_UNSUPPORTED() { return 36061; }

  int GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE() { return 36182; }

  int glGenFramebuffers() { return GL30.glGenFramebuffers(); }

  void glBindFramebuffer(int int0, int int1) {
    GL30.glBindFramebuffer(int0, int1);
  }

  void glFramebufferTexture2D(int int0, int int1, int int2, int int3,
                              int int4) {
    GL30.glFramebufferTexture2D(int0, int1, int2, int3, int4);
  }

  int glGenRenderbuffers() { return GL30.glGenRenderbuffers(); }

  void glBindRenderbuffer(int int0, int int1) {
    GL30.glBindRenderbuffer(int0, int1);
  }

  void glRenderbufferStorage(int int0, int int1, int int2, int int3) {
    GL30.glRenderbufferStorage(int0, int1, int2, int3);
  }

  void glFramebufferRenderbuffer(int int0, int int1, int int2, int int3) {
    GL30.glFramebufferRenderbuffer(int0, int1, int2, int3);
  }

  int glCheckFramebufferStatus(int int0) {
    return GL30.glCheckFramebufferStatus(int0);
  }

  void glDeleteFramebuffers(int int0) { GL30.glDeleteFramebuffers(int0); }

  void glDeleteRenderbuffers(int int0) { GL30.glDeleteRenderbuffers(int0); }
}
} // namespace textures
} // namespace core
} // namespace zombie
