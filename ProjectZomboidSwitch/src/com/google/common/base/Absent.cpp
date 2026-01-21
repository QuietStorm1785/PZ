#include <string>
#include "com/google/common/base/Absent.h"

namespace com {
namespace google {
namespace common {
namespace base {

private Absent::Absent() {
    // TODO: Implement Absent
    return nullptr;
}

bool Absent::isPresent() {
    // TODO: Implement isPresent
    return false;
}

T Absent::get() {
    // TODO: Implement get
    return nullptr;
}

T Absent::or(T defaultValue) {
    // TODO: Implement or
    return nullptr;
}

T Absent::or(Supplier<? extends) {
    // TODO: Implement or
    return nullptr;
}

T Absent::orNull() {
    // TODO: Implement orNull
    return nullptr;
}

bool Absent::equals(@Nullable Object) {
    // TODO: Implement equals
    return false;
}

int Absent::hashCode() {
    // TODO: Implement hashCode
    return 0;
}

std::string Absent::toString() {
    // TODO: Implement toString
    return "";
}

void* Absent::readResolve() {
    // TODO: Implement readResolve
    return nullptr;
}

} // namespace base
} // namespace common
} // namespace google
} // namespace com
