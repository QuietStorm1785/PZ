#pragma once
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace Collections {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class NonBlockingHashSet {
public:
 static const void *V = "";
private
 NonBlockingHashMap<E, Object> _map =
 std::make_unique<NonBlockingHashMap<>>();

 bool add(E object) { return this->_map.putIfAbsent((E)object, V) != V; }

 bool contains(void *object) { return this->_map.containsKey(object); }

 bool remove(void *object) { return this->_map.remove(object) == V; }

 int size() { return this->_map.size(); }

 void clear() { this->_map.clear(); }

public
 Iterator<E> iterator() { return this->_map.keySet().iterator(); }

 void readOnly() { throw RuntimeException("Unimplemented"); }
}
} // namespace Collections
} // namespace core
} // namespace zombie
