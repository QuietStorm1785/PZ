#ifndef ORG_LWJGL_UTIL_GLU_GLU_H
#define ORG_LWJGL_UTIL_GLU_GLU_H

namespace org::lwjgl::util::glu {

class GLU {
public:
 static void gluOrtho2D(double /*left*/, double /*right*/, double /*bottom*/, double /*top*/) {}
 static void gluPerspective(double /*fovy*/, double /*aspect*/, double /*zNear*/, double /*zFar*/) {}
 static const char* gluErrorString(int /*err*/) { return "GLU_OK"; }
};

} // namespace org::lwjgl::util::glu

#endif // ORG_LWJGL_UTIL_GLU_GLU_H
