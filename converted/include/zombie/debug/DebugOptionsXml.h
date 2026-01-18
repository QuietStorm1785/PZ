#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DebugOptionsXml {
public:
 bool setDebugMode = false;
 bool debugMode = true;
 public ArrayList<DebugOptionsXml.OptionNode> options = std::make_unique<ArrayList<>>();

 public static class OptionNode {
 std::string name;
 bool value;

 public OptionNode() {
 }

 public OptionNode(const std::string& string, bool boolean0) {
 this->name = string;
 this->value = boolean0;
 }
 }
}
} // namespace debug
} // namespace zombie
