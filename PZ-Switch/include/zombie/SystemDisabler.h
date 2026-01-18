#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

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

 static void setDoCharacterStats(bool bDo) { doCharacterStats = bDo; }

 static void setDoZombieCreation(bool bDo) { doZombieCreation = bDo; }

 static void setDoSurvivorCreation(bool bDo) { doSurvivorCreation = bDo; }

 static void setDoPlayerCreation(bool bDo) { doPlayerCreation = bDo; }

 static void setOverridePOVCharacters(bool bDo) {
 doOverridePOVCharacters = bDo;
 }

 static void setVehiclesEverywhere(bool bDo) { doVehiclesEverywhere = bDo; }

 static void setWorldSyncEnable(bool bDo) { doWorldSyncEnable = bDo; }

 static void setObjectStateSyncEnable(bool bDo) {
 doObjectStateSyncEnable = bDo;
 }

 static bool getAllowDebugConnections() { return doAllowDebugConnections; }

 static bool getOverrideServerConnectDebugCheck() {
 return doOverrideServerConnectDebugCheck;
 }

 static bool getdoHighFriction() { return doHighFriction; }

 static bool getdoVehicleLowRider() { return doVehicleLowRider; }

 static bool getDoMainLoopDealWithNetData() {
 return doMainLoopDealWithNetData;
 }

 static void setEnableAdvancedSoundOptions(bool enable) {
 bEnableAdvancedSoundOptions = enable;
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
