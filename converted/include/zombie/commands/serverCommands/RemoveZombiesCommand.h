#pragma once
#include "zombie/characters/IsoZombie.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/network/GameServer.h"
#include "zombie/popman/NetworkZombiePacker.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
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

    name = "removezombies"
)
    varArgs = true
)
    helpText = "UI_ServerOptionDesc_RemoveZombies"
)
    requiredRights = 56
)
class RemoveZombiesCommand : public CommandBase {
    public:
    public
      RemoveZombiesCommand(const std::string &string0,
                           const std::string &string1,
                           const std::string &string2,
                           UdpConnection udpConnection) {
        super(string0, string1, string2, udpConnection);
      }

      std::string Command() {
        int int0 = -1;
        int int1 = -1;
        int int2 = -1;
        int int3 = -1;
        bool boolean0 = false;
        bool boolean1 = false;
        bool boolean2 = false;

        for (byte byte0 = 0; byte0 < this.getCommandArgsCount() - 1;
             byte0 += 2) {
          std::string string0 = this.getCommandArg(Integer.valueOf(byte0));
          std::string string1 = this.getCommandArg(byte0 + 1);
          switch (string0) {
          case "-radius":
            int0 = PZMath.tryParseInt(string1, -1);
            break;
          case "-reanimated":
            boolean0 = StringUtils.tryParseBoolean(string1);
            break;
          case "-x":
            int1 = PZMath.tryParseInt(string1, -1);
            break;
          case "-y":
            int2 = PZMath.tryParseInt(string1, -1);
            break;
          case "-z":
            int3 = PZMath.tryParseInt(string1, -1);
            break;
          case "-remove":
            boolean1 = StringUtils.tryParseBoolean(string1);
            break;
          case "-clear":
            boolean2 = StringUtils.tryParseBoolean(string1);
            break;
          default:
            return this.getHelp();
          }
        }

        if (boolean1) {
          GameServer.removeZombiesConnection = this.connection;
          return "Zombies removed.";
        } else if (int3 >= 0 && int3 < 8) {
          for (int int4 = int2 - int0; int4 <= int2 + int0; int4++) {
            for (int int5 = int1 - int0; int5 <= int1 + int0; int5++) {
              IsoGridSquare square =
                  IsoWorld.instance.CurrentCell.getGridSquare(int5, int4, int3);
              if (square != nullptr) {
                if (boolean2) {
                  if (!square.getStaticMovingObjects().isEmpty()) {
                    for (int int6 = square.getStaticMovingObjects().size() - 1;
                         int6 >= 0; int6--) {
                      IsoDeadBody deadBody = Type.tryCastTo(
                          square.getStaticMovingObjects().get(int6),
                          IsoDeadBody.class);
                      if (deadBody != nullptr) {
                        GameServer.sendRemoveCorpseFromMap(deadBody);
                        deadBody.removeFromWorld();
                        deadBody.removeFromSquare();
                      }
                    }
                  }
                } else if (!square.getMovingObjects().isEmpty()) {
                  for (int int7 = square.getMovingObjects().size() - 1;
                       int7 >= 0; int7--) {
                    IsoZombie zombie0 = Type.tryCastTo(
                        square.getMovingObjects().get(int7), IsoZombie.class);
                    if (zombie0 != nullptr &&
                        (boolean0 || !zombie0.isReanimatedPlayer())) {
                      NetworkZombiePacker.getInstance().deleteZombie(zombie0);
                      zombie0.removeFromWorld();
                      zombie0.removeFromSquare();
                    }
                  }
                }
              }
            }
          }

          LoggerManager.getLogger("admin").write(this.getExecutorUsername() +
                                                     " removed zombies near " +
                                                     int1 + "," + int2,
                                                 "IMPORTANT");
          return "Zombies removed.";
        } else {
          return "invalid z";
        }
      }
    }
    } // namespace serverCommands
    } // namespace commands
    } // namespace zombie
