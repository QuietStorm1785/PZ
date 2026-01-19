#pragma once
#include "java/text/SimpleDateFormat.h"
#include "zombie/debug/DebugLog.h"
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
namespace core {
namespace logger {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class ZLogger {
public:
 const std::string name;
private
 ZLogger.OutputStreams outputStreams = new ZLogger.OutputStreams();
 File file = nullptr;
 static const SimpleDateFormat s_fileNameSdf =
 new SimpleDateFormat("dd-MM-yy_HH-mm-ss");
 static const SimpleDateFormat s_logSdf =
 new SimpleDateFormat("dd-MM-yy HH:mm:ss.SSS");
 static const long s_maxSizeKo = 10000L;

 /**
 * Write logs into file and console.
 *
 * @param _name filename
 * @param useConsole if true then write logs into console also
 */
public
 ZLogger(std::string_view _name, bool useConsole) {
 this->name = _name;

 try {
 this->file = new File(LoggerManager.getLogsDir() + File.separator +
 getLoggerName(_name) + ".txt");
 this->outputStreams.file = new PrintStream(this->file);
 } catch (FileNotFoundException fileNotFoundException) {
 fileNotFoundException.printStackTrace();
 }

 if (useConsole) {
 this->outputStreams.console = System.out;
 }
 }

 static std::string getLoggerName(std::string_view string) {
 return s_fileNameSdf.format(Calendar.getInstance().getTime()) + "_" +
 string;
 }

 void write(std::string_view logs) { this->write(logs, nullptr); }

 void write(std::string_view logs, std::string_view level) {
 this->write(logs, level, false);
 }

 void write(std::string_view string0, std::string_view string1,
 bool boolean0) {
 try {
 this->writeUnsafe(string0, string1, boolean0);
 } catch (Exception exception) {
 exception.printStackTrace();
 }
 }

public
 void writeUnsafe(String string1, String string0,
 boolean boolean0) throws Exception {
 StringBuilder stringBuilder = new StringBuilder();
 stringBuilder.setLength(0);
 if (!boolean0) {
 stringBuilder.append("[")
 .append(s_logSdf.format(Calendar.getInstance().getTime()))
 .append("]");
 }

 if (!StringUtils.isNullOrEmpty(string0) {
 stringBuilder.append("[").append(string0).append("]");
 }

 int int0 = string1.length();
 if (string1.lastIndexOf(10) == string1.length() - 1) {
 int0--;
 }

 if (!boolean0) {
 stringBuilder.append(" ").append(string1, 0, int0).append(".");
 } else {
 stringBuilder.append(string1, 0, int0);
 }

 this->outputStreams.println(stringBuilder.toString());
 this->checkSizeUnsafe();
 }

public
 void write(Exception ex) {
 ex.printStackTrace(this->outputStreams.file);
 this->checkSize();
 }

private
 void checkSize() noexcept{
 try {
 this->checkSizeUnsafe();
 } catch (Exception exception) {
 DebugLog.General.error("Exception thrown checking log file size.");
 DebugLog.General.error(exception);
 exception.printStackTrace();
 }
 }

private
 void checkSizeUnsafe() throws Exception {
 long long0 = this->file.length() / 1024L;
 if (long0 > 10000L) {
 this->outputStreams.file.close();
 this->file = new File(LoggerManager.getLogsDir() + File.separator +
 getLoggerName(this->name) + ".txt");
 this->outputStreams.file = new PrintStream(this->file);
 }
 }

private
 static class OutputStreams {
 PrintStream file;
 PrintStream console;

 void println(std::string_view arg0) {
 if (this->file != nullptr) {
 this->file.println(arg0);
 this->file.flush();
 }

 if (this->console != nullptr) {
 this->console.println(arg0);
 }
 }
 }
}
} // namespace logger
} // namespace core
} // namespace zombie
