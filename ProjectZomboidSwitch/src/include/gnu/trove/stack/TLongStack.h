#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace gnu {
namespace trove {
namespace stack {

class TLongStack {
public:
    virtual ~TLongStack() = default;
    long getNoEntryValue();

    void push(long var1);

    long pop();

    long peek();

    int size();

    void clear();

   long[] toArray();

    void toArray(long[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
