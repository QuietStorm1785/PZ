#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/debug/DebugLog.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace logger {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class LoggerManager {
public:
 static bool s_isInitialized = false;
 private static HashMap<String, ZLogger> s_loggers = std::make_unique<HashMap<>>();

 public static synchronized ZLogger getLogger(String string) {
 if (!s_loggers.containsKey(string) {
 createLogger(string, false);
 }

 return s_loggers.get(string);
 }

 public static synchronized void init() {
 if (!s_isInitialized) {
 DebugLog.General.debugln("Initializing...");
 s_isInitialized = true;
 backupOldLogFiles();
 }
 }

 static void backupOldLogFiles() {
 try {
 File file0 = new File(getLogsDir());
 String[] strings = file0.list();
 if (strings == nullptr || strings.length == 0) {
 return;
 }

 Calendar calendar = getLogFileLastModifiedTime(strings[0]);
 std::string string = "logs_";
 if (calendar.get(5) < 9) {
 string = string + "0" + calendar.get(5);
 } else {
 string = string + calendar.get(5);
 }

 if (calendar.get(2) < 9) {
 string = string + "-0" + (calendar.get(2) + 1);
 } else {
 string = string + "-" + (calendar.get(2) + 1);
 }

 File file1 = new File(getLogsDir() + File.separator + string);
 if (!file1.exists()) {
 file1.mkdir();
 }

 for (int int0 = 0; int0 < strings.length; int0++) {
 string = strings[int0];
 File file2 = new File(getLogsDir() + File.separator + string);
 if (file2.isFile()) {
 file2.renameTo(new File(file1.getAbsolutePath() + File.separator + file2.getName()));
 file2.delete();
 }
 }
 } catch (Exception exception) {
 DebugLog.General.error("Exception thrown trying to initialize LoggerManager, trying to copy old log files.");
 DebugLog.General.error("Exception: ");
 DebugLog.General.error(exception);
 exception.printStackTrace();
 }
 }

 static Calendar getLogFileLastModifiedTime(const std::string& string) {
 File file = new File(getLogsDir() + File.separator + string);
 Calendar calendar = Calendar.getInstance();
 calendar.setTimeInMillis(file.lastModified());
 return calendar;
 }

 public static synchronized void createLogger(String string, boolean boolean0) {
 init();
 s_loggers.put(string, new ZLogger(string, boolean0);
 }

 static std::string getLogsDir() {
 std::string string = ZomboidFileSystem.instance.getCacheDirSub("Logs");
 ZomboidFileSystem.ensureFolderExists(string);
 File file = new File(string);
 return file.getAbsolutePath();
 }

 static std::string getPlayerCoords(IsoPlayer player) {
 return "(" + (int)player.getX() + "," + (int)player.getY() + "," + (int)player.getZ() + ")";
 }
}
} // namespace logger
} // namespace core
} // namespace zombie
