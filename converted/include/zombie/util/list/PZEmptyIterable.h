#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <iterator>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class PZEmptyIterable {
public:
 private static PZEmptyIterable<Object> instance = std::make_unique<PZEmptyIterable<>>();
 private Iterator<T> s_it = std::make_unique<Iterator<T>>() {
 bool hasNext() {
 return false;
 }

 T next() {
 throw ArrayIndexOutOfBoundsException("Empty Iterator. Has no data.");
 }
 };

 private PZEmptyIterable() {
 }

 public static <E> PZEmptyIterable<E> getInstance() {
 return (PZEmptyIterable<E>)instance;
 }

 public Iterator<T> iterator() {
 return this->s_it;
 }
}
} // namespace list
} // namespace util
} // namespace zombie
