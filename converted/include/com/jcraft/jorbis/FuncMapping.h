#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/jcraft/jogg/Buffer.h"

namespace com {
namespace jcraft {
namespace jorbis {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class FuncMapping {
public:
 public static FuncMapping[] mapping_P = new FuncMapping[]{std::make_unique<Mapping0>()};

 void free_info(Object var1);

 void free_look(Object var1);

 int inverse(Block var1, Object var2);

 Object look(DspState var1, InfoMode var2, Object var3);

 void pack(Info var1, Object var2, Buffer var3);

 Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
