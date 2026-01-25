// ZNetSessionState.h
// Merged from Java source, including all inner classes as nested C++ classes.
#pragma once

#include <cstdint>

namespace zombie {
namespace network {

class ZNetSessionState {
public:
    enum State : uint8_t {
        UNKNOWN = 0,
        CONNECTING,
        CONNECTED,
        DISCONNECTED,
        // ...add more states as needed from Java source...
    };

    ZNetSessionState();
    ~ZNetSessionState();

    void setState(State s);
    State getState() const;

private:
    State state;
};

} // namespace network
} // namespace zombie
