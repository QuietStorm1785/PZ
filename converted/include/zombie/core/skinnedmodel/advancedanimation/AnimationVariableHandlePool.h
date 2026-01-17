#pragma once
#include "zombie/util/StringUtils.h"
#include <cstdint>
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

class AnimationVariableHandlePool {
public:
  static const void *s_threadLock = "AnimationVariableHandlePool.ThreadLock";
private
  static HashMap<String, AnimationVariableHandle> s_handlePool =
      std::make_unique<HashMap<>>();
  static int s_globalIndexGenerator = 0;

  static AnimationVariableHandle getOrCreate(const std::string &string) {
    synchronized(s_threadLock) { return getOrCreateInternal(); }
  }

  static AnimationVariableHandle
  getOrCreateInternal(const std::string &string) {
    if (!isVariableNameValid(string)) {
      return null;
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

  static bool isVariableNameValid(const std::string &string) {
    return !StringUtils.isNullOrWhitespace(string);
  }

  static int generateNewVariableIndex() { return s_globalIndexGenerator++; }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
