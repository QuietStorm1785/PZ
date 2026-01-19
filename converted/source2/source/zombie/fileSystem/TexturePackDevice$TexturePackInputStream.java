package zombie.fileSystem;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import zombie.core.textures.TexturePackPage;
import zombie.fileSystem.TexturePackDevice.Page;

class TexturePackDevice$TexturePackInputStream extends FileInputStream {
   TexturePackDevice m_device;

   TexturePackDevice$TexturePackInputStream(String var1, TexturePackDevice var2) throws IOException {
      super(var2.m_filename);
      this.m_device = var2;
      Page var3 = (Page)this.m_device.m_pagemap.get(var1);
      if (var3 == null) {
         throw new FileNotFoundException();
      } else {
         TexturePackDevice.skipInput(this, var3.m_png_start);
         if (var2.m_version >= 1) {
            int var4 = TexturePackPage.readInt(this);
         }
      }
   }
}
