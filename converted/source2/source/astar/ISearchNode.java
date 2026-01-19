package astar;

import java.util.ArrayList;

public interface ISearchNode {
   double f();

   double g();

   void setG(double var1);

   double h();

   double c(ISearchNode var1);

   void getSuccessors(ArrayList<ISearchNode> var1);

   ISearchNode getParent();

   void setParent(ISearchNode var1);

   Integer keyCode();

   @Override
   boolean equals(Object var1);

   @Override
   int hashCode();

   int getDepth();

   void setDepth(int var1);
}
