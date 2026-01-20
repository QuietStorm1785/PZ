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

class TCharStack {
public:
    virtual ~TCharStack() = default;
    char getNoEntryValue();

    void push(char var1);

    char pop();

    char peek();

    int size();

    void clear();

   char[] toArray();

    void toArray(char[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
