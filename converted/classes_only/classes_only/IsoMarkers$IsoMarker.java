package zombie.iso;

import java.util.ArrayList;
import se.krka.kahlua.vm.KahluaTable;
import zombie.core.textures.Texture;
import zombie.util.Type;

public final class IsoMarkers$IsoMarker {
   private int ID;
   private ArrayList<Texture> textures = new ArrayList<>();
   private ArrayList<Texture> overlayTextures = new ArrayList<>();
   private ArrayList<IsoObject> tempObjects = new ArrayList<>();
   private IsoGridSquare square;
   private float x;
   private float y;
   private float z;
   private float r;
   private float g;
   private float b;
   private float a;
   private boolean doAlpha;
   private float fadeSpeed = 0.006F;
   private float alpha = 0.0F;
   private float alphaMax = 1.0F;
   private float alphaMin = 0.3F;
   private boolean alphaInc = true;
   private boolean active = true;
   private boolean isRemoved = false;

   public IsoMarkers$IsoMarker() {
      this.ID = IsoMarkers.NextIsoMarkerID++;
   }

   public int getID() {
      return this.ID;
   }

   public void remove() {
      this.isRemoved = true;
   }

   public boolean isRemoved() {
      return this.isRemoved;
   }

   public void init(KahluaTable var1, KahluaTable var2, int var3, int var4, int var5, IsoGridSquare var6) {
      this.square = var6;
      if (var1 != null) {
         int var7 = var1.len();

         for (int var8 = 1; var8 <= var7; var8++) {
            String var9 = (String)Type.tryCastTo(var1.rawget(var8), String.class);
            Texture var10 = Texture.trygetTexture(var9);
            if (var10 != null) {
               this.textures.add(var10);
               this.setPos(var3, var4, var5);
            }
         }
      }

      if (var2 != null) {
         int var11 = var2.len();

         for (int var12 = 1; var12 <= var11; var12++) {
            String var13 = (String)Type.tryCastTo(var2.rawget(var12), String.class);
            Texture var14 = Texture.trygetTexture(var13);
            if (var14 != null) {
               this.overlayTextures.add(var14);
               this.setPos(var3, var4, var5);
            }
         }
      }
   }

   public void init(KahluaTable var1, KahluaTable var2, int var3, int var4, int var5, IsoGridSquare var6, boolean var7) {
      this.square = var6;
      if (var7) {
         if (var1 != null) {
            int var8 = var1.len();

            for (int var9 = 1; var9 <= var8; var9++) {
               String var10 = (String)Type.tryCastTo(var1.rawget(var9), String.class);
               Texture var11 = Texture.trygetTexture(var10);
               if (var11 != null) {
                  IsoObject var12 = new IsoObject(var6.getCell(), var6, var11.getName());
                  this.tempObjects.add(var12);
                  this.addTempSquareObject(var12);
                  this.setPos(var3, var4, var5);
               }
            }
         }
      } else {
         this.init(var1, var2, var3, var4, var5, var6);
      }
   }

   public void init(String var1, int var2, int var3, int var4, IsoGridSquare var5, boolean var6) {
      this.square = var5;
      if (var6 && var1 != null) {
         IsoObject var7 = IsoObject.getNew(var5, var1, var1, false);
         this.tempObjects.add(var7);
         this.addTempSquareObject(var7);
         this.setPos(var2, var3, var4);
      }
   }

   public boolean hasTempSquareObject() {
      return this.tempObjects.size() > 0;
   }

   public void addTempSquareObject(IsoObject var1) {
      this.square.localTemporaryObjects.add(var1);
   }

   public void removeTempSquareObjects() {
      this.square.localTemporaryObjects.clear();
   }

   public float getX() {
      return this.x;
   }

   public float getY() {
      return this.y;
   }

   public float getZ() {
      return this.z;
   }

   public float getR() {
      return this.r;
   }

   public float getG() {
      return this.g;
   }

   public float getB() {
      return this.b;
   }

   public float getA() {
      return this.a;
   }

   public void setR(float var1) {
      this.r = var1;
   }

   public void setG(float var1) {
      this.g = var1;
   }

   public void setB(float var1) {
      this.b = var1;
   }

   public void setA(float var1) {
      this.a = var1;
   }

   public float getAlpha() {
      return this.alpha;
   }

   public void setAlpha(float var1) {
      this.alpha = var1;
   }

   public float getAlphaMax() {
      return this.alphaMax;
   }

   public void setAlphaMax(float var1) {
      this.alphaMax = var1;
   }

   public float getAlphaMin() {
      return this.alphaMin;
   }

   public void setAlphaMin(float var1) {
      this.alphaMin = var1;
   }

   public boolean isDoAlpha() {
      return this.doAlpha;
   }

   public void setDoAlpha(boolean var1) {
      this.doAlpha = var1;
   }

   public float getFadeSpeed() {
      return this.fadeSpeed;
   }

   public void setFadeSpeed(float var1) {
      this.fadeSpeed = var1;
   }

   public IsoGridSquare getSquare() {
      return this.square;
   }

   public void setSquare(IsoGridSquare var1) {
      this.square = var1;
   }

   public void setPos(int var1, int var2, int var3) {
      this.x = var1 + 0.5F;
      this.y = var2 + 0.5F;
      this.z = var3;
   }

   public boolean isActive() {
      return this.active;
   }

   public void setActive(boolean var1) {
      this.active = var1;
   }
}
