#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ui {

enum class UIFont {
   Small,
   Medium,
   Large,
   Massive,
   MainMenu1,
   MainMenu2,
   Cred1,
   Cred2,
   NewSmall,
   NewMedium,
   NewLarge,
   Code,
   MediumNew,
   AutoNormSmall,
   AutoNormMedium,
   AutoNormLarge,
   Dialogue,
   Intro,
   Handwritten,
   DebugConsole,
   Title;

    static UIFont FromString(const std::string& var0) {
      try {
    return valueOf();
      } catch (Exception var2) {
    return nullptr;
      }
   }
}
} // namespace ui
} // namespace zombie
