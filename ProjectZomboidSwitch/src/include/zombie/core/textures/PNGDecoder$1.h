#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/PNGDecoder/Format.h"

namespace zombie {
namespace core {
namespace textures {


// $VF: synthetic class
class PNGDecoder {
public:
   static {
      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.ABGR.ordinal()] = 1;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.RGBA.ordinal()] = 2;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.BGRA.ordinal()] = 3;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.RGB.ordinal()] = 4;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.LUMINANCE.ordinal()] = 5;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.ALPHA.ordinal()] = 6;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$textures$PNGDecoder$Format[Format.LUMINANCE_ALPHA.ordinal()] = 7;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace textures
} // namespace core
} // namespace zombie
