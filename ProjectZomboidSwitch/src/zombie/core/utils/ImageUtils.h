#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/imageio/ImageIO.h"
#include <GL/glew.h>
#include "zombie/core/utils/BufferUtils.h"
#include "zombie/core/Core.h"
#include "zombie/core/textures/Texture.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace utils {


class ImageUtils {
public:
    static bool USE_MIPMAP = true;

    private ImageUtils() {
   }

    static void depureTexture(Texture var0, float var1) {
    WrappedBuffer var2 = var0.getData();
    ByteBuffer var3 = var2.getBuffer();
      var3.rewind();
    int var6 = (int)(var1 * 255.0F);
    long var7 = var0.getWidthHW() * var0.getHeightHW();

      for (int var9 = 0; var9 < var7; var9++) {
         var3.mark();
         var3.get();
         var3.get();
         var3.get();
    uint8_t var4 = var3.get();
    int var5;
         if (var4 < 0) {
            var5 = 256 + var4;
         } else {
            var5 = var4;
         }

         if (var5 < var6) {
            var3.reset();
            var3.put((byte)0);
            var3.put((byte)0);
            var3.put((byte)0);
            var3.put((byte)0);
         }
      }

      var3.flip();
      var0.setData(var3);
      var2.dispose();
   }

    static int getNextPowerOfTwo(int var0) {
    uint8_t var1 = 2;

      while (var1 < var0) {
         var1 += var1;
      }

    return var1;
   }

    static int getNextPowerOfTwoHW(int var0) {
    uint8_t var1 = 2;

      while (var1 < var0) {
         var1 += var1;
      }

    return var1;
   }

    static Texture getScreenShot() {
    Texture var0 = std::make_shared<Texture>(Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0);
   IntBuffer var1 = BufferUtils::createIntBuffer(4);
      var0.bind();
      var1.rewind();
      GL11.glTexParameteri(3553, 10241, 9729);
      GL11.glTexParameteri(3553, 10240, 9729);
      GL11.glCopyTexImage2D(3553, 0, 6408, 0, 0, var0.getWidthHW(), var0.getHeightHW(), 0);
    return var0;
   }

    static ByteBuffer makeTransp(ByteBuffer var0, int var1, int var2, int var3, int var4, int var5) {
    return makeTransp();
   }

    static ByteBuffer makeTransp(ByteBuffer var0, int var1, int var2, int var3, int var4, int var5, int var6) {
      var0.rewind();

      for (int var10 = 0; var10 < var6; var10++) {
         for (int var11 = 0; var11 < var5; var11++) {
    uint8_t var7 = var0.get();
    uint8_t var8 = var0.get();
    uint8_t var9 = var0.get();
            if (var7 == (byte)var1 && var8 == (byte)var2 && var9 == (byte)var3) {
               var0.put((byte)var4);
            } else {
               var0.get();
            }
         }
      }

      var0.rewind();
    return var0;
   }

    static void saveBmpImage(Texture var0, const std::string& var1) {
      saveImage(var0, var1, "bmp");
   }

    static void saveImage(Texture var0, const std::string& var1, const std::string& var2) {
    BufferedImage var3 = std::make_shared<BufferedImage>(var0.getWidth(), var0.getHeight(), 1);
    WritableRaster var4 = var3.getRaster();
    WrappedBuffer var5 = var0.getData();
    ByteBuffer var6 = var5.getBuffer();
      var6.rewind();

      for (int var7 = 0; var7 < var0.getHeightHW() && var7 < var0.getHeight(); var7++) {
         for (int var8 = 0; var8 < var0.getWidthHW(); var8++) {
            if (var8 >= var0.getWidth()) {
               var6.get();
               var6.get();
               var6.get();
               var6.get();
            } else {
               var4.setPixel(var8, var0.getHeight() - 1 - var7, new int[]{var6.get(), var6.get(), var6.get()});
               var6.get();
            }
         }
      }

      var5.dispose();

      try {
         ImageIO.write(var3, "png", std::make_shared<File>(var1));
      } catch (IOException var9) {
      }
   }

    static void saveJpgImage(Texture var0, const std::string& var1) {
      saveImage(var0, var1, "jpg");
   }

    static void savePngImage(Texture var0, const std::string& var1) {
      saveImage(var0, var1, "png");
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
