#ifndef ORG_LWJGL_OPENGL_EXTFRAMEBUFFEROBJECT_H
#define ORG_LWJGL_OPENGL_EXTFRAMEBUFFEROBJECT_H

namespace org { namespace lwjgl { namespace opengl {

class EXTFramebufferObject {
public:
 static const int GL_FRAMEBUFFER_EXT = 0x8D40;
 static const int GL_RENDERBUFFER_EXT = 0x8D41;
 static const int GL_COLOR_ATTACHMENT0_EXT = 0x8CE0;
 static const int GL_DEPTH_ATTACHMENT_EXT = 0x8D00;
 static const int GL_STENCIL_ATTACHMENT_EXT = 0x8D20;
};

}}} // namespace org::lwjgl::opengl

#endif // ORG_LWJGL_OPENGL_EXTFRAMEBUFFEROBJECT_H
