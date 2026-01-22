#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class MD5Checksum {
public:
    static long createChecksum(const std::string& var0) {
    File var1 = std::make_shared<File>(var0);
      if (!var1.exists()) {
    return 0L;
      } else {
    FileInputStream var2 = std::make_shared<FileInputStream>(var0);
    CRC32 var3 = std::make_shared<CRC32>();
         byte[] var4 = new byte[1024];

    int var5;
         while ((var5 = var2.read(var4)) != -1) {
            var3.update(var4, 0, var5);
         }

    long var6 = var3.getValue();
         var2.close();
    return var6;
      }
   }

    static void main(std::string[] var0) {
   }
}
} // namespace network
} // namespace zombie
