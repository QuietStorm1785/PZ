#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/collect/LinkedHashMultimap/ValueSetLink.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace collect {


class LinkedHashMultimap {
public:
    const int smearedValueHash;
   LinkedHashMultimap$ValueEntry<K, V> nextInValueBucket;
   ValueSetLink<K, V> predecessorInValueSet;
   ValueSetLink<K, V> successorInValueSet;
   LinkedHashMultimap$ValueEntry<K, V> predecessorInMultimap;
   LinkedHashMultimap$ValueEntry<K, V> successorInMultimap;

   LinkedHashMultimap$ValueEntry(@Nullable K key, @Nullable V value, int smearedValueHash, @Nullable LinkedHashMultimap$ValueEntry<K, V> nextInValueBucket) {
      super(key, value);
      this.smearedValueHash = smearedValueHash;
      this.nextInValueBucket = nextInValueBucket;
   }

    bool matchesValue(@Nullable Object, int smearedVHash) {
      return this.smearedValueHash == smearedVHash && Objects.equal(this.getValue(), v);
   }

   public ValueSetLink<K, V> getPredecessorInValueSet() {
      return this.predecessorInValueSet;
   }

   public ValueSetLink<K, V> getSuccessorInValueSet() {
      return this.successorInValueSet;
   }

    void setPredecessorInValueSet(V> entry) {
      this.predecessorInValueSet = entry;
   }

    void setSuccessorInValueSet(V> entry) {
      this.successorInValueSet = entry;
   }

   public LinkedHashMultimap$ValueEntry<K, V> getPredecessorInMultimap() {
      return this.predecessorInMultimap;
   }

   public LinkedHashMultimap$ValueEntry<K, V> getSuccessorInMultimap() {
      return this.successorInMultimap;
   }

    void setSuccessorInMultimap(V> multimapSuccessor) {
      this.successorInMultimap = multimapSuccessor;
   }

    void setPredecessorInMultimap(V> multimapPredecessor) {
      this.predecessorInMultimap = multimapPredecessor;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
