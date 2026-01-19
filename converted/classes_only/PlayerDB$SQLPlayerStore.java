package zombie.savefile;

import gnu.trove.set.hash.TIntHashSet;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.savefile.PlayerDB.IPlayerStore;
import zombie.savefile.PlayerDB.PlayerData;
import zombie.util.ByteBufferBackedInputStream;

final class PlayerDB$SQLPlayerStore implements IPlayerStore {
   Connection m_conn = null;

   private PlayerDB$SQLPlayerStore() {
   }

   public void init(TIntHashSet var1) throws Exception {
      var1.clear();
      if (!Core.getInstance().isNoSave()) {
         this.m_conn = PlayerDBHelper.create();
         this.initUsedIDs(var1);
      }
   }

   public void Reset() {
      if (this.m_conn != null) {
         try {
            this.m_conn.close();
         } catch (SQLException var2) {
            ExceptionLogger.logException(var2);
         }

         this.m_conn = null;
      }
   }

   public void save(PlayerData var1) throws Exception {
      if (!$assertionsDisabled && var1.m_sqlID < 1) {
         throw new AssertionError();
      } else if (this.m_conn != null) {
         if (this.isInDB(var1.m_sqlID)) {
            this.update(var1);
         } else {
            this.add(var1);
         }
      }
   }

   public boolean load(PlayerData var1) throws Exception {
      if (!$assertionsDisabled && var1.m_sqlID < 1) {
         throw new AssertionError();
      } else if (this.m_conn == null) {
         return false;
      } else {
         String var2 = "SELECT data,worldversion,x,y,z,isDead,name FROM localPlayers WHERE id=?";

         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_sqlID);
            ResultSet var4 = var3.executeQuery();
            if (var4.next()) {
               InputStream var5 = var4.getBinaryStream(1);
               var1.setBytes(var5);
               var1.m_WorldVersion = var4.getInt(2);
               var1.m_x = var4.getInt(3);
               var1.m_y = var4.getInt(4);
               var1.m_z = var4.getInt(5);
               var1.m_isDead = var4.getBoolean(6);
               var1.m_name = var4.getString(7);
               return true;
            }
         }

         return false;
      }
   }

   public boolean loadEverythingExceptBytes(PlayerData var1) throws Exception {
      if (this.m_conn == null) {
         return false;
      } else {
         String var2 = "SELECT worldversion,x,y,z,isDead,name FROM localPlayers WHERE id=?";

         try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
            var3.setInt(1, var1.m_sqlID);
            ResultSet var4 = var3.executeQuery();
            if (var4.next()) {
               var1.m_WorldVersion = var4.getInt(1);
               var1.m_x = var4.getInt(2);
               var1.m_y = var4.getInt(3);
               var1.m_z = var4.getInt(4);
               var1.m_isDead = var4.getBoolean(5);
               var1.m_name = var4.getString(6);
               return true;
            }
         }

         return false;
      }
   }

   void initUsedIDs(TIntHashSet var1) throws SQLException {
      String var2 = "SELECT id FROM localPlayers";

      try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
         ResultSet var4 = var3.executeQuery();

         while (var4.next()) {
            var1.add(var4.getInt(1));
         }
      }
   }

   boolean isInDB(int var1) throws SQLException {
      String var2 = "SELECT 1 FROM localPlayers WHERE id=?";

      boolean var5;
      try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
         var3.setInt(1, var1);
         ResultSet var4 = var3.executeQuery();
         var5 = var4.next();
      }

      return var5;
   }

   void add(PlayerData var1) throws Exception {
      if (this.m_conn != null && var1.m_sqlID >= 1) {
         String var2 = "INSERT INTO localPlayers(wx,wy,x,y,z,worldversion,data,isDead,name,id) VALUES(?,?,?,?,?,?,?,?,?,?)";

         try {
            try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
               var3.setInt(1, (int)(var1.m_x / 10.0F));
               var3.setInt(2, (int)(var1.m_y / 10.0F));
               var3.setFloat(3, var1.m_x);
               var3.setFloat(4, var1.m_y);
               var3.setFloat(5, var1.m_z);
               var3.setInt(6, var1.m_WorldVersion);
               ByteBuffer var4 = var1.m_byteBuffer;
               var4.rewind();
               var3.setBinaryStream(7, new ByteBufferBackedInputStream(var4), var4.remaining());
               var3.setBoolean(8, var1.m_isDead);
               var3.setString(9, var1.m_name);
               var3.setInt(10, var1.m_sqlID);
               int var5 = var3.executeUpdate();
               this.m_conn.commit();
            }
         } catch (Exception var8) {
            PlayerDBHelper.rollback(this.m_conn);
            throw var8;
         }
      }
   }

   public void update(PlayerData var1) throws Exception {
      if (this.m_conn != null && var1.m_sqlID >= 1) {
         String var2 = "UPDATE localPlayers SET wx = ?, wy = ?, x = ?, y = ?, z = ?, worldversion = ?, data = ?, isDead = ?, name = ? WHERE id=?";

         try {
            try (PreparedStatement var3 = this.m_conn.prepareStatement(var2)) {
               var3.setInt(1, (int)(var1.m_x / 10.0F));
               var3.setInt(2, (int)(var1.m_y / 10.0F));
               var3.setFloat(3, var1.m_x);
               var3.setFloat(4, var1.m_y);
               var3.setFloat(5, var1.m_z);
               var3.setInt(6, var1.m_WorldVersion);
               ByteBuffer var4 = var1.m_byteBuffer;
               var4.rewind();
               var3.setBinaryStream(7, new ByteBufferBackedInputStream(var4), var4.remaining());
               var3.setBoolean(8, var1.m_isDead);
               var3.setString(9, var1.m_name);
               var3.setInt(10, var1.m_sqlID);
               int var5 = var3.executeUpdate();
               this.m_conn.commit();
            }
         } catch (Exception var8) {
            PlayerDBHelper.rollback(this.m_conn);
            throw var8;
         }
      }
   }
}
