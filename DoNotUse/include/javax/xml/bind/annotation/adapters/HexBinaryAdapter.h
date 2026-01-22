#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/DatatypeConverter.h"

namespace javax {
namespace xml {
namespace bind {
namespace annotation {
namespace adapters {


class HexBinaryAdapter : public XmlAdapter {
public:
   public byte[] unmarshal(std::string s) {
    return s = = nullptr ? nullptr : DatatypeConverter.parseHexBinary(s);
   }

    std::string marshal(byte[] bytes) {
    return bytes = = nullptr ? nullptr : DatatypeConverter.printHexBinary(bytes);
   }
}
} // namespace adapters
} // namespace annotation
} // namespace bind
} // namespace xml
} // namespace javax
