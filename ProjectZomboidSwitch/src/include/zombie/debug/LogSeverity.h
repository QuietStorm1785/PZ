#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {

enum class LogSeverity {
   Trace,
   Debug,
   General,
   Warning,
   Error;
}
} // namespace debug
} // namespace zombie
