#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace astar {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

 bool equals(void *var1);

 int hashCode();

 int getDepth();

 void setDepth(int var1);
}
} // namespace astar
