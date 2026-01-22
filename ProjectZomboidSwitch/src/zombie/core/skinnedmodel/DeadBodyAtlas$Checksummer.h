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
#include "zombie/core/ImmutableColor.h"
#include "zombie/iso/IsoGridSquare/ResultLight.h"

namespace zombie {
namespace core {
namespace skinnedmodel {


class DeadBodyAtlas {
public:
    MessageDigest md;
    const std::stringstream sb = new std::stringstream();

   private DeadBodyAtlas$Checksummer() {
   }

    void reset() {
      if (this.md == nullptr) {
         this.md = MessageDigest.getInstance("MD5");
      }

      this.md.reset();
   }

    void update(uint8_t var1) {
      this.md.update(var1);
   }

    void update(bool var1) {
      this.md.update((byte)(var1 ? 1 : 0));
   }

    void update(int var1) {
      this.md.update((byte)(var1 & 0xFF));
      this.md.update((byte)(var1 >> 8 & 0xFF));
      this.md.update((byte)(var1 >> 16 & 0xFF));
      this.md.update((byte)(var1 >> 24 & 0xFF));
   }

    void update(const std::string& var1) {
      if (var1 != nullptr && !var1.empty()) {
         this.md.update(var1.getBytes());
      }
   }

    void update(ImmutableColor var1) {
      this.update((byte)(var1.r * 255.0F));
      this.update((byte)(var1.g * 255.0F));
      this.update((byte)(var1.b * 255.0F));
   }

    void update(ResultLight var1, float var2, float var3, float var4) {
      if (var1 != nullptr && var1.radius > 0) {
         this.update((int)(var1.x - var2));
         this.update((int)(var1.y - var3));
         this.update((int)(var1.z - var4));
         this.update((byte)(var1.r * 255.0F));
         this.update((byte)(var1.g * 255.0F));
         this.update((byte)(var1.b * 255.0F));
         this.update((byte)var1.radius);
      }
   }

    std::string checksumToString() {
      byte[] var1 = this.md.digest();
      this.sb.setLength(0);

      for (int var2 = 0; var2 < var1.length; var2++) {
         this.sb.append(var1[var2] & 255);
      }

      return this.sb;
   }
}
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
