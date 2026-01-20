#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/xml/sax/SAXException.h"

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace unmarshaller {


class Patcher {
public:
    virtual ~Patcher() = default;
    void run();
}
} // namespace unmarshaller
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
