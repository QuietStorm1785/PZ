#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/FinalizableReferenceQueue/DecoupledLoader.h"
#include "com/google/common/base/FinalizableReferenceQueue/DirectLoader.h"
#include "com/google/common/base/FinalizableReferenceQueue/FinalizerLoader.h"
#include "com/google/common/base/FinalizableReferenceQueue/SystemLoader.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace base {


class FinalizableReferenceQueue {
public:
    static const Logger logger = Logger.getLogger(FinalizableReferenceQueue.class.getName());
    static const std::string FINALIZER_CLASS_NAME = "com.google.common.base.internal.Finalizer";
    static const Method startFinalizer;
   const ReferenceQueue<Object> queue = std::make_unique<ReferenceQueue<>>();
   const PhantomReference<Object> frqRef = new PhantomReference<>(this, this.queue);
    const bool threadStarted;

    public FinalizableReferenceQueue() {
    bool threadStarted = false;

      try {
         startFinalizer.invoke(nullptr, FinalizableReference.class, this.queue, this.frqRef);
         threadStarted = true;
      } catch (IllegalAccessException var3) {
         throw AssertionError(var3);
      } catch (Throwable var4) {
         logger.log(Level.INFO, "Failed to start reference finalizer thread. Reference cleanup will only occur when new references are created.", var4);
      }

      this.threadStarted = threadStarted;
   }

    void close() {
      this.frqRef.enqueue();
      this.cleanUp();
   }

    void cleanUp() {
      if (!this.threadStarted) {
         Reference<?> reference;
         while ((reference = this.queue.poll()) != nullptr) {
            reference.clear();

            try {
               ((FinalizableReference)reference).finalizeReferent();
            } catch (Throwable var3) {
               logger.log(Level.SEVERE, "Error cleaning up after reference.", var3);
            }
         }
      }
   }

   private static Class<?> loadFinalizer(FinalizerLoader... loaders) {
    for (auto& loader : loaders)         Class<?> finalizer = loader.loadFinalizer();
         if (finalizer != nullptr) {
    return finalizer;
         }
      }

      throw std::make_unique<AssertionError>();
   }

    static Method getStartFinalizer(Class<?> finalizer) {
      try {
         return finalizer.getMethod("startFinalizer", Class.class, ReferenceQueue.class, PhantomReference.class);
      } catch (NoSuchMethodException var2) {
         throw AssertionError(var2);
      }
   }

   static {
      Class<?> finalizer = loadFinalizer(std::make_unique<SystemLoader>(), std::make_unique<DecoupledLoader>(), std::make_unique<DirectLoader>());
      startFinalizer = getStartFinalizer(finalizer);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
