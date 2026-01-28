// --- Static field definitions for helicopter, modData, and server time sync ---
#include "GameTime.h"
#include <unordered_map>
#include <cmath>
#include <thread>
#include "LuaManager.h"
    #include "IsoWorld.h"
    #include "IsoCell.h"
    #include "IsoZombie.h"
// ...existing code up to the end of the file, removing duplicate static fields and constructor...
// --- Server time and sync methods ---
zombie::GameTime* zombie::GameTime::getInstance() {
    if (!instance) instance = new GameTime();
    return instance;
}

void zombie::GameTime::setInstance(GameTime* var0) {
    instance = var0;
}

void zombie::GameTime::syncServerTime(long var0, long var2, long var4) {
    long var6 = var4 - var0;
    long var8 = var2 - var4 + var6 / 2L;
    long var10 = serverTimeShift;
    if (!serverTimeShiftIsSet) {
        serverTimeShift = var8;
    } else {
        serverTimeShift = serverTimeShift + (var8 - serverTimeShift) / 100L;
    }
    long var12 = 10000000L;
    if (std::abs(serverTimeShift - var10) > var12) {
        sendTimeSync();
    } else {
        serverTimeShiftIsSet = true;
    }
}

long zombie::GameTime::getServerTime() {
    if (isUTest) {
        return getNanoTime() + serverTimeShift;
    } else {
        return getNanoTime();
    }
}

long zombie::GameTime::getServerTimeMills() {
    return getServerTime() / 1000000L;
}

bool zombie::GameTime::getServerTimeShiftIsSet() {
    return serverTimeShiftIsSet;
}

void zombie::GameTime::setServerTimeShift(long var0) {
    isUTest = true;
    serverTimeShift = var0;
    serverTimeShiftIsSet = true;
}

void zombie::GameTime::sendTimeSync() {
    // Stub: Networking not implemented
}

void zombie::GameTime::receiveTimeSync(/*ByteBuffer var0, UdpConnection var1*/) {
    // Stub: Networking not implemented
}

long zombie::GameTime::getNanoTime() {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(
        std::chrono::steady_clock::now().time_since_epoch()
    ).count();
}

// --- Time update methods ---
float zombie::GameTime::getRealworldSecondsSinceLastUpdate() const {
    return 0.016666668f * FPSMultiplier;
}

float zombie::GameTime::getMultipliedSecondsSinceLastUpdate() const {
    return 0.016666668f * getUnmoddedMultiplier();
}

float zombie::GameTime::getGameWorldSecondsSinceLastUpdate() const {
    float var1 = 1440.0f / getMinutesPerDay();
    return getTimeDelta() * var1;
}

// --- Survival and death string methods ---
std::string zombie::GameTime::getDeathString(const IsoPlayer& var1) const {
    return std::string("Survived for: ") + getTimeSurvived(var1); // TODO: Translator
}

int zombie::GameTime::getDaysSurvived() const {
    // Stub: No IsoPlayer array, return 0
    return 0;
}

std::string zombie::GameTime::getTimeSurvived(const IsoPlayer& var1) const {
    // Java: complex string formatting, stub for now
    return std::string("0 days, 0 hours");
}
#include <string>
#include "zombie/GameTime.h"

namespace zombie {

GameTime* GameTime::instance = nullptr;
long GameTime::serverTimeShift = 0;
bool GameTime::serverTimeShiftIsSet = false;
bool GameTime::isUTest = false;

GameTime::GameTime() {
    serverTimeShift = 0;
    serverTimeShiftIsSet = false;
}

GameTime* GameTime::getInstance() {
    if (!instance) instance = new GameTime();
    return instance;
}

void GameTime::setInstance(GameTime* var0) {
    instance = var0;
}

void GameTime::syncServerTime(long var0, long var2, long var4) {
    long var6 = var4 - var0;
    long var8 = var2 - var4 + var6 / 2L;
    long var10 = serverTimeShift;
    if (!serverTimeShiftIsSet) {
        serverTimeShift = var8;
    } else {
        serverTimeShift = serverTimeShift + (var8 - serverTimeShift) / 100L;
    }
    long var12 = 10000000L;
    if (std::abs(serverTimeShift - var10) > var12) {
        sendTimeSync();
    } else {
        serverTimeShiftIsSet = true;
    }
}

long GameTime::getServerTime() {
    // TODO: Implement GameServer/GameClient logic
    if (isUTest) {
        return getNanoTime() + serverTimeShift;
    } else {
        // Only local for now
        return getNanoTime();
    }
}

long GameTime::getServerTimeMills() {
    return getServerTime() / 1000000L;
}

bool GameTime::getServerTimeShiftIsSet() {
    return serverTimeShiftIsSet;
}

void GameTime::setServerTimeShift(long var0) {
    isUTest = true;
    serverTimeShift = var0;
    serverTimeShiftIsSet = true;
}

void GameTime::sendTimeSync() {
    // TODO: Implement networking
}

void GameTime::receiveTimeSync(/*ByteBuffer var0, UdpConnection var1*/) {
    // TODO: Implement networking
}

// Helper for nanosecond time
long GameTime::getNanoTime() {
    using namespace std::chrono;
    return duration_cast<nanoseconds>(steady_clock::now().time_since_epoch()).count();
}


float GameTime::getRealworldSecondsSinceLastUpdate() {
    // Java: return 0.016666668F * this.FPSMultiplier;
    return 0.016666668f * FPSMultiplier;
}

float GameTime::getMultipliedSecondsSinceLastUpdate() {
    // Java: return 0.016666668F * this.getUnmoddedMultiplier();
    return 0.016666668f * getUnmoddedMultiplier();
}

float GameTime::getGameWorldSecondsSinceLastUpdate() {
    // Java: float var1 = 1440.0F / this.getMinutesPerDay();
    // return this.getTimeDelta() * var1;
    float var1 = 1440.0f / getMinutesPerDay();
    return getTimeDelta() * var1;
}

int GameTime::daysInMonth(int year, int month) {
    // Java: int[] var3 = new int[]{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    static const int days[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
    bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    if (month == 1 && leap) return 29;
    if (month >= 0 && month < 12) return days[month];
    return 30;
}

std::string GameTime::getDeathString(IsoPlayer var1) {
    // Java: Translator.getText("IGUI_Gametime_SurvivedFor", this.getTimeSurvived(var1));
    return "Survived for: " + getTimeSurvived(var1); // TODO: Translator
}

// Simulate IsoPlayer array for demonstration (stub)
namespace {
    constexpr int MAX_PLAYERS = 4;
    IsoPlayer g_players[MAX_PLAYERS];
    int g_numPlayers = MAX_PLAYERS;
}

int GameTime::getDaysSurvived() {
    // Java: max hours survived among players, divided by 24, mod 30
    float maxHours = 0.0f;
    for (int i = 0; i < g_numPlayers; ++i) {
        float h = g_players[i].getHoursSurvived();
        if (h > maxHours) maxHours = h;
    }
    int days = static_cast<int>(maxHours) / 24;
    return days % 30;
}

std::string GameTime::getTimeSurvived(IsoPlayer var1) {
    // Java: complex string formatting, use var1.getHoursSurvived()
    float hours = var1.getHoursSurvived();
    int h = static_cast<int>(hours) % 24;
    int d = static_cast<int>(hours) / 24;
    int m = d / 30;
    d = d % 30;
    int y = m / 12;
    m = m % 12;
    std::string result;
    if (y > 0) result += std::to_string(y) + (y == 1 ? " year, " : " years, ");
    if (m > 0) result += std::to_string(m) + (m == 1 ? " month, " : " months, ");
    if (d > 0) result += std::to_string(d) + (d == 1 ? " day, " : " days, ");
    if (h > 0) result += std::to_string(h) + (h == 1 ? " hour" : " hours");
    if (!result.empty() && result.back() == ' ') result.erase(result.size() - 2); // Remove trailing comma/space
    if (result.empty()) result = "0 hours";
    return result;
}

std::string GameTime::getZombieKilledText(IsoPlayer var1) {
    // Java: var1.getZombieKills()
    int kills = var1.getZombieKills();
    if (kills == 1) return "Killed 1 zombie";
    return "Killed " + std::to_string(kills) + " zombies";
}

std::string GameTime::getGameModeText() {
    // Java: Core.GameMode, Translator.getText("IGUI_Gametime_GameMode", ...)
    // In C++, we need to access the game mode string. Assume a global or static variable for now.
    extern std::string g_GameMode; // Should be set by Core or main game logic
    if (g_GameMode.empty()) {
        return "Game mode: (unknown)";
    }
    // Optionally, translate the mode name (stubbed here)
    std::string modeText = g_GameMode;
    // Example: translate "Survival" to "Survival Mode" etc. (stub, real translation system needed)
    if (modeText == "Survival") modeText = "Survival Mode";
    else if (modeText == "Sandbox") modeText = "Sandbox Mode";
    else if (modeText == "Challenge") modeText = "Challenge Mode";
    // ... add more as needed
    return "Game mode: " + modeText;
}

void GameTime::init() {
    setDay(getStartDay());
    setTimeOfDay(getStartTimeOfDay());
    setMonth(getStartMonth());
    setYear(getStartYear());

    // --- Helicopter event logic (Java: GameTime.init) ---
    // In Java: HelicopterDay1 = Rand.Next(6, 9); HelicopterTime1Start = Rand.Next(9, 15); HelicopterTime1End = HelicopterTime1Start + Rand.Next(1, 3);
    // Here, use C++ random and set static fields
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dayDist(6, 8); // inclusive
        std::uniform_int_distribution<> hourStartDist(9, 14); // inclusive
        std::uniform_int_distribution<> hourLenDist(1, 2); // inclusive
        HelicopterDay1 = dayDist(gen);
        HelicopterTime1Start = hourStartDist(gen);
        HelicopterTime1End = HelicopterTime1Start + hourLenDist(gen);
    }

    // --- Lua event hook ---
    // In Java: LuaEventManager.triggerEvent("OnGameTimeInit");
    // In C++: Use LuaManager to trigger the event (Lua is always required)
    
    if (LuaManager::instance()) {
        LuaManager::instance()->triggerEvent("OnGameTimeInit");
    }

    setMinutesStamp();
}

float GameTime::Lerp(float a, float b, float t) {
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    return a + (b - a) * t;
}


void GameTime::RemoveZombiesIndiscriminate(int /*var1*/) {
    // Java: GameTime.RemoveZombiesIndiscriminate(int count)
    // In Java, this triggers LuaEventManager.triggerEvent("OnRemoveZombiesIndiscriminate", count)
    // and then removes zombies from the world (IsoWorld, IsoZombie)
    // In C++, trigger Lua event and (stub) remove zombies
    if (LuaManager::instance()) {
        bool handled = LuaManager::instance()->triggerEvent("OnRemoveZombiesIndiscriminate", var1);
        if (handled) {
            // If Lua handled, do not remove zombies here
            return;
        }
    }
    // Remove zombies from IsoWorld
    // Java: IsoWorld.instance.CurrentCell.getZombieList()
    // In C++: IsoWorld::getInstance()->getCurrentCell()->getZombieList()
    IsoWorld* world = IsoWorld::getInstance();
    if (!world) return;
    IsoCell* cell = world->getCurrentCell();
    if (!cell) return;
    auto& zombies = cell->getZombieList();
    int removed = 0;
    // Remove up to var1 zombies
    for (auto it = zombies.begin(); it != zombies.end() && removed < var1;) {
        IsoZombie* zombie = *it;
        it = zombies.erase(it);
        delete zombie; // or zombie->removeFromWorld() if managed elsewhere
        ++removed;
    }
}

float GameTime::TimeLerp(float a, float b, float t0, float t1) {
    // Java logic, simplified for C++
    float t = getInstance()->getTimeOfDay();
    if (t1 < t0) t1 += 24.0f;
    bool flip = false;
    if ((t > t1 && t > t0) || (t < t1 && t < t0)) {
        t0 += 24.0f;
        flip = true;
        t0 = t1;
        t1 = t0;
        if (t < t0) t += 24.0f;
    }
    float dt = t1 - t0;
    float d = t - t0;
    float ratio = 0.0f;
    if (d > dt) ratio = 1.0f;
    if (d < dt && d > 0.0f) ratio = d / dt;
    if (flip) ratio = 1.0f - ratio;
    float sign = (ratio < 0.0f) ? -1.0f : 1.0f;
    ratio = std::abs(ratio);
    ratio = 1.0f - ratio;
    ratio = std::pow(ratio, 8.0f);
    ratio = 1.0f - ratio;
    ratio *= sign;
    ratio = ratio * 0.5f + 0.5f;
    return Lerp(a, b, ratio);
}

float GameTime::getDeltaMinutesPerDay() {
    return MinutesPerDayStart / MinutesPerDay;
}

float GameTime::getNightMin() {
    return 1.0f - NightMin;
}

void GameTime::setNightMin(float v) {
    NightMin = 1.0f - v;
}

float GameTime::getNightMax() {
    return 1.0f - NightMax;
}

void GameTime::setNightMax(float v) {
    NightMax = 1.0f - v;
}

int GameTime::getMinutes() {
    return static_cast<int>((getTimeOfDay() - static_cast<int>(getTimeOfDay())) * 60.0f);
}

void GameTime::setMoon(float v) {
    Moon = v;
}

void GameTime::update(bool /*var1*/) {
    // Java: GameTime.update(boolean doWorldUpdate)
    // 1. Update time of day
    float prevTimeOfDay = getTimeOfDay();
    float delta = getGameWorldSecondsSinceLastUpdate() / 3600.0f; // convert seconds to hours
    setTimeOfDay(getTimeOfDay() + delta);
    if (getTimeOfDay() >= 24.0f) {
        setTimeOfDay(getTimeOfDay() - 24.0f);
        setDay(getDay() + 1);
        setNightsSurvived(getNightsSurvived() + 1);
    }

    // 2. Call Lua event for time update
    if (LuaManager::instance()) {
        LuaManager::instance()->triggerEvent("OnGameTimeUpdate", delta);
    }

    // 3. Update IsoPlayers (stub: update hours survived)
    for (int i = 0; i < g_numPlayers; ++i) {
        g_players[i].addHoursSurvived(delta);
    }

    // 4. Update world if requested
    if (var1) {
        IsoWorld* world = IsoWorld::getInstance();
        if (world) world->update();
    }

    // 5. Helicopter event logic (simplified)
    if (getDay() == HelicopterDay1 &&
        getTimeOfDay() >= HelicopterTime1Start &&
        getTimeOfDay() < HelicopterTime1End) {
        // Trigger helicopter event (Lua or C++ logic)
        if (LuaManager::instance()) {
            LuaManager::instance()->triggerEvent("OnHelicopterEvent");
        }
    }
}

void GameTime::updateRoomLight() {
    // Java: GameTime.updateRoomLight()
    // 1. Update lighting for all rooms in the current IsoCell
    IsoWorld* world = IsoWorld::getInstance();
    if (!world) return;
    IsoCell* cell = world->getCurrentCell();
    if (!cell) return;
    cell->updateRoomLights();

    // 2. Trigger Lua event for room light update
    if (LuaManager::instance()) {
        LuaManager::instance()->triggerEvent("OnRoomLightUpdate");
    }
}

void GameTime::setMinutesStamp() {
    minutesStamp = static_cast<long>(getWorldAgeHours() * 60.0 + getMinutes());
}

long GameTime::getMinutesStamp() {
    return minutesStamp;
}

bool GameTime::getThunderStorm() {
    // TODO: Implement getThunderStorm (requires ClimateManager)
    return false;
}

void GameTime::doMetaEvents() {
    // Java: GameTime.doMetaEvents()
    // 1. Trigger Lua event for meta events
    if (LuaManager::instance()) {
        LuaManager::instance()->triggerEvent("OnMetaEvents");
    }
    // 2. Handle meta events in C++ if needed
    // Java: GameTime.doMetaEvents() triggers Lua event and then handles meta events (e.g., world events, random events)
    // C++: Integrate with MetaEventManager if available
    // Example: if (MetaEventManager::getInstance()) MetaEventManager::getInstance()->update();
    // See Java GameTime.java and MetaEventManager.java for logic
    //
    // Note: MetaEventManager is assumed to be a singleton with update() method.
    // If not present, this is a no-op.
    //
    // If/when MetaEventManager is implemented, this will update all meta events (world, random, NPC, etc.)
    #ifdef HAS_METAEVENTMANAGER
    if (MetaEventManager::getInstance()) {
        MetaEventManager::getInstance()->update();
    }
    #endif
}

float GameTime::getAmbient() {
    return Ambient;
}

void GameTime::setAmbient(float v) {
    Ambient = v;
}

float GameTime::getAmbientMax() {
    return AmbientMax;
}

void GameTime::setAmbientMax(float v) {
    AmbientMax = std::min(1.0f, std::max(0.0f, v));
}

float GameTime::getAmbientMin() {
    return AmbientMin;
}

void GameTime::setAmbientMin(float v) {
    AmbientMin = std::min(1.0f, std::max(0.0f, v));
}

int GameTime::getDay() {
    return Day;
}

int GameTime::getDayPlusOne() {
    return Day + 1;
}

void GameTime::setDay(int v) {
    Day = v;
}

int GameTime::getStartDay() {
    return StartDay;
}

void GameTime::setStartDay(int v) {
    StartDay = v;
}

float GameTime::getMaxZombieCountStart() {
    return MaxZombieCountStart;
}

void GameTime::setMaxZombieCountStart(float v) {
    MaxZombieCountStart = v;
}

float GameTime::getMinZombieCountStart() {
    return MinZombieCountStart;
}

void GameTime::setMinZombieCountStart(float v) {
    MinZombieCountStart = v;
}

float GameTime::getMaxZombieCount() {
    return MaxZombieCount;
}

void GameTime::setMaxZombieCount(float v) {
    MaxZombieCount = v;
}

float GameTime::getMinZombieCount() {
    return MinZombieCount;
}

void GameTime::setMinZombieCount(float v) {
    MinZombieCount = v;
}

int GameTime::getMonth() {
    return Month;
}

void GameTime::setMonth(int v) {
    Month = v;
}

int GameTime::getStartMonth() {
    return StartMonth;
}

void GameTime::setStartMonth(int v) {
    StartMonth = v;
}

float GameTime::getNightTint() {
    // Return the current night strength from the climate system
    // If ClimateManager is not available, return 0.0f
    auto& climate = zombie::iso::weather::ClimateManager::getInstance();
    return climate.getNightStrength();
    
}

void GameTime::setNightTint(float v) {
    // Set the night strength in the climate system
    auto& climate = zombie::iso::weather::ClimateManager::getInstance();
    climate.nightStrength.finalValue = v;
}

float GameTime::getNight() {
    // TODO: Implement getNight (requires ClimateManager)
    return 0.0f;
}

void GameTime::setNight(float /*v*/) {
    // TODO: Implement setNight
}

float GameTime::getTimeOfDay() {
    return TimeOfDay;
}

void GameTime::setTimeOfDay(float v) {
    TimeOfDay = v;
}

float GameTime::getStartTimeOfDay() {
    return StartTimeOfDay;
}

void GameTime::setStartTimeOfDay(float v) {
    StartTimeOfDay = v;
}

float GameTime::getViewDist() {
    // TODO: Implement getViewDist (requires ClimateManager)
    return 0.0f;
}

float GameTime::getViewDistMax() {
    return ViewDistMax;
}

void GameTime::setViewDistMax(float v) {
    ViewDistMax = v;
}

float GameTime::getViewDistMin() {
    return ViewDistMin;
}

void GameTime::setViewDistMin(float v) {
    ViewDistMin = v;
}

int GameTime::getYear() {
    return Year;
}

void GameTime::setYear(int v) {
    Year = v;
}

int GameTime::getStartYear() {
    return StartYear;
}

void GameTime::setStartYear(int v) {
    StartYear = v;
}

int GameTime::getNightsSurvived() {
    return NightsSurvived;
}

void GameTime::setNightsSurvived(int v) {
    NightsSurvived = v;
}

double GameTime::getWorldAgeHours() {
    float v = getNightsSurvived() * 24.0f;
    if (getTimeOfDay() >= 7.0f) v += getTimeOfDay() - 7.0f;
    else v += getTimeOfDay() + 17.0f;
    return v;
}

double GameTime::getHoursSurvived() {
    // TODO: Implement getHoursSurvived (should use IsoPlayer)
    return HoursSurvived;
}

void GameTime::setHoursSurvived(double v) {
    // TODO: Implement setHoursSurvived (should use IsoPlayer)
    HoursSurvived = v;
}

int GameTime::getHour() {
    double v = std::floor(getTimeOfDay() * 3600.0f);
    return static_cast<int>(std::floor(v / 3600.0));
}


#include "zombie/util/PZCalendar_simple.h"
using zombie::util::PZCalendar;

// --- Helicopter fields ---
int GameTime::HelicopterDay1 = 0;
int GameTime::HelicopterTime1Start = 0;
int GameTime::HelicopterTime1End = 0;

// --- Mod data ---
// In Java, this is a KahluaTable. Here, we use LuaTable for mod data.
LuaTable GameTime::modData;

// Save GameTime state to a binary file
void GameTime::save(const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) return;
    out.write("GMTM", 4); // Magic
    int version = 195;
    out.write(reinterpret_cast<const char*>(&version), sizeof(version));
    out.write(reinterpret_cast<const char*>(&Multiplier), sizeof(Multiplier));
    out.write(reinterpret_cast<const char*>(&NightsSurvived), sizeof(NightsSurvived));
    out.write(reinterpret_cast<const char*>(&TargetZombies), sizeof(TargetZombies));
    out.write(reinterpret_cast<const char*>(&LastTimeOfDay), sizeof(LastTimeOfDay));
    out.write(reinterpret_cast<const char*>(&TimeOfDay), sizeof(TimeOfDay));
    out.write(reinterpret_cast<const char*>(&Day), sizeof(Day));
    out.write(reinterpret_cast<const char*>(&Month), sizeof(Month));
    out.write(reinterpret_cast<const char*>(&Year), sizeof(Year));
    float zero = 0.0f;
    int zeroInt = 0;
    out.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    out.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
    out.write(reinterpret_cast<const char*>(&zeroInt), sizeof(zeroInt));
    // --- Mod data (stub: write count, then key-value pairs) ---
    int modDataCount = static_cast<int>(modData.size());
    out.write(reinterpret_cast<const char*>(&modDataCount), sizeof(modDataCount));
    for (const auto& kv : modData) {
        int klen = static_cast<int>(kv.first.size());
        int vlen = static_cast<int>(kv.second.size());
        out.write(reinterpret_cast<const char*>(&klen), sizeof(klen));
        out.write(kv.first.data(), klen);
        out.write(reinterpret_cast<const char*>(&vlen), sizeof(vlen));
        out.write(kv.second.data(), vlen);
    }
    // --- Helicopter fields ---
    out.write(reinterpret_cast<const char*>(&HelicopterDay1), sizeof(HelicopterDay1));
    out.write(reinterpret_cast<const char*>(&HelicopterTime1Start), sizeof(HelicopterTime1Start));
    out.write(reinterpret_cast<const char*>(&HelicopterTime1End), sizeof(HelicopterTime1End));
    // --- Climate ---
    zombie::iso::weather::ClimateManager::getInstance().save(out);
    out.close();
}

// Load GameTime state from a binary file
bool GameTime::load(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) return false;
    char magic[4];
    in.read(magic, 4);
    if (std::string(magic, 4) != "GMTM") return false;
    int version = 0;
    in.read(reinterpret_cast<char*>(&version), sizeof(version));
    in.read(reinterpret_cast<char*>(&Multiplier), sizeof(Multiplier));
    in.read(reinterpret_cast<char*>(&NightsSurvived), sizeof(NightsSurvived));
    in.read(reinterpret_cast<char*>(&TargetZombies), sizeof(TargetZombies));
    in.read(reinterpret_cast<char*>(&LastTimeOfDay), sizeof(LastTimeOfDay));
    in.read(reinterpret_cast<char*>(&TimeOfDay), sizeof(TimeOfDay));
    in.read(reinterpret_cast<char*>(&Day), sizeof(Day));
    in.read(reinterpret_cast<char*>(&Month), sizeof(Month));
    in.read(reinterpret_cast<char*>(&Year), sizeof(Year));
    float dummy;
    int dummyInt;
    in.read(reinterpret_cast<char*>(&dummy), sizeof(dummy));
    in.read(reinterpret_cast<char*>(&dummy), sizeof(dummy));
    in.read(reinterpret_cast<char*>(&dummyInt), sizeof(dummyInt));
    // --- Mod data (stub: read count, then key-value pairs) ---
    int modDataCount = 0;
    in.read(reinterpret_cast<char*>(&modDataCount), sizeof(modDataCount));
    modData.clear();
    for (int i = 0; i < modDataCount; ++i) {
        int klen = 0, vlen = 0;
        in.read(reinterpret_cast<char*>(&klen), sizeof(klen));
        std::string key(klen, '\0');
        in.read(&key[0], klen);
        in.read(reinterpret_cast<char*>(&vlen), sizeof(vlen));
        std::string val(vlen, '\0');
        in.read(&val[0], vlen);
        modData[key] = val;
    }
    // --- Helicopter fields ---
    in.read(reinterpret_cast<char*>(&HelicopterDay1), sizeof(HelicopterDay1));
    in.read(reinterpret_cast<char*>(&HelicopterTime1Start), sizeof(HelicopterTime1Start));
    in.read(reinterpret_cast<char*>(&HelicopterTime1End), sizeof(HelicopterTime1End));
    // --- Climate ---
    zombie::iso::weather::ClimateManager::getInstance().load(in, version);
    in.close();
    setMinutesStamp();
    return true;
}

// Calendar integration using PZCalendar_simple.h
std::shared_ptr<PZCalendar> GameTime::calendar;

void GameTime::updateCalendar(int year, int month, int day, int hour, int minute) {
    if (!calendar) calendar = std::make_shared<PZCalendar>();
    // PZCalendar uses 1-based months, Java uses 0-based, so adjust if needed
    std::tm tm = {};
    tm.tm_year = year - 1900;
    tm.tm_mon = month; // If 0-based, use as is; if 1-based, subtract 1
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = 0;
    std::time_t t = std::mktime(&tm);
    calendar->setTimeInMillis(static_cast<long long>(t) * 1000);
}

void GameTime::setCalender(std::shared_ptr<PZCalendar> cal) {
    calendar = cal;
}

std::shared_ptr<PZCalendar> GameTime::getCalender() {
    if (!calendar) calendar = std::make_shared<PZCalendar>();
    return calendar;
}

float GameTime::getMinutesPerDay() {
    return MinutesPerDay;
}

void GameTime::setMinutesPerDay(float v) {
    MinutesPerDay = v;
}

float GameTime::getLastTimeOfDay() {
    return LastTimeOfDay;
}

void GameTime::setLastTimeOfDay(float v) {
    LastTimeOfDay = v;
}

void GameTime::setTargetZombies(int v) {
    TargetZombies = v;
}

bool GameTime::isRainingToday() {
    return RainingToday;
}

float GameTime::getMultiplier() {
    // TODO: Implement full logic (requires GameServer, GameClient, IsoPlayer, etc.)
    return Multiplier * FPSMultiplier * multiplierBias * PerObjectMultiplier * 0.8f;
}

float GameTime::getTimeDelta() {
    return getMultiplier() / (0.8f * multiplierBias) / 60.0f;
}

float GameTime::getAnimSpeedFix() {
    return 0.8f;
}

void GameTime::setMultiplier(float v) {
    Multiplier = v;
}

float GameTime::getServerMultiplier() {
    // TODO: Implement full logic (requires GameServer, GameClient, etc.)
    return Multiplier * 0.5f * 1.6f * multiplierBias;
}

float GameTime::getUnmoddedMultiplier() {
    // TODO: Implement full logic (requires GameServer, GameClient, IsoPlayer, etc.)
    return Multiplier * FPSMultiplier * PerObjectMultiplier;
}

float GameTime::getInvMultiplier() {
    return 1.0f / getMultiplier();
}

float GameTime::getTrueMultiplier() {
    return Multiplier * PerObjectMultiplier;
}

void GameTime::save() {
    // TODO: Implement save
}

void GameTime::save(DataOutputStream var1) {
    // TODO: Implement save
}

void GameTime::save(ByteBuffer var1) {
    // TODO: Implement save
}

void GameTime::load(DataInputStream var1) {
    // TODO: Implement load
}

void GameTime::load(ByteBuffer var1) {
    // TODO: Implement load
}

void GameTime::load() {
    // TODO: Implement load
}

int GameTime::getDawn() {
    // TODO: Implement getDawn
    return 0;
}

void GameTime::setDawn(int var1) {
    // TODO: Implement setDawn
}

int GameTime::getDusk() {
    // TODO: Implement getDusk
    return 0;
}

void GameTime::setDusk(int var1) {
    // TODO: Implement setDusk
}

KahluaTable GameTime::getModData() {
    // TODO: Implement getModData
    return nullptr;
}

bool GameTime::isThunderDay() {
    // TODO: Implement isThunderDay
    return false;
}

void GameTime::setThunderDay(bool var1) {
    // TODO: Implement setThunderDay
}

void GameTime::saveToPacket(ByteBuffer var1) {
    // TODO: Implement saveToPacket
}

int GameTime::getHelicopterDay1() {
    // TODO: Implement getHelicopterDay1
    return 0;
}

int GameTime::getHelicopterDay() {
    // TODO: Implement getHelicopterDay
    return 0;
}

void GameTime::setHelicopterDay(int var1) {
    // TODO: Implement setHelicopterDay
}

int GameTime::getHelicopterStartHour() {
    // TODO: Implement getHelicopterStartHour
    return 0;
}

void GameTime::setHelicopterStartHour(int var1) {
    // TODO: Implement setHelicopterStartHour
}

int GameTime::getHelicopterEndHour() {
    // TODO: Implement getHelicopterEndHour
    return 0;
}

void GameTime::setHelicopterEndHour(int var1) {
    // TODO: Implement setHelicopterEndHour
}

bool GameTime::isGamePaused() {
    // TODO: Implement isGamePaused
    return false;
}

} // namespace zombie
