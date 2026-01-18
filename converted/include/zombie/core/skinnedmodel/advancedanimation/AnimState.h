#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/asset/AssetPath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/DebugType.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class AnimState {
public:
 std::string m_Name = "";
 public List<AnimNode> m_Nodes = std::make_unique<ArrayList<>>();
 int m_DefaultIndex = 0;
 AnimationSet m_Set = nullptr;
 static const bool s_bDebugLog_NodeConditions = false;

 public List<AnimNode> getAnimNodes(IAnimationVariableSource varSource, List<AnimNode> nodes) {
 nodes.clear();
 if (this->m_Nodes.size() <= 0) {
 return nodes;
 } else if (DebugOptions.instance.Animation.AnimLayer.AllowAnimNodeOverride.getValue()
 && varSource.getVariableBoolean("dbgForceAnim")
 && varSource.isVariable("dbgForceAnimStateName", this->m_Name) {
 std::string string = varSource.getVariableString("dbgForceAnimNodeName");
 int int0 = 0;

 for (int int1 = this->m_Nodes.size(); int0 < int1; int0++) {
 AnimNode animNode0 = this->m_Nodes.get(int0);
 if (StringUtils.equalsIgnoreCase(animNode0.m_Name, string) {
 nodes.add(animNode0);
 break;
 }
 }

 return nodes;
 } else {
 int int2 = -1;
 int int3 = 0;

 for (int int4 = this->m_Nodes.size(); int3 < int4; int3++) {
 AnimNode animNode1 = this->m_Nodes.get(int3);
 if (!animNode1.isAbstract() && animNode1.m_Conditions.size() >= int2 && animNode1.checkConditions(varSource) {
 if (int2 < animNode1.m_Conditions.size()) {
 nodes.clear();
 int2 = animNode1.m_Conditions.size();
 }

 nodes.add(animNode1);
 }
 }

 if (!nodes.empty()) {
 }

 return nodes;
 }
 }

 static AnimState Parse(const std::string& name, const std::string& statePath) {
 bool boolean0 = DebugLog.isEnabled(DebugType.Animation);
 AnimState animState = new AnimState();
 animState.m_Name = name;
 if (boolean0) {
 DebugLog.Animation.println("Loading AnimState: " + name);
 }

 String[] strings = ZomboidFileSystem.instance.resolveAllFiles(statePath, filex -> filex.getName().endsWith(".xml"), true);

 for (auto& string0 : strings) File file = new File(string0);
 std::string string1 = file.getName().split(".xml")[0].toLowerCase();
 if (boolean0) {
 DebugLog.Animation.println(name + " -> AnimNode: " + string1);
 }

 std::string string2 = ZomboidFileSystem.instance.resolveFileOrGUID(string0);
 AnimNodeAsset animNodeAsset = (AnimNodeAsset)AnimNodeAssetManager.instance.load(new AssetPath(string2);
 if (animNodeAsset.isReady()) {
 AnimNode animNode = animNodeAsset.m_animNode;
 animNode.m_State = animState;
 animState.m_Nodes.add(animNode);
 }
 }

 return animState;
 }

 std::string toString() {
 return "AnimState{" + this->m_Name + ", NodeCount:" + this->m_Nodes.size() + ", DefaultIndex:" + this->m_DefaultIndex + "}";
 }

 /**
 * Null-safe function that returns a given state's name. If nullptr, returns a nullptr
 */
 static std::string getStateName(AnimState state) {
 return state != nullptr ? state.m_Name : nullptr;
 }

 void clear() {
 this->m_Nodes.clear();
 this->m_Set = nullptr;
 }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
