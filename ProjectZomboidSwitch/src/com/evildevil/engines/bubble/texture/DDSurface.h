#pragma once
#include <string>
#include <memory>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class DDSurface {
public:
    virtual ~DDSurface() = default;
    static constexpr int DDSD_CAPS = 1;
    static constexpr int DDSD_HEIGHT = 2;
    static constexpr int DDSD_WIDTH = 4;
    static constexpr int DDSD_PITCH = 8;
    static constexpr int DDSD_PIXELFORMAT = 4096;
    static constexpr int DDSD_MIPMAPCOUNT = 131072;
    static constexpr int DDSD_LINEARSIZE = 524288;
    static constexpr int DDSD_DEPTH = 8388608;
    static constexpr int DDPF_APHAPIXES = 1;
    static constexpr int DDPF_FOURCC = 4;
    static constexpr int DDPF_RGB = 64;
    static constexpr int DDSCAPS_COMPLEX = 8;
    static constexpr int DDSCAPS_TEXTURE = 4096;
    static constexpr int DDSCAPS_MIPMAP = 4194304;
    static constexpr int DDSCAPS2_CUBEMAP = 512;
    static constexpr int DDSCAPS2_CUBEMAP_POSITVEX = 1024;
    static constexpr int DDSCAPS2_CUBEMAP_NEGATIVEX = 2048;
    static constexpr int DDSCAPS2_CUBEMAP_POSITIVEY = 4096;
    static constexpr int DDSCAPS2_CUBEMAP_NEGATIVEY = 8192;
    static constexpr int DDSCAPS2_CUBEMAP_POSITIVEZ = 16384;
    static constexpr int DDSCAPS2_CUBEMAP_NEGATIVEZ = 32768;
    static constexpr int DDSCAPS2_VOLUME = 2097152;
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
