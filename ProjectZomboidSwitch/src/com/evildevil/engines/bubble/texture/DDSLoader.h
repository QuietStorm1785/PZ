#pragma once
#include <string>
#include <vector>
#include <memory>
#include <GL/glew.h>
#include "com/evildevil/engines/bubble/texture/DDSurfaceDesc2.h"
#include "com/evildevil/engines/bubble/texture/DDPixelFormat.h"
#include "com/evildevil/engines/bubble/texture/DDSCaps2.h"

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

class DDSLoader {
public:
    static constexpr const char* DDS_IDENTIFIER = "DDS ";
    static constexpr int DDS_HEADER_SIZE = 128;
    static constexpr int DDS_DESC2_RESERVED_1 = 44;
    static constexpr int DDS_DESC2_RESERVED_2 = 4;
    static constexpr int DDS_CAPS2_RESERVED = 8;
    static constexpr int DEFAULT_DXT_BLOCKSIZE = 16;
    static constexpr int DXT1_BLOCKSIZE = 8;

    std::shared_ptr<DDSurfaceDesc2> ddsDesc2;
    // ByteBuffer ddsHeader, imageData, imageData2; // TODO: Implement or replace with std::vector<uint8_t>
    // BufferedInputStream ddsFileChannel; // TODO: Implement or replace with std::ifstream
    static int lastWid;
    static int lastHei;

    DDSLoader();
    int loadDDSFile(const std::string& filename);
    void readFileHeader();
    int readFileData();
    int calculateSize(int size);
    void debugInfo();

    // Additional features
    bool isDXT1() const {
        return ddsDesc2 && ddsDesc2->getDDPixelformat()->getFourCCString() == "DXT1";
    }
    bool isDXT3() const {
        return ddsDesc2 && ddsDesc2->getDDPixelformat()->getFourCCString() == "DXT3";
    }
    bool isDXT5() const {
        return ddsDesc2 && ddsDesc2->getDDPixelformat()->getFourCCString() == "DXT5";
    }
    int getWidth() const {
        return ddsDesc2 ? static_cast<int>(ddsDesc2->width) : 0;
    }
    int getHeight() const {
        return ddsDesc2 ? static_cast<int>(ddsDesc2->height) : 0;
    }
    int getMipMapCount() const {
        return ddsDesc2 ? static_cast<int>(ddsDesc2->mipMapCount) : 0;
    }
    std::string getFormatString() const {
        return ddsDesc2 ? ddsDesc2->getDDPixelformat()->getFourCCString() : "";
    }

    // Advanced features
    // Returns the raw image data buffer (after header)
    const std::vector<uint8_t>& getImageData() const { return imageData; }
    // Returns true if the DDS file is valid and loaded
    bool isValid() const { return valid; }
    // Returns error message if any
    const std::string& getError() const { return errorMsg; }
    // Mipmap support (stub for now)
    int getNumMipmaps() const { return getMipMapCount(); }
    // Reset loader state
    void reset();
    // GPU integration
    int uploadToGPU();
    unsigned int getGLTextureID() const { return glTextureID; }
    // More DDS features
    int getBlockSize() const {
        return isDXT1() ? 8 : 16;
    }
    size_t getImageDataOffset(int mipLevel = 0) const {
        int w = getWidth();
        int h = getHeight();
        int blockSize = getBlockSize();
        size_t offset = 0;
        for (int i = 0; i < mipLevel; ++i) {
            int size = ((w+3)/4) * ((h+3)/4) * blockSize;
            offset += size;
            w = w > 1 ? w/2 : 1;
            h = h > 1 ? h/2 : 1;
        }
        return offset;
    }
    int getMipmapWidth(int mipLevel) const {
        int w = getWidth();
        for (int i = 0; i < mipLevel; ++i) w = w > 1 ? w/2 : 1;
        return w;
    }
    int getMipmapHeight(int mipLevel) const {
        int h = getHeight();
        for (int i = 0; i < mipLevel; ++i) h = h > 1 ? h/2 : 1;
        return h;
    }

private:
    std::vector<uint8_t> imageData;
    bool valid = false;
    std::string errorMsg;
    unsigned int glTextureID = 0;
};

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
