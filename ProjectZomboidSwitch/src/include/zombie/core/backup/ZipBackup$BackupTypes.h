#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace backup {

enum class ZipBackup {
   period,
   startup,
   version;
}
} // namespace backup
} // namespace core
} // namespace zombie
