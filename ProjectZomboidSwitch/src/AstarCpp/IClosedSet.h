#ifndef ASTARCPP_ICLOSEDSET_H
#define ASTARCPP_ICLOSEDSET_H

#include "ISearchNode.h"
#include <memory>

class IClosedSet {
public:
    virtual ~IClosedSet() = default;
    virtual bool contains(const std::shared_ptr<ISearchNode>& node) const = 0;
    virtual void add(const std::shared_ptr<ISearchNode>& node) = 0;
    virtual std::shared_ptr<ISearchNode> min() const = 0;
    virtual void clear() = 0;
};

#endif // ASTARCPP_ICLOSEDSET_H
