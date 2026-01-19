#pragma once
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class SoundTimelineScript : public BaseScriptObject {
public:
 std::string eventName;
private
 HashMap<String, Integer> positionByName = std::make_unique<HashMap<>>();

 void Load(std::string_view name, std::string_view totalFile) {
 this->eventName = name;
 ScriptParser.Block block = ScriptParser.parse(totalFile);
 block = block.children.get(0);

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 this->positionByName.put(string0, PZMath.tryParseInt(string1, 0);
 }
 }

 std::string getEventName() { return this->eventName; }

 int getPosition(std::string_view id) {
 return this->positionByName.containsKey(id) ? this->positionByName.get(id)
 : -1;
 }

 void reset() { this->positionByName.clear(); }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
