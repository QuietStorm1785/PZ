#ifndef ASTARCPP_IOPENSET_H
#define ASTARCPP_IOPENSET_H

#include "ISearchNode.h"
#include <memory>

class IOpenSet {
public:
    virtual ~IOpenSet() = default;
    virtual void add(const std::shared_ptr<ISearchNode>& node) = 0;
    virtual void remove(const std::shared_ptr<ISearchNode>& node) = 0;
    virtual std::shared_ptr<ISearchNode> poll() = 0;
    virtual std::shared_ptr<ISearchNode> getNode(const std::shared_ptr<ISearchNode>& node) = 0;
    virtual int size() const = 0;
    virtual void clear() = 0;
};

#endif // ASTARCPP_IOPENSET_H
