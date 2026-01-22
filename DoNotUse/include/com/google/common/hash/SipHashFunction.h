#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/SipHashFunction/SipHasher.h"
#include "javax/annotation/Nullable.h"
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class SipHashFunction : public AbstractStreamingHashFunction {
public:
    const int c;
    const int d;
    const long k0;
    const long k1;
    static const long serialVersionUID = 0L;

   SipHashFunction(int c, int d, long k0, long k1) {
      Preconditions.checkArgument(c > 0, "The number of SipRound iterations (c=%s) during Compression must be positive.", c);
      Preconditions.checkArgument(d > 0, "The number of SipRound iterations (d=%s) during Finalization must be positive.", d);
      this.c = c;
      this.d = d;
      this.k0 = k0;
      this.k1 = k1;
   }

    int bits() {
    return 64;
   }

    Hasher newHasher() {
      return std::make_shared<SipHasher>(this.c, this.d, this.k0, this.k1);
   }

    std::string toString() {
      return "Hashing.sipHash" + this.c + "" + this.d + "(" + this.k0 + ", " + this.k1 + ")";
   }

    bool equals(@Nullable Object) {
      if (!(dynamic_cast<SipHashFunction*>(object) != nullptr)) {
    return false;
      } else {
    SipHashFunction other = (SipHashFunction)object;
         return this.c == other.c && this.d == other.d && this.k0 == other.k0 && this.k1 == other.k1;
      }
   }

    int hashCode() {
      return (int)(this.getClass().hashCode() ^ this.c ^ this.d ^ this.k0 ^ this.k1);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
