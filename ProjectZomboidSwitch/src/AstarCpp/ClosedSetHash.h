#ifndef ASTARCPP_CLOSEDSETHASH_H
#define ASTARCPP_CLOSEDSETHASH_H

#include "IClosedSet.h"
#include <unordered_map>
#include <memory>

class ClosedSetHash : public IClosedSet {
public:
    bool contains(const std::shared_ptr<ISearchNode>& node) const override {
        return map_.find(node->keyCode()) != map_.end();
    }
    void add(const std::shared_ptr<ISearchNode>& node) override {
        map_[node->keyCode()] = node;
    }
    std::shared_ptr<ISearchNode> min() const override {
        std::shared_ptr<ISearchNode> minNode;
        for (const auto& kv : map_) {
            if (!minNode || kv.second->f() < minNode->f()) minNode = kv.second;
        }
        return minNode;
    }
    void clear() override {
        map_.clear();
    }
private:
    std::unordered_map<int, std::shared_ptr<ISearchNode>> map_;
};

#endif // ASTARCPP_CLOSEDSETHASH_H
