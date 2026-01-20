#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace google {
namespace common {
namespace graph {

class DirectedGraphConnections {
public:
    const void* successorValue;

   DirectedGraphConnections$PredAndSucc(Object successorValue) {
      this.successorValue = successorValue;
   }
}
} // namespace graph
} // namespace common
} // namespace google
} // namespace com
