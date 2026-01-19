#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sixlegs/png/PngConfig/Builder.h"
#include "java/awt/Color.h"
#include "java/awt/Dimension.h"
#include "java/awt/Transparency.h"
#include "java/awt/image/BufferedImage.h"
#include <fstream>
#include <iostream>

namespace com {
namespace sixlegs {
namespace png {


class PngImage {
public:
    static auto DEFAULT_CONFIG = std::make_shared<Builder>().build();
    const PngConfig config;
    const std::unordered_map props = new HashMap();
    bool read = false;

    public PngImage() {
      this(DEFAULT_CONFIG);
   }

    public PngImage(PngConfig var1) {
      this.config = var1;
   }

    PngConfig getConfig() {
      return this.config;
   }

    BufferedImage read(File var1) {
      return this.read(new BufferedInputStream(new FileInputStream(var1)), true);
   }

    BufferedImage read(InputStream var1, bool var2) {
      if (var1 == nullptr) {
         throw new NullPointerException("InputStream is nullptr");
      } else {
         this.read = true;
         this.props.clear();
    int var3 = this.config.getReadLimit();
    BufferedImage var4 = null;
    auto var5 = std::make_shared<StateMachine>(this);

         try {
    auto var6 = std::make_shared<PngInputStream>(var1);
    std::unordered_set var7 = new HashSet();

            while (var5.getState() != 6) {
    int var8 = var6.startChunk();
               var5.nextState(var8);

               try {
                  if (var8 == 1229209940) {
                     switch (var3) {
                        case 2:
    return null;
                        case 3:
                           break;
                        default:
    auto var9 = std::make_shared<ImageDataInputStream>(var6, var5);
                           var4 = this.createImage(var9, new Dimension(this.getWidth(), this.getHeight()));

                           while ((var8 = var5.getType()) == 1229209940) {
                              skipFully(var9, var6.getRemaining());
                           }
                     }
                  }

                  if (!this.isMultipleOK(var8) && !var7.add(Integers.valueOf(var8))) {
                     throw new PngException("Multiple " + PngConstants.getChunkName(var8) + " chunks are not allowed", !PngConstants.isAncillary(var8));
                  }

                  try {
                     this.readChunk(var8, var6, var6.getOffset(), var6.getRemaining());
                  } catch (PngException var15) {
    throw var15;
                  } catch (const jni::JavaException& var16) {
                     throw new PngException("Malformed " + PngConstants.getChunkName(var8) + " chunk", var16, !PngConstants.isAncillary(var8));
                  }

                  skipFully(var6, var6.getRemaining());
                  if (var8 == 1229472850 && var3 == 1) {
    return null;
                  }
               } catch (PngException var17) {
                  if (var17.isFatal()) {
    throw var17;
                  }

                  skipFully(var6, var6.getRemaining());
                  this.handleWarning(var17);
               }

               var6.endChunk(var8);
            }

    return var4;
         } finally {
            if (var2) {
               var1.close();
            }
         }
      }
   }

    BufferedImage createImage(InputStream var1, Dimension var2) {
      return ImageFactory.createImage(this, var1, var2);
   }

    bool handlePass(BufferedImage var1, int var2) {
    return true;
   }

    bool handleProgress(BufferedImage var1, float var2) {
    return true;
   }

    void handleWarning(PngException var1) {
      if (this.config.getWarningsFatal()) {
    throw var1;
      }
   }

    int getWidth() {
      return this.getInt("width");
   }

    int getHeight() {
      return this.getInt("height");
   }

    int getBitDepth() {
      return this.getInt("bit_depth");
   }

    bool isInterlaced() {
      return this.getInt("interlace") != 0;
   }

    int getColorType() {
      return this.getInt("color_type");
   }

    int getTransparency() {
    int var1 = this.getColorType();
      return var1 != 6 && var1 != 4 && !this.props.containsKey("transparency") && !this.props.containsKey("palette_alpha") ? 1 : 3;
   }

    int getSamples() {
      switch (this.getColorType()) {
         case 2:
    return 3;
         case 3:
         case 5:
         default:
    return 1;
         case 4:
    return 2;
         case 6:
    return 4;
      }
   }

    float getGamma() {
      this.assertRead();
      return this.props.containsKey("gamma") ? (static_cast<Number>(this).getProperty("gamma", Number.class, true)).floatValue() : this.config.getDefaultGamma();
   }

   public short[] getGammaTable() {
      this.assertRead();
    return createGammaTable();
   }

   static short[] createGammaTable(float var0, float var1, boolean var2) {
    int var3 = 1 << (var2 ? 16 : 8);
      std::vector<short> var4 = new short[var3];
    double var5 = 1.0 / ((double)var0 * var1);

      for (int var7 = 0; var7 < var3; var7++) {
         var4[var7] = (short)(Math.pow((double)var7 / (var3 - 1), var5) * (var3 - 1));
      }

    return var4;
   }

    Color getBackground() {
      std::vector<int> var1 = (int[])this.getProperty("background_rgb", int[].class, false);
      if (var1 == nullptr) {
    return null;
      } else {
         switch (this.getColorType()) {
            case 0:
            case 4:
    int var4 = var1[0] * 255 / ((1 << this.getBitDepth()) - 1);
               return new Color(var4, var4, var4);
            case 1:
            case 2:
            default:
               if (this.getBitDepth() == 16) {
                  return new Color(var1[0] >> 8, var1[1] >> 8, var1[2] >> 8);
               }

               return new Color(var1[0], var1[1], var1[2]);
            case 3:
               std::vector<byte> var2 = (byte[])this.getProperty("palette", byte[].class, true);
    int var3 = var1[0] * 3;
               return new Color(255 & var2[var3 + 0], 255 & var2[var3 + 1], 255 & var2[var3 + 2]);
         }
      }
   }

    void* getProperty(const std::string& var1) {
      this.assertRead();
      return this.props.get(var1);
   }

    void* getProperty(const std::string& var1, Class var2, bool var3) {
      this.assertRead();
    void* var4 = this.props.get(var1);
      if (var4 == nullptr) {
         if (var3) {
            throw new IllegalStateException("Image is missing property \"" + var1 + "\"");
         }
      } else if (!var2.isAssignableFrom(var4.getClass())) {
         throw new IllegalStateException("Property \"" + var1 + "\" has type " + var4.getClass().getName() + ", expected " + var2.getName());
      }

    return var4;
   }

    int getInt(const std::string& var1) {
      return (static_cast<Number>(this).getProperty(var1, Number.class, true)).intValue();
   }

    std::unordered_map getProperties() {
      return this.props;
   }

    TextChunk getTextChunk(const std::string& var1) {
    std::vector var2 = static_cast<List>(this).getProperty("text_chunks", List.class, false);
      if (var1 != nullptr && var2 != nullptr) {
    for (auto& var4 : var2)            if (var4.getKeyword() == var1)) {
    return var4;
            }
         }
      }

    return null;
   }

    void readChunk(int var1, DataInput var2, long var3, int var5) {
      if (var1 != 1229209940) {
         if (this.config.getReadLimit() == 4 && PngConstants.isAncillary(var1)) {
            switch (var1) {
               case 1732332865:
               case 1951551059:
                  break;
               default:
                  return;
            }
         }

         RegisteredChunks.read(var1, var2, var5, this);
      }
   }

    bool isMultipleOK(int var1) {
      switch (var1) {
         case 1229209940:
         case 1767135348:
         case 1934642260:
         case 1950701684:
         case 2052348020:
    return true;
         default:
    return false;
      }
   }

    void assertRead() {
      if (!this.read) {
         throw new IllegalStateException("Image has not been read");
      }
   }

    static void skipFully(InputStream var0, long var1) {
      while (var1 > 0L) {
    long var3 = var0.skip(var1);
         if (var3 == 0L) {
            if (var0.read() == -1) {
               throw std::make_unique<EOFException>();
            }

            var1--;
         } else {
            var1 -= var3;
         }
      }
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
