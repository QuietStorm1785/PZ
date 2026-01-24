#ifndef ASTARCPP_ASEARCHNODE_H
#define ASTARCPP_ASEARCHNODE_H

#include "ISearchNode.h"
#include <memory>

class ASearchNode : public ISearchNode {
public:
    ASearchNode();
    double f() const override;
    double g() const override;
    void setG(double) override;
    double h() const override;
    double c(const std::shared_ptr<ISearchNode>& other) const override;
    void getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const override;
    std::shared_ptr<ISearchNode> getParent() const override;
    void setParent(const std::shared_ptr<ISearchNode>& parent) override;
    int keyCode() const override;
    bool equals(const std::shared_ptr<ISearchNode>& other) const override;
    int hashCode() const override;
    int getDepth() const override;
    void setDepth(int) override;
private:
    double g_;
    int depth_;
    std::shared_ptr<ISearchNode> parent_;
};

#endif // ASTARCPP_ASEARCHNODE_H
