#ifndef ORG_LWJGL_OPENGL_GL32_H
#define ORG_LWJGL_OPENGL_GL32_H

namespace org::lwjgl::opengl {

class GL32 {
public:
 // OpenGL 3.2 Core Profile constants
 
 // Blend modes
 static const int GL_BLEND = 0x0BE2;
 static const int GL_BLEND_COLOR = 0x8005;
 static const int GL_BLEND_DST_ALPHA = 0x80CA;
 static const int GL_BLEND_DST_RGB = 0x80C8;
 static const int GL_BLEND_EQUATION = 0x8009;
 static const int GL_BLEND_EQUATION_ALPHA = 0x883D;
 static const int GL_BLEND_EQUATION_RGB = 0x8009;
 static const int GL_BLEND_SRC_ALPHA = 0x80CB;
 static const int GL_BLEND_SRC_RGB = 0x80C9;
 
 // Clear buffers
 static const int GL_COLOR_BUFFER_BIT = 0x00004000;
 static const int GL_DEPTH_BUFFER_BIT = 0x00000100;
 static const int GL_STENCIL_BUFFER_BIT = 0x00000400;
 
 // Texture parameters
 static const int GL_TEXTURE_MAG_FILTER = 0x2800;
 static const int GL_TEXTURE_MIN_FILTER = 0x2801;
 static const int GL_TEXTURE_WRAP_S = 0x2802;
 static const int GL_TEXTURE_WRAP_T = 0x2803;
 
 // Filter modes
 static const int GL_NEAREST = 0x2600;
 static const int GL_LINEAR = 0x2601;
 static const int GL_LINEAR_MIPMAP_LINEAR = 0x2703;
 
 // Wrap modes
 static const int GL_REPEAT = 0x2901;
 static const int GL_CLAMP_TO_EDGE = 0x812F;
 static const int GL_MIRRORED_REPEAT = 0x8370;
 
 // Buffer objects
 static const int GL_ARRAY_BUFFER = 0x8892;
 static const int GL_ELEMENT_ARRAY_BUFFER = 0x8893;
 static const int GL_UNIFORM_BUFFER = 0x8A11;
 static const int GL_COPY_READ_BUFFER = 0x8F36;
 static const int GL_COPY_WRITE_BUFFER = 0x8F37;
 
 static const int GL_STATIC_DRAW = 0x88E4;
 static const int GL_DYNAMIC_DRAW = 0x88E8;
 static const int GL_STREAM_DRAW = 0x88E0;
 
 // Vertex attributes
 static const int GL_VERTEX_ATTRIB_ARRAY_ENABLED = 0x8622;
 static const int GL_VERTEX_ATTRIB_ARRAY_SIZE = 0x8623;
 static const int GL_VERTEX_ATTRIB_ARRAY_STRIDE = 0x8624;
 static const int GL_VERTEX_ATTRIB_ARRAY_TYPE = 0x8625;
 
 // Data types
 static const int GL_BYTE = 0x1400;
 static const int GL_UNSIGNED_BYTE = 0x1401;
 static const int GL_SHORT = 0x1402;
 static const int GL_UNSIGNED_SHORT = 0x1403;
 static const int GL_INT = 0x1404;
 static const int GL_UNSIGNED_INT = 0x1405;
 static const int GL_FLOAT = 0x1406;
 static const int GL_DOUBLE = 0x140A;
 
 // Primitives
 static const int GL_POINTS = 0x0000;
 static const int GL_LINES = 0x0001;
 static const int GL_LINE_LOOP = 0x0002;
 static const int GL_LINE_STRIP = 0x0003;
 static const int GL_TRIANGLES = 0x0004;
 static const int GL_TRIANGLE_STRIP = 0x0005;
 static const int GL_TRIANGLE_FAN = 0x0006;
 
 // Texture target
 static const int GL_TEXTURE_2D = 0x0DE1;
 static const int GL_TEXTURE_CUBE_MAP = 0x8513;
 static const int GL_TEXTURE_1D = 0x0DE0;
 static const int GL_TEXTURE_3D = 0x806F;
 
 // Texture format
 static const int GL_ALPHA = 0x1906;
 static const int GL_RGB = 0x1907;
 static const int GL_RGBA = 0x1908;
 static const int GL_LUMINANCE = 0x1909;
 
 // Shader types
 static const int GL_VERTEX_SHADER = 0x8B31;
 static const int GL_FRAGMENT_SHADER = 0x8B30;
 static const int GL_GEOMETRY_SHADER = 0x8DD9;
 
 // Error codes
 static const int GL_NO_ERROR = 0;
 static const int GL_INVALID_ENUM = 0x0500;
 static const int GL_INVALID_VALUE = 0x0501;
 static const int GL_INVALID_OPERATION = 0x0502;
 static const int GL_OUT_OF_MEMORY = 0x0505;
 
 // Depth testing
 static const int GL_DEPTH_TEST = 0x0B71;
 static const int GL_LESS = 0x0201;
 static const int GL_EQUAL = 0x0202;
 static const int GL_LEQUAL = 0x0203;
 static const int GL_GREATER = 0x0204;
 static const int GL_GEQUAL = 0x0206;
 static const int GL_NOTEQUAL = 0x0205;
 static const int GL_ALWAYS = 0x0207;
 static const int GL_NEVER = 0x0200;
 
 // Culling
 static const int GL_CULL_FACE = 0x0B44;
 static const int GL_FRONT = 0x0404;
 static const int GL_BACK = 0x0405;
 static const int GL_FRONT_AND_BACK = 0x0408;
 
 // Polygon mode
 static const int GL_POLYGON_MODE = 0x0B40;
 static const int GL_POINT = 0x1B00;
 static const int GL_LINE = 0x1B01;
 static const int GL_FILL = 0x1B02;
 
 // Framebuffer objects
 static const int GL_FRAMEBUFFER = 0x8D40;
 static const int GL_RENDERBUFFER = 0x8D41;
 static const int GL_COLOR_ATTACHMENT0 = 0x8CE0;
 static const int GL_DEPTH_ATTACHMENT = 0x8D00;
 static const int GL_STENCIL_ATTACHMENT = 0x8D20;
 
 // Sync objects
 static const int GL_SYNC_GPU_COMMANDS_COMPLETE = 0x9117;
};

} // namespace org::lwjgl::opengl

#endif // ORG_LWJGL_OPENGL_GL32_H
