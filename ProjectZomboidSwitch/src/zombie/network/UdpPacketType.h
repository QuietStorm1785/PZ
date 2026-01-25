// UdpPacketType.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <cstdint>

namespace zombie {
namespace network {

class UdpPacketType {
public:
    enum Type : uint8_t {
        UNKNOWN = 0,
        DATA,
        ACK,
        NACK,
        // ...add more types as needed from Java source...
    };

    UdpPacketType();
    ~UdpPacketType();

    void setType(Type t);
    Type getType() const;

private:
    Type type;
};

} // namespace network
} // namespace zombie
