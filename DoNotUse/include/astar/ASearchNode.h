#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {

class ASearchNode : public ISearchNode {
public:
   ASearchNode() : g_(0.0), depth_(0) {}

   double f() const override {
      return g_ + h();
   }

   double g() const override {
      return g_;
   }

   void setG(double value) override {
      g_ = value;
   }

   double h() const override {
      // TODO: Implement heuristic
      return 0.0;
   }

   double c(const std::shared_ptr<ISearchNode>& other) const override {
      // TODO: Implement cost function
      return 0.0;
   }

   void getSuccessors(std::vector<std::shared_ptr<ISearchNode>>& outSuccessors) const override {
      // TODO: Implement successor generation
   }

   std::shared_ptr<ISearchNode> getParent() const override {
      return parent_;
   }

   void setParent(const std::shared_ptr<ISearchNode>& parent) override {
      parent_ = parent;
   }

   int keyCode() const override {
      // TODO: Implement keyCode
      return 0;
   }

   bool equals(const std::shared_ptr<ISearchNode>& other) const override {
      // TODO: Implement equality
      return false;
   }

   int hashCode() const override {
      // TODO: Implement hashCode
      return 0;
   }

   int getDepth() const override {
      return depth_;
   }

   void setDepth(int depth) override {
      depth_ = depth;
   }

private:
   double g_;
   int depth_;
   std::shared_ptr<ISearchNode> parent_;
};
} // namespace astar
