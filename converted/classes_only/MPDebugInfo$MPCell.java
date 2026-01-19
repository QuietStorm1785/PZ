package zombie.popman;

final class MPDebugInfo$MPCell {
   public short cx;
   public short cy;
   public short currentPopulation;
   public short desiredPopulation;
   public float lastRepopTime;

   private MPDebugInfo$MPCell() {
   }

   MPDebugInfo$MPCell init(int var1, int var2, int var3, int var4, float var5) {
      this.cx = (short)var1;
      this.cy = (short)var2;
      this.currentPopulation = (short)var3;
      this.desiredPopulation = (short)var4;
      this.lastRepopTime = var5;
      return this;
   }
}
