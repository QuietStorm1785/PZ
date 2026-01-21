#include <string>
#include "com/google/common/io/CharSink.h"

namespace com {
namespace google {
namespace common {
namespace io {

protected CharSink::CharSink() {
    // TODO: Implement CharSink
    return nullptr;
}

Writer CharSink::openBufferedStream() {
    // TODO: Implement openBufferedStream
    return nullptr;
}

void CharSink::write(CharSequence charSequence) {
    // TODO: Implement write
}

void CharSink::writeLines(Iterable<? extends) {
    // TODO: Implement writeLines
}

void CharSink::writeLines(Iterable<? extends, const std::string& lineSeparator) {
    // TODO: Implement writeLines
}

long CharSink::writeFrom(Readable readable) {
    // TODO: Implement writeFrom
    return 0;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
