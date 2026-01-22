#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/MacHashFunction/MacHasher.h"
#include "java/security/InvalidKeyException.h"
#include "java/security/Key.h"
#include "java/security/NoSuchAlgorithmException.h"
#include "javax/crypto/Mac.h"

namespace com {
namespace google {
namespace common {
namespace hash {


class MacHashFunction : public AbstractStreamingHashFunction {
public:
    const Mac prototype;
    const Key key;
    const std::string toString;
    const int bits;
    const bool supportsClone;

   MacHashFunction(std::string algorithmName, Key key, std::string toString) {
      this.prototype = getMac(algorithmName, key);
      this.key = (Key)Preconditions.checkNotNull(key);
      this.toString = (std::string)Preconditions.checkNotNull(toString);
      this.bits = this.prototype.getMacLength() * 8;
      this.supportsClone = supportsClone(this.prototype);
   }

    int bits() {
      return this.bits;
   }

    static bool supportsClone(Mac mac) {
      try {
         mac.clone();
    return true;
      } catch (CloneNotSupportedException var2) {
    return false;
      }
   }

    static Mac getMac(const std::string& algorithmName, Key key) {
      try {
    Mac mac = Mac.getInstance(algorithmName);
         mac.init(key);
    return mac;
      } catch (NoSuchAlgorithmException var3) {
         throw IllegalStateException(var3);
      } catch (InvalidKeyException var4) {
         throw IllegalArgumentException(var4);
      }
   }

    Hasher newHasher() {
      if (this.supportsClone) {
         try {
            return std::make_shared<MacHasher>((Mac)this.prototype.clone(), nullptr);
         } catch (CloneNotSupportedException var2) {
         }
      }

      return std::make_shared<MacHasher>(getMac(this.prototype.getAlgorithm(), this.key), nullptr);
   }

    std::string toString() {
      return this.toString;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
