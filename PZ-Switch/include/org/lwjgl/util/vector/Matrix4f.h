#ifndef ORG_LWJGL_UTIL_VECTOR_MATRIX4F_H
#define ORG_LWJGL_UTIL_VECTOR_MATRIX4F_H

namespace org { namespace lwjgl { namespace util { namespace vector {

class Matrix4f {
public:
 float m00=1, m01=0, m02=0, m03=0;
 float m10=0, m11=1, m12=0, m13=0;
 float m20=0, m21=0, m22=1, m23=0;
 float m30=0, m31=0, m32=0, m33=1;
};

}}}} // namespace org::lwjgl::util::vector

#endif // ORG_LWJGL_UTIL_VECTOR_MATRIX4F_H
