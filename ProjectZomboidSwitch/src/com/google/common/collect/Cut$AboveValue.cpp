#include <sstream>
#include <string>
#include "com\google\common\collect/Cut$AboveValue.h"

namespace com {
namespace google {
namespace common {
namespace collect {

bool Cut$AboveValue::isLessThan(C value) {
    // TODO: Implement isLessThan
    return false;
}

BoundType Cut$AboveValue::typeAsLowerBound() {
    // TODO: Implement typeAsLowerBound
    return nullptr;
}

BoundType Cut$AboveValue::typeAsUpperBound() {
    // TODO: Implement typeAsUpperBound
    return nullptr;
}

void Cut$AboveValue::describeAsLowerBound(std::stringstream sb) {
    // TODO: Implement describeAsLowerBound
}

void Cut$AboveValue::describeAsUpperBound(std::stringstream sb) {
    // TODO: Implement describeAsUpperBound
}

C Cut$AboveValue::leastValueAbove(DiscreteDomain<C> domain) {
    // TODO: Implement leastValueAbove
    return nullptr;
}

C Cut$AboveValue::greatestValueBelow(DiscreteDomain<C> domain) {
    // TODO: Implement greatestValueBelow
    return nullptr;
}

int Cut$AboveValue::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

std::string Cut$AboveValue::toString() {
    // TODO: Implement toString
    return "";
}

} // namespace collect
} // namespace common
} // namespace google
} // namespace com
