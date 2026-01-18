#pragma once
#include "zombie/Lua/LuaManager.h"
#include "zombie/commands/CommandArgs.h"
#include "zombie/commands/CommandBase.h"
#include "zombie/commands/CommandHelp.h"
#include "zombie/commands/CommandName.h"
#include "zombie/commands/RequiredRight.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/LoggerManager.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"
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

 name = "createhorde2"
)
 varArgs = true
)
 helpText = "UI_ServerOptionDesc_CreateHorde2"
)
 requiredRights = 56
)
class CreateHorde2Command : public CommandBase {
 public:
 public
 CreateHorde2Command(const std::string &string0,
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
 int int4 = -1;
 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;
 bool boolean3 = false;
 float float0 = 1.0F;
 std::string string0 = nullptr;

 for (byte byte0 = 0; byte0 < this->getCommandArgsCount() - 1;
 byte0 += 2) {
 std::string string1 = this->getCommandArg(Integer.valueOf(byte0);
 std::string string2 = this->getCommandArg(byte0 + 1);
 switch (string1) {
 case "-count":
 int0 = PZMath.tryParseInt(string2, -1);
 break;
 case "-radius":
 int1 = PZMath.tryParseInt(string2, -1);
 break;
 case "-x":
 int2 = PZMath.tryParseInt(string2, -1);
 break;
 case "-y":
 int3 = PZMath.tryParseInt(string2, -1);
 break;
 case "-z":
 int4 = PZMath.tryParseInt(string2, -1);
 break;
 case "-outfit":
 string0 = StringUtils.discardNullOrWhitespace(string2);
 break;
 case "-crawler":
 boolean0 = !"false" == string2);
 break;
 case "-isFallOnFront":
 boolean1 = !"false" == string2);
 break;
 case "-isFakeDead":
 boolean2 = !"false" == string2);
 break;
 case "-knockedDown":
 boolean3 = !"false" == string2);
 break;
 case "-health":
 float0 = Float.valueOf(string2);
 break;
 default:
 return this->getHelp();
 }
 }

 int0 = PZMath.clamp(int0, 1, 500);
 IsoGridSquare square =
 IsoWorld.instance.CurrentCell.getGridSquare(int2, int3, int4);
 if (square.empty()) {
 return "invalid location";
 } else if (string0 != nullptr &&
 OutfitManager.instance.FindMaleOutfit(string0) == nullptr &&
 OutfitManager.instance.FindFemaleOutfit(string0) ==
 nullptr) {
 return "invalid outfit";
 } else {
 int integer = nullptr;
 if (string0 != nullptr) {
 if (OutfitManager.instance.FindFemaleOutfit(string0) == nullptr) {
 integer = Integer.MIN_VALUE;
 } else if (OutfitManager.instance.FindMaleOutfit(string0) ==
 nullptr) {
 integer = Integer.MAX_VALUE;
 }
 }

 for (int int5 = 0; int5 < int0; int5++) {
 int int6 =
 int1 <= 0 ? int2 : Rand.Next(int2 - int1, int2 + int1 + 1);
 int int7 =
 int1 <= 0 ? int3 : Rand.Next(int3 - int1, int3 + int1 + 1);
 LuaManager.GlobalObject.addZombiesInOutfit(
 int6, int7, int4, 1, string0, integer, boolean0, boolean1,
 boolean2, boolean3, float0);
 }

 LoggerManager.getLogger("admin").write(
 this->getExecutorUsername() + " created a horde of " + int0 +
 " zombies near " + int2 + "," + int3,
 "IMPORTANT");
 return "Horde spawned.";
 }
 }
 }
 } // namespace serverCommands
 } // namespace commands
 } // namespace zombie
