#include <string>
#include "zombie\core\znet/SteamUtils.h"

namespace zombie {
namespace core {
namespace znet {

void SteamUtils::loadLibrary(const std::string& var0) {
    // TODO: Implement loadLibrary
}

void SteamUtils::init() {
    // TODO: Implement init
}

void SteamUtils::shutdown() {
    // TODO: Implement shutdown
}

void SteamUtils::runLoop() {
    // TODO: Implement runLoop
}

bool SteamUtils::isSteamModeEnabled() {
    // TODO: Implement isSteamModeEnabled
    return false;
}

bool SteamUtils::isOverlayEnabled() {
    // TODO: Implement isOverlayEnabled
    return false;
}

std::string SteamUtils::convertSteamIDToString(long var0) {
    // TODO: Implement convertSteamIDToString
    return "";
}

bool SteamUtils::isValidSteamID(const std::string& var0) {
    // TODO: Implement isValidSteamID
    return false;
}

long SteamUtils::convertStringToSteamID(const std::string& var0) {
    // TODO: Implement convertStringToSteamID
    return 0;
}

void SteamUtils::addJoinRequestCallback(IJoinRequestCallback var0) {
    // TODO: Implement addJoinRequestCallback
}

void SteamUtils::removeJoinRequestCallback(IJoinRequestCallback var0) {
    // TODO: Implement removeJoinRequestCallback
}

bool SteamUtils::isRunningOnSteamDeck() {
    // TODO: Implement isRunningOnSteamDeck
    return false;
}

return SteamUtils::n_IsSteamRunningOnSteamDeck() {
    // TODO: Implement n_IsSteamRunningOnSteamDeck
    return nullptr;
}

bool SteamUtils::showGamepadTextInput(bool var0, bool var1, const std::string& var2, int var3, const std::string& var4) {
    // TODO: Implement showGamepadTextInput
    return false;
}

return SteamUtils::n_ShowGamepadTextInput(var0 ?, var1 ?) {
    // TODO: Implement n_ShowGamepadTextInput
    return nullptr;
}

bool SteamUtils::showFloatingGamepadTextInput(bool var0, int var1, int var2, int var3, int var4) {
    // TODO: Implement showFloatingGamepadTextInput
    return false;
}

bool SteamUtils::isFloatingGamepadTextInputVisible() {
    // TODO: Implement isFloatingGamepadTextInputVisible
    return false;
}

void SteamUtils::joinRequestCallback(long var0, const std::string& var2) {
    // TODO: Implement joinRequestCallback
}

int SteamUtils::clientInitiateConnectionCallback(long var0) {
    // TODO: Implement clientInitiateConnectionCallback
    return 0;
}

int SteamUtils::validateOwnerCallback(long var0, long var2) {
    // TODO: Implement validateOwnerCallback
    return 0;
}

void SteamUtils::gamepadTextInputDismissedCallback(const std::string& var0) {
    // TODO: Implement gamepadTextInputDismissedCallback
}

void SteamUtils::floatingGamepadTextInputDismissedCallback() {
    // TODO: Implement floatingGamepadTextInputDismissedCallback
}

} // namespace znet
} // namespace core
} // namespace zombie
