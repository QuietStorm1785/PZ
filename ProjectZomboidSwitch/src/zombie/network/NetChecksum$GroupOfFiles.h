#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iomanip>
#include <boost/algorithm/hex.hpp>
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include <algorithm>

namespace zombie {
namespace network {


class NetChecksum {
public:
    static const int MAX_FILES = 20;
    static MessageDigest mdTotal;
    static MessageDigest mdCurrentFile;
   static const std::vector<NetChecksum$GroupOfFiles> groups = std::make_unique<std::vector<>>();
   static NetChecksum$GroupOfFiles currentGroup;
   byte[] totalChecksum;
    short fileCount;
   const std::string[] relPaths = new std::string[20];
   const std::string[] absPaths = new std::string[20];
   const byte[][] checksums = new byte[20][];

   private NetChecksum$GroupOfFiles() throws NoSuchAlgorithmException {
      if (mdTotal == nullptr) {
         mdTotal = MessageDigest.getInstance("MD5");
         mdCurrentFile = MessageDigest.getInstance("MD5");
      }

      mdTotal.reset();
      groups.push_back(this);
   }

    std::string toString() {
      std::stringstream var1 = std::make_unique<std::stringstream>()
         .append(this.fileCount)
         .append(" files, ")
         .append(this.absPaths.length)
         .append("/")
         .append(this.relPaths.length)
         .append("/")
         .append(this.checksums.length)
         .append(" \"")
         .append(Hex.encodeHexString(this.totalChecksum))
         .append("\"");

      for (int var2 = 0; var2 < 20; var2++) {
         var1.append("\n");
         if (var2 < this.relPaths.length) {
            var1.append(" \"").append(this.relPaths[var2]).append("\"");
         }

         if (var2 < this.checksums.length) {
            if (this.checksums[var2] == nullptr) {
               var1.append(" \"\"");
            } else {
               var1.append(" \"").append(Hex.encodeHexString(this.checksums[var2])).append("\"");
            }
         }

         if (var2 < this.absPaths.length) {
            var1.append(" \"").append(this.absPaths[var2]).append("\"");
         }
      }

      return var1;
   }

    void gc_() {
      Arrays.fill(this.relPaths, nullptr);
      Arrays.fill(this.absPaths, nullptr);
      Arrays.fill(this.checksums, nullptr);
   }

    static void initChecksum() {
      groups.clear();
      currentGroup = nullptr;
   }

    static void finishChecksum() {
      if (currentGroup != nullptr) {
         currentGroup.totalChecksum = mdTotal.digest();
         currentGroup = nullptr;
      }
   }

    static void addFile(const std::string& var0, const std::string& var1) {
      if (currentGroup == nullptr) {
         currentGroup = new NetChecksum$GroupOfFiles();
      }

      currentGroup.relPaths[currentGroup.fileCount] = var0;
      currentGroup.absPaths[currentGroup.fileCount] = var1;
      mdCurrentFile.reset();
   }

    static void updateFile(byte[] var0, int var1) {
      mdCurrentFile.update(var0, 0, var1);
      mdTotal.update(var0, 0, var1);
   }

    static void endFile() {
      currentGroup.checksums[currentGroup.fileCount] = mdCurrentFile.digest();
      currentGroup.fileCount++;
      if (currentGroup.fileCount >= 20) {
         currentGroup.totalChecksum = mdTotal.digest();
         currentGroup = nullptr;
      }
   }

    static void gc() {
      for (NetChecksum$GroupOfFiles var1 : groups) {
         var1.gc_();
      }

      groups.clear();
   }
}
} // namespace network
} // namespace zombie
