package zombie.popman;

import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Map.Entry;
import java.util.concurrent.ConcurrentHashMap;
import zombie.GameTime;
import zombie.WorldSoundManager.WorldSound;
import zombie.characters.IsoPlayer;
import zombie.core.Color;
import zombie.core.Colors;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.RakVoice;
import zombie.core.raknet.UdpConnection;
import zombie.debug.DebugOptions;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoMetaGrid;
import zombie.iso.IsoWorld;
import zombie.iso.Vector2;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.popman.MPDebugInfo.MPCell;
import zombie.popman.MPDebugInfo.MPRepopEvent;
import zombie.popman.MPDebugInfo.MPSoundDebugInfo;

public final class MPDebugInfo {
   public static final MPDebugInfo instance = new MPDebugInfo();
   private static final ConcurrentHashMap<Long, MPSoundDebugInfo> debugSounds = new ConcurrentHashMap<>();
   private final ArrayList<MPCell> loadedCells = new ArrayList<>();
   private final ObjectPool<MPCell> cellPool = new ObjectPool(MPCell::new);
   private final LoadedAreas loadedAreas = new LoadedAreas(false);
   private ArrayList<MPRepopEvent> repopEvents = new ArrayList<>();
   private final ObjectPool<MPRepopEvent> repopEventPool = new ObjectPool(MPRepopEvent::new);
   private short repopEpoch = 0;
   private long requestTime = 0L;
   private boolean requestFlag = false;
   private boolean requestPacketReceived = false;
   private final ByteBuffer byteBuffer = ByteBuffer.allocateDirect(1024);
   private float RESPAWN_EVERY_HOURS = 1.0F;
   private float REPOP_DISPLAY_HOURS = 0.5F;

   private static native boolean n_hasData(boolean var0);

   private static native void n_requestData();

   private static native int n_getLoadedCellsCount();

   private static native int n_getLoadedCellsData(int var0, ByteBuffer var1);

   private static native int n_getLoadedAreasCount();

   private static native int n_getLoadedAreasData(int var0, ByteBuffer var1);

   private static native int n_getRepopEventCount();

   private static native int n_getRepopEventData(int var0, ByteBuffer var1);

   private void requestServerInfo() {
      if (GameClient.bClient) {
         long var1 = System.currentTimeMillis();
         if (this.requestTime + 1000L <= var1) {
            this.requestTime = var1;
            ByteBufferWriter var3 = GameClient.connection.startPacket();
            PacketType.KeepAlive.doPacket(var3);
            var3.bb.put((byte)1);
            var3.bb.putShort(this.repopEpoch);
            PacketType.KeepAlive.send(GameClient.connection);
         }
      }
   }

   public void clientPacket(ByteBuffer var1) {
      if (GameClient.bClient) {
         byte var2 = var1.get();
         if (var2 == 1) {
            this.cellPool.release(this.loadedCells);
            this.loadedCells.clear();
            this.RESPAWN_EVERY_HOURS = var1.getFloat();
            short var3 = var1.getShort();

            for (int var4 = 0; var4 < var3; var4++) {
               MPCell var5 = (MPCell)this.cellPool.alloc();
               var5.cx = var1.getShort();
               var5.cy = var1.getShort();
               var5.currentPopulation = var1.getShort();
               var5.desiredPopulation = var1.getShort();
               var5.lastRepopTime = var1.getFloat();
               this.loadedCells.add(var5);
            }

            this.loadedAreas.clear();
            short var11 = var1.getShort();

            for (int var13 = 0; var13 < var11; var13++) {
               short var6 = var1.getShort();
               short var7 = var1.getShort();
               short var8 = var1.getShort();
               short var9 = var1.getShort();
               this.loadedAreas.add(var6, var7, var8, var9);
            }
         }

         if (var2 == 2) {
            this.repopEventPool.release(this.repopEvents);
            this.repopEvents.clear();
            this.repopEpoch = var1.getShort();
            short var10 = var1.getShort();

            for (int var12 = 0; var12 < var10; var12++) {
               MPRepopEvent var14 = (MPRepopEvent)this.repopEventPool.alloc();
               var14.wx = var1.getShort();
               var14.wy = var1.getShort();
               var14.worldAge = var1.getFloat();
               this.repopEvents.add(var14);
            }
         }
      }
   }

   public void serverPacket(ByteBuffer var1, UdpConnection var2) {
      if (GameServer.bServer) {
         if (var2.accessLevel == 32) {
            byte var3 = var1.get();
            if (var3 == 1) {
               this.requestTime = System.currentTimeMillis();
               this.requestPacketReceived = true;
               short var4 = var1.getShort();
               ByteBufferWriter var5 = var2.startPacket();
               PacketType.KeepAlive.doPacket(var5);
               var5.bb.put((byte)1);
               var5.bb.putFloat(this.RESPAWN_EVERY_HOURS);
               var5.bb.putShort((short)this.loadedCells.size());

               for (int var6 = 0; var6 < this.loadedCells.size(); var6++) {
                  MPCell var7 = this.loadedCells.get(var6);
                  var5.bb.putShort(var7.cx);
                  var5.bb.putShort(var7.cy);
                  var5.bb.putShort(var7.currentPopulation);
                  var5.bb.putShort(var7.desiredPopulation);
                  var5.bb.putFloat(var7.lastRepopTime);
               }

               var5.bb.putShort((short)this.loadedAreas.count);

               for (int var16 = 0; var16 < this.loadedAreas.count; var16++) {
                  int var18 = var16 * 4;
                  var5.bb.putShort((short)this.loadedAreas.areas[var18++]);
                  var5.bb.putShort((short)this.loadedAreas.areas[var18++]);
                  var5.bb.putShort((short)this.loadedAreas.areas[var18++]);
                  var5.bb.putShort((short)this.loadedAreas.areas[var18++]);
               }

               if (var4 != this.repopEpoch) {
                  var3 = 2;
               }

               PacketType.KeepAlive.send(var2);
            }

            if (var3 != 2) {
               if (var3 == 3) {
                  short var11 = var1.getShort();
                  short var15 = var1.getShort();
                  ZombiePopulationManager.instance.dbgSpawnTimeToZero(var11, var15);
               } else if (var3 == 4) {
                  short var10 = var1.getShort();
                  short var14 = var1.getShort();
                  ZombiePopulationManager.instance.dbgClearZombies(var10, var14);
               } else if (var3 == 5) {
                  short var9 = var1.getShort();
                  short var13 = var1.getShort();
                  ZombiePopulationManager.instance.dbgSpawnNow(var9, var13);
               }
            } else {
               ByteBufferWriter var8 = var2.startPacket();
               PacketType.KeepAlive.doPacket(var8);
               var8.bb.put((byte)2);
               var8.bb.putShort(this.repopEpoch);
               var8.bb.putShort((short)this.repopEvents.size());

               for (int var12 = 0; var12 < this.repopEvents.size(); var12++) {
                  MPRepopEvent var17 = this.repopEvents.get(var12);
                  var8.bb.putShort((short)var17.wx);
                  var8.bb.putShort((short)var17.wy);
                  var8.bb.putFloat(var17.worldAge);
               }

               PacketType.KeepAlive.send(var2);
            }
         }
      }
   }

   public void request() {
      if (GameServer.bServer) {
         this.requestTime = System.currentTimeMillis();
      }
   }

   private void addRepopEvent(int var1, int var2, float var3) {
      float var4 = (float)GameTime.getInstance().getWorldAgeHours();

      while (!this.repopEvents.isEmpty() && this.repopEvents.get(0).worldAge + this.REPOP_DISPLAY_HOURS < var4) {
         this.repopEventPool.release(this.repopEvents.remove(0));
      }

      this.repopEvents.add(((MPRepopEvent)this.repopEventPool.alloc()).init(var1, var2, var3));
      this.repopEpoch++;
   }

   public void serverUpdate() {
      if (GameServer.bServer) {
         long var1 = System.currentTimeMillis();
         if (this.requestTime + 10000L < var1) {
            this.requestFlag = false;
            this.requestPacketReceived = false;
         } else {
            if (this.requestFlag) {
               if (n_hasData(false)) {
                  this.requestFlag = false;
                  this.cellPool.release(this.loadedCells);
                  this.loadedCells.clear();
                  this.loadedAreas.clear();
                  int var3 = n_getLoadedCellsCount();
                  int var4 = 0;

                  while (var4 < var3) {
                     this.byteBuffer.clear();
                     int var5 = n_getLoadedCellsData(var4, this.byteBuffer);
                     var4 += var5;

                     for (int var6 = 0; var6 < var5; var6++) {
                        MPCell var7 = (MPCell)this.cellPool.alloc();
                        var7.cx = this.byteBuffer.getShort();
                        var7.cy = this.byteBuffer.getShort();
                        var7.currentPopulation = this.byteBuffer.getShort();
                        var7.desiredPopulation = this.byteBuffer.getShort();
                        var7.lastRepopTime = this.byteBuffer.getFloat();
                        this.loadedCells.add(var7);
                     }
                  }

                  var3 = n_getLoadedAreasCount();
                  var4 = 0;

                  while (var4 < var3) {
                     this.byteBuffer.clear();
                     int var16 = n_getLoadedAreasData(var4, this.byteBuffer);
                     var4 += var16;

                     for (int var18 = 0; var18 < var16; var18++) {
                        boolean var20 = this.byteBuffer.get() == 0;
                        short var8 = this.byteBuffer.getShort();
                        short var9 = this.byteBuffer.getShort();
                        short var10 = this.byteBuffer.getShort();
                        short var11 = this.byteBuffer.getShort();
                        this.loadedAreas.add(var8, var9, var10, var11);
                     }
                  }
               }
            } else if (this.requestPacketReceived) {
               n_requestData();
               this.requestFlag = true;
               this.requestPacketReceived = false;
            }

            if (n_hasData(true)) {
               int var13 = n_getRepopEventCount();
               int var15 = 0;

               while (var15 < var13) {
                  this.byteBuffer.clear();
                  int var17 = n_getRepopEventData(var15, this.byteBuffer);
                  var15 += var17;

                  for (int var19 = 0; var19 < var17; var19++) {
                     short var21 = this.byteBuffer.getShort();
                     short var22 = this.byteBuffer.getShort();
                     float var23 = this.byteBuffer.getFloat();
                     this.addRepopEvent(var21, var22, var23);
                  }
               }
            }
         }
      }
   }

   boolean isRespawnEnabled() {
      return IsoWorld.getZombiesDisabled() ? false : !(this.RESPAWN_EVERY_HOURS <= 0.0F);
   }

   public void render(ZombiePopulationRenderer var1, float var2) {
      this.requestServerInfo();
      float var3 = (float)GameTime.getInstance().getWorldAgeHours();
      IsoMetaGrid var4 = IsoWorld.instance.MetaGrid;
      var1.outlineRect(
         var4.minX * 300 * 1.0F,
         var4.minY * 300 * 1.0F,
         (var4.maxX - var4.minX + 1) * 300 * 1.0F,
         (var4.maxY - var4.minY + 1) * 300 * 1.0F,
         1.0F,
         1.0F,
         1.0F,
         0.25F
      );

      for (int var5 = 0; var5 < this.loadedCells.size(); var5++) {
         MPCell var6 = this.loadedCells.get(var5);
         var1.outlineRect(var6.cx * 300, var6.cy * 300, 300.0F, 300.0F, 1.0F, 1.0F, 1.0F, 0.25F);
         if (this.isRespawnEnabled()) {
            float var7 = Math.min(var3 - var6.lastRepopTime, this.RESPAWN_EVERY_HOURS) / this.RESPAWN_EVERY_HOURS;
            if (var6.lastRepopTime > var3) {
               var7 = 0.0F;
            }

            var1.outlineRect(var6.cx * 300 + 1, var6.cy * 300 + 1, 298.0F, 298.0F, 0.0F, 1.0F, 0.0F, var7 * var7);
         }
      }

      for (int var12 = 0; var12 < this.loadedAreas.count; var12++) {
         int var17 = var12 * 4;
         int var27 = this.loadedAreas.areas[var17++];
         int var8 = this.loadedAreas.areas[var17++];
         int var9 = this.loadedAreas.areas[var17++];
         int var10 = this.loadedAreas.areas[var17++];
         var1.outlineRect(var27 * 10, var8 * 10, var9 * 10, var10 * 10, 0.7F, 0.7F, 0.7F, 1.0F);
      }

      for (int var13 = 0; var13 < this.repopEvents.size(); var13++) {
         MPRepopEvent var22 = this.repopEvents.get(var13);
         if (!(var22.worldAge + this.REPOP_DISPLAY_HOURS < var3)) {
            float var28 = 1.0F - (var3 - var22.worldAge) / this.REPOP_DISPLAY_HOURS;
            var28 = Math.max(var28, 0.1F);
            var1.outlineRect(var22.wx * 10, var22.wy * 10, 50.0F, 50.0F, 0.0F, 0.0F, 1.0F, var28);
         }
      }

      if (GameClient.bClient && DebugOptions.instance.MultiplayerShowPosition.getValue()) {
         float var14 = (IsoChunkMap.ChunkGridWidth / 2 + 2) * 10;

         for (Entry var30 : GameClient.positions.entrySet()) {
            IsoPlayer var34 = (IsoPlayer)GameClient.IDToPlayerMap.get(var30.getKey());
            Color var36 = Color.white;
            if (var34 != null) {
               var36 = var34.getSpeakColour();
            }

            Vector2 var37 = (Vector2)var30.getValue();
            var1.renderZombie(var37.x, var37.y, var36.r, var36.g, var36.b);
            var1.renderCircle(var37.x, var37.y, var14, var36.r, var36.g, var36.b, var36.a);
            var1.renderString(var37.x, var37.y, var34 == null ? String.valueOf(var30.getKey()) : var34.getUsername(), var36.r, var36.g, var36.b, var36.a);
         }

         if (IsoPlayer.getInstance() != null) {
            IsoPlayer var24 = IsoPlayer.getInstance();
            Color var31 = var24.getSpeakColour();
            var1.renderZombie(var24.x, var24.y, var31.r, var31.g, var31.b);
            var1.renderCircle(var24.x, var24.y, var14, var31.r, var31.g, var31.b, var31.a);
            var1.renderString(var24.x, var24.y, var24.getUsername(), var31.r, var31.g, var31.b, var31.a);
            var31 = Colors.LightBlue;
            var1.renderCircle(var24.x, var24.y, RakVoice.GetMinDistance(), var31.r, var31.g, var31.b, var31.a);
            var1.renderCircle(var24.x, var24.y, RakVoice.GetMaxDistance(), var31.r, var31.g, var31.b, var31.a);
         }
      }

      if (var2 > 0.25F) {
         for (int var15 = 0; var15 < this.loadedCells.size(); var15++) {
            MPCell var25 = this.loadedCells.get(var15);
            var1.renderCellInfo(var25.cx, var25.cy, var25.currentPopulation, var25.desiredPopulation, var25.lastRepopTime + this.RESPAWN_EVERY_HOURS - var3);
         }
      }

      try {
         debugSounds.entrySet().removeIf(var0 -> System.currentTimeMillis() > var0.getKey() + 1000L);

         for (Entry var26 : debugSounds.entrySet()) {
            Color var33 = Colors.LightBlue;
            if (((MPSoundDebugInfo)var26.getValue()).sourceIsZombie) {
               var33 = Colors.GreenYellow;
            } else if (((MPSoundDebugInfo)var26.getValue()).bRepeating) {
               var33 = Colors.Coral;
            }

            float var35 = 1.0F - Math.max(0.0F, Math.min(1.0F, (float)(System.currentTimeMillis() - (Long)var26.getKey()) / 1000.0F));
            var1.renderCircle(
               ((MPSoundDebugInfo)var26.getValue()).x,
               ((MPSoundDebugInfo)var26.getValue()).y,
               ((MPSoundDebugInfo)var26.getValue()).radius,
               var33.r,
               var33.g,
               var33.b,
               var35
            );
         }
      } catch (Exception var11) {
      }
   }

   public static void AddDebugSound(WorldSound var0) {
      try {
         debugSounds.put(System.currentTimeMillis(), new MPSoundDebugInfo(var0));
      } catch (Exception var2) {
      }
   }
}
