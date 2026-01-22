#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace text {
namespace templating {


class ReplaceList {
public:
   private const std::vector<std::string> replacements;

    public ReplaceList() {
      this.replacements = std::make_unique<std::vector<>>();
   }

    public ReplaceList(std::vector<std::string> var1) {
      this.replacements = var1;
   }

   protected std::vector<std::string> getReplacements() {
      return this.replacements;
   }

    std::string getString() {
      return this.replacements.size() == 0 ? "!ERROR_EMPTY_LIST!" : this.replacements.get(TemplateText.RandNext(this.replacements.size()));
   }
}
} // namespace templating
} // namespace text
} // namespace zombie
