#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/FinalizableReferenceQueue/FinalizerLoader.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizableReferenceQueue {
public:
    static bool disabled;

   public Class<?> loadFinalizer() {
      if (disabled) {
    return nullptr;
      } else {
    ClassLoader systemLoader;
         try {
            systemLoader = ClassLoader.getSystemClassLoader();
         } catch (SecurityException var4) {
            FinalizableReferenceQueue.access$000().info("Not allowed to access system class loader.");
    return nullptr;
         }

         if (systemLoader != nullptr) {
            try {
               return systemLoader.loadClass("com.google.common.base.internal.Finalizer");
            } catch (ClassNotFoundException var3) {
    return nullptr;
            }
         } else {
    return nullptr;
         }
      }
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
