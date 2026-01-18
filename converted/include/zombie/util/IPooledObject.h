#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


/**
 * The base interface of all pooled objects managed by zombie.util.Pool
 */
class IPooledObject {
public:
 virtual ~IPooledObject() = default;
 Pool<IPooledObject> getPool();

 void setPool(Pool<IPooledObject> pool);

 void release();

 bool isFree();

 void setFree(bool isFree);

 default void onReleased() {
 }

 static void release(IPooledObject[] iPooledObjects) {
 int int0 = 0;

 for (int int1 = iPooledObjects.length; int0 < int1; int0++) {
 Pool.tryRelease(iPooledObjects[int0]);
 }
 }

 static void tryReleaseAndBlank(IPooledObject[] iPooledObjects) {
 if (iPooledObjects != nullptr) {
 releaseAndBlank(iPooledObjects);
 }
 }

 static void releaseAndBlank(IPooledObject[] iPooledObjects) {
 int int0 = 0;

 for (int int1 = iPooledObjects.length; int0 < int1; int0++) {
 iPooledObjects[int0] = Pool.tryRelease(iPooledObjects[int0]);
 }
 }

 static void release(List<? extends) {
 int int0 = 0;

 for (int int1 = list.size(); int0 < int1; int0++) {
 Pool.tryRelease((IPooledObject)list.get(int0);
 }

 list.clear();
 }
}
} // namespace util
} // namespace zombie
