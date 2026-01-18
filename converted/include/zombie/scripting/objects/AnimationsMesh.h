#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/skinnedmodel/model/ModelMesh.h"
#include "zombie/scripting/ScriptParser.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimationsMesh : public BaseScriptObject {
public:
 std::string name = nullptr;
 std::string meshFile = nullptr;
 public ArrayList<String> animationDirectories = std::make_unique<ArrayList<>>();
 ModelMesh modelMesh = nullptr;

 void Load(const std::string& _name, const std::string& totalFile) {
 this->name = _name;
 ScriptParser.Block block = ScriptParser.parse(totalFile);
 block = block.children.get(0);

 for (ScriptParser.Value value : block.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("meshFile".equalsIgnoreCase(string0) {
 this->meshFile = string1;
 } else if ("animationDirectory".equalsIgnoreCase(string0) {
 this->animationDirectories.add(string1);
 }
 }
 }

 void reset() {
 this->meshFile = nullptr;
 this->animationDirectories.clear();
 this->modelMesh = nullptr;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
