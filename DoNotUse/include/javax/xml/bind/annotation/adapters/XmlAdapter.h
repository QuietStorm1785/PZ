#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace javax {
namespace xml {
namespace bind {
namespace annotation {
namespace adapters {

class XmlAdapter {
public:
    protected XmlAdapter() {
   }

   public abstract BoundType unmarshal(ValueType var1) throws Exception;

   public abstract ValueType marshal(BoundType var1) throws Exception;
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
