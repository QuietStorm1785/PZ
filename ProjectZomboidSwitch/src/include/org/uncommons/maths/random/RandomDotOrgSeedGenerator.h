#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/net/URL.h"
#include "java/net/URLConnection.h"
#include "java/text/MessageFormat.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace org {
namespace uncommons {
namespace maths {
namespace random {


class RandomDotOrgSeedGenerator {
public:
    static const std::string BASE_URL = "https://www.random.org";
    static const std::string RANDOM_URL = "https://www.random.org/integers/?num={0,number,0}&min=0&max=255&col=1&base=16&format=plain&rnd=new";
    static const std::string USER_AGENT = RandomDotOrgSeedGenerator.class.getName();
    static const int MAX_REQUEST_SIZE = 10000;
    static const Lock cacheLock = std::make_shared<ReentrantLock>();
   private static byte[] cache = new byte[1024];
    static int cacheOffset = cache.length;

   public byte[] generateSeed(int length) throws SeedException {
      byte[] seedData = new byte[length];

      try {
         cacheLock.lock();
    int count = 0;

         while (count < length) {
            if (cacheOffset < cache.length) {
    int numberOfBytes = Math.min(length - count, cache.length - cacheOffset);
               System.arraycopy(cache, cacheOffset, seedData, count, numberOfBytes);
               count += numberOfBytes;
               cacheOffset += numberOfBytes;
            } else {
               this.refreshCache(length - count);
            }
         }
      } catch (IOException var9) {
         throw SeedException("Failed downloading bytes from https://www.random.org", var9);
      } catch (SecurityException var10) {
         throw SeedException("SecurityManager prevented access to https://www.random.org", var10);
      } finally {
         cacheLock.unlock();
      }

    return seedData;
   }

    void refreshCache(int requiredBytes) {
    int numberOfBytes = Math.max(requiredBytes, cache.length);
      numberOfBytes = Math.min(numberOfBytes, 10000);
      if (numberOfBytes != cache.length) {
         cache = new byte[numberOfBytes];
         cacheOffset = numberOfBytes;
      }

      URL url = std::make_shared<URL>(
         MessageFormat.format("https://www.random.org/integers/?num={0,number,0}&min=0&max=255&col=1&base=16&format=plain&rnd=new", numberOfBytes)
      );
    URLConnection connection = url.openConnection();
      connection.setRequestProperty("User-Agent", USER_AGENT);
    BufferedReader reader = std::make_shared<BufferedReader>(std::make_shared<InputStreamReader>(connection.getInputStream()));

      try {
    int index = -1;

         for (std::string line = reader.readLine(); line != nullptr; line = reader.readLine()) {
            cache[++index] = (byte)int.parseInt(line, 16);
         }

         if (index < cache.length - 1) {
            throw IOException("Insufficient data received.");
         }

         cacheOffset = 0;
      } finally {
         reader.close();
      }
   }

    std::string toString() {
      return "https://www.random.org";
   }
}
} // namespace random
} // namespace maths
} // namespace uncommons
} // namespace org
