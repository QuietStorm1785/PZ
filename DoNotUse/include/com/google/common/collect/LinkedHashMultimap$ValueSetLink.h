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
namespace collect {

class LinkedHashMultimap {
public:
    virtual ~LinkedHashMultimap() = default;
   LinkedHashMultimap$ValueSetLink<K, V> getPredecessorInValueSet();

   LinkedHashMultimap$ValueSetLink<K, V> getSuccessorInValueSet();

    void setPredecessorInValueSet(V> var1);

    void setSuccessorInValueSet(V> var1);
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
