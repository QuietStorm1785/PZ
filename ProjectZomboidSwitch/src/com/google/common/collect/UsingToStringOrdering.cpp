#include <string>
#include "com\google\common\collect/UsingToStringOrdering.h"

namespace com {
namespace google {
namespace common {
namespace collect {

int UsingToStringOrdering::compare(void* left, void* right) {
    // TODO: Implement compare
    return 0;
}

void* UsingToStringOrdering::readResolve() {
    // TODO: Implement readResolve
    return nullptr;
}

std::string UsingToStringOrdering::toString() {
    // TODO: Implement toString
    return "";
}

private UsingToStringOrdering::UsingToStringOrdering() {
    // TODO: Implement UsingToStringOrdering
    return nullptr;
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
