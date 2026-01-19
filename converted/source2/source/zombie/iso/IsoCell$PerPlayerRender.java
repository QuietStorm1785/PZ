package zombie.iso;

public final class IsoCell$PerPlayerRender {
   public final IsoGridStack GridStacks = new IsoGridStack(9);
   public boolean[][][] VisiOccludedFlags;
   public boolean[][] VisiCulledFlags;
   public short[][][] StencilValues;
   public boolean[][] FlattenGrassEtc;
   public int minX;
   public int minY;
   public int maxX;
   public int maxY;

   public void setSize(int var1, int var2) {
      if (this.VisiOccludedFlags == null || this.VisiOccludedFlags.length < var1 || this.VisiOccludedFlags[0].length < var2) {
         this.VisiOccludedFlags = new boolean[var1][var2][2];
         this.VisiCulledFlags = new boolean[var1][var2];
         this.StencilValues = new short[var1][var2][2];
         this.FlattenGrassEtc = new boolean[var1][var2];
      }
   }
}
