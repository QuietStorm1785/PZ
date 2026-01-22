#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TIntCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TIntQueue {
public:
    virtual ~TIntQueue() = default;
    int element();

    bool offer(int var1);

    int peek();

    int poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
