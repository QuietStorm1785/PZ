package zombie.savefile;

import java.nio.ByteBuffer;
import java.sql.Connection;
import java.sql.DatabaseMetaData;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.concurrent.ConcurrentLinkedQueue;
import zombie.core.Core;
import zombie.core.logger.ExceptionLogger;
import zombie.core.network.ByteBufferWriter;
import zombie.core.raknet.UdpConnection;
import zombie.core.znet.SteamUtils;
import zombie.debug.DebugLog;
import zombie.network.GameServer;
import zombie.network.PacketTypes.PacketType;
import zombie.savefile.ServerPlayerDB.NetworkCharacterData;

public final class ServerPlayerDB {
   private static ServerPlayerDB instance = null;
   private static boolean allow = false;
   private Connection conn = null;
   private ConcurrentLinkedQueue<NetworkCharacterData> CharactersToSave;

   public static void setAllow(boolean var0) {
      allow = var0;
   }

   public static boolean isAllow() {
      return allow;
   }

   public static synchronized ServerPlayerDB getInstance() {
      if (instance == null && allow) {
         instance = new ServerPlayerDB();
      }

      return instance;
   }

   public static boolean isAvailable() {
      return instance != null;
   }

   public ServerPlayerDB() {
      if (!Core.getInstance().isNoSave()) {
         this.create();
      }
   }

   public void close() {
      instance = null;
      allow = false;
   }

   private void create() {
      this.conn = PlayerDBHelper.create();
      this.CharactersToSave = new ConcurrentLinkedQueue<>();
      DatabaseMetaData var1 = null;

      try {
         var1 = this.conn.getMetaData();
         Statement var2 = this.conn.createStatement();
         ResultSet var3 = var1.getColumns(null, null, "networkPlayers", "steamid");
         if (!var3.next()) {
            var2.executeUpdate("ALTER TABLE 'networkPlayers' ADD 'steamid' STRING NULL");
         }

         var3.close();
         var2.close();
      } catch (SQLException var4) {
         var4.printStackTrace();
      }
   }

   public void process() {
      if (!this.CharactersToSave.isEmpty()) {
         for (NetworkCharacterData var1 = this.CharactersToSave.poll(); var1 != null; var1 = this.CharactersToSave.poll()) {
            this.serverUpdateNetworkCharacterInt(var1);
         }
      }
   }

   public void serverUpdateNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
      this.CharactersToSave.add(new NetworkCharacterData(var1, var2));
   }

   private void serverUpdateNetworkCharacterInt(NetworkCharacterData var1) {
      if (var1.playerIndex >= 0 && var1.playerIndex < 4) {
         if (this.conn != null) {
            String var2;
            if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
               var2 = "SELECT id FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
            } else {
               var2 = "SELECT id FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
            }

            String var3 = "INSERT INTO networkPlayers(world,username,steamid, playerIndex,name,x,y,z,worldversion,isDead,data) VALUES(?,?,?,?,?,?,?,?,?,?,?)";
            String var4 = "UPDATE networkPlayers SET x=?, y=?, z=?, worldversion = ?, isDead = ?, data = ?, name = ? WHERE id=?";

            try {
               try (PreparedStatement var5 = this.conn.prepareStatement(var2)) {
                  if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
                     var5.setString(1, var1.steamid);
                  } else {
                     var5.setString(1, var1.username);
                  }

                  var5.setString(2, Core.GameSaveWorld);
                  var5.setInt(3, var1.playerIndex);
                  ResultSet var6 = var5.executeQuery();
                  if (var6.next()) {
                     int var7 = var6.getInt(1);

                     try (PreparedStatement var8 = this.conn.prepareStatement(var4)) {
                        var8.setFloat(1, var1.x);
                        var8.setFloat(2, var1.y);
                        var8.setFloat(3, var1.z);
                        var8.setInt(4, var1.worldVersion);
                        var8.setBoolean(5, var1.isDead);
                        var8.setBytes(6, var1.buffer);
                        var8.setString(7, var1.playerName);
                        var8.setInt(8, var7);
                        int var9 = var8.executeUpdate();
                        this.conn.commit();
                        return;
                     }
                  }
               }

               try (PreparedStatement var18 = this.conn.prepareStatement(var3)) {
                  var18.setString(1, Core.GameSaveWorld);
                  var18.setString(2, var1.username);
                  var18.setString(3, var1.steamid);
                  var18.setInt(4, var1.playerIndex);
                  var18.setString(5, var1.playerName);
                  var18.setFloat(6, var1.x);
                  var18.setFloat(7, var1.y);
                  var18.setFloat(8, var1.z);
                  var18.setInt(9, var1.worldVersion);
                  var18.setBoolean(10, var1.isDead);
                  var18.setBytes(11, var1.buffer);
                  int var19 = var18.executeUpdate();
                  this.conn.commit();
               }
            } catch (Exception var17) {
               ExceptionLogger.logException(var17);
               PlayerDBHelper.rollback(this.conn);
            }
         }
      }
   }

   private void serverConvertNetworkCharacter(String var1, String var2) {
      try {
         String var3 = "UPDATE networkPlayers SET steamid=? WHERE username=? AND world=? AND (steamid is null or steamid = '')";

         try (PreparedStatement var4 = this.conn.prepareStatement(var3)) {
            var4.setString(1, var2);
            var4.setString(2, var1);
            var4.setString(3, Core.GameSaveWorld);
            int var5 = var4.executeUpdate();
            if (var5 > 0) {
               DebugLog.General.warn("serverConvertNetworkCharacter: The steamid was set for the '" + var1 + "' for " + var5 + " players. ");
            }

            this.conn.commit();
         }
      } catch (SQLException var9) {
         ExceptionLogger.logException(var9);
      }
   }

   public void serverLoadNetworkCharacter(ByteBuffer var1, UdpConnection var2) {
      byte var3 = var1.get();
      if (var3 < 0 || var3 >= 4) {
         ByteBufferWriter var18 = var2.startPacket();
         PacketType.LoadPlayerProfile.doPacket(var18);
         var18.putByte((byte)0);
         var18.putInt(var3);
         PacketType.LoadPlayerProfile.send(var2);
      } else if (this.conn != null) {
         if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
            this.serverConvertNetworkCharacter(var2.username, var2.idStr);
         }

         String var4;
         if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
            var4 = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE steamid=? AND world=? AND playerIndex=?";
         } else {
            var4 = "SELECT id, x, y, z, data, worldversion, isDead FROM networkPlayers WHERE username=? AND world=? AND playerIndex=?";
         }

         try (PreparedStatement var5 = this.conn.prepareStatement(var4)) {
            if (GameServer.bCoop && SteamUtils.isSteamModeEnabled()) {
               var5.setString(1, var2.idStr);
            } else {
               var5.setString(1, var2.username);
            }

            var5.setString(2, Core.GameSaveWorld);
            var5.setInt(3, var3);
            ResultSet var6 = var5.executeQuery();
            if (var6.next()) {
               int var7 = var6.getInt(1);
               float var8 = var6.getFloat(2);
               float var9 = var6.getFloat(3);
               float var10 = var6.getFloat(4);
               byte[] var11 = var6.getBytes(5);
               int var12 = var6.getInt(6);
               boolean var13 = var6.getBoolean(7);
               ByteBufferWriter var14 = var2.startPacket();
               PacketType.LoadPlayerProfile.doPacket(var14);
               var14.putByte((byte)1);
               var14.putInt(var3);
               var14.putFloat(var8);
               var14.putFloat(var9);
               var14.putFloat(var10);
               var14.putInt(var12);
               var14.putByte((byte)(var13 ? 1 : 0));
               var14.putInt(var11.length);
               var14.bb.put(var11);
               PacketType.LoadPlayerProfile.send(var2);
            } else {
               ByteBufferWriter var19 = var2.startPacket();
               PacketType.LoadPlayerProfile.doPacket(var19);
               var19.putByte((byte)0);
               var19.putInt(var3);
               PacketType.LoadPlayerProfile.send(var2);
            }
         } catch (SQLException var17) {
            ExceptionLogger.logException(var17);
         }
      }
   }
}
