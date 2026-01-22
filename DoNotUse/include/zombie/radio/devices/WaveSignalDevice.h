#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatManager.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/objects/IsoWaveSignal.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/ui/UIFont.h"
#include "zombie/vehicles/VehiclePart.h"

namespace zombie {
namespace radio {
namespace devices {


class WaveSignalDevice {
public:
    virtual ~WaveSignalDevice() = default;
    DeviceData getDeviceData();

    void setDeviceData(DeviceData var1);

    float getDelta();

    void setDelta(float var1);

    IsoGridSquare getSquare();

    float getX();

    float getY();

    float getZ();

    void AddDeviceText(const std::string& var1, float var2, float var3, float var4, const std::string& var5, const std::string& var6, int var7);

    bool HasPlayerInRange();

   default void AddDeviceText(IsoPlayer var1, std::string var2, float var3, float var4, float var5, std::string var6, std::string var7, int var8) {
      if (this.getDeviceData() != nullptr && this.getDeviceData().getDeviceVolume() > 0.0F) {
         if (!ZomboidRadio.isStaticSound(var2)) {
            this.getDeviceData().doReceiveSignal(var8);
         }

         if (var1 != nullptr && var1.isLocalPlayer() && !var1.Traits.Deaf.isSet()) {
            if (this.getDeviceData().getParent() instanceof InventoryItem && var1.isEquipped((InventoryItem)this.getDeviceData().getParent())) {
               var1.getChatElement()
                  .addChatLine(
                     var2, var3, var4, var5, UIFont.Medium, this.getDeviceData().getDeviceVolumeRange(), "default", true, true, true, false, false, true
                  );
            } else if (this.getDeviceData().getParent() instanceof IsoWaveSignal) {
               ((IsoWaveSignal)this.getDeviceData().getParent())
                  .getChatElement()
                  .addChatLine(
                     var2, var3, var4, var5, UIFont.Medium, this.getDeviceData().getDeviceVolumeRange(), "default", true, true, true, true, true, true
                  );
            } else if (this.getDeviceData().getParent() instanceof VehiclePart) {
               ((VehiclePart)this.getDeviceData().getParent())
                  .getChatElement()
                  .addChatLine(
                     var2, var3, var4, var5, UIFont.Medium, this.getDeviceData().getDeviceVolumeRange(), "default", true, true, true, true, true, true
                  );
            }

            if (ZomboidRadio.isStaticSound(var2)) {
               ChatManager.getInstance().showStaticRadioSound(var2);
            } else {
               ChatManager.getInstance().showRadioMessage(var2, this.getDeviceData().getChannel());
            }

            if (var7 != nullptr) {
               LuaEventManager.triggerEvent("OnDeviceText", var6, var7, -1, -1, -1, var2, this);
            }
         }
      }
   }
}
} // namespace devices
} // namespace radio
} // namespace zombie
