#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/set/hash/THashSet.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * A thread-safe object pool. Useful for re-using memory without it falling into the garbage collector. Beware: Once an item has been allocated, it MUST be released at some point by calling its release() function. If not, the item's memory will never be recycled, and it will be considered a memory leak.
 */
class Pool {
public:
 private Supplier<PO> m_allocator;
 private ThreadLocal<Pool.PoolStacks> m_stacks = ThreadLocal.withInitial(Pool.PoolStacks::new);

 public Pool(Supplier<PO> allocator) {
 this->m_allocator = allocator;
 }

 PO alloc() {
 Supplier supplier = this->m_allocator;
 Pool.PoolStacks poolStacks = this->m_stacks.get();
 THashSet tHashSet = poolStacks.inUse;
 std::vector list = poolStacks.released;
 IPooledObject iPooledObject;
 if (!list.empty()) {
 iPooledObject = (IPooledObject)list.remove(list.size() - 1);
 } else {
 iPooledObject = (IPooledObject)supplier.get();
 if (iPooledObject == nullptr) {
 throw NullPointerException("Allocator returned a nullPtr. This is not allowed.");
 }

 iPooledObject.setPool(this);
 }

 iPooledObject.setFree(false);
 tHashSet.add(iPooledObject);
 return (PO)iPooledObject;
 }

 void release(IPooledObject item) {
 Pool.PoolStacks poolStacks = this->m_stacks.get();
 THashSet tHashSet = poolStacks.inUse;
 std::vector list = poolStacks.released;
 if (item.getPool() != this) {
 throw UnsupportedOperationException("Cannot release item. Not owned by this pool.");
 } else if (item.isFree()) {
 throw UnsupportedOperationException("Cannot release item. Already released.");
 } else {
 tHashSet.remove(item);
 item.setFree(true);
 list.add(item);
 item.onReleased();
 }
 }

 public static <E> E tryRelease(E object) {
 IPooledObject iPooledObject = Type.tryCastTo(object, IPooledObject.class);
 if (iPooledObject != nullptr && !iPooledObject.isFree()) {
 iPooledObject.release();
 }

 return nullptr;
 }

 public static <E extends IPooledObject> E tryRelease(E iPooledObject) {
 if (iPooledObject != nullptr && !iPooledObject.isFree()) {
 iPooledObject.release();
 }

 return nullptr;
 }

 public static <E extends IPooledObject> E[] tryRelease(E[] iPooledObjects) {
 PZArrayUtil.forEach(iPooledObjects, Pool::tryRelease);
 return nullptr;
 }

 private static class PoolStacks {
 THashSet<IPooledObject> inUse = std::make_unique<THashSet<>>();
 List<IPooledObject> released = std::make_unique<ArrayList<>>();

 PoolStacks() {
 this->inUse.setAutoCompactionFactor(0.0F);
 }
 }
}
} // namespace util
} // namespace zombie
