package zombie.audio;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import zombie.audio.ObjectAmbientEmitters.1;
import zombie.audio.ObjectAmbientEmitters.DoorLogic;
import zombie.audio.ObjectAmbientEmitters.ObjectWithDistance;
import zombie.audio.ObjectAmbientEmitters.PerObjectLogic;
import zombie.audio.ObjectAmbientEmitters.PowerPolicy;
import zombie.audio.ObjectAmbientEmitters.Slot;
import zombie.audio.ObjectAmbientEmitters.WindowLogic;
import zombie.characters.IsoPlayer;
import zombie.core.math.PZMath;
import zombie.debug.DebugOptions;
import zombie.debug.LineDrawer;
import zombie.iso.IsoCamera;
import zombie.iso.IsoChunk;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoObject;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;
import zombie.network.GameServer;
import zombie.popman.ObjectPool;
import zombie.util.list.PZArrayUtil;

public final class ObjectAmbientEmitters {
   private final HashMap<String, PowerPolicy> powerPolicyMap = new HashMap<>();
   private static ObjectAmbientEmitters instance = null;
   static final Vector2 tempVector2 = new Vector2();
   private final HashMap<IsoObject, ObjectWithDistance> m_added = new HashMap<>();
   private final ObjectPool<ObjectWithDistance> m_objectPool = new ObjectPool(ObjectWithDistance::new);
   private final ArrayList<ObjectWithDistance> m_objects = new ArrayList<>();
   private final Slot[] m_slots;
   private final Comparator<ObjectWithDistance> comp = new 1(this);

   public static ObjectAmbientEmitters getInstance() {
      if (instance == null) {
         instance = new ObjectAmbientEmitters();
      }

      return instance;
   }

   private ObjectAmbientEmitters() {
      byte var1 = 16;
      this.m_slots = (Slot[])PZArrayUtil.newInstance(Slot.class, var1, Slot::new);
      this.powerPolicyMap.put("FactoryMachineAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("HotdogMachineAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("PayPhoneAmbiance", PowerPolicy.ExteriorOK);
      this.powerPolicyMap.put("StreetLightAmbiance", PowerPolicy.ExteriorOK);
      this.powerPolicyMap.put("NeonLightAmbiance", PowerPolicy.ExteriorOK);
      this.powerPolicyMap.put("NeonSignAmbiance", PowerPolicy.ExteriorOK);
      this.powerPolicyMap.put("JukeboxAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("ControlStationAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("ClockAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("GasPumpAmbiance", PowerPolicy.ExteriorOK);
      this.powerPolicyMap.put("LightBulbAmbiance", PowerPolicy.InteriorHydro);
      this.powerPolicyMap.put("ArcadeMachineAmbiance", PowerPolicy.InteriorHydro);
   }

   private void addObject(IsoObject var1, PerObjectLogic var2) {
      if (!GameServer.bServer) {
         if (!this.m_added.containsKey(var1)) {
            boolean var3 = false;

            for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
               IsoPlayer var5 = IsoPlayer.players[var4];
               if (var5 != null && var1.getObjectIndex() != -1) {
                  byte var6 = 15;
                  if (var2 instanceof DoorLogic || var2 instanceof WindowLogic) {
                     var6 = 10;
                  }

                  if ((var1.square.z == PZMath.fastfloor(var5.getZ()) || !(var2 instanceof DoorLogic) && !(var2 instanceof WindowLogic))
                     && !(var5.DistToSquared(var1.square.x + 0.5F, var1.square.y + 0.5F) > var6 * var6)) {
                     var3 = true;
                     break;
                  }
               }
            }

            if (var3) {
               ObjectWithDistance var7 = (ObjectWithDistance)this.m_objectPool.alloc();
               var7.object = var1;
               var7.logic = var2;
               this.m_objects.add(var7);
               this.m_added.put(var1, var7);
            }
         }
      }
   }

   void removeObject(IsoObject var1) {
      if (!GameServer.bServer) {
         ObjectWithDistance var2 = this.m_added.remove(var1);
         if (var2 != null) {
            this.m_objects.remove(var2);
            this.m_objectPool.release(var2);
         }
      }
   }

   public void update() {
      if (!GameServer.bServer) {
         this.addObjectsFromChunks();

         for (int var1 = 0; var1 < this.m_slots.length; var1++) {
            this.m_slots[var1].playing = false;
         }

         if (this.m_objects.isEmpty()) {
            this.stopNotPlaying();
         } else {
            for (int var6 = 0; var6 < this.m_objects.size(); var6++) {
               ObjectWithDistance var2 = this.m_objects.get(var6);
               IsoObject var3 = var2.object;
               PerObjectLogic var4 = this.m_objects.get(var6).logic;
               if (!this.shouldPlay(var3, var4)) {
                  this.m_added.remove(var3);
                  this.m_objects.remove(var6--);
                  this.m_objectPool.release(var2);
               } else {
                  var3.getFacingPosition(tempVector2);
                  var2.distSq = this.getClosestListener(tempVector2.x, tempVector2.y, var3.square.z);
               }
            }

            this.m_objects.sort(this.comp);
            int var7 = Math.min(this.m_objects.size(), this.m_slots.length);

            for (int var8 = 0; var8 < var7; var8++) {
               IsoObject var10 = this.m_objects.get(var8).object;
               PerObjectLogic var12 = this.m_objects.get(var8).logic;
               if (this.shouldPlay(var10, var12)) {
                  int var5 = this.getExistingSlot(var10);
                  if (var5 != -1) {
                     this.m_slots[var5].playSound(var10, var12);
                  }
               }
            }

            for (int var9 = 0; var9 < var7; var9++) {
               IsoObject var11 = this.m_objects.get(var9).object;
               PerObjectLogic var13 = this.m_objects.get(var9).logic;
               if (this.shouldPlay(var11, var13)) {
                  int var14 = this.getExistingSlot(var11);
                  if (var14 == -1) {
                     var14 = this.getFreeSlot();
                     if (this.m_slots[var14].object != null) {
                        this.m_slots[var14].stopPlaying();
                        this.m_slots[var14].object = null;
                     }

                     this.m_slots[var14].playSound(var11, var13);
                  }
               }
            }

            this.stopNotPlaying();
            this.m_added.clear();
            this.m_objectPool.release(this.m_objects);
            this.m_objects.clear();
         }
      }
   }

   void addObjectsFromChunks() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
         IsoChunkMap var2 = IsoWorld.instance.CurrentCell.ChunkMap[var1];
         if (!var2.ignore) {
            int var3 = IsoChunkMap.ChunkGridWidth / 2;
            int var4 = IsoChunkMap.ChunkGridWidth / 2;

            for (int var5 = -1; var5 <= 1; var5++) {
               for (int var6 = -1; var6 <= 1; var6++) {
                  IsoChunk var7 = var2.getChunk(var3 + var6, var4 + var5);
                  if (var7 != null) {
                     for (IsoObject var10 : var7.m_objectEmitterData.m_objects.keySet()) {
                        this.addObject(var10, (PerObjectLogic)var7.m_objectEmitterData.m_objects.get(var10));
                     }
                  }
               }
            }
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

   boolean shouldPlay(IsoObject var1, PerObjectLogic var2) {
      if (var1 == null) {
         return false;
      } else {
         return var1.getObjectIndex() == -1 ? false : var2.shouldPlaySound();
      }
   }

   int getExistingSlot(IsoObject var1) {
      for (int var2 = 0; var2 < this.m_slots.length; var2++) {
         if (this.m_slots[var2].object == var1) {
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
            var2.object = null;
         }
      }
   }

   public void render() {
      if (DebugOptions.instance.ObjectAmbientEmitterRender.getValue()) {
         IsoChunkMap var1 = IsoWorld.instance.CurrentCell.ChunkMap[IsoCamera.frameState.playerIndex];
         if (!var1.ignore) {
            int var2 = IsoChunkMap.ChunkGridWidth / 2;
            int var3 = IsoChunkMap.ChunkGridWidth / 2;

            for (int var4 = -1; var4 <= 1; var4++) {
               for (int var5 = -1; var5 <= 1; var5++) {
                  IsoChunk var6 = var1.getChunk(var2 + var5, var3 + var4);
                  if (var6 != null) {
                     for (IsoObject var9 : var6.m_objectEmitterData.m_objects.keySet()) {
                        if (var9.square.z == (int)IsoCamera.frameState.CamCharacterZ) {
                           var9.getFacingPosition(tempVector2);
                           float var10 = tempVector2.x;
                           float var11 = tempVector2.y;
                           float var12 = var9.square.z;
                           LineDrawer.addLine(var10 - 0.45F, var11 - 0.45F, var12, var10 + 0.45F, var11 + 0.45F, var12, 0.5F, 0.5F, 0.5F, null, false);
                        }
                     }
                  }
               }
            }
         }

         for (int var13 = 0; var13 < this.m_slots.length; var13++) {
            Slot var14 = this.m_slots[var13];
            if (var14.playing) {
               IsoObject var15 = var14.object;
               var15.getFacingPosition(tempVector2);
               float var16 = tempVector2.x;
               float var17 = tempVector2.y;
               float var18 = var15.square.z;
               LineDrawer.addLine(var16 - 0.45F, var17 - 0.45F, var18, var16 + 0.45F, var17 + 0.45F, var18, 0.0F, 0.0F, 1.0F, null, false);
            }
         }
      }
   }

   public static void Reset() {
      if (instance != null) {
         for (int var0 = 0; var0 < instance.m_slots.length; var0++) {
            instance.m_slots[var0].stopPlaying();
            instance.m_slots[var0].object = null;
            instance.m_slots[var0].playing = false;
         }
      }
   }
}
