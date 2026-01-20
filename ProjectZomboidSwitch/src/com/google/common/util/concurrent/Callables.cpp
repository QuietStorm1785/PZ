#include <string>
#include "com\google\common\util\concurrent/Callables.h"

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {

private Callables::Callables() {
    // TODO: Implement Callables
    return nullptr;
}

Runnable Callables::threadRenaming(Runnable task, Supplier<std::string> nameSupplier) {
    // TODO: Implement threadRenaming
    return nullptr;
}

bool Callables::trySetName(const std::string& threadName, Thread currentThread) {
    // TODO: Implement trySetName
    return false;
}

} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
