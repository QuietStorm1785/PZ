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

class FuncResidue {
public:
public
 static FuncResidue[] residue_P = new FuncResidue[]{
 std::make_unique<Residue0>(), std::make_unique<Residue1>(),
 std::make_unique<Residue2>()};

 void free_info(Object var1);

 void free_look(Object var1);

 int inverse(Block var1, Object var2, float[][] var3, int[] var4,
 int var5);

 Object look(DspState var1, InfoMode var2, Object var3);

 void pack(Object var1, Buffer var2);

 Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
