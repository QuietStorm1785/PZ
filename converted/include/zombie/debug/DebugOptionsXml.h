#pragma once
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugOptionsXml {
public:
  bool setDebugMode = false;
  bool debugMode = true;
public
  final ArrayList<DebugOptionsXml.OptionNode> options =
      std::make_unique<ArrayList<>>();

public
  static final class OptionNode {
    std::string name;
    bool value;

  public
    OptionNode() {}

  public
    OptionNode(const std::string &string, bool boolean0) {
      this.name = string;
      this.value = boolean0;
    }
  }
}
} // namespace debug
} // namespace zombie
