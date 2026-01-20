#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/Marshaller.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {


class CycleRecoverable {
public:
    virtual ~CycleRecoverable() = default;
    Marshaller getMarshaller();
}
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
