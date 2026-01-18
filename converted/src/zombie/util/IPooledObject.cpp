#include "zombie/util/IPooledObject.h"

namespace zombie {
namespace util {

void IPooledObject::setPool(Pool<IPooledObject> pool) {
 // TODO: Implement setPool
}

void IPooledObject::release() {
 // TODO: Implement release
}

bool IPooledObject::isFree() {
 // TODO: Implement isFree
 return false;
}

void IPooledObject::setFree(bool isFree) {
 // TODO: Implement setFree
}

void IPooledObject::release(IPooledObject[] iPooledObjects) {
 // TODO: Implement release
}

void IPooledObject::tryReleaseAndBlank(IPooledObject[] iPooledObjects) {
 // TODO: Implement tryReleaseAndBlank
}

void IPooledObject::releaseAndBlank(IPooledObject[] iPooledObjects) {
 // TODO: Implement releaseAndBlank
}

void IPooledObject::release(List<? extends) {
 // TODO: Implement release
}

} // namespace util
} // namespace zombie
