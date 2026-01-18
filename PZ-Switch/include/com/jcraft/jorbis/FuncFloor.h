#pragma once
#include "com/jcraft/jogg/Buffer.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FuncFloor {
public:
public
 static FuncFloor[] floor_P =
 new FuncFloor[]{std::make_unique<Floor0>(), std::make_unique<Floor1>()};

 int forward(Block var1, Object var2, float[] var3, float[] var4,
 Object var5);

 void free_info(Object var1);

 void free_look(Object var1);

 void free_state(Object var1);

 Object inverse1(Block var1, Object var2, Object var3);

 int inverse2(Block var1, Object var2, Object var3, float[] var4);

 Object look(DspState var1, InfoMode var2, Object var3);

 void pack(Object var1, Buffer var2);

 Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
