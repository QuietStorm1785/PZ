#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {

// $VF: synthetic class
class FileTask_AbstractLoadModel {
public:
   static {
      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelFileExtensionType[ModelFileExtensionType.X.ordinal()] = 1;
      } catch (NoSuchFieldError var4) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelFileExtensionType[ModelFileExtensionType.Fbx.ordinal()] = 2;
      } catch (NoSuchFieldError var3) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelFileExtensionType[ModelFileExtensionType.Txt.ordinal()] = 3;
      } catch (NoSuchFieldError var2) {
      }

      try {
         $SwitchMap$zombie$core$skinnedmodel$model$ModelFileExtensionType[ModelFileExtensionType.None.ordinal()] = 4;
      } catch (NoSuchFieldError var1) {
      }
   }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
