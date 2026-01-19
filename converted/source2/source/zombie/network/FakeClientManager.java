package zombie.network;

import fmod.fmod.FMODManager;
import java.nio.ByteBuffer;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.HashMap;
import java.util.HashSet;
import org.json.JSONArray;
import org.json.JSONObject;
import zombie.core.Core;
import zombie.core.Rand;
import zombie.core.raknet.VoiceManager;
import zombie.core.znet.ZNet;
import zombie.debug.DebugLog;
import zombie.debug.DebugType;
import zombie.iso.IsoDirections;
import zombie.network.FakeClientManager.1;
import zombie.network.FakeClientManager.Client;
import zombie.network.FakeClientManager.HordeCreator;
import zombie.network.FakeClientManager.Movement;
import zombie.network.FakeClientManager.Network;
import zombie.network.FakeClientManager.Player;
import zombie.network.FakeClientManager.SoundMaker;
import zombie.network.FakeClientManager.StringUTF;
import zombie.network.FakeClientManager.ZombieSimulator;
import zombie.network.FakeClientManager.Movement.Motion;
import zombie.network.FakeClientManager.Movement.Type;
import zombie.network.FakeClientManager.ZombieSimulator.Behaviour;

public class FakeClientManager {
   private static final int SERVER_PORT = 16261;
   private static final int CLIENT_PORT = 17500;
   private static final String CLIENT_ADDRESS = "0.0.0.0";
   private static final String versionNumber = Core.getInstance().getVersion();
   private static final DateFormat logDateFormat = new SimpleDateFormat("HH:mm:ss.SSS");
   private static final ThreadLocal<StringUTF> stringUTF = ThreadLocal.withInitial(StringUTF::new);
   private static int logLevel = 0;
   private static long startTime = System.currentTimeMillis();
   private static final HashSet<Player> players = new HashSet<>();

   public static String ReadStringUTF(ByteBuffer var0) {
      return stringUTF.get().load(var0);
   }

   public static void WriteStringUTF(ByteBuffer var0, String var1) {
      stringUTF.get().save(var0, var1);
   }

   private static void sleep(long var0) {
      try {
         Thread.sleep(var0);
      } catch (InterruptedException var3) {
         var3.printStackTrace();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private static HashMap<Integer, Movement> load(String var0) {
      HashMap var1 = new HashMap();

      try {
         String var2 = new String(Files.readAllBytes(Paths.get(var0)));
         JSONObject var3 = new JSONObject(var2);
         Movement.version = var3.getString("version");
         JSONObject var4 = var3.getJSONObject("config");
         JSONObject var5 = var4.getJSONObject("client");
         JSONObject var6 = var5.getJSONObject("connection");
         if (var6.has("serverHost")) {
            Client.connectionServerHost = var6.getString("serverHost");
         }

         Client.connectionInterval = var6.getLong("interval");
         Client.connectionTimeout = var6.getLong("timeout");
         Client.connectionDelay = var6.getLong("delay");
         JSONObject var7 = var5.getJSONObject("statistics");
         Client.statisticsPeriod = var7.getInt("period");
         Client.statisticsClientID = Math.max(var7.getInt("id"), -1);
         if (var5.has("checksum")) {
            JSONObject var8 = var5.getJSONObject("checksum");
            Client.luaChecksum = var8.getString("lua");
            Client.scriptChecksum = var8.getString("script");
         }

         if (var4.has("zombies")) {
            var6 = var4.getJSONObject("zombies");
            Behaviour var43 = Behaviour.Normal;
            if (var6.has("behaviour")) {
               var43 = Behaviour.valueOf(var6.getString("behaviour"));
            }

            ZombieSimulator.behaviour = var43;
            if (var6.has("maxZombiesPerUpdate")) {
               ZombieSimulator.maxZombiesPerUpdate = var6.getInt("maxZombiesPerUpdate");
            }

            if (var6.has("deleteZombieDistance")) {
               int var46 = var6.getInt("deleteZombieDistance");
               ZombieSimulator.deleteZombieDistanceSquared = var46 * var46;
            }

            if (var6.has("forgotZombieDistance")) {
               int var47 = var6.getInt("forgotZombieDistance");
               ZombieSimulator.forgotZombieDistanceSquared = var47 * var47;
            }

            if (var6.has("canSeeZombieDistance")) {
               int var48 = var6.getInt("canSeeZombieDistance");
               ZombieSimulator.canSeeZombieDistanceSquared = var48 * var48;
            }

            if (var6.has("seeZombieDistance")) {
               int var49 = var6.getInt("seeZombieDistance");
               ZombieSimulator.seeZombieDistanceSquared = var49 * var49;
            }

            if (var6.has("canChangeTarget")) {
               ZombieSimulator.canChangeTarget = var6.getBoolean("canChangeTarget");
            }
         }

         var6 = var4.getJSONObject("player");
         Player.fps = var6.getInt("fps");
         Player.predictInterval = var6.getInt("predict");
         if (var6.has("damage")) {
            Player.damage = (float)var6.getDouble("damage");
         }

         if (var6.has("voip")) {
            Player.isVOIPEnabled = var6.getBoolean("voip");
         }

         var7 = var4.getJSONObject("movement");
         Movement.defaultRadius = var7.getInt("radius");
         JSONObject var50 = var7.getJSONObject("motion");
         Movement.aimSpeed = var50.getInt("aim");
         Movement.sneakSpeed = var50.getInt("sneak");
         Movement.sneakRunSpeed = var50.getInt("sneakrun");
         Movement.walkSpeed = var50.getInt("walk");
         Movement.runSpeed = var50.getInt("run");
         Movement.sprintSpeed = var50.getInt("sprint");
         JSONObject var9 = var50.getJSONObject("pedestrian");
         Movement.pedestrianSpeedMin = var9.getInt("min");
         Movement.pedestrianSpeedMax = var9.getInt("max");
         JSONObject var10 = var50.getJSONObject("vehicle");
         Movement.vehicleSpeedMin = var10.getInt("min");
         Movement.vehicleSpeedMax = var10.getInt("max");
         JSONArray var39 = var3.getJSONArray("movements");

         for (int var42 = 0; var42 < var39.length(); var42++) {
            var7 = var39.getJSONObject(var42);
            int var51 = var7.getInt("id");
            String var52 = null;
            if (var7.has("description")) {
               var52 = var7.getString("description");
            }

            int var53 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
            int var11 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
            if (var7.has("spawn")) {
               JSONObject var12 = var7.getJSONObject("spawn");
               var53 = var12.getInt("x");
               var11 = var12.getInt("y");
            }

            Motion var54 = Math.random() > 0.8F ? Motion.Vehicle : Motion.Pedestrian;
            if (var7.has("motion")) {
               var54 = Motion.valueOf(var7.getString("motion"));
            }

            int var13 = 0;
            if (var7.has("speed")) {
               var13 = var7.getInt("speed");
            } else {
               switch (1.$SwitchMap$zombie$network$FakeClientManager$Movement$Motion[var54.ordinal()]) {
                  case 1:
                     var13 = Movement.aimSpeed;
                     break;
                  case 2:
                     var13 = Movement.sneakSpeed;
                     break;
                  case 3:
                     var13 = Movement.sneakRunSpeed;
                     break;
                  case 4:
                     var13 = Movement.runSpeed;
                     break;
                  case 5:
                     var13 = Movement.sprintSpeed;
                     break;
                  case 6:
                     var13 = Movement.walkSpeed;
                     break;
                  case 7:
                     var13 = (int)Math.round(Math.random() * (Movement.pedestrianSpeedMax - Movement.pedestrianSpeedMin) + Movement.pedestrianSpeedMin);
                     break;
                  case 8:
                     var13 = (int)Math.round(Math.random() * (Movement.vehicleSpeedMax - Movement.vehicleSpeedMin) + Movement.vehicleSpeedMin);
               }
            }

            Type var14 = Type.Line;
            if (var7.has("type")) {
               var14 = Type.valueOf(var7.getString("type"));
            }

            int var15 = Movement.defaultRadius;
            if (var7.has("radius")) {
               var15 = var7.getInt("radius");
            }

            IsoDirections var16 = IsoDirections.fromIndex((int)Math.round(Math.random() * 7.0));
            if (var7.has("direction")) {
               var16 = IsoDirections.valueOf(var7.getString("direction"));
            }

            boolean var17 = false;
            if (var7.has("ghost")) {
               var17 = var7.getBoolean("ghost");
            }

            long var18 = var51 * Client.connectionInterval;
            if (var7.has("connect")) {
               var18 = var7.getLong("connect");
            }

            long var20 = 0L;
            if (var7.has("disconnect")) {
               var20 = var7.getLong("disconnect");
            }

            long var22 = 0L;
            if (var7.has("reconnect")) {
               var22 = var7.getLong("reconnect");
            }

            long var24 = 0L;
            if (var7.has("teleport")) {
               var24 = var7.getLong("teleport");
            }

            int var26 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
            int var27 = (int)Math.round(Math.random() * 6000.0 + 6000.0);
            if (var7.has("destination")) {
               JSONObject var28 = var7.getJSONObject("destination");
               var26 = var28.getInt("x");
               var27 = var28.getInt("y");
            }

            HordeCreator var55 = null;
            if (var7.has("createHorde")) {
               JSONObject var29 = var7.getJSONObject("createHorde");
               int var30 = var29.getInt("count");
               int var31 = var29.getInt("radius");
               long var32 = var29.getLong("interval");
               if (var32 != 0L) {
                  var55 = new HordeCreator(var31, var30, var32);
               }
            }

            SoundMaker var56 = null;
            if (var7.has("makeSound")) {
               JSONObject var57 = var7.getJSONObject("makeSound");
               int var59 = var57.getInt("interval");
               int var60 = var57.getInt("radius");
               String var33 = var57.getString("message");
               if (var59 != 0) {
                  var56 = new SoundMaker(var59, var60, var33);
               }
            }

            Movement var58 = new Movement(
               var51, var52, var53, var11, var54, var13, var14, var15, var26, var27, var16, var17, var18, var20, var22, var24, var55, var56
            );
            if (var1.containsKey(var51)) {
               error(var51, String.format("Client %d already exists", var58.id));
            } else {
               var1.put(var51, var58);
            }
         }

         return var1;
      } catch (Exception var37) {
         error(-1, "Scenarios file load failed");
         var37.printStackTrace();
         return var1;
      } finally {
         ;
      }
   }

   private static void error(int var0, String var1) {
      System.out.print(String.format("%5s : %s , [%2d] > %s\n", "ERROR", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
   }

   private static void info(int var0, String var1) {
      if (logLevel >= 0) {
         System.out.print(String.format("%5s : %s , [%2d] > %s\n", "INFO", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

   private static void log(int var0, String var1) {
      if (logLevel >= 1) {
         System.out.print(String.format("%5s : %s , [%2d] > %s\n", "LOG", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

   private static void trace(int var0, String var1) {
      if (logLevel >= 2) {
         System.out.print(String.format("%5s : %s , [%2d] > %s\n", "TRACE", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

   public static boolean isVOIPEnabled() {
      return Player.isVOIPEnabled && getOnlineID() != -1L && getConnectedGUID() != -1L;
   }

   public static long getConnectedGUID() {
      return players.isEmpty() ? -1L : players.iterator().next().client.connectionGUID;
   }

   public static long getOnlineID() {
      return players.isEmpty() ? -1L : players.iterator().next().OnlineID;
   }

   public static void main(String[] var0) {
      String var1 = null;
      int var2 = -1;

      for (int var3 = 0; var3 < var0.length; var3++) {
         if (var0[var3].startsWith("-scenarios=")) {
            var1 = var0[var3].replace("-scenarios=", "").trim();
         } else if (var0[var3].startsWith("-id=")) {
            var2 = Integer.parseInt(var0[var3].replace("-id=", "").trim());
         }
      }

      if (var1 == null || var1.isBlank()) {
         error(-1, "Invalid scenarios file name");
         System.exit(0);
      }

      Rand.init();
      System.loadLibrary("RakNet64");
      System.loadLibrary("ZNetNoSteam64");

      try {
         String var10 = System.getProperty("zomboid.znetlog");
         if (var10 != null) {
            logLevel = Integer.parseInt(var10);
            ZNet.init();
            ZNet.SetLogLevel(logLevel);
         }
      } catch (NumberFormatException var9) {
         error(-1, "Invalid log arguments");
      }

      DebugLog.setLogEnabled(DebugType.General, false);
      HashMap var11 = load(var1);
      if (Player.isVOIPEnabled) {
         FMODManager.instance.init();
         VoiceManager.instance.InitVMClient();
         VoiceManager.instance.setMode(1);
      }

      Network var4;
      int var5;
      if (var2 != -1) {
         var5 = 17500 + var2;
         var4 = new Network(var11.size(), var5);
      } else {
         var5 = 17500;
         var4 = new Network(var11.size(), var5);
      }

      if (var4.isStarted()) {
         int var6 = 0;
         if (var2 != -1) {
            Movement var12 = (Movement)var11.get(var2);
            if (var12 != null) {
               players.add(new Player(var12, var4, var6, var5));
            } else {
               error(var2, "Client movement not found");
            }
         } else {
            for (Movement var8 : var11.values()) {
               players.add(new Player(var8, var4, var6++, var5));
            }
         }

         while (!players.isEmpty()) {
            sleep(1000L);
         }
      }
   }
}
