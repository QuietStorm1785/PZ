#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/network/NetChecksum/GroupOfFiles.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace network {


class NetChecksum {
public:
    MessageDigest md;
   private const byte[] fileBytes = new byte[1024];
   private const byte[] convertBytes = new byte[1024];
    bool convertLineEndings;

    void reset(bool var1) {
      if (this.md == nullptr) {
         this.md = MessageDigest.getInstance("MD5");
      }

      this.convertLineEndings = var1;
      this.md.reset();
   }

    void addFile(const std::string& var1, const std::string& var2) {
      if (this.md == nullptr) {
         this.md = MessageDigest.getInstance("MD5");
      }

      try (FileInputStream var3 = std::make_shared<FileInputStream>(var2)) {
         GroupOfFiles.addFile(var1, var2);

    int var4;
         while ((var4 = var3.read(this.fileBytes)) != -1) {
            if (this.convertLineEndings) {
    bool var5 = false;
    int var6 = 0;

               for (int var7 = 0; var7 < var4 - 1; var7++) {
                  if (this.fileBytes[var7] == 13 && this.fileBytes[var7 + 1] == 10) {
                     this.convertBytes[var6++] = 10;
                     var5 = true;
                  } else {
                     var5 = false;
                     this.convertBytes[var6++] = this.fileBytes[var7];
                  }
               }

               if (!var5) {
                  this.convertBytes[var6++] = this.fileBytes[var4 - 1];
               }

               this.md.update(this.convertBytes, 0, var6);
               GroupOfFiles.updateFile(this.convertBytes, var6);
            } else {
               this.md.update(this.fileBytes, 0, var4);
               GroupOfFiles.updateFile(this.fileBytes, var4);
            }
         }

         GroupOfFiles.endFile();
      } catch (Exception var10) {
         ExceptionLogger.logException(var10);
      }
   }

    std::string checksumToString() {
      byte[] var1 = this.md.digest();
    std::stringstream var2 = new std::stringstream();

      for (int var3 = 0; var3 < var1.length; var3++) {
         var2.append(int.toString((var1[var3] & 255) + 256, 16).substr(1));
      }

      return var2;
   }

    std::string toString() {
    std::stringstream var1 = new std::stringstream();

      for (GroupOfFiles var3 : GroupOfFiles.groups) {
    std::string var4 = var3;
         var1.append("\n").append(var4);
         if (GameClient.bClient) {
            NetChecksum.comparer.sendError(GameClient.connection, var4);
         }
      }

      return var1;
   }
}
} // namespace network
} // namespace zombie
