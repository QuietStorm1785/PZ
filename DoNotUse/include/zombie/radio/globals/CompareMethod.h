#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace radio {
namespace globals {

enum class CompareMethod {
   equals,
   notequals,
   lessthan,
   morethan,
   lessthanorequals,
   morethanorequals;
}
} // namespace globals
} // namespace radio
} // namespace zombie
