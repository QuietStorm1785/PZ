#include "astar/ASearchNode.h"

namespace astar {

double ASearchNode::f() const {
    return g_ + h();
}

double ASearchNode::g() const {
    return g_;
}

void ASearchNode::setG(double value) {
    g_ = value;
}

double ASearchNode::h() const {
    // TODO: Implement heuristic
    return 0.0;
}

double ASearchNode::c(const std::shared_ptr<ISearchNode>& other) const {
    // TODO: Implement cost function
    return 0.0;
}

void ASearchNode::getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const {
    // TODO: Implement successor generation
}

std::shared_ptr<ISearchNode> ASearchNode::getParent() const {
    return parent_;
}

void ASearchNode::setParent(const std::shared_ptr<ISearchNode>& parent) {
    parent_ = parent;
}

int ASearchNode::keyCode() const {
    // TODO: Implement keyCode
    return 0;
}

bool ASearchNode::equals(const std::shared_ptr<ISearchNode>& other) const {
    // TODO: Implement equality
    return false;
}

int ASearchNode::hashCode() const {
    // TODO: Implement hashCode
    return 0;
}

int ASearchNode::getDepth() const {
    return depth_;
}

void ASearchNode::setDepth(int depth) {
    depth_ = depth;
}

} // namespace astar
