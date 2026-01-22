#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
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

namespace zombie {
namespace commands {


class CommandBase {
public:
    const int playerType;
    const std::string username;
    const std::string command;
   private std::string[] commandArgs;
    bool parsingSuccessful = false;
    bool parsed = false;
    std::string message = "";
    const UdpConnection connection;
    std::string argsName = "default args name. Nothing match";
    static const std::string defaultArgsName = "default args name. Nothing match";
    const std::string description;
   private static Class[] childrenClasses = new Class[]{
      SaveCommand.class,
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
      CheckModsNeedUpdate.class
   };

   public static Class[] getSubClasses() {
    return childrenClasses;
   }

    static Class findCommandCls(const std::string& var0) {
    for (auto& var5 : childrenClasses)         if (!isDisabled(var5)) {
            CommandName[] var1 = var5.getAnnotationsByType(CommandName.class);

    for (auto& var10 : var1)    Pattern var6 = Pattern.compile("^" + var10.name() + "\\b", 2);
               if (var6.matcher(var0).find()) {
    return var5;
               }
            }
         }
      }

    return nullptr;
   }

    static std::string getHelp(Class var0) {
    CommandHelp var1 = getAnnotation(CommandHelp.class, var0);
      if (var1 == nullptr) {
    return nullptr;
      } else if (var1.shouldTranslated()) {
    std::string var2 = var1.helpText();
         return Translator.getText(var2);
      } else {
         return var1.helpText();
      }
   }

    static std::string getCommandName(Class var0) {
      Annotation[] var1 = var0.getAnnotationsByType(CommandName.class);
      return ((CommandName)var1[0]).name();
   }

    static bool isDisabled(Class var0) {
    DisabledCommand var1 = getAnnotation(DisabledCommand.class, var0);
      return var1 != nullptr;
   }

    static int accessLevelToInt(const std::string& var0) {
      switch (var0) {
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

    protected CommandBase(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
      this.username = var1;
      this.command = var3;
      this.connection = var4;
      this.playerType = accessLevelToInt(var2);
    std::vector var5 = new std::vector();
    Matcher var6 = Pattern.compile("([^\"]\\S*|\".*?\")\\s*").matcher(var3);

      while (var6.find()) {
         var5.push_back(var6.group(1).replace("\"", ""));
      }

      this.commandArgs = new std::string[var5.size() - 1];

      for (int var7 = 1; var7 < var5.size(); var7++) {
         this.commandArgs[var7 - 1] = (std::string)var5.get(var7);
      }

      this.description = "cmd=\""
         + var3
         + "\" user=\""
         + var1
         + "\" role=\""
         + this.playerType
         + "\" "
         + (var4 != nullptr ? "guid=\"" + var4.getConnectedGUID() + "\" id=\"" + var4.idStr : "unknown connection")
         + "\"";
   }

    std::string Execute() {
      return this.canBeExecuted() ? this.Command() : this.message;
   }

    bool canBeExecuted() {
      if (this.parsed) {
         return this.parsingSuccessful;
      } else if (!this.PlayerSatisfyRequiredRights()) {
         this.message = this.playerHasNoRightError();
    return false;
      } else {
         this.parsingSuccessful = this.parseCommand();
         return this.parsingSuccessful;
      }
   }

    bool isCommandComeFromServerConsole() {
      return this.connection == nullptr;
   }

    RequiredRight getRequiredRights() {
      return this.getClass().getAnnotation(RequiredRight.class);
   }

   protected CommandArgs[] getCommandArgVariants() {
    Class var1 = this.getClass();
      return var1.getAnnotationsByType(CommandArgs.class);
   }

    bool hasHelp() {
    Class var1 = this.getClass();
    CommandHelp var2 = var1.getAnnotation(CommandHelp.class);
      return var2 != nullptr;
   }

    std::string getHelp() {
    Class var1 = this.getClass();
    return getHelp();
   }

    std::string getCommandArg(int var1) {
      return this.commandArgs != nullptr && var1 >= 0 && var1 < this.commandArgs.length ? this.commandArgs[var1] : nullptr;
   }

    bool hasOptionalArg(int var1) {
      return this.commandArgs != nullptr && var1 >= 0 && var1 < this.commandArgs.length;
   }

    int getCommandArgsCount() {
      return this.commandArgs.length;
   }

   protected abstract std::string Command() throws SQLException;

    bool parseCommand() {
      CommandArgs[] var1 = this.getCommandArgVariants();
      if (var1.length == 1 && var1[0].varArgs()) {
         this.parsed = true;
    return true;
      } else {
    bool var2 = var1.length != 0 && this.commandArgs.length != 0 || var1.length == 0 && this.commandArgs.length == 0;
    std::vector var3 = new std::vector();

    for (auto& var7 : var1)            var3.clear();
            this.message = "";
    int var8 = 0;
            var2 = true;

            for (int var9 = 0; var9 < var7.required().length; var9++) {
    std::string var10 = var7.required()[var9];
               if (var8 == this.commandArgs.length) {
                  var2 = false;
                  break;
               }

    Matcher var11 = Pattern.compile(var10).matcher(this.commandArgs[var8]);
               if (!var11.matches()) {
                  var2 = false;
                  break;
               }

               for (int var12 = 0; var12 < var11.groupCount(); var12++) {
                  var3.push_back(var11.group(var12 + 1));
               }

               var8++;
            }

            if (var2) {
               if (var8 == this.commandArgs.length) {
                  this.argsName = var7.argName();
                  break;
               }

               if (!var7.optional() == "no value")) {
    Matcher var13 = Pattern.compile(var7.optional()).matcher(this.commandArgs[var8]);
                  if (var13.matches()) {
                     for (int var14 = 0; var14 < var13.groupCount(); var14++) {
                        var3.push_back(var13.group(var14 + 1));
                     }
                  } else {
                     var2 = false;
                  }
               } else if (var8 < this.commandArgs.length) {
                  var2 = false;
               }

               if (var2) {
                  this.argsName = var7.argName();
                  break;
               }
            }
         }

         if (var2) {
            this.commandArgs = new std::string[var3.size()];
            this.commandArgs = var3.toArray(this.commandArgs);
         } else {
            this.message = this.invalidCommand();
            this.commandArgs = new std::string[0];
         }

         this.parsed = true;
    return var2;
      }
   }

    int getAccessLevel() {
      return this.playerType;
   }

    std::string getExecutorUsername() {
      return this.username;
   }

    std::string getCommand() {
      return this.command;
   }

   protected static <T> T getAnnotation(Class<T> var0, Class var1) {
      return var1.getAnnotation(var0);
   }

    bool isParsingSuccessful() {
      if (!this.parsed) {
         this.parsingSuccessful = this.parseCommand();
      }

      return this.parsingSuccessful;
   }

    bool PlayerSatisfyRequiredRights() {
    RequiredRight var1 = this.getRequiredRights();
      return (this.playerType & var1.requiredRights()) != 0;
   }

    std::string invalidCommand() {
      return this.hasHelp() ? this.getHelp() : Translator.getText("UI_command_arg_parse_failed", this.command);
   }

    std::string playerHasNoRightError() {
      return Translator.getText("UI_has_no_right_to_execute_command", this.username, this.command);
   }
}
} // namespace commands
} // namespace zombie
