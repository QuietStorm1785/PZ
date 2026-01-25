#include "BodyDamageSync.h"

// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

BodyDamageSync::BodyDamageSync() {
    // Java: updaters = new ArrayList<>();
    updaters.clear();
}

BodyDamageSync::~BodyDamageSync() {
    updaters.clear();
}

#include <chrono>
#include <iostream>

// Singleton instance
BodyDamageSync& BodyDamageSync::getInstance() {
    static BodyDamageSync instance;
    return instance;
}


void BodyDamageSync::startSendingUpdates(int16_t localIndex, int16_t remoteID) {
    // Only if GameClient.bClient (assume always true for now)
    for (const auto& updater : updaters) {
        if (updater->localIndex == localIndex && updater->remoteID == remoteID) {
            return;
        }
    }
    // IsoPlayer* player = IsoPlayer::players[localIndex];
    IsoPlayer* player = nullptr;
    if (localIndex >= 0 && localIndex < IsoPlayer::MAX && IsoPlayer::players[localIndex]) {
        player = IsoPlayer::players[localIndex];
    }
    auto updater = std::make_shared<Updater>();
    updater->localIndex = localIndex;
    updater->remoteID = remoteID;
    updater->bdLocal = player ? player->getBodyDamage() : nullptr;
    updater->bdSent = new BodyDamage(nullptr);
    updaters.push_back(updater);
}


void BodyDamageSync::stopSendingUpdates(int16_t localIndex, int16_t remoteID) {
    for (auto it = updaters.begin(); it != updaters.end(); ++it) {
        if ((*it)->localIndex == localIndex && (*it)->remoteID == remoteID) {
            updaters.erase(it);
            return;
        }
    }
}


void BodyDamageSync::startReceivingUpdates(int16_t remoteID) {
    // Send a packet to the server to start receiving body damage updates for remoteID
    // (Assumes GameClient::connection and ByteBufferWriter are available and set up as in the Java code)
    if (!IsoPlayer::players[0]) return;
    int16_t localID = IsoPlayer::players[0]->getOnlineID();
    // Log for debug
    std::cout << "start receiving updates from " << remoteID << " to " << localID << std::endl;
    // Prepare and send the packet
    ByteBufferWriter* writer = GameClient::connection->startPacket();
    PacketType::BodyDamageUpdate::doPacket(writer);
    writer->putByte(PKT_START_UPDATING);
    writer->putShort(localID);
    writer->putShort(remoteID);
    PacketType::BodyDamageUpdate::send(GameClient::connection);
}


void BodyDamageSync::stopReceivingUpdates(int16_t remoteID) {
    // Send a packet to the server to stop receiving body damage updates for remoteID
    if (!IsoPlayer::players[0]) return;
    int16_t localID = IsoPlayer::players[0]->getOnlineID();
    // Log for debug
    std::cout << "stop receiving updates from " << remoteID << " to " << localID << std::endl;
    // Prepare and send the packet
    ByteBufferWriter* writer = GameClient::connection->startPacket();
    PacketType::BodyDamageUpdate::doPacket(writer);
    writer->putByte(PKT_STOP_UPDATING);
    writer->putShort(localID);
    writer->putShort(remoteID);
    PacketType::BodyDamageUpdate::send(GameClient::connection);
}


void BodyDamageSync::update() {
    for (auto& updater : updaters) {
        updater->update();
    }
}


void BodyDamageSync::serverPacket(void* buffer) {
    // Implement packet routing and forwarding as in Java
    ByteBuffer* buf = static_cast<ByteBuffer*>(buffer);
    uint8_t type = buf->get();
    using namespace zombie::network;
    using zombie::core::raknet::UdpConnection;
    using zombie::core::raknet::UdpEngine;
    // Access GameServer static fields (assume they are globally accessible for now)
    extern std::unordered_map<int16_t, int64_t> IDToAddressMap;
    extern UdpEngine udpEngine;
    switch (type) {
        case PKT_START_UPDATING: {
            int16_t localID = buf->getShort();
            int16_t remoteID = buf->getShort();
            std::cout << "[serverPacket] PKT_START_UPDATING: localID=" << localID << ", remoteID=" << remoteID << std::endl;
            auto it = IDToAddressMap.find(remoteID);
            if (it != IDToAddressMap.end()) {
                int64_t guid = it->second;
                UdpConnection* conn = udpEngine.getActiveConnection(guid);
                if (conn) {
                    ByteBufferWriter* writer = conn->startPacket();
                    PacketType::BodyDamageUpdate::doPacket(writer);
                    writer->putByte(PKT_START_UPDATING);
                    writer->putShort(localID);
                    writer->putShort(remoteID);
                    PacketType::BodyDamageUpdate::send(conn);
                }
            }
            break;
        }
        case PKT_STOP_UPDATING: {
            int16_t localID = buf->getShort();
            int16_t remoteID = buf->getShort();
            std::cout << "[serverPacket] PKT_STOP_UPDATING: localID=" << localID << ", remoteID=" << remoteID << std::endl;
            auto it = IDToAddressMap.find(remoteID);
            if (it != IDToAddressMap.end()) {
                int64_t guid = it->second;
                UdpConnection* conn = udpEngine.getActiveConnection(guid);
                if (conn) {
                    ByteBufferWriter* writer = conn->startPacket();
                    PacketType::BodyDamageUpdate::doPacket(writer);
                    writer->putByte(PKT_STOP_UPDATING);
                    writer->putShort(localID);
                    writer->putShort(remoteID);
                    PacketType::BodyDamageUpdate::send(conn);
                }
            }
            break;
        }
        case PKT_UPDATE: {
            int16_t localID = buf->getShort();
            int16_t remoteID = buf->getShort();
            std::cout << "[serverPacket] PKT_UPDATE: localID=" << localID << ", remoteID=" << remoteID << std::endl;
            auto it = IDToAddressMap.find(remoteID);
            if (it != IDToAddressMap.end()) {
                int64_t guid = it->second;
                UdpConnection* conn = udpEngine.getActiveConnection(guid);
                if (conn) {
                    ByteBufferWriter* writer = conn->startPacket();
                    PacketType::BodyDamageUpdate::doPacket(writer);
                    writer->putByte(PKT_UPDATE);
                    writer->putShort(localID);
                    writer->putShort(remoteID);
                    // Copy the rest of the buffer (fields) into the packet
                    // Assume buf->remaining() and buf->get(void*, size_t) exist
                    size_t remaining = buf->remaining();
                    if (remaining > 0) {
                        std::vector<uint8_t> tmp(remaining);
                        buf->get(tmp.data(), remaining);
                        writer->bb.put(tmp.data(), remaining);
                    }
                    PacketType::BodyDamageUpdate::send(conn);
                }
            }
            break;
        }
        default:
            std::cout << "[serverPacket] Unknown packet type: " << (int)type << std::endl;
            break;
    }
}


void BodyDamageSync::clientPacket(void* buffer) {
    // Ported from Java: BodyDamageSync.clientPacket(ByteBuffer var1)
    ByteBuffer* buf = static_cast<ByteBuffer*>(buffer);
    uint8_t type = buf->get();
    if (type == PKT_START_UPDATING) {
        int16_t remoteID = buf->getShort();
        int16_t localID = buf->getShort();
        // Find the local player with matching online ID
        for (int16_t i = 0; i < IsoPlayer::numPlayers; ++i) {
            IsoPlayer* player = IsoPlayer::players[i];
            if (player && player->isAlive() && player->getOnlineID() == localID) {
                // Start sending updates for this player to remoteID
                startSendingUpdates(i, remoteID);
                break;
            }
        }
    } else if (type == PKT_STOP_UPDATING) {
        int16_t remoteID = buf->getShort();
        int16_t localID = buf->getShort();
        for (int16_t i = 0; i < IsoPlayer::numPlayers; ++i) {
            IsoPlayer* player = IsoPlayer::players[i];
            if (player && player->getOnlineID() == localID) {
                stopSendingUpdates(i, remoteID);
                break;
            }
        }
    } else if (type == PKT_UPDATE) {
        int16_t remoteID = buf->getShort();
        int16_t localID = buf->getShort();
        // Find the player by remoteID (as in Java: GameClient.IDToPlayerMap.get(var3))
        IsoPlayer* player = nullptr;
        for (int16_t i = 0; i < IsoPlayer::numPlayers; ++i) {
            if (IsoPlayer::players[i] && IsoPlayer::players[i]->getOnlineID() == remoteID) {
                player = IsoPlayer::players[i];
                break;
            }
        }
        if (player) {
            BodyDamage* bd = player->getBodyDamageRemote();
            uint8_t field = buf->get();
            if (field == BD_BodyDamage) {
                bd->setOverallBodyHealth(buf->getFloat());
                bd->setRemotePainLevel(buf->get());
                bd->IsFakeInfected = (buf->get() == 1);
                bd->InfectionLevel = buf->getFloat();
                field = buf->get();
            }
            while (field == BD_START) {
                uint8_t partIndex = buf->get();
                BodyPart* part = bd->getBodyPart(partIndex);
                uint8_t subField = buf->get();
                while (subField != BD_END) {
                    part->sync(buf, subField);
                    subField = buf->get();
                }
                field = buf->get();
            }
        }
    }
}

// Updater implementation
/* static */ void* BodyDamageSync::Updater::bb = nullptr;


BodyDamageSync::Updater::Updater()
    : localIndex(0), remoteID(0), bdLocal(nullptr), bdSent(nullptr), partStarted(false), partIndex(0), sendTime(0) {
}

BodyDamageSync::Updater::~Updater() {
}

void BodyDamageSync::Updater::update() {
    // Ported from Java: Updater.update()
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
    if (now - sendTime < 500) return;
    sendTime = now;

    if (!bdLocal || !bdSent) return;

    // Prepare a buffer for the update packet
    uint8_t bb[1024];
    int bb_pos = 0;

    // Get pain level (assume getParentChar and getMoodles exist)
    int painLevel = 0;
    if (auto* parent = static_cast<IsoGameCharacter*>(static_cast<BodyDamage*>(bdLocal)->getParentChar())) {
        if (auto* moodles = parent->getMoodles()) {
            painLevel = moodles->getMoodleLevel(MoodleType::Pain);
        }
    }

    bool changed = false;
    BodyDamage* bdL = static_cast<BodyDamage*>(bdLocal);
    BodyDamage* bdS = static_cast<BodyDamage*>(bdSent);
    if (compareFloats(bdL->getOverallBodyHealth(), bdS->getOverallBodyHealth())
        || painLevel != bdS->getRemotePainLevel()
        || bdL->IsFakeInfected != bdS->IsFakeInfected
        || compareFloats(bdL->InfectionLevel, bdS->InfectionLevel)) {
        bb[bb_pos++] = BD_BodyDamage;
        // Write fields
        float health = bdL->getOverallBodyHealth();
        std::memcpy(&bb[bb_pos], &health, sizeof(float)); bb_pos += sizeof(float);
        bb[bb_pos++] = static_cast<uint8_t>(painLevel);
        bb[bb_pos++] = bdL->IsFakeInfected ? 1 : 0;
        float inf = bdL->InfectionLevel;
        std::memcpy(&bb[bb_pos], &inf, sizeof(float)); bb_pos += sizeof(float);
        // Update sent values
        bdS->setOverallBodyHealth(health);
        bdS->setRemotePainLevel(painLevel);
        bdS->IsFakeInfected = bdL->IsFakeInfected;
        bdS->InfectionLevel = bdL->InfectionLevel;
        changed = true;
    }

    // Per-bodypart sync
    for (int i = 0; i < 17; ++i) {
        partStarted = false;
        partIndex = static_cast<uint8_t>(i);
        BodyPart* partL = bdL->getBodyPart(i);
        BodyPart* partS = bdS->getBodyPart(i);
        if (partL && partS) {
            // This will call updateField as needed, which will write to bb
            partL->sync(partS, this);
            if (partStarted) {
                bb[bb_pos++] = BD_END;
                changed = true;
            }
        }
    }

    if (changed && bb_pos > 0) {
        bb[bb_pos++] = BD_END;
        // Send the update packet to the remote client
        // Use the same logic as startSendingUpdates, but send PKT_UPDATE
        ByteBufferWriter* writer = nullptr;
        // Find the connection for remoteID (assume GameClient::connection or similar)
        // This is a placeholder; actual connection lookup may differ
        writer = GameClient::connection->startPacket();
        PacketType::BodyDamageUpdate::doPacket(writer);
        writer->putByte(PKT_UPDATE);
        writer->putShort(localIndex);
        writer->putShort(remoteID);
        writer->bb.put(bb, bb_pos);
        PacketType::BodyDamageUpdate::send(GameClient::connection);
    }
}


void BodyDamageSync::Updater::updatePart(int partIndex) {
    // Ported from Java
    partStarted = false;
    this->partIndex = static_cast<uint8_t>(partIndex);
    if (!bdLocal || !bdSent) return;
    BodyDamage* bdL = static_cast<BodyDamage*>(bdLocal);
    BodyDamage* bdS = static_cast<BodyDamage*>(bdSent);
    BodyPart* partL = bdL->getBodyPart(partIndex);
    BodyPart* partS = bdS->getBodyPart(partIndex);
    if (partL && partS) {
        partL->sync(partS, this);
        // If any field was updated, partStarted will be true and BD_END will be written by update()
    }
}


void BodyDamageSync::Updater::updateField(uint8_t field, bool value) {
    // Ported from Java
    extern uint8_t* g_updater_bb;
    extern int g_updater_bb_pos;
    if (!partStarted) {
        g_updater_bb[g_updater_bb_pos++] = BD_START;
        g_updater_bb[g_updater_bb_pos++] = partIndex;
        partStarted = true;
    }
    g_updater_bb[g_updater_bb_pos++] = field;
    g_updater_bb[g_updater_bb_pos++] = value ? 1 : 0;
}


bool BodyDamageSync::Updater::updateField(uint8_t field, float value, float sentValue) {
    // Ported from Java: only update if value changed
    if (!compareFloats(value, sentValue)) {
        return false;
    }
    // Use the update buffer from Updater::update (bb, bb_pos)
    extern uint8_t* g_updater_bb;
    extern int g_updater_bb_pos;
    if (!partStarted) {
        g_updater_bb[g_updater_bb_pos++] = BD_START;
        g_updater_bb[g_updater_bb_pos++] = partIndex;
        partStarted = true;
    }
    g_updater_bb[g_updater_bb_pos++] = field;
    std::memcpy(&g_updater_bb[g_updater_bb_pos], &value, sizeof(float));
    g_updater_bb_pos += sizeof(float);
    return true;
}


void BodyDamageSync::Updater::updateField(uint8_t field, const std::string& value) {
    // Ported from Java
    extern uint8_t* g_updater_bb;
    extern int g_updater_bb_pos;
    if (!partStarted) {
        g_updater_bb[g_updater_bb_pos++] = BD_START;
        g_updater_bb[g_updater_bb_pos++] = partIndex;
        partStarted = true;
    }
    g_updater_bb[g_updater_bb_pos++] = field;
    // Write string as length-prefixed UTF-8 (like Java's writeUTF)
    uint16_t len = static_cast<uint16_t>(value.size());
    std::memcpy(&g_updater_bb[g_updater_bb_pos], &len, sizeof(uint16_t));
    g_updater_bb_pos += sizeof(uint16_t);
    std::memcpy(&g_updater_bb[g_updater_bb_pos], value.data(), len);
    g_updater_bb_pos += len;
}


bool BodyDamageSync::Updater::compareFloats(float a, float b) {
    // Ported from Java: compare floats for updateField
    return (std::abs(a - b) > 0.01f) || (static_cast<int>(a) != static_cast<int>(b));
}

// BodyDamageSync::Updater methods
BodyDamageSync::Updater::Updater()
    : localIndex(0),
      remoteID(0),
      bdLocal(nullptr),
      bdSent(nullptr),
      partStarted(false),
      partIndex(0),
      sendTime(0)
{
    // All fields initialized above; nothing else needed for now.
}

BodyDamageSync::Updater::~Updater() {
    // Clean up bdSent if allocated
    if (bdSent) {
        delete static_cast<BodyDamage*>(bdSent);
        bdSent = nullptr;
    }
}

} // namespace network
} // namespace zombie
