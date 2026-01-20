#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TLongCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TLongQueue {
public:
    virtual ~TLongQueue() = default;
    long element();

    bool offer(long var1);

    long peek();

    long poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
