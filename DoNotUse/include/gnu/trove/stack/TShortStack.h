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

class TShortStack {
public:
    virtual ~TShortStack() = default;
    short getNoEntryValue();

    void push(short var1);

    short pop();

    short peek();

    int size();

    void clear();

   short[] toArray();

    void toArray(short[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
