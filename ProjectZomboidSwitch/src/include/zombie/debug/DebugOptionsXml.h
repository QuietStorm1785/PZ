#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"
#include "zombie/debug/DebugOptionsXml/OptionNode.h"

namespace zombie {
namespace debug {


class DebugOptionsXml {
public:
    bool setDebugMode = false;
    bool debugMode = true;
   public const std::vector<OptionNode> options = std::make_unique<std::vector<>>();
}
} // namespace debug
} // namespace zombie
