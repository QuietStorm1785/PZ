#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/math/PZMath.h"
#include "zombie/iso/areas/NonPvpZone.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/ServerOptions.h"
#include <filesystem>

namespace zombie {
namespace characters {


class Safety {
public:
    bool enabled;
    bool last;
    float cooldown;
    float toggle;
    IsoGameCharacter character;

    public Safety() {
   }

    public Safety(IsoGameCharacter var1) {
      this.character = var1;
      this.enabled = true;
      this.last = true;
      this.cooldown = 0.0F;
      this.toggle = 0.0F;
   }

    void copyFrom(Safety var1) {
      this.enabled = var1.enabled;
      this.last = var1.last;
      this.cooldown = var1.cooldown;
      this.toggle = var1.toggle;
   }

    void* getCharacter() {
      return this.character;
   }

    bool isEnabled() {
      return this.enabled;
   }

    void setEnabled(bool var1) {
      this.enabled = var1;
   }

    bool isLast() {
      return this.last;
   }

    void setLast(bool var1) {
      this.last = var1;
   }

    float getCooldown() {
      return this.cooldown;
   }

    void setCooldown(float var1) {
      this.cooldown = var1;
   }

    float getToggle() {
      return this.toggle;
   }

    void setToggle(float var1) {
      this.toggle = var1;
   }

    bool isToggleAllowed() {
      return ServerOptions.getInstance().PVP.getValue()
         && NonPvpZone.getNonPvpZone(PZMath.fastfloor(this.character.getX()), PZMath.fastfloor(this.character.getY())) == nullptr
         && (!ServerOptions.getInstance().SafetySystem.getValue() || this.getCooldown() == 0.0F && this.getToggle() == 0.0F);
   }

    void toggleSafety() {
      if (this.isToggleAllowed()) {
         if (GameClient.bClient) {
            GameClient.sendChangeSafety(this);
         } else {
            this.setToggle(ServerOptions.getInstance().SafetyToggleTimer.getValue());
            this.setLast(this.isEnabled());
            if (this.isEnabled()) {
               this.setEnabled(!this.isEnabled());
            }

            if (GameServer.bServer) {
               GameServer.sendChangeSafety(this);
            }
         }
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.enabled = var1.get() != 0;
      this.last = var1.get() != 0;
      this.cooldown = var1.getFloat();
      this.toggle = var1.getFloat();
   }

    void save(ByteBuffer var1) {
      var1.put((byte)(this.enabled ? 1 : 0));
      var1.put((byte)(this.last ? 1 : 0));
      var1.putFloat(this.cooldown);
      var1.putFloat(this.toggle);
   }

    std::string getDescription() {
      return "enabled=" + this.enabled + " last=" + this.last + " cooldown=" + this.cooldown + " toggle=" + this.toggle;
   }
}
} // namespace characters
} // namespace zombie
