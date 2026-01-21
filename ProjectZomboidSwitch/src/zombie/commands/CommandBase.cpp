#include <string>
#include "zombie/commands/CommandBase.h"

namespace zombie {
namespace commands {

Class CommandBase::findCommandCls(const std::string& var0) {
    // TODO: Implement findCommandCls
    return nullptr;
}

std::string CommandBase::getHelp(Class var0) {
    // TODO: Implement getHelp
    return "";
}

std::string CommandBase::getCommandName(Class var0) {
    // TODO: Implement getCommandName
    return "";
}

bool CommandBase::isDisabled(Class var0) {
    // TODO: Implement isDisabled
    return false;
}

int CommandBase::accessLevelToInt(const std::string& var0) {
    // TODO: Implement accessLevelToInt
    return 0;
}

protected CommandBase::CommandBase(const std::string& var1, const std::string& var2, const std::string& var3, UdpConnection var4) {
    // TODO: Implement CommandBase
    return nullptr;
}

std::string CommandBase::Execute() {
    // TODO: Implement Execute
    return "";
}

bool CommandBase::canBeExecuted() {
    // TODO: Implement canBeExecuted
    return false;
}

bool CommandBase::isCommandComeFromServerConsole() {
    // TODO: Implement isCommandComeFromServerConsole
    return false;
}

RequiredRight CommandBase::getRequiredRights() {
    // TODO: Implement getRequiredRights
    return nullptr;
}

bool CommandBase::hasHelp() {
    // TODO: Implement hasHelp
    return false;
}

std::string CommandBase::getHelp() {
    // TODO: Implement getHelp
    return "";
}

return CommandBase::getHelp() {
    // TODO: Implement getHelp
    return nullptr;
}

std::string CommandBase::getCommandArg(int var1) {
    // TODO: Implement getCommandArg
    return "";
}

bool CommandBase::hasOptionalArg(int var1) {
    // TODO: Implement hasOptionalArg
    return false;
}

int CommandBase::getCommandArgsCount() {
    // TODO: Implement getCommandArgsCount
    return 0;
}

bool CommandBase::parseCommand() {
    // TODO: Implement parseCommand
    return false;
}

int CommandBase::getAccessLevel() {
    // TODO: Implement getAccessLevel
    return 0;
}

std::string CommandBase::getExecutorUsername() {
    // TODO: Implement getExecutorUsername
    return "";
}

std::string CommandBase::getCommand() {
    // TODO: Implement getCommand
    return "";
}

bool CommandBase::isParsingSuccessful() {
    // TODO: Implement isParsingSuccessful
    return false;
}

bool CommandBase::PlayerSatisfyRequiredRights() {
    // TODO: Implement PlayerSatisfyRequiredRights
    return false;
}

std::string CommandBase::invalidCommand() {
    // TODO: Implement invalidCommand
    return "";
}

std::string CommandBase::playerHasNoRightError() {
    // TODO: Implement playerHasNoRightError
    return "";
}

} // namespace commands
} // namespace zombie
