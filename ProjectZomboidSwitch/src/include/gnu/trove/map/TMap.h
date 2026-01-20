#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/function/TObjectFunction.h"
#include "gnu/trove/procedure/TObjectObjectProcedure.h"
#include "gnu/trove/procedure/TObjectProcedure.h"

namespace gnu {
namespace trove {
namespace map {


class TMap {
public:
    virtual ~TMap() = default;
    V putIfAbsent(K var1, V var2);

    bool forEachKey(TObjectProcedure<? super);

    bool forEachValue(TObjectProcedure<? super);

    bool forEachEntry(TObjectObjectProcedure<? super, ? super);

    bool retainEntries(TObjectObjectProcedure<? super, ? super);

    void transformValues(V> var1);
}
} // namespace map
} // namespace trove
} // namespace gnu
