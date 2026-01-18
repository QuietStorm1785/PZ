#pragma once

#include <unordered_map>

namespace gnu {
namespace trove {
namespace map {
namespace hash {

template<typename K, typename V>
class TShortObjectHashMap {
public:
 void put(K key, V value) { data[key] = value; }
 V get(K key) const { 
 auto it = data.find(key);
 return it != data.end() ? it->second : nullptr;
 }
 bool containsKey(K key) const { return data.find(key) != data.end(); }
 void remove(K key) { data.erase(key); }
 int size() const { return data.size(); }
 void clear() { data.clear(); }
 
private:
 std::unordered_map<K, V> data;
};

} // namespace hash
} // namespace map
} // namespace trove
} // namespace gnu
