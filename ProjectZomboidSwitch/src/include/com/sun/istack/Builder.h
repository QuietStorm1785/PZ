#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace istack {

class Builder {
public:
    virtual ~Builder() = default;
    T build();
}
} // namespace istack
} // namespace sun
} // namespace com
