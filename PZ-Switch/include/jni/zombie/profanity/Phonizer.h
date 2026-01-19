#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace profanity {


class Phonizer {
:
    std::string name;
    std::string regex;

     Phonizer(const std::string& var1, const std::string& var2) {
      this.name = var1;
      this.regex = var2;
   }

    std::string getName() const {
      return this.name;
   }

    std::string getRegex() const {
      return this.regex;
   }

    void execute(Matcher var1, StringBuffer var2) {
      if (var1.group(this.name) != nullptr) {
         var1.appendReplacement(var2, "${" + this.name + "}");
      }
   }
}
} // namespace profanity
} // namespace zombie
