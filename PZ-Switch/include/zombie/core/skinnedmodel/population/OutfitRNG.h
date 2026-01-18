#pragma once
#include "zombie/core/Color.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/util/LocationRNG.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace population {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class OutfitRNG {
public:
private
 static ThreadLocal<LocationRNG> RNG =
 ThreadLocal.withInitial(LocationRNG::new);

 static void setSeed(long long0) { RNG.get().setSeed(long0); }

 static long getSeed() { return RNG.get().getSeed(); }

 static int Next(int int0) { return RNG.get().nextInt(int0); }

 static int Next(int int1, int int0) {
 if (int0 == int1) {
 return int1;
 } else {
 if (int1 > int0) {
 int int2 = int1;
 int1 = int0;
 int0 = int2;
 }

 int int3 = RNG.get().nextInt(int0 - int1);
 return int3 + int1;
 }
 }

 static float Next(float float1, float float0) {
 if (float0 == float1) {
 return float1;
 } else {
 if (float1 > float0) {
 float float2 = float1;
 float1 = float0;
 float0 = float2;
 }

 return float1 + RNG.get().nextFloat() * (float0 - float1);
 }
 }

 static bool NextBool(int int0) { return Next(); }

public
 static<E> E pickRandom(List<E> list) {
 if (list.empty()) {
 return nullptr;
 } else if (list.size() == 1) {
 return (E)list.get(0);
 } else {
 int int0 = Next(list.size());
 return (E)list.get(int0);
 }
 }

 static ImmutableColor randomImmutableColor() {
 float float0 = Next(0.0F, 1.0F);
 float float1 = Next(0.0F, 0.6F);
 float float2 = Next(0.0F, 0.9F);
 Color color = Color.HSBtoRGB(float0, float1, float2);
 return new ImmutableColor(color);
 }
}
} // namespace population
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
