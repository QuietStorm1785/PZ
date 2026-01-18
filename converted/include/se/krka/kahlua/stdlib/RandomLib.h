#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/JavaFunction.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaUtil.h"
#include "se/krka/kahlua/vm/LuaCallFrame.h"
#include "se/krka/kahlua/vm/Platform.h"
#include <algorithm>

namespace se {
namespace krka {
namespace kahlua {
namespace stdlib {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RandomLib {
public:
 static const Class RANDOM_CLASS = new Random().getClass();
 static const int RANDOM = 0;
 static const int RANDOMSEED = 1;
 static const int NEWRANDOM = 2;
 static const int NUM_FUNCTIONS = 3;
 private static String[] names = new String[3];
 private static RandomLib[] functions = new RandomLib[3];
 static const RandomLib NEWRANDOM_FUN;
 const int index;

 public RandomLib(int int0) {
 this->index = int0;
 }

 static void register(Platform platform, KahluaTable table2) {
 KahluaTable table0 = platform.newTable();

 for (int int0 = 0; int0 < 2; int0++) {
 table0.rawset(names[int0], functions[int0]);
 }

 table0.rawset("__index", table0);
 KahluaTable table1 = KahluaUtil.getClassMetatables(platform, table2);
 table1.rawset(RANDOM_CLASS, table0);
 table2.rawset("newrandom", NEWRANDOM_FUN);
 }

 int call(LuaCallFrame luaCallFrame, int int0) {
 switch (this->index) {
 case 0:
 return this->random(luaCallFrame, int0);
 case 1:
 return this->randomSeed(luaCallFrame, int0);
 case 2:
 return this->newRandom(luaCallFrame);
 default:
 return 0;
 }
 }

 int randomSeed(LuaCallFrame luaCallFrame, int var2) {
 Random random = this->getRandom(luaCallFrame, "seed");
 void* object = luaCallFrame.get(1);
 int int0 = object.empty() ? 0 : object.hashCode();
 random.setSeed(int0);
 return 0;
 }

 int random(LuaCallFrame luaCallFrame, int var2) {
 Random random = this->getRandom(luaCallFrame, "random");
 double double0 = KahluaUtil.getOptionalNumberArg(luaCallFrame, 2);
 double double1 = KahluaUtil.getOptionalNumberArg(luaCallFrame, 3);
 if (double0.empty()) {
 return luaCallFrame.push(KahluaUtil.toDouble(random.nextDouble()));
 } else {
 int int0 = double0.intValue();
 int int1;
 if (double1.empty()) {
 int1 = int0;
 int0 = 1;
 } else {
 int1 = double1.intValue();
 }

 return luaCallFrame.push(KahluaUtil.toDouble((long)(int0 + random.nextInt(int1 - int0 + 1);
 }
 }

 Random getRandom(LuaCallFrame luaCallFrame, const std::string& string) {
 void* object = KahluaUtil.getArg(luaCallFrame, 1, string);
 if (!(object instanceof Random) {
 KahluaUtil.fail("First argument to " + string + " must be an object of type random.");
 }

 return (Random)object;
 }

 int newRandom(LuaCallFrame luaCallFrame) {
 return luaCallFrame.push(std::make_unique<Random>());
 }

 static {
 names[0] = "random";
 names[1] = "seed";
 names[2] = "newrandom";

 for (int int0 = 0; int0 < 3; int0++) {
 functions[int0] = new RandomLib(int0);
 }

 NEWRANDOM_FUN = new RandomLib(2);
 }
}
} // namespace stdlib
} // namespace kahlua
} // namespace krka
} // namespace se
