package zombie.savefile;

import gnu.trove.set.hash.TIntHashSet;
import java.io.File;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.ZomboidFileSystem;
import zombie.characters.IsoPlayer;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.utils.UpdateLimit;
import zombie.iso.IsoCell;
import zombie.iso.IsoChunkMap;
import zombie.iso.IsoWorld;
import zombie.iso.WorldStreamer;
import zombie.savefile.PlayerDB.IPlayerStore;
import zombie.savefile.PlayerDB.PlayerData;
import zombie.savefile.PlayerDB.SQLPlayerStore;
import zombie.vehicles.VehiclesDB2;

public final class PlayerDB {
   public static final int INVALID_ID = -1;
   private static final int MIN_ID = 1;
   private static PlayerDB instance = null;
   private static final ThreadLocal<ByteBuffer> TL_SliceBuffer = ThreadLocal.withInitial(() -> ByteBuffer.allocate(32768));
   private static final ThreadLocal<byte[]> TL_Bytes = ThreadLocal.withInitial(() -> new byte[1024]);
   private static boolean s_allow = false;
   private final IPlayerStore m_store = new SQLPlayerStore();
   private final TIntHashSet m_usedIDs = new TIntHashSet();
   private final ConcurrentLinkedQueue<PlayerData> m_toThread = new ConcurrentLinkedQueue<>();
   private final ConcurrentLinkedQueue<PlayerData> m_fromThread = new ConcurrentLinkedQueue<>();
   private boolean m_forceSavePlayers;
   public boolean m_canSavePlayers = false;
   private final UpdateLimit m_saveToDBPeriod = new UpdateLimit(10000L);

   public static synchronized PlayerDB getInstance() {
      if (instance == null && s_allow) {
         instance = new PlayerDB();
      }

      return instance;
   }

   public static void setAllow(boolean var0) {
      s_allow = var0;
   }

   public static boolean isAllow() {
      return s_allow;
   }

   public static boolean isAvailable() {
      return instance != null;
   }

   public PlayerDB() {
      if (!Core.getInstance().isNoSave()) {
         this.create();
      }
   }

   private void create() {
      try {
         this.m_store.init(this.m_usedIDs);
         this.m_usedIDs.add(1);
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }
   }

   public void close() {
      assert WorldStreamer.instance.worldStreamer == null;

      this.updateWorldStreamer();

      assert this.m_toThread.isEmpty();

      try {
         this.m_store.Reset();
      } catch (Exception var2) {
         ExceptionLogger.logException(var2);
      }

      this.m_fromThread.clear();
      instance = null;
      s_allow = false;
   }

   private int allocateID() {
      synchronized (this.m_usedIDs) {
         for (int var2 = 1; var2 < Integer.MAX_VALUE; var2++) {
            if (!this.m_usedIDs.contains(var2)) {
               this.m_usedIDs.add(var2);
               return var2;
            }
         }
      }

      throw new RuntimeException("ran out of unused players.db ids");
   }

   private PlayerData allocPlayerData() {
      PlayerData var1 = this.m_fromThread.poll();
      if (var1 == null) {
         var1 = new PlayerData();
      }

      assert var1.m_sqlID == -1;

      return var1;
   }

   private void releasePlayerData(PlayerData var1) {
      var1.m_sqlID = -1;
      this.m_fromThread.add(var1);
   }

   public void updateMain() {
      if (this.m_canSavePlayers && (this.m_forceSavePlayers || this.m_saveToDBPeriod.Check())) {
         this.m_forceSavePlayers = false;
         this.savePlayersAsync();
         VehiclesDB2.instance.setForceSave();
      }
   }

   public void updateWorldStreamer() {
      for (PlayerData var1 = this.m_toThread.poll(); var1 != null; var1 = this.m_toThread.poll()) {
         try {
            this.m_store.save(var1);
         } catch (Exception var6) {
            ExceptionLogger.logException(var6);
         } finally {
            this.releasePlayerData(var1);
         }
      }
   }

   private void savePlayerAsync(IsoPlayer var1) throws Exception {
      if (var1 != null) {
         if (var1.sqlID == -1) {
            var1.sqlID = this.allocateID();
         }

         PlayerData var2 = this.allocPlayerData();

         try {
            var2.set(var1);
            this.m_toThread.add(var2);
         } catch (Exception var4) {
            this.releasePlayerData(var2);
            throw var4;
         }
      }
   }

   private void savePlayersAsync() {
      for (int var1 = 0; var1 < IsoPlayer.numPlayers; var1++) {
         IsoPlayer var2 = IsoPlayer.players[var1];
         if (var2 != null) {
            try {
               this.savePlayerAsync(var2);
            } catch (Exception var4) {
               ExceptionLogger.logException(var4);
            }
         }
      }
   }

   public void savePlayers() {
      if (this.m_canSavePlayers) {
         this.m_forceSavePlayers = true;
      }
   }

   public void saveLocalPlayersForce() {
      this.savePlayersAsync();
      if (WorldStreamer.instance.worldStreamer == null) {
         this.updateWorldStreamer();
      }
   }

   public void importPlayersFromVehiclesDB() {
      VehiclesDB2.instance.importPlayersFromOldDB((var1, var2, var3, var4, var5, var6, var7, var8, var9, var10) -> {
         PlayerData var11 = this.allocPlayerData();
         var11.m_sqlID = this.allocateID();
         var11.m_x = var5;
         var11.m_y = var6;
         var11.m_z = var7;
         var11.m_isDead = var10;
         var11.m_name = var2;
         var11.m_WorldVersion = var8;
         var11.setBytes(var9);

         try {
            this.m_store.save(var11);
         } catch (Exception var13) {
            ExceptionLogger.logException(var13);
         }

         this.releasePlayerData(var11);
      });
   }

   public void uploadLocalPlayers2DB() {
      this.savePlayersAsync();
      String var1 = ZomboidFileSystem.instance.getCurrentSaveDir();

      for (int var2 = 1; var2 < 100; var2++) {
         File var3 = new File(var1 + File.separator + "map_p" + var2 + ".bin");
         if (var3.exists()) {
            try {
               IsoPlayer var4 = new IsoPlayer(IsoWorld.instance.CurrentCell);
               var4.load(var3.getAbsolutePath());
               this.savePlayerAsync(var4);
               var3.delete();
            } catch (Exception var5) {
               ExceptionLogger.logException(var5);
            }
         }
      }

      if (WorldStreamer.instance.worldStreamer == null) {
         this.updateWorldStreamer();
      }
   }

   private boolean loadPlayer(int var1, IsoPlayer var2) {
      PlayerData var3 = this.allocPlayerData();

      boolean var4;
      try {
         var3.m_sqlID = var1;
         if (this.m_store.load(var3)) {
            var2.load(var3.m_byteBuffer, var3.m_WorldVersion);
            if (var3.m_isDead) {
               var2.getBodyDamage().setOverallBodyHealth(0.0F);
               var2.setHealth(0.0F);
            }

            var2.sqlID = var1;
            return true;
         }

         var4 = false;
      } catch (Exception var8) {
         ExceptionLogger.logException(var8);
         return false;
      } finally {
         this.releasePlayerData(var3);
      }

      return var4;
   }

   public boolean loadLocalPlayer(int var1) {
      try {
         IsoPlayer var2 = IsoPlayer.getInstance();
         if (var2 == null) {
            var2 = new IsoPlayer(IsoCell.getInstance());
            IsoPlayer.setInstance(var2);
            IsoPlayer.players[0] = var2;
         }

         if (this.loadPlayer(var1, var2)) {
            int var3 = (int)(var2.x / 10.0F);
            int var4 = (int)(var2.y / 10.0F);
            IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldX = var3 + IsoWorld.saveoffsetx * 30;
            IsoCell.getInstance().ChunkMap[IsoPlayer.getPlayerIndex()].WorldY = var4 + IsoWorld.saveoffsety * 30;
            return true;
         }
      } catch (Exception var5) {
         ExceptionLogger.logException(var5);
      }

      return false;
   }

   public ArrayList<IsoPlayer> getAllLocalPlayers() {
      ArrayList var1 = new ArrayList();
      this.m_usedIDs.forEach(var2 -> {
         if (var2 <= 1) {
            return true;
         } else {
            IsoPlayer var3 = new IsoPlayer(IsoWorld.instance.CurrentCell);
            if (this.loadPlayer(var2, var3)) {
               var1.add(var3);
            }

            return true;
         }
      });
      return var1;
   }

   public boolean loadLocalPlayerInfo(int var1) {
      PlayerData var2 = this.allocPlayerData();

      boolean var3;
      try {
         var2.m_sqlID = var1;
         if (!this.m_store.loadEverythingExceptBytes(var2)) {
            return false;
         }

         IsoChunkMap.WorldXA = (int)var2.m_x;
         IsoChunkMap.WorldYA = (int)var2.m_y;
         IsoChunkMap.WorldZA = (int)var2.m_z;
         IsoChunkMap.WorldXA = IsoChunkMap.WorldXA + 300 * IsoWorld.saveoffsetx;
         IsoChunkMap.WorldYA = IsoChunkMap.WorldYA + 300 * IsoWorld.saveoffsety;
         IsoChunkMap.SWorldX[0] = (int)(var2.m_x / 10.0F);
         IsoChunkMap.SWorldY[0] = (int)(var2.m_y / 10.0F);
         IsoChunkMap.SWorldX[0] = IsoChunkMap.SWorldX[0] + 30 * IsoWorld.saveoffsetx;
         IsoChunkMap.SWorldY[0] = IsoChunkMap.SWorldY[0] + 30 * IsoWorld.saveoffsety;
         var3 = true;
      } catch (Exception var7) {
         ExceptionLogger.logException(var7);
         return false;
      } finally {
         this.releasePlayerData(var2);
      }

      return var3;
   }
}
