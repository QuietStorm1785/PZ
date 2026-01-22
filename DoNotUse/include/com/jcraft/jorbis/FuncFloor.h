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


class FuncFloor {
public:
   public static FuncFloor[] floor_P = new FuncFloor[]{std::make_unique<Floor0>(), std::make_unique<Floor1>()};

   abstract int forward(Block var1, Object var2, float[] var3, float[] var4, Object var5);

   abstract void free_info(Object var1);

   abstract void free_look(Object var1);

   abstract void free_state(Object var1);

   abstract Object inverse1(Block var1, Object var2, Object var3);

   abstract int inverse2(Block var1, Object var2, Object var3, float[] var4);

   abstract Object look(DspState var1, InfoMode var2, Object var3);

   abstract void pack(Object var1, Buffer var2);

   abstract Object unpack(Info var1, Buffer var2);
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
