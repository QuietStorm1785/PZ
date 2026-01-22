#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {

enum class DebugType {
   Packet,
   NetworkFileDebug,
   Network,
   General,
   Lua,
   Mod,
   Sound,
   Zombie,
   Combat,
   Objects,
   Fireplace,
   Radio,
   MapLoading,
   Clothing,
   Animation,
   Asset,
   Script,
   Shader,
   Input,
   Recipe,
   ActionSystem,
   IsoRegion,
   UnitTests,
   FileIO,
   Multiplayer,
   Ownership,
   Death,
   Damage,
   Statistic,
   Vehicle,
   Voice,
   Checksum;

    static bool Do(DebugType var0) {
      return DebugLog.isEnabled(var0);
   }
}
} // namespace debug
} // namespace zombie
