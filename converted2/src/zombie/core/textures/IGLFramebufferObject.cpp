#include "zombie/core/textures/IGLFramebufferObject.h"

namespace zombie {
namespace core {
namespace textures {

int IGLFramebufferObject::GL_FRAMEBUFFER() {
  // TODO: Implement GL_FRAMEBUFFER
  return 0;
}

int IGLFramebufferObject::GL_RENDERBUFFER() {
  // TODO: Implement GL_RENDERBUFFER
  return 0;
}

int IGLFramebufferObject::GL_COLOR_ATTACHMENT0() {
  // TODO: Implement GL_COLOR_ATTACHMENT0
  return 0;
}

int IGLFramebufferObject::GL_DEPTH_ATTACHMENT() {
  // TODO: Implement GL_DEPTH_ATTACHMENT
  return 0;
}

int IGLFramebufferObject::GL_STENCIL_ATTACHMENT() {
  // TODO: Implement GL_STENCIL_ATTACHMENT
  return 0;
}

int IGLFramebufferObject::GL_DEPTH_STENCIL() {
  // TODO: Implement GL_DEPTH_STENCIL
  return 0;
}

int IGLFramebufferObject::GL_DEPTH24_STENCIL8() {
  // TODO: Implement GL_DEPTH24_STENCIL8
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_COMPLETE() {
  // TODO: Implement GL_FRAMEBUFFER_COMPLETE
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_UNDEFINED() {
  // TODO: Implement GL_FRAMEBUFFER_UNDEFINED
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_FORMATS() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_FORMATS
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_UNSUPPORTED() {
  // TODO: Implement GL_FRAMEBUFFER_UNSUPPORTED
  return 0;
}

int IGLFramebufferObject::GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE() {
  // TODO: Implement GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE
  return 0;
}

int IGLFramebufferObject::glGenFramebuffers() {
  // TODO: Implement glGenFramebuffers
  return 0;
}

void IGLFramebufferObject::glBindFramebuffer(int target, int framebuffer) {
  // TODO: Implement glBindFramebuffer
}

void IGLFramebufferObject::glFramebufferTexture2D(int target, int attachment,
                                                  int textarget, int texture,
                                                  int level) {
  // TODO: Implement glFramebufferTexture2D
}

int IGLFramebufferObject::glGenRenderbuffers() {
  // TODO: Implement glGenRenderbuffers
  return 0;
}

void IGLFramebufferObject::glBindRenderbuffer(int target, int renderbuffer) {
  // TODO: Implement glBindRenderbuffer
}

void IGLFramebufferObject::glRenderbufferStorage(int target, int internalformat,
                                                 int width, int height) {
  // TODO: Implement glRenderbufferStorage
}

void IGLFramebufferObject::glFramebufferRenderbuffer(int target, int attachment,
                                                     int renderbuffertarget,
                                                     int renderbuffer) {
  // TODO: Implement glFramebufferRenderbuffer
}

int IGLFramebufferObject::glCheckFramebufferStatus(int target) {
  // TODO: Implement glCheckFramebufferStatus
  return 0;
}

void IGLFramebufferObject::glDeleteFramebuffers(int renderbuffer) {
  // TODO: Implement glDeleteFramebuffers
}

void IGLFramebufferObject::glDeleteRenderbuffers(int renderbuffer) {
  // TODO: Implement glDeleteRenderbuffers
}

} // namespace textures
} // namespace core
} // namespace zombie
