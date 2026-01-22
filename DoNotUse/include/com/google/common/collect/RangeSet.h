#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class RangeSet {
public:
    virtual ~RangeSet() = default;
    bool contains(C var1);

   Range<C> rangeContaining(C var1);

    bool intersects(Range<C> var1);

    bool encloses(Range<C> var1);

    bool enclosesAll(RangeSet<C> var1);

    bool isEmpty();

   Range<C> span();

   Set<Range<C>> asRanges();

   Set<Range<C>> asDescendingSetOfRanges();

   RangeSet<C> complement();

   RangeSet<C> subRangeSet(Range<C> var1);

    void add(Range<C> var1);

    void remove(Range<C> var1);

    void clear();

    void addAll(RangeSet<C> var1);

    void removeAll(RangeSet<C> var1);

    bool equals(@Nullable Object);

    int hashCode();

    std::string toString();
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
