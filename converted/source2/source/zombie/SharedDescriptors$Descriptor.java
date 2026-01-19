package zombie;

import java.io.IOException;
import java.nio.ByteBuffer;
import zombie.core.skinnedmodel.visual.HumanVisual;
import zombie.core.skinnedmodel.visual.IHumanVisual;
import zombie.core.skinnedmodel.visual.ItemVisual;
import zombie.core.skinnedmodel.visual.ItemVisuals;

public final class SharedDescriptors$Descriptor implements IHumanVisual {
   public int ID = 0;
   public int persistentOutfitID = 0;
   public String outfitName;
   public final HumanVisual humanVisual = new HumanVisual(this);
   public final ItemVisuals itemVisuals = new ItemVisuals();
   public boolean bFemale = false;
   public boolean bZombie = false;

   public int getID() {
      return this.ID;
   }

   public int getPersistentOutfitID() {
      return this.persistentOutfitID;
   }

   public HumanVisual getHumanVisual() {
      return this.humanVisual;
   }

   public void getItemVisuals(ItemVisuals var1) {
      var1.clear();
      var1.addAll(this.itemVisuals);
   }

   public boolean isFemale() {
      return this.bFemale;
   }

   public boolean isZombie() {
      return this.bZombie;
   }

   public boolean isSkeleton() {
      return false;
   }

   public void save(ByteBuffer var1) throws IOException {
      byte var2 = 0;
      if (this.bFemale) {
         var2 = (byte)(var2 | 1);
      }

      if (this.bZombie) {
         var2 = (byte)(var2 | 2);
      }

      var1.put(var2);
      var1.putInt(this.ID);
      var1.putInt(this.persistentOutfitID);
      GameWindow.WriteStringUTF(var1, this.outfitName);
      this.humanVisual.save(var1);
      this.itemVisuals.save(var1);
   }

   public void load(ByteBuffer var1, int var2) throws IOException {
      this.humanVisual.clear();
      this.itemVisuals.clear();
      byte var3 = var1.get();
      this.bFemale = (var3 & 1) != 0;
      this.bZombie = (var3 & 2) != 0;
      this.ID = var1.getInt();
      this.persistentOutfitID = var1.getInt();
      this.outfitName = GameWindow.ReadStringUTF(var1);
      this.humanVisual.load(var1, var2);
      short var4 = var1.getShort();

      for (int var5 = 0; var5 < var4; var5++) {
         ItemVisual var6 = new ItemVisual();
         var6.load(var1, var2);
         this.itemVisuals.add(var6);
      }
   }
}
