#include <string>
#include "com/evildevil/engines/bubble/texture/DDSurfaceDesc2.h"
#include "com/evildevil/engines/bubble/texture/DDPixelFormat.h"
#include <cstring>
#include <stdexcept>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {


// DDSurfaceDesc2 constructor implementation
DDSurfaceDesc2::DDSurfaceDesc2()
    : identifier(0L), size(0L), flags(0L), height(0L), width(0L), pitchOrLinearSize(0L), depth(0L), mipMapCount(0L), reserved(0L), reserved2(0) {
    pixelFormat = std::make_shared<DDPixelFormat>();
    caps2 = std::make_shared<DDSCaps2>();
}

void DDSurfaceDesc2::setIdentifier(long var1) {
    identifier = var1;
    createIdentifierString();
}

void DDSurfaceDesc2::createIdentifierString() {
    char buf[5] = {0};
    buf[0] = static_cast<char>(identifier & 0xFF);
    buf[1] = static_cast<char>((identifier >> 8) & 0xFF);
    buf[2] = static_cast<char>((identifier >> 16) & 0xFF);
    buf[3] = static_cast<char>((identifier >> 24) & 0xFF);
    identifierString = std::string(buf);
    if (identifierString != DDS_IDENTIFIER) {
        throw TextureFormatException("The DDS Identifier is wrong. Have to be \"DDS \"!");
    }
}

void DDSurfaceDesc2::setSize(long var1) {
    if (var1 != 124L) {
        throw TextureFormatException("Wrong DDSurfaceDesc2 size. DDSurfaceDesc2 size must be 124!");
    }
    size = var1;
}

void DDSurfaceDesc2::setFlags(long var1) {
    flags = var1;
    if ((var1 & 1L) != 1L || (var1 & 4096L) != 4096L || (var1 & 4L) != 4L || (var1 & 2L) != 2L) {
        throw TextureFormatException("One or more required flag bits are set wrong. Flags must include DDSD_CAPS, DDSD_PIXELFORMAT, DDSD_WIDTH, DDSD_HEIGHT");
    }
}

void DDSurfaceDesc2::setHeight(long var1) {
    height = (var1 < 0) ? -var1 : var1;
}

void DDSurfaceDesc2::setWidth(long var1) {
    width = var1;
}

void DDSurfaceDesc2::setPitchOrLinearSize(long var1) {
    pitchOrLinearSize = var1;
    // Optionally recalculate for compressed textures
    if (pitchOrLinearSize > 1000000L) {
        pitchOrLinearSize = ((width + 3L) / 4L) * ((height + 3L) / 4L) * 16L;
    }
}

void DDSurfaceDesc2::setDepth(long var1) {
    depth = var1;
}

void DDSurfaceDesc2::setMipMapCount(long var1) {
    mipMapCount = var1;
}

void DDSurfaceDesc2::setDDPixelFormat(std::shared_ptr<DDPixelFormat> var1) {
    if (!var1) {
        throw std::invalid_argument("DDPixelFormat can't be nullptr. DDSurfaceDesc2 needs a valid DDPixelFormat.");
    }
    pixelFormat = var1;
}

std::shared_ptr<DDPixelFormat> DDSurfaceDesc2::getDDPixelformat() {
    return pixelFormat;
}

void DDSurfaceDesc2::setDDSCaps2(std::shared_ptr<DDSCaps2> var1) {
    if (!var1) {
        throw std::invalid_argument("DDSCaps can't be nullptr. DDSurfaceDesc2 needs a valid DDSCaps2.");
    }
    caps2 = var1;
}

std::shared_ptr<DDSCaps2> DDSurfaceDesc2::getDDSCaps2() {
    return caps2;
}

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
