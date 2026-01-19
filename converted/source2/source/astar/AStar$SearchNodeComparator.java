package astar;

import java.util.Comparator;

class AStar$SearchNodeComparator implements Comparator<ISearchNode> {
   public int compare(ISearchNode var1, ISearchNode var2) {
      return Double.compare(var1.f(), var2.f());
   }
}
