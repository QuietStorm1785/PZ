#include <string>
#include "com/google/common/io/CharSource.h"

namespace com {
namespace google {
namespace common {
namespace io {

protected CharSource::CharSource() {
    // TODO: Implement CharSource
    return nullptr;
}

ByteSource CharSource::asByteSource(Charset charset) {
    // TODO: Implement asByteSource
    return nullptr;
}

BufferedReader CharSource::openBufferedStream() {
    // TODO: Implement openBufferedStream
    return nullptr;
}

long CharSource::length() {
    // TODO: Implement length
    return 0;
}

long CharSource::countBySkipping(Reader reader) {
    // TODO: Implement countBySkipping
    return 0;
}

long CharSource::copyTo(Appendable appendable) {
    // TODO: Implement copyTo
    return 0;
}

long CharSource::copyTo(CharSink sink) {
    // TODO: Implement copyTo
    return 0;
}

std::string CharSource::read() {
    // TODO: Implement read
    return "";
}

std::string CharSource::readFirstLine() {
    // TODO: Implement readFirstLine
    return "";
}

bool CharSource::isEmpty() {
    // TODO: Implement isEmpty
    return false;
}

CharSource CharSource::concat(Iterable<? extends) {
    // TODO: Implement concat
    return nullptr;
}

CharSource CharSource::concat(Iterator<? extends) {
    // TODO: Implement concat
    return nullptr;
}

return CharSource::concat() {
    // TODO: Implement concat
    return nullptr;
}

CharSource CharSource::concat(CharSource... sources) {
    // TODO: Implement concat
    return nullptr;
}

return CharSource::concat() {
    // TODO: Implement concat
    return nullptr;
}

CharSource CharSource::wrap(CharSequence charSequence) {
    // TODO: Implement wrap
    return nullptr;
}

CharSource CharSource::empty() {
    // TODO: Implement empty
    return nullptr;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
