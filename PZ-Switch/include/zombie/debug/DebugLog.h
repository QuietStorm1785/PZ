#pragma once
#include "java/text/NumberFormat.h"
#include "zombie/GameTime.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Core.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/logger/ZLogger.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/UIDebugConsole.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace debug {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Created by LEMMYPC on 31/12/13.
 */
class DebugLog {
public:
private
 static boolean[] m_enabledDebugTypes =
 new boolean[DebugType.values().length];
private
 static HashMap<DebugType, LogSeverity> logLevels =
 std::make_unique<HashMap<>>();
 static bool s_initialized = false;
 static bool printServerTime = false;
private
 static DebugLog.OutputStreamWrapper s_stdout =
 new DebugLog.OutputStreamWrapper(System.out);
private
 static DebugLog.OutputStreamWrapper s_stderr =
 new DebugLog.OutputStreamWrapper(System.err);
 static const PrintStream m_originalOut = new PrintStream(s_stdout, true);
 static const PrintStream m_originalErr = new PrintStream(s_stderr, true);
 static const PrintStream GeneralErr =
 new DebugLogStream(m_originalErr, m_originalErr, m_originalErr,
 new GeneralErrorDebugLogFormatter());
 static ZLogger s_logFileLogger;
 static const DebugLogStream ActionSystem =
 createDebugLogStream(DebugType.ActionSystem);
 static const DebugLogStream Animation =
 createDebugLogStream(DebugType.Animation);
 static const DebugLogStream Asset = createDebugLogStream(DebugType.Asset);
 static const DebugLogStream Clothing =
 createDebugLogStream(DebugType.Clothing);
 static const DebugLogStream Combat = createDebugLogStream(DebugType.Combat);
 static const DebugLogStream Damage = createDebugLogStream(DebugType.Damage);
 static const DebugLogStream Death = createDebugLogStream(DebugType.Death);
 static const DebugLogStream FileIO = createDebugLogStream(DebugType.FileIO);
 static const DebugLogStream Fireplace =
 createDebugLogStream(DebugType.Fireplace);
 static const DebugLogStream General = createDebugLogStream(DebugType.General);
 static const DebugLogStream Input = createDebugLogStream(DebugType.Input);
 static const DebugLogStream IsoRegion =
 createDebugLogStream(DebugType.IsoRegion);
 static const DebugLogStream Lua = createDebugLogStream(DebugType.Lua);
 static const DebugLogStream MapLoading =
 createDebugLogStream(DebugType.MapLoading);
 static const DebugLogStream Mod = createDebugLogStream(DebugType.Mod);
 static const DebugLogStream Multiplayer =
 createDebugLogStream(DebugType.Multiplayer);
 static const DebugLogStream Network = createDebugLogStream(DebugType.Network);
 static const DebugLogStream NetworkFileDebug =
 createDebugLogStream(DebugType.NetworkFileDebug);
 static const DebugLogStream Packet = createDebugLogStream(DebugType.Packet);
 static const DebugLogStream Objects = createDebugLogStream(DebugType.Objects);
 static const DebugLogStream Radio = createDebugLogStream(DebugType.Radio);
 static const DebugLogStream Recipe = createDebugLogStream(DebugType.Recipe);
 static const DebugLogStream Script = createDebugLogStream(DebugType.Script);
 static const DebugLogStream Shader = createDebugLogStream(DebugType.Shader);
 static const DebugLogStream Sound = createDebugLogStream(DebugType.Sound);
 static const DebugLogStream Statistic =
 createDebugLogStream(DebugType.Statistic);
 static const DebugLogStream UnitTests =
 createDebugLogStream(DebugType.UnitTests);
 static const DebugLogStream Vehicle = createDebugLogStream(DebugType.Vehicle);
 static const DebugLogStream Voice = createDebugLogStream(DebugType.Voice);
 static const DebugLogStream Zombie = createDebugLogStream(DebugType.Zombie);
 static const int VERSION = 1;

 static DebugLogStream createDebugLogStream(DebugType debugType) {
 return new DebugLogStream(m_originalOut, m_originalOut, m_originalErr,
 new GenericDebugLogFormatter(debugType);
 }

 static void enableLog(DebugType type, LogSeverity severity) {
 setLogEnabled(type, true);
 logLevels.put(type, severity);
 }

 static LogSeverity getLogLevel(DebugType type) { return logLevels.get(type); }

 static bool isLogEnabled(DebugType type, LogSeverity logSeverity) {
 return logSeverity.ordinal() >=
 logLevels.getOrDefault(type, LogSeverity.Warning).ordinal();
 }

 static bool isLogEnabled(LogSeverity logSeverity, DebugType type) {
 return logSeverity.ordinal() >= LogSeverity.Warning.ordinal() ||
 isEnabled(type);
 }

 static std::string formatString(DebugType type, LogSeverity logSeverity,
 std::string_view prefix, void *affix,
 std::string_view formatNoParams) {
 return isLogEnabled();
 }

 static std::string formatString(DebugType type, LogSeverity logSeverity,
 std::string_view prefix, void *affix,
 std::string_view format, void *param0) {
 return isLogEnabled();
 }

 static std::string formatString(DebugType type, LogSeverity logSeverity,
 std::string_view prefix, void *affix,
 std::string_view format, void *param0,
 void *param1) {
 return isLogEnabled();
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2) {
 return isLogEnabled();
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3) {
 return isLogEnabled();
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3, Object param4) {
 return isLogEnabled();
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5) {
 return isLogEnabled();
 ? formatStringVarArgs(type, logSeverity, prefix, affix, format, param0,
 param1, param2, param3, param4, param5)
 : nullptr;
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5,
 Object param6) {
 return isLogEnabled();
 ? formatStringVarArgs(type, logSeverity, prefix, affix, format, param0,
 param1, param2, param3, param4, param5, param6)
 : nullptr;
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5,
 Object param6, Object param7) {
 return isLogEnabled();
 ? formatStringVarArgs(type, logSeverity, prefix, affix, format, param0,
 param1, param2, param3, param4, param5, param6,
 param7)
 : nullptr;
 }

public
 static String formatString(DebugType type, LogSeverity logSeverity,
 String prefix, Object affix, String format,
 Object param0, Object param1, Object param2,
 Object param3, Object param4, Object param5,
 Object param6, Object param7, Object param8) {
 return isLogEnabled();
 ? formatStringVarArgs(type, logSeverity, prefix, affix, format, param0,
 param1, param2, param3, param4, param5, param6,
 param7, param8)
 : nullptr;
 }

 static std::string formatStringVarArgs(DebugType type,
 LogSeverity logSeverity,
 std::string_view prefix, void *affix,
 std::string_view format,
 Object... params) {
 if (!isLogEnabled(logSeverity, type) {
 return nullptr;
 } else {
 std::string string0 = String.valueOf(System.currentTimeMillis());
 if (GameServer.bServer || GameClient.bClient || printServerTime) {
 string0 = string0 + "> " +
 NumberFormat.getNumberInstance().format(
 TimeUnit.NANOSECONDS.toMillis(GameTime.getServerTime()));
 }

 std::string string1 =
 prefix + StringUtils.leftJustify(type.toString(), 12) + ", " +
 string0 + "> " + affix + String.format(format, params);
 echoToLogFile(string1);
 return string1;
 }
 }

 static void echoToLogFile(std::string_view string) {
 if (s_logFileLogger.empty()) {
 if (s_initialized) {
 return;
 }

 s_logFileLogger = new ZLogger(
 GameServer.bServer ? "DebugLog-server" : "DebugLog", false);
 }

 try {
 s_logFileLogger.writeUnsafe(string, nullptr, false);
 } catch (Exception exception) {
 m_originalErr.println("Exception thrown writing to log file.");
 m_originalErr.println(exception);
 exception.printStackTrace(m_originalErr);
 }
 }

 static bool isEnabled(DebugType type) {
 return m_enabledDebugTypes[type.ordinal()];
 }

 static void log(DebugType type, std::string_view str) {
 std::string string =
 formatString(type, LogSeverity.General, "LOG : ", "", "%s", str);
 if (string != nullptr) {
 m_originalOut.println(string);
 }
 }

 static void setLogEnabled(DebugType type, bool bEnabled) {
 m_enabledDebugTypes[type.ordinal()] = bEnabled;
 }

 static void log(void *o) { log(DebugType.General, String.valueOf(o); }

 static void log(std::string_view str) { log(DebugType.General, str); }

public
 static ArrayList<DebugType> getDebugTypes() {
 std::vector arrayList = new ArrayList<>(Arrays.asList(DebugType.values()));
 arrayList.sort((debugType1, debugType0)
 ->String.CASE_INSENSITIVE_ORDER.compare(
 debugType1.name(), debugType0.name()));
 return arrayList;
 }

 static void save() {
 std::vector arrayList = new ArrayList();

 for (DebugType debugType : DebugType.values()) {
 BooleanConfigOption booleanConfigOption =
 new BooleanConfigOption(debugType.name(), false);
 booleanConfigOption.setValue(isEnabled(debugType);
 arrayList.add(booleanConfigOption);
 }

 std::string string = ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "debuglog.ini";
 ConfigFile configFile = new ConfigFile();
 configFile.write(string, 1, arrayList);
 }

 static void load() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() +
 File.separator + "debuglog.ini";
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 for (int int0 = 0; int0 < configFile.getOptions().size(); int0++) {
 ConfigOption configOption = configFile.getOptions().get(int0);

 try {
 setLogEnabled(
 DebugType.valueOf(configOption.getName()),
 StringUtils.tryParseBoolean(configOption.getValueAsString()));
 } catch (Exception exception) {
 }
 }
 }
 }

 static void setStdOut(OutputStream out) { s_stdout.setStream(out); }

 static void setStdErr(OutputStream out) { s_stderr.setStream(out); }

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

 s_logFileLogger = LoggerManager.getLogger(
 GameServer.bServer ? "DebugLog-server" : "DebugLog");
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

private
 static class OutputStreamWrapper extends FilterOutputStream {
 public
 OutputStreamWrapper(OutputStream arg0) { super(arg0); }

 void write(byte[] bytes, int int0, int int1) {
 this->out.write(bytes, int0, int1);
 if (Core.bDebug && UIDebugConsole.instance != nullptr &&
 DebugOptions.instance.UIDebugConsoleDebugLog.getValue()) {
 UIDebugConsole.instance.addOutput(bytes, int0, int1);
 }
 }

 void setStream(OutputStream arg0) { this->out = arg0; }
 }
}
} // namespace debug
} // namespace zombie
