#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/text/SimpleDateFormat.h"
#include "zombie/core/logger/ZLogger/OutputStreams.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/StringUtils.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace zombie {
namespace core {
namespace logger {


class ZLogger {
public:
    const std::string name;
    const OutputStreams outputStreams = std::make_shared<OutputStreams>();
    File file = nullptr;
    static const SimpleDateFormat s_fileNameSdf = std::make_shared<SimpleDateFormat>("dd-MM-yy_HH-mm-ss");
    static const SimpleDateFormat s_logSdf = std::make_shared<SimpleDateFormat>("dd-MM-yy HH:mm:ss.SSS");
    static const long s_maxSizeKo = 10000L;

    public ZLogger(const std::string& var1, bool var2) {
      this.name = var1;

      try {
         this.file = std::make_shared<File>(LoggerManager.getLogsDir() + File.separator + getLoggerName(var1) + ".txt");
         this.outputStreams.file = std::make_shared<PrintStream>(this.file);
      } catch (FileNotFoundException var4) {
         var4.printStackTrace();
      }

      if (var2) {
         this.outputStreams.console = System.out;
      }
   }

    static std::string getLoggerName(const std::string& var0) {
      return s_fileNameSdf.format(Calendar.getInstance().getTime()) + "_" + var0;
   }

    void write(const std::string& var1) {
      this.write(var1, nullptr);
   }

    void write(const std::string& var1, const std::string& var2) {
      this.write(var1, var2, false);
   }

    void write(const std::string& var1, const std::string& var2, bool var3) {
      try {
         this.writeUnsafe(var1, var2, var3);
      } catch (Exception var5) {
         var5.printStackTrace();
      }
   }

   public /* synchronized - TODO: add std::mutex */ void writeUnsafe(std::string var1, std::string var2, boolean var3) throws Exception {
    std::stringstream var4 = new std::stringstream();
      var4.setLength(0);
      if (!var3) {
         var4.append("[").append(s_logSdf.format(Calendar.getInstance().getTime())).append("]");
      }

      if (!StringUtils.isNullOrEmpty(var2)) {
         var4.append("[").append(var2).append("]");
      }

    int var5 = var1.length();
      if (var1.lastIndexOf(10) == var1.length() - 1) {
         var5--;
      }

      if (!var3) {
         var4.append(" ").append(var1, 0, var5).append(".");
      } else {
         var4.append(var1, 0, var5);
      }

      this.outputStreams.println(var4);
      this.checkSizeUnsafe();
   }

   public /* synchronized - TODO: add std::mutex */ void write(Exception var1) {
      var1.printStackTrace(this.outputStreams.file);
      this.checkSize();
   }

   private /* synchronized - TODO: add std::mutex */ void checkSize() {
      try {
         this.checkSizeUnsafe();
      } catch (Exception var2) {
         DebugLog.General.error("Exception thrown checking log file size.");
         DebugLog.General.error(var2);
         var2.printStackTrace();
      }
   }

   private /* synchronized - TODO: add std::mutex */ void checkSizeUnsafe() throws Exception {
    long var1 = this.file.length() / 1024L;
      if (var1 > 10000L) {
         this.outputStreams.file.close();
         this.file = std::make_shared<File>(LoggerManager.getLogsDir() + File.separator + getLoggerName(this.name) + ".txt");
         this.outputStreams.file = std::make_shared<PrintStream>(this.file);
      }
   }
}
} // namespace logger
} // namespace core
} // namespace zombie
