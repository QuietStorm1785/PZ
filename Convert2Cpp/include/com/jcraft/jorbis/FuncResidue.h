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


class FuncResidue {
public:
   public static std::vector<FuncResidue> residue_P = std::make_shared<std::vector<FuncResidue>>(){std::make_unique<Residue0>(), std::make_unique<Residue1>(), std::make_unique<Residue2>()};

   abstract void free_info(Object var1);

   abstract void free_look(Object var1);

   abstract int inverse(Block var1, Object var2, float[][] var3, int[] var4, int var5);

   abstract Object look(DspState var1, InfoMode var2, Object var3);

   abstract void pack(Object var1, Buffer var2);

   abstract Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
