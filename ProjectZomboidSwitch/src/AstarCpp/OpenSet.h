#ifndef ASTARCPP_OPENSET_H
#define ASTARCPP_OPENSET_H

#include "IOpenSet.h"
#include <queue>
#include <vector>
#include <algorithm>

class OpenSet : public IOpenSet {
public:
    void add(const std::shared_ptr<ISearchNode>& node) override {
        queue_.push(node);
        array_.push_back(node);
    }
    void remove(const std::shared_ptr<ISearchNode>& node) override {
        array_.erase(std::remove(array_.begin(), array_.end(), node), array_.end());
        // Rebuild queue
        std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp> newQ;
        for (auto& n : array_) newQ.push(n);
        queue_ = std::move(newQ);
    }
    std::shared_ptr<ISearchNode> poll() override {
        if (queue_.empty()) return nullptr;
        auto node = queue_.top();
        queue_.pop();
        array_.erase(std::remove(array_.begin(), array_.end(), node), array_.end());
        return node;
    }
    std::shared_ptr<ISearchNode> getNode(const std::shared_ptr<ISearchNode>& node) override {
        auto it = std::find(array_.begin(), array_.end(), node);
        return it != array_.end() ? *it : nullptr;
    }
    int size() const override { return static_cast<int>(array_.size()); }
    void clear() override {
        array_.clear();
        queue_ = std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp>();
    }
private:
    struct NodeCmp {
        bool operator()(const std::shared_ptr<ISearchNode>& a, const std::shared_ptr<ISearchNode>& b) const {
            return a->f() > b->f();
        }
    };
    std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp> queue_;
    std::vector<std::shared_ptr<ISearchNode>> array_;
};

#endif // ASTARCPP_OPENSET_H
