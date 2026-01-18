#ifndef GNU_TROVE_LIST_ARRAY_TINTARRAYLIST_H
#define GNU_TROVE_LIST_ARRAY_TINTARRAYLIST_H

#include <vector>

namespace gnu { namespace trove { namespace list { namespace array {

class TIntArrayList {
public:
 void add(int value) { data.push_back(value); }
 int get(int index) const { return data[index]; }
 int size() const { return static_cast<int>(data.size()); }
 void clear() { data.clear(); }
private:
 std::vector<int> data;
};

}}}} // namespace gnu::trove::list::array

#endif // GNU_TROVE_LIST_ARRAY_TINTARRAYLIST_H
