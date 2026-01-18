#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "fmod/fmod/Audio.h"
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameServer.h"
#include <algorithm>

namespace zombie {
namespace iso {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class RainManager {
public:
 static bool IsRaining = false;
 static int NumActiveRainSplashes = 0;
 static int NumActiveRaindrops = 0;
 static int MaxRainSplashObjects = 500;
 static int MaxRaindropObjects = 500;
 static float RainSplashAnimDelay = 0.2F;
 static int AddNewSplashesDelay = 30;
 static int AddNewSplashesTimer = AddNewSplashesDelay;
 static float RaindropGravity = 0.065F;
 static float GravModMin = 0.28F;
 static float GravModMax = 0.5F;
 static float RaindropStartDistance = 850.0F;
 public static IsoGridSquare[] PlayerLocation = new IsoGridSquare[4];
 public static IsoGridSquare[] PlayerOldLocation = new IsoGridSquare[4];
 static bool PlayerMoved = true;
 static int RainRadius = 18;
 static Audio RainAmbient;
 static Audio ThunderAmbient = nullptr;
 static ColorInfo RainSplashTintMod = new ColorInfo(0.8F, 0.9F, 1.0F, 0.3F);
 static ColorInfo RaindropTintMod = new ColorInfo(0.8F, 0.9F, 1.0F, 0.3F);
 static ColorInfo DarkRaindropTintMod = new ColorInfo(0.8F, 0.9F, 1.0F, 0.3F);
 public static ArrayList<IsoRainSplash> RainSplashStack = new ArrayList<>(1600);
 public static ArrayList<IsoRaindrop> RaindropStack = new ArrayList<>(1600);
 public static Stack<IsoRainSplash> RainSplashReuseStack = std::make_unique<Stack<>>();
 public static Stack<IsoRaindrop> RaindropReuseStack = std::make_unique<Stack<>>();
 static float RainChangeTimer = 1.0F;
 static float RainChangeRate = 0.01F;
 static float RainChangeRateMin = 0.006F;
 static float RainChangeRateMax = 0.01F;
 static float RainIntensity = 1.0F;
 static float RainDesiredIntensity = 1.0F;
 static int randRain = 0;
 static int randRainMin = 0;
 static int randRainMax = 0;
 static bool stopRain = false;
 static Audio OutsideAmbient = nullptr;
 static Audio OutsideNightAmbient = nullptr;
 static ColorInfo AdjustedRainSplashTintMod = std::make_unique<ColorInfo>();

 static void reset() {
 RainSplashStack.clear();
 RaindropStack.clear();
 RaindropReuseStack.clear();
 RainSplashReuseStack.clear();
 NumActiveRainSplashes = 0;
 NumActiveRaindrops = 0;

 for (int int0 = 0; int0 < 4; int0++) {
 PlayerLocation[int0] = nullptr;
 PlayerOldLocation[int0] = nullptr;
 }

 RainAmbient = nullptr;
 ThunderAmbient = nullptr;
 IsRaining = false;
 stopRain = false;
 }

 static void AddRaindrop(IsoRaindrop NewRaindrop) {
 if (NumActiveRaindrops < MaxRaindropObjects) {
 RaindropStack.add(NewRaindrop);
 NumActiveRaindrops++;
 } else {
 IsoRaindrop raindrop = nullptr;
 int int0 = -1;

 for (int int1 = 0; int1 < RaindropStack.size(); int1++) {
 if (RaindropStack.get(int1).Life > int0) {
 int0 = RaindropStack.get(int1).Life;
 raindrop = RaindropStack.get(int1);
 }
 }

 if (raindrop != nullptr) {
 RemoveRaindrop(raindrop);
 RaindropStack.add(NewRaindrop);
 NumActiveRaindrops++;
 }
 }
 }

 static void AddRainSplash(IsoRainSplash NewRainSplash) {
 if (NumActiveRainSplashes < MaxRainSplashObjects) {
 RainSplashStack.add(NewRainSplash);
 NumActiveRainSplashes++;
 } else {
 IsoRainSplash rainSplash = nullptr;
 int int0 = -1;

 for (int int1 = 0; int1 < RainSplashStack.size(); int1++) {
 if (RainSplashStack.get(int1).Age > int0) {
 int0 = RainSplashStack.get(int1).Age;
 rainSplash = RainSplashStack.get(int1);
 }
 }

 RemoveRainSplash(rainSplash);
 RainSplashStack.add(NewRainSplash);
 NumActiveRainSplashes++;
 }
 }

 static void AddSplashes() {
 if (AddNewSplashesTimer > 0) {
 AddNewSplashesTimer--;
 } else {
 AddNewSplashesTimer = (int)(AddNewSplashesDelay * (PerformanceSettings.getLockFPS() / 30.0F);
 void* object = nullptr;
 if (!stopRain) {
 if (PlayerMoved) {
 for (int int0 = RainSplashStack.size() - 1; int0 >= 0; int0--) {
 IsoRainSplash rainSplash0 = RainSplashStack.get(int0);
 if (!inBounds(rainSplash0.square) {
 RemoveRainSplash(rainSplash0);
 }
 }

 for (int int1 = RaindropStack.size() - 1; int1 >= 0; int1--) {
 IsoRaindrop raindrop0 = RaindropStack.get(int1);
 if (!inBounds(raindrop0.square) {
 RemoveRaindrop(raindrop0);
 }
 }
 }

 int int2 = 0;

 for (int int3 = 0; int3 < IsoPlayer.numPlayers; int3++) {
 if (IsoPlayer.players[int3] != nullptr) {
 int2++;
 }
 }

 int int4 = RainRadius * 2 * RainRadius * 2;
 int int5 = int4 / (randRain + 1);
 int5 = Math.min(MaxRainSplashObjects, int5);

 while (NumActiveRainSplashes > int5 * int2) {
 RemoveRainSplash(RainSplashStack.get(0);
 }

 while (NumActiveRaindrops > int5 * int2) {
 RemoveRaindrop(RaindropStack.get(0);
 }

 IsoCell cell = IsoWorld.instance.CurrentCell;

 for (int int6 = 0; int6 < IsoPlayer.numPlayers; int6++) {
 if (IsoPlayer.players[int6] != nullptr && PlayerLocation[int6] != nullptr) {
 for (int int7 = 0; int7 < int5; int7++) {
 int int8 = Rand.Next(-RainRadius, RainRadius);
 int int9 = Rand.Next(-RainRadius, RainRadius);
 object = cell.getGridSquare(PlayerLocation[int6].getX() + int8, PlayerLocation[int6].getY() + int9, 0);
 if (object != nullptr
 && ((IsoGridSquare)object).isSeen(int6)
 && !((IsoGridSquare)object).getProperties().Is(IsoFlagType.vegitation)
 && ((IsoGridSquare)object).getProperties().Is(IsoFlagType.exterior) {
 StartRainSplash(cell, (IsoGridSquare)object, true);
 }
 }
 }
 }
 }

 PlayerMoved = false;
 if (!stopRain) {
 randRain--;
 if (randRain < randRainMin) {
 randRain = randRainMin;
 }
 } else {
 randRain = (int)(randRain - 1.0F * GameTime.instance.getMultiplier());
 if (randRain < randRainMin) {
 removeAll();
 randRain = randRainMin;
 } else {
 for (int int10 = RainSplashStack.size() - 1; int10 >= 0; int10--) {
 if (Rand.Next(randRain) == 0) {
 IsoRainSplash rainSplash1 = RainSplashStack.get(int10);
 RemoveRainSplash(rainSplash1);
 }
 }

 for (int int11 = RaindropStack.size() - 1; int11 >= 0; int11--) {
 if (Rand.Next(randRain) == 0) {
 IsoRaindrop raindrop1 = RaindropStack.get(int11);
 RemoveRaindrop(raindrop1);
 }
 }
 }
 }
 }
 }

 static void RemoveRaindrop(IsoRaindrop DyingRaindrop) {
 if (DyingRaindrop.square != nullptr) {
 DyingRaindrop.square.getProperties().UnSet(IsoFlagType.HasRaindrop);
 DyingRaindrop.square.setRainDrop(nullptr);
 DyingRaindrop.square = nullptr;
 }

 RaindropStack.remove(DyingRaindrop);
 NumActiveRaindrops--;
 RaindropReuseStack.push(DyingRaindrop);
 }

 static void RemoveRainSplash(IsoRainSplash DyingRainSplash) {
 if (DyingRainSplash.square != nullptr) {
 DyingRainSplash.square.getProperties().UnSet(IsoFlagType.HasRainSplashes);
 DyingRainSplash.square.setRainSplash(nullptr);
 DyingRainSplash.square = nullptr;
 }

 RainSplashStack.remove(DyingRainSplash);
 NumActiveRainSplashes--;
 RainSplashReuseStack.push(DyingRainSplash);
 }

 static void SetPlayerLocation(int playerIndex, IsoGridSquare PlayerCurrentSquare) {
 PlayerOldLocation[playerIndex] = PlayerLocation[playerIndex];
 PlayerLocation[playerIndex] = PlayerCurrentSquare;
 if (PlayerOldLocation[playerIndex] != PlayerLocation[playerIndex]) {
 PlayerMoved = true;
 }
 }

 static bool isRaining() {
 return ClimateManager.getInstance().isRaining();
 }

 static void stopRaining() {
 stopRain = true;
 randRain = randRainMax;
 RainDesiredIntensity = 0.0F;
 if (GameServer.bServer) {
 GameServer.stopRain();
 }

 LuaEventManager.triggerEvent("OnRainStop");
 }

 static void startRaining() {
 }

 static void StartRaindrop(IsoCell cell, IsoGridSquare gridSquare, bool CanSee) {
 if (!gridSquare.getProperties().Is(IsoFlagType.HasRaindrop) {
 IsoRaindrop raindrop = nullptr;
 if (!RaindropReuseStack.empty()) {
 if (CanSee) {
 if (gridSquare.getRainDrop() != nullptr) {
 return;
 }

 raindrop = RaindropReuseStack.pop();
 raindrop.Reset(gridSquare, CanSee);
 gridSquare.setRainDrop(raindrop);
 }
 } else if (CanSee) {
 if (gridSquare.getRainDrop() != nullptr) {
 return;
 }

 raindrop = new IsoRaindrop(cell, gridSquare, CanSee);
 gridSquare.setRainDrop(raindrop);
 }
 }
 }

 static void StartRainSplash(IsoCell cell, IsoGridSquare gridSquare, bool CanSee) {
 }

 static void Update() {
 IsRaining = ClimateManager.getInstance().isRaining();
 RainIntensity = IsRaining ? ClimateManager.getInstance().getPrecipitationIntensity() : 0.0F;
 if (IsoPlayer.getInstance() != nullptr) {
 if (IsoPlayer.getInstance().getCurrentSquare() != nullptr) {
 if (!GameServer.bServer) {
 AddSplashes();
 }
 }
 }
 }

 static void UpdateServer() {
 }

 static void setRandRainMax(int pRandRainMax) {
 randRainMax = pRandRainMax;
 randRain = randRainMax;
 }

 static void setRandRainMin(int pRandRainMin) {
 randRainMin = pRandRainMin;
 }

 static bool inBounds(IsoGridSquare sq) {
 if (sq.empty()) {
 return false;
 } else {
 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr && PlayerLocation[int0] != nullptr) {
 if (sq.getX() < PlayerLocation[int0].getX() - RainRadius || sq.getX() >= PlayerLocation[int0].getX() + RainRadius) {
 return true;
 }

 if (sq.getY() < PlayerLocation[int0].getY() - RainRadius || sq.getY() >= PlayerLocation[int0].getY() + RainRadius) {
 return true;
 }
 }
 }

 return false;
 }
 }

 static void RemoveAllOn(IsoGridSquare sq) {
 if (sq.getRainDrop() != nullptr) {
 RemoveRaindrop(sq.getRainDrop());
 }

 if (sq.getRainSplash() != nullptr) {
 RemoveRainSplash(sq.getRainSplash());
 }
 }

 static float getRainIntensity() {
 return ClimateManager.getInstance().getPrecipitationIntensity();
 }

 static void removeAll() {
 for (int int0 = RainSplashStack.size() - 1; int0 >= 0; int0--) {
 IsoRainSplash rainSplash = RainSplashStack.get(int0);
 RemoveRainSplash(rainSplash);
 }

 for (int int1 = RaindropStack.size() - 1; int1 >= 0; int1--) {
 IsoRaindrop raindrop = RaindropStack.get(int1);
 RemoveRaindrop(raindrop);
 }

 RaindropStack.clear();
 RainSplashStack.clear();
 NumActiveRainSplashes = 0;
 NumActiveRaindrops = 0;
 }

 static bool interruptSleep(IsoPlayer player) {
 if (player.isAsleep() && player.isOutside() && player.getBed() != nullptr && !player.getBed().getName() == "Tent")) {
 IsoObject object = player.getBed();
 if (object.getCell().getGridSquare((double)object.getX(), (double)object.getY(), (double)(object.getZ() + 1.0F) == nullptr
 || object.getCell().getGridSquare((double)object.getX(), (double)object.getY(), (double)(object.getZ() + 1.0F).getFloor() == nullptr) {
 return true;
 }
 }

 return false;
 }
}
} // namespace objects
} // namespace iso
} // namespace zombie
