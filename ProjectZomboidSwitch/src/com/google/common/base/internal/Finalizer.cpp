#include <queue>
#include "com\google\common\base\internal/Finalizer.h"

namespace com {
namespace google {
namespace common {
namespace base {
namespace internal {

void Finalizer::startFinalizer(Class<?> finalizableReferenceClass, ReferenceQueue<Object> queue, PhantomReference<Object> frqReference) {
    // TODO: Implement startFinalizer
}

private Finalizer::Finalizer(Class<?> finalizableReferenceClass, ReferenceQueue<Object> queue, PhantomReference<Object> frqReference) {
    // TODO: Implement Finalizer
    return nullptr;
}

void Finalizer::run() {
    // TODO: Implement run
}

bool Finalizer::cleanUp(Reference<?> reference) {
    // TODO: Implement cleanUp
    return false;
}

Method Finalizer::getFinalizeReferentMethod() {
    // TODO: Implement getFinalizeReferentMethod
    return nullptr;
}

Field Finalizer::getInheritableThreadLocalsField() {
    // TODO: Implement getInheritableThreadLocalsField
    return nullptr;
}

} // namespace internal
} // namespace base
} // namespace common
} // namespace google
} // namespace com
