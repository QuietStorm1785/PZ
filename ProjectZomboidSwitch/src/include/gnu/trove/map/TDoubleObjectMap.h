#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TDoubleObjectIterator.h"
#include "gnu/trove/procedure/TDoubleObjectProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleObjectMap {
public:
    virtual ~TDoubleObjectMap() = default;
    double getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(double var1);

    bool containsValue(void* var1);

    V get(double var1);

    V put(double var1, V var3);

    V putIfAbsent(double var1, V var3);

    V remove(double var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleObjectMap<? extends);

    void clear();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TDoubleObjectIterator<V> iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TDoubleObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TDoubleObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
