#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/TCharCollection.h"

namespace gnu {
namespace trove {
namespace queue {


class TCharQueue {
public:
    virtual ~TCharQueue() = default;
    char element();

    bool offer(char var1);

    char peek();

    char poll();
}
} // namespace queue
} // namespace trove
} // namespace gnu
