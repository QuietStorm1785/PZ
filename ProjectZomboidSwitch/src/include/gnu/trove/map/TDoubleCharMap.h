#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TDoubleCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TDoubleCharProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleCharMap {
public:
    virtual ~TDoubleCharMap() = default;
    double getNoEntryKey();

    char getNoEntryValue();

    char put(double var1, char var3);

    char putIfAbsent(double var1, char var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleCharMap var1);

    char get(double var1);

    void clear();

    bool isEmpty();

    char remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

    bool containsValue(char var1);

    bool containsKey(double var1);

    TDoubleCharIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TDoubleCharProcedure var1);

    void transformValues(TCharFunction var1);

    bool retainEntries(TDoubleCharProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, char var3);

    char adjustOrPutValue(double var1, char var3, char var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
