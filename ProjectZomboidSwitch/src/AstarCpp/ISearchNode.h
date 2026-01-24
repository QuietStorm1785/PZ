#ifndef ASTARCPP_ISEARCHNODE_H
#define ASTARCPP_ISEARCHNODE_H

#include <vector>
#include <memory>

class ISearchNode {
public:
    virtual ~ISearchNode() = default;
    virtual double f() const = 0;
    virtual double g() const = 0;
    virtual void setG(double) = 0;
    virtual double h() const = 0;
    virtual double c(const std::shared_ptr<ISearchNode>& other) const = 0;
    virtual void getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const = 0;
    virtual std::shared_ptr<ISearchNode> getParent() const = 0;
    virtual void setParent(const std::shared_ptr<ISearchNode>& parent) = 0;
    virtual int keyCode() const = 0;
    virtual bool equals(const std::shared_ptr<ISearchNode>& other) const = 0;
    virtual int hashCode() const = 0;
    virtual int getDepth() const = 0;
    virtual void setDepth(int) = 0;
};

#endif // ASTARCPP_ISEARCHNODE_H
