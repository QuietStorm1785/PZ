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


class FuncMapping {
:
    static FuncMapping[] mapping_P = new FuncMapping[]{std::make_unique<Mapping0>()};

   abstract void free_info(Object var1);

   abstract void free_look(Object var1);

   abstract int inverse(Block var1, Object var2);

   abstract Object look(DspState var1, InfoMode var2, Object var3);

   abstract void pack(Info var1, Object var2, Buffer var3);

   abstract Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
