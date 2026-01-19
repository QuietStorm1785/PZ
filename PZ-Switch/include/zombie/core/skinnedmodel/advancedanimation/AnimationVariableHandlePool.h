#pragma once
#include <mutex>
#include "zombie/util/StringUtils.h"
#include <cstdint>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AnimationVariableHandlePool {
public:

 // Mutexes for synchronized blocks
 std::mutex s_threadLock_mutex;
 static const void *s_threadLock = "AnimationVariableHandlePool.ThreadLock";
private
 static HashMap<String, AnimationVariableHandle> s_handlePool =
 std::make_unique<HashMap<>>();
 static int s_globalIndexGenerator = 0;

 static AnimationVariableHandle getOrCreate(std::string_view string) {
 { std::lock_guard<std::mutex> __sync_lock__(s_threadLock_mutex); return getOrCreateInternal(); }
 }

 static AnimationVariableHandle
 getOrCreateInternal(std::string_view string) {
 if (!isVariableNameValid(string) {
 return nullptr;
 } else {
 AnimationVariableHandle animationVariableHandle0 =
 s_handlePool.get(string);
 if (animationVariableHandle0 != nullptr) {
 return animationVariableHandle0;
 } else {
 AnimationVariableHandle animationVariableHandle1 =
 new AnimationVariableHandle();
 animationVariableHandle1.setVariableName(string);
 animationVariableHandle1.setVariableIndex(generateNewVariableIndex());
 s_handlePool.put(string, animationVariableHandle1);
 return animationVariableHandle1;
 }
 }
 }

 static bool isVariableNameValid(std::string_view string) {
 return !StringUtils.isNullOrWhitespace(string);
 }

 static int generateNewVariableIndex() { return s_globalIndexGenerator++; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
