#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/adapters/XmlAdapter.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class AnyTypeAdapter : public XmlAdapter {
public:
    void* unmarshal(void* v) {
    return v;
   }

    void* marshal(void* v) {
    return v;
   }
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
