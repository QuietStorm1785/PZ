#pragma once

#include <vector>

namespace gnu {
namespace trove {
namespace list {
namespace array {

template<typename T>
class TShortArrayList {
public:
 void add(T value) { data.push_back(value); }
 T get(int index) const { return data[index]; }
 int size() const { return data.size(); }
 void clear() { data.clear(); }
 
private:
 std::vector<T> data;
};

// Common specialization for short
typedef TShortArrayList<short> TShortArrayListImpl;

} // namespace array
} // namespace list
} // namespace trove
} // namespace gnu
