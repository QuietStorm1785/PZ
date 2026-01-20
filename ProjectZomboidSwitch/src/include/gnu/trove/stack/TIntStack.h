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

class TIntStack {
public:
    virtual ~TIntStack() = default;
    int getNoEntryValue();

    void push(int var1);

    int pop();

    int peek();

    int size();

    void clear();

   int[] toArray();

    void toArray(int[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
