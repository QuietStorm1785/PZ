#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class VehicleManager {
public:
    static const uint8_t PassengerPosition = 1;
    static const uint8_t Enter = 2;
    static const uint8_t Exit = 3;
    static const uint8_t SwitchSeat = 4;
    static const uint8_t Update = 5;
    static const uint8_t Remove = 8;
    static const uint8_t Physic = 9;
    static const uint8_t Config = 10;
    static const uint8_t RequestGetFull = 11;
    static const uint8_t RequestGetPosition = 12;
    static const uint8_t AddImpulse = 13;
    static const uint8_t Collide = 15;
    static const uint8_t Sound = 16;
    static const uint8_t TowingCar = 17;
    static const uint8_t DetachTowingCar = 18;
    static const uint8_t InitialWorldState = 19;
    static const uint8_t Sound_Crash = 1;
}
} // namespace vehicles
} // namespace zombie
