package zombie.iso.objects;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import zombie.characters.IsoPlayer;
import zombie.iso.IsoUtils;
import zombie.iso.objects.IsoFireManager.FireSounds.1;
import zombie.iso.objects.IsoFireManager.FireSounds.Slot;
import zombie.network.GameServer;
import zombie.util.list.PZArrayUtil;

final class IsoFireManager$FireSounds {
   final ArrayList<IsoFire> fires = new ArrayList<>();
   final Slot[] slots;
   final Comparator<IsoFire> comp = new 1(this);

   IsoFireManager$FireSounds(int var1) {
      this.slots = (Slot[])PZArrayUtil.newInstance(Slot.class, var1, Slot::new);
   }

   void addFire(IsoFire var1) {
      if (!this.fires.contains(var1)) {
         this.fires.add(var1);
      }
   }

   void removeFire(IsoFire var1) {
      this.fires.remove(var1);
   }

   void update() {
      if (!GameServer.bServer) {
         for (int var1 = 0; var1 < this.slots.length; var1++) {
            this.slots[var1].playing = false;
         }

         if (this.fires.isEmpty()) {
            this.stopNotPlaying();
         } else {
            Collections.sort(this.fires, this.comp);
            int var5 = Math.min(this.fires.size(), this.slots.length);

            for (int var2 = 0; var2 < var5; var2++) {
               IsoFire var3 = this.fires.get(var2);
               if (this.shouldPlay(var3)) {
                  int var4 = this.getExistingSlot(var3);
                  if (var4 != -1) {
                     this.slots[var4].playSound(var3);
                  }
               }
            }

            for (int var6 = 0; var6 < var5; var6++) {
               IsoFire var7 = this.fires.get(var6);
               if (this.shouldPlay(var7)) {
                  int var8 = this.getExistingSlot(var7);
                  if (var8 == -1) {
                     var8 = this.getFreeSlot();
                     this.slots[var8].playSound(var7);
                  }
               }
            }

            this.stopNotPlaying();
            this.fires.clear();
         }
      }
   }

   float getClosestListener(float var1, float var2, float var3) {
      float var4 = Float.MAX_VALUE;

      for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
         IsoPlayer var6 = IsoPlayer.players[var5];
         if (var6 != null && var6.getCurrentSquare() != null) {
            float var7 = var6.getX();
            float var8 = var6.getY();
            float var9 = var6.getZ();
            float var10 = IsoUtils.DistanceToSquared(var7, var8, var9 * 3.0F, var1, var2, var3 * 3.0F);
            if (var6.Traits.HardOfHearing.isSet()) {
               var10 *= 4.5F;
            }

            if (var10 < var4) {
               var4 = var10;
            }
         }
      }

      return var4;
   }

   boolean shouldPlay(IsoFire var1) {
      return var1 != null && var1.getObjectIndex() != -1 && var1.LifeStage < 4;
   }

   int getExistingSlot(IsoFire var1) {
      for (int var2 = 0; var2 < this.slots.length; var2++) {
         if (this.slots[var2].fire == var1) {
            return var2;
         }
      }

      return -1;
   }

   int getFreeSlot() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
         if (!this.slots[var1].playing) {
            return var1;
         }
      }

      return -1;
   }

   void stopNotPlaying() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
         Slot var2 = this.slots[var1];
         if (!var2.playing) {
            var2.stopPlaying();
            var2.fire = null;
         }
      }
   }

   void Reset() {
      for (int var1 = 0; var1 < this.slots.length; var1++) {
         this.slots[var1].stopPlaying();
         this.slots[var1].fire = null;
         this.slots[var1].playing = false;
      }
   }
}
