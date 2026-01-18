#pragma once
#include "zombie/ZomboidFileSystem.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationSet {
public:
protected
 static HashMap<String, AnimationSet> setMap =
 std::make_unique<HashMap<>>();
public
 HashMap<String, AnimState> states = std::make_unique<HashMap<>>();
 std::string m_Name = "";

 static AnimationSet GetAnimationSet(const std::string &name, bool reload) {
 AnimationSet animationSet = setMap.get(name);
 if (animationSet != nullptr && !reload) {
 return animationSet;
 } else {
 animationSet = std::make_unique<AnimationSet>();
 animationSet.Load(name);
 setMap.put(name, animationSet);
 return animationSet;
 }
 }

 static void Reset() {
 for (AnimationSet animationSet : setMap.values()) {
 animationSet.clear();
 }

 setMap.clear();
 }

 AnimState GetState(const std::string &name) {
 AnimState animState = this->states.get(name.toLowerCase(Locale.ENGLISH);
 if (animState != nullptr) {
 return animState;
 } else {
 DebugLog.Animation.warn("AnimState not found: " + name);
 return std::make_unique<AnimState>();
 }
 }

 bool containsState(const std::string &name) {
 return this->states.containsKey(name.toLowerCase(Locale.ENGLISH);
 }

 bool Load(const std::string &name) {
 if (DebugLog.isEnabled(DebugType.Animation) {
 DebugLog.Animation.println("Loading AnimSet: " + name);
 }

 this->m_Name = name;
 String[] strings = ZomboidFileSystem.instance.resolveAllDirectories(
 "media/AnimSets/" + name, var0->true, false);

 for (auto &string0 : strings)
 std::string string1 = new File(string0).getName();
 AnimState animState = AnimState.Parse(string1, string0);
 animState.m_Set = this;
 this->states.put(string1, animState);
 }

 return true;
}

 void clear() {
 for (AnimState animState : this->states.values()) {
 animState.clear();
 }

 this->states.clear();
}
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
