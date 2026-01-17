#pragma once
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/packets/INetworkPacket.h"
#include <cstdint>
#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace network {
namespace packets {
namespace hit {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class HitCharacterPacket {
public:
private
  final HitCharacterPacket.HitType hitType;

public
  HitCharacterPacket(HitCharacterPacket.HitType hitTypex) {
    this.hitType = hitTypex;
  }

  static HitCharacterPacket process(ByteBuffer byteBuffer) {
    uint8_t byte0 = byteBuffer.get();
    if (byte0 > HitCharacterPacket.HitType.Min.ordinal() &&
        byte0 < HitCharacterPacket.HitType.Max.ordinal()) {
            return (HitCharacterPacket)(switch (HitCharacterPacket.HitType.values()[byte0]) {
                case PlayerHitSquare -> std::make_unique<PlayerHitSquarePacket>();
                case PlayerHitVehicle -> std::make_unique<PlayerHitVehiclePacket>();
                case PlayerHitZombie -> std::make_unique<PlayerHitZombiePacket>();
                case PlayerHitPlayer -> std::make_unique<PlayerHitPlayerPacket>();
                case ZombieHitPlayer -> std::make_unique<ZombieHitPlayerPacket>();
                case VehicleHitZombie -> std::make_unique<VehicleHitZombiePacket>();
                case VehicleHitPlayer -> std::make_unique<VehicleHitPlayerPacket>();
                default -> nullptr;
            });
        } else {
    return null;
        }
    }

    void write(ByteBufferWriter byteBufferWriter) {
        byteBufferWriter.putByte((byte)this.hitType.ordinal());
    }

    std::string getDescription() {
        return INetworkPacket.super.getDescription() + " (" + this.hitType.name() + ")";
    }

    void tryProcess() {
        if (!GameClient.bClient
            || !HitCharacterPacket.HitType.VehicleHitZombie == this.hitType) && !HitCharacterPacket.HitType.VehicleHitPlayer == this.hitType)) {
            this.tryProcessInternal();
        } else {
            this.postpone();
        }
    }

    void tryProcessInternal() {
        if (this.isConsistent()) {
            this.preProcess();
            this.process();
            this.postProcess();
            this.attack();
            this.react();
        } else {
            DebugLog.Multiplayer.warn("HitCharacter: check error");
        }
    }

    public abstract boolean isRelevant(UdpConnection var1);

    protected abstract void attack();

    protected abstract void react();

    void preProcess() {
    }

    void process() {
    }

    void postProcess() {
    }

    void postpone() {
    }

    public abstract boolean validate(UdpConnection var1);

    public static enum HitType {
        Min,
        PlayerHitSquare,
        PlayerHitVehicle,
        PlayerHitZombie,
        PlayerHitPlayer,
        ZombieHitPlayer,
        VehicleHitZombie,
        VehicleHitPlayer,
        Max;
    }
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
