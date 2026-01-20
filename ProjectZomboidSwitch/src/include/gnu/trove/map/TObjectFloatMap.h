#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TObjectFloatIterator.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/procedure/TObjectFloatProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectFloatMap {
public:
    virtual ~TObjectFloatMap() = default;
    float getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(float var1);

    float get(void* var1);

    float put(K var1, float var2);

    float putIfAbsent(K var1, float var2);

    float remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectFloatMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

   TObjectFloatIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, float var2);

    float adjustOrPutValue(K var1, float var2, float var3);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TObjectFloatProcedure<? super);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TObjectFloatProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
