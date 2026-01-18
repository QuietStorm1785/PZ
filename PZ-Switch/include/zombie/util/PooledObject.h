#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PooledObject {
public:
 bool m_isFree = true;
private
 Pool<IPooledObject> m_pool;

public
 Pool<IPooledObject> getPool() { return this->m_pool; }

 void setPool(Pool<IPooledObject> pool) { this->m_pool = pool; }

 void release() {
 if (this->m_pool != nullptr) {
 this->m_pool.release(this);
 } else {
 this->onReleased();
 }
 }

 bool isFree() { return this->m_isFree; }

 void setFree(bool boolean0) { this->m_isFree = boolean0; }
}
} // namespace util
} // namespace zombie
