#include "zombie/ai/states/PathFindState.h"

namespace zombie {
namespace ai {
namespace states {

PathFindState2& PathFindState::instance() {
    static PathFindState2 _instance;
    return _instance;
}

} // namespace states
} // namespace ai
} // namespace zombie
