#include <sstream>
#include <string>
#include "com/google/common/base/Joiner.h"

namespace com {
namespace google {
namespace common {
namespace base {

Joiner Joiner::on(const std::string& separator) {
    // TODO: Implement on
    return nullptr;
}

Joiner Joiner::on(char separator) {
    // TODO: Implement on
    return nullptr;
}

private Joiner::Joiner(const std::string& separator) {
    // TODO: Implement Joiner
    return nullptr;
}

private Joiner::Joiner(Joiner prototype) {
    // TODO: Implement Joiner
    return nullptr;
}

std::stringstream Joiner::appendTo(std::stringstream builder, Iterable<?> parts) {
    // TODO: Implement appendTo
    return nullptr;
}

std::stringstream Joiner::appendTo(std::stringstream builder, Iterator<?> parts) {
    // TODO: Implement appendTo
    return nullptr;
}

std::stringstream Joiner::appendTo(std::stringstream builder, Object[] parts) {
    // TODO: Implement appendTo
    return nullptr;
}

std::stringstream Joiner::appendTo(std::stringstream builder, @Nullable Object, @Nullable Object, Object... rest) {
    // TODO: Implement appendTo
    return nullptr;
}

std::string Joiner::join(Iterable<?> parts) {
    // TODO: Implement join
    return "";
}

std::string Joiner::join(Iterator<?> parts) {
    // TODO: Implement join
    return "";
}

std::string Joiner::join(Object[] parts) {
    // TODO: Implement join
    return "";
}

std::string Joiner::join(@Nullable Object, @Nullable Object, Object... rest) {
    // TODO: Implement join
    return "";
}

Joiner Joiner::useForNull(const std::string& nullText) {
    // TODO: Implement useForNull
    return nullptr;
}

Joiner Joiner::skipNulls() {
    // TODO: Implement skipNulls
    return nullptr;
}

MapJoiner Joiner::withKeyValueSeparator(char keyValueSeparator) {
    // TODO: Implement withKeyValueSeparator
    return nullptr;
}

MapJoiner Joiner::withKeyValueSeparator(const std::string& keyValueSeparator) {
    // TODO: Implement withKeyValueSeparator
    return nullptr;
}

CharSequence Joiner::toString(void* part) {
    // TODO: Implement toString
    return nullptr;
}

} // namespace base
} // namespace common
} // namespace google
} // namespace com
