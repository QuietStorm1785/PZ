#pragma once
#include <mutex>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/erosion/ErosionMain.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/iso/weather/ClimateManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes.h"
#include "zombie/network/ServerOptions.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/SpeedControls.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/PZCalendar.h"
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

/**
 * Tracks both in-game time and real world time. This class is very old and so
 * has a lot of random/deprecated functionality.
 */
class GameTime {
public:
 /**
 * Because of how Kahlua exposes static fields, when accessed from Lua, this
 * will return a stale GameTime object that does not hold the correct game
 * state. Lua mods should always use getGameTime() or GameTime.getInstance()
 * instead of this field.
 */
 static GameTime instance = new GameTime();
 static const float MULTIPLIER = 0.8F;
 static long serverTimeShift = 0L;
 static bool serverTimeShiftIsSet = false;
 static bool isUTest = false;
 float TimeOfDay = 9.0F;
 int NightsSurvived = 0;
 PZCalendar Calender;
 float FPSMultiplier = 1.0F;
 float Moon = 0.0F;
 float ServerTimeOfDay;
 float ServerLastTimeOfDay;
 int ServerNewDays;
 float lightSourceUpdate = 0.0F;
 float multiplierBias = 1.0F;
 float LastLastTimeOfDay = 0.0F;
 int HelicopterTime1Start = 0;
 float PerObjectMultiplier = 1.0F;
 int HelicopterTime1End = 0;
 int HelicopterDay1 = 0;
 float Ambient = 0.9F;
 float AmbientMax = 1.0F;
 float AmbientMin = 0.24F;
 int Day = 22;
 int StartDay = 22;
 float MaxZombieCountStart = 750.0F;
 float MinZombieCountStart = 750.0F;
 float MaxZombieCount = 750.0F;
 float MinZombieCount = 750.0F;
 int Month = 7;
 int StartMonth = 7;
 float StartTimeOfDay = 9.0F;
 float ViewDistMax = 42.0F;
 float ViewDistMin = 19.0F;
 int Year = 2012;
 int StartYear = 2012;
 double HoursSurvived = 0.0;
 float MinutesPerDayStart = 30.0F;
 float MinutesPerDay = this->MinutesPerDayStart;
 float LastTimeOfDay;
 int TargetZombies = (int)this->MinZombieCountStart;
 bool RainingToday = true;
 bool bGunFireEventToday = false;
private
 float[] GunFireTimes = new float[5];
 int NumGunFireEvents = 1;
 long lastPing = 0L;
 long lastClockSync = 0L;
 KahluaTable table = nullptr;
 int minutesMod = -1;
 bool thunderDay = true;
 bool randomAmbientToday = true;
 float Multiplier = 1.0F;
 int dusk = 3;
 int dawn = 12;
 float NightMin = 0.0F;
 float NightMax = 1.0F;
 long minutesStamp = 0L;
 long previousMinuteStamp = 0L;

public
 GameTime() {
 serverTimeShift = 0L;
 serverTimeShiftIsSet = false;
 }

 static GameTime getInstance() { return instance; }

 static void setInstance(GameTime aInstance) { instance = aInstance; }

 static void syncServerTime(long timeClientSend, long timeServer,
 long timeClientReceive) {
 long long0 = timeClientReceive - timeClientSend;
 long long1 = timeServer - timeClientReceive + long0 / 2L;
 long long2 = serverTimeShift;
 if (!serverTimeShiftIsSet) {
 serverTimeShift = long1;
 } else {
 serverTimeShift = serverTimeShift + (long1 - serverTimeShift) / 100L;
 }

 long long3 = 10000000L;
 if (Math.abs(serverTimeShift - long2) > long3) {
 sendTimeSync();
 } else {
 serverTimeShiftIsSet = true;
 }
 }

 static long getServerTime() {
 if (isUTest) {
 return System.nanoTime() + serverTimeShift;
 } else if (GameServer.bServer) {
 return System.nanoTime();
 } else if (GameClient.bClient) {
 return !serverTimeShiftIsSet ? 0L : System.nanoTime() + serverTimeShift;
 } else {
 return 0L;
 }
 }

 static long getServerTimeMills() {
 return TimeUnit.NANOSECONDS.toMillis(getServerTime());
 }

 static bool getServerTimeShiftIsSet() { return serverTimeShiftIsSet; }

 static void setServerTimeShift(long tshift) {
 isUTest = true;
 serverTimeShift = tshift;
 serverTimeShiftIsSet = true;
 }

 static void sendTimeSync() {
 ByteBufferWriter byteBufferWriter = GameClient.connection.startPacket();
 PacketTypes.PacketType.TimeSync.doPacket(byteBufferWriter);
 byteBufferWriter.putLong(System.nanoTime());
 byteBufferWriter.putFloat(instance.Multiplier);
 PacketTypes.PacketType.TimeSync.send(GameClient.connection);
 }

 static void receiveTimeSync(ByteBuffer bb, UdpConnection connection) {
 if (GameServer.bServer) {
 long long0 = bb.getLong();
 long long1 = System.nanoTime();
 float float0 = bb.getFloat();
 if (GameServer.bServer && !GameServer.bFastForward) {
 if (instance.Multiplier != float0) {
 connection.validator.failTimeMultiplier(float0);
 } else {
 connection.validator.successTimeMultiplier();
 }
 }

 ByteBufferWriter byteBufferWriter = connection.startPacket();
 PacketTypes.PacketType.TimeSync.doPacket(byteBufferWriter);
 byteBufferWriter.putLong(long0);
 byteBufferWriter.putLong(long1);
 PacketTypes.PacketType.TimeSync.send(connection);
 }

 if (GameClient.bClient) {
 long long2 = bb.getLong();
 long long3 = bb.getLong();
 long long4 = System.nanoTime();
 syncServerTime(long2, long3, long4);
 DebugLog.printServerTime = true;
 }
 }

 /**
 * Number of real seconds since the last tick.
 */
 float getRealworldSecondsSinceLastUpdate() {
 return 0.016666668F * this->FPSMultiplier;
 }

 /**
 * Number of real world seconds since the last tick, multiplied by game speed.
 */
 float getMultipliedSecondsSinceLastUpdate() {
 return 0.016666668F * this->getUnmoddedMultiplier();
 }

 /**
 * Number of in-game seconds passed since the last tick.
 */
 float getGameWorldSecondsSinceLastUpdate() {
 float float0 = 1440.0F / this->getMinutesPerDay();
 return this->getTimeDelta() * float0;
 }

 /**
 * Returns the number of days in a month.
 *
 * @param year Year of the month. Required to account for leap years.
 * @param month 0 indexed month of the year.
 * @return Number of days in the month.
 */
 int daysInMonth(int year, int month) {
 if (this->Calender.empty()) {
 this->updateCalendar(this->getYear(), this->getMonth(), this->getDay(),
 (int)this->getTimeOfDay(), this->getMinutes());
 }

 int[] ints = new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
 ints[1] += this->getCalender().isLeapYear(year) ? 1 : 0;
 return ints[month];
 }

 /**
 * Returns the time survived string to show on death for a player.
 *
 * @param playerObj Player to get the string for.
 * @return Time survived string.
 */
 std::string getDeathString(IsoPlayer playerObj) {
 return Translator.getText("IGUI_Gametime_SurvivedFor",
 this->getTimeSurvived(playerObj);
 }

 /**
 * The number of full days survived by the current local player who has
 * survived the longest modulo 30.
 * @return Highest number of days survived by a current local player
 * modulo 30.
 */
 int getDaysSurvived() {
 float float0 = 0.0F;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 float0 = Math.max(float0, (float)player.getHoursSurvived());
 }
 }

 int int1 = (int)float0 / 24;
 return int1 % 30;
 }

 /**
 * Gets a string that describes how long a player has survived for.
 *
 * @param playerObj Player to get the string for.
 * @return String describing how long the player has survived.
 */
 std::string getTimeSurvived(IsoPlayer playerObj) {
 void *object = "";
 float float0 = (float)playerObj.getHoursSurvived();
 int integer0 = (int)float0 % 24;
 int integer1 = (int)float0 / 24;
 int integer2 = integer1 / 30;
 integer1 = integer1 % 30;
 int integer3 = integer2 / 12;
 integer2 = integer2 % 12;
 std::string string0 = Translator.getText("IGUI_Gametime_day");
 std::string string1 = Translator.getText("IGUI_Gametime_year");
 std::string string2 = Translator.getText("IGUI_Gametime_hour");
 std::string string3 = Translator.getText("IGUI_Gametime_month");
 if (integer3 != 0) {
 if (integer3 > 1) {
 string1 = Translator.getText("IGUI_Gametime_years");
 }

 object = object + integer3 + " " + string1;
 }

 if (integer2 != 0) {
 if (integer2 > 1) {
 string3 = Translator.getText("IGUI_Gametime_months");
 }

 if (object.length() > 0) {
 object = object + ", ";
 }

 object = object + integer2 + " " + string3;
 }

 if (integer1 != 0) {
 if (integer1 > 1) {
 string0 = Translator.getText("IGUI_Gametime_days");
 }

 if (object.length() > 0) {
 object = object + ", ";
 }

 object = object + integer1 + " " + string0;
 }

 if (integer0 != 0) {
 if (integer0 > 1) {
 string2 = Translator.getText("IGUI_Gametime_hours");
 }

 if (object.length() > 0) {
 object = object + ", ";
 }

 object = object + integer0 + " " + string2;
 }

 if (object.trim().length() == 0) {
 int int0 = (int)(float0 * 60.0F);
 int int1 = (int)(float0 * 60.0F * 60.0F) - int0 * 60;
 object = int0 + " " + Translator.getText("IGUI_Gametime_minutes") + ", " +
 int1 + " " + Translator.getText("IGUI_Gametime_secondes");
 }

 return (String)object;
 }

 /**
 * Returns a string describing how many zombies a player has killed.
 *
 * @param playerObj Player to get the string for.
 * @return String describing how many zombies the player has killed.
 */
 std::string getZombieKilledText(IsoPlayer playerObj) {
 int int0 = playerObj.getZombieKills();
 if (int0 == 0 || int0 > 1) {
 return Translator.getText("IGUI_Gametime_zombiesCount", int0);
 } else {
 return int0 = = 1 ? Translator.getText("IGUI_Gametime_zombieCount", int0)
 : nullptr;
 }
 }

 /**
 * Returns a string describing the current game mode.
 * @return String describing the current game mode.
 */
 std::string getGameModeText() {
 std::string string0 =
 Translator.getTextOrNull("IGUI_Gametime_" + Core.GameMode);
 if (string0.empty()) {
 string0 = Core.GameMode;
 }

 std::string string1 =
 Translator.getTextOrNull("IGUI_Gametime_GameMode", string0);
 if (string1.empty()) {
 string1 = "Game mode: " + string0;
 }

 if (Core.bDebug) {
 string1 = string1 + " (DEBUG)";
 }

 return string1;
 }

 void init() {
 this->setDay(this->getStartDay());
 this->setTimeOfDay(this->getStartTimeOfDay());
 this->setMonth(this->getStartMonth());
 this->setYear(this->getStartYear());
 if (SandboxOptions.instance.Helicopter.getValue() != 1) {
 this->HelicopterDay1 = Rand.Next(6, 10);
 this->HelicopterTime1Start = Rand.Next(9, 19);
 this->HelicopterTime1End = this->HelicopterTime1Start + Rand.Next(4) + 1;
 }

 this->setMinutesStamp();
 }

 /**
 * Interpolates between two values by a given amount.
 *
 * @param start Value to interpolation from.
 * @param end Value to interpolate to.
 * @param delta 0-1 amount to interpolate between the two values.
 * @return Interpolated value.
 */
 float Lerp(float start, float end, float delta) {
 if (delta < 0.0F) {
 delta = 0.0F;
 }

 if (delta >= 1.0F) {
 delta = 1.0F;
 }

 float float0 = end - start;
 float float1 = float0 * delta;
 return start + float1;
 }

 /**
 * Removes a specific number of zombies from the world.
 *
 * @param i Number of zombies to remove.
 */
 void RemoveZombiesIndiscriminate(int i) {
 if (i != 0) {
 for (int int0 = 0;
 int0 < IsoWorld.instance.CurrentCell.getZombieList().size();
 int0++) {
 IsoZombie zombie0 =
 IsoWorld.instance.CurrentCell.getZombieList().get(0);
 IsoWorld.instance.CurrentCell.getZombieList().remove(int0);
 IsoWorld.instance.CurrentCell.getRemoveList().add(zombie0);
 zombie0.getCurrentSquare().getMovingObjects().remove(zombie0);
 int0--;
 if (--i == 0 ||
 IsoWorld.instance.CurrentCell.getZombieList().empty()) {
 return;
 }
 }
 }
 }

 /**
 * Interpolates between two values based on the current time of day.
 *
 * @param startVal Value to interpolate from.
 * @param endVal Value to interpoalte to.
 * @param startTime Time of day in hours to start interpolation. If the
 * current time is before this, startVal is returned.
 * @param endTime Time of day in hours to end interpolation. If the current
 * time is after this, endVal is returned. If this is less than startTime, it
 * is considered a time in the next day.
 * @return Interpolated value based on the current time.
 */
 float TimeLerp(float startVal, float endVal, float startTime, float endTime) {
 float float0 = getInstance().getTimeOfDay();
 if (endTime < startTime) {
 endTime += 24.0F;
 }

 bool boolean0 = false;
 if (float0 > endTime && float0 > startTime ||
 float0 < endTime && float0 < startTime) {
 startTime += 24.0F;
 boolean0 = true;
 startTime = endTime;
 endTime = startTime;
 if (float0 < startTime) {
 float0 += 24.0F;
 }
 }

 float float1 = endTime - startTime;
 float float2 = float0 - startTime;
 float float3 = 0.0F;
 if (float2 > float1) {
 float3 = 1.0F;
 }

 if (float2 < float1 && float2 > 0.0F) {
 float3 = float2 / float1;
 }

 if (boolean0) {
 float3 = 1.0F - float3;
 }

 float float4 = 0.0F;
 float3 = (float3 - 0.5F) * 2.0F;
 if (float3 < 0.0) {
 float4 = -1.0F;
 } else {
 float4 = 1.0F;
 }

 float3 = Math.abs(float3);
 float3 = 1.0F - float3;
 float3 = (float)Math.pow(float3, 8.0);
 float3 = 1.0F - float3;
 float3 *= float4;
 float3 = float3 * 0.5F + 0.5F;
 return this->Lerp(startVal, endVal, float3);
 }

 /**
 * Delta between the default and current day length (as configured in the
 * sandbox options). When using a time delta, multiply by this as well to make
 * the value increase at a fixed game-time rate rather than real time.
 * @return The default day length is considered by this method to be 30
 * minutes, so a 0.33 delta is expected on default settings, not 1.
 */
 float getDeltaMinutesPerDay() {
 return this->MinutesPerDayStart / this->MinutesPerDay;
 }

 /**
 * @deprecated
 */
 float getNightMin() { return 1.0F - this->NightMin; }

 /**
 * @deprecated
 */
 void setNightMin(float min) { this->NightMin = 1.0F - min; }

 /**
 * @deprecated
 */
 float getNightMax() { return 1.0F - this->NightMax; }

 /**
 * @deprecated
 */
 void setNightMax(float max) { this->NightMax = 1.0F - max; }

 int getMinutes() {
 return (int)((this->getTimeOfDay() - (int)this->getTimeOfDay()) * 60.0F);
 }

 /**
 * @deprecated
 */
 void setMoon(float moon) { this->Moon = moon; }

 void update(bool bSleeping) {
 long long0 = System.currentTimeMillis();
 if (GameClient.bClient &&
 (this->lastPing == 0L || long0 - this->lastPing > 10000L) {
 sendTimeSync();
 this->lastPing = long0;
 }

 short short0 = 9000;
 if (SandboxOptions.instance.MetaEvent.getValue() == 1) {
 short0 = -1;
 }

 if (SandboxOptions.instance.MetaEvent.getValue() == 3) {
 short0 = 6000;
 }

 if (!GameClient.bClient && this->randomAmbientToday && short0 != -1 &&
 Rand.Next(Rand.AdjustForFramerate(short0) == 0 && !isGamePaused()) {
 AmbientStreamManager.instance.addRandomAmbient();
 this->randomAmbientToday =
 SandboxOptions.instance.MetaEvent.getValue() == 3 &&
 Rand.Next(3) == 0;
 }

 if (GameServer.bServer && UIManager.getSpeedControls() != nullptr) {
 UIManager.getSpeedControls().SetCurrentGameSpeed(1);
 }

 if (GameServer.bServer || !GameClient.bClient) {
 if (this->bGunFireEventToday) {
 for (int int0 = 0; int0 < this->NumGunFireEvents; int0++) {
 if (this->TimeOfDay > this->GunFireTimes[int0] &&
 this->LastLastTimeOfDay < this->GunFireTimes[int0]) {
 AmbientStreamManager.instance.doGunEvent();
 }
 }
 }

 if (this->NightsSurvived == this->HelicopterDay1 &&
 this->TimeOfDay > this->HelicopterTime1Start &&
 this->TimeOfDay < this->HelicopterTime1End &&
 !IsoWorld.instance.helicopter.isActive() &&
 Rand.Next((int)(800.0F * this->getInvMultiplier())) == 0) {
 this->HelicopterTime1Start = (int)(this->HelicopterTime1Start + 0.5F);
 IsoWorld.instance.helicopter.pickRandomTarget();
 }

 if (this->NightsSurvived > this->HelicopterDay1 &&
 (SandboxOptions.instance.Helicopter.getValue() == 3 ||
 SandboxOptions.instance.Helicopter.getValue() == 4) {
 if (SandboxOptions.instance.Helicopter.getValue() == 3) {
 this->HelicopterDay1 = this->NightsSurvived + Rand.Next(10, 16);
 }

 if (SandboxOptions.instance.Helicopter.getValue() == 4) {
 this->HelicopterDay1 = this->NightsSurvived + Rand.Next(6, 10);
 }

 this->HelicopterTime1Start = Rand.Next(9, 19);
 this->HelicopterTime1End = this->HelicopterTime1Start + Rand.Next(4) + 1;
 }
 }

 int int1 = this->getHour();
 this->updateCalendar(
 this->getYear(), this->getMonth(), this->getDay(),
 (int)this->getTimeOfDay(),
 (int)((this->getTimeOfDay() - (int)this->getTimeOfDay()) * 60.0F);
 float float0 = this->getTimeOfDay();
 if (!isGamePaused()) {
 float float1 =
 1.0F / this->getMinutesPerDay() / 60.0F * this->getMultiplier() / 2.0F;
 if (Core.bLastStand) {
 float1 = 1.0F / this->getMinutesPerDay() / 60.0F *
 this->getUnmoddedMultiplier() / 2.0F;
 }

 this->setTimeOfDay(this->getTimeOfDay() + float1);
 if (this->getHour() != int1) {
 LuaEventManager.triggerEvent("EveryHours");
 }

 if (!GameServer.bServer) {
 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 IsoPlayer player0 = IsoPlayer.players[int2];
 if (player0 != nullptr && player0.isAlive()) {
 player0.setHoursSurvived(player0.getHoursSurvived() + float1);
 }
 }
 }

 if (GameServer.bServer) {
 std::vector arrayList0 = GameClient.instance.getPlayers();

 for (int int3 = 0; int3 < arrayList0.size(); int3++) {
 IsoPlayer player1 = (IsoPlayer)arrayList0.get(int3);
 player1.setHoursSurvived(player1.getHoursSurvived() + float1);
 }
 }

 if (GameClient.bClient) {
 std::vector arrayList1 = GameClient.instance.getPlayers();

 for (int int4 = 0; int4 < arrayList1.size(); int4++) {
 IsoPlayer player2 = (IsoPlayer)arrayList1.get(int4);
 if (player2 != nullptr && !player2.isDead() &&
 !player2.isLocalPlayer()) {
 player2.setHoursSurvived(player2.getHoursSurvived() + float1);
 }
 }
 }

 for (int int5 = 0; int5 < IsoPlayer.numPlayers; int5++) {
 IsoPlayer player3 = IsoPlayer.players[int5];
 if (player3 != nullptr) {
 if (player3.isAsleep()) {
 player3.setAsleepTime(player3.getAsleepTime() + float1);
 SleepingEvent.instance.update(player3);
 } else {
 player3.setAsleepTime(0.0F);
 }
 }
 }
 }

 if (!GameClient.bClient && float0 <= 7.0F && this->getTimeOfDay() > 7.0F) {
 this->setNightsSurvived(this->getNightsSurvived() + 1);
 this->doMetaEvents();
 }

 if (GameClient.bClient) {
 if (this->getTimeOfDay() >= 24.0F) {
 this->setTimeOfDay(this->getTimeOfDay() - 24.0F);
 }

 while (this->ServerNewDays > 0) {
 this->ServerNewDays--;
 this->setDay(this->getDay() + 1);
 if (this->getDay() >=
 this->daysInMonth(this->getYear(), this->getMonth())) {
 this->setDay(0);
 this->setMonth(this->getMonth() + 1);
 if (this->getMonth() >= 12) {
 this->setMonth(0);
 this->setYear(this->getYear() + 1);
 }
 }

 this->updateCalendar(this->getYear(), this->getMonth(), this->getDay(),
 (int)this->getTimeOfDay(), this->getMinutes());
 LuaEventManager.triggerEvent("EveryDays");
 }
 } else if (this->getTimeOfDay() >= 24.0F) {
 this->setTimeOfDay(this->getTimeOfDay() - 24.0F);
 this->setDay(this->getDay() + 1);
 if (this->getDay() >= this->daysInMonth(this->getYear(), this->getMonth())) {
 this->setDay(0);
 this->setMonth(this->getMonth() + 1);
 if (this->getMonth() >= 12) {
 this->setMonth(0);
 this->setYear(this->getYear() + 1);
 }
 }

 this->updateCalendar(this->getYear(), this->getMonth(), this->getDay(),
 (int)this->getTimeOfDay(), this->getMinutes());
 LuaEventManager.triggerEvent("EveryDays");
 if (GameServer.bServer) {
 GameServer.syncClock();
 this->lastClockSync = long0;
 }
 }

 float float2 = this->Moon * 20.0F;
 if (!ClimateManager.getInstance().getThunderStorm().isModifyingNight()) {
 this->setAmbient(this->TimeLerp(this->getAmbientMin(), this->getAmbientMax(),
 this->getDusk(), this->getDawn()));
 }

 if (Core.getInstance().RenderShader != nullptr &&
 Core.getInstance().getOffscreenBuffer() != nullptr) {
 this->setNightTint(0.0F);
 }

 this->setMinutesStamp();
 int int6 = (int)((this->getTimeOfDay() - (int)this->getTimeOfDay()) * 60.0F);
 if (int6 / 10 != this->minutesMod) {
 IsoPlayer[] players = IsoPlayer.players;

 for (int int7 = 0; int7 < players.length; int7++) {
 IsoPlayer player4 = players[int7];
 if (player4 != nullptr) {
 player4.dirtyRecalcGridStackTime = 1.0F;
 }
 }

 ErosionMain.EveryTenMinutes();
 ClimateManager.getInstance().updateEveryTenMins();
 getInstance().updateRoomLight();
 LuaEventManager.triggerEvent("EveryTenMinutes");
 this->minutesMod = int6 / 10;
 ZomboidRadio.getInstance().UpdateScripts(this->getHour(), int6);
 }

 if (this->previousMinuteStamp != this->minutesStamp) {
 LuaEventManager.triggerEvent("EveryOneMinute");
 this->previousMinuteStamp = this->minutesStamp;
 }

 if (GameServer.bServer &&
 (long0 - this->lastClockSync > 10000L || GameServer.bFastForward) {
 GameServer.syncClock();
 this->lastClockSync = long0;
 }
 }

 void updateRoomLight() {}

 void setMinutesStamp() {
 this->minutesStamp = (long)this->getWorldAgeHours() * 60L + this->getMinutes();
 }

 /**
 * Number of minutes since the world was created. Has the same inaccuracy as
 * getWorldAgeHours().
 * @return Number of minutes since the world was created.
 */
 long getMinutesStamp() { return this->minutesStamp; }

 /**
 * @deprecated
 */
 bool getThunderStorm() {
 return ClimateManager.getInstance().getIsThunderStorming();
 }

 void doMetaEvents() {
 uint8_t byte0 = 3;
 if (SandboxOptions.instance.MetaEvent.getValue() == 1) {
 byte0 = -1;
 }

 if (SandboxOptions.instance.MetaEvent.getValue() == 3) {
 byte0 = 2;
 }

 this->bGunFireEventToday = byte0 != -1 && Rand.Next((int)byte0) == 0;
 if (this->bGunFireEventToday) {
 this->NumGunFireEvents = 1;

 for (int int0 = 0; int0 < this->NumGunFireEvents; int0++) {
 this->GunFireTimes[int0] = Rand.Next(18000) / 1000.0F + 7.0F;
 }
 }

 this->randomAmbientToday = true;
 }

 /**
 * @return the Ambient
 */
 float getAmbient() { return ClimateManager.getInstance().getAmbient(); }

 /**
 *
 * @param _Ambient the Ambient to set
 * @deprecated
 */
 void setAmbient(float _Ambient) { this->Ambient = _Ambient; }

 /**
 * @return the AmbientMax
 * @deprecated
 */
 float getAmbientMax() { return this->AmbientMax; }

 /**
 *
 * @param _AmbientMax the AmbientMax to set
 * @deprecated
 */
 void setAmbientMax(float _AmbientMax) {
 _AmbientMax = Math.min(1.0F, _AmbientMax);
 _AmbientMax = Math.max(0.0F, _AmbientMax);
 this->AmbientMax = _AmbientMax;
 }

 /**
 * @return the AmbientMin
 * @deprecated
 */
 float getAmbientMin() { return this->AmbientMin; }

 /**
 *
 * @param _AmbientMin the AmbientMin to set
 * @deprecated
 */
 void setAmbientMin(float _AmbientMin) {
 _AmbientMin = Math.min(1.0F, _AmbientMin);
 _AmbientMin = Math.max(0.0F, _AmbientMin);
 this->AmbientMin = _AmbientMin;
 }

 /**
 * Current day of the month in the game world.
 * @return 0 indexed day of the month.
 */
 int getDay() { return this->Day; }

 /**
 * Current day of the month in the game world, plus 1.
 * @return 1 indexed day of the month.
 */
 int getDayPlusOne() { return this->Day + 1; }

 /**
 * Current day of the month in the game world.
 *
 * @param _Day 0 indexed day of the month.
 */
 void setDay(int _Day) { this->Day = _Day; }

 /**
 * Day of the month the game started on as defined by sandbox options. The
 * value will change if sandbox options are changed, so getNightsSurvived() or
 * getWorldAgeHours() should be used instead to determine the age of the
 * world.
 * @return 0 indexed day of the month the game started on.
 */
 int getStartDay() { return this->StartDay; }

 /**
 * Day of the month the game started on as defined by sandbox options.
 * Changing this does not affect the age of the world.
 *
 * @param _StartDay 0 indexed day of the month the game started on.
 */
 void setStartDay(int _StartDay) { this->StartDay = _StartDay; }

 /**
 * @return the MaxZombieCountStart
 * @deprecated
 */
 float getMaxZombieCountStart() noexcept{ return 0.0F; }

 /**
 *
 * @param _MaxZombieCountStart the MaxZombieCountStart to set
 * @deprecated
 */
 void setMaxZombieCountStart(float _MaxZombieCountStart) {
 this->MaxZombieCountStart = _MaxZombieCountStart;
 }

 /**
 * @return the MinZombieCountStart
 * @deprecated
 */
 float getMinZombieCountStart() noexcept{ return 0.0F; }

 /**
 *
 * @param _MinZombieCountStart the MinZombieCountStart to set
 * @deprecated
 */
 void setMinZombieCountStart(float _MinZombieCountStart) {
 this->MinZombieCountStart = _MinZombieCountStart;
 }

 /**
 * @return the MaxZombieCount
 * @deprecated
 */
 float getMaxZombieCount() noexcept{ return this->MaxZombieCount; }

 /**
 *
 * @param _MaxZombieCount the MaxZombieCount to set
 * @deprecated
 */
 void setMaxZombieCount(float _MaxZombieCount) {
 this->MaxZombieCount = _MaxZombieCount;
 }

 /**
 * @return the MinZombieCount
 * @deprecated
 */
 float getMinZombieCount() noexcept{ return this->MinZombieCount; }

 /**
 *
 * @param _MinZombieCount the MinZombieCount to set
 * @deprecated
 */
 void setMinZombieCount(float _MinZombieCount) {
 this->MinZombieCount = _MinZombieCount;
 }

 /**
 * Current month of the year in the game world.
 * @return 0 indexed month of the year.
 */
 int getMonth() { return this->Month; }

 /**
 * Current month of the year in the game world.
 *
 * @param _Month 0 indexed month of the year.
 */
 void setMonth(int _Month) { this->Month = _Month; }

 /**
 * Month of the year the game started on as defined by sandbox options. The
 * value will change if sandbox options are changed, so getNightsSurvived() or
 * getWorldAgeHours() should be used instead to determine the age of the
 * world.
 * @return 0 indexed month of the year the game started on.
 */
 int getStartMonth() { return this->StartMonth; }

 /**
 * Month of the year the game started on as defined by sandbox options.
 * Changing this does not affect the age of the world.
 *
 * @param _StartMonth the StartMonth to set
 */
 void setStartMonth(int _StartMonth) { this->StartMonth = _StartMonth; }

 /**
 * @return the NightTint
 * @deprecated
 */
 float getNightTint() {
 return ClimateManager.getInstance().getNightStrength();
 }

 /**
 *
 * @param NightTint the NightTint to set
 * @deprecated
 */
 void setNightTint(float NightTint) {}

 /**
 * @return the NightTint
 * @deprecated
 */
 float getNight() { return ClimateManager.getInstance().getNightStrength(); }

 /**
 *
 * @param NightTint the NightTint to set
 * @deprecated
 */
 void setNight(float NightTint) {}

 /**
 * @return the TimeOfDay
 */
 float getTimeOfDay() { return this->TimeOfDay; }

 /**
 *
 * @param _TimeOfDay the TimeOfDay to set
 */
 void setTimeOfDay(float _TimeOfDay) { this->TimeOfDay = _TimeOfDay; }

 /**
 * Time of day the game started on as defined by sandbox options. The value
 * will change if sandbox options are changed, so getNightsSurvived() or
 * getWorldAgeHours() should be used instead to determine the age of the
 * world.
 * @return The time of day in hours the game started at.
 */
 float getStartTimeOfDay() { return this->StartTimeOfDay; }

 /**
 * Time of day the game started on as defined by sandbox options. The value
 * will change if sandbox options are changed, so getNightsSurvived() or
 * getWorldAgeHours() should be used instead to determine the age of the
 * world. Changing this does not affect the age of the world.
 *
 * @param _StartTimeOfDay The time of day in hours the game started at.
 */
 void setStartTimeOfDay(float _StartTimeOfDay) {
 this->StartTimeOfDay = _StartTimeOfDay;
 }

 /**
 * @return the ViewDist
 */
 float getViewDist() { return ClimateManager.getInstance().getViewDistance(); }

 /**
 * @return the ViewDistMax
 */
 float getViewDistMax() { return this->ViewDistMax; }

 /**
 *
 * @param _ViewDistMax the ViewDistMax to set
 */
 void setViewDistMax(float _ViewDistMax) { this->ViewDistMax = _ViewDistMax; }

 /**
 * @return the ViewDistMin
 * @deprecated
 */
 float getViewDistMin() { return this->ViewDistMin; }

 /**
 *
 * @param _ViewDistMin the ViewDistMin to set
 * @deprecated
 */
 void setViewDistMin(float _ViewDistMin) { this->ViewDistMin = _ViewDistMin; }

 /**
 * Current year in the game world.
 * @return Current year in the game world.
 */
 int getYear() { return this->Year; }

 /**
 * Current year in the game world.
 *
 * @param _Year Current year in the game world.
 */
 void setYear(int _Year) { this->Year = _Year; }

 /**
 * Year the game started on.
 * @return Year the game started on.
 */
 int getStartYear() { return this->StartYear; }

 /**
 * Year the game started on. Changing this does not affect the age of the
 * world.
 *
 * @param _StartYear Year the game started on.
 */
 void setStartYear(int _StartYear) { this->StartYear = _StartYear; }

 /**
 * Gets the number of nights that have passed since the save was created. 7am
 * is considered the end of a night.
 * @return Number of nights since game start.
 */
 int getNightsSurvived() { return this->NightsSurvived; }

 /**
 * Number of nights since the game began. A night is survived when the time
 * passes 7am.
 *
 * @param _NightsSurvived the NightsSurvived to set
 */
 void setNightsSurvived(int _NightsSurvived) {
 this->NightsSurvived = _NightsSurvived;
 }

 /**
 * Gets the age of the world from the start of the game in hours. The value
 * can be slightly off from the true value depending on game settings, as it
 * considers every 7am passing to be a 24 hour period, however the game does
 * not by default start at 7am. The true number of hours can be calculated by
 * subtracting (getStartTimeOfDay() - 7). However, the uncorrected value is
 * still suitable as a timestamp, as the offset is consistent.
 * @return Age of the world in hours.
 */
 double getWorldAgeHours() {
 float float0 = this->getNightsSurvived() * 24;
 if (this->getTimeOfDay() >= 7.0F) {
 float0 += this->getTimeOfDay() - 7.0F;
 } else {
 float0 += this->getTimeOfDay() + 17.0F;
 }

 return float0;
 }

 /**
 * @return the HoursSurvived
 * @deprecated
 */
 double getHoursSurvived() {
 DebugLog.log("GameTime.getHoursSurvived() has no meaning, use "
 "IsoPlayer.getHourSurvived() instead");
 return this->HoursSurvived;
 }

 /**
 *
 * @param _HoursSurvived the HoursSurvived to set
 * @deprecated
 */
 void setHoursSurvived(double _HoursSurvived) {
 DebugLog.log("GameTime.getHoursSurvived() has no meaning, use "
 "IsoPlayer.getHourSurvived() instead");
 this->HoursSurvived = _HoursSurvived;
 }

 int getHour() {
 double double0 = Math.floor(this->getTimeOfDay() * 3600.0F);
 return (int)Math.floor(double0 / 3600.0);
 }

 /**
 * @return the Calender
 */
 PZCalendar getCalender() {
 this->updateCalendar(
 this->getYear(), this->getMonth(), this->getDay(),
 (int)this->getTimeOfDay(),
 (int)((this->getTimeOfDay() - (int)this->getTimeOfDay()) * 60.0F);
 return this->Calender;
 }

 /**
 *
 * @param _Calender the Calender to set
 */
 void setCalender(PZCalendar _Calender) { this->Calender = _Calender; }

 void updateCalendar(int year, int month, int dayOfMonth, int hourOfDay,
 int minute) {
 if (this->Calender.empty()) {
 this->Calender = new PZCalendar(std::make_unique<GregorianCalendar>());
 }

 this->Calender.set(year, month, dayOfMonth, hourOfDay, minute);
 }

 /**
 * @return the MinutesPerDay
 */
 float getMinutesPerDay() { return this->MinutesPerDay; }

 /**
 *
 * @param _MinutesPerDay the MinutesPerDay to set
 */
 void setMinutesPerDay(float _MinutesPerDay) {
 this->MinutesPerDay = _MinutesPerDay;
 }

 /**
 * @return the LastTimeOfDay
 */
 float getLastTimeOfDay() { return this->LastTimeOfDay; }

 /**
 *
 * @param _LastTimeOfDay the LastTimeOfDay to set
 */
 void setLastTimeOfDay(float _LastTimeOfDay) {
 this->LastTimeOfDay = _LastTimeOfDay;
 }

 /**
 *
 * @param _TargetZombies the TargetZombies to set
 * @deprecated
 */
 void setTargetZombies(int _TargetZombies) {
 this->TargetZombies = _TargetZombies;
 }

 /**
 * @return the RainingToday
 * @deprecated
 */
 bool isRainingToday() { return this->RainingToday; }

 /**
 * Number of real world seconds since the last tick, multiplied by game speed.
 * Also multiplied by 48 for some reason.
 * @return the Multiplier
 */
 float getMultiplier() {
 if (!GameServer.bServer && !GameClient.bClient &&
 IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersAsleep()) {
 return 200.0F * (30.0F / PerformanceSettings.getLockFPS());
 } else {
 float float0 = 1.0F;
 if (GameServer.bServer && GameServer.bFastForward) {
 float0 =
 (float)ServerOptions.instance.FastForwardMultiplier.getValue() /
 this->getDeltaMinutesPerDay();
 } else if (GameClient.bClient && GameClient.bFastForward) {
 float0 =
 (float)ServerOptions.instance.FastForwardMultiplier.getValue() /
 this->getDeltaMinutesPerDay();
 }

 float0 *= this->Multiplier;
 float0 *= this->FPSMultiplier;
 float0 *= this->multiplierBias;
 float0 *= this->PerObjectMultiplier;
 if (DebugOptions.instance.GameTimeSpeedQuarter.getValue()) {
 float0 *= 0.25F;
 }

 if (DebugOptions.instance.GameTimeSpeedHalf.getValue()) {
 float0 *= 0.5F;
 }

 return float0 * 0.8F;
 }
 }

 /**
 * Number of real world seconds since the last tick, multiplied by game speed.
 */
 float getTimeDelta() {
 return this->getMultiplier() / (0.8F * this->multiplierBias) / 60.0F;
 }

 static float getAnimSpeedFix() { return 0.8F; }

 /**
 * The multiplier scales the game simulation speed. getTrueMultiplier() can be
 * used to retrieve this value. getMultiplier() does not return this value.
 *
 * @param _Multiplier the Multiplier to set
 */
 void setMultiplier(float _Multiplier) { this->Multiplier = _Multiplier; }

 /**
 * Delta based on the target framerate rather than the actual framerate.
 * Unclear purpose. Probably shouldn't be used.
 */
 float getServerMultiplier() {
 float float0 = 10.0F / GameWindow.averageFPS /
 (PerformanceSettings.ManualFrameSkips + 1);
 float float1 = this->Multiplier * float0;
 float1 *= 0.5F;
 if (!GameServer.bServer && !GameClient.bClient &&
 IsoPlayer.getInstance() != nullptr && IsoPlayer.allPlayersAsleep()) {
 return 200.0F * (30.0F / PerformanceSettings.getLockFPS());
 } else {
 float1 *= 1.6F;
 return float1 * this->multiplierBias;
 }
 }

 /**
 * Number of real world seconds since the last tick, multiplied by game speed.
 */
 float getUnmoddedMultiplier() {
 return !GameServer.bServer && !GameClient.bClient &&
 IsoPlayer.getInstance() != nullptr &&
 IsoPlayer.allPlayersAsleep()
 ? 200.0F * (30.0F / PerformanceSettings.getLockFPS())
 : this->Multiplier * this->FPSMultiplier *
 this->PerObjectMultiplier;
 }

 /**
 * Return the inverse of getMultiplier() (1 / getMultiplier()). Per-tick RNG
 * functions can multiply by this value to keep chances relatively stable
 * across different framerates.
 */
 float getInvMultiplier() { return 1.0F / this->getMultiplier(); }

 /**
 * Returns the current game speed multiplier (from the singleplayer speed up
 * UI or while all players are sleeping).
 */
 float getTrueMultiplier() {
 return this->Multiplier * this->PerObjectMultiplier;
 }

 void save() {
 File file = new File(
 ZomboidFileSystem.instance.getFileNameInCurrentSave("map_t.bin"));
 void *object = nullptr;

 try {
 object = new FileOutputStream(file);
 } catch (FileNotFoundException fileNotFoundException) {
 fileNotFoundException.printStackTrace();
 return;
 }

 DataOutputStream dataOutputStream =
 new DataOutputStream(new BufferedOutputStream((OutputStream)object);

 try {
 instance.save(dataOutputStream);
 } catch (IOException iOException0) {
 iOException0.printStackTrace();
 }

 try {
 dataOutputStream.flush();
 dataOutputStream.close();
 } catch (IOException iOException1) {
 iOException1.printStackTrace();
 }
 }

 void save(DataOutputStream output) {
 output.writeByte(71);
 output.writeByte(77);
 output.writeByte(84);
 output.writeByte(77);
 output.writeInt(195);
 output.writeFloat(this->Multiplier);
 output.writeInt(this->NightsSurvived);
 output.writeInt(this->TargetZombies);
 output.writeFloat(this->LastTimeOfDay);
 output.writeFloat(this->TimeOfDay);
 output.writeInt(this->Day);
 output.writeInt(this->Month);
 output.writeInt(this->Year);
 output.writeFloat(0.0F);
 output.writeFloat(0.0F);
 output.writeInt(0);
 if (this->table != nullptr) {
 output.writeByte(1);
 this->table.save(output);
 } else {
 output.writeByte(0);
 }

 GameWindow.WriteString(output, Core.getInstance().getPoisonousBerry());
 GameWindow.WriteString(output, Core.getInstance().getPoisonousMushroom());
 output.writeInt(this->HelicopterDay1);
 output.writeInt(this->HelicopterTime1Start);
 output.writeInt(this->HelicopterTime1End);
 ClimateManager.getInstance().save(output);
 }

 void save(ByteBuffer output) {
 output.putFloat(this->Multiplier);
 output.putInt(this->NightsSurvived);
 output.putInt(this->TargetZombies);
 output.putFloat(this->LastTimeOfDay);
 output.putFloat(this->TimeOfDay);
 output.putInt(this->Day);
 output.putInt(this->Month);
 output.putInt(this->Year);
 output.putFloat(0.0F);
 output.putFloat(0.0F);
 output.putInt(0);
 if (this->table != nullptr) {
 output.put((byte)1);
 this->table.save(output);
 } else {
 output.put((byte)0);
 }
 }

 void load(DataInputStream input) {
 int int0 = IsoWorld.SavedWorldVersion;
 if (int0 == -1) {
 int0 = 195;
 }

 input.mark(0);
 uint8_t byte0 = input.readByte();
 uint8_t byte1 = input.readByte();
 uint8_t byte2 = input.readByte();
 uint8_t byte3 = input.readByte();
 if (byte0 == 71 && byte1 == 77 && byte2 == 84 && byte3 == 77) {
 int0 = input.readInt();
 } else {
 input.reset();
 }

 this->Multiplier = input.readFloat();
 this->NightsSurvived = input.readInt();
 this->TargetZombies = input.readInt();
 this->LastTimeOfDay = input.readFloat();
 this->TimeOfDay = input.readFloat();
 this->Day = input.readInt();
 this->Month = input.readInt();
 this->Year = input.readInt();
 input.readFloat();
 input.readFloat();
 int int1 = input.readInt();
 if (input.readByte() == 1) {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 this->table.load(input, int0);
 }

 if (int0 >= 74) {
 Core.getInstance().setPoisonousBerry(GameWindow.ReadString(input);
 Core.getInstance().setPoisonousMushroom(GameWindow.ReadString(input);
 }

 if (int0 >= 90) {
 this->HelicopterDay1 = input.readInt();
 this->HelicopterTime1Start = input.readInt();
 this->HelicopterTime1End = input.readInt();
 }

 if (int0 >= 135) {
 ClimateManager.getInstance().load(input, int0);
 }

 this->setMinutesStamp();
 }

 void load(ByteBuffer input) {
 short short0 = 195;
 this->Multiplier = input.getFloat();
 this->NightsSurvived = input.getInt();
 this->TargetZombies = input.getInt();
 this->LastTimeOfDay = input.getFloat();
 this->TimeOfDay = input.getFloat();
 this->Day = input.getInt();
 this->Month = input.getInt();
 this->Year = input.getInt();
 input.getFloat();
 input.getFloat();
 int int0 = input.getInt();
 if (input.get() == 1) {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 this->table.load(input, short0);
 }

 this->setMinutesStamp();
 }

 void load() {
 File file = ZomboidFileSystem.instance.getFileInCurrentSave("map_t.bin");

 try(FileInputStream fileInputStream = new FileInputStream(file);
 BufferedInputStream bufferedInputStream =
 new BufferedInputStream(fileInputStream);) {
 { std::lock_guard<std::mutex> __sync_lock__(SliceY.SliceBufferLock_mutex);
 SliceY.SliceBuffer.clear();
 int int0 = bufferedInputStream.read(SliceY.SliceBuffer.array());
 SliceY.SliceBuffer.limit(int0);
 DataInputStream dataInputStream = new DataInputStream(
 new ByteArrayInputStream(SliceY.SliceBuffer.array(), 0, int0);
 this->load(dataInputStream);
 }
 }
 catch (FileNotFoundException fileNotFoundException) {
 }
 catch (Exception exception) {
 ExceptionLogger.logException(exception);
 }
 }

 /**
 * @deprecated
 */
 int getDawn() { return this->dawn; }

 /**
 * @deprecated
 */
 void setDawn(int _dawn) { this->dawn = _dawn; }

 /**
 * @deprecated
 */
 int getDusk() { return this->dusk; }

 /**
 * @deprecated
 */
 void setDusk(int _dusk) { this->dusk = _dusk; }

 /**
 * This was used to store non-object-specific mod data in the save file before
 * global mod data was added. It is generally better to use the global mod
 * data API provided by ModData.
 */
 KahluaTable getModData() {
 if (this->table.empty()) {
 this->table = LuaManager.platform.newTable();
 }

 return this->table;
 }

 /**
 * @deprecated
 */
 bool isThunderDay() { return this->thunderDay; }

 /**
 * @deprecated
 */
 void setThunderDay(bool _thunderDay) { this->thunderDay = _thunderDay; }

 void saveToPacket(ByteBuffer bb) {
 KahluaTable tablex = getInstance().getModData();
 void *object0 = tablex.rawget("camping");
 void *object1 = tablex.rawget("farming");
 void *object2 = tablex.rawget("trapping");
 tablex.rawset("camping", nullptr);
 tablex.rawset("farming", nullptr);
 tablex.rawset("trapping", nullptr);
 this->save(bb);
 tablex.rawset("camping", object0);
 tablex.rawset("farming", object1);
 tablex.rawset("trapping", object2);
 }

 int getHelicopterDay1() { return this->HelicopterDay1; }

 int getHelicopterDay() { return this->HelicopterDay1; }

 void setHelicopterDay(int day) { this->HelicopterDay1 = PZMath.max(day, 0); }

 int getHelicopterStartHour() { return this->HelicopterTime1Start; }

 void setHelicopterStartHour(int hour) {
 this->HelicopterTime1Start = PZMath.clamp(hour, 0, 24);
 }

 int getHelicopterEndHour() { return this->HelicopterTime1End; }

 void setHelicopterEndHour(int hour) {
 this->HelicopterTime1End = PZMath.clamp(hour, 0, 24);
 }

 static bool isGamePaused() {
 if (GameServer.bServer) {
 return GameServer.Players.empty() &&
 ServerOptions.instance.PauseEmpty.getValue();
 } else if (GameClient.bClient) {
 return GameClient.IsClientPaused();
 } else {
 SpeedControls speedControls = UIManager.getSpeedControls();
 return speedControls != nullptr &&
 speedControls.getCurrentGameSpeed() == 0;
 }
 }

public
 static class AnimTimer {
 float Elapsed;
 float Duration;
 bool Finished = true;
 int Ticks;

 void init(int ticks) {
 this->Ticks = ticks;
 this->Elapsed = 0.0F;
 this->Duration = ticks * 1 / 30.0F;
 this->Finished = false;
 }

 void update() {
 this->Elapsed = this->Elapsed +
 GameTime.instance.getMultipliedSecondsSinceLastUpdate() *
 60.0F / 30.0F;
 if (this->Elapsed >= this->Duration) {
 this->Elapsed = this->Duration;
 this->Finished = true;
 }
 }

 float ratio() { return this->Elapsed / this->Duration; }

 bool finished() { return this->Finished; }
 }
}
} // namespace zombie
