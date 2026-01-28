#pragma once
#include <stdexcept>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class DDSCaps2 {
public:
    long caps1;
    long caps2;
    long reserved;
    bool isVolumeTexture;

    DDSCaps2();
    void setCaps1(long var1);
    void setCaps2(long var1);
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
