#include "com/google/common/io/ByteSource.h"

namespace com {
namespace google {
namespace common {
namespace io {

protected ByteSource::ByteSource() {
    // TODO: Implement ByteSource
    return nullptr;
}

CharSource ByteSource::asCharSource(Charset charset) {
    // TODO: Implement asCharSource
    return nullptr;
}

InputStream ByteSource::openBufferedStream() {
    // TODO: Implement openBufferedStream
    return nullptr;
}

ByteSource ByteSource::slice(long offset, long length) {
    // TODO: Implement slice
    return nullptr;
}

bool ByteSource::isEmpty() {
    // TODO: Implement isEmpty
    return false;
}

long ByteSource::size() {
    // TODO: Implement size
    return 0;
}

long ByteSource::countBySkipping(InputStream in) {
    // TODO: Implement countBySkipping
    return 0;
}

long ByteSource::copyTo(OutputStream output) {
    // TODO: Implement copyTo
    return 0;
}

long ByteSource::copyTo(ByteSink sink) {
    // TODO: Implement copyTo
    return 0;
}

HashCode ByteSource::hash(HashFunction hashFunction) {
    // TODO: Implement hash
    return nullptr;
}

bool ByteSource::contentEquals(ByteSource other) {
    // TODO: Implement contentEquals
    return false;
}

ByteSource ByteSource::concat(Iterable<? extends) {
    // TODO: Implement concat
    return nullptr;
}

ByteSource ByteSource::concat(Iterator<? extends) {
    // TODO: Implement concat
    return nullptr;
}

return ByteSource::concat() {
    // TODO: Implement concat
    return nullptr;
}

ByteSource ByteSource::concat(ByteSource... sources) {
    // TODO: Implement concat
    return nullptr;
}

return ByteSource::concat() {
    // TODO: Implement concat
    return nullptr;
}

ByteSource ByteSource::wrap(byte[] b) {
    // TODO: Implement wrap
    return nullptr;
}

ByteSource ByteSource::empty() {
    // TODO: Implement empty
    return nullptr;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
