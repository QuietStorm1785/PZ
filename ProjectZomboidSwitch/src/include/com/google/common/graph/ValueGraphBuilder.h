#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"

namespace com {
namespace google {
namespace common {
namespace graph {


class ValueGraphBuilder {
public:
    private ValueGraphBuilder(bool directed) {
      super(directed);
   }

   public static ValueGraphBuilder<Object, Object> directed() {
      return new ValueGraphBuilder<>(true);
   }

   public static ValueGraphBuilder<Object, Object> undirected() {
      return new ValueGraphBuilder<>(false);
   }

   public static <N> ValueGraphBuilder<N, Object> from(Graph<N> graph) {
      return new ValueGraphBuilder<N, Object>(graph.isDirected()).allowsSelfLoops(graph.allowsSelfLoops()).nodeOrder(graph.nodeOrder());
   }

   public ValueGraphBuilder<N, V> allowsSelfLoops(boolean allowsSelfLoops) {
      this.allowsSelfLoops = allowsSelfLoops;
    return this;
   }

   public ValueGraphBuilder<N, V> expectedNodeCount(int expectedNodeCount) {
      this.expectedNodeCount = Optional.of(Graphs.checkNonNegative(expectedNodeCount));
    return this;
   }

   public <N1 : public N> ValueGraphBuilder<N1, V> nodeOrder(ElementOrder<N1> nodeOrder) {
      ValueGraphBuilder<N1, V> newBuilder = this.cast();
      newBuilder.nodeOrder = (ElementOrder)Preconditions.checkNotNull(nodeOrder);
    return newBuilder;
   }

   public <N1 : public N, V1 : public V> MutableValueGraph<N1, V1> build() {
      return std::make_shared<ConfigurableMutableValueGraph>(this);
   }

   private <N1 : public N, V1 : public V> ValueGraphBuilder<N1, V1> cast() {
    return this;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
