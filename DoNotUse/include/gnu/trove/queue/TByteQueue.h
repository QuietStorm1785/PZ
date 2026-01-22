#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TByteCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TByteQueue {
public:
    virtual ~TByteQueue() = default;
    uint8_t element();

    bool offer(uint8_t var1);

    uint8_t peek();

    uint8_t poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
