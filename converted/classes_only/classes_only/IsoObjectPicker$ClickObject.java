package zombie.iso;

import zombie.characters.IsoPlayer;
import zombie.iso.SpriteDetails.IsoFlagType;
import zombie.iso.SpriteDetails.IsoObjectType;
import zombie.iso.objects.IsoCurtain;
import zombie.iso.objects.IsoDoor;
import zombie.iso.objects.IsoLightSwitch;
import zombie.iso.objects.IsoThumpable;
import zombie.iso.objects.IsoWaveSignal;
import zombie.iso.objects.IsoWindow;
import zombie.iso.sprite.IsoSprite;
import zombie.util.Type;

public final class IsoObjectPicker$ClickObject {
   public int height;
   public IsoGridSquare square;
   public IsoObject tile;
   public int width;
   public int x;
   public int y;
   public int lx;
   public int ly;
   public float scaleX;
   public float scaleY;
   private boolean flip;
   private int score;

   public int calculateScore() {
      float var1 = 1.0F;
      IsoPlayer var2 = IsoPlayer.getInstance();
      IsoGridSquare var3 = var2.getCurrentSquare();
      IsoObjectPicker.tempo.x = this.square.getX() + 0.5F;
      IsoObjectPicker.tempo.y = this.square.getY() + 0.5F;
      IsoObjectPicker.tempo.x = IsoObjectPicker.tempo.x - var2.getX();
      IsoObjectPicker.tempo.y = IsoObjectPicker.tempo.y - var2.getY();
      IsoObjectPicker.tempo.normalize();
      Vector2 var4 = var2.getVectorFromDirection(IsoObjectPicker.tempo2);
      float var5 = var4.dot(IsoObjectPicker.tempo);
      var1 += Math.abs(var5 * 4.0F);
      IsoGridSquare var6 = this.square;
      IsoObject var7 = this.tile;
      IsoSprite var8 = var7.sprite;
      IsoDoor var9 = (IsoDoor)Type.tryCastTo(var7, IsoDoor.class);
      IsoThumpable var10 = (IsoThumpable)Type.tryCastTo(var7, IsoThumpable.class);
      if (var9 == null && (var10 == null || !var10.isDoor())) {
         if (var7 instanceof IsoWindow) {
            var1 += 4.0F;
            if (var2.getZ() > var6.getZ()) {
               var1 -= 1000.0F;
            }
         } else {
            if (var3 != null && var6.getRoom() == var3.getRoom()) {
               var1++;
            } else {
               var1 -= 100000.0F;
            }

            if (var2.getZ() > var6.getZ()) {
               var1 -= 1000.0F;
            }

            if (var7 instanceof IsoPlayer) {
               var1 -= 100000.0F;
            } else if (var7 instanceof IsoThumpable && var7.getTargetAlpha() < 0.99F && (var7.getTargetAlpha() < 0.5F || var7.getContainer() == null)) {
               var1 -= 100000.0F;
            }

            if (var7 instanceof IsoCurtain) {
               var1 += 3.0F;
            } else if (var7 instanceof IsoLightSwitch) {
               var1 += 20.0F;
            } else if (var8.Properties.Is(IsoFlagType.bed)) {
               var1 += 2.0F;
            } else if (var7.container != null) {
               var1 += 10.0F;
            } else if (var7 instanceof IsoWaveSignal) {
               var1 += 20.0F;
            } else if (var10 != null && var10.getLightSource() != null) {
               var1 += 3.0F;
            } else if (var8.Properties.Is(IsoFlagType.waterPiped)) {
               var1 += 3.0F;
            } else if (var8.Properties.Is(IsoFlagType.solidfloor)) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofB) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofM) {
               var1 -= 100.0F;
            } else if (var8.getType() == IsoObjectType.WestRoofT) {
               var1 -= 100.0F;
            } else if (var8.Properties.Is(IsoFlagType.cutW) || var8.Properties.Is(IsoFlagType.cutN)) {
               var1 -= 2.0F;
            }
         }
      } else {
         var1 += 6.0F;
         if (var9 != null && var9.isAdjacentToSquare(var3) || var10 != null && var10.isAdjacentToSquare(var3)) {
            var1++;
         }

         if (var2.getZ() > var6.getZ()) {
            var1 -= 1000.0F;
         }
      }

      float var11 = IsoUtils.DistanceManhatten(var6.getX() + 0.5F, var6.getY() + 0.5F, var2.getX(), var2.getY());
      var1 -= var11 / 2.0F;
      return (int)var1;
   }

   public int getScore() {
      return this.score;
   }
}
