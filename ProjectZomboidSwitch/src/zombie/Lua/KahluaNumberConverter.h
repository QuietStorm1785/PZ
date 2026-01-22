#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/converter/KahluaConverterManager.h"
#include "zombie/Lua/KahluaNumberConverter/1.h"
#include "zombie/Lua/KahluaNumberConverter/2.h"
#include "zombie/Lua/KahluaNumberConverter/3.h"
#include "zombie/Lua/KahluaNumberConverter/4.h"
#include "zombie/Lua/KahluaNumberConverter/5.h"
#include "zombie/Lua/KahluaNumberConverter/6.h"
#include "zombie/Lua/KahluaNumberConverter/7.h"
#include "zombie/Lua/KahluaNumberConverter/NumberToLuaConverter.h"

namespace zombie {
namespace Lua {


class KahluaNumberConverter {
public:
    private KahluaNumberConverter() {
   }

    static void install(KahluaConverterManager var0) {
      var0.addLuaConverter(std::make_unique<1>());
      var0.addLuaConverter(std::make_unique<2>());
      var0.addLuaConverter(std::make_unique<3>());
      var0.addLuaConverter(std::make_unique<4>());
      var0.addLuaConverter(std::make_unique<5>());
      var0.addLuaConverter(std::make_unique<6>());
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(double.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(float.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(int.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(int64_t.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(int16_t.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(uint8_t.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(char.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(double.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(float.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(int.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(long.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(short.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(byte.class));
      var0.addJavaConverter(std::make_shared<NumberToLuaConverter>(char.class));
      var0.addJavaConverter(std::make_unique<7>());
   }
}
} // namespace Lua
} // namespace zombie
