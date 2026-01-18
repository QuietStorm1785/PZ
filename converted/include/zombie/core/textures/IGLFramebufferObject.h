#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace textures {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class IGLFramebufferObject {
public:
 virtual ~IGLFramebufferObject() = default;
 int GL_FRAMEBUFFER();

 int GL_RENDERBUFFER();

 int GL_COLOR_ATTACHMENT0();

 int GL_DEPTH_ATTACHMENT();

 int GL_STENCIL_ATTACHMENT();

 int GL_DEPTH_STENCIL();

 int GL_DEPTH24_STENCIL8();

 int GL_FRAMEBUFFER_COMPLETE();

 int GL_FRAMEBUFFER_UNDEFINED();

 int GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT();

 int GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT();

 int GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS();

 int GL_FRAMEBUFFER_INCOMPLETE_FORMATS();

 int GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER();

 int GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER();

 int GL_FRAMEBUFFER_UNSUPPORTED();

 int GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE();

 int glGenFramebuffers();

 void glBindFramebuffer(int target, int framebuffer);

 void glFramebufferTexture2D(int target, int attachment, int textarget, int texture, int level);

 int glGenRenderbuffers();

 void glBindRenderbuffer(int target, int renderbuffer);

 void glRenderbufferStorage(int target, int internalformat, int width, int height);

 void glFramebufferRenderbuffer(int target, int attachment, int renderbuffertarget, int renderbuffer);

 int glCheckFramebufferStatus(int target);

 void glDeleteFramebuffers(int renderbuffer);

 void glDeleteRenderbuffers(int renderbuffer);
}
} // namespace textures
} // namespace core
} // namespace zombie
