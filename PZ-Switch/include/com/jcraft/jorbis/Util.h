#pragma once
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

class Util {
public:
 static int icount(int int1) {
 int int0 = 0;

 while (int1 != 0) {
 int0 += int1 & 1;
 int1 >> >= 1;
 }

 return int0;
 }

 static int ilog(int int1) {
 int int0 = 0;

 while (int1 != 0) {
 int0++;
 int1 >> >= 1;
 }

 return int0;
 }

 static int ilog2(int int1) {
 int int0 = 0;

 while (int1 > 1) {
 int0++;
 int1 >> >= 1;
 }

 return int0;
 }
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
