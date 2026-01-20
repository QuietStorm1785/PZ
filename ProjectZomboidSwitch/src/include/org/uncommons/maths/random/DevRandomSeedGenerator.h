#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class DevRandomSeedGenerator {
public:
    static const File DEV_RANDOM = std::make_shared<File>("/dev/random");

   public byte[] generateSeed(int length) throws SeedException {
    FileInputStream file = nullptr;

      byte[] var18;
      try {
         file = std::make_shared<FileInputStream>(DEV_RANDOM);
         byte[] randomSeed = new byte[length];
    int count = 0;

         while (count < length) {
    int bytesRead = file.read(randomSeed, count, length - count);
            if (bytesRead == -1) {
               throw SeedException("EOF encountered reading random data.");
            }

            count += bytesRead;
         }

         var18 = randomSeed;
      } catch (IOException var15) {
         throw SeedException("Failed reading from " + DEV_RANDOM.getName(), var15);
      } catch (SecurityException var16) {
         throw SeedException("SecurityManager prevented access to " + DEV_RANDOM.getName(), var16);
      } finally {
         if (file != nullptr) {
            try {
               file.close();
            } catch (IOException var14) {
            }
         }
      }

    return var18;
   }

    std::string toString() {
      return "/dev/random";
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
