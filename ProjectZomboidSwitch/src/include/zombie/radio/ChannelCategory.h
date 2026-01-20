#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {

enum class ChannelCategory {
   Undefined,
   Radio,
   Television,
   Military,
   Amateur,
   Bandit,
   Emergency,
   Other;
}
} // namespace radio
} // namespace zombie
