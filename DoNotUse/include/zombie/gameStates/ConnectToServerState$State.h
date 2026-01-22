#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace gameStates {

enum class ConnectToServerState {
   Start,
   TestTCP,
   WorkshopInit,
   WorkshopQuery,
   WorkshopConfirm,
   ServerWorkshopItemScreen,
   WorkshopUpdate,
   CheckMods,
   Finish,
   Exit;
}
} // namespace gameStates
} // namespace zombie
