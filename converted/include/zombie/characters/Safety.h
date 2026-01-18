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
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Safety {
public:
 bool enabled;
 bool last;
 float cooldown;
 float toggle;
 IsoGameCharacter character;

 public Safety() {
 }

 public Safety(IsoGameCharacter _character) {
 this->character = _character;
 this->enabled = true;
 this->last = true;
 this->cooldown = 0.0F;
 this->toggle = 0.0F;
 }

 void copyFrom(Safety other) {
 this->enabled = other.enabled;
 this->last = other.last;
 this->cooldown = other.cooldown;
 this->toggle = other.toggle;
 }

 void* getCharacter() {
 return this->character;
 }

 bool isEnabled() {
 return this->enabled;
 }

 void setEnabled(bool _enabled) {
 this->enabled = _enabled;
 }

 bool isLast() {
 return this->last;
 }

 void setLast(bool _last) {
 this->last = _last;
 }

 float getCooldown() {
 return this->cooldown;
 }

 void setCooldown(float _cooldown) {
 this->cooldown = _cooldown;
 }

 float getToggle() {
 return this->toggle;
 }

 void setToggle(float _toggle) {
 this->toggle = _toggle;
 }

 bool isToggleAllowed() {
 return ServerOptions.getInstance().PVP.getValue()
 && NonPvpZone.getNonPvpZone(PZMath.fastfloor(this->character.getX()), PZMath.fastfloor(this->character.getY())) == nullptr
 && (!ServerOptions.getInstance().SafetySystem.getValue() || this->getCooldown() == 0.0F && this->getToggle() == 0.0F);
 }

 void toggleSafety() {
 if (this->isToggleAllowed()) {
 if (GameClient.bClient) {
 GameClient.sendChangeSafety(this);
 } else {
 this->setToggle(ServerOptions.getInstance().SafetyToggleTimer.getValue());
 this->setLast(this->isEnabled());
 if (this->isEnabled()) {
 this->setEnabled(!this->isEnabled());
 }

 if (GameServer.bServer) {
 GameServer.sendChangeSafety(this);
 }
 }
 }
 }

 void load(ByteBuffer input, int WorldVersion) {
 this->enabled = input.get() != 0;
 this->last = input.get() != 0;
 this->cooldown = input.getFloat();
 this->toggle = input.getFloat();
 }

 void save(ByteBuffer output) {
 output.put((byte)(this->enabled ? 1 : 0);
 output.put((byte)(this->last ? 1 : 0);
 output.putFloat(this->cooldown);
 output.putFloat(this->toggle);
 }

 std::string getDescription() {
 return "enabled=" + this->enabled + " last=" + this->last + " cooldown=" + this->cooldown + " toggle=" + this->toggle;
 }
}
} // namespace characters
} // namespace zombie
