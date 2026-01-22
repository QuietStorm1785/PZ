#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {

class GenericDebugLogFormatter {
public:
    const DebugType debugType;

    public GenericDebugLogFormatter(DebugType var1) {
      this.debugType = var1;
   }

    bool isLogEnabled(LogSeverity var1) {
      return DebugLog.isLogEnabled(var1, this.debugType);
   }

    bool isLogSeverityEnabled(LogSeverity var1) {
      return DebugLog.isLogEnabled(this.debugType, var1);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8, void* var9) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8, var9);
   }

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8, void* var9, void* var10) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10);
   }

   public std::string format(
      LogSeverity var1, std::string var2, std::string var3, std::string var4, Object var5, Object var6, Object var7, Object var8, Object var9, Object var10, Object var11
   ) {
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11);
   }

   public std::string format(
      LogSeverity var1,
      std::string var2,
      std::string var3,
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
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12);
   }

   public std::string format(
      LogSeverity var1,
      std::string var2,
      std::string var3,
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
      return DebugLog.formatString(this.debugType, var1, var2, var3, var4, var5, var6, var7, var8, var9, var10, var11, var12, var13);
   }
}
} // namespace debug
} // namespace zombie
