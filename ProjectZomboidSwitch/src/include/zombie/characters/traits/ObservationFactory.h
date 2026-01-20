#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/traits/ObservationFactory/Observation.h"

namespace zombie {
namespace characters {
namespace traits {


class ObservationFactory {
public:
   public static std::unordered_map<std::string, Observation> ObservationMap = std::make_unique<std::unordered_map<>>();

    static void init() {
   }

    static void setMutualExclusive(const std::string& var0, const std::string& var1) {
      ObservationMap.get(var0).MutuallyExclusive.push_back(var1);
      ObservationMap.get(var1).MutuallyExclusive.push_back(var0);
   }

    static void addObservation(const std::string& var0, const std::string& var1, const std::string& var2) {
      ObservationMap.put(var0, std::make_shared<Observation>(var0, var1, var2));
   }

    static Observation getObservation(const std::string& var0) {
      return ObservationMap.containsKey(var0) ? ObservationMap.get(var0) : nullptr;
   }
}
} // namespace traits
} // namespace characters
} // namespace zombie
