#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/iterator/TByteObjectIterator.h"
#include "gnu/trove/procedure/TByteObjectProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteObjectMap {
public:
    virtual ~TByteObjectMap() = default;
    uint8_t getNoEntryKey();

    int size();

    bool isEmpty();

    bool containsKey(uint8_t var1);

    bool containsValue(void* var1);

    V get(uint8_t var1);

    V put(uint8_t var1, V var2);

    V putIfAbsent(uint8_t var1, V var2);

    V remove(uint8_t var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteObjectMap<? extends);

    void clear();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

   Collection<V> valueCollection();

   Object[] values();

   V[] values(V[] var1);

   TByteObjectIterator<V> iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TByteObjectProcedure<? super);

    void transformValues(V> var1);

    bool retainEntries(TByteObjectProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
