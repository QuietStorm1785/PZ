#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ReferenceEntry.h"
#include "com/google/common/cache/LocalCache/ValueReference.h"

namespace com {
namespace google {
namespace common {
namespace cache {


enum class LocalCache {
   INSTANCE;

   public ValueReference<Object, Object> getValueReference() {
    return nullptr;
   }

    void setValueReference(Object> valueReference) {
   }

   public ReferenceEntry<Object, Object> getNext() {
    return nullptr;
   }

    int getHash() {
    return 0;
   }

    void* getKey() {
    return nullptr;
   }

    long getAccessTime() {
    return 0L;
   }

    void setAccessTime(long time) {
   }

   public ReferenceEntry<Object, Object> getNextInAccessQueue() {
    return this;
   }

    void setNextInAccessQueue(Object> next) {
   }

   public ReferenceEntry<Object, Object> getPreviousInAccessQueue() {
    return this;
   }

    void setPreviousInAccessQueue(Object> previous) {
   }

    long getWriteTime() {
    return 0L;
   }

    void setWriteTime(long time) {
   }

   public ReferenceEntry<Object, Object> getNextInWriteQueue() {
    return this;
   }

    void setNextInWriteQueue(Object> next) {
   }

   public ReferenceEntry<Object, Object> getPreviousInWriteQueue() {
    return this;
   }

    void setPreviousInWriteQueue(Object> previous) {
   }
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
