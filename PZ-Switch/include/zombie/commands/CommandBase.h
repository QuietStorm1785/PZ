#pragma once
#include "java/sql/SQLException.h"
#include "zombie/commands/serverCommands/AddAllToWhiteListCommand.h"
#include "zombie/commands/serverCommands/AddItemCommand.h"
#include "zombie/commands/serverCommands/AddUserCommand.h"
#include "zombie/commands/serverCommands/AddUserToWhiteListCommand.h"
#include "zombie/commands/serverCommands/AddVehicleCommand.h"
#include "zombie/commands/serverCommands/AddXPCommand.h"
#include "zombie/commands/serverCommands/AlarmCommand.h"
#include "zombie/commands/serverCommands/BanSteamIDCommand.h"
#include "zombie/commands/serverCommands/BanUserCommand.h"
#include "zombie/commands/serverCommands/ChangeOptionCommand.h"
#include "zombie/commands/serverCommands/CheckModsNeedUpdate.h"
#include "zombie/commands/serverCommands/ChopperCommand.h"
#include "zombie/commands/serverCommands/ClearCommand.h"
#include "zombie/commands/serverCommands/ConnectionsCommand.h"
#include "zombie/commands/serverCommands/CreateHorde2Command.h"
#include "zombie/commands/serverCommands/CreateHordeCommand.h"
#include "zombie/commands/serverCommands/DebugPlayerCommand.h"
#include "zombie/commands/serverCommands/GodModeCommand.h"
#include "zombie/commands/serverCommands/GrantAdminCommand.h"
#include "zombie/commands/serverCommands/GunShotCommand.h"
#include "zombie/commands/serverCommands/HelpCommand.h"
#include "zombie/commands/serverCommands/InvisibleCommand.h"
#include "zombie/commands/serverCommands/KickUserCommand.h"
#include "zombie/commands/serverCommands/LightningCommand.h"
#include "zombie/commands/serverCommands/LogCommand.h"
#include "zombie/commands/serverCommands/NoClipCommand.h"
#include "zombie/commands/serverCommands/PlayersCommand.h"
#include "zombie/commands/serverCommands/QuitCommand.h"
#include "zombie/commands/serverCommands/ReleaseSafehouseCommand.h"
#include "zombie/commands/serverCommands/ReloadLuaCommand.h"
#include "zombie/commands/serverCommands/ReloadOptionsCommand.h"
#include "zombie/commands/serverCommands/RemoveAdminCommand.h"
#include "zombie/commands/serverCommands/RemoveUserFromWhiteList.h"
#include "zombie/commands/serverCommands/RemoveZombiesCommand.h"
#include "zombie/commands/serverCommands/ReplayCommands.h"
#include "zombie/commands/serverCommands/SaveCommand.h"
#include "zombie/commands/serverCommands/ServerMessageCommand.h"
#include "zombie/commands/serverCommands/SetAccessLevelCommand.h"
#include "zombie/commands/serverCommands/ShowOptionsCommand.h"
#include "zombie/commands/serverCommands/StartRainCommand.h"
#include "zombie/commands/serverCommands/StartStormCommand.h"
#include "zombie/commands/serverCommands/StatisticsCommand.h"
#include "zombie/commands/serverCommands/StopRainCommand.h"
#include "zombie/commands/serverCommands/StopWeatherCommand.h"
#include "zombie/commands/serverCommands/TeleportCommand.h"
#include "zombie/commands/serverCommands/TeleportToCommand.h"
#include "zombie/commands/serverCommands/ThunderCommand.h"
#include "zombie/commands/serverCommands/UnbanSteamIDCommand.h"
#include "zombie/commands/serverCommands/UnbanUserCommand.h"
#include "zombie/commands/serverCommands/VoiceBanCommand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace commands {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class CommandBase {
public:
 const int playerType;
 const std::string username;
 const std::string command;
private
 String[] commandArgs;
 bool parsingSuccessful = false;
 bool parsed = false;
 std::string message = "";
 const UdpConnection connection;
 std::string argsName = "default args name. Nothing match";
 static const std::string defaultArgsName = "default args name. Nothing match";
 const std::string description;
private
 static Class[] childrenClasses = new Class[]{SaveCommand.class,
 ServerMessageCommand.class,
 ConnectionsCommand.class,
 AddUserCommand.class,
 GrantAdminCommand.class,
 RemoveAdminCommand.class,
 DebugPlayerCommand.class,
 QuitCommand.class,
 AlarmCommand.class,
 ChopperCommand.class,
 AddAllToWhiteListCommand.class,
 KickUserCommand.class,
 TeleportCommand.class,
 TeleportToCommand.class,
 ReleaseSafehouseCommand.class,
 StartRainCommand.class,
 StopRainCommand.class,
 ThunderCommand.class,
 GunShotCommand.class,
 ReloadOptionsCommand.class,
 BanUserCommand.class,
 BanSteamIDCommand.class,
 UnbanUserCommand.class,
 UnbanSteamIDCommand.class,
 AddUserToWhiteListCommand.class,
 RemoveUserFromWhiteList.class,
 ChangeOptionCommand.class,
 ShowOptionsCommand.class,
 GodModeCommand.class,
 VoiceBanCommand.class,
 NoClipCommand.class,
 InvisibleCommand.class,
 HelpCommand.class,
 ClearCommand.class,
 PlayersCommand.class,
 AddItemCommand.class,
 AddXPCommand.class,
 AddVehicleCommand.class,
 CreateHordeCommand.class,
 CreateHorde2Command.class,
 ReloadLuaCommand.class,
 RemoveZombiesCommand.class,
 SetAccessLevelCommand.class,
 LogCommand.class,
 StatisticsCommand.class,
 LightningCommand.class,
 StopWeatherCommand.class,
 StartStormCommand.class,
 ReplayCommands.class,
 CheckModsNeedUpdate.class};

public
 static Class[] getSubClasses() { return childrenClasses; }

 static Class findCommandCls(const std::string &string) {
 for (auto &clazz : childrenClasses)
 if (!isDisabled(clazz) {
 CommandName[] commandNames =
 clazz.getAnnotationsByType(CommandName.class);

 for (auto &commandName : commandNames)
 Pattern pattern =
 Pattern.compile("^" + commandName.name() + "\\b", 2);
 if (pattern.matcher(string).find()) {
 return clazz;
 }
 }
 }
}

return nullptr;
}

static std::string getHelp(Class clazz) {
 CommandHelp commandHelp = getAnnotation(CommandHelp.class, clazz);
 if (commandHelp.empty()) {
 return nullptr;
 } else if (commandHelp.shouldTranslated()) {
 std::string string = commandHelp.helpText();
 return Translator.getText(string);
 } else {
 return commandHelp.helpText();
 }
}

static std::string getCommandName(Class clazz) {
 Annotation[] annotations = clazz.getAnnotationsByType(CommandName.class);
 return ((CommandName)annotations[0]).name();
}

static bool isDisabled(Class clazz) {
 DisabledCommand disabledCommand = getAnnotation(DisabledCommand.class, clazz);
 return disabledCommand != nullptr;
}

static int accessLevelToInt(const std::string &string) {
 switch (string) {
 case "admin":
 return 32;
 case "observer":
 return 2;
 case "moderator":
 return 16;
 case "overseer":
 return 8;
 case "gm":
 return 4;
 default:
 return 1;
 }
}

protected
CommandBase(const std::string &string0, const std::string &string2,
 const std::string &string1, UdpConnection udpConnection) {
 this->username = string0;
 this->command = string1;
 this->connection = udpConnection;
 this->playerType = accessLevelToInt(string2);
 std::vector arrayList = new ArrayList();
 Matcher matcher = Pattern.compile("([^\"]\\S*|\".*?\")\\s*").matcher(string1);

 while (matcher.find()) {
 arrayList.add(matcher.group(1).replace("\"", ""));
 }

 this->commandArgs = new String[arrayList.size() - 1];

 for (int int0 = 1; int0 < arrayList.size(); int0++) {
 this->commandArgs[int0 - 1] = (String)arrayList.get(int0);
 }

 this->description =
 "cmd=\"" + string1 + "\" user=\"" + string0 + "\" role=\"" +
 this->playerType + "\" " +
 (udpConnection != nullptr ? "guid=\"" + udpConnection.getConnectedGUID() +
 "\" id=\"" + udpConnection.idStr
 : "unknown connection") +
 "\"";
}

std::string Execute() {
 return this->canBeExecuted() ? this->Command() : this->message;
}

bool canBeExecuted() {
 if (this->parsed) {
 return this->parsingSuccessful;
 } else if (!this->PlayerSatisfyRequiredRights()) {
 this->message = this->playerHasNoRightError();
 return false;
 } else {
 this->parsingSuccessful = this->parseCommand();
 return this->parsingSuccessful;
 }
}

bool isCommandComeFromServerConsole() { return this->connection.empty(); }

RequiredRight getRequiredRights() {
 return this->getClass().getAnnotation(RequiredRight.class);
}

protected
CommandArgs[] getCommandArgVariants() {
 Class clazz = this->getClass();
 return clazz.getAnnotationsByType(CommandArgs.class);
}

bool hasHelp() {
 Class clazz = this->getClass();
 CommandHelp commandHelp = clazz.getAnnotation(CommandHelp.class);
 return commandHelp != nullptr;
}

std::string getHelp() {
 Class clazz = this->getClass();
 return getHelp();
}

std::string getCommandArg(int integer) {
 return this->commandArgs != nullptr && integer >= 0 &&
 integer < this->commandArgs.length
 ? this->commandArgs[integer]
 : nullptr;
}

bool hasOptionalArg(int integer) {
 return this->commandArgs != nullptr && integer >= 0 &&
 integer < this->commandArgs.length;
}

int getCommandArgsCount() { return this->commandArgs.length; }

protected
 String Command() throws SQLException;

bool parseCommand() {
 CommandArgs[] commandArgss = this->getCommandArgVariants();
 if (commandArgss.length == 1 && commandArgss[0].varArgs()) {
 this->parsed = true;
 return true;
 } else {
 bool boolean0 = commandArgss.length != 0 && this->commandArgs.length != 0 ||
 commandArgss.length == 0 && this->commandArgs.length == 0;
 std::vector arrayList = new ArrayList();

 for (auto &commandArgsx : commandArgss)
 arrayList.clear();
 this->message = "";
 int int0 = 0;
 boolean0 = true;

 for (int int1 = 0; int1 < commandArgsx.required().length; int1++) {
 std::string string = commandArgsx.required()[int1];
 if (int0 == this->commandArgs.length) {
 boolean0 = false;
 break;
 }

 Matcher matcher0 =
 Pattern.compile(string).matcher(this->commandArgs[int0]);
 if (!matcher0.matches()) {
 boolean0 = false;
 break;
 }

 for (int int2 = 0; int2 < matcher0.groupCount(); int2++) {
 arrayList.add(matcher0.group(int2 + 1);
 }

 int0++;
 }

 if (boolean0) {
 if (int0 == this->commandArgs.length) {
 this->argsName = commandArgsx.argName();
 break;
 }

 if (!commandArgsx.optional() == "no value")) {
 Matcher matcher1 = Pattern.compile(commandArgsx.optional())
 .matcher(this->commandArgs[int0]);
 if (matcher1.matches()) {
 for (int int3 = 0; int3 < matcher1.groupCount(); int3++) {
 arrayList.add(matcher1.group(int3 + 1);
 }
 } else {
 boolean0 = false;
 }
 }
 else if (int0 < this->commandArgs.length) {
 boolean0 = false;
 }

 if (boolean0) {
 this->argsName = commandArgsx.argName();
 break;
 }
 }
 }

 if (boolean0) {
 this->commandArgs = new String[arrayList.size()];
 this->commandArgs = arrayList.toArray(this->commandArgs);
 } else {
 this->message = this->invalidCommand();
 this->commandArgs = new String[0];
 }

 this->parsed = true;
 return boolean0;
}
}

int getAccessLevel() { return this->playerType; }

std::string getExecutorUsername() { return this->username; }

std::string getCommand() { return this->command; }

protected
static<T> T getAnnotation(Class<T> clazz1, Class clazz0) {
 return clazz0.getAnnotation(clazz1);
}

bool isParsingSuccessful() {
 if (!this->parsed) {
 this->parsingSuccessful = this->parseCommand();
 }

 return this->parsingSuccessful;
}

bool PlayerSatisfyRequiredRights() {
 RequiredRight requiredRight = this->getRequiredRights();
 return (this->playerType & requiredRight.requiredRights()) != 0;
}

std::string invalidCommand() {
 return this->hasHelp()
 ? this->getHelp()
 : Translator.getText("UI_command_arg_parse_failed", this->command);
}

std::string playerHasNoRightError() {
 return Translator.getText("UI_has_no_right_to_execute_command", this->username,
 this->command);
}
}
} // namespace commands
} // namespace zombie
