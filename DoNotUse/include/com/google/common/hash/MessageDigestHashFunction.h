#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/MessageDigestHashFunction/MessageDigestHasher.h"
#include "com/google/common/hash/MessageDigestHashFunction/SerializedForm.h"
#include "java/security/MessageDigest.h"
#include "java/security/NoSuchAlgorithmException.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class MessageDigestHashFunction : public AbstractStreamingHashFunction {
public:
    const MessageDigest prototype;
    const int bytes;
    const bool supportsClone;
    const std::string toString;

   MessageDigestHashFunction(std::string algorithmName, std::string toString) {
      this.prototype = getMessageDigest(algorithmName);
      this.bytes = this.prototype.getDigestLength();
      this.toString = (std::string)Preconditions.checkNotNull(toString);
      this.supportsClone = supportsClone(this.prototype);
   }

   MessageDigestHashFunction(std::string algorithmName, int bytes, std::string toString) {
      this.toString = (std::string)Preconditions.checkNotNull(toString);
      this.prototype = getMessageDigest(algorithmName);
    int maxLength = this.prototype.getDigestLength();
      Preconditions.checkArgument(bytes >= 4 && bytes <= maxLength, "bytes (%s) must be >= 4 and < %s", bytes, maxLength);
      this.bytes = bytes;
      this.supportsClone = supportsClone(this.prototype);
   }

    static bool supportsClone(MessageDigest digest) {
      try {
         digest.clone();
    return true;
      } catch (CloneNotSupportedException var2) {
    return false;
      }
   }

    int bits() {
      return this.bytes * 8;
   }

    std::string toString() {
      return this.toString;
   }

    static MessageDigest getMessageDigest(const std::string& algorithmName) {
      try {
         return MessageDigest.getInstance(algorithmName);
      } catch (NoSuchAlgorithmException var2) {
         throw AssertionError(var2);
      }
   }

    Hasher newHasher() {
      if (this.supportsClone) {
         try {
            return std::make_shared<MessageDigestHasher>((MessageDigest)this.prototype.clone(), this.bytes, nullptr);
         } catch (CloneNotSupportedException var2) {
         }
      }

      return std::make_shared<MessageDigestHasher>(getMessageDigest(this.prototype.getAlgorithm()), this.bytes, nullptr);
   }

    void* writeReplace() {
      return std::make_shared<SerializedForm>(this.prototype.getAlgorithm(), this.bytes, this.toString, nullptr);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
