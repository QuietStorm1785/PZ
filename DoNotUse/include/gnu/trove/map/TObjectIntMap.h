#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"
#include "gnu/trove/function/TIntFunction.h"
#include "gnu/trove/iterator/TObjectIntIterator.h"
#include "gnu/trove/procedure/TIntProcedure.h"
#include "gnu/trove/procedure/TObjectIntProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectIntMap {
public:
    virtual ~TObjectIntMap() = default;
    int getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(int var1);

    int get(void* var1);

    int put(K var1, int var2);

    int putIfAbsent(K var1, int var2);

    int remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectIntMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TIntCollection valueCollection();

   int[] values();

   int[] values(int[] var1);

   TObjectIntIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, int var2);

    int adjustOrPutValue(K var1, int var2, int var3);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TIntProcedure var1);

    bool forEachEntry(TObjectIntProcedure<? super);

    void transformValues(TIntFunction var1);

    bool retainEntries(TObjectIntProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
