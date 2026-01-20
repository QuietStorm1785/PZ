#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {
namespace internal {


class Finalizer {
public:
    static const Logger logger = Logger.getLogger(Finalizer.class.getName());
    static const std::string FINALIZABLE_REFERENCE = "com.google.common.base.FinalizableReference";
   private const WeakReference<Class<?>> finalizableReferenceClassReference;
   private const PhantomReference<Object> frqReference;
   private const ReferenceQueue<Object> queue;
    static const Field inheritableThreadLocals = getInheritableThreadLocalsField();

    static void startFinalizer(Class<?> finalizableReferenceClass, ReferenceQueue<Object> queue, PhantomReference<Object> frqReference) {
      if (!finalizableReferenceClass.getName() == "com.google.common.base.FinalizableReference")) {
         throw IllegalArgumentException("Expected com.google.common.base.FinalizableReference.");
      } else {
    Finalizer finalizer = std::make_shared<Finalizer>(finalizableReferenceClass, queue, frqReference);
    Thread thread = std::make_shared<Thread>(finalizer);
         thread.setName(Finalizer.class.getName());
         thread.setDaemon(true);

         try {
            if (inheritableThreadLocals != nullptr) {
               inheritableThreadLocals.set(thread, nullptr);
            }
         } catch (Throwable var6) {
            logger.log(Level.INFO, "Failed to clear thread local values inherited by reference finalizer thread.", var6);
         }

         thread.start();
      }
   }

    private Finalizer(Class<?> finalizableReferenceClass, ReferenceQueue<Object> queue, PhantomReference<Object> frqReference) {
      this.queue = queue;
      this.finalizableReferenceClassReference = new WeakReference<>(finalizableReferenceClass);
      this.frqReference = frqReference;
   }

    void run() {
      while (true) {
         try {
            if (!this.cleanUp(this.queue.remove())) {
               return;
            }
         } catch (InterruptedException var2) {
         }
      }
   }

    bool cleanUp(Reference<?> reference) {
    Method finalizeReferentMethod = this.getFinalizeReferentMethod();
      if (finalizeReferentMethod == nullptr) {
    return false;
      } else {
         do {
            reference.clear();
            if (reference == this.frqReference) {
    return false;
            }

            try {
               finalizeReferentMethod.invoke(reference);
            } catch (Throwable var4) {
               logger.log(Level.SEVERE, "Error cleaning up after reference.", var4);
            }
         } while ((reference = this.queue.poll()) != nullptr);

    return true;
      }
   }

    Method getFinalizeReferentMethod() {
      Class<?> finalizableReferenceClass = this.finalizableReferenceClassReference.get();
      if (finalizableReferenceClass == nullptr) {
    return nullptr;
      } else {
         try {
            return finalizableReferenceClass.getMethod("finalizeReferent");
         } catch (NoSuchMethodException var3) {
            throw AssertionError(var3);
         }
      }
   }

    static Field getInheritableThreadLocalsField() {
      try {
    Field inheritableThreadLocals = Thread.class.getDeclaredField("inheritableThreadLocals");
         inheritableThreadLocals.setAccessible(true);
    return inheritableThreadLocals;
      } catch (Throwable var1) {
         logger.log(Level.INFO, "Couldn't access Thread.inheritableThreadLocals. Reference finalizer threads will inherit thread local values.");
    return nullptr;
      }
   }
}
} // namespace internal
} // namespace base
} // namespace common
} // namespace google
} // namespace com
