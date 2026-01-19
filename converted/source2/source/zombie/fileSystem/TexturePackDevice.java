package zombie.fileSystem;

import java.io.BufferedInputStream;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashMap;
import zombie.ZomboidFileSystem;
import zombie.core.textures.TexturePackPage;
import zombie.core.textures.TexturePackPage.SubTextureInfo;
import zombie.fileSystem.FileSystem.TexturePackTextures;
import zombie.fileSystem.TexturePackDevice.Page;
import zombie.fileSystem.TexturePackDevice.PositionInputStream;
import zombie.fileSystem.TexturePackDevice.SubTexture;
import zombie.fileSystem.TexturePackDevice.TexturePackInputStream;

public final class TexturePackDevice implements IFileDevice {
   static final int VERSION1 = 1;
   static final int VERSION_LATEST = 1;
   String m_name;
   String m_filename;
   int m_version = -1;
   final ArrayList<Page> m_pages = new ArrayList<>();
   final HashMap<String, Page> m_pagemap = new HashMap<>();
   final HashMap<String, SubTexture> m_submap = new HashMap<>();
   int m_textureFlags;

   private static long skipInput(InputStream var0, long var1) throws IOException {
      long var3 = 0L;

      while (var3 < var1) {
         long var5 = var0.skip(var1 - var3);
         if (var5 > 0L) {
            var3 += var5;
         }
      }

      return var3;
   }

   public TexturePackDevice(String var1, int var2) {
      this.m_name = var1;
      this.m_filename = ZomboidFileSystem.instance.getString("media/texturepacks/" + var1 + ".pack");
      this.m_textureFlags = var2;
   }

   public IFile createFile(IFile var1) {
      return null;
   }

   public void destroyFile(IFile var1) {
   }

   public InputStream createStream(String var1, InputStream var2) throws IOException {
      this.initMetaData();
      return new TexturePackInputStream(var1, this);
   }

   public void destroyStream(InputStream var1) {
      if (var1 instanceof TexturePackInputStream) {
      }
   }

   public String name() {
      return this.m_name;
   }

   public void getSubTextureInfo(TexturePackTextures var1) throws IOException {
      this.initMetaData();

      for (SubTexture var3 : this.m_submap.values()) {
         zombie.fileSystem.FileSystem.SubTexture var4 = new zombie.fileSystem.FileSystem.SubTexture(this.name(), var3.m_page.m_name, var3.m_info);
         var1.put(var3.m_info.name, var4);
      }
   }

   private void initMetaData() throws IOException {
      if (this.m_pages.isEmpty()) {
         try (
            FileInputStream var1 = new FileInputStream(this.m_filename);
            BufferedInputStream var2 = new BufferedInputStream(var1);
         ) {
            PositionInputStream var3 = new PositionInputStream(this, var2);

            try {
               var3.mark(4);
               int var4 = var3.read();
               int var5 = var3.read();
               int var6 = var3.read();
               int var7 = var3.read();
               if (var4 == 80 && var5 == 90 && var6 == 80 && var7 == 75) {
                  this.m_version = TexturePackPage.readInt(var3);
                  if (this.m_version < 1 || this.m_version > 1) {
                     throw new IOException("invalid .pack file version " + this.m_version);
                  }
               } else {
                  var3.reset();
                  this.m_version = 0;
               }

               int var8 = TexturePackPage.readInt(var3);

               for (int var9 = 0; var9 < var8; var9++) {
                  Page var10 = this.readPage(var3);
                  this.m_pages.add(var10);
                  this.m_pagemap.put(var10.m_name, var10);

                  for (SubTextureInfo var12 : var10.m_sub) {
                     this.m_submap.put(var12.name, new SubTexture(var10, var12));
                  }
               }
            } catch (Throwable var16) {
               try {
                  var3.close();
               } catch (Throwable var15) {
                  var16.addSuppressed(var15);
               }

               throw var16;
            }

            var3.close();
         }
      }
   }

   private Page readPage(PositionInputStream var1) throws IOException {
      Page var2 = new Page();
      String var3 = TexturePackPage.ReadString(var1);
      int var4 = TexturePackPage.readInt(var1);
      boolean var5 = TexturePackPage.readInt(var1) != 0;
      var2.m_name = var3;
      var2.m_has_alpha = var5;

      for (int var6 = 0; var6 < var4; var6++) {
         String var7 = TexturePackPage.ReadString(var1);
         int var8 = TexturePackPage.readInt(var1);
         int var9 = TexturePackPage.readInt(var1);
         int var10 = TexturePackPage.readInt(var1);
         int var11 = TexturePackPage.readInt(var1);
         int var12 = TexturePackPage.readInt(var1);
         int var13 = TexturePackPage.readInt(var1);
         int var14 = TexturePackPage.readInt(var1);
         int var15 = TexturePackPage.readInt(var1);
         var2.m_sub.add(new SubTextureInfo(var8, var9, var10, var11, var12, var13, var14, var15, var7));
      }

      var2.m_png_start = var1.getPosition();
      if (this.m_version == 0) {
         int var16 = 0;

         do {
            var16 = TexturePackPage.readIntByte(var1);
         } while (var16 != -559038737);
      } else {
         int var18 = TexturePackPage.readInt(var1);
         skipInput(var1, var18);
      }

      return var2;
   }

   public boolean isAlpha(String var1) {
      Page var2 = this.m_pagemap.get(var1);
      return var2.m_has_alpha;
   }

   public int getTextureFlags() {
      return this.m_textureFlags;
   }
}
