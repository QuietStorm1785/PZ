#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/cache/LocalCache/ValueReference.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace cache {


class LocalCache {
public:
    virtual ~LocalCache() = default;
   ValueReference<K, V> getValueReference();

    void setValueReference(V> var1);

   LocalCache$ReferenceEntry<K, V> getNext();

    int getHash();

    K getKey();

    long getAccessTime();

    void setAccessTime(long var1);

   LocalCache$ReferenceEntry<K, V> getNextInAccessQueue();

    void setNextInAccessQueue(V> var1);

   LocalCache$ReferenceEntry<K, V> getPreviousInAccessQueue();

    void setPreviousInAccessQueue(V> var1);

    long getWriteTime();

    void setWriteTime(long var1);

   LocalCache$ReferenceEntry<K, V> getNextInWriteQueue();

    void setNextInWriteQueue(V> var1);

   LocalCache$ReferenceEntry<K, V> getPreviousInWriteQueue();

    void setPreviousInWriteQueue(V> var1);
}
} // namespace cache
} // namespace common
} // namespace google
} // namespace com
