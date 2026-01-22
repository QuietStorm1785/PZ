#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TFloatCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TFloatQueue {
public:
    virtual ~TFloatQueue() = default;
    float element();

    bool offer(float var1);

    float peek();

    float poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
