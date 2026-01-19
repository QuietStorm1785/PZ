package zombie.gameStates;

import java.util.Stack;
import zombie.ai.astar.Mover;
import zombie.core.SpriteRenderer;
import zombie.core.utils.BooleanGrid;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.SpriteDetails.IsoObjectType;
import zombie.iso.areas.IsoBuilding;

class DebugChunkState$FloodFill {
   private IsoGridSquare start;
   private final int FLOOD_SIZE;
   private BooleanGrid visited;
   private Stack<IsoGridSquare> stack;
   private IsoBuilding building;
   private Mover mover;

   private DebugChunkState$FloodFill(DebugChunkState var1) {
      this.this$0 = var1;
      this.start = null;
      this.FLOOD_SIZE = 11;
      this.visited = new BooleanGrid(11, 11);
      this.stack = new Stack<>();
      this.building = null;
      this.mover = null;
   }

   void calculate(Mover var1, IsoGridSquare var2) {
      this.start = var2;
      this.mover = var1;
      if (this.start.getRoom() != null) {
         this.building = this.start.getRoom().getBuilding();
      }

      boolean var3 = false;
      boolean var4 = false;
      if (this.push(this.start.getX(), this.start.getY())) {
         while ((var2 = this.pop()) != null) {
            int var6 = var2.getX();
            int var5 = var2.getY();

            while (this.shouldVisit(var6, var5, var6, var5 - 1)) {
               var5--;
            }

            var4 = false;
            var3 = false;

            do {
               this.visited.setValue(this.gridX(var6), this.gridY(var5), true);
               if (!var3 && this.shouldVisit(var6, var5, var6 - 1, var5)) {
                  if (!this.push(var6 - 1, var5)) {
                     return;
                  }

                  var3 = true;
               } else if (var3 && !this.shouldVisit(var6, var5, var6 - 1, var5)) {
                  var3 = false;
               } else if (var3 && !this.shouldVisit(var6 - 1, var5, var6 - 1, var5 - 1) && !this.push(var6 - 1, var5)) {
                  return;
               }

               if (!var4 && this.shouldVisit(var6, var5, var6 + 1, var5)) {
                  if (!this.push(var6 + 1, var5)) {
                     return;
                  }

                  var4 = true;
               } else if (var4 && !this.shouldVisit(var6, var5, var6 + 1, var5)) {
                  var4 = false;
               } else if (var4 && !this.shouldVisit(var6 + 1, var5, var6 + 1, var5 - 1) && !this.push(var6 + 1, var5)) {
                  return;
               }

               var5++;
            } while (this.shouldVisit(var6, var5 - 1, var6, var5));
         }
      }
   }

   boolean shouldVisit(int var1, int var2, int var3, int var4) {
      if (this.gridX(var3) < 11 && this.gridX(var3) >= 0) {
         if (this.gridY(var4) < 11 && this.gridY(var4) >= 0) {
            if (this.visited.getValue(this.gridX(var3), this.gridY(var4))) {
               return false;
            } else {
               IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var3, var4, this.start.getZ());
               if (var5 == null) {
                  return false;
               } else if (var5.Has(IsoObjectType.stairsBN) || var5.Has(IsoObjectType.stairsMN) || var5.Has(IsoObjectType.stairsTN)) {
                  return false;
               } else if (var5.Has(IsoObjectType.stairsBW) || var5.Has(IsoObjectType.stairsMW) || var5.Has(IsoObjectType.stairsTW)) {
                  return false;
               } else if (var5.getRoom() != null && this.building == null) {
                  return false;
               } else {
                  return var5.getRoom() == null && this.building != null
                     ? false
                     : !IsoWorld.instance.CurrentCell.blocked(this.mover, var3, var4, this.start.getZ(), var1, var2, this.start.getZ());
               }
            }
         } else {
            return false;
         }
      } else {
         return false;
      }
   }

   boolean push(int var1, int var2) {
      IsoGridSquare var3 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, this.start.getZ());
      this.stack.push(var3);
      return true;
   }

   IsoGridSquare pop() {
      return this.stack.isEmpty() ? null : this.stack.pop();
   }

   int gridX(int var1) {
      return var1 - (this.start.getX() - 5);
   }

   int gridY(int var1) {
      return var1 - (this.start.getY() - 5);
   }

   int gridX(IsoGridSquare var1) {
      return var1.getX() - (this.start.getX() - 5);
   }

   int gridY(IsoGridSquare var1) {
      return var1.getY() - (this.start.getY() - 5);
   }

   void draw() {
      int var1 = this.start.getX() - 5;
      int var2 = this.start.getY() - 5;

      for (int var3 = 0; var3 < 11; var3++) {
         for (int var4 = 0; var4 < 11; var4++) {
            if (this.visited.getValue(var4, var3)) {
               int var5 = (int)IsoUtils.XToScreenExact(var1 + var4, var2 + var3 + 1, this.start.getZ(), 0);
               int var6 = (int)IsoUtils.YToScreenExact(var1 + var4, var2 + var3 + 1, this.start.getZ(), 0);
               SpriteRenderer.instance.renderPoly(var5, var6, var5 + 32, var6 - 16, var5 + 64, var6, var5 + 32, var6 + 16, 1.0F, 1.0F, 0.0F, 0.5F);
            }
         }
      }
   }
}
