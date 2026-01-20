#include <string>
#include <unordered_map>
#include "zombie\gameStates/ChooseGameInfo.h"

namespace zombie {
namespace gameStates {

private ChooseGameInfo::ChooseGameInfo() {
    // TODO: Implement ChooseGameInfo
    return nullptr;
}

void ChooseGameInfo::Reset() {
    // TODO: Implement Reset
}

void ChooseGameInfo::readTitleDotTxt(std::unordered_map var0, const std::string& var1, Language var2) {
    // TODO: Implement readTitleDotTxt
}

void ChooseGameInfo::readDescriptionDotTxt(std::unordered_map var0, const std::string& var1, Language var2) {
    // TODO: Implement readDescriptionDotTxt
}

std::unordered_map ChooseGameInfo::getMapDetails(const std::string& var0) {
    // TODO: Implement getMapDetails
    return {};
}

Mod ChooseGameInfo::getModDetails(const std::string& var0) {
    // TODO: Implement getModDetails
    return nullptr;
}

Mod ChooseGameInfo::getAvailableModDetails(const std::string& var0) {
    // TODO: Implement getAvailableModDetails
    return nullptr;
}

Mod ChooseGameInfo::readModInfo(const std::string& var0) {
    // TODO: Implement readModInfo
    return nullptr;
}

Mod ChooseGameInfo::readModInfoAux(const std::string& var0) {
    // TODO: Implement readModInfoAux
    return nullptr;
}

} // namespace gameStates
} // namespace zombie
