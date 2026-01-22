#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableMap.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class UndirectedGraphConnections {
public:
   private const Map<N, V> adjacentNodeValues;

    private UndirectedGraphConnections(V> adjacentNodeValues) {
      this.adjacentNodeValues = (Map<N, V>)Preconditions.checkNotNull(adjacentNodeValues);
   }

   static <N, V> UndirectedGraphConnections<N, V> of() {
      return new UndirectedGraphConnections<>(new std::unordered_map<>(2, 1.0F));
   }

   static <N, V> UndirectedGraphConnections<N, V> ofImmutable(Map<N, V> adjacentNodeValues) {
      return new UndirectedGraphConnections<>(ImmutableMap.copyOf(adjacentNodeValues));
   }

   public Set<N> adjacentNodes() {
      return Collections.unmodifiableSet(this.adjacentNodeValues.keySet());
   }

   public Set<N> predecessors() {
      return this.adjacentNodes();
   }

   public Set<N> successors() {
      return this.adjacentNodes();
   }

    V value(void* node) {
      return this.adjacentNodeValues.get(node);
   }

    void removePredecessor(void* node) {
    V unused = this.removeSuccessor(node);
   }

    V removeSuccessor(void* node) {
      return this.adjacentNodeValues.remove(node);
   }

    void addPredecessor(N node, V value) {
    V unused = this.addSuccessor(node, value);
   }

    V addSuccessor(N node, V value) {
      return this.adjacentNodeValues.put(node, value);
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
