#ifndef ORG_LWJGL_OPENGL_ARBFRAMEBUFFEROBJECT_H
#define ORG_LWJGL_OPENGL_ARBFRAMEBUFFEROBJECT_H

namespace org { namespace lwjgl { namespace opengl {

class ARBFramebufferObject {
public:
 static const int GL_FRAMEBUFFER = 0x8D40;
 static const int GL_RENDERBUFFER = 0x8D41;
 static const int GL_COLOR_ATTACHMENT0 = 0x8CE0;
 static const int GL_DEPTH_ATTACHMENT = 0x8D00;
 static const int GL_STENCIL_ATTACHMENT = 0x8D20;
};

}}} // namespace org::lwjgl::opengl

#endif // ORG_LWJGL_OPENGL_ARBFRAMEBUFFEROBJECT_H
