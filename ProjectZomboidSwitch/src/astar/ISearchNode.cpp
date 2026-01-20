#include <vector>
#include "astar/ISearchNode.h"

namespace astar {

double ISearchNode::f() {
    // TODO: Implement f
    return 0;
}

double ISearchNode::g() {
    // TODO: Implement g
    return 0;
}

void ISearchNode::setG(double var1) {
    // TODO: Implement setG
}

double ISearchNode::h() {
    // TODO: Implement h
    return 0;
}

double ISearchNode::c(ISearchNode var1) {
    // TODO: Implement c
    return 0;
}

void ISearchNode::getSuccessors(std::vector<ISearchNode> var1) {
    // TODO: Implement getSuccessors
}

ISearchNode ISearchNode::getParent() {
    // TODO: Implement getParent
    // ISearchNode is now a pure interface; no implementation needed.
}
