#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace text {
namespace templating {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ReplaceList {
public:
private
  final ArrayList<String> replacements;

public
  ReplaceList() { this.replacements = std::make_unique<ArrayList<>>(); }

public
  ReplaceList(ArrayList<String> arrayList) { this.replacements = arrayList; }

protected
  ArrayList<String> getReplacements() { return this.replacements; }

  std::string getString() {
    return this.replacements.size() == 0
               ? "!ERROR_EMPTY_LIST!"
               : this.replacements.get(
                     TemplateText.RandNext(this.replacements.size()));
  }
}
} // namespace templating
} // namespace text
} // namespace zombie
