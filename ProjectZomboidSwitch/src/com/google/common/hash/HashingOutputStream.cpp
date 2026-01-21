#include "com/google/common/hash/HashingOutputStream.h"

namespace com {
namespace google {
namespace common {
namespace hash {

public HashingOutputStream::HashingOutputStream(HashFunction hashFunction, OutputStream out) {
    // TODO: Implement HashingOutputStream
    return nullptr;
}

void HashingOutputStream::write(int b) {
    // TODO: Implement write
}

void HashingOutputStream::write(byte[] bytes, int off, int len) {
    // TODO: Implement write
}

HashCode HashingOutputStream::hash() {
    // TODO: Implement hash
    return nullptr;
}

void HashingOutputStream::close() {
    // TODO: Implement close
}

} // namespace hash
} // namespace common
} // namespace google
} // namespace com
