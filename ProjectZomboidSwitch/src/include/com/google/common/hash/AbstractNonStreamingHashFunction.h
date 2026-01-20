#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/AbstractNonStreamingHashFunction/BufferingHasher.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractNonStreamingHashFunction {
public:
    Hasher newHasher() {
      return std::make_shared<BufferingHasher>(this, 32);
   }

    Hasher newHasher(int expectedInputSize) {
      Preconditions.checkArgument(expectedInputSize >= 0);
      return std::make_shared<BufferingHasher>(this, expectedInputSize);
   }

   public <T> HashCode hashObject(T instance, Funnel<? super T> funnel) {
      return this.newHasher().putObject(instance, funnel).hash();
   }

    HashCode hashUnencodedChars(CharSequence input) {
    int len = input.length();
    Hasher hasher = this.newHasher(len * 2);

      for (int i = 0; i < len; i++) {
         hasher.putChar(input.charAt(i));
      }

      return hasher.hash();
   }

    HashCode hashString(CharSequence input, Charset charset) {
      return this.hashBytes(input.getBytes(charset));
   }

    HashCode hashInt(int input) {
      return this.newHasher(4).putInt(input).hash();
   }

    HashCode hashLong(long input) {
      return this.newHasher(8).putLong(input).hash();
   }

    HashCode hashBytes(byte[] input) {
      return this.hashBytes(input, 0, input.length);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
