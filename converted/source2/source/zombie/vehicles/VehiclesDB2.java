package zombie.vehicles;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.sql.DatabaseMetaData;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import zombie.core.logger.ExceptionLogger;
import zombie.iso.IsoChunk;
import zombie.iso.WorldStreamer;
import zombie.popman.ZombiePopulationRenderer;
import zombie.util.Type;
import zombie.vehicles.VehiclesDB2.IImportPlayerFromOldDB;
import zombie.vehicles.VehiclesDB2.MainThread;
import zombie.vehicles.VehiclesDB2.QueueItem;
import zombie.vehicles.VehiclesDB2.SQLStore;
import zombie.vehicles.VehiclesDB2.WorldStreamerThread;

public final class VehiclesDB2 {
   public static final int INVALID_ID = -1;
   private static final int MIN_ID = 1;
   public static final VehiclesDB2 instance = new VehiclesDB2();
   private static final ThreadLocal<ByteBuffer> TL_SliceBuffer = ThreadLocal.withInitial(() -> ByteBuffer.allocate(32768));
   private static final ThreadLocal<byte[]> TL_Bytes = ThreadLocal.withInitial(() -> new byte[1024]);
   private final MainThread m_main = new MainThread();
   private final WorldStreamerThread m_worldStreamer = new WorldStreamerThread();

   public void init() {
      this.m_worldStreamer.m_store.init(this.m_main.m_usedIDs, this.m_main.m_seenChunks);
   }

   public void Reset() {
      assert WorldStreamer.instance.worldStreamer == null;

      this.updateWorldStreamer();

      for (QueueItem var1 = (QueueItem)this.m_main.m_queue.poll(); var1 != null; var1 = (QueueItem)this.m_main.m_queue.poll()) {
         var1.release();
      }

      this.m_main.Reset();
      this.m_worldStreamer.Reset();
   }

   public void updateMain() throws IOException {
      this.m_main.update();
   }

   public void updateWorldStreamer() {
      this.m_worldStreamer.update();
   }

   public void setForceSave() {
      this.m_main.m_forceSave = true;
   }

   public void renderDebug(ZombiePopulationRenderer var1) {
   }

   public void setChunkSeen(int var1, int var2) {
      this.m_main.setChunkSeen(var1, var2);
   }

   public boolean isChunkSeen(int var1, int var2) {
      return this.m_main.isChunkSeen(var1, var2);
   }

   public void setVehicleLoaded(BaseVehicle var1) {
      this.m_main.setVehicleLoaded(var1);
   }

   public void setVehicleUnloaded(BaseVehicle var1) {
      this.m_main.setVehicleUnloaded(var1);
   }

   public boolean isVehicleLoaded(BaseVehicle var1) {
      return this.m_main.m_loadedIDs.contains(var1.sqlID);
   }

   public void loadChunkMain(IsoChunk var1) {
      this.m_main.loadChunk(var1);
   }

   public void loadChunk(IsoChunk var1) throws IOException {
      this.m_worldStreamer.loadChunk(var1);
   }

   public void unloadChunk(IsoChunk var1) {
      if (Thread.currentThread() != WorldStreamer.instance.worldStreamer) {
         boolean var2 = true;
      }

      this.m_worldStreamer.unloadChunk(var1);
   }

   public void addVehicle(BaseVehicle var1) {
      try {
         this.m_main.addVehicle(var1);
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

   public void removeVehicle(BaseVehicle var1) {
      this.m_main.removeVehicle(var1);
   }

   public void updateVehicle(BaseVehicle var1) {
      try {
         this.m_main.updateVehicle(var1);
      } catch (Exception var3) {
         ExceptionLogger.logException(var3);
      }
   }

   public void updateVehicleAndTrailer(BaseVehicle var1) {
      if (var1 != null) {
         this.updateVehicle(var1);
         BaseVehicle var2 = var1.getVehicleTowing();
         if (var2 != null) {
            this.updateVehicle(var2);
         }
      }
   }

   public void importPlayersFromOldDB(IImportPlayerFromOldDB var1) {
      SQLStore var2 = (SQLStore)Type.tryCastTo(this.m_worldStreamer.m_store, SQLStore.class);
      if (var2 != null && var2.m_conn != null) {
         try {
            label100: {
               DatabaseMetaData var3 = var2.m_conn.getMetaData();

               try (ResultSet var4 = var3.getTables(null, null, "localPlayers", null)) {
                  if (var4.next()) {
                     break label100;
                  }
               }

               return;
            }
         } catch (Exception var22) {
            ExceptionLogger.logException(var22);
            return;
         }

         String var23 = "SELECT id, name, wx, wy, x, y, z, worldversion, data, isDead FROM localPlayers";

         try (PreparedStatement var24 = var2.m_conn.prepareStatement(var23)) {
            ResultSet var5 = var24.executeQuery();

            while (var5.next()) {
               int var6 = var5.getInt(1);
               String var7 = var5.getString(2);
               int var8 = var5.getInt(3);
               int var9 = var5.getInt(4);
               float var10 = var5.getFloat(5);
               float var11 = var5.getFloat(6);
               float var12 = var5.getFloat(7);
               int var13 = var5.getInt(8);
               byte[] var14 = var5.getBytes(9);
               boolean var15 = var5.getBoolean(10);
               var1.accept(var6, var7, var8, var9, var10, var11, var12, var13, var14, var15);
            }
         } catch (Exception var20) {
            ExceptionLogger.logException(var20);
         }

         try {
            Statement var25 = var2.m_conn.createStatement();
            var25.executeUpdate("DROP TABLE localPlayers");
            var25.executeUpdate("DROP TABLE networkPlayers");
            var2.m_conn.commit();
         } catch (Exception var17) {
            ExceptionLogger.logException(var17);
         }
      }
   }
}
