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

class TByteStack {
public:
    virtual ~TByteStack() = default;
    uint8_t getNoEntryValue();

    void push(uint8_t var1);

    uint8_t pop();

    uint8_t peek();

    int size();

    void clear();

   byte[] toArray();

    void toArray(byte[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
