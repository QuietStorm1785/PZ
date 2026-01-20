#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"
#include "gnu/trove/function/TShortFunction.h"
#include "gnu/trove/iterator/TObjectShortIterator.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include "gnu/trove/procedure/TObjectShortProcedure.h"
#include "gnu/trove/procedure/TShortProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectShortMap {
public:
    virtual ~TObjectShortMap() = default;
    short getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(short var1);

    short get(void* var1);

    short put(K var1, short var2);

    short putIfAbsent(K var1, short var2);

    short remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectShortMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TShortCollection valueCollection();

   short[] values();

   short[] values(short[] var1);

   TObjectShortIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, short var2);

    short adjustOrPutValue(K var1, short var2, short var3);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TShortProcedure var1);

    bool forEachEntry(TObjectShortProcedure<? super);

    void transformValues(TShortFunction var1);

    bool retainEntries(TObjectShortProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
