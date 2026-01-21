#include "com/google/common/io/ByteSink.h"

namespace com {
namespace google {
namespace common {
namespace io {

protected ByteSink::ByteSink() {
    // TODO: Implement ByteSink
    return nullptr;
}

CharSink ByteSink::asCharSink(Charset charset) {
    // TODO: Implement asCharSink
    return nullptr;
}

OutputStream ByteSink::openBufferedStream() {
    // TODO: Implement openBufferedStream
    return nullptr;
}

void ByteSink::write(byte[] bytes) {
    // TODO: Implement write
}

long ByteSink::writeFrom(InputStream input) {
    // TODO: Implement writeFrom
    return 0;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
