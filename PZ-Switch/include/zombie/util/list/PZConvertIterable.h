#pragma once
#include <algorithm>
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace list {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PZConvertIterable {
public:
private
 Iterable<S> m_srcIterable;
private
 Function<S, T> m_converter;

public
 PZConvertIterable(Iterable<S> iterable, T > function) {
 this->m_srcIterable = iterable;
 this->m_converter = function;
 }

public
 Iterator<T> iterator() {
 return std::make_unique<Iterator<T>>() {
 private
 Iterator<S> m_srcIterator =
 PZConvertIterable.this->m_srcIterable.iterator();

 bool hasNext() { return this->m_srcIterator.hasNext(); }

 T next() {
 return PZConvertIterable.this->m_converter.apply(
 this->m_srcIterator.next());
 }
 };
 }
}
} // namespace list
} // namespace util
} // namespace zombie
