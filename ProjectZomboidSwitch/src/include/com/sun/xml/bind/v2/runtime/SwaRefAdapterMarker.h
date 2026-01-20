#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/activation/DataHandler.h"
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace runtime {


class SwaRefAdapterMarker : public XmlAdapter {
public:
    DataHandler unmarshal(const std::string& v) {
      throw IllegalStateException("Not implemented");
   }

    std::string marshal(DataHandler v) {
      throw IllegalStateException("Not implemented");
   }
}
} // namespace runtime
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
