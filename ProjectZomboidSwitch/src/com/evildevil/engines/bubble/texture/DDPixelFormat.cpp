#include "com/evildevil/engines/bubble/texture/DDPixelFormat.h"
#include "com/evildevil/engines/bubble/texture/TextureFormatException.h"


namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

DDPixelFormat::DDPixelFormat() : size(0L), flags(0L), fourCC(0L), fourCCString(""), rgbBitCount(0L), rBitMask(0L), gBitMask(0L), bBitMask(0L), rgbAlphaBitMask(0L), isCompressed(true) {}

void DDPixelFormat::setSize(long var1) {
    if (var1 != 32L) {
        throw TextureFormatException("Wrong DDPixelFormat size. DDPixelFormat size must be 32!");
    }
    size = var1;
}

void DDPixelFormat::setFlags(long var1) {
    flags = var1;
    if ((var1 & 64L) == 64L) {
        isCompressed = false;
    } else if ((var1 & 4L) == 4L) {
        isCompressed = true;
    }
}

void DDPixelFormat::setFourCC(long var1) {
    fourCC = var1;
    if (isCompressed) {
        createFourCCString();
    }
}

void DDPixelFormat::createFourCCString() {
    char buf[5] = {0};
    buf[0] = static_cast<char>(fourCC & 0xFF);
    buf[1] = static_cast<char>((fourCC >> 8) & 0xFF);
    buf[2] = static_cast<char>((fourCC >> 16) & 0xFF);
    buf[3] = static_cast<char>((fourCC >> 24) & 0xFF);
    fourCCString = std::string(buf);
}

std::string DDPixelFormat::getFourCCString() {
    return fourCCString;
}

void DDPixelFormat::setRGBBitCount(long var1) {
    rgbBitCount = var1;
}

void DDPixelFormat::setRBitMask(long var1) {
    rBitMask = var1;
}

void DDPixelFormat::setGBitMask(long var1) {
    gBitMask = var1;
}

void DDPixelFormat::setBBitMask(long var1) {
    bBitMask = var1;
}

void DDPixelFormat::setRGBAlphaBitMask(long var1) {
    rgbAlphaBitMask = var1;
}

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
