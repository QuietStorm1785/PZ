package zombie.savefile;

import java.io.File;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import zombie.ZomboidFileSystem;
import zombie.core.BoxedStaticValues;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.debug.DebugLog;
import zombie.util.PZSQLUtils;
import zombie.vehicles.VehicleDBHelper;

public final class PlayerDBHelper {
   public static Connection create() {
      Connection var0 = null;
      String var1 = ZomboidFileSystem.instance.getCurrentSaveDir();
      File var2 = new File(var1);
      if (!var2.exists()) {
         var2.mkdirs();
      }

      File var3 = new File(var1 + File.separator + "players.db");
      var3.setReadable(true, false);
      var3.setExecutable(true, false);
      var3.setWritable(true, false);
      if (!var3.exists()) {
         try {
            var3.createNewFile();
            var0 = PZSQLUtils.getConnection(var3.getAbsolutePath());
            Statement var4 = var0.createStatement();
            var4.executeUpdate(
               "CREATE TABLE localPlayers (id   INTEGER PRIMARY KEY NOT NULL,name STRING,wx    INTEGER,wy    INTEGER,x    FLOAT,y    FLOAT,z    FLOAT,worldversion    INTEGER,data BLOB,isDead BOOLEAN);"
            );
            var4.executeUpdate(
               "CREATE TABLE networkPlayers (id   INTEGER PRIMARY KEY NOT NULL,world TEXT,username TEXT,playerIndex   INTEGER,name STRING,steamid STRING,x    FLOAT,y    FLOAT,z    FLOAT,worldversion    INTEGER,data BLOB,isDead BOOLEAN);"
            );
            var4.executeUpdate("CREATE INDEX inpusername ON networkPlayers (username);");
            var4.close();
         } catch (Exception var8) {
            ExceptionLogger.logException(var8);
            DebugLog.log("failed to create players database");
            System.exit(1);
         }
      }

      if (var0 == null) {
         try {
            var0 = PZSQLUtils.getConnection(var3.getAbsolutePath());
         } catch (Exception var7) {
            ExceptionLogger.logException(var7);
            DebugLog.log("failed to create players database");
            System.exit(1);
         }
      }

      try {
         Statement var9 = var0.createStatement();
         var9.executeQuery("PRAGMA JOURNAL_MODE=TRUNCATE;");
         var9.close();
      } catch (Exception var6) {
         ExceptionLogger.logException(var6);
         DebugLog.log("failed to config players.db");
         System.exit(1);
      }

      try {
         var0.setAutoCommit(false);
      } catch (SQLException var5) {
         DebugLog.log("failed to setAutoCommit for players.db");
      }

      return var0;
   }

   public static void rollback(Connection var0) {
      if (var0 != null) {
         try {
            var0.rollback();
         } catch (SQLException var2) {
            ExceptionLogger.logException(var2);
         }
      }
   }

   public static boolean isPlayerAlive(String var0, int var1) {
      if (Core.getInstance().isNoSave()) {
         return false;
      } else {
         File var2 = new File(var0 + File.separator + "map_p.bin");
         if (var2.exists()) {
            return true;
         } else if (VehicleDBHelper.isPlayerAlive(var0, var1)) {
            return true;
         } else if (var1 == -1) {
            return false;
         } else {
            try {
               File var3 = new File(var0 + File.separator + "players.db");
               if (!var3.exists()) {
                  return false;
               } else {
                  var3.setReadable(true, false);

                  boolean var8;
                  try (Connection var4 = PZSQLUtils.getConnection(var3.getAbsolutePath())) {
                     String var5 = "SELECT isDead FROM localPlayers WHERE id=?";

                     try (PreparedStatement var6 = var4.prepareStatement(var5)) {
                        var6.setInt(1, var1);
                        ResultSet var7 = var6.executeQuery();
                        if (!var7.next()) {
                           return false;
                        }

                        var8 = !var7.getBoolean(1);
                     }
                  }

                  return var8;
               }
            } catch (Throwable var13) {
               ExceptionLogger.logException(var13);
               return false;
            }
         }
      }
   }

   public static ArrayList<Object> getPlayers(String var0) throws SQLException {
      ArrayList var1 = new ArrayList();
      if (Core.getInstance().isNoSave()) {
         return var1;
      } else {
         File var2 = new File(var0 + File.separator + "players.db");
         if (!var2.exists()) {
            return var1;
         } else {
            var2.setReadable(true, false);

            try (Connection var3 = PZSQLUtils.getConnection(var2.getAbsolutePath())) {
               String var4 = "SELECT id, name, isDead FROM localPlayers";

               try (PreparedStatement var5 = var3.prepareStatement(var4)) {
                  ResultSet var6 = var5.executeQuery();

                  while (var6.next()) {
                     int var7 = var6.getInt(1);
                     String var8 = var6.getString(2);
                     boolean var9 = var6.getBoolean(3);
                     var1.add(BoxedStaticValues.toDouble(var7));
                     var1.add(var8);
                     var1.add(var9 ? Boolean.TRUE : Boolean.FALSE);
                  }
               }
            }

            return var1;
         }
      }
   }

   public static void setPlayer1(String var0, int var1) throws SQLException {
      if (!Core.getInstance().isNoSave()) {
         if (var1 != 1) {
            File var2 = new File(var0 + File.separator + "players.db");
            if (var2.exists()) {
               var2.setReadable(true, false);

               try (Connection var3 = PZSQLUtils.getConnection(var2.getAbsolutePath())) {
                  boolean var4 = false;
                  boolean var5 = false;
                  int var6 = -1;
                  int var7 = -1;
                  String var8 = "SELECT id FROM localPlayers";

                  try (PreparedStatement var9 = var3.prepareStatement(var8)) {
                     ResultSet var10 = var9.executeQuery();

                     while (var10.next()) {
                        int var11 = var10.getInt(1);
                        if (var11 == 1) {
                           var4 = true;
                        } else if (var6 == -1 || var6 > var11) {
                           var6 = var11;
                        }

                        if (var11 == var1) {
                           var5 = true;
                        }

                        var7 = Math.max(var7, var11);
                     }
                  }

                  if (var1 <= 0) {
                     if (!var4) {
                        return;
                     }

                     var8 = "UPDATE localPlayers SET id=? WHERE id=?";

                     try (PreparedStatement var27 = var3.prepareStatement(var8)) {
                        var27.setInt(1, var7 + 1);
                        var27.setInt(2, 1);
                        var27.executeUpdate();
                        return;
                     }
                  }

                  if (!var5) {
                     return;
                  }

                  if (var4) {
                     var8 = "UPDATE localPlayers SET id=? WHERE id=?";

                     try (PreparedStatement var25 = var3.prepareStatement(var8)) {
                        var25.setInt(1, var7 + 1);
                        var25.setInt(2, 1);
                        var25.executeUpdate();
                        var25.setInt(1, 1);
                        var25.setInt(2, var1);
                        var25.executeUpdate();
                        var25.setInt(1, var1);
                        var25.setInt(2, var7 + 1);
                        var25.executeUpdate();
                     }
                  } else {
                     var8 = "UPDATE localPlayers SET id=? WHERE id=?";

                     try (PreparedStatement var26 = var3.prepareStatement(var8)) {
                        var26.setInt(1, 1);
                        var26.setInt(2, var1);
                        var26.executeUpdate();
                     }
                  }
               }
            }
         }
      }
   }
}
