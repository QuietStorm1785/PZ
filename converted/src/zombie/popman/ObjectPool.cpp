#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace popman {

bool ObjectPool::contains(void *object) {
  // TODO: Implement contains
  return false;
}

public
ObjectPool::ObjectPool() {
  // TODO: Implement ObjectPool
  return nullptr;
}

public
ObjectPool::ObjectPool(ObjectPool.Allocator<T> alloc) {
  // TODO: Implement ObjectPool
  return nullptr;
}

T ObjectPool::alloc() {
  // TODO: Implement alloc
  return nullptr;
}

void ObjectPool::release(T object) {
  // TODO: Implement release
}

void ObjectPool::release(List<T> objs) {
  // TODO: Implement release
}

void ObjectPool::release(Iterable<T> objs) {
  // TODO: Implement release
}

void ObjectPool::release(T[] objects) {
  // TODO: Implement release
}

void ObjectPool::releaseAll(List<T> objs) {
  // TODO: Implement releaseAll
}

void ObjectPool::clear() {
  // TODO: Implement clear
}

T ObjectPool::makeObject() {
  // TODO: Implement makeObject
  return nullptr;
}

void ObjectPool::forEach(Consumer<T> consumer) {
  // TODO: Implement forEach
}

T ObjectPool::allocate() {
  // TODO: Implement allocate
  return nullptr;
}

} // namespace popman
} // namespace zombie
