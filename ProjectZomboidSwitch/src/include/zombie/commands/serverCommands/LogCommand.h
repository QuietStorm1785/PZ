#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/Translator.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/znet/ZNet.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugType.h"
#include "zombie/debug/LogSeverity.h"

namespace zombie {
namespace commands {
namespace serverCommands {


class LogCommand : public CommandBase {
public:
    public LogCommand(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      super(var1, var2, var3, var4);
   }

    static DebugType getDebugType(const std::string& var0) {
    std::vector var1 = new std::vector();

      for (DebugType var5 : DebugType.values()) {
         if (var5.name().toLowerCase().startsWith(var0.toLowerCase())) {
            var1.push_back(var5);
         }
      }

      return var1.size() == 1 ? (DebugType)var1.get(0) : nullptr;
   }

    static LogSeverity getLogSeverity(const std::string& var0) {
    std::vector var1 = new std::vector();

      for (LogSeverity var5 : LogSeverity.values()) {
         if (var5.name().toLowerCase().startsWith(var0.toLowerCase())) {
            var1.push_back(var5);
         }
      }

      return var1.size() == 1 ? (LogSeverity)var1.get(0) : nullptr;
   }

    std::string Command() {
    DebugType var1 = getDebugType(this.getCommandArg(0));
    LogSeverity var2 = getLogSeverity(this.getCommandArg(1));
      if (var1 != nullptr && var2 != nullptr) {
         DebugLog.enableLog(var1, var2);
         if (DebugType.Network == var1)) {
            ZNet.SetLogLevel(var2);
         }

         return std::string.format("Server \"%s\" log level is \"%s\"", var1.name().toLowerCase(), var2.name().toLowerCase());
      } else {
         return Translator.getText(
            "UI_ServerOptionDesc_SetLogLevel", var1 == nullptr ? "\"type\"" : var1.name().toLowerCase(), var2 == nullptr ? "\"severity\"" : var2.name().toLowerCase()
         );
      }
   }
}
} // namespace serverCommands
} // namespace commands
} // namespace zombie
