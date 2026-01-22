#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace gameStates {

enum class GameStateMachine {
   Continue,
   Remain,
   Yield;
}
} // namespace gameStates
} // namespace zombie
