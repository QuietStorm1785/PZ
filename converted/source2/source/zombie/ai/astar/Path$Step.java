package zombie.ai.astar;

public class Path$Step {
   public int x;
   public int y;
   public int z;

   public Path$Step(int var1, int var2, int var3) {
      this.x = var1;
      this.y = var2;
      this.z = var3;
   }

   public Path$Step() {
   }

   @Override
   public boolean equals(Object var1) {
      return !(var1 instanceof Path$Step var2) ? false : var2.x == this.x && var2.y == this.y && var2.z == this.z;
   }

   public int getX() {
      return this.x;
   }

   public int getY() {
      return this.y;
   }

   public int getZ() {
      return this.z;
   }

   @Override
   public int hashCode() {
      return this.x * this.y * this.z;
   }
}
