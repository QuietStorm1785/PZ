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

class TFloatStack {
public:
    virtual ~TFloatStack() = default;
    float getNoEntryValue();

    void push(float var1);

    float pop();

    float peek();

    int size();

    void clear();

   float[] toArray();

    void toArray(float[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
