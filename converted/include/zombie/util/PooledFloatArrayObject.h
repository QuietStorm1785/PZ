#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/list/PZArrayUtil.h"

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PooledFloatArrayObject : public PooledObject {
public:
 private static Pool<PooledFloatArrayObject> s_pool = new Pool<>(PooledFloatArrayObject::new);
 private float[] m_array = PZArrayUtil.emptyFloatArray;

 static PooledFloatArrayObject alloc(int count) {
 PooledFloatArrayObject pooledFloatArrayObject = s_pool.alloc();
 pooledFloatArrayObject.initCapacity(count);
 return pooledFloatArrayObject;
 }

 static PooledFloatArrayObject toArray(PooledFloatArrayObject source) {
 if (source.empty()) {
 return nullptr;
 } else {
 int int0 = source.length();
 PooledFloatArrayObject pooledFloatArrayObject = alloc(int0);
 if (int0 > 0) {
 System.arraycopy(source.array(), 0, pooledFloatArrayObject.array(), 0, int0);
 }

 return pooledFloatArrayObject;
 }
 }

 void initCapacity(int int0) {
 if (this->m_array.length != int0) {
 this->m_array = new float[int0];
 }
 }

 public float[] array() {
 return this->m_array;
 }

 float get(int idx) {
 return this->m_array[idx];
 }

 void set(int idx, float val) {
 this->m_array[idx] = val;
 }

 int length() {
 return this->m_array.length;
 }
}
} // namespace util
} // namespace zombie
