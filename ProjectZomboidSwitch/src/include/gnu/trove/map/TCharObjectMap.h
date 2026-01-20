#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TCharObjectIterator.h"
#include "gnu/trove/procedure/TCharObjectProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharObjectMap {
public:
    virtual ~TCharObjectMap() = default;
    char getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(char var1);

    bool containsValue(void* var1);

    V get(char var1);

    V put(char var1, V var2);

    V putIfAbsent(char var1, V var2);

    V remove(char var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharObjectMap<? extends);

    void clear();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TCharObjectIterator<V> iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TCharObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TCharObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
