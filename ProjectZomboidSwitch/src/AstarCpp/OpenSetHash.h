#ifndef ASTARCPP_OPENSETHASH_H
#define ASTARCPP_OPENSETHASH_H

#include "IOpenSet.h"
#include <unordered_map>
#include <queue>
#include <memory>

class OpenSetHash : public IOpenSet {
public:
    void add(const std::shared_ptr<ISearchNode>& node) override {
        map_[node->keyCode()] = node;
        queue_.push(node);
    }
    void remove(const std::shared_ptr<ISearchNode>& node) override {
        map_.erase(node->keyCode());
        // Rebuild queue
        std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp> newQ;
        for (const auto& kv : map_) newQ.push(kv.second);
        queue_ = std::move(newQ);
    }
    std::shared_ptr<ISearchNode> poll() override {
        while (!queue_.empty()) {
            auto node = queue_.top();
            queue_.pop();
            if (map_.count(node->keyCode())) {
                map_.erase(node->keyCode());
                return node;
            }
        }
        return nullptr;
    }
    std::shared_ptr<ISearchNode> getNode(const std::shared_ptr<ISearchNode>& node) override {
        auto it = map_.find(node->keyCode());
        return it != map_.end() ? it->second : nullptr;
    }
    int size() const override { return static_cast<int>(map_.size()); }
    void clear() override {
        map_.clear();
        queue_ = std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp>();
    }
private:
    struct NodeCmp {
        bool operator()(const std::shared_ptr<ISearchNode>& a, const std::shared_ptr<ISearchNode>& b) const {
            return a->f() > b->f();
        }
    };
    std::unordered_map<int, std::shared_ptr<ISearchNode>> map_;
    std::priority_queue<std::shared_ptr<ISearchNode>, std::vector<std::shared_ptr<ISearchNode>>, NodeCmp> queue_;
};

#endif // ASTARCPP_OPENSETHASH_H
