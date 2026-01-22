#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/debug/DebugLogStream/1.h"
#include "zombie/util/StringUtils.h"
#include <fstream>
#include <iostream>

namespace zombie {
namespace debug {


class DebugLogStream : public PrintStream {
public:
    const PrintStream m_wrappedStream;
    const PrintStream m_wrappedWarnStream;
    const PrintStream m_wrappedErrStream;
    const IDebugLogFormatter m_formatter;
    static const std::string s_prefixErr = "ERROR: ";
    static const std::string s_prefixWarn = "WARN : ";
    static const std::string s_prefixOut = "LOG  : ";
    static const std::string s_prefixDebug = "DEBUG: ";
    static const std::string s_prefixTrace = "TRACE: ";

    public DebugLogStream(PrintStream var1, PrintStream var2, PrintStream var3, IDebugLogFormatter var4) {
      super(var1);
      this.m_wrappedStream = var1;
      this.m_wrappedWarnStream = var2;
      this.m_wrappedErrStream = var3;
      this.m_formatter = var4;
   }

    void write(PrintStream var1, const std::string& var2) {
    std::string var3 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var2);
      if (var3 != nullptr) {
         var1.print(var3);
      }
   }

    void writeln(PrintStream var1, const std::string& var2) {
      this.writeln(var1, LogSeverity.General, "LOG  : ", var2);
   }

    void writeln(PrintStream var1, const std::string& var2, void* var3) {
      this.writeln(var1, LogSeverity.General, "LOG  : ", var2, var3);
   }

    void writeln(PrintStream var1, LogSeverity var2, const std::string& var3, const std::string& var4) {
    std::string var5 = this.m_formatter.format(var2, var3, "", var4);
      if (var5 != nullptr) {
         var1.println(var5);
      }
   }

    void writeln(PrintStream var1, LogSeverity var2, const std::string& var3, const std::string& var4, void* var5) {
    std::string var6 = this.m_formatter.format(var2, var3, "", var4, var5);
      if (var6 != nullptr) {
         var1.println(var6);
      }
   }

    static std::string generateCallerPrefix() {
    StackTraceElement var0 = tryGetCallerTraceElement(4);
    return var0 = = nullptr ? "(UnknownStack)" : getStackTraceElementString(var0, false);
   }

    static StackTraceElement tryGetCallerTraceElement(int var0) {
      StackTraceElement[] var1 = Thread.currentThread().getStackTrace();
      return var1.length <= var0 ? nullptr : var1[var0];
   }

    static std::string getStackTraceElementString(StackTraceElement var0, bool var1) {
      if (var0 == nullptr) {
         return "(UnknownStack)";
      } else {
    std::string var2 = getUnqualifiedClassName(var0.getClassName());
    std::string var3 = var0.getMethodName();
    int var4 = var0.getLineNumber();
    std::string var5;
         if (var0.isNativeMethod()) {
            var5 = " (Native Method)";
         } else if (var1 && var4 > -1) {
            var5 = " line:" + var4;
         } else {
            var5 = "";
         }

         return var2 + "." + var3 + var5;
      }
   }

    static std::string getTopStackTraceString(std::exception var0) {
      if (var0 == nullptr) {
         return "Null Exception";
      } else {
         StackTraceElement[] var1 = var0.getStackTrace();
         if (var1 != nullptr && var1.length != 0) {
    StackTraceElement var2 = var1[0];
    return getStackTraceElementString();
         } else {
            return "No std::stack Trace Available";
         }
      }
   }

    void printStackTrace() {
      this.printStackTrace(0, nullptr);
   }

    void printStackTrace(const std::string& var1) {
      this.printStackTrace(0, var1);
   }

    void printStackTrace(int var1, const std::string& var2) {
      if (var2 != nullptr) {
         this.println(var2);
      }

      StackTraceElement[] var3 = Thread.currentThread().getStackTrace();
    int var4 = var1 == 0 ? var3.length : Math.min(var1, var3.length);

      for (int var5 = 0; var5 < var4; var5++) {
    StackTraceElement var6 = var3[var5];
         this.println("\t" + var6);
      }
   }

    static std::string getUnqualifiedClassName(const std::string& var0) {
    std::string var1 = var0;
    int var2 = var0.lastIndexOf(46);
      if (var2 > -1 && var2 < var0.length() - 1) {
         var1 = var0.substr(var2 + 1);
      }

    return var1;
   }

    void debugln(const std::string& var1) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var2 = generateCallerPrefix();
    std::string var3 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var2, 36) + "> ", "%s", var1);
         this.m_wrappedStream.println(var3);
      }
   }

    void debugln(const std::string& var1, void* var2) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var3 = generateCallerPrefix();
    std::string var4 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var3, 36) + "> ", var1, var2);
         this.m_wrappedStream.println(var4);
      }
   }

    void debugln(const std::string& var1, void* var2, void* var3) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var4 = generateCallerPrefix();
    std::string var5 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var4, 36) + "> ", var1, var2, var3);
         this.m_wrappedStream.println(var5);
      }
   }

    void debugln(const std::string& var1, void* var2, void* var3, void* var4) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var5 = generateCallerPrefix();
    std::string var6 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var5, 36) + "> ", var1, var2, var3, var4);
         this.m_wrappedStream.println(var6);
      }
   }

    void debugln(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var6 = generateCallerPrefix();
    std::string var7 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var6, 36) + "> ", var1, var2, var3, var4, var5);
         this.m_wrappedStream.println(var7);
      }
   }

    void debugln(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var7 = generateCallerPrefix();
    std::string var8 = this.m_formatter.format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var7, 36) + "> ", var1, var2, var3, var4, var5, var6);
         this.m_wrappedStream.println(var8);
      }
   }

    void debugln(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
      if (this.m_formatter.isLogEnabled(LogSeverity.General)) {
    std::string var8 = generateCallerPrefix();
         std::string var9 = this.m_formatter
            .format(LogSeverity.General, "DEBUG: ", StringUtils.leftJustify(var8, 36) + "> ", var1, var2, var3, var4, var5, var6, var7);
         this.m_wrappedStream.println(var9);
      }
   }

    void print(bool var1) {
      this.write(this.m_wrappedStream, var1 ? "true" : "false");
   }

    void print(char var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(int var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(long var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(float var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(double var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(const std::string& var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    void print(void* var1) {
      this.write(this.m_wrappedStream, std::string.valueOf(var1));
   }

    PrintStream printf(const std::string& var1, Object... var2) {
      this.write(this.m_wrappedStream, std::string.format(var1, var2));
    return this;
   }

    void println() {
      this.writeln(this.m_wrappedStream, "");
   }

    void println(bool var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(char var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(int var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(long var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(float var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(double var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(char[] var1) {
      this.writeln(this.m_wrappedStream, "%s", std::string.valueOf(var1));
   }

    void println(const std::string& var1) {
      this.writeln(this.m_wrappedStream, "%s", var1);
   }

    void println(void* var1) {
      this.writeln(this.m_wrappedStream, "%s", var1);
   }

    void println(const std::string& var1, void* var2) {
    std::string var3 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2);
      if (var3 != nullptr) {
         this.m_wrappedStream.println(var3);
      }
   }

    void println(const std::string& var1, void* var2, void* var3) {
    std::string var4 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3);
      if (var4 != nullptr) {
         this.m_wrappedStream.println(var4);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4) {
    std::string var5 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4);
      if (var5 != nullptr) {
         this.m_wrappedStream.println(var5);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
    std::string var6 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5);
      if (var6 != nullptr) {
         this.m_wrappedStream.println(var6);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
    std::string var7 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5, var6);
      if (var7 != nullptr) {
         this.m_wrappedStream.println(var7);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
    std::string var8 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5, var6, var7);
      if (var8 != nullptr) {
         this.m_wrappedStream.println(var8);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7, void* var8) {
    std::string var9 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5, var6, var7, var8);
      if (var9 != nullptr) {
         this.m_wrappedStream.println(var9);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7, void* var8, void* var9) {
    std::string var10 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5, var6, var7, var8, var9);
      if (var10 != nullptr) {
         this.m_wrappedStream.println(var10);
      }
   }

    void println(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7, void* var8, void* var9, void* var10) {
    std::string var11 = this.m_formatter.format(LogSeverity.General, "LOG  : ", "", var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
      if (var11 != nullptr) {
         this.m_wrappedStream.println(var11);
      }
   }

    void error(void* var1) {
      this.writeln(this.m_wrappedErrStream, LogSeverity.Error, "ERROR: ", generateCallerPrefix() + "> " + var1);
   }

    void error(const std::string& var1, Object... var2) {
      this.writeln(this.m_wrappedErrStream, LogSeverity.Error, "ERROR: ", generateCallerPrefix() + "> " + std::string.format(var1, var2));
   }

    void warn(void* var1) {
      this.writeln(this.m_wrappedWarnStream, LogSeverity.Warning, "WARN : ", generateCallerPrefix() + "> " + var1);
   }

    void warn(const std::string& var1, Object... var2) {
      this.writeln(this.m_wrappedWarnStream, LogSeverity.Warning, "WARN : ", generateCallerPrefix() + "> " + std::string.format(var1, var2));
   }

    void printUnitTest(const std::string& var1, bool var2, Object... var3) {
      if (!var2) {
         this.error(var1 + ", fail", var3);
      } else {
         this.println(var1 + ", pass", var3);
      }
   }

    void printException(std::exception var1, const std::string& var2, LogSeverity var3) {
      this.printException(var1, var2, generateCallerPrefix(), var3);
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    void printException(std::exception var1, const std::string& var2, const std::string& var3, LogSeverity var4) {
      if (var1 == nullptr) {
         this.warn("Null exception passed.");
      } else {
    std::string var5;
    PrintStream var6;
    bool var7;
         switch (1.$SwitchMap$zombie$debug$LogSeverity[var4.ordinal()]) {
            case 1:
            case 2:
               var5 = "LOG  : ";
               var6 = this.m_wrappedStream;
               var7 = false;
               break;
            case 3:
               var5 = "WARN : ";
               var6 = this.m_wrappedWarnStream;
               var7 = false;
               break;
            default:
               this.error("Unhandled LogSeverity: %s. Defaulted to Error.", std::string.valueOf(var4));
            case 4:
               var5 = "ERROR: ";
               var6 = this.m_wrappedErrStream;
               var7 = true;
         }

         if (var2 != nullptr) {
            this.writeln(
               var6, var4, var5, std::string.format("%s> Exception thrown %s at %s. Message: %s", var3, var1, getTopStackTraceString(var1), var2)
            );
         } else {
            this.writeln(var6, var4, var5, std::string.format("%s> Exception thrown %s at %s.", var3, var1, getTopStackTraceString(var1)));
         }

         if (var7) {
            this.error("std::stack trace:");
            var1.printStackTrace(var6);
         }
      }
   }

    void noise(const std::string& var1) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var2 = generateCallerPrefix();
    std::string var3 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var2, 36) + "> ", "%s", var1);
         if (var3 != nullptr) {
            this.m_wrappedStream.println(var3);
         }
      }
   }

    void noise(const std::string& var1, void* var2) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var3 = generateCallerPrefix();
    std::string var4 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var3, 36) + "> ", var1, var2);
         if (var4 != nullptr) {
            this.m_wrappedStream.println(var4);
         }
      }
   }

    void noise(const std::string& var1, void* var2, void* var3) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var4 = generateCallerPrefix();
    std::string var5 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var4, 36) + "> ", var1, var2, var3);
         if (var5 != nullptr) {
            this.m_wrappedStream.println(var5);
         }
      }
   }

    void noise(const std::string& var1, void* var2, void* var3, void* var4) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var5 = generateCallerPrefix();
    std::string var6 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var5, 36) + "> ", var1, var2, var3, var4);
         if (var6 != nullptr) {
            this.m_wrappedStream.println(var6);
         }
      }
   }

    void noise(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var6 = generateCallerPrefix();
    std::string var7 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var6, 36) + "> ", var1, var2, var3, var4, var5);
         if (var7 != nullptr) {
            this.m_wrappedStream.println(var7);
         }
      }
   }

    void noise(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var7 = generateCallerPrefix();
    std::string var8 = this.m_formatter.format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var7, 36) + "> ", var1, var2, var3, var4, var5, var6);
         if (var8 != nullptr) {
            this.m_wrappedStream.println(var8);
         }
      }
   }

    void noise(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
      if (Core.bDebug && this.m_formatter.isLogSeverityEnabled(LogSeverity.Debug)) {
    std::string var8 = generateCallerPrefix();
         std::string var9 = this.m_formatter
            .format(LogSeverity.Debug, "DEBUG: ", StringUtils.leftJustify(var8, 36) + "> ", var1, var2, var3, var4, var5, var6, var7);
         if (var9 != nullptr) {
            this.m_wrappedStream.println(var9);
         }
      }
   }

    void trace(const std::string& var1) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var2 = generateCallerPrefix();
    std::string var3 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var2, 36) + "> ", "%s", var1);
         if (var3 != nullptr) {
            this.m_wrappedStream.println(var3);
         }
      }
   }

    void trace(const std::string& var1, void* var2) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var3 = generateCallerPrefix();
    std::string var4 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var3, 36) + "> ", var1, var2);
         if (var4 != nullptr) {
            this.m_wrappedStream.println(var4);
         }
      }
   }

    void trace(const std::string& var1, void* var2, void* var3) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var4 = generateCallerPrefix();
    std::string var5 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var4, 36) + "> ", var1, var2, var3);
         if (var5 != nullptr) {
            this.m_wrappedStream.println(var5);
         }
      }
   }

    void trace(const std::string& var1, void* var2, void* var3, void* var4) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var5 = generateCallerPrefix();
    std::string var6 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var5, 36) + "> ", var1, var2, var3, var4);
         if (var6 != nullptr) {
            this.m_wrappedStream.println(var6);
         }
      }
   }

    void trace(const std::string& var1, void* var2, void* var3, void* var4, void* var5) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var6 = generateCallerPrefix();
    std::string var7 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var6, 36) + "> ", var1, var2, var3, var4, var5);
         if (var7 != nullptr) {
            this.m_wrappedStream.println(var7);
         }
      }
   }

    void trace(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var7 = generateCallerPrefix();
    std::string var8 = this.m_formatter.format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var7, 36) + "> ", var1, var2, var3, var4, var5, var6);
         if (var8 != nullptr) {
            this.m_wrappedStream.println(var8);
         }
      }
   }

    void trace(const std::string& var1, void* var2, void* var3, void* var4, void* var5, void* var6, void* var7) {
      if (this.m_formatter.isLogSeverityEnabled(LogSeverity.Trace)) {
    std::string var8 = generateCallerPrefix();
         std::string var9 = this.m_formatter
            .format(LogSeverity.Trace, "TRACE: ", StringUtils.leftJustify(var8, 36) + "> ", var1, var2, var3, var4, var5, var6, var7);
         if (var9 != nullptr) {
            this.m_wrappedStream.println(var9);
         }
      }
   }
}
} // namespace debug
} // namespace zombie
