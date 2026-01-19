package astar;

import astar.AStar.SearchNodeComparator;
import astar.datastructures.ClosedSet;
import astar.datastructures.ClosedSetHash;
import astar.datastructures.IClosedSet;
import astar.datastructures.IOpenSet;
import astar.datastructures.OpenSet;
import java.util.ArrayList;

public class AStar {
   private int verbose = 0;
   private int maxSteps = -1;
   private int numSearchSteps;
   public ISearchNode bestNodeAfterSearch;
   private ArrayList<ISearchNode> successorNodes = new ArrayList<>();
   private final IOpenSet openSet = new OpenSet(new SearchNodeComparator());
   private final IClosedSet closedSetHash = new ClosedSetHash(new SearchNodeComparator());
   private final IClosedSet closedSetNoHash = new ClosedSet(new SearchNodeComparator());

   public ArrayList<ISearchNode> shortestPath(ISearchNode var1, IGoalNode var2) {
      ISearchNode var3 = this.search(var1, var2);
      return var3 == null ? null : path(var3);
   }

   public ISearchNode search(ISearchNode var1, IGoalNode var2) {
      boolean var3 = var1.keyCode() != null;
      var1.setDepth(0);
      this.openSet.clear();
      this.openSet.add(var1);
      IClosedSet var4 = var3 ? this.closedSetHash : this.closedSetNoHash;
      var4.clear();

      for (this.numSearchSteps = 0; this.openSet.size() > 0 && (this.maxSteps < 0 || this.numSearchSteps < this.maxSteps); this.numSearchSteps++) {
         ISearchNode var5 = this.openSet.poll();
         if (var2.inGoal(var5)) {
            this.bestNodeAfterSearch = var5;
            return var5;
         }

         this.successorNodes.clear();
         var5.getSuccessors(this.successorNodes);

         for (int var6 = 0; var6 < this.successorNodes.size(); var6++) {
            ISearchNode var7 = this.successorNodes.get(var6);
            if (!var4.contains(var7)) {
               ISearchNode var9 = this.openSet.getNode(var7);
               boolean var8;
               if (var9 != null) {
                  var7 = var9;
                  var8 = true;
               } else {
                  var8 = false;
               }

               double var10 = var5.g() + var5.c(var7);
               if (!var8 || !(var10 >= var7.g())) {
                  var7.setParent(var5);
                  var7.setDepth(var5.getDepth() + 1);
                  if (var8) {
                     this.openSet.remove(var7);
                     var7.setG(var10);
                     this.openSet.add(var7);
                  } else {
                     var7.setG(var10);
                     this.openSet.add(var7);
                  }
               }
            }
         }

         var4.add(var5);
      }

      this.bestNodeAfterSearch = var4.min();
      return null;
   }

   public static ArrayList<ISearchNode> path(ISearchNode var0) {
      ArrayList var1 = new ArrayList();
      var1.add(var0);
      ISearchNode var2 = var0;

      while (var2.getParent() != null) {
         ISearchNode var3 = var2.getParent();
         var1.add(0, var3);
         var2 = var3;
      }

      return var1;
   }

   public int numSearchSteps() {
      return this.numSearchSteps;
   }

   public ISearchNode bestNodeAfterSearch() {
      return this.bestNodeAfterSearch;
   }

   public void setMaxSteps(int var1) {
      this.maxSteps = var1;
   }
}
