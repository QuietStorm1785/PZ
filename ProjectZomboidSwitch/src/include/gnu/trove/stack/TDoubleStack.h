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

class TDoubleStack {
public:
    virtual ~TDoubleStack() = default;
    double getNoEntryValue();

    void push(double var1);

    double pop();

    double peek();

    int size();

    void clear();

   double[] toArray();

    void toArray(double[] var1);
}
} // namespace stack
} // namespace trove
} // namespace gnu
