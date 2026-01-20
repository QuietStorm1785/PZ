#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/NumberFormat.h"
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/debug/DebugLog/OutputStreamWrapper.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace debug {


class DebugLog {
public:
   private static const boolean[] m_enabledDebugTypes = new boolean[DebugType.values().length];
   private static const std::unordered_map<DebugType, LogSeverity> logLevels = std::make_unique<std::unordered_map<>>();
    static bool s_initialized = false;
    static bool printServerTime = false;
    static const OutputStreamWrapper s_stdout = std::make_shared<OutputStreamWrapper>(System.out);
    static const OutputStreamWrapper s_stderr = std::make_shared<OutputStreamWrapper>(System.err);
    static const PrintStream m_originalOut = std::make_shared<PrintStream>(s_stdout, true);
    static const PrintStream m_originalErr = std::make_shared<PrintStream>(s_stderr, true);
    static const PrintStream GeneralErr = std::make_shared<DebugLogStream>(m_originalErr, m_originalErr, m_originalErr, std::make_shared<GeneralErrorDebugLogFormatter>());
    static ZLogger s_logFileLogger;
    static const DebugLogStream ActionSystem = createDebugLogStream(DebugType.ActionSystem);
    static const DebugLogStream Animation = createDebugLogStream(DebugType.Animation);
    static const DebugLogStream Asset = createDebugLogStream(DebugType.Asset);
    static const DebugLogStream Clothing = createDebugLogStream(DebugType.Clothing);
    static const DebugLogStream Combat = createDebugLogStream(DebugType.Combat);
    static const DebugLogStream Damage = createDebugLogStream(DebugType.Damage);
    static const DebugLogStream Death = createDebugLogStream(DebugType.Death);
    static const DebugLogStream FileIO = createDebugLogStream(DebugType.FileIO);
    static const DebugLogStream Fireplace = createDebugLogStream(DebugType.Fireplace);
    static const DebugLogStream General = createDebugLogStream(DebugType.General);
    static const DebugLogStream Input = createDebugLogStream(DebugType.Input);
    static const DebugLogStream IsoRegion = createDebugLogStream(DebugType.IsoRegion);
    static const DebugLogStream Lua = createDebugLogStream(DebugType.Lua);
    static const DebugLogStream MapLoading = createDebugLogStream(DebugType.MapLoading);
    static const DebugLogStream Mod = createDebugLogStream(DebugType.Mod);
    static const DebugLogStream Multiplayer = createDebugLogStream(DebugType.Multiplayer);
    static const DebugLogStream Network = createDebugLogStream(DebugType.Network);
    static const DebugLogStream NetworkFileDebug = createDebugLogStream(DebugType.NetworkFileDebug);
    static const DebugLogStream Packet = createDebugLogStream(DebugType.Packet);
    static const DebugLogStream Objects = createDebugLogStream(DebugType.Objects);
    static const DebugLogStream Radio = createDebugLogStream(DebugType.Radio);
    static const DebugLogStream Recipe = createDebugLogStream(DebugType.Recipe);
    static const DebugLogStream Script = createDebugLogStream(DebugType.Script);
    static const DebugLogStream Shader = createDebugLogStream(DebugType.Shader);
    static const DebugLogStream Sound = createDebugLogStream(DebugType.Sound);
    static const DebugLogStream Statistic = createDebugLogStream(DebugType.Statistic);
    static const DebugLogStream UnitTests = createDebugLogStream(DebugType.UnitTests);
    static const DebugLogStream Vehicle = createDebugLogStream(DebugType.Vehicle);
    static const DebugLogStream Voice = createDebugLogStream(DebugType.Voice);
    static const DebugLogStream Zombie = createDebugLogStream(DebugType.Zombie);
    static const int VERSION = 1;

    static DebugLogStream createDebugLogStream(DebugType var0) {
      return std::make_shared<DebugLogStream>(m_originalOut, m_originalOut, m_originalErr, std::make_shared<GenericDebugLogFormatter>(var0));
   }

    static void enableLog(DebugType var0, LogSeverity var1) {
      setLogEnabled(var0, true);
      logLevels.put(var0, var1);
   }

    static LogSeverity getLogLevel(DebugType var0) {
      return logLevels.get(var0);
   }

    static bool isLogEnabled(DebugType var0, LogSeverity var1) {
      return var1.ordinal() >= logLevels.getOrDefault(var0, LogSeverity.Warning).ordinal();
   }

    static bool isLogEnabled(LogSeverity var0, DebugType var1) {
      return var0.ordinal() >= LogSeverity.Warning.ordinal() || isEnabled(var1);
   }

    static std::string formatString(DebugType var0, LogSeverity var1, const std::string& var2, void* var3, const std::string& var4) {
    return isLogEnabled();
   }

    static std::string formatString(DebugType var0, LogSeverity var1, const std::string& var2, void* var3, const std::string& var4, void* var5) {
    return isLogEnabled();
   }

    static std::string formatString(DebugType var0, LogSeverity var1, const std::string& var2, void* var3, const std::string& var4, void* var5, void* var6) {
    return isLogEnabled();
   }

    static std::string formatString(DebugType var0, LogSeverity var1, const std::string& var2, void* var3, const std::string& var4, void* var5, void* var6, void* var7) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0, LogSeverity var1, std::string var2, Object var3, std::string var4, Object var5, Object var6, Object var7, Object var8
   ) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0, LogSeverity var1, std::string var2, Object var3, std::string var4, Object var5, Object var6, Object var7, Object var8, Object var9
   ) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0, LogSeverity var1, std::string var2, Object var3, std::string var4, Object var5, Object var6, Object var7, Object var8, Object var9, Object var10
   ) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0,
      LogSeverity var1,
      std::string var2,
      Object var3,
      std::string var4,
      Object var5,
      Object var6,
      Object var7,
      Object var8,
      Object var9,
      Object var10,
      Object var11
   ) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0,
      LogSeverity var1,
      std::string var2,
      Object var3,
      std::string var4,
      Object var5,
      Object var6,
      Object var7,
      Object var8,
      Object var9,
      Object var10,
      Object var11,
      Object var12
   ) {
    return isLogEnabled();
   }

   public static std::string formatString(
      DebugType var0,
      LogSeverity var1,
      std::string var2,
      Object var3,
      std::string var4,
      Object var5,
      Object var6,
      Object var7,
      Object var8,
      Object var9,
      Object var10,
      Object var11,
      Object var12,
      Object var13
   ) {
    return isLogEnabled();
   }

    static std::string formatStringVarArgs(DebugType var0, LogSeverity var1, const std::string& var2, void* var3, const std::string& var4, Object... var5) {
      if (!isLogEnabled(var1, var0)) {
    return nullptr;
      } else {
    std::string var6 = std::string.valueOf(System.currentTimeMillis());
         if (GameServer.bServer || GameClient.bClient || printServerTime) {
            var6 = var6 + "> " + NumberFormat.getNumberInstance().format(TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()));
         }

    std::string var7 = var2 + StringUtils.leftJustify(var0, 12) + ", " + var6 + "> " + var3 + std::string.format(var4, var5);
         echoToLogFile(var7);
    return var7;
      }
   }

    static void echoToLogFile(const std::string& var0) {
      if (s_logFileLogger == nullptr) {
         if (s_initialized) {
            return;
         }

         s_logFileLogger = std::make_shared<ZLogger>(GameServer.bServer ? "DebugLog-server" : "DebugLog", false);
      }

      try {
         s_logFileLogger.writeUnsafe(var0, nullptr, false);
      } catch (Exception var2) {
         m_originalErr.println("Exception thrown writing to log file.");
         m_originalErr.println(var2);
         var2.printStackTrace(m_originalErr);
      }
   }

    static bool isEnabled(DebugType var0) {
      return m_enabledDebugTypes[var0.ordinal()];
   }

    static void log(DebugType var0, const std::string& var1) {
    std::string var2 = formatString(var0, LogSeverity.General, "LOG  : ", "", "%s", var1);
      if (var2 != nullptr) {
         m_originalOut.println(var2);
      }
   }

    static void setLogEnabled(DebugType var0, bool var1) {
      m_enabledDebugTypes[var0.ordinal()] = var1;
   }

    static void log(void* var0) {
      log(DebugType.General, std::string.valueOf(var0));
   }

    static void log(const std::string& var0) {
      log(DebugType.General, var0);
   }

   public static std::vector<DebugType> getDebugTypes() {
    std::vector var0 = new std::vector<>(Arrays.asList(DebugType.values()));
      var0.sort((var0x, var1) -> std::string.CASE_INSENSITIVE_ORDER.compare(var0x.name(), var1.name()));
    return var0;
   }

    static void save() {
    std::vector var0 = new std::vector();

      for (DebugType var4 : DebugType.values()) {
    BooleanConfigOption var5 = std::make_shared<BooleanConfigOption>(var4.name(), false);
         var5.setValue(isEnabled(var4));
         var0.push_back(var5);
      }

    std::string var6 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debuglog.ini";
    ConfigFile var7 = std::make_shared<ConfigFile>();
      var7.write(var6, 1, var0);
   }

    static void load() {
    std::string var0 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debuglog.ini";
    ConfigFile var1 = std::make_shared<ConfigFile>();
      if (var1.read(var0)) {
         for (int var2 = 0; var2 < var1.getOptions().size(); var2++) {
    ConfigOption var3 = (ConfigOption)var1.getOptions().get(var2);

            try {
               setLogEnabled(DebugType.valueOf(var3.getName()), StringUtils.tryParseBoolean(var3.getValueAsString()));
            } catch (Exception var5) {
            }
         }
      }
   }

    static void setStdOut(OutputStream var0) {
      s_stdout.setStream(var0);
   }

    static void setStdErr(OutputStream var0) {
      s_stderr.setStream(var0);
   }

    static void init() {
      if (!s_initialized) {
         s_initialized = true;
         setStdOut(System.out);
         setStdErr(System.err);
         System.setOut(General);
         System.setErr(GeneralErr);
         if (!GameServer.bServer) {
            load();
         }

         s_logFileLogger = LoggerManager.getLogger(GameServer.bServer ? "DebugLog-server" : "DebugLog");
      }
   }

   static {
      enableLog(DebugType.Checksum, LogSeverity.Debug);
      enableLog(DebugType.Combat, LogSeverity.Debug);
      enableLog(DebugType.General, LogSeverity.Debug);
      enableLog(DebugType.IsoRegion, LogSeverity.Debug);
      enableLog(DebugType.Lua, LogSeverity.Debug);
      enableLog(DebugType.Mod, LogSeverity.Debug);
      enableLog(DebugType.Multiplayer, LogSeverity.Debug);
      enableLog(DebugType.Network, LogSeverity.Debug);
      enableLog(DebugType.Vehicle, LogSeverity.Debug);
      enableLog(DebugType.Voice, LogSeverity.Debug);
      if (GameServer.bServer) {
         enableLog(DebugType.Damage, LogSeverity.Debug);
         enableLog(DebugType.Death, LogSeverity.Debug);
         enableLog(DebugType.Statistic, LogSeverity.Debug);
      }
   }
}
} // namespace debug
} // namespace zombie
