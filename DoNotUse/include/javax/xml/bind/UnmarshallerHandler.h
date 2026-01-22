#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/ContentHandler.h"

namespace javax {
namespace xml {
namespace bind {


class UnmarshallerHandler {
public:
    virtual ~UnmarshallerHandler() = default;
    void* getResult();
}
} // namespace bind
} // namespace xml
} // namespace javax
