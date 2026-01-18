#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IntCollection {
public:
 virtual ~IntCollection() = default;
 bool add(int var1);

 bool addAll(IntCollection var1);

 void clear();

 bool contains(int var1);

 bool containsAll(IntCollection var1);

 bool equals(void *var1);

 int hashCode();

 bool isEmpty();

 IntIterator iterator();

 bool remove(int var1);

 bool removeAll(IntCollection var1);

 bool retainAll(IntCollection var1);

 int size();

 int[] toArray();

 int[] toArray(int[] var1);

 void trimToSize();
}
} // namespace util
} // namespace zombie
