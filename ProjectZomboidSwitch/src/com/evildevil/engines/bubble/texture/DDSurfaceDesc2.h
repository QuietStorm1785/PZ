#pragma once
#include <string>
#include <memory>
#include "com/evildevil/engines/bubble/texture/DDPixelFormat.h"
#include "com/evildevil/engines/bubble/texture/DDSCaps2.h"
#include "com/evildevil/engines/bubble/texture/TextureFormatException.h"

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class DDSurfaceDesc2 {
public:
    static constexpr const char* DDS_IDENTIFIER = "DDS ";
    long identifier = 0L;
    std::string identifierString;
    long size = 0L;
    long flags = 0L;
    long height = 0L;
    long width = 0L;
    long pitchOrLinearSize = 0L;
    long depth = 0L;
    long mipMapCount = 0L;
    long reserved = 0L;
    std::shared_ptr<DDPixelFormat> pixelFormat;
    std::shared_ptr<DDSCaps2> caps2;
    int reserved2 = 0;

    DDSurfaceDesc2();
    void setIdentifier(long var1);
    void createIdentifierString();
    void setSize(long var1);
    void setFlags(long var1);
    void setHeight(long var1);
    void setWidth(long var1);
    void setPitchOrLinearSize(long var1);
    void setDepth(long var1);
    void setMipMapCount(long var1);
    void setDDPixelFormat(std::shared_ptr<DDPixelFormat> var1);
    std::shared_ptr<DDPixelFormat> getDDPixelformat();
    void setDDSCaps2(std::shared_ptr<DDSCaps2> var1);
    std::shared_ptr<DDSCaps2> getDDSCaps2();
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
