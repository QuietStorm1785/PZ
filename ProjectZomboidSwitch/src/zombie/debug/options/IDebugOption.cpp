#include <string>
#include "zombie/debug/options/IDebugOption.h"

namespace zombie {
namespace debug {
namespace options {

std::string IDebugOption::getName() {
    // TODO: Implement getName
    return "";
}

IDebugOptionGroup IDebugOption::getParent() {
    // TODO: Implement getParent
    return nullptr;
}

void IDebugOption::setParent(IDebugOptionGroup var1) {
    // TODO: Implement setParent
}

} // namespace options
} // namespace debug
} // namespace zombie
