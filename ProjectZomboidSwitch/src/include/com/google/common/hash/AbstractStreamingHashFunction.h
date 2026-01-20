#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace hash {


class AbstractStreamingHashFunction {
public:
   public <T> HashCode hashObject(T instance, Funnel<? super T> funnel) {
      return this.newHasher().putObject(instance, funnel).hash();
   }

    HashCode hashUnencodedChars(CharSequence input) {
      return this.newHasher().putUnencodedChars(input).hash();
   }

    HashCode hashString(CharSequence input, Charset charset) {
      return this.newHasher().putString(input, charset).hash();
   }

    HashCode hashInt(int input) {
      return this.newHasher().putInt(input).hash();
   }

    HashCode hashLong(long input) {
      return this.newHasher().putLong(input).hash();
   }

    HashCode hashBytes(byte[] input) {
      return this.newHasher().putBytes(input).hash();
   }

    HashCode hashBytes(byte[] input, int off, int len) {
      return this.newHasher().putBytes(input, off, len).hash();
   }

    Hasher newHasher(int expectedInputSize) {
      Preconditions.checkArgument(expectedInputSize >= 0);
      return this.newHasher();
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
