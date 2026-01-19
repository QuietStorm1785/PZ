#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class MD5Checksum {
public:
 static long createChecksum(std::string_view string) {
 File file = new File(string);
 if (!file.exists()) {
 return 0L;
 } else {
 FileInputStream fileInputStream = new FileInputStream(string);
 CRC32 crc32 = new CRC32();
 byte[] bytes = new byte[1024];

 int int0;
 while ((int0 = fileInputStream.read(bytes) != -1) {
 crc32.update(bytes, 0, int0);
 }

 long long0 = crc32.getValue();
 fileInputStream.close();
 return long0;
 }
 }

 static void main(String[] var0) {}
}
} // namespace network
} // namespace zombie
