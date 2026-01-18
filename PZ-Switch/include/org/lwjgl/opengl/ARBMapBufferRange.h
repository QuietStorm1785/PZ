#pragma once
namespace org { namespace lwjgl { namespace opengl {
class ARBMapBufferRange {
public:
    static constexpr int GL_MAP_READ_BIT = 0x0001;
    static constexpr int GL_MAP_WRITE_BIT = 0x0002;
    static constexpr int GL_MAP_PERSISTENT_BIT = 0x0040;
    static constexpr int GL_MAP_COHERENT_BIT = 0x0080;
    static constexpr int GL_DYNAMIC_STORAGE_BIT = 0x0100;
    static constexpr int GL_CLIENT_STORAGE_BIT = 0x0200;
};
}}}
