package zombie.util;

import zombie.SoundManager;
import zombie.Lua.LuaEventManager;
import zombie.characters.IsoPlayer;
import zombie.core.network.ByteBufferWriter;
import zombie.core.physics.WorldSimulation;
import zombie.debug.DebugLog;
import zombie.iso.IsoCell;
import zombie.iso.IsoChunk;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoWorld;
import zombie.iso.LightingJNI;
import zombie.iso.LosUtil;
import zombie.network.GameClient;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.popman.ZombiePopulationManager;
import zombie.ui.UIManager;
import zombie.util.AddCoopPlayer.1;
import zombie.util.AddCoopPlayer.Stage;

public final class AddCoopPlayer {
   private Stage stage = Stage.Init;
   private IsoPlayer player;

   public AddCoopPlayer(IsoPlayer var1) {
      this.player = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   public void update() {
      switch (1.$SwitchMap$zombie$util$AddCoopPlayer$Stage[this.stage.ordinal()]) {
         case 1:
            if (GameClient.bClient) {
               ByteBufferWriter var21 = GameClient.connection.startPacket();
               PacketType.AddCoopPlayer.doPacket(var21);
               var21.putByte((byte)1);
               var21.putByte((byte)this.player.PlayerIndex);
               var21.putUTF(this.player.username != null ? this.player.username : "");
               var21.putFloat(this.player.x);
               var21.putFloat(this.player.y);
               PacketType.AddCoopPlayer.send(GameClient.connection);
               this.stage = Stage.ReceiveClientConnect;
            } else {
               this.stage = Stage.StartMapLoading;
            }
         case 2:
         case 6:
         case 8:
         default:
            break;
         case 3:
            IsoCell var20 = IsoWorld.instance.CurrentCell;
            int var22 = this.player.PlayerIndex;
            IsoChunkMap var24 = var20.ChunkMap[var22];
            IsoChunkMap.bSettingChunk.lock();

            try {
               var24.Unload();
               var24.ignore = false;
               int var25 = (int)(this.player.x / 10.0F);
               int var5 = (int)(this.player.y / 10.0F);

               try {
                  if (LightingJNI.init) {
                     LightingJNI.teleport(var22, var25 - IsoChunkMap.ChunkGridWidth / 2, var5 - IsoChunkMap.ChunkGridWidth / 2);
                  }
               } catch (Exception var16) {
               }

               if (!GameServer.bServer && !GameClient.bClient) {
                  ZombiePopulationManager.instance.playerSpawnedAt((int)this.player.x, (int)this.player.y, (int)this.player.z);
               }

               var24.WorldX = var25;
               var24.WorldY = var5;
               if (!GameServer.bServer) {
                  WorldSimulation.instance.activateChunkMap(var22);
               }

               int var6 = var25 - IsoChunkMap.ChunkGridWidth / 2;
               int var7 = var5 - IsoChunkMap.ChunkGridWidth / 2;
               int var8 = var25 + IsoChunkMap.ChunkGridWidth / 2 + 1;
               int var9 = var5 + IsoChunkMap.ChunkGridWidth / 2 + 1;

               for (int var10 = var6; var10 < var8; var10++) {
                  for (int var11 = var7; var11 < var9; var11++) {
                     if (IsoWorld.instance.getMetaGrid().isValidChunk(var10, var11)) {
                        IsoChunk var12 = var24.LoadChunkForLater(var10, var11, var10 - var6, var11 - var7);
                        if (var12 != null && var12.bLoaded) {
                           var20.setCacheChunk(var12, var22);
                        }
                     }
                  }
               }

               var24.SwapChunkBuffers();
            } finally {
               IsoChunkMap.bSettingChunk.unlock();
            }

            this.stage = Stage.CheckMapLoading;
            break;
         case 4:
            IsoCell var19 = IsoWorld.instance.CurrentCell;
            IsoChunkMap var2 = var19.ChunkMap[this.player.PlayerIndex];
            var2.update();

            for (int var3 = 0; var3 < IsoChunkMap.ChunkGridWidth; var3++) {
               for (int var4 = 0; var4 < IsoChunkMap.ChunkGridWidth; var4++) {
                  if (IsoWorld.instance.getMetaGrid().isValidChunk(var2.getWorldXMin() + var4, var2.getWorldYMin() + var3) && var2.getChunk(var4, var3) == null
                     )
                   {
                     return;
                  }
               }
            }

            IsoGridSquare var23 = var19.getGridSquare((int)this.player.x, (int)this.player.y, (int)this.player.z);
            if (var23 != null && var23.getRoom() != null) {
               var23.getRoom().def.setExplored(true);
               var23.getRoom().building.setAllExplored(true);
            }

            this.stage = GameClient.bClient ? Stage.SendPlayerConnect : Stage.AddToWorld;
            break;
         case 5:
            ByteBufferWriter var18 = GameClient.connection.startPacket();
            PacketType.AddCoopPlayer.doPacket(var18);
            var18.putByte((byte)2);
            var18.putByte((byte)this.player.PlayerIndex);
            GameClient.instance.writePlayerConnectData(var18, this.player);
            PacketType.AddCoopPlayer.send(GameClient.connection);
            this.stage = Stage.ReceivePlayerConnect;
            break;
         case 7:
            IsoPlayer.players[this.player.PlayerIndex] = this.player;
            LosUtil.cachecleared[this.player.PlayerIndex] = true;
            this.player.updateLightInfo();
            IsoCell var1 = IsoWorld.instance.CurrentCell;
            this.player.setCurrent(var1.getGridSquare((int)this.player.x, (int)this.player.y, (int)this.player.z));
            this.player.updateUsername();
            this.player.setSceneCulled(false);
            if (var1.isSafeToAdd()) {
               var1.getObjectList().add(this.player);
            } else {
               var1.getAddList().add(this.player);
            }

            this.player.getInventory().addItemsToProcessItems();
            LuaEventManager.triggerEvent("OnCreatePlayer", this.player.PlayerIndex, this.player);
            if (this.player.isAsleep()) {
               UIManager.setFadeBeforeUI(this.player.PlayerIndex, true);
               UIManager.FadeOut(this.player.PlayerIndex, 2.0);
               UIManager.setFadeTime(this.player.PlayerIndex, 0.0);
            }

            this.stage = Stage.Finished;
            SoundManager.instance.stopMusic(IsoPlayer.DEATH_MUSIC_NAME);
      }
   }

   public boolean isFinished() {
      return this.stage == Stage.Finished;
   }

   public void accessGranted(int var1) {
      if (this.player.PlayerIndex == var1) {
         DebugLog.log("coop player=" + (var1 + 1) + "/4 access granted");
         this.stage = Stage.StartMapLoading;
      }
   }

   public void accessDenied(int var1, String var2) {
      if (this.player.PlayerIndex == var1) {
         DebugLog.log("coop player=" + (var1 + 1) + "/4 access denied: " + var2);
         IsoCell var3 = IsoWorld.instance.CurrentCell;
         int var4 = this.player.PlayerIndex;
         IsoChunkMap var5 = var3.ChunkMap[var4];
         var5.Unload();
         var5.ignore = true;
         this.stage = Stage.Finished;
         LuaEventManager.triggerEvent("OnCoopJoinFailed", var1);
      }
   }

   public void receivePlayerConnect(int var1) {
      if (this.player.PlayerIndex == var1) {
         this.stage = Stage.AddToWorld;
         this.update();
      }
   }

   public boolean isLoadingThisSquare(int var1, int var2) {
      int var3 = (int)(this.player.x / 10.0F);
      int var4 = (int)(this.player.y / 10.0F);
      int var5 = var3 - IsoChunkMap.ChunkGridWidth / 2;
      int var6 = var4 - IsoChunkMap.ChunkGridWidth / 2;
      int var7 = var5 + IsoChunkMap.ChunkGridWidth;
      int var8 = var6 + IsoChunkMap.ChunkGridWidth;
      var1 /= 10;
      var2 /= 10;
      return var1 >= var5 && var1 < var7 && var2 >= var6 && var2 < var8;
   }
}
