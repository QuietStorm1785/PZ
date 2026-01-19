#pragma once
#include "org/lwjglx/util/glu/tessellation/GLUtessellatorImpl.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class GLU {
public:
 static const float PI = (float)Math.PI;
 static const int GLU_INVALID_ENUM = 100900;
 static const int GLU_INVALID_VALUE = 100901;
 static const int GLU_OUT_OF_MEMORY = 100902;
 static const int GLU_INCOMPATIBLE_GL_VERSION = 100903;
 static const int GLU_VERSION = 100800;
 static const int GLU_EXTENSIONS = 100801;
 static const bool GLU_TRUE = true;
 static const bool GLU_FALSE = false;
 static const int GLU_SMOOTH = 100000;
 static const int GLU_FLAT = 100001;
 static const int GLU_NONE = 100002;
 static const int GLU_POINT = 100010;
 static const int GLU_LINE = 100011;
 static const int GLU_FILL = 100012;
 static const int GLU_SILHOUETTE = 100013;
 static const int GLU_OUTSIDE = 100020;
 static const int GLU_INSIDE = 100021;
 static const double GLU_TESS_MAX_COORD = 1.0E150;
 static const double TESS_MAX_COORD = 1.0E150;
 static const int GLU_TESS_WINDING_RULE = 100140;
 static const int GLU_TESS_BOUNDARY_ONLY = 100141;
 static const int GLU_TESS_TOLERANCE = 100142;
 static const int GLU_TESS_WINDING_ODD = 100130;
 static const int GLU_TESS_WINDING_NONZERO = 100131;
 static const int GLU_TESS_WINDING_POSITIVE = 100132;
 static const int GLU_TESS_WINDING_NEGATIVE = 100133;
 static const int GLU_TESS_WINDING_ABS_GEQ_TWO = 100134;
 static const int GLU_TESS_BEGIN = 100100;
 static const int GLU_TESS_VERTEX = 100101;
 static const int GLU_TESS_END = 100102;
 static const int GLU_TESS_ERROR = 100103;
 static const int GLU_TESS_EDGE_FLAG = 100104;
 static const int GLU_TESS_COMBINE = 100105;
 static const int GLU_TESS_BEGIN_DATA = 100106;
 static const int GLU_TESS_VERTEX_DATA = 100107;
 static const int GLU_TESS_END_DATA = 100108;
 static const int GLU_TESS_ERROR_DATA = 100109;
 static const int GLU_TESS_EDGE_FLAG_DATA = 100110;
 static const int GLU_TESS_COMBINE_DATA = 100111;
 static const int GLU_TESS_ERROR1 = 100151;
 static const int GLU_TESS_ERROR2 = 100152;
 static const int GLU_TESS_ERROR3 = 100153;
 static const int GLU_TESS_ERROR4 = 100154;
 static const int GLU_TESS_ERROR5 = 100155;
 static const int GLU_TESS_ERROR6 = 100156;
 static const int GLU_TESS_ERROR7 = 100157;
 static const int GLU_TESS_ERROR8 = 100158;
 static const int GLU_TESS_MISSING_BEGIN_POLYGON = 100151;
 static const int GLU_TESS_MISSING_BEGIN_CONTOUR = 100152;
 static const int GLU_TESS_MISSING_END_POLYGON = 100153;
 static const int GLU_TESS_MISSING_END_CONTOUR = 100154;
 static const int GLU_TESS_COORD_TOO_LARGE = 100155;
 static const int GLU_TESS_NEED_COMBINE_CALLBACK = 100156;
 static const int GLU_AUTO_LOAD_MATRIX = 100200;
 static const int GLU_CULLING = 100201;
 static const int GLU_SAMPLING_TOLERANCE = 100203;
 static const int GLU_DISPLAY_MODE = 100204;
 static const int GLU_PARAMETRIC_TOLERANCE = 100202;
 static const int GLU_SAMPLING_METHOD = 100205;
 static const int GLU_U_STEP = 100206;
 static const int GLU_V_STEP = 100207;
 static const int GLU_PATH_LENGTH = 100215;
 static const int GLU_PARAMETRIC_ERROR = 100216;
 static const int GLU_DOMAIN_DISTANCE = 100217;
 static const int GLU_MAP1_TRIM_2 = 100210;
 static const int GLU_MAP1_TRIM_3 = 100211;
 static const int GLU_OUTLINE_POLYGON = 100240;
 static const int GLU_OUTLINE_PATCH = 100241;
 static const int GLU_NURBS_ERROR1 = 100251;
 static const int GLU_NURBS_ERROR2 = 100252;
 static const int GLU_NURBS_ERROR3 = 100253;
 static const int GLU_NURBS_ERROR4 = 100254;
 static const int GLU_NURBS_ERROR5 = 100255;
 static const int GLU_NURBS_ERROR6 = 100256;
 static const int GLU_NURBS_ERROR7 = 100257;
 static const int GLU_NURBS_ERROR8 = 100258;
 static const int GLU_NURBS_ERROR9 = 100259;
 static const int GLU_NURBS_ERROR10 = 100260;
 static const int GLU_NURBS_ERROR11 = 100261;
 static const int GLU_NURBS_ERROR12 = 100262;
 static const int GLU_NURBS_ERROR13 = 100263;
 static const int GLU_NURBS_ERROR14 = 100264;
 static const int GLU_NURBS_ERROR15 = 100265;
 static const int GLU_NURBS_ERROR16 = 100266;
 static const int GLU_NURBS_ERROR17 = 100267;
 static const int GLU_NURBS_ERROR18 = 100268;
 static const int GLU_NURBS_ERROR19 = 100269;
 static const int GLU_NURBS_ERROR20 = 100270;
 static const int GLU_NURBS_ERROR21 = 100271;
 static const int GLU_NURBS_ERROR22 = 100272;
 static const int GLU_NURBS_ERROR23 = 100273;
 static const int GLU_NURBS_ERROR24 = 100274;
 static const int GLU_NURBS_ERROR25 = 100275;
 static const int GLU_NURBS_ERROR26 = 100276;
 static const int GLU_NURBS_ERROR27 = 100277;
 static const int GLU_NURBS_ERROR28 = 100278;
 static const int GLU_NURBS_ERROR29 = 100279;
 static const int GLU_NURBS_ERROR30 = 100280;
 static const int GLU_NURBS_ERROR31 = 100281;
 static const int GLU_NURBS_ERROR32 = 100282;
 static const int GLU_NURBS_ERROR33 = 100283;
 static const int GLU_NURBS_ERROR34 = 100284;
 static const int GLU_NURBS_ERROR35 = 100285;
 static const int GLU_NURBS_ERROR36 = 100286;
 static const int GLU_NURBS_ERROR37 = 100287;
 static const int GLU_CW = 100120;
 static const int GLU_CCW = 100121;
 static const int GLU_INTERIOR = 100122;
 static const int GLU_EXTERIOR = 100123;
 static const int GLU_UNKNOWN = 100124;
 static const int GLU_BEGIN = 100100;
 static const int GLU_VERTEX = 100101;
 static const int GLU_END = 100102;
 static const int GLU_ERROR = 100103;
 static const int GLU_EDGE_FLAG = 100104;

 static void gluLookAt(float float0, float float1, float float2, float float3,
 float float4, float float5, float float6, float float7,
 float float8) {
 Project.gluLookAt(float0, float1, float2, float3, float4, float5, float6,
 float7, float8);
 }

 static void gluOrtho2D(float float0, float float1, float float2,
 float float3) {
 gluOrtho2D(float0, float1, float2, float3);
 }

 static void gluPerspective(float float0, float float1, float float2,
 float float3) {
 Project.gluPerspective(float0, float1, float2, float3);
 }

public
 static boolean gluProject(float float0, float float1, float float2,
 FloatBuffer floatBuffer0, FloatBuffer floatBuffer1,
 IntBuffer intBuffer, FloatBuffer floatBuffer2) {
 return Project.gluProject(float0, float1, float2, floatBuffer0,
 floatBuffer1, intBuffer, floatBuffer2);
 }

public
 static boolean gluUnProject(float float0, float float1, float float2,
 FloatBuffer floatBuffer0,
 FloatBuffer floatBuffer1, IntBuffer intBuffer,
 FloatBuffer floatBuffer2) {
 return Project.gluUnProject(float0, float1, float2, floatBuffer0,
 floatBuffer1, intBuffer, floatBuffer2);
 }

 static void gluPickMatrix(float float0, float float1, float float2,
 float float3, IntBuffer intBuffer) {
 Project.gluPickMatrix(float0, float1, float2, float3, intBuffer);
 }

 static std::string gluGetString(int int0) {
 return Registry.gluGetString(int0);
 }

 static bool gluCheckExtension(std::string_view string0,
 std::string_view string1) {
 return Registry.gluCheckExtension(string0, string1);
 }

 static int gluBuild2DMipmaps(int int0, int int1, int int2, int int3, int int4,
 int int5, ByteBuffer byteBuffer) {
 return MipMap.gluBuild2DMipmaps(int0, int1, int2, int3, int4, int5,
 byteBuffer);
 }

 static int gluScaleImage(int int0, int int1, int int2, int int3,
 ByteBuffer byteBuffer0, int int4, int int5, int int6,
 ByteBuffer byteBuffer1) {
 return MipMap.gluScaleImage(int0, int1, int2, int3, byteBuffer0, int4, int5,
 int6, byteBuffer1);
 }

 static std::string gluErrorString(int int0) {
 switch (int0) {
 case 100900:
 return "Invalid enum (glu)";
 case 100901:
 return "Invalid value (glu)";
 case 100902:
 return "Out of memory (glu)";
 default:
 return org.lwjglx.opengl.Util.translateGLErrorString(int0);
 }
 }

 static GLUtessellator gluNewTess() {
 return std::make_unique<GLUtessellatorImpl>();
 }
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
