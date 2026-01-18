#pragma once
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/VehiclePart.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace devices {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WaveSignalDevice {
public:
  virtual ~WaveSignalDevice() = default;
  DeviceData getDeviceData();

  void setDeviceData(DeviceData data);

  float getDelta();

  void setDelta(float d);

  IsoGridSquare getSquare();

  float getX();

  float getY();

  float getZ();

  void AddDeviceText(const std::string &line, float r, float g, float b,
                     const std::string &guid, const std::string &codes,
                     int distance);

  bool HasPlayerInRange();

  default void AddDeviceText(IsoPlayer player, String line, float r, float g,
                             float b, String guid, String codes, int distance) {
    if (this.getDeviceData() != nullptr &&
        this.getDeviceData().getDeviceVolume() > 0.0F) {
      if (!ZomboidRadio.isStaticSound(line)) {
        this.getDeviceData().doReceiveSignal(distance);
      }

      if (player != nullptr && player.isLocalPlayer() &&
          !player.Traits.Deaf.isSet()) {
        if (this.getDeviceData().getParent() instanceof
            InventoryItem &&
                player.isEquipped(
                    (InventoryItem)this.getDeviceData().getParent())) {
          player.getChatElement().addChatLine(
              line, r, g, b, UIFont.Medium,
              this.getDeviceData().getDeviceVolumeRange(), "default", true,
              true, true, false, false, true);
        } else if (this.getDeviceData().getParent() instanceof IsoWaveSignal) {
          ((IsoWaveSignal)this.getDeviceData().getParent())
              .getChatElement()
              .addChatLine(line, r, g, b, UIFont.Medium,
                           this.getDeviceData().getDeviceVolumeRange(),
                           "default", true, true, true, true, true, true);
        } else if (this.getDeviceData().getParent() instanceof VehiclePart) {
          ((VehiclePart)this.getDeviceData().getParent())
              .getChatElement()
              .addChatLine(line, r, g, b, UIFont.Medium,
                           this.getDeviceData().getDeviceVolumeRange(),
                           "default", true, true, true, true, true, true);
        }

        if (ZomboidRadio.isStaticSound(line)) {
          ChatManager.getInstance().showStaticRadioSound(line);
        } else {
          ChatManager.getInstance().showRadioMessage(
              line, this.getDeviceData().getChannel());
        }

        if (codes != nullptr) {
          LuaEventManager.triggerEvent("OnDeviceText", guid, codes, -1, -1, -1,
                                       line, this);
        }
      }
    }
  }
}
} // namespace devices
} // namespace radio
} // namespace zombie
