#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace asset {

enum class Asset {
   EMPTY,
   READY,
   FAILURE;
}
} // namespace asset
} // namespace zombie
