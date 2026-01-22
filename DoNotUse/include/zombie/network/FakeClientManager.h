#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/FMODManager.h"
#include "java/text/DateFormat.h"
#include "java/text/SimpleDateFormat.h"
#include <boost/json.hpp>
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/raknet/VoiceManager.h"
#include "zombie/core/znet/ZNet.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/network/FakeClientManager/1.h"
#include "zombie/network/FakeClientManager/Client.h"
#include "zombie/network/FakeClientManager/HordeCreator.h"
#include "zombie/network/FakeClientManager/Movement.h"
#include "zombie/network/FakeClientManager/Movement/Motion.h"
#include "zombie/network/FakeClientManager/Movement/Type.h"
#include "zombie/network/FakeClientManager/Network.h"
#include "zombie/network/FakeClientManager/Player.h"
#include "zombie/network/FakeClientManager/SoundMaker.h"
#include "zombie/network/FakeClientManager/StringUTF.h"
#include "zombie/network/FakeClientManager/ZombieSimulator.h"
#include "zombie/network/FakeClientManager/ZombieSimulator/Behaviour.h"
#include <algorithm>
#include <filesystem>

namespace zombie {
namespace network {


class FakeClientManager {
public:
    static const int SERVER_PORT = 16261;
    static const int CLIENT_PORT = 17500;
    static const std::string CLIENT_ADDRESS = "0.0.0.0";
    static const std::string versionNumber = Core.getInstance().getVersion();
    static const DateFormat logDateFormat = std::make_shared<SimpleDateFormat>("HH:mm:ss.SSS");
   private static const ThreadLocal<StringUTF> stringUTF = ThreadLocal.withInitial(StringUTF::new);
    static int logLevel = 0;
    static long startTime = System.currentTimeMillis();
   private static const std::unordered_set<Player> players = std::make_unique<std::unordered_set<>>();

    static std::string ReadStringUTF(ByteBuffer var0) {
      return stringUTF.get().load(var0);
   }

    static void WriteStringUTF(ByteBuffer var0, const std::string& var1) {
      stringUTF.get().save(var0, var1);
   }

    static void sleep(long var0) {
      try {
         Thread.sleep(var0);
      } catch (InterruptedException var3) {
         var3.printStackTrace();
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
   private static std::unordered_map<int, Movement> load(std::string var0) {
    std::unordered_map var1 = new std::unordered_map();

      try {
    std::string var2 = new std::string(Files.readAllBytes(Paths.get(var0)));
    JSONObject var3 = std::make_shared<JSONObject>(var2);
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
    std::string var52 = nullptr;
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

    bool var17 = false;
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

    HordeCreator var55 = nullptr;
            if (var7.has("createHorde")) {
    JSONObject var29 = var7.getJSONObject("createHorde");
    int var30 = var29.getInt("count");
    int var31 = var29.getInt("radius");
    long var32 = var29.getLong("interval");
               if (var32 != 0L) {
                  var55 = std::make_shared<HordeCreator>(var31, var30, var32);
               }
            }

    SoundMaker var56 = nullptr;
            if (var7.has("makeSound")) {
    JSONObject var57 = var7.getJSONObject("makeSound");
    int var59 = var57.getInt("interval");
    int var60 = var57.getInt("radius");
    std::string var33 = var57.getString("message");
               if (var59 != 0) {
                  var56 = std::make_shared<SoundMaker>(var59, var60, var33);
               }
            }

            Movement var58 = std::make_shared<Movement>(
               var51, var52, var53, var11, var54, var13, var14, var15, var26, var27, var16, var17, var18, var20, var22, var24, var55, var56
            );
            if (var1.containsKey(var51)) {
               error(var51, std::string.format("Client %d already exists", var58.id));
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

    static void error(int var0, const std::string& var1) {
      System.out.print(std::string.format("%5s : %s , [%2d] > %s\n", "ERROR", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
   }

    static void info(int var0, const std::string& var1) {
      if (logLevel >= 0) {
         System.out.print(std::string.format("%5s : %s , [%2d] > %s\n", "INFO", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

    static void log(int var0, const std::string& var1) {
      if (logLevel >= 1) {
         System.out.print(std::string.format("%5s : %s , [%2d] > %s\n", "LOG", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

    static void trace(int var0, const std::string& var1) {
      if (logLevel >= 2) {
         System.out.print(std::string.format("%5s : %s , [%2d] > %s\n", "TRACE", logDateFormat.format(Calendar.getInstance().getTime()), var0, var1));
      }
   }

    static bool isVOIPEnabled() {
      return Player.isVOIPEnabled && getOnlineID() != -1L && getConnectedGUID() != -1L;
   }

    static long getConnectedGUID() {
      return players.empty() ? -1L : players.iterator().next().client.connectionGUID;
   }

    static long getOnlineID() {
      return players.empty() ? -1L : players.iterator().next().OnlineID;
   }

    static void main(std::string[] var0) {
    std::string var1 = nullptr;
    int var2 = -1;

      for (int var3 = 0; var3 < var0.length; var3++) {
         if (var0[var3].startsWith("-scenarios=")) {
            var1 = var0[var3].replace("-scenarios=", "").trim();
         } else if (var0[var3].startsWith("-id=")) {
            var2 = int.parseInt(var0[var3].replace("-id=", "").trim());
         }
      }

      if (var1 == nullptr || var1.isBlank()) {
         error(-1, "Invalid scenarios file name");
         System.exit(0);
      }

      Rand.init();
      System.loadLibrary("RakNet64");
      System.loadLibrary("ZNetNoSteam64");

      try {
    std::string var10 = System.getProperty("zomboid.znetlog");
         if (var10 != nullptr) {
            logLevel = int.parseInt(var10);
            ZNet.init();
            ZNet.SetLogLevel(logLevel);
         }
      } catch (NumberFormatException var9) {
         error(-1, "Invalid log arguments");
      }

      DebugLog.setLogEnabled(DebugType.General, false);
    std::unordered_map var11 = load(var1);
      if (Player.isVOIPEnabled) {
         FMODManager.instance.init();
         VoiceManager.instance.InitVMClient();
         VoiceManager.instance.setMode(1);
      }

    Network var4;
    int var5;
      if (var2 != -1) {
         var5 = 17500 + var2;
         var4 = std::make_shared<Network>(var11.size(), var5);
      } else {
         var5 = 17500;
         var4 = std::make_shared<Network>(var11.size(), var5);
      }

      if (var4.isStarted()) {
    int var6 = 0;
         if (var2 != -1) {
    Movement var12 = (Movement)var11.get(var2);
            if (var12 != nullptr) {
               players.push_back(std::make_shared<Player>(var12, var4, var6, var5));
            } else {
               error(var2, "Client movement not found");
            }
         } else {
            for (Movement var8 : var11.values()) {
               players.push_back(std::make_shared<Player>(var8, var4, var6++, var5));
            }
         }

         while (!players.empty()) {
            sleep(1000L);
         }
      }
   }
}
} // namespace network
} // namespace zombie
