#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace advancedanimation {


class AnimationVariableHandlePool {
public:
    static const void* s_threadLock = "AnimationVariableHandlePool.ThreadLock";
   private static std::unordered_map<std::string, AnimationVariableHandle> s_handlePool = std::make_unique<std::unordered_map<>>();
    static int s_globalIndexGenerator = 0;

    static AnimationVariableHandle getOrCreate(const std::string& var0) {
      /* synchronized - TODO: add std::mutex */ (s_threadLock) {
    return getOrCreateInternal();
      }
   }

    static AnimationVariableHandle getOrCreateInternal(const std::string& var0) {
      if (!isVariableNameValid(var0)) {
    return nullptr;
      } else {
    AnimationVariableHandle var1 = s_handlePool.get(var0);
         if (var1 != nullptr) {
    return var1;
         } else {
    AnimationVariableHandle var2 = std::make_shared<AnimationVariableHandle>();
            var2.setVariableName(var0);
            var2.setVariableIndex(generateNewVariableIndex());
            s_handlePool.put(var0, var2);
    return var2;
         }
      }
   }

    static bool isVariableNameValid(const std::string& var0) {
      return !StringUtils.isNullOrWhitespace(var0);
   }

    static int generateNewVariableIndex() {
      return s_globalIndexGenerator++;
   }
}
} // namespace advancedanimation
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
