#include "zombie/ai/astar/AStarPathFinder.h"

namespace zombie {
namespace ai {
namespace astar {
std::shared_ptr<Mover> AStarPathFinder::search(const std::shared_ptr<Mover>& start,
											   const std::shared_ptr<IPathfinder>& goal,
											   int maxSteps) {
	struct NodeCmp {
		bool operator()(const std::shared_ptr<Mover>& a, const std::shared_ptr<Mover>& b) const {
			// Replace with actual cost/heuristic logic
			return a->getPathFindIndex() > b->getPathFindIndex();
		}
	};
	std::priority_queue<std::shared_ptr<Mover>, std::vector<std::shared_ptr<Mover>>, NodeCmp> openSet;
	std::unordered_set<int> closedSet;
	int steps = 0;

	openSet.push(start);

	while (!openSet.empty() && (maxSteps < 0 || steps < maxSteps)) {
		auto current = openSet.top();
		openSet.pop();
		++steps;

		// Replace with actual goal logic
		if (goal->getName() == "goal") {
			return current;
		}
		closedSet.insert(current->getID());

		// Replace with actual successor logic
		std::vector<std::shared_ptr<Mover>> successors; // Fill with real successors
		for (auto& succ : successors) {
			if (closedSet.count(succ->getID())) continue;
			openSet.push(succ);
		}
	}
	return nullptr;
}

std::vector<std::shared_ptr<Mover>> AStarPathFinder::shortestPath(const std::shared_ptr<Mover>& start,
																  const std::shared_ptr<IPathfinder>& goal,
																  int maxSteps) {
	auto finalNode = search(start, goal, maxSteps);
	std::vector<std::shared_ptr<Mover>> path;
	if (!finalNode) return path;
	// Replace with actual path reconstruction logic
	path.push_back(finalNode);
	return path;
}
} // namespace astar
} // namespace ai
} // namespace zombie
