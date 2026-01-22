#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/IntCollection.h"

namespace zombie {
namespace util {
namespace list {


class IntList {
public:
    virtual ~IntList() = default;
    void add(int var1, int var2);

    bool addAll(int var1, IntCollection var2);

    int get(int var1);

    int indexOf(int var1);

    int indexOf(int var1, int var2);

    int lastIndexOf(int var1);

    int lastIndexOf(int var1, int var2);

    IntListIterator listIterator();

    IntListIterator listIterator(int var1);

    int removeElementAt(int var1);

    int set(int var1, int var2);
}
} // namespace list
} // namespace util
} // namespace zombie
