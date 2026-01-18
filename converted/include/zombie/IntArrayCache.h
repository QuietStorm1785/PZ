#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/map/hash/TIntObjectHashMap.h"
#include <algorithm>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class IntArrayCache {
public:
 static IntArrayCache instance = new IntArrayCache();
 TIntObjectHashMap<Stack<Integer[]>> Map = std::make_unique<TIntObjectHashMap<>>();

 void Init() {
 for (int int0 = 0; int0 < 100; int0++) {
 std::stack stack = new Stack();

 for (int int1 = 0; int1 < 1000; int1++) {
 stack.push(new Integer[int0]);
 }
 }
 }

 void put(Integer[] integers) {
 if (this->Map.containsKey(integers.length) {
 this->Map.get(integers.length).push(integers);
 } else {
 std::stack stack = new Stack();
 stack.push(integers);
 this->Map.put(integers.length, stack);
 }
 }

 public Integer[] get(int int0) {
 if (this->Map.containsKey(int0) {
 std::stack stack = this->Map.get(int0);
 if (!stack.empty()) {
 return (Integer[])stack.pop();
 }
 }

 return new Integer[int0];
 }
}
} // namespace zombie
