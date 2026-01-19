#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sixlegs {
namespace png {

class PngConstants {
:
    static const long SIGNATURE = -8552249625308161526L;
    static const int IHDR = 1229472850;
    static const int PLTE = 1347179589;
    static const int IDAT = 1229209940;
    static const int IEND = 1229278788;
    static const int bKGD = 1649100612;
    static const int cHRM = 1665684045;
    static const int gAMA = 1732332865;
    static const int hIST = 1749635924;
    static const int iCCP = 1766015824;
    static const int iTXt = 1767135348;
    static const int pHYs = 1883789683;
    static const int sBIT = 1933723988;
    static const int sPLT = 1934642260;
    static const int sRGB = 1934772034;
    static const int tEXt = 1950701684;
    static const int tIME = 1950960965;
    static const int tRNS = 1951551059;
    static const int zTXt = 2052348020;
    static const int oFFs = 1866876531;
    static const int pCAL = 1883455820;
    static const int sCAL = 1933787468;
    static const int gIFg = 1732855399;
    static const int gIFx = 1732855416;
    static const int sTER = 1934902610;
    static const std::string BIT_DEPTH = "bit_depth";
    static const std::string COLOR_TYPE = "color_type";
    static const std::string COMPRESSION = "compression";
    static const std::string FILTER = "filter";
    static const std::string GAMMA = "gamma";
    static const std::string WIDTH = "width";
    static const std::string HEIGHT = "height";
    static const std::string INTERLACE = "interlace";
    static const std::string PALETTE = "palette";
    static const std::string PALETTE_ALPHA = "palette_alpha";
    static const std::string TRANSPARENCY = "transparency";
    static const std::string BACKGROUND = "background_rgb";
    static const std::string PIXELS_PER_UNIT_X = "pixels_per_unit_x";
    static const std::string PIXELS_PER_UNIT_Y = "pixels_per_unit_y";
    static const std::string RENDERING_INTENT = "rendering_intent";
    static const std::string SIGNIFICANT_BITS = "significant_bits";
    static const std::string TEXT_CHUNKS = "text_chunks";
    static const std::string TIME = "time";
    static const std::string UNIT = "unit";
    static const std::string CHROMATICITY = "chromaticity";
    static const std::string ICC_PROFILE = "icc_profile";
    static const std::string ICC_PROFILE_NAME = "icc_profile_name";
    static const std::string HISTOGRAM = "histogram";
    static const std::string SUGGESTED_PALETTES = "suggested_palettes";
    static const std::string GIF_DISPOSAL_METHOD = "gif_disposal_method";
    static const std::string GIF_USER_INPUT_FLAG = "gif_user_input_flag";
    static const std::string GIF_DELAY_TIME = "gif_delay_time";
    static const std::string SCALE_UNIT = "scale_unit";
    static const std::string PIXEL_WIDTH = "pixel_width";
    static const std::string PIXEL_HEIGHT = "pixel_height";
    static const std::string POSITION_UNIT = "position_unit";
    static const std::string STEREO_MODE = "stereo_mode";
    static const int COLOR_TYPE_GRAY = 0;
    static const int COLOR_TYPE_GRAY_ALPHA = 4;
    static const int COLOR_TYPE_PALETTE = 3;
    static const int COLOR_TYPE_RGB = 2;
    static const int COLOR_TYPE_RGB_ALPHA = 6;
    static const int INTERLACE_NONE = 0;
    static const int INTERLACE_ADAM7 = 1;
    static const int FILTER_BASE = 0;
    static const int COMPRESSION_BASE = 0;
    static const int UNIT_UNKNOWN = 0;
    static const int UNIT_METER = 1;
    static const int SRGB_PERCEPTUAL = 0;
    static const int SRGB_RELATIVE_COLORIMETRIC = 1;
    static const int SRGB_SATURATION_PRESERVING = 2;
    static const int SRGB_ABSOLUTE_COLORIMETRIC = 3;
    static const std::string POSITION_X = "position_x";
    static const std::string POSITION_Y = "position_y";
    static const int POSITION_UNIT_PIXEL = 0;
    static const int POSITION_UNIT_MICROMETER = 1;
    static const int SCALE_UNIT_METER = 1;
    static const int SCALE_UNIT_RADIAN = 2;
    static const int STEREO_MODE_CROSS = 0;
    static const int STEREO_MODE_DIVERGING = 1;

    static bool isAncillary(int var0) {
      return (var0 & 536870912) != 0;
   }

    static bool isPrivate(int var0) {
      return (var0 & 2097152) != 0;
   }

    static bool isReserved(int var0) {
      return (var0 & 8192) != 0;
   }

    static bool isSafeToCopy(int var0) {
      return (var0 & 32) != 0;
   }

    static std::string getChunkName(int var0) {
      return "" + (char)(var0 >>> 24 & 0xFF) + (char)(var0 >>> 16 & 0xFF) + (char)(var0 >>> 8 & 0xFF) + (char)(var0 & 0xFF);
   }

    static int getChunkType(std::string_view var0) {
      return (var0.charAt(0) & 0xFF) << 24 | (var0.charAt(1) & 0xFF) << 16 | (var0.charAt(2) & 0xFF) << 8 | var0.charAt(3) & 0xFF;
   }
}
} // namespace png
} // namespace sixlegs
} // namespace com
