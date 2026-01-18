#ifndef GNU_TROVE_SET_HASH_THASHSET_H
#define GNU_TROVE_SET_HASH_THASHSET_H

#include <unordered_set>

namespace gnu { namespace trove { namespace set { namespace hash {

template <typename T>
class THashSet {
public:
 bool contains(const T& value) const { return set.find(value) != set.end(); }
 void add(const T& value) { set.insert(value); }
 void remove(const T& value) { set.erase(value); }
 void clear() { set.clear(); }
 size_t size() const { return set.size(); }
private:
 std::unordered_set<T> set;
};

}}}} // namespace gnu::trove::set::hash

#endif // GNU_TROVE_SET_HASH_THASHSET_H
