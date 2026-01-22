#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace vehicles {

class BaseVehicle {
public:
    static const short Full = 1;
    static const short PositionOrientation = 2;
    static const short Engine = 4;
    static const short Lights = 8;
    static const short PartModData = 16;
    static const short PartUsedDelta = 32;
    static const short PartModels = 64;
    static const short PartItem = 128;
    static const short PartWindow = 256;
    static const short PartDoor = 512;
    static const short Sounds = 1024;
    static const short PartCondition = 2048;
    static const short UpdateCarProperties = 4096;
    static const short Authorization = 16384;
    static const short AllPartFlags = 19440;

   protected BaseVehicle$UpdateFlags() {
   }
}
} // namespace vehicles
} // namespace zombie
