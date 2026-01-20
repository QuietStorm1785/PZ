#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Lists.h"
#include "com/google/common/collect/MapMaker.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/1.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/CycleDetectingReentrantReadWriteLock.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/LockGraphNode.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policies.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/Policy.h"
#include "com/google/common/util/concurrent/CycleDetectingLockFactory/WithExplicitOrdering.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/concurrent/ThreadSafe.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace util {
namespace concurrent {


class CycleDetectingLockFactory {
public:
   private static const ConcurrentMap<Class<? : public Enum>, Map<? : public Enum, LockGraphNode>> lockGraphNodesPerType = std::make_unique<MapMaker>().weakKeys().makeMap();
    static const Logger logger = Logger.getLogger(CycleDetectingLockFactory.class.getName());
    const Policy policy;
   private static const ThreadLocal<std::vector<LockGraphNode>> acquiredLocks = std::make_unique<1>();

    static CycleDetectingLockFactory newInstance(Policy policy) {
      return std::make_shared<CycleDetectingLockFactory>(policy);
   }

    ReentrantLock newReentrantLock(const std::string& lockName) {
      return this.newReentrantLock(lockName, false);
   }

    ReentrantLock newReentrantLock(const std::string& lockName, bool fair) {
      return (ReentrantLock)(this.policy == Policies.DISABLED
         ? std::make_shared<ReentrantLock>(fair)
         : std::make_shared<CycleDetectingReentrantLock>(this, std::make_shared<LockGraphNode>(lockName), fair, nullptr));
   }

    ReentrantReadWriteLock newReentrantReadWriteLock(const std::string& lockName) {
      return this.newReentrantReadWriteLock(lockName, false);
   }

    ReentrantReadWriteLock newReentrantReadWriteLock(const std::string& lockName, bool fair) {
      return (ReentrantReadWriteLock)(this.policy == Policies.DISABLED
         ? std::make_shared<ReentrantReadWriteLock>(fair)
         : std::make_shared<CycleDetectingReentrantReadWriteLock>(this, std::make_shared<LockGraphNode>(lockName), fair, nullptr));
   }

   public static <E : public Enum<E>> WithExplicitOrdering<E> newInstanceWithExplicitOrdering(Class<E> enumClass, Policy policy) {
      Preconditions.checkNotNull(enumClass);
      Preconditions.checkNotNull(policy);
      Map<E, LockGraphNode> lockGraphNodes = (Map<E, LockGraphNode>)getOrCreateNodes(enumClass);
      return std::make_shared<WithExplicitOrdering>(policy, lockGraphNodes);
   }

   private static Map<? : public Enum, LockGraphNode> getOrCreateNodes(Class<? : public Enum> clazz) {
      Map<? : public Enum, LockGraphNode> existing = lockGraphNodesPerType.get(clazz);
      if (existing != nullptr) {
    return existing;
      } else {
         Map<? : public Enum, LockGraphNode> created = createNodes(clazz);
         existing = lockGraphNodesPerType.putIfAbsent(clazz, created);
         return (Map<? : public Enum, LockGraphNode>)MoreObjects.firstNonNull(existing, created);
      }
   }

   static <E : public Enum<E>> Map<E, LockGraphNode> createNodes(Class<E> clazz) {
      EnumMap<E, LockGraphNode> map = Maps.newEnumMap(clazz);
      E[] keys = (E[])clazz.getEnumConstants();
    int numKeys = keys.length;
      std::vector<LockGraphNode> nodes = Lists.newArrayListWithCapacity(numKeys);

    for (auto& key : keys)    LockGraphNode node = std::make_shared<LockGraphNode>(getLockName(key));
         nodes.push_back(node);
         map.put(key, node);
      }

      for (int i = 1; i < numKeys; i++) {
         nodes.get(i).checkAcquiredLocks(Policies.THROW, nodes.subList(0, i));
      }

      for (int i = 0; i < numKeys - 1; i++) {
         nodes.get(i).checkAcquiredLocks(Policies.DISABLED, nodes.subList(i + 1, numKeys));
      }

      return Collections.unmodifiableMap(map);
   }

    static std::string getLockName(Enum<?> rank) {
      return rank.getDeclaringClass().getSimpleName() + "." + rank.name();
   }

    private CycleDetectingLockFactory(Policy policy) {
      this.policy = (Policy)Preconditions.checkNotNull(policy);
   }

    void aboutToAcquire(CycleDetectingLock lock) {
      if (!lock.isAcquiredByCurrentThread()) {
         std::vector<LockGraphNode> acquiredLockList = acquiredLocks.get();
    LockGraphNode node = lock.getLockGraphNode();
         node.checkAcquiredLocks(this.policy, acquiredLockList);
         acquiredLockList.push_back(node);
      }
   }

    static void lockStateChanged(CycleDetectingLock lock) {
      if (!lock.isAcquiredByCurrentThread()) {
         std::vector<LockGraphNode> acquiredLockList = acquiredLocks.get();
    LockGraphNode node = lock.getLockGraphNode();

         for (int i = acquiredLockList.size() - 1; i >= 0; i--) {
            if (acquiredLockList.get(i) == node) {
               acquiredLockList.remove(i);
               break;
            }
         }
      }
   }
}
} // namespace concurrent
} // namespace util
} // namespace common
} // namespace google
} // namespace com
