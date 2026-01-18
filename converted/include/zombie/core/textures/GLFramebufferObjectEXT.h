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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


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

 void glBindFramebuffer(int int0, int int1) {
 EXTFramebufferObject.glBindFramebufferEXT(int0, int1);
 }

 void glFramebufferTexture2D(int int0, int int1, int int2, int int3, int int4) {
 EXTFramebufferObject.glFramebufferTexture2DEXT(int0, int1, int2, int3, int4);
 }

 int glGenRenderbuffers() {
 return EXTFramebufferObject.glGenRenderbuffersEXT();
 }

 void glBindRenderbuffer(int int0, int int1) {
 EXTFramebufferObject.glBindRenderbufferEXT(int0, int1);
 }

 void glRenderbufferStorage(int int0, int int1, int int2, int int3) {
 EXTFramebufferObject.glRenderbufferStorageEXT(int0, int1, int2, int3);
 }

 void glFramebufferRenderbuffer(int int0, int int1, int int2, int int3) {
 EXTFramebufferObject.glFramebufferRenderbufferEXT(int0, int1, int2, int3);
 }

 int glCheckFramebufferStatus(int int0) {
 return EXTFramebufferObject.glCheckFramebufferStatusEXT(int0);
 }

 void glDeleteFramebuffers(int int0) {
 EXTFramebufferObject.glDeleteFramebuffersEXT(int0);
 }

 void glDeleteRenderbuffers(int int0) {
 EXTFramebufferObject.glDeleteRenderbuffersEXT(int0);
 }
}
} // namespace textures
} // namespace core
} // namespace zombie
