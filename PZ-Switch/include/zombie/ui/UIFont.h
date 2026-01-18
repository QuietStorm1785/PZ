#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

enum class UIFont {
 Small, Medium, Large, Massive, MainMenu1, MainMenu2, Cred1, Cred2, NewSmall,
 NewMedium, NewLarge, Code, MediumNew, AutoNormSmall, AutoNormMedium,
 AutoNormLarge, Dialogue, Intro, Handwritten, DebugConsole, Title;

 static UIFont FromString(const std::string &str){try {return valueOf();}
catch (Exception exception) {
 return nullptr;
}
} // namespace ui
} // namespace zombie
} // namespace ui
} // namespace zombie
