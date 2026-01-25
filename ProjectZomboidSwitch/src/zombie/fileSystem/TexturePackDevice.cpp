#include <string>
#include "zombie/fileSystem/TexturePackDevice.h"

namespace zombie {
namespace fileSystem {

long TexturePackDevice::skipInput(InputStream var0, long var1) {
    long total = 0;
    while (total < var1) {
        long skipped = var0->skip(var1 - total);
        if (skipped > 0) {
            total += skipped;
        } else {
            break;
        }
    }
    return total;
}
}

TexturePackDevice::TexturePackDevice(const std::string& var1, int var2)
    : m_name(var1), m_filename("media/texturepacks/" + var1 + ".pack"), m_textureFlags(var2), m_version(-1)
{
    m_isLoaded = false;
    m_packSize = 0;
    m_packOffset = 0;
    m_packStream = nullptr;
    m_pages.clear();
    m_submap.clear();
    m_pagemap.clear();
    // Java/header fields
    // m_version is already set to -1 in initializer
    // m_textureFlags is set from var2
    // m_name and m_filename are set from var1
    // Add any additional fields as needed
}
}

IFile TexturePackDevice::createFile(IFile var1) {
    // TexturePackDevice is read-only; cannot create files in a texture pack
    // Optionally, throw or log an error here
    return nullptr;
}
}

void TexturePackDevice::destroyFile(IFile var1) {
    // No-op
}
}

InputStream TexturePackDevice::createStream(const std::string& var1, InputStream var2) {
    initMetaData();
    // TexturePackInputStream should be constructed with the texture name and this device
    return std::make_shared<TexturePackInputStream>(var1, shared_from_this());
}
}

void TexturePackDevice::destroyStream(InputStream var1) {
    // If var1 is a TexturePackInputStream, reset the pointer to release resources
    auto texStream = std::dynamic_pointer_cast<TexturePackInputStream>(var1);
    if (texStream) {
        texStream.reset();
    }
}
}

std::string TexturePackDevice::name() {
    return m_name;
}
}

void TexturePackDevice::getSubTextureInfo(TexturePackTextures var1) {
    initMetaData();
    for (const auto& pair : m_submap) {
        const auto& key = pair.first;
        const auto& sub = pair.second;
        // Construct a FileSystem::SubTexture (pack name, page name, subtexture info)
        FileSystem::SubTexture fsSubTex(name(), sub.m_page.m_name, sub.m_info);
        (*var1)[key] = fsSubTex;
    }
}
}

void TexturePackDevice::initMetaData() {
    if (!m_pages.empty()) {
        return;
    }

    // Open the file
    std::ifstream file(m_filename, std::ios::binary);
    if (!file.is_open()) {
        // Could not open file, handle error as needed
        return;
    }

    // Read first 4 bytes
    char magic[4];
    file.read(magic, 4);
    if (!file) {
        file.close();
        return;
    }

    if (magic[0] == 'P' && magic[1] == 'Z' && magic[2] == 'P' && magic[3] == 'K') {
        // Read version (int32)
        int32_t version = 0;
        file.read(reinterpret_cast<char*>(&version), sizeof(version));
        m_version = version;
        if (m_version < 1 || m_version > 1) {
            file.close();
            return;
        }
    } else {
        // Not a PZPK file, reset and set version 0
        file.seekg(0);
        m_version = 0;
    }

    // Read number of pages (int32)
    int32_t numPages = 0;
    file.read(reinterpret_cast<char*>(&numPages), sizeof(numPages));
    if (!file) {
        file.close();
        return;
    }


    // Wrap the file stream in a PositionInputStream (if available)
    // For now, assume file is compatible with PositionInputStream constructor
    auto posStream = std::make_shared<PositionInputStream>(shared_from_this(), file);
    for (int i = 0; i < numPages; ++i) {
        Page page = readPage(posStream);
        m_pages.push_back(page);
        m_pagemap[page->m_name] = page;
        for (const auto& sub : page->m_sub) {
            m_submap[sub->name] = SubTexture(page, *sub);
        }
    }

    file.close();
}
}

Page TexturePackDevice::readPage(PositionInputStream var1) {
    // Create a new Page object
    auto page = std::make_shared<Page>();

    // Read page name
    page->m_name = TexturePackPage::ReadString(var1);
    // Read number of subtextures
    int numSubs = TexturePackPage::readInt(var1);
    // Read has_alpha
    page->m_has_alpha = TexturePackPage::readInt(var1) != 0;

    // Read subtextures
    for (int i = 0; i < numSubs; ++i) {
        std::string subName = TexturePackPage::ReadString(var1);
        int x = TexturePackPage::readInt(var1);
        int y = TexturePackPage::readInt(var1);
        int w = TexturePackPage::readInt(var1);
        int h = TexturePackPage::readInt(var1);
        int ox = TexturePackPage::readInt(var1);
        int oy = TexturePackPage::readInt(var1);
        int fx = TexturePackPage::readInt(var1);
        int fy = TexturePackPage::readInt(var1);
        auto subInfo = std::make_shared<SubTextureInfo>(x, y, w, h, ox, oy, fx, fy, subName);
        page->m_sub.push_back(subInfo);
    }

    // Set PNG start position
    page->m_png_start = var1->getPosition();

    if (m_version == 0) {
        int marker = 0;
        do {
            marker = TexturePackPage::readIntByte(var1);
        } while (marker != -559038737);
    } else {
        int skipLen = TexturePackPage::readInt(var1);
        skipInput(var1, skipLen);
    }

    return page;
}
}

bool TexturePackDevice::isAlpha(const std::string& var1) {
    auto it = m_pagemap.find(var1);
    if (it != m_pagemap.end() && it->second) {
        return it->second->m_has_alpha;
    }
    return false;
}
}

int TexturePackDevice::getTextureFlags() {
    return m_textureFlags;
}
}

} // namespace fileSystem
} // namespace zombie
