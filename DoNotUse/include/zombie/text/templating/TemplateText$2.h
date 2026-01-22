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
      return TemplateText.RandNext(100) > 50 ? SurvivorFactory.getRandomForename(true) : SurvivorFactory.getRandomForename(false);
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
