#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"
#include "gnu/trove/function/TByteFunction.h"
#include "gnu/trove/iterator/TDoubleByteIterator.h"
#include "gnu/trove/procedure/TByteProcedure.h"
#include "gnu/trove/procedure/TDoubleByteProcedure.h"
#include "gnu/trove/procedure/TDoubleProcedure.h"
#include "gnu/trove/set/TDoubleSet.h"

namespace gnu {
namespace trove {
namespace map {


class TDoubleByteMap {
public:
    virtual ~TDoubleByteMap() = default;
    double getNoEntryKey();

    uint8_t getNoEntryValue();

    uint8_t put(double var1, uint8_t var3);

    uint8_t putIfAbsent(double var1, uint8_t var3);

    void putAll(Map<? extends, ? extends);

    void putAll(TDoubleByteMap var1);

    uint8_t get(double var1);

    void clear();

    bool isEmpty();

    uint8_t remove(double var1);

    int size();

    TDoubleSet keySet();

   double[] keys();

   double[] keys(double[] var1);

    TByteCollection valueCollection();

   byte[] values();

   byte[] values(byte[] var1);

    bool containsValue(uint8_t var1);

    bool containsKey(double var1);

    TDoubleByteIterator iterator();

    bool forEachKey(TDoubleProcedure var1);

    bool forEachValue(TByteProcedure var1);

    bool forEachEntry(TDoubleByteProcedure var1);

    void transformValues(TByteFunction var1);

    bool retainEntries(TDoubleByteProcedure var1);

    bool increment(double var1);

    bool adjustValue(double var1, uint8_t var3);

    uint8_t adjustOrPutValue(double var1, uint8_t var3, uint8_t var4);
}
} // namespace map
} // namespace trove
} // namespace gnu
