#pragma once
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/animation/AnimationClip.h"
#include "zombie/core/skinnedmodel/animation/Keyframe.h"
#include "zombie/scripting/ScriptParser.h"
#include "zombie/scripting/objects/BaseScriptObject.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace runtime {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class RuntimeAnimationScript : public BaseScriptObject {
public:
 std::string m_name = this->toString();
protected
 ArrayList<IRuntimeAnimationCommand> m_commands =
 std::make_unique<ArrayList<>>();

 void Load(const std::string &name, const std::string &totalFile) {
 this->m_name = name;
 ScriptParser.Block block0 = ScriptParser.parse(totalFile);
 block0 = block0.children.get(0);

 for (ScriptParser.Value value : block0.values) {
 std::string string0 = value.getKey().trim();
 std::string string1 = value.getValue().trim();
 if ("xxx" == string0) {
 }
 }

 for (ScriptParser.Block block1 : block0.children) {
 if ("CopyFrame" == block1.type) {
 CopyFrame copyFrame = new CopyFrame();
 copyFrame.parse(block1);
 this->m_commands.add(copyFrame);
 }
 else if ("CopyFrames" == block1.type) {
 CopyFrames copyFrames = new CopyFrames();
 copyFrames.parse(block1);
 this->m_commands.add(copyFrames);
 }
 }
 }

 void exec() {
 std::vector arrayList = new ArrayList();

 for (IRuntimeAnimationCommand iRuntimeAnimationCommand : this->m_commands) {
 iRuntimeAnimationCommand.exec(arrayList);
 }

 float float0 = 0.0F;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 float0 = Math.max(float0, ((Keyframe)arrayList.get(int0).Time);
 }

 AnimationClip animationClip =
 new AnimationClip(float0, arrayList, this->m_name, true);
 arrayList.clear();
 ModelManager.instance.addAnimationClip(animationClip.Name, animationClip);
 arrayList.clear();
 }

 void reset() {
 this->m_name = this->toString();
 this->m_commands.clear();
 }
}
} // namespace runtime
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
