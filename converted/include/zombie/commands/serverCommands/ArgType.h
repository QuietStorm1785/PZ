#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class ArgType {
public:
 static const std::string PlayerName = "(.+)";
 static const std::string AnyText = "(.+)";
 static const std::string Script = "([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)";
 static const std::string Coordinates = "(\\d+),(\\d+),(\\d+)";
 static const std::string IP = "((?:\\d{1,3}\\.){3}\\d{1,3})";
 static const std::string TrueFalse = "(-true|-false)";
 static const std::string ItemName = "([a-zA-Z0-9.-]*[a-zA-Z][a-zA-Z0-9_.-]*)";
 static const std::string Value = "(\\d+)";
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
