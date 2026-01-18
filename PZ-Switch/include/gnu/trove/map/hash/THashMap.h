#ifndef GNU_TROVE_MAP_HASH_THASHMAP_H
#define GNU_TROVE_MAP_HASH_THASHMAP_H

#include <unordered_map>

namespace gnu { namespace trove { namespace map { namespace hash {

template <typename K, typename V>
class THashMap {
public:
 bool containsKey(const K& key) const { return map.find(key) != map.end(); }
 V get(const K& key) const {
 auto it = map.find(key);
 return it != map.end() ? it->second : V();
 }
 void put(const K& key, const V& value) { map[key] = value; }
 void remove(const K& key) { map.erase(key); }
 void clear() { map.clear(); }
private:
 std::unordered_map<K, V> map;
};

}}}} // namespace gnu::trove::map::hash

#endif // GNU_TROVE_MAP_HASH_THASHMAP_H
