#pragma once
#include <string>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class DDPixelFormat {
public:
    long size = 0L;
    long flags = 0L;
    long fourCC = 0L;
    std::string fourCCString = "";
    long rgbBitCount = 0L;
    long rBitMask = 0L;
    long gBitMask = 0L;
    long bBitMask = 0L;
    long rgbAlphaBitMask = 0L;
    bool isCompressed = true;

    DDPixelFormat();
    void setSize(long var1);
    void setFlags(long var1);
    void setFourCC(long var1);
    void createFourCCString();
    std::string getFourCCString();
    void setRGBBitCount(long var1);
    void setRBitMask(long var1);
    void setGBitMask(long var1);
    void setBBitMask(long var1);
    void setRGBAlphaBitMask(long var1);
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com