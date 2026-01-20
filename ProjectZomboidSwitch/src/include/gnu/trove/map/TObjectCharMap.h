#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"
#include "gnu/trove/function/TCharFunction.h"
#include "gnu/trove/iterator/TObjectCharIterator.h"
#include "gnu/trove/procedure/TCharProcedure.h"
#include "gnu/trove/procedure/TObjectCharProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TObjectCharMap {
public:
    virtual ~TObjectCharMap() = default;
    char getNoEntryValue();

    int size();

    bool isEmpty();

    bool containsKey(void* var1);

    bool containsValue(char var1);

    char get(void* var1);

    char put(K var1, char var2);

    char putIfAbsent(K var1, char var2);

    char remove(void* var1);

    void putAll(Map<? extends, ? extends);

    void putAll(TObjectCharMap<? extends);

    void clear();

   Set<K> keySet();

   Object[] keys();

   K[] keys(K[] var1);

    TCharCollection valueCollection();

   char[] values();

   char[] values(char[] var1);

   TObjectCharIterator<K> iterator();

    bool increment(K var1);

    bool adjustValue(K var1, char var2);

    char adjustOrPutValue(K var1, char var2, char var3);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TCharProcedure var1);

    bool forEachEntry(TObjectCharProcedure<? super);

    void transformValues(TCharFunction var1);

    bool retainEntries(TObjectCharProcedure<? super);

    bool equals(void* var1);

    int hashCode();
}
} // namespace map
} // namespace trove
} // namespace gnu
