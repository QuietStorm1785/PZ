#ifndef GNU_TROVE_MAP_HASH_TLONGOBJECTHASHMAP_H
#define GNU_TROVE_MAP_HASH_TLONGOBJECTHASHMAP_H

#include <unordered_map>

namespace gnu { namespace trove { namespace map { namespace hash {

template <typename T>
class TLongObjectHashMap {
public:
 bool containsKey(long key) const { return map.find(key) != map.end(); }
 T get(long key) const {
 auto it = map.find(key);
 return it != map.end() ? it->second : T();
 }
 void put(long key, const T& value) { map[key] = value; }
 void remove(long key) { map.erase(key); }
 void clear() { map.clear(); }
private:
 std::unordered_map<long, T> map;
};

}}}} // namespace gnu::trove::map::hash

#endif // GNU_TROVE_MAP_HASH_TLONGOBJECTHASHMAP_H
