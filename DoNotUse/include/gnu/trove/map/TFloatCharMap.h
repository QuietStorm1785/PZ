#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TFloatCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TFloatCharProcedure.h"
#include "gnu/trove/procedure/TFloatProcedure.h"
#include "gnu/trove/set/TFloatSet.h"

namespace gnu {
namespace trove {
namespace map {


class TFloatCharMap {
public:
    virtual ~TFloatCharMap() = default;
    float getNoEntryKey();

    char getNoEntryValue();

    char put(float var1, char var2);

    char putIfAbsent(float var1, char var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TFloatCharMap var1);

    char get(float var1);

    void clear();

    bool isEmpty();

    char remove(float var1);

    int size();

    TFloatSet keySet();

   float[] keys();

   float[] keys(float[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(float var1);

    TFloatCharIterator iterator();

    bool forEachKey(TFloatProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TFloatCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TFloatCharProcedure var1);

    bool increment(float var1);

    bool adjustValue(float var1, char var2);

    char adjustOrPutValue(float var1, char var2, char var3);
}
} // namespace map
} // namespace trove
} // namespace gnu
