#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace sixlegs {
namespace png {


class RegisteredChunks {
public:
    static const TimeZone TIME_ZONE = TimeZone.getTimeZone("UTC");
    static const std::string ISO_8859_1 = "ISO-8859-1";
    static const std::string US_ASCII = "US-ASCII";
    static const std::string UTF_8 = "UTF-8";

    static bool read(int var0, DataInput var1, int var2, PngImage var3) {
    std::unordered_map var4 = var3.getProperties();
      switch (var0) {
         case 1229278788:
            checkLength(1229278788, var2, 0);
            break;
         case 1229472850:
            read_IHDR(var1, var2, var4);
            break;
         case 1347179589:
            read_PLTE(var1, var2, var4, var3);
            break;
         case 1649100612:
            read_bKGD(var1, var2, var4, var3);
            break;
         case 1665684045:
            read_cHRM(var1, var2, var4);
            break;
         case 1732332865:
            read_gAMA(var1, var2, var4);
            break;
         case 1732855399:
            read_gIFg(var1, var2, var4);
            break;
         case 1749635924:
            read_hIST(var1, var2, var4, var3);
            break;
         case 1766015824:
            read_iCCP(var1, var2, var4);
            break;
         case 1767135348:
         case 1950701684:
         case 2052348020:
            readText(var0, var1, var2, var4, var3);
            break;
         case 1866876531:
            read_oFFs(var1, var2, var4);
            break;
         case 1883789683:
            read_pHYs(var1, var2, var4);
            break;
         case 1933723988:
            read_sBIT(var1, var2, var4, var3);
            break;
         case 1933787468:
            read_sCAL(var1, var2, var4);
            break;
         case 1934642260:
            read_sPLT(var1, var2, var4, var3);
            break;
         case 1934772034:
            read_sRGB(var1, var2, var4);
            break;
         case 1934902610:
            read_sTER(var1, var2, var4);
            break;
         case 1950960965:
            read_tIME(var1, var2, var4);
            break;
         case 1951551059:
            read_tRNS(var1, var2, var4, var3);
            break;
         default:
    return false;
      }

    return true;
   }

    static void read_IHDR(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1229472850, var1, 13);
    int var3 = var0.readInt();
    int var4 = var0.readInt();
      if (var3 > 0 && var4 > 0) {
    uint8_t var5 = var0.readByte();
         switch (var5) {
            case 1:
            case 2:
            case 4:
            case 8:
            case 16:
    void* var6 = null;
    int var7 = var0.readUnsignedByte();
               switch (var7) {
                  case 0:
                  case 2:
                     break;
                  case 1:
                  case 5:
                  default:
                     throw new PngException("Bad color type: " + var7, true);
                  case 3:
                     if (var5 == 16) {
                        throw new PngException("Bad bit depth for color type " + var7 + ": " + var5, true);
                     }
                     break;
                  case 4:
                  case 6:
                     if (var5 <= 4) {
                        throw new PngException("Bad bit depth for color type " + var7 + ": " + var5, true);
                     }
               }

    int var8 = var0.readUnsignedByte();
               if (var8 != 0) {
                  throw new PngException("Unrecognized compression method: " + var8, true);
               } else {
    int var9 = var0.readUnsignedByte();
                  if (var9 != 0) {
                     throw new PngException("Unrecognized filter method: " + var9, true);
                  } else {
    int var10 = var0.readUnsignedByte();
                     switch (var10) {
                        case 0:
                        case 1:
                           var2.put("width", Integers.valueOf(var3));
                           var2.put("height", Integers.valueOf(var4));
                           var2.put("bit_depth", Integers.valueOf(var5));
                           var2.put("interlace", Integers.valueOf(var10));
                           var2.put("compression", Integers.valueOf(var8));
                           var2.put("filter", Integers.valueOf(var9));
                           var2.put("color_type", Integers.valueOf(var7));
                           return;
                        default:
                           throw new PngException("Unrecognized interlace method: " + var10, true);
                     }
                  }
               }
            default:
               throw new PngException("Bad bit depth: " + var5, true);
         }
      } else {
         throw new PngException("Bad image size: " + var3 + "x" + var4, true);
      }
   }

    static void read_PLTE(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
      if (var1 == 0) {
         throw new PngException("PLTE chunk cannot be empty", true);
      } else if (var1 % 3 != 0) {
         throw new PngException("PLTE chunk length indivisible by 3: " + var1, true);
      } else {
    int var4 = var1 / 3;
         if (var4 > 256) {
            throw new PngException("Too many palette entries: " + var4, true);
         } else {
            switch (var3.getColorType()) {
               case 0:
               case 4:
                  throw new PngException("PLTE chunk found in grayscale image", false);
               case 3:
                  if (var4 > 2 << var3.getBitDepth() - 1) {
                     throw new PngException("Too many palette entries: " + var4, true);
                  }
               case 1:
               case 2:
               default:
                  std::vector<byte> var5 = new byte[var1];
                  var0.readFully(var5);
                  var2.put("palette", var5);
            }
         }
      }
   }

    static void read_tRNS(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
      switch (var3.getColorType()) {
         case 0:
            checkLength(1951551059, var1, 2);
            var2.put("transparency", std::make_shared<std::vector<int>>(){var0.readUnsignedShort()});
            break;
         case 1:
         default:
            throw new PngException("tRNS prohibited for color type " + var3.getColorType(), true);
         case 2:
            checkLength(1951551059, var1, 6);
            var2.put("transparency", std::make_shared<std::vector<int>>(){var0.readUnsignedShort(), var0.readUnsignedShort(), var0.readUnsignedShort()});
            break;
         case 3:
    int var4 = ((byte[])var3.getProperty("palette", byte[].class, true)).length / 3;
            if (var1 > var4) {
               throw new PngException("Too many transparency palette entries (" + var1 + " > " + var4 + ")", true);
            }

            std::vector<byte> var5 = new byte[var1];
            var0.readFully(var5);
            var2.put("palette_alpha", var5);
      }
   }

    static void read_bKGD(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
      var2.put("background_rgb", switch (var3.getColorType()) {
         case 0, 4 -> {
            checkLength(1649100612, var1, 2);
            yield std::make_shared<std::vector<int>>(){var0.readUnsignedShort()};
         }
         default -> {
            checkLength(1649100612, var1, 6);
            yield std::make_shared<std::vector<int>>(){var0.readUnsignedShort(), var0.readUnsignedShort(), var0.readUnsignedShort()};
         }
         case 3 -> {
            checkLength(1649100612, var1, 1);
            yield std::make_shared<std::vector<int>>(){var0.readUnsignedByte()};
         }
      });
   }

    static void read_cHRM(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1665684045, var1, 32);
      std::vector<float> var3 = std::make_shared<std::array<float, 8>>();

      for (int var4 = 0; var4 < 8; var4++) {
         var3[var4] = var0.readInt() / 100000.0F;
      }

      if (!var2.containsKey("chromaticity")) {
         var2.put("chromaticity", var3);
      }
   }

    static void read_gAMA(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1732332865, var1, 4);
    int var3 = var0.readInt();
      if (var3 == 0) {
         throw new PngException("Meaningless zero gAMA chunk value", false);
      } else {
         if (!var2.containsKey("rendering_intent")) {
            var2.put("gamma", new Float(var3 / 100000.0F));
         }
      }
   }

    static void read_hIST(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
    int var4 = ((byte[])var3.getProperty("palette", byte[].class, true)).length / 3;
      checkLength(1749635924, var1, var4 * 2);
      std::vector<int> var5 = new int[var4];

      for (int var6 = 0; var6 < var4; var6++) {
         var5[var6] = var0.readUnsignedShort();
      }

      var2.put("histogram", var5);
   }

    static void read_iCCP(DataInput var0, int var1, std::unordered_map var2) {
    std::string var3 = readKeyword(var0, var1);
      std::vector<byte> var4 = readCompressed(var0, var1 - var3.length() - 1, true);
      var2.put("icc_profile_name", var3);
      var2.put("icc_profile", var4);
   }

    static void read_pHYs(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1883789683, var1, 9);
    int var3 = var0.readInt();
    int var4 = var0.readInt();
    int var5 = var0.readUnsignedByte();
      if (var5 != 0 && var5 != 1) {
         throw new PngException("Illegal pHYs chunk unit specifier: " + var5, false);
      } else {
         var2.put("pixels_per_unit_x", Integers.valueOf(var3));
         var2.put("pixels_per_unit_y", Integers.valueOf(var4));
         var2.put("unit", Integers.valueOf(var5));
      }
   }

    static void read_sBIT(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
    bool var4 = var3.getColorType() == 3;
    int var5 = var4 ? 3 : var3.getSamples();
      checkLength(1933723988, var1, var5);
    int var6 = var4 ? 8 : var3.getBitDepth();
      std::vector<byte> var7 = new byte[var5];

      for (int var8 = 0; var8 < var5; var8++) {
    uint8_t var9 = var0.readByte();
         if (var9 <= 0 || var9 > var6) {
            throw new PngException("Illegal sBIT sample depth", false);
         }

         var7[var8] = var9;
      }

      var2.put("significant_bits", var7);
   }

    static void read_sRGB(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1934772034, var1, 1);
    uint8_t var3 = var0.readByte();
      var2.put("rendering_intent", Integers.valueOf(var3));
      var2.put("gamma", new Float(0.45455));
      var2.put("chromaticity", std::make_shared<std::vector<float>>(){0.3127F, 0.329F, 0.64F, 0.33F, 0.3F, 0.6F, 0.15F, 0.06F});
   }

    static void read_tIME(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1950960965, var1, 7);
    Calendar var3 = Calendar.getInstance(TIME_ZONE);
      var3.set(
         var0.readUnsignedShort(),
         check(var0.readUnsignedByte(), 1, 12, "month") - 1,
         check(var0.readUnsignedByte(), 1, 31, "day"),
         check(var0.readUnsignedByte(), 0, 23, "hour"),
         check(var0.readUnsignedByte(), 0, 59, "minute"),
         check(var0.readUnsignedByte(), 0, 60, "second")
      );
      var2.put("time", var3.getTime());
   }

    static int check(int var0, int var1, int var2, const std::string& var3) {
      if (var0 >= var1 && var0 <= var2) {
    return var0;
      } else {
         throw new PngException("tIME " + var3 + " value " + var0 + " is out of bounds (" + var1 + "-" + var2 + ")", false);
      }
   }

    static void read_sPLT(DataInput var0, int var1, std::unordered_map var2, PngImage var3) {
    std::string var4 = readKeyword(var0, var1);
    uint8_t var5 = var0.readByte();
      if (var5 != 8 && var5 != 16) {
         throw new PngException("Sample depth must be 8 or 16", false);
      } else {
         var1 -= var4.length() + 2;
         if (var1 % (var5 == 8 ? 6 : 10) != 0) {
            throw new PngException("Incorrect sPLT data length for given sample depth", false);
         } else {
            std::vector<byte> var6 = new byte[var1];
            var0.readFully(var6);
    void* var7 = static_cast<List>(var3).getProperty("suggested_palettes", List.class, false);
            if (var7 == nullptr) {
               var2.put("suggested_palettes", var7 = std::make_unique<ArrayList>());
            }

    Iterator var8 = var7.iterator();

            while (var8.hasNext()) {
               if (var4 == (static_cast<SuggestedPalette>(var8).next()).getName())) {
                  throw new PngException("Duplicate suggested palette name " + var4, false);
               }
            }

            var7.add(new SuggestedPaletteImpl(var4, var5, var6));
         }
      }
   }

    static void readText(int var0, DataInput var1, int var2, std::unordered_map var3, PngImage var4) {
      std::vector<byte> var5 = new byte[var2];
      var1.readFully(var5);
    auto var6 = std::make_shared<DataInputStream>(new ByteArrayInputStream(var5));
    std::string var7 = readKeyword(var6, var2);
    std::string var8 = "ISO-8859-1";
    bool var9 = false;
    bool var10 = true;
    std::string var11 = null;
    std::string var12 = null;
      switch (var0) {
         case 1767135348:
            var8 = "UTF-8";
    uint8_t var13 = var6.readByte();
    uint8_t var14 = var6.readByte();
            if (var13 == 1) {
               var9 = true;
               var10 = false;
               if (var14 != 0) {
                  throw new PngException("Unrecognized " + PngConstants.getChunkName(var0) + " compression method: " + var14, false);
               }
            } else if (var13 != 0) {
               throw new PngException("Illegal " + PngConstants.getChunkName(var0) + " compression flag: " + var13, false);
            }

            var11 = readString(var6, var6.available(), "US-ASCII");
            var12 = readString(var6, var6.available(), "UTF-8");
         case 1950701684:
         default:
            break;
         case 2052348020:
            var9 = true;
      }

    std::string var15;
      if (var9) {
         var15 = new String(readCompressed(var6, var6.available(), var10), var8);
      } else {
         var15 = new String(var5, var5.length - var6.available(), var6.available(), var8);
      }

      if (var15.indexOf(0) >= 0) {
         throw new PngException("Text value contains nullptr", false);
      } else {
    void* var16 = static_cast<List>(var4).getProperty("text_chunks", List.class, false);
         if (var16 == nullptr) {
            var3.put("text_chunks", var16 = std::make_unique<ArrayList>());
         }

         var16.add(new TextChunkImpl(var7, var15, var11, var12, var0));
      }
   }

    static void read_gIFg(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1732855399, var1, 4);
    int var3 = var0.readUnsignedByte();
    int var4 = var0.readUnsignedByte();
    int var5 = var0.readUnsignedShort();
      var2.put("gif_disposal_method", Integers.valueOf(var3));
      var2.put("gif_user_input_flag", Integers.valueOf(var4));
      var2.put("gif_delay_time", Integers.valueOf(var5));
   }

    static void read_oFFs(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1866876531, var1, 9);
    int var3 = var0.readInt();
    int var4 = var0.readInt();
    uint8_t var5 = var0.readByte();
      if (var5 != 0 && var5 != 1) {
         throw new PngException("Illegal oFFs chunk unit specifier: " + var5, false);
      } else {
         var2.put("position_x", Integers.valueOf(var3));
         var2.put("position_y", Integers.valueOf(var4));
         var2.put("position_unit", Integers.valueOf(var5));
      }
   }

    static void read_sCAL(DataInput var0, int var1, std::unordered_map var2) {
      std::vector<byte> var3 = new byte[var1];
      var0.readFully(var3);
    auto var4 = std::make_shared<DataInputStream>(new ByteArrayInputStream(var3));
    uint8_t var5 = var4.readByte();
      if (var5 != 1 && var5 != 2) {
         throw new PngException("Illegal sCAL chunk unit specifier: " + var5, false);
      } else {
    double var6 = readFloatingPoint(var4, var4.available());
    double var8 = readFloatingPoint(var4, var4.available());
         if (!(var6 <= 0.0) && !(var8 <= 0.0)) {
            var2.put("scale_unit", Integers.valueOf(var5));
            var2.put("pixel_width", new Double(var6));
            var2.put("pixel_height", new Double(var8));
         } else {
            throw new PngException("sCAL measurements must be >= 0", false);
         }
      }
   }

    static void read_sTER(DataInput var0, int var1, std::unordered_map var2) {
      checkLength(1934902610, var1, 1);
    uint8_t var3 = var0.readByte();
      switch (var3) {
         case 0:
         case 1:
            var2.put("stereo_mode", Integers.valueOf(var3));
            return;
         default:
            throw new PngException("Unknown sTER mode: " + var3, false);
      }
   }

    static void checkLength(int var0, int var1, int var2) {
      if (var1 != var2) {
         throw new PngException("Bad " + PngConstants.getChunkName(var0) + " chunk length: " + var1 + " (expected " + var2 + ")", true);
      }
   }

   private static byte[] readCompressed(DataInput var0, int var1, boolean var2) throws IOException {
      if (var2) {
    uint8_t var3 = var0.readByte();
         if (var3 != 0) {
            throw new PngException("Unrecognized compression method: " + var3, false);
         }

         var1--;
      }

      std::vector<byte> var9 = new byte[var1];
      var0.readFully(var9);
      std::vector<byte> var4 = std::make_shared<std::array<byte, 4096>>();
    auto var5 = std::make_shared<ByteArrayOutputStream>();
    auto var6 = std::make_shared<Inflater>();
      var6.reset();
      var6.setInput(var9, 0, var1);

      try {
         while (!var6.needsInput()) {
            var5.write(var4, 0, var6.inflate(var4));
         }
      } catch (DataFormatException var8) {
         throw new PngException("Error reading compressed data", var8, false);
      }

      return var5.toByteArray();
   }

    static std::string readString(DataInput var0, int var1, const std::string& var2) {
      return new String(readToNull(var0, var1), var2);
   }

    static std::string readKeyword(DataInput var0, int var1) {
    std::string var2 = readString(var0, var1, "ISO-8859-1");
      if (var2.length() != 0 && var2.length() <= 79) {
    return var2;
      } else {
         throw new PngException("Invalid keyword length: " + var2.length(), false);
      }
   }

   private static byte[] readToNull(DataInput var0, int var1) throws IOException {
    auto var2 = std::make_shared<ByteArrayOutputStream>();

      for (int var3 = 0; var3 < var1; var3++) {
    int var4 = var0.readUnsignedByte();
         if (var4 == 0) {
            return var2.toByteArray();
         }

         var2.write(var4);
      }

      return var2.toByteArray();
   }

    static double readFloatingPoint(DataInput var0, int var1) {
    std::string var2 = readString(var0, var1, "US-ASCII");
    int var3 = Math.max(var2.indexOf(101), var2.indexOf(69));
    double var4 = Double.valueOf(var2.substring(0, var3 < 0 ? var2.length() : var3));
      if (var3 >= 0) {
         var4 *= Math.pow(10.0, Double.valueOf(var2.substring(var3 + 1)));
      }

    return var4;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
