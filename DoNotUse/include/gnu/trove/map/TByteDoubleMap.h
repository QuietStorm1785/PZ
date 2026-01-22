#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"
#include "gnu/trove/function/TDoubleFunction.h"
#include "gnu/trove/iterator/TByteDoubleIterator.h"
#include "gnu/trove/procedure/TByteDoubleProcedure.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TByteSet.h"

namespace gnu {
namespace trove {
namespace map {


class TByteDoubleMap {
public:
    virtual ~TByteDoubleMap() = default;
    uint8_t getNoEntryKey();

    double getNoEntryValue();

    double put(uint8_t var1, double var2);

    double putIfAbsent(uint8_t var1, double var2);

    void putAll(Map<? extends, ? extends);

    void putAll(TByteDoubleMap var1);

    double get(uint8_t var1);

    void clear();

    bool isEmpty();

    double remove(uint8_t var1);

    int size();

    TByteSet keySet();

   byte[] keys();

   byte[] keys(byte[] var1);

    TDoubleCollection valueCollection();

   double[] values();

   double[] values(double[] var1);

    bool containsValue(double var1);

    bool containsKey(uint8_t var1);

    TByteDoubleIterator iterator();

    bool forEachKey(TByteProcedure var1);

    bool forEachValue(TDoubleProcedure var1);

    bool forEachEntry(TByteDoubleProcedure var1);

    void transformValues(TDoubleFunction var1);

    bool retainEntries(TByteDoubleProcedure var1);

    bool increment(uint8_t var1);

    bool adjustValue(uint8_t var1, double var2);

    double adjustOrPutValue(uint8_t var1, double var2, double var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
