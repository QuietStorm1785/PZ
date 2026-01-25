// ZNetSessionState.cpp
// Merged from Java source, including all inner classes as nested C++ classes.
#include "ZNetSessionState.h"

namespace zombie {
namespace network {

ZNetSessionState::ZNetSessionState() : state(UNKNOWN) {}
ZNetSessionState::~ZNetSessionState() {}

void ZNetSessionState::setState(State s) {
    state = s;
}

ZNetSessionState::State ZNetSessionState::getState() const {
    return state;
}

// ...implement more nested class logic as needed...

} // namespace network
} // namespace zombie
