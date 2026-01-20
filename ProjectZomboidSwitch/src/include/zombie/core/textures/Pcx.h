#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Image.h"
#include "java/awt/Toolkit.h"
#include "java/awt/image/MemoryImageSource.h"
#include "java/net/URL.h"
#include "zombie/GameWindow.h"
#include "zombie/core/textures/Pcx/pcx_t.h"
#include "zombie/debug/DebugLog.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace textures {


class Pcx {
public:
   public static std::unordered_map<std::string, Pcx> Cache = std::make_unique<std::unordered_map<>>();
   public byte[] imageData;
    int imageWidth;
    int imageHeight;
   public int[] palette;
   public int[] pic;

    public Pcx(const std::string& var1) {
   }

    public Pcx(URL var1) {
   }

    public Pcx(const std::string& var1, int[] var2) {
   }

    public Pcx(const std::string& var1, const std::string& var2) {
   }

    Image getImage() {
      int[] var1 = new int[this.imageWidth * this.imageHeight];
    int var2 = 0;
    int var3 = 0;

      for (int var4 = 0; var4 < this.imageWidth; var4++) {
         for (int var5 = 0; var5 < this.imageHeight; var5++) {
            var1[var2++] = 0xFF000000 | (this.imageData[var3++] & 255) << 16 | (this.imageData[var3++] & 255) << 8 | this.imageData[var3++] & 255;
         }
      }

    Toolkit var8 = Toolkit.getDefaultToolkit();
      return var8.createImage(std::make_shared<MemoryImageSource>(this.imageWidth, this.imageHeight, var1, 0, this.imageWidth));
   }

    int loadPCX(URL var1) {
      try {
    InputStream var12 = var1.openStream();
    int var7 = var12.available();
         byte[] var13 = new byte[var7 + 1];
         var13[var7] = 0;

         for (int var14 = 0; var14 < var7; var14++) {
            var13[var14] = (byte)var12.read();
         }

         var12.close();
         if (var7 == -1) {
            return -1;
         } else {
    pcx_t var4 = std::make_shared<pcx_t>(this, var13);
            byte[] var3 = var4.data;
            if (var4.manufacturer == '\n' && var4.version == 5 && var4.encoding == 1 && var4.bits_per_pixel == '\b' && var4.xmax < 640 && var4.ymax < 480) {
               this.palette = new int[768];

               for (int var17 = 0; var17 < 768; var17++) {
                  if (var7 - 128 - 768 + var17 < var4.data.length) {
                     this.palette[var17] = var4.data[var7 - 128 - 768 + var17] & 255;
                  }
               }

               this.imageWidth = var4.xmax + 1;
               this.imageHeight = var4.ymax + 1;
               int[] var10 = new int[(var4.ymax + 1) * (var4.xmax + 1)];
               this.pic = var10;
               int[] var11 = var10;
    int var18 = 0;
    int var15 = 0;

               for (int var6 = 0; var6 <= var4.ymax; var18 += var4.xmax + 1) {
    int var5 = 0;

                  while (var5 <= var4.xmax) {
    uint8_t var8 = var3[var15++];
    int var9;
                     if ((var8 & 192) == 192) {
                        var9 = var8 & 63;
                        var8 = var3[var15++];
                     } else {
                        var9 = 1;
                     }

                     while (var9-- > 0) {
                        var11[var18 + var5++] = var8 & 255;
                     }
                  }

                  var6++;
               }

               if (this.pic != nullptr && this.palette != nullptr) {
                  this.imageData = new byte[(this.imageWidth + 1) * (this.imageHeight + 1) * 3];

                  for (int var2 = 0; var2 < this.imageWidth * this.imageHeight; var2++) {
                     this.imageData[var2 * 3] = (byte)this.palette[this.pic[var2] * 3];
                     this.imageData[var2 * 3 + 1] = (byte)this.palette[this.pic[var2] * 3 + 1];
                     this.imageData[var2 * 3 + 2] = (byte)this.palette[this.pic[var2] * 3 + 2];
                  }

    return 1;
               } else {
                  return -1;
               }
            } else {
               DebugLog.log("Bad pcx file " + var1);
               return -1;
            }
         }
      } catch (Exception var16) {
         var16.printStackTrace();
    return 1;
      }
   }

    int loadPCXminusPal(const std::string& var1) {
      try {
         if (Cache.containsKey(var1)) {
    Pcx var17 = Cache.get(var1);
            this.imageWidth = var17.imageWidth;
            this.imageHeight = var17.imageHeight;
            this.imageData = new byte[(var17.imageWidth + 1) * (var17.imageHeight + 1) * 3];

            for (int var18 = 0; var18 < var17.imageWidth * var17.imageHeight; var18++) {
               this.imageData[var18 * 3] = (byte)this.palette[var17.pic[var18] * 3];
               this.imageData[var18 * 3 + 1] = (byte)this.palette[var17.pic[var18] * 3 + 1];
               this.imageData[var18 * 3 + 2] = (byte)this.palette[var17.pic[var18] * 3 + 2];
            }

    return 1;
         } else {
    InputStream var12 = GameWindow.class.getClassLoader().getResourceAsStream(var1);
            if (var12 == nullptr) {
    return 0;
            } else {
    int var7 = var12.available();
               byte[] var13 = new byte[var7 + 1];
               var13[var7] = 0;

               for (int var14 = 0; var14 < var7; var14++) {
                  var13[var14] = (byte)var12.read();
               }

               var12.close();
               if (var7 == -1) {
                  return -1;
               } else {
    pcx_t var4 = std::make_shared<pcx_t>(this, var13);
                  byte[] var3 = var4.data;
                  if (var4.manufacturer == '\n' && var4.version == 5 && var4.encoding == 1 && var4.bits_per_pixel == '\b' && var4.xmax < 640 && var4.ymax < 480
                     )
                   {
                     this.imageWidth = var4.xmax + 1;
                     this.imageHeight = var4.ymax + 1;
                     int[] var10 = new int[(var4.ymax + 1) * (var4.xmax + 1)];
                     this.pic = var10;
                     int[] var11 = var10;
    int var19 = 0;
    int var15 = 0;

                     for (int var6 = 0; var6 <= var4.ymax; var19 += var4.xmax + 1) {
    int var5 = 0;

                        while (var5 <= var4.xmax) {
    uint8_t var8 = var3[var15++];
    int var9;
                           if ((var8 & 192) == 192) {
                              var9 = var8 & 63;
                              var8 = var3[var15++];
                           } else {
                              var9 = 1;
                           }

                           while (var9-- > 0) {
                              var11[var19 + var5++] = var8 & 255;
                           }
                        }

                        var6++;
                     }

                     if (this.pic != nullptr && this.palette != nullptr) {
                        this.imageData = new byte[(this.imageWidth + 1) * (this.imageHeight + 1) * 3];

                        for (int var2 = 0; var2 < this.imageWidth * this.imageHeight; var2++) {
                           this.imageData[var2 * 3] = (byte)this.palette[this.pic[var2] * 3];
                           this.imageData[var2 * 3 + 1] = (byte)this.palette[this.pic[var2] * 3 + 1];
                           this.imageData[var2 * 3 + 2] = (byte)this.palette[this.pic[var2] * 3 + 2];
                        }

                        Cache.put(var1, this);
    return 1;
                     } else {
                        return -1;
                     }
                  } else {
                     DebugLog.log("Bad pcx file " + var1);
                     return -1;
                  }
               }
            }
         }
      } catch (Exception var16) {
         var16.printStackTrace();
    return 1;
      }
   }

    int loadPCXpal(const std::string& var1) {
      try {
    InputStream var12 = GameWindow.class.getClassLoader().getResourceAsStream(var1);
         if (var12 == nullptr) {
    return 1;
         } else {
    int var7 = var12.available();
            byte[] var13 = new byte[var7 + 1];
            var13[var7] = 0;

            for (int var14 = 0; var14 < var7; var14++) {
               var13[var14] = (byte)var12.read();
            }

            var12.close();
            if (var7 == -1) {
               return -1;
            } else {
    pcx_t var4 = std::make_shared<pcx_t>(this, var13);
               byte[] var3 = var4.data;
               if (var4.manufacturer == '\n' && var4.version == 5 && var4.encoding == 1 && var4.bits_per_pixel == '\b' && var4.xmax < 640 && var4.ymax < 480) {
                  this.palette = new int[768];

                  for (int var17 = 0; var17 < 768; var17++) {
                     if (var7 - 128 - 768 + var17 < var4.data.length) {
                        this.palette[var17] = var4.data[var7 - 128 - 768 + var17] & 255;
                     }
                  }

                  this.imageWidth = var4.xmax + 1;
                  this.imageHeight = var4.ymax + 1;
                  int[] var10 = new int[(var4.ymax + 1) * (var4.xmax + 1)];
                  this.pic = var10;
    bool var18 = false;
    bool var15 = false;
                  return this.pic != nullptr && this.palette != nullptr ? 1 : -1;
               } else {
                  DebugLog.log("Bad pcx file " + var1);
                  return -1;
               }
            }
         }
      } catch (Exception var16) {
         var16.printStackTrace();
    return 1;
      }
   }

    void loadPCXpal(int[] var1) {
      this.palette = var1;
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
