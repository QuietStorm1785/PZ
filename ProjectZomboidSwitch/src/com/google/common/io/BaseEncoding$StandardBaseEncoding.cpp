#include <string>
#include "com\google\common\io/BaseEncoding$StandardBaseEncoding.h"

namespace com {
namespace google {
namespace common {
namespace io {

CharMatcher BaseEncoding$StandardBaseEncoding::padding() {
    // TODO: Implement padding
    return nullptr;
}

int BaseEncoding$StandardBaseEncoding::maxEncodedSize(int bytes) {
    // TODO: Implement maxEncodedSize
    return 0;
}

OutputStream BaseEncoding$StandardBaseEncoding::encodingStream(Writer out) {
    // TODO: Implement encodingStream
    return nullptr;
}

void BaseEncoding$StandardBaseEncoding::encodeTo(Appendable target, byte[] bytes, int off, int len) {
    // TODO: Implement encodeTo
}

void BaseEncoding$StandardBaseEncoding::encodeChunkTo(Appendable target, byte[] bytes, int off, int len) {
    // TODO: Implement encodeChunkTo
}

int BaseEncoding$StandardBaseEncoding::maxDecodedSize(int chars) {
    // TODO: Implement maxDecodedSize
    return 0;
}

bool BaseEncoding$StandardBaseEncoding::canDecode(CharSequence chars) {
    // TODO: Implement canDecode
    return false;
}

int BaseEncoding$StandardBaseEncoding::decodeTo(byte[] target, CharSequence chars) {
    // TODO: Implement decodeTo
    return 0;
}

InputStream BaseEncoding$StandardBaseEncoding::decodingStream(Reader reader) {
    // TODO: Implement decodingStream
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::omitPadding() {
    // TODO: Implement omitPadding
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::withPadChar(char padChar) {
    // TODO: Implement withPadChar
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::withSeparator(const std::string& separator, int afterEveryChars) {
    // TODO: Implement withSeparator
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::upperCase() {
    // TODO: Implement upperCase
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::lowerCase() {
    // TODO: Implement lowerCase
    return nullptr;
}

BaseEncoding BaseEncoding$StandardBaseEncoding::newInstance(Alphabet alphabet, @Nullable char) {
    // TODO: Implement newInstance
    return nullptr;
}

std::string BaseEncoding$StandardBaseEncoding::toString() {
    // TODO: Implement toString
    return "";
}

bool BaseEncoding$StandardBaseEncoding::equals(@Nullable Object) {
    // TODO: Implement equals
    return false;
}

int BaseEncoding$StandardBaseEncoding::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

} // namespace io
} // namespace common
} // namespace google
} // namespace com
