#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {

class SystemDisabler {
public:
    static bool doCharacterStats = true;
    static bool doZombieCreation = true;
    static bool doSurvivorCreation = false;
    static bool doPlayerCreation = true;
    static bool doOverridePOVCharacters = true;
    static bool doVehiclesEverywhere = false;
    static bool doWorldSyncEnable = false;
    static bool doObjectStateSyncEnable = false;
    static bool doAllowDebugConnections = false;
    static bool doOverrideServerConnectDebugCheck = false;
    static bool doHighFriction = false;
    static bool doVehicleLowRider = false;
    static bool doEnableDetectOpenGLErrorsInTexture = false;
    static bool doVehiclesWithoutTextures = false;
    static bool zombiesDontAttack = false;
    static bool zombiesSwitchOwnershipEachUpdate = false;
    static bool doMainLoopDealWithNetData = true;
    static bool useNetworkCharacter = false;
    static bool bEnableAdvancedSoundOptions = false;
    static bool doKickInDebug = true;

    static void setDoCharacterStats(bool var0) {
      doCharacterStats = var0;
   }

    static void setDoZombieCreation(bool var0) {
      doZombieCreation = var0;
   }

    static void setDoSurvivorCreation(bool var0) {
      doSurvivorCreation = var0;
   }

    static void setDoPlayerCreation(bool var0) {
      doPlayerCreation = var0;
   }

    static void setOverridePOVCharacters(bool var0) {
      doOverridePOVCharacters = var0;
   }

    static void setVehiclesEverywhere(bool var0) {
      doVehiclesEverywhere = var0;
   }

    static void setWorldSyncEnable(bool var0) {
      doWorldSyncEnable = var0;
   }

    static void setObjectStateSyncEnable(bool var0) {
      doObjectStateSyncEnable = var0;
   }

    static bool getAllowDebugConnections() {
    return doAllowDebugConnections;
   }

    static bool getOverrideServerConnectDebugCheck() {
    return doOverrideServerConnectDebugCheck;
   }

    static bool getdoHighFriction() {
    return doHighFriction;
   }

    static bool getdoVehicleLowRider() {
    return doVehicleLowRider;
   }

    static bool getDoMainLoopDealWithNetData() {
    return doMainLoopDealWithNetData;
   }

    static void setEnableAdvancedSoundOptions(bool var0) {
      bEnableAdvancedSoundOptions = var0;
   }

    static bool getEnableAdvancedSoundOptions() {
    return bEnableAdvancedSoundOptions;
   }

    static void Reset() {
      doCharacterStats = true;
      doZombieCreation = true;
      doSurvivorCreation = false;
      doPlayerCreation = true;
      doOverridePOVCharacters = true;
      doVehiclesEverywhere = false;
      doAllowDebugConnections = false;
      doWorldSyncEnable = false;
      doObjectStateSyncEnable = false;
      doMainLoopDealWithNetData = true;
      bEnableAdvancedSoundOptions = false;
   }
}
} // namespace zombie
