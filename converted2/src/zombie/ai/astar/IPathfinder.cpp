#include "zombie/ai/astar/IPathfinder.h"

namespace zombie {
namespace ai {
namespace astar {

void IPathfinder::Failed(Mover mover) {
  // TODO: Implement Failed
}

void IPathfinder::Succeeded(Path path, Mover mover) {
  // TODO: Implement Succeeded
}

std::string IPathfinder::getName() {
  // TODO: Implement getName
  return "";
}

} // namespace astar
} // namespace ai
} // namespace zombie
