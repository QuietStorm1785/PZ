#include <string>
#include "com/evildevil/engines/bubble/texture/DDSLoader.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <memory>
#include <cstring>
#include <cmath>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {

int DDSLoader::lastWid = 0;
int DDSLoader::lastHei = 0;

DDSLoader::DDSLoader() {
    ddsDesc2 = std::make_shared<DDSurfaceDesc2>();
}

void DDSLoader::reset() {
    imageData.clear();
    valid = false;
    errorMsg.clear();
    ddsDesc2 = std::make_shared<DDSurfaceDesc2>();
}

int DDSLoader::loadDDSFile(const std::string& filename) {
    reset();
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        errorMsg = "Failed to open DDS file: " + filename;
        return -1;
    }
    std::vector<uint8_t> header(DDS_HEADER_SIZE);
    if (!file.read(reinterpret_cast<char*>(header.data()), DDS_HEADER_SIZE)) {
        errorMsg = "Failed to read DDS header from: " + filename;
        return -1;
    }
    size_t offset = 0;
    auto readInt = [&header, &offset]() -> uint32_t {
        uint32_t val = header[offset] | (header[offset+1] << 8) | (header[offset+2] << 16) | (header[offset+3] << 24);
        offset += 4;
        return val;
    };
    try {
        ddsDesc2->setIdentifier(readInt());
        ddsDesc2->setSize(readInt());
        ddsDesc2->setFlags(readInt());
        ddsDesc2->setHeight(readInt());
        ddsDesc2->setWidth(readInt());
        ddsDesc2->setPitchOrLinearSize(readInt());
        ddsDesc2->setDepth(readInt());
        ddsDesc2->setMipMapCount(readInt());
        offset += DDS_DESC2_RESERVED_1;
        auto pf = ddsDesc2->getDDPixelformat();
        pf->setSize(readInt());
        pf->setFlags(readInt());
        pf->setFourCC(readInt());
        pf->setRGBBitCount(readInt());
        pf->setRBitMask(readInt());
        pf->setGBitMask(readInt());
        pf->setBBitMask(readInt());
        pf->setRGBAlphaBitMask(readInt());
        auto caps = ddsDesc2->getDDSCaps2();
        caps->setCaps1(readInt());
        caps->setCaps2(readInt());
        offset += DDS_CAPS2_RESERVED + DDS_DESC2_RESERVED_2;
    } catch (const std::exception& e) {
        errorMsg = std::string("DDS header parse error: ") + e.what();
        return -1;
    }
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(DDS_HEADER_SIZE, std::ios::beg);
    size_t dataSize = fileSize > DDS_HEADER_SIZE ? fileSize - DDS_HEADER_SIZE : 0;
    imageData.resize(dataSize);
    if (dataSize > 0) {
        file.read(reinterpret_cast<char*>(imageData.data()), dataSize);
    }
    lastWid = static_cast<int>(ddsDesc2->width);
    lastHei = static_cast<int>(ddsDesc2->height);
    valid = true;
    return 1;
}

void DDSLoader::readFileHeader() {
    // Not used in this implementation, logic moved to loadDDSFile
}

int DDSLoader::readFileData() {
    // This is a stub. Actual texture upload to GPU would go here.
    // For now, just return success.
    lastWid = static_cast<int>(ddsDesc2->width);
    lastHei = static_cast<int>(ddsDesc2->height);
    return 1;
}

int DDSLoader::calculateSize(int size) {
    // Example logic from Java/C++
    return static_cast<int>(std::ceil(ddsDesc2->width / 4.0) * std::ceil(ddsDesc2->height / 4.0) * size);
}

void DDSLoader::debugInfo() {
    auto var1 = ddsDesc2->getDDPixelformat();
    auto var2 = ddsDesc2->getDDSCaps2();
    std::cout << "\nDDSURFACEDESC2:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "SIZE: " << ddsDesc2->size << std::endl;
    std::cout << "FLAGS: " << ddsDesc2->flags << std::endl;
    std::cout << "HEIGHT: " << ddsDesc2->height << std::endl;
    std::cout << "WIDTH: " << ddsDesc2->width << std::endl;
    std::cout << "PITCH_OR_LINEAR_SIZE: " << ddsDesc2->pitchOrLinearSize << std::endl;
    std::cout << "DEPTH: " << ddsDesc2->depth << std::endl;
    std::cout << "MIP_MAP_COUNT: " << ddsDesc2->mipMapCount << std::endl;
    std::cout << "\nDDPIXELFORMAT of DDSURFACEDESC2:\n";
    std::cout << "----------------------------------------\n";
    std::cout << "SIZE :" << var1->size << std::endl;
    std::cout << "FLAGS: " << var1->flags << std::endl;
    std::cout << "FOUR_CC: " << var1->getFourCCString() << std::endl;
    std::cout << "RGB_BIT_COUNT: " << var1->rgbBitCount << std::endl;
    std::cout << "R_BIT_MASK: " << var1->rBitMask << std::endl;
    std::cout << "G_BIT_MASK: " << var1->gBitMask << std::endl;
    std::cout << "B_BIT_MASK: " << var1->bBitMask << std::endl;
    std::cout << "RGB_ALPHA_BIT_MASK: " << var1->rgbAlphaBitMask << std::endl;
    std::cout << "\nDDSCAPS of DDSURFACEDESC2" << std::endl;
    std::cout << "----------------------------------------\n";
    std::cout << "CAPS1: " << var2->caps1 << std::endl;
    std::cout << "CAPS2: " << var2->caps2 << std::endl;
}


int DDSLoader::uploadToGPU() {
    if (!valid || imageData.empty()) {
        errorMsg = "No valid DDS data to upload.";
        return -1;
    }
    if (glTextureID != 0) {
        // Already uploaded
        return glTextureID;
    }
    // Determine format
    GLenum format = 0;
    if (isDXT1()) format = 0x83F1; // GL_COMPRESSED_RGBA_S3TC_DXT1_EXT
    else if (isDXT3()) format = 0x83F2; // GL_COMPRESSED_RGBA_S3TC_DXT3_EXT
    else if (isDXT5()) format = 0x83F3; // GL_COMPRESSED_RGBA_S3TC_DXT5_EXT
    else {
        errorMsg = "Unsupported DDS format for GPU upload.";
        return -1;
    }
    glGenTextures(1, &glTextureID);
    glBindTexture(GL_TEXTURE_2D, glTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    int w = getWidth();
    int h = getHeight();
    int mipmaps = getNumMipmaps();
    int blockSize = isDXT1() ? 8 : 16;
    size_t offset = 0;
    for (int level = 0; level < mipmaps && (w || h); ++level) {
        int size = ((w+3)/4) * ((h+3)/4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, w, h, 0, size, imageData.data() + offset);
        offset += size;
        w = w > 1 ? w/2 : 1;
        h = h > 1 ? h/2 : 1;
    }
    return glTextureID;
}

} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
