#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/network/packets/PlayerVariables/NetworkPlayerVariable.h"
#include "zombie/network/packets/PlayerVariables/NetworkPlayerVariableIDs.h"
#include <filesystem>

namespace zombie {
namespace network {
namespace packets {


class PlayerVariables {
public:
    uint8_t count = 0;
   NetworkPlayerVariable[] variables = new NetworkPlayerVariable[2];

    public PlayerVariables() {
      for (byte var1 = 0; var1 < this.variables.length; var1++) {
         this.variables[var1] = std::make_shared<NetworkPlayerVariable>(this);
      }
   }

    void set(IsoPlayer var1) {
    std::string var2 = var1.getActionStateName();
      if (var2 == "idle")) {
         this.variables[0].set(var1, NetworkPlayerVariableIDs.IdleSpeed);
         this.count = 1;
      } else if (var2 == "maskingleft") || var2 == "maskingright") || var2 == "movement") || var2 == "run") || var2 == "sprint")) {
         this.variables[0].set(var1, NetworkPlayerVariableIDs.WalkInjury);
         this.variables[1].set(var1, NetworkPlayerVariableIDs.WalkSpeed);
         this.count = 2;
      }
   }

    void apply(IsoPlayer var1) {
      for (byte var2 = 0; var2 < this.count; var2++) {
         var1.setVariable(this.variables[var2].id.name(), this.variables[var2].value);
      }
   }

    void parse(ByteBuffer var1, UdpConnection var2) {
      this.count = var1.get();

      for (byte var3 = 0; var3 < this.count; var3++) {
         this.variables[var3].id = NetworkPlayerVariableIDs.values()[var1.get()];
         this.variables[var3].value = var1.getFloat();
      }
   }

    void write(ByteBufferWriter var1) {
      var1.putByte(this.count);

      for (byte var2 = 0; var2 < this.count; var2++) {
         var1.putByte((byte)this.variables[var2].id.ordinal());
         var1.putFloat(this.variables[var2].value);
      }
   }

    int getPacketSizeBytes() {
      return 1 + this.count * 5;
   }

    std::string getDescription() {
    std::string var1 = "PlayerVariables: ";
      var1 = var1 + "count=" + this.count + " | ";

      for (byte var2 = 0; var2 < this.count; var2++) {
         var1 = var1 + "id=" + this.variables[var2].id.name() + ", ";
         var1 = var1 + "value=" + this.variables[var2].value + " | ";
      }

    return var1;
   }

    void copy(PlayerVariables var1) {
      this.count = var1.count;

      for (byte var2 = 0; var2 < this.count; var2++) {
         this.variables[var2].id = var1.variables[var2].id;
         this.variables[var2].value = var1.variables[var2].value;
      }
   }
}
} // namespace packets
} // namespace network
} // namespace zombie
