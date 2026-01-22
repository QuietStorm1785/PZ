#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/AddCoopPlayer/Stage.h"

namespace zombie {
namespace util {


// $VF: synthetic class
class AddCoopPlayer {
public:
   static {
      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.Init.ordinal()] = 1;
      } catch (NoSuchFieldError var8) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.ReceiveClientConnect.ordinal()] = 2;
      } catch (NoSuchFieldError var7) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.StartMapLoading.ordinal()] = 3;
      } catch (NoSuchFieldError var6) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.CheckMapLoading.ordinal()] = 4;
      } catch (NoSuchFieldError var5) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.SendPlayerConnect.ordinal()] = 5;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.ReceivePlayerConnect.ordinal()] = 6;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.AddToWorld.ordinal()] = 7;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$util$AddCoopPlayer$Stage[Stage.Finished.ordinal()] = 8;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace util
} // namespace zombie
