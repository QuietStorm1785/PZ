#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace debug {

class IDebugLogFormatter {
public:
    virtual ~IDebugLogFormatter() = default;
    bool isLogEnabled(LogSeverity var1);

    bool isLogSeverityEnabled(LogSeverity var1);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8, void* var9);

    std::string format(LogSeverity var1, const std::string& var2, const std::string& var3, const std::string& var4, void* var5, void* var6, void* var7, void* var8, void* var9, void* var10);

   std::string format(
      LogSeverity var1, std::string var2, std::string var3, std::string var4, Object var5, Object var6, Object var7, Object var8, Object var9, Object var10, Object var11
   );

   std::string format(
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
   );

   std::string format(
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
   );
}
} // namespace debug
} // namespace zombie
