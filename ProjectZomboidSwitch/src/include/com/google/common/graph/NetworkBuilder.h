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


class NetworkBuilder {
public:
    bool allowsParallelEdges = false;
   ElementOrder<? super E> edgeOrder = ElementOrder.insertion();
   Optional<int> expectedEdgeCount = Optional.absent();

    private NetworkBuilder(bool directed) {
      super(directed);
   }

   public static NetworkBuilder<Object, Object> directed() {
      return new NetworkBuilder<>(true);
   }

   public static NetworkBuilder<Object, Object> undirected() {
      return new NetworkBuilder<>(false);
   }

   public static <N, E> NetworkBuilder<N, E> from(Network<N, E> network) {
      return new NetworkBuilder<N, E>(network.isDirected())
         .allowsParallelEdges(network.allowsParallelEdges())
         .allowsSelfLoops(network.allowsSelfLoops())
         .<N>nodeOrder(network.nodeOrder())
         .edgeOrder(network.edgeOrder());
   }

   public NetworkBuilder<N, E> allowsParallelEdges(boolean allowsParallelEdges) {
      this.allowsParallelEdges = allowsParallelEdges;
    return this;
   }

   public NetworkBuilder<N, E> allowsSelfLoops(boolean allowsSelfLoops) {
      this.allowsSelfLoops = allowsSelfLoops;
    return this;
   }

   public NetworkBuilder<N, E> expectedNodeCount(int expectedNodeCount) {
      this.expectedNodeCount = Optional.of(Graphs.checkNonNegative(expectedNodeCount));
    return this;
   }

   public NetworkBuilder<N, E> expectedEdgeCount(int expectedEdgeCount) {
      this.expectedEdgeCount = Optional.of(Graphs.checkNonNegative(expectedEdgeCount));
    return this;
   }

   public <N1 : public N> NetworkBuilder<N1, E> nodeOrder(ElementOrder<N1> nodeOrder) {
      NetworkBuilder<N1, E> newBuilder = this.cast();
      newBuilder.nodeOrder = (ElementOrder)Preconditions.checkNotNull(nodeOrder);
    return newBuilder;
   }

   public <E1 : public E> NetworkBuilder<N, E1> edgeOrder(ElementOrder<E1> edgeOrder) {
      NetworkBuilder<N, E1> newBuilder = this.cast();
      newBuilder.edgeOrder = (ElementOrder<? super E1>)Preconditions.checkNotNull(edgeOrder);
    return newBuilder;
   }

   public <N1 : public N, E1 : public E> MutableNetwork<N1, E1> build() {
      return std::make_shared<ConfigurableMutableNetwork>(this);
   }

   private <N1 : public N, E1 : public E> NetworkBuilder<N1, E1> cast() {
    return this;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
