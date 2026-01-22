#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"
#include "com/google/common/graph/DirectedGraphConnections/1.h"
#include "com/google/common/graph/DirectedGraphConnections/2.h"
#include "com/google/common/graph/DirectedGraphConnections/PredAndSucc.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class DirectedGraphConnections {
public:
    static const void* PRED = std::make_shared<Object>();
   private const Map<N, Object> adjacentNodeValues;
    int predecessorCount;
    int successorCount;

    private DirectedGraphConnections(Object> adjacentNodeValues, int predecessorCount, int successorCount) {
      this.adjacentNodeValues = (Map<N, Object>)Preconditions.checkNotNull(adjacentNodeValues);
      this.predecessorCount = Graphs.checkNonNegative(predecessorCount);
      this.successorCount = Graphs.checkNonNegative(successorCount);
      Preconditions.checkState(predecessorCount <= adjacentNodeValues.size() && successorCount <= adjacentNodeValues.size());
   }

   static <N, V> DirectedGraphConnections<N, V> of() {
    int initialCapacity = 4;
      return new DirectedGraphConnections<>(new std::unordered_map<>(initialCapacity, 1.0F), 0, 0);
   }

   static <N, V> DirectedGraphConnections<N, V> ofImmutable(Set<N> predecessors, Map<N, V> successorValues) {
      Map<N, Object> adjacentNodeValues = std::make_unique<std::unordered_map<>>();
      adjacentNodeValues.putAll(successorValues);

    for (auto& predecessor : predecessors)    void* value = adjacentNodeValues.put(predecessor, PRED);
         if (value != nullptr) {
            adjacentNodeValues.put(predecessor, std::make_shared<PredAndSucc>(value));
         }
      }

      return new DirectedGraphConnections<>(ImmutableMap.copyOf(adjacentNodeValues), predecessors.size(), successorValues.size());
   }

   public Set<N> adjacentNodes() {
      return Collections.unmodifiableSet(this.adjacentNodeValues.keySet());
   }

   public Set<N> predecessors() {
      return std::make_shared<1>(this);
   }

   public Set<N> successors() {
      return std::make_shared<2>(this);
   }

    V value(void* node) {
    void* value = this.adjacentNodeValues.get(node);
      if (value == PRED) {
    return nullptr;
      } else {
         return (V)(dynamic_cast<PredAndSucc*>(value) != nullptr ? PredAndSucc.access$500((PredAndSucc)value) : value);
      }
   }

    void removePredecessor(void* node) {
    void* previousValue = this.adjacentNodeValues.get(node);
      if (previousValue == PRED) {
         this.adjacentNodeValues.remove(node);
         Graphs.checkNonNegative(--this.predecessorCount);
      } else if (dynamic_cast<PredAndSucc*>(previousValue) != nullptr) {
         this.adjacentNodeValues.put((N)node, PredAndSucc.access$500((PredAndSucc)previousValue));
         Graphs.checkNonNegative(--this.predecessorCount);
      }
   }

    V removeSuccessor(void* node) {
    void* previousValue = this.adjacentNodeValues.get(node);
      if (previousValue == nullptr || previousValue == PRED) {
    return nullptr;
      } else if (dynamic_cast<PredAndSucc*>(previousValue) != nullptr) {
         this.adjacentNodeValues.put((N)node, PRED);
         Graphs.checkNonNegative(--this.successorCount);
         return (V)PredAndSucc.access$500((PredAndSucc)previousValue);
      } else {
         this.adjacentNodeValues.remove(node);
         Graphs.checkNonNegative(--this.successorCount);
         return (V)previousValue;
      }
   }

    void addPredecessor(N node, V unused) {
    void* previousValue = this.adjacentNodeValues.put(node, PRED);
      if (previousValue == nullptr) {
         Graphs.checkPositive(++this.predecessorCount);
      } else if (dynamic_cast<PredAndSucc*>(previousValue) != nullptr) {
         this.adjacentNodeValues.put(node, previousValue);
      } else if (previousValue != PRED) {
         this.adjacentNodeValues.put(node, std::make_shared<PredAndSucc>(previousValue));
         Graphs.checkPositive(++this.predecessorCount);
      }
   }

    V addSuccessor(N node, V value) {
    void* previousValue = this.adjacentNodeValues.put(node, value);
      if (previousValue == nullptr) {
         Graphs.checkPositive(++this.successorCount);
    return nullptr;
      } else if (dynamic_cast<PredAndSucc*>(previousValue) != nullptr) {
         this.adjacentNodeValues.put(node, std::make_shared<PredAndSucc>(value));
         return (V)PredAndSucc.access$500((PredAndSucc)previousValue);
      } else if (previousValue == PRED) {
         this.adjacentNodeValues.put(node, std::make_shared<PredAndSucc>(value));
         Graphs.checkPositive(++this.successorCount);
    return nullptr;
      } else {
         return (V)previousValue;
      }
   }

    static bool isPredecessor(@Nullable Object) {
    return value = = PRED || dynamic_cast<PredAndSucc*>(value) != nullptr;
   }

    static bool isSuccessor(@Nullable Object) {
      return value != PRED && value != nullptr;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
