#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class Ordering {
public:
    const AtomicInteger counter = std::make_shared<AtomicInteger>(0);
   private const ConcurrentMap<Object, int> uids = Platform.tryWeakKeys(std::make_unique<MapMaker>()).makeMap();

    int getUid(void* obj) {
    int uid = this.uids.get(obj);
      if (uid == nullptr) {
         uid = this.counter.getAndIncrement();
    int alreadySet = this.uids.putIfAbsent(obj, uid);
         if (alreadySet != nullptr) {
            uid = alreadySet;
         }
      }

    return uid;
   }

    int compare(void* left, void* right) {
      if (left == right) {
    return 0;
      } else if (left == nullptr) {
         return -1;
      } else if (right == nullptr) {
    return 1;
      } else {
    int leftCode = this.identityHashCode(left);
    int rightCode = this.identityHashCode(right);
         if (leftCode != rightCode) {
            return leftCode < rightCode ? -1 : 1;
         } else {
    int result = this.getUid(left).compareTo(this.getUid(right));
            if (result == 0) {
               throw std::make_unique<AssertionError>();
            } else {
    return result;
            }
         }
      }
   }

    std::string toString() {
      return "Ordering.arbitrary()";
   }

    int identityHashCode(void* object) {
      return System.identityHashCode(object);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
