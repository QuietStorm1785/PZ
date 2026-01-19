#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace astar {


class ISearchNode {
public:
    virtual ~ISearchNode() = default;
    double f();

    double g();

    void setG(double var1);

    double h();

    double c(ISearchNode var1);

    void getSuccessors(ArrayList<ISearchNode> var1);

    ISearchNode getParent();

    void setParent(ISearchNode var1);

    int keyCode();

    bool equals(void* var1);

    int hashCode();

    int getDepth();

    void setDepth(int var1);
}
} // namespace astar
