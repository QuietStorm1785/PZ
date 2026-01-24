#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace ai {
namespace astar {

class AStarPathFinder {
public:
	// Returns the final node if found, nullptr otherwise
	std::shared_ptr<Mover> search(const std::shared_ptr<Mover>& start,
								  const std::shared_ptr<IPathfinder>& goal,
								  int maxSteps = -1);
	// Returns the path from start to goal as a vector of nodes
	std::vector<std::shared_ptr<Mover>> shortestPath(const std::shared_ptr<Mover>& start,
													 const std::shared_ptr<IPathfinder>& goal,
													 int maxSteps = -1);
}
} // namespace astar
} // namespace ai
} // namespace zombie
