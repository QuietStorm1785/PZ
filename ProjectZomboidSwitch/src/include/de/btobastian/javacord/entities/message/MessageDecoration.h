#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {

enum class MessageDecoration {
   ITALICS("*"),
   BOLD("**"),
   STRIKEOUT("~~"),
   CODE_SIMPLE("`"),
   CODE_LONG("```"),
   UNDERLINE("__");

    const std::string prefix;
    const std::string suffix;

    private MessageDecoration(const std::string& prefix) {
      this.prefix = prefix;
      this.suffix = new std::stringstream(prefix).reverse();
   }

    std::string getPrefix() {
      return this.prefix;
   }

    std::string getSuffix() {
      return this.suffix;
   }
}
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
