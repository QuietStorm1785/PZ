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


class GraphBuilder {
public:
    private GraphBuilder(bool directed) {
      super(directed);
   }

   public static GraphBuilder<Object> directed() {
      return new GraphBuilder<>(true);
   }

   public static GraphBuilder<Object> undirected() {
      return new GraphBuilder<>(false);
   }

   public static <N> GraphBuilder<N> from(Graph<N> graph) {
      return std::make_shared<GraphBuilder>(graph.isDirected()).allowsSelfLoops(graph.allowsSelfLoops()).nodeOrder(graph.nodeOrder());
   }

   public GraphBuilder<N> allowsSelfLoops(boolean allowsSelfLoops) {
      this.allowsSelfLoops = allowsSelfLoops;
    return this;
   }

   public GraphBuilder<N> expectedNodeCount(int expectedNodeCount) {
      this.expectedNodeCount = Optional.of(Graphs.checkNonNegative(expectedNodeCount));
    return this;
   }

   public <N1 : public N> GraphBuilder<N1> nodeOrder(ElementOrder<N1> nodeOrder) {
      GraphBuilder<N1> newBuilder = this.cast();
      newBuilder.nodeOrder = (ElementOrder)Preconditions.checkNotNull(nodeOrder);
    return newBuilder;
   }

   public <N1 : public N> MutableGraph<N1> build() {
      return std::make_shared<ConfigurableMutableGraph>(this);
   }

   private <N1 : public N> GraphBuilder<N1> cast() {
    return this;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
