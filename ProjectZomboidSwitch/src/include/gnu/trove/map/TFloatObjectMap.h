#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TFloatObjectIterator.h"
#include "gnu/trove/procedure/TFloatObjectProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatObjectMap {
public:
    virtual ~TFloatObjectMap() = default;
    float getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(float var1);

    bool containsValue(void* var1);

    V get(float var1);

    V put(float var1, V var2);

    V putIfAbsent(float var1, V var2);

    V remove(float var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatObjectMap<? extends);

    void clear();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TFloatObjectIterator<V> iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TFloatObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TFloatObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
