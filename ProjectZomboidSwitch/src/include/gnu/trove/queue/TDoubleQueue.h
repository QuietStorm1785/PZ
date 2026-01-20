#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TDoubleCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TDoubleQueue {
public:
    virtual ~TDoubleQueue() = default;
    double element();

    bool offer(double var1);

    double peek();

    double poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
