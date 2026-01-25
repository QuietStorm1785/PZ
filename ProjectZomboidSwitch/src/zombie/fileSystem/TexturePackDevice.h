#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/core/textures/TexturePackPage/SubTextureInfo.h"
#include "zombie/fileSystem/FileSystem/TexturePackTextures.h"
#include "zombie/fileSystem/TexturePackDevice/Page.h"
#include "zombie/fileSystem/TexturePackDevice/PositionInputStream.h"
#include "zombie/fileSystem/TexturePackDevice/SubTexture.h"
#include "zombie/fileSystem/TexturePackDevice/TexturePackInputStream.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class TexturePackDevice : public std::enable_shared_from_this<TexturePackDevice> {
public:
    static constexpr int VERSION1 = 1;
    static constexpr int VERSION_LATEST = 1;
    std::string m_name;
    std::string m_filename;
    int m_version;
    std::vector<std::shared_ptr<Page>> m_pages;
    std::unordered_map<std::string, std::shared_ptr<Page>> m_pagemap;
    std::unordered_map<std::string, std::shared_ptr<SubTexture>> m_submap;
    int m_textureFlags;

    static int64_t skipInput(InputStream var0, int64_t var1);

    TexturePackDevice(const std::string& name, int textureFlags);

    IFile createFile(IFile var1);
    void destroyFile(IFile var1);
    InputStream createStream(const std::string& var1, InputStream var2);
    void destroyStream(InputStream var1);
    std::string name() const;
    void getSubTextureInfo(TexturePackTextures var1);
    void initMetaData();
    std::shared_ptr<Page> readPage(std::shared_ptr<PositionInputStream> var1);
    bool isAlpha(const std::string& var1) const;
    int getTextureFlags() const;
};
} // namespace fileSystem
} // namespace zombie
