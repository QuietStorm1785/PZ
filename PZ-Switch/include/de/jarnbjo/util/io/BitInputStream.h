#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace util {
namespace io {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BitInputStream {
public:
 virtual ~BitInputStream() = default;
 int LITTLE_ENDIAN = 0;
 int BIG_ENDIAN = 1;

 bool getBit();

 int getInt(int var1);

 int getSignedInt(int var1);

 int getInt(HuffmanNode var1);

 int readSignedRice(int var1);

 void readSignedRice(int var1, int[] var2, int var3, int var4);

 long getLong(int var1);

 void align();

 void setEndian(int var1);
}
} // namespace io
} // namespace util
} // namespace jarnbjo
} // namespace de
