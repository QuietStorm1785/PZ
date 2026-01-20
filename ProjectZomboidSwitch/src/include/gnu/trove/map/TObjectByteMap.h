#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TObjectByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TObjectByteProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectByteMap {
public:
    virtual ~TObjectByteMap() = default;
    uint8_t getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(uint8_t var1);

    uint8_t get(void* var1);

    uint8_t put(K var1, uint8_t var2);

    uint8_t putIfAbsent(K var1, uint8_t var2);

    uint8_t remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectByteMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

   TObjectByteIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, uint8_t var2);

    uint8_t adjustOrPutValue(K var1, uint8_t var2, uint8_t var3);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TObjectByteProcedure<? super);

    void transformValues(TByteFunction var1);

    bool retainEntries(TObjectByteProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
