#pragma once
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
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
namespace serverCommands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

    name = "log"
)
    required = {"(.+)", "(.+)"}
)
    helpText = "UI_ServerOptionDesc_SetLogLevel"
)
    requiredRights = 32
)
class LogCommand : public CommandBase {
    public:
    public
      LogCommand(const std::string &string0, const std::string &string1,
                 const std::string &string2, UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      static DebugType getDebugType(const std::string &string) {
        std::vector arrayList = new ArrayList();

        for (DebugType debugType : DebugType.values()) {
          if (debugType.name().toLowerCase().startsWith(string.toLowerCase())) {
            arrayList.add(debugType);
          }
        }

        return arrayList.size() == 1 ? (DebugType)arrayList.get(0) : nullptr;
      }

      static LogSeverity getLogSeverity(const std::string &string) {
        std::vector arrayList = new ArrayList();

        for (LogSeverity logSeverity : LogSeverity.values()) {
          if (logSeverity.name().toLowerCase().startsWith(
                  string.toLowerCase())) {
            arrayList.add(logSeverity);
          }
        }

        return arrayList.size() == 1 ? (LogSeverity)arrayList.get(0) : nullptr;
      }

      std::string Command() {
        DebugType debugType = getDebugType(this.getCommandArg(0));
        LogSeverity logSeverity = getLogSeverity(this.getCommandArg(1));
        if (debugType != nullptr && logSeverity != nullptr) {
          DebugLog.enableLog(debugType, logSeverity);
          if (DebugType.Network == debugType)) {
                ZNet.SetLogLevel(logSeverity);
            }

          return String.format("Server \"%s\" log level is \"%s\"",
                               debugType.name().toLowerCase(),
                               logSeverity.name().toLowerCase());
        } else {
          return Translator.getText(
              "UI_ServerOptionDesc_SetLogLevel",
              debugType == nullptr ? "\"type\""
                                   : debugType.name().toLowerCase(),
              logSeverity == nullptr ? "\"severity\""
                                     : logSeverity.name().toLowerCase());
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
