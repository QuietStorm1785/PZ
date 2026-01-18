#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class SoundTimelineScript : public BaseScriptObject {
public:
 std::string eventName;
 private HashMap<String, Integer> positionByName = std::make_unique<HashMap<>>();

 void Load(const std::string& name, const std::string& totalFile) {
 this->eventName = name;
 ScriptParser.Block block = ScriptParser.parse(totalFile);
 block = block.children.get(0);

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 this->positionByName.put(string0, PZMath.tryParseInt(string1, 0);
 }
 }

 std::string getEventName() {
 return this->eventName;
 }

 int getPosition(const std::string& id) {
 return this->positionByName.containsKey(id) ? this->positionByName.get(id) : -1;
 }

 void reset() {
 this->positionByName.clear();
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
