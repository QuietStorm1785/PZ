#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/fileSystem/TexturePackDevice/Page.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace fileSystem {


class TexturePackDevice {
public:
    TexturePackDevice m_device;

   TexturePackDevice$TexturePackInputStream(std::string var1, TexturePackDevice var2) throws IOException {
      super(var2.m_filename);
      this.m_device = var2;
    Page var3 = (Page)this.m_device.m_pagemap.get(var1);
      if (var3 == nullptr) {
         throw std::make_unique<FileNotFoundException>();
      } else {
         TexturePackDevice.skipInput(this, var3.m_png_start);
         if (var2.m_version >= 1) {
    int var4 = TexturePackPage.readInt(this);
         }
      }
   }
}
} // namespace fileSystem
} // namespace zombie
