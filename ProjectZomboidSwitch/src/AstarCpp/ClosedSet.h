#ifndef ASTARCPP_CLOSEDSET_H
#define ASTARCPP_CLOSEDSET_H

#include "IClosedSet.h"
#include <vector>
#include <algorithm>

class ClosedSet : public IClosedSet {
public:
    bool contains(const std::shared_ptr<ISearchNode>& node) const override {
        return std::find(list_.begin(), list_.end(), node) != list_.end();
    }
    void add(const std::shared_ptr<ISearchNode>& node) override {
        list_.push_back(node);
    }
    std::shared_ptr<ISearchNode> min() const override {
        return *std::min_element(list_.begin(), list_.end(), [](const auto& a, const auto& b) { return a->f() < b->f(); });
    }
    void clear() override {
        list_.clear();
    }
private:
    std::vector<std::shared_ptr<ISearchNode>> list_;
};

#endif // ASTARCPP_CLOSEDSET_H
