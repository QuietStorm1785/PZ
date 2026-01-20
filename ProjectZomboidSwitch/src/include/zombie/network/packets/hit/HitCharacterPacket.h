#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/packets/INetworkPacket.h"
#include "zombie/network/packets/hit/HitCharacterPacket/1.h"
#include "zombie/network/packets/hit/HitCharacterPacket/HitType.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {
namespace hit {


class HitCharacterPacket {
public:
    const HitType hitType;

    public HitCharacterPacket(HitType var1) {
      this.hitType = var1;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    static HitCharacterPacket process(ByteBuffer var0) {
    uint8_t var1 = var0.get();
      if (var1 > HitType.Min.ordinal() && var1 < HitType.Max.ordinal()) {
         return (HitCharacterPacket)(switch (1.$SwitchMap$zombie$network$packets$hit$HitCharacterPacket$HitType[HitType.values()[var1].ordinal()]) {
            case 1 -> std::make_unique<PlayerHitSquarePacket>();
            case 2 -> std::make_unique<PlayerHitVehiclePacket>();
            case 3 -> std::make_unique<PlayerHitZombiePacket>();
            case 4 -> std::make_unique<PlayerHitPlayerPacket>();
            case 5 -> std::make_unique<ZombieHitPlayerPacket>();
            case 6 -> std::make_unique<VehicleHitZombiePacket>();
            case 7 -> std::make_unique<VehicleHitPlayerPacket>();
            default -> nullptr;
         });
      } else {
    return nullptr;
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putByte((byte)this.hitType.ordinal());
   }

    std::string getDescription() {
      return super.getDescription() + " (" + this.hitType.name() + ")";
   }

    void tryProcess() {
      if (!GameClient.bClient || !HitType.VehicleHitZombie == this.hitType) && !HitType.VehicleHitPlayer == this.hitType)) {
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
}
} // namespace hit
} // namespace packets
} // namespace network
} // namespace zombie
