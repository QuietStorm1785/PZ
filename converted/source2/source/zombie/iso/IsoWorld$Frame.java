package zombie.iso;

import java.util.ArrayList;
import java.util.Iterator;
import zombie.characters.IsoPlayer;
import zombie.characters.IsoSurvivor;
import zombie.characters.IsoZombie;

public class IsoWorld$Frame {
   public ArrayList<Integer> xPos;
   public ArrayList<Integer> yPos;
   public ArrayList<Integer> Type;

   public IsoWorld$Frame(IsoWorld var1) {
      this.this$0 = var1;
      this.xPos = new ArrayList<>();
      this.yPos = new ArrayList<>();
      this.Type = new ArrayList<>();
      Iterator var2 = IsoWorld.instance.CurrentCell.getObjectList().iterator();

      while (var2 != null && var2.hasNext()) {
         IsoMovingObject var3 = (IsoMovingObject)var2.next();
         byte var4 = 2;
         if (var3 instanceof IsoPlayer) {
            var4 = 0;
         } else if (var3 instanceof IsoSurvivor) {
            var4 = 1;
         } else {
            if (!(var3 instanceof IsoZombie) || ((IsoZombie)var3).Ghost) {
               continue;
            }

            var4 = 2;
         }

         this.xPos.add((int)var3.getX());
         this.yPos.add((int)var3.getY());
         this.Type.add(Integer.valueOf(var4));
      }
   }
}
