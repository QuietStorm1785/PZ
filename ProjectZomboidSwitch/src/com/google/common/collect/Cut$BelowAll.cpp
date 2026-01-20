#include <sstream>
#include <string>
#include "com\google\common\collect/Cut$BelowAll.h"

namespace com {
namespace google {
namespace common {
namespace collect {

bool Cut$BelowAll::isLessThan(Comparable<?> value) {
    // TODO: Implement isLessThan
    return false;
}

BoundType Cut$BelowAll::typeAsLowerBound() {
    // TODO: Implement typeAsLowerBound
    return nullptr;
}

BoundType Cut$BelowAll::typeAsUpperBound() {
    // TODO: Implement typeAsUpperBound
    return nullptr;
}

void Cut$BelowAll::describeAsLowerBound(std::stringstream sb) {
    // TODO: Implement describeAsLowerBound
}

void Cut$BelowAll::describeAsUpperBound(std::stringstream sb) {
    // TODO: Implement describeAsUpperBound
}

int Cut$BelowAll::compareTo(Cut<Comparable<?>> o) {
    // TODO: Implement compareTo
    return 0;
}

std::string Cut$BelowAll::toString() {
    // TODO: Implement toString
    return "";
}

void* Cut$BelowAll::readResolve() {
    // TODO: Implement readResolve
    return nullptr;
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
