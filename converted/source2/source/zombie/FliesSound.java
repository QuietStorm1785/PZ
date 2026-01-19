package zombie;

import java.util.ArrayList;
import zombie.FliesSound.ChunkData;
import zombie.FliesSound.ChunkLevelData;
import zombie.FliesSound.FadeEmitter;
import zombie.FliesSound.PlayerData;
import zombie.characters.IsoGameCharacter;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.SpriteRenderer;
import zombie.debug.DebugLog;
import zombie.iso.IsoChunk;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoGridSquare;
import zombie.iso.IsoUtils;
import zombie.iso.IsoWorld;
import zombie.iso.areas.IsoBuilding;

public final class FliesSound {
   public static final FliesSound instance = new FliesSound();
   private static final IsoGridSquare[] tempSquares = new IsoGridSquare[100];
   private final PlayerData[] playerData = new PlayerData[4];
   private final ArrayList<FadeEmitter> fadeEmitters = new ArrayList<>();
   private float fliesVolume = -1.0F;

   public FliesSound() {
      for (int var1 = 0; var1 < this.playerData.length; var1++) {
         this.playerData[var1] = new PlayerData(this);
      }
   }

   public void Reset() {
      for (int var1 = 0; var1 < this.playerData.length; var1++) {
         this.playerData[var1].Reset();
      }
   }

   public void update() {
      if (SandboxOptions.instance.DecayingCorpseHealthImpact.getValue() != 1) {
         for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
            IsoPlayer var2 = IsoPlayer.players[var1];
            if (var2 != null && var2.getCurrentSquare() != null) {
               this.playerData[var1].update(var2);
            }
         }

         for (int var3 = 0; var3 < this.fadeEmitters.size(); var3++) {
            FadeEmitter var4 = this.fadeEmitters.get(var3);
            if (var4.update()) {
               this.fadeEmitters.remove(var3--);
            }
         }
      }
   }

   public void render() {
      IsoChunkMap var1 = IsoWorld.instance.CurrentCell.ChunkMap[0];

      for (int var2 = 0; var2 < IsoChunkMap.ChunkGridWidth; var2++) {
         for (int var3 = 0; var3 < IsoChunkMap.ChunkGridWidth; var3++) {
            IsoChunk var4 = var1.getChunk(var3, var2);
            if (var4 != null) {
               ChunkData var5 = var4.corpseData;
               if (var5 != null) {
                  int var6 = (int)IsoPlayer.players[0].z;
                  ChunkLevelData var7 = var5.levelData[var6];

                  for (int var8 = 0; var8 < var7.emitters.length; var8++) {
                     FadeEmitter var9 = var7.emitters[var8];
                     if (var9 != null && var9.emitter != null) {
                        this.paintSquare(var9.sq.x, var9.sq.y, var9.sq.z, 0.0F, 1.0F, 0.0F, 1.0F);
                     }

                     if (var7.refCount[var8] > 0) {
                        this.paintSquare(var4.wx * 10 + 5, var4.wy * 10 + 5, 0, 0.0F, 0.0F, 1.0F, 1.0F);
                     }
                  }

                  IsoBuilding var10 = IsoPlayer.players[0].getCurrentBuilding();
                  if (var10 != null && var7.buildingCorpseCount != null && var7.buildingCorpseCount.containsKey(var10)) {
                     this.paintSquare(var4.wx * 10 + 5, var4.wy * 10 + 5, var6, 1.0F, 0.0F, 0.0F, 1.0F);
                  }
               }
            }
         }
      }
   }

   private void paintSquare(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
      int var8 = Core.TileScale;
      int var9 = (int)IsoUtils.XToScreenExact(var1, var2 + 1, var3, 0);
      int var10 = (int)IsoUtils.YToScreenExact(var1, var2 + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var9, var10, var9 + 32 * var8, var10 - 16 * var8, var9 + 64 * var8, var10, var9 + 32 * var8, var10 + 16 * var8, var4, var5, var6, var7);
   }

   public void chunkLoaded(IsoChunk var1) {
      if (var1.corpseData == null) {
         var1.corpseData = new ChunkData(this, var1.wx, var1.wy);
      }

      var1.corpseData.wx = var1.wx;
      var1.corpseData.wy = var1.wy;
      var1.corpseData.Reset();
   }

   public void corpseAdded(int var1, int var2, int var3) {
      if (var3 >= 0 && var3 < 8) {
         ChunkData var4 = this.getChunkData(var1, var2);
         if (var4 != null) {
            var4.corpseAdded(var1, var2, var3);

            for (int var5 = 0; var5 < this.playerData.length; var5++) {
               if (var4.levelData[var3].refCount[var5] > 0) {
                  this.playerData[var5].forceUpdate = true;
               }
            }
         }
      } else {
         DebugLog.General.error("invalid z-coordinate %d,%d,%d", new Object[]{var1, var2, var3});
      }
   }

   public void corpseRemoved(int var1, int var2, int var3) {
      if (var3 >= 0 && var3 < 8) {
         ChunkData var4 = this.getChunkData(var1, var2);
         if (var4 != null) {
            var4.corpseRemoved(var1, var2, var3);

            for (int var5 = 0; var5 < this.playerData.length; var5++) {
               if (var4.levelData[var3].refCount[var5] > 0) {
                  this.playerData[var5].forceUpdate = true;
               }
            }
         }
      } else {
         DebugLog.General.error("invalid z-coordinate %d,%d,%d", new Object[]{var1, var2, var3});
      }
   }

   public int getCorpseCount(IsoGameCharacter var1) {
      return var1 != null && var1.getCurrentSquare() != null
         ? this.getCorpseCount((int)var1.getX() / 10, (int)var1.getY() / 10, (int)var1.getZ(), var1.getBuilding())
         : 0;
   }

   private int getCorpseCount(int var1, int var2, int var3, IsoBuilding var4) {
      int var5 = 0;

      for (int var6 = -1; var6 <= 1; var6++) {
         for (int var7 = -1; var7 <= 1; var7++) {
            ChunkData var8 = this.getChunkData((var1 + var7) * 10, (var2 + var6) * 10);
            if (var8 != null) {
               ChunkLevelData var9 = var8.levelData[var3];
               if (var4 == null) {
                  var5 += var9.corpseCount;
               } else if (var9.buildingCorpseCount != null) {
                  Integer var10 = (Integer)var9.buildingCorpseCount.get(var4);
                  if (var10 != null) {
                     var5 += var10;
                  }
               }
            }
         }
      }

      return var5;
   }

   private ChunkData getChunkData(int var1, int var2) {
      IsoChunk var3 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(var1, var2, 0);
      return var3 != null ? var3.corpseData : null;
   }
}
