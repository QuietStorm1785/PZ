#include "com\google\common\hash/HashingInputStream.h"

namespace com {
namespace google {
namespace common {
namespace hash {

public HashingInputStream::HashingInputStream(HashFunction hashFunction, InputStream in) {
    // TODO: Implement HashingInputStream
    return nullptr;
}

int HashingInputStream::read() {
    // TODO: Implement read
    return 0;
}

int HashingInputStream::read(byte[] bytes, int off, int len) {
    // TODO: Implement read
    return 0;
}

bool HashingInputStream::markSupported() {
    // TODO: Implement markSupported
    return false;
}

void HashingInputStream::mark(int readlimit) {
    // TODO: Implement mark
}

void HashingInputStream::reset() {
    // TODO: Implement reset
}

HashCode HashingInputStream::hash() {
    // TODO: Implement hash
    return nullptr;
}

} // namespace hash
} // namespace common
} // namespace google
} // namespace com
