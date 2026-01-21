#include <cstdint>
#include <string>
#include "com/google/common/primitives/SignedBytes.h"

namespace com {
namespace google {
namespace common {
namespace primitives {

private SignedBytes::SignedBytes() {
    // TODO: Implement SignedBytes
    return nullptr;
}

uint8_t SignedBytes::checkedCast(long value) {
    // TODO: Implement checkedCast
    return 0;
}

uint8_t SignedBytes::saturatedCast(long value) {
    // TODO: Implement saturatedCast
    return 0;
}

int SignedBytes::compare(uint8_t a, uint8_t b) {
    // TODO: Implement compare
    return 0;
}

uint8_t SignedBytes::min(byte... array) {
    // TODO: Implement min
    return 0;
}

uint8_t SignedBytes::max(byte... array) {
    // TODO: Implement max
    return 0;
}

std::string SignedBytes::join(const std::string& separator, byte... array) {
    // TODO: Implement join
    return "";
}

} // namespace primitives
} // namespace common
} // namespace google
} // namespace com
