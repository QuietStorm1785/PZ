#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Supplier.h"
#include "com/google/common/hash/ChecksumHashFunction/ChecksumHasher.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class ChecksumHashFunction : public AbstractStreamingHashFunction {
public:
   private const Supplier<? : public Checksum> checksumSupplier;
    const int bits;
    const std::string toString;
    static const long serialVersionUID = 0L;

   ChecksumHashFunction(Supplier<? : public Checksum> checksumSupplier, int bits, std::string toString) {
      this.checksumSupplier = (Supplier<? : public Checksum>)Preconditions.checkNotNull(checksumSupplier);
      Preconditions.checkArgument(bits == 32 || bits == 64, "bits (%s) must be either 32 or 64", bits);
      this.bits = bits;
      this.toString = (std::string)Preconditions.checkNotNull(toString);
   }

    int bits() {
      return this.bits;
   }

    Hasher newHasher() {
      return std::make_shared<ChecksumHasher>(this, (Checksum)this.checksumSupplier.get(), nullptr);
   }

    std::string toString() {
      return this.toString;
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
