#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TShortCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TShortQueue {
public:
    virtual ~TShortQueue() = default;
    short element();

    bool offer(short var1);

    short peek();

    short poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
