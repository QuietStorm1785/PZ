#pragma once

// Ported from Java: BodyDamageSync and BodyDamageSync.Updater

#include <vector>
#include <cstdint>
#include <memory>
#include <string>

namespace zombie {
namespace network {

class BodyDamageSync {
public:
    // Constants
    static constexpr uint8_t BD_Health = 1;
    static constexpr uint8_t BD_bandaged = 2;
    static constexpr uint8_t BD_bitten = 3;
    static constexpr uint8_t BD_bleeding = 4;
    static constexpr uint8_t BD_IsBleedingStemmed = 5;
    static constexpr uint8_t BD_IsCortorised = 6;
    static constexpr uint8_t BD_scratched = 7;
    static constexpr uint8_t BD_stitched = 8;
    static constexpr uint8_t BD_deepWounded = 9;
    static constexpr uint8_t BD_IsInfected = 10;
    static constexpr uint8_t BD_IsFakeInfected = 11;
    static constexpr uint8_t BD_bandageLife = 12;
    static constexpr uint8_t BD_scratchTime = 13;
    static constexpr uint8_t BD_biteTime = 14;
    static constexpr uint8_t BD_alcoholicBandage = 15;
    static constexpr uint8_t BD_woundInfectionLevel = 16;
    static constexpr uint8_t BD_infectedWound = 17;
    static constexpr uint8_t BD_bleedingTime = 18;
    static constexpr uint8_t BD_deepWoundTime = 19;
    static constexpr uint8_t BD_haveGlass = 20;
    static constexpr uint8_t BD_stitchTime = 21;
    static constexpr uint8_t BD_alcoholLevel = 22;
    static constexpr uint8_t BD_additionalPain = 23;
    static constexpr uint8_t BD_bandageType = 24;
    static constexpr uint8_t BD_getBandageXp = 25;
    static constexpr uint8_t BD_getStitchXp = 26;
    static constexpr uint8_t BD_getSplintXp = 27;
    static constexpr uint8_t BD_fractureTime = 28;
    static constexpr uint8_t BD_splint = 29;
    static constexpr uint8_t BD_splintFactor = 30;
    static constexpr uint8_t BD_haveBullet = 31;
    static constexpr uint8_t BD_burnTime = 32;
    static constexpr uint8_t BD_needBurnWash = 33;
    static constexpr uint8_t BD_lastTimeBurnWash = 34;
    static constexpr uint8_t BD_splintItem = 35;
    static constexpr uint8_t BD_plantainFactor = 36;
    static constexpr uint8_t BD_comfreyFactor = 37;
    static constexpr uint8_t BD_garlicFactor = 38;
    static constexpr uint8_t BD_cut = 39;
    static constexpr uint8_t BD_cutTime = 40;
    static constexpr uint8_t BD_stiffness = 41;
    static constexpr uint8_t BD_BodyDamage = 50;
    static constexpr uint8_t BD_START = 64;
    static constexpr uint8_t BD_END = 65;
    static constexpr uint8_t PKT_START_UPDATING = 1;
    static constexpr uint8_t PKT_STOP_UPDATING = 2;
    static constexpr uint8_t PKT_UPDATE = 3;

    BodyDamageSync();
    ~BodyDamageSync();

    // Singleton instance
    static BodyDamageSync& getInstance();

    // Methods
    void startSendingUpdates(int16_t localIndex, int16_t remoteID);
    void stopSendingUpdates(int16_t localIndex, int16_t remoteID);
    void startReceivingUpdates(int16_t remoteID);
    void stopReceivingUpdates(int16_t remoteID);
    void update();
    void serverPacket(/*ByteBuffer*/ void* buffer); // Replace void* with actual ByteBuffer type
    void clientPacket(/*ByteBuffer*/ void* buffer); // Replace void* with actual ByteBuffer type

    // Updater inner class
    class Updater {
    public:
        Updater();
        ~Updater();
        void update();
        void updatePart(int partIndex);
        void updateField(uint8_t field, bool value);
        bool updateField(uint8_t field, float value, float sentValue);
        void updateField(uint8_t field, const std::string& value);
    private:
        static /*ByteBuffer*/ void* bb; // Replace void* with actual ByteBuffer type
        int16_t localIndex;
        int16_t remoteID;
        void* bdLocal; // Replace void* with actual BodyDamage*
        void* bdSent;  // Replace void* with actual BodyDamage*
        bool partStarted;
        uint8_t partIndex;
        int64_t sendTime;
        bool compareFloats(float a, float b);
    };


private:
    std::vector<std::shared_ptr<Updater>> updaters;
};

} // namespace network
} // namespace zombie
