package zombie.characters;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashSet;
import zombie.characters.ZombieVocalsManager.1;
import zombie.characters.ZombieVocalsManager.ObjectWithDistance;
import zombie.characters.ZombieVocalsManager.Slot;
import zombie.core.Core;
import zombie.core.math.PZMath;
import zombie.iso.IsoUtils;
import zombie.network.GameServer;
import zombie.popman.ObjectPool;
import zombie.util.list.PZArrayUtil;

public final class ZombieVocalsManager {
   public static final ZombieVocalsManager instance = new ZombieVocalsManager();
   private final HashSet<IsoZombie> m_added = new HashSet<>();
   private final ObjectPool<ObjectWithDistance> m_objectPool = new ObjectPool(ObjectWithDistance::new);
   private final ArrayList<ObjectWithDistance> m_objects = new ArrayList<>();
   private final Slot[] m_slots;
   private long m_updateMS = 0L;
   private final Comparator<ObjectWithDistance> comp = new 1(this);

   public ZombieVocalsManager() {
      byte var1 = 20;
      this.m_slots = (Slot[])PZArrayUtil.newInstance(Slot.class, var1, Slot::new);
   }

   public void addCharacter(IsoZombie var1) {
      if (!this.m_added.contains(var1)) {
         this.m_added.add(var1);
         ObjectWithDistance var2 = (ObjectWithDistance)this.m_objectPool.alloc();
         var2.character = var1;
         this.m_objects.add(var2);
      }
   }

   public void update() {
      if (!GameServer.bServer) {
         long var1 = System.currentTimeMillis();
         if (var1 - this.m_updateMS >= 500L) {
            this.m_updateMS = var1;

            for (int var3 = 0; var3 < this.m_slots.length; var3++) {
               this.m_slots[var3].playing = false;
            }

            if (this.m_objects.isEmpty()) {
               this.stopNotPlaying();
            } else {
               for (int var7 = 0; var7 < this.m_objects.size(); var7++) {
                  ObjectWithDistance var4 = this.m_objects.get(var7);
                  IsoZombie var5 = var4.character;
                  var4.distSq = this.getClosestListener(var5.x, var5.y, var5.z);
               }

               this.m_objects.sort(this.comp);
               int var8 = PZMath.min(this.m_slots.length, this.m_objects.size());

               for (int var9 = 0; var9 < var8; var9++) {
                  IsoZombie var11 = this.m_objects.get(var9).character;
                  if (this.shouldPlay(var11)) {
                     int var6 = this.getExistingSlot(var11);
                     if (var6 != -1) {
                        this.m_slots[var6].playSound(var11);
                     }
                  }
               }

               for (int var10 = 0; var10 < var8; var10++) {
                  IsoZombie var12 = this.m_objects.get(var10).character;
                  if (this.shouldPlay(var12)) {
                     int var13 = this.getExistingSlot(var12);
                     if (var13 == -1) {
                        var13 = this.getFreeSlot();
                        this.m_slots[var13].playSound(var12);
                     }
                  }
               }

               this.stopNotPlaying();
               this.postUpdate();
               this.m_added.clear();
               this.m_objectPool.release(this.m_objects);
               this.m_objects.clear();
            }
         }
      }
   }

   boolean shouldPlay(IsoZombie var1) {
      return var1.getCurrentSquare() != null;
   }

   int getExistingSlot(IsoZombie var1) {
      for (int var2 = 0; var2 < this.m_slots.length; var2++) {
         if (this.m_slots[var2].character == var1) {
            return var2;
         }
      }

      return -1;
   }

   int getFreeSlot() {
      for (int var1 = 0; var1 < this.m_slots.length; var1++) {
         if (!this.m_slots[var1].playing) {
            return var1;
         }
      }

      return -1;
   }

   void stopNotPlaying() {
      for (int var1 = 0; var1 < this.m_slots.length; var1++) {
         Slot var2 = this.m_slots[var1];
         if (!var2.playing) {
            var2.stopPlaying();
            var2.character = null;
         }
      }
   }

   public void postUpdate() {
   }

   private float getClosestListener(float var1, float var2, float var3) {
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

   public void render() {
      if (Core.bDebug) {
      }
   }

   public static void Reset() {
      for (int var0 = 0; var0 < instance.m_slots.length; var0++) {
         instance.m_slots[var0].stopPlaying();
         instance.m_slots[var0].character = null;
         instance.m_slots[var0].playing = false;
      }
   }
}
