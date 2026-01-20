#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"
#include "gnu/trove/function/TFloatFunction.h"
#include "gnu/trove/iterator/TCharFloatIterator.h"
#include "gnu/trove/procedure/TCharFloatProcedure.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TCharSet.h"

namespace gnu {
namespace trove {
namespace map {


class TCharFloatMap {
public:
    virtual ~TCharFloatMap() = default;
    char getNoEntryKey();

    float getNoEntryValue();

    float put(char var1, float var2);

    float putIfAbsent(char var1, float var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TCharFloatMap var1);

    float get(char var1);

    void clear();

    bool isEmpty();

    float remove(char var1);

    int size();

    TCharSet keySet();

   char[] keys();

   char[] keys(char[] var1);

    TFloatCollection valueCollection();

   float[] values();

   float[] values(float[] var1);

    bool containsValue(float var1);

    bool containsKey(char var1);

    TCharFloatIterator iterator();

    bool forEachKey(TCharProcedure var1);

    bool forEachValue(TFloatProcedure var1);

    bool forEachEntry(TCharFloatProcedure var1);

    void transformValues(TFloatFunction var1);

    bool retainEntries(TCharFloatProcedure var1);

    bool increment(char var1);

    bool adjustValue(char var1, float var2);

    float adjustOrPutValue(char var1, float var2, float var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
