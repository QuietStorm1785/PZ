#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/SurvivorFactory.h"

namespace zombie {
namespace text {
namespace templating {


class TemplateText {
public:
    std::string getString() {
      return SurvivorFactory.getRandomSurname();
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
