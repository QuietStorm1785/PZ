#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class Multiset {
public:
    virtual ~Multiset() = default;
    int count(@Nullable Object);

    int add(@Nullable E, int var2);

    int remove(@Nullable Object, int var2);

    int setCount(E var1, int var2);

    bool setCount(E var1, int var2, int var3);

   Set<E> elementSet();

   Set<Entry<E>> entrySet();

    bool equals(@Nullable Object);

    int hashCode();

    std::string toString();

   Iterator<E> iterator();

    bool contains(@Nullable Object);

    bool containsAll(Collection<?> var1);

    bool add(E var1);

    bool remove(@Nullable Object);

    bool removeAll(Collection<?> var1);

    bool retainAll(Collection<?> var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
