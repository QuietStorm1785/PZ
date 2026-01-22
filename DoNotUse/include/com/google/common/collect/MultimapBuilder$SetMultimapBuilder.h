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

class MultimapBuilder {
public:
   MultimapBuilder$SetMultimapBuilder() {
      super(nullptr);
   }

   public abstract <K : public K0, V : public V0> SetMultimap<K, V> build();

   public <K : public K0, V : public V0> SetMultimap<K, V> build(Multimap<? : public K, ? : public V> multimap) {
      return (SetMultimap<K, V>)super.build(multimap);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
