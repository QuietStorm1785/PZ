#include <string>
#include "com\google\common\hash/AbstractNonStreamingHashFunction.h"

namespace com {
namespace google {
namespace common {
namespace hash {

Hasher AbstractNonStreamingHashFunction::newHasher() {
    // TODO: Implement newHasher
    return nullptr;
}

Hasher AbstractNonStreamingHashFunction::newHasher(int expectedInputSize) {
    // TODO: Implement newHasher
    return nullptr;
}

HashCode AbstractNonStreamingHashFunction::hashUnencodedChars(CharSequence input) {
    // TODO: Implement hashUnencodedChars
    return nullptr;
}

HashCode AbstractNonStreamingHashFunction::hashString(CharSequence input, Charset charset) {
    // TODO: Implement hashString
    return nullptr;
}

HashCode AbstractNonStreamingHashFunction::hashInt(int input) {
    // TODO: Implement hashInt
    return nullptr;
}

HashCode AbstractNonStreamingHashFunction::hashLong(long input) {
    // TODO: Implement hashLong
    return nullptr;
}

HashCode AbstractNonStreamingHashFunction::hashBytes(byte[] input) {
    // TODO: Implement hashBytes
    return nullptr;
}

} // namespace hash
} // namespace common
} // namespace google
} // namespace com
