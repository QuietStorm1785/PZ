#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/SoundManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/ai/sadisticAIDirector/SleepingEvent.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/Translator.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/utils/OnceEvery.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemSoundManager.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class AlarmClockClothing : public Clothing {
public:
    int alarmHour = -1;
    int alarmMinutes = -1;
    bool alarmSet = false;
    long ringSound;
    double ringSince = -1.0;
    int forceDontRing = -1;
    std::string alarmSound = "AlarmClockLoop";
    int soundRadius = 40;
    bool isDigital = true;
    static short PacketPlayer = 1;
    static short PacketWorld = 2;
    static const OnceEvery sendEvery = std::make_shared<OnceEvery>(2.0F);

    public AlarmClockClothing(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4, const std::string& var5, const std::string& var6) {
      super(var1, var2, var3, var4, var5, var6);
      this.cat = ItemType.AlarmClockClothing;
      if (this.fullType.contains("Classic")) {
         this.isDigital = false;
      }

      this.randomizeAlarm();
   }

    public AlarmClockClothing(const std::string& var1, const std::string& var2, const std::string& var3, Item var4, const std::string& var5, const std::string& var6) {
      super(var1, var2, var3, var4, var5, var6);
      this.cat = ItemType.AlarmClockClothing;
      if (this.fullType.contains("Classic")) {
         this.isDigital = false;
      }

      this.randomizeAlarm();
   }

    void randomizeAlarm() {
      if (!Core.bLastStand) {
         if (this.isDigital()) {
            this.alarmHour = Rand.Next(0, 23);
            this.alarmMinutes = (int)Math.floor(Rand.Next(0, 59) / 10) * 10;
            this.alarmSet = Rand.Next(15) == 1;
         }
      }
   }

    IsoGridSquare getAlarmSquare() {
    IsoGridSquare var1 = nullptr;
    ItemContainer var2 = this.getOutermostContainer();
      if (var2 != nullptr) {
         var1 = var2.getSourceGrid();
         if (var1 == nullptr && var2.parent != nullptr) {
            var1 = var2.parent.square;
         }

    InventoryItem var3 = var2.containingItem;
         if (var1 == nullptr && var3 != nullptr && var3.getWorldItem() != nullptr) {
            var1 = var3.getWorldItem().getSquare();
         }
      }

      if (var1 == nullptr && this.getWorldItem() != nullptr && this.getWorldItem().getWorldObjectIndex() != -1) {
         var1 = this.getWorldItem().square;
      }

    return var1;
   }

    bool shouldUpdateInWorld() {
      return this.alarmSet;
   }

    void update() {
      if (this.alarmSet) {
    int var1 = GameTime.instance.getMinutes() / 10 * 10;
         if (!this.isRinging() && this.forceDontRing != var1 && this.alarmHour == GameTime.instance.getHour() && this.alarmMinutes == var1) {
            this.ringSince = GameTime.getInstance().getWorldAgeHours();
         }

         if (this.isRinging()) {
    double var2 = GameTime.getInstance().getWorldAgeHours();
            if (this.ringSince > var2) {
               this.ringSince = var2;
            }

    IsoGridSquare var4 = this.getAlarmSquare();
            if (var4 == nullptr || this.ringSince + 0.5 < var2) {
               this.stopRinging();
            } else if (!GameClient.bClient && var4 != nullptr) {
               WorldSoundManager.instance.addSoundRepeating(nullptr, var4.getX(), var4.getY(), var4.getZ(), this.getSoundRadius(), 3, false);
            }

            if (!GameServer.bServer && this.isRinging()) {
               ItemSoundManager.addItem(this);
            }
         }

         if (this.forceDontRing != var1) {
            this.forceDontRing = -1;
         }
      }
   }

    void updateSound(BaseSoundEmitter var1) {
      assert !GameServer.bServer;

    IsoGridSquare var2 = this.getAlarmSquare();
      if (var2 != nullptr) {
         var1.setPos(var2.x + 0.5F, var2.y + 0.5F, var2.z);
         if (!var1.isPlaying(this.ringSound)) {
            if (this.alarmSound == nullptr || "" == this.alarmSound)) {
               this.alarmSound = "AlarmClockLoop";
            }

            this.ringSound = var1.playSoundImpl(this.alarmSound, var2);
         }

         if (GameClient.bClient && sendEvery.Check() && this.isInLocalPlayerInventory()) {
            GameClient.instance.sendWorldSound(nullptr, var2.x, var2.y, var2.z, this.getSoundRadius(), 3, false, 0.0F, 1.0F);
         }

         this.wakeUpPlayers(var2);
      }
   }

    void wakeUpPlayers(IsoGridSquare var1) {
      if (!GameServer.bServer) {
    int var2 = this.getSoundRadius();
    int var3 = Math.max(var1.getZ() - 3, 0);
    int var4 = Math.min(var1.getZ() + 3, 8);

         for (int var5 = 0; var5 < IsoPlayer.numPlayers; var5++) {
    IsoPlayer var6 = IsoPlayer.players[var5];
            if (var6 != nullptr && !var6.isDead() && var6.getCurrentSquare() != nullptr && !var6.Traits.Deaf.isSet()) {
    IsoGridSquare var7 = var6.getCurrentSquare();
               if (var7.z >= var3 && var7.z < var4) {
    float var8 = IsoUtils.DistanceToSquared(var1.x, var1.y, var7.x, var7.y);
                  if (var6.Traits.HardOfHearing.isSet()) {
                     var8 *= 4.5F;
                  }

                  if (!(var8 > var2 * var2)) {
                     this.wakeUp(var6);
                  }
               }
            }
         }
      }
   }

    void wakeUp(IsoPlayer var1) {
      if (var1.Asleep) {
         SoundManager.instance.setMusicWakeState(var1, "WakeNormal");
         SleepingEvent.instance.wakeUp(var1);
      }
   }

    bool isRinging() {
      return this.ringSince >= 0.0;
   }

    bool finishupdate() {
      return !this.alarmSet;
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
    LayoutItem var3 = var2.addItem();
      var3.setLabel(Translator.getText("IGUI_CurrentTime"), 1.0F, 1.0F, 0.8F, 1.0F);
    int var4 = GameTime.instance.getMinutes() / 10 * 10;
      var3.setValue(GameTime.getInstance().getHour() + ":" + (var4 == 0 ? "00" : var4), 1.0F, 1.0F, 0.8F, 1.0F);
      if (this.alarmSet) {
         var3 = var2.addItem();
         var3.setLabel(Translator.getText("IGUI_AlarmIsSetFor"), 1.0F, 1.0F, 0.8F, 1.0F);
         var3.setValue(this.alarmHour + ":" + (this.alarmMinutes == 0 ? "00" : this.alarmMinutes), 1.0F, 1.0F, 0.8F, 1.0F);
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
      var1.putInt(this.alarmHour);
      var1.putInt(this.alarmMinutes);
      var1.put((byte)(this.alarmSet ? 1 : 0));
      var1.putFloat((float)this.ringSince);
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.alarmHour = var1.getInt();
      this.alarmMinutes = var1.getInt();
      this.alarmSet = var1.get() == 1;
      this.ringSince = var1.getFloat();
      this.ringSound = -1L;
   }

    int getSaveType() {
      return Type.AlarmClock.ordinal();
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "AlarmClock";
   }

    void setAlarmSet(bool var1) {
      this.stopRinging();
      this.alarmSet = var1;
      this.ringSound = -1L;
      if (var1) {
         IsoWorld.instance.CurrentCell.addToProcessItems(this);
    IsoWorldInventoryObject var2 = this.getWorldItem();
         if (var2 != nullptr && var2.getSquare() != nullptr) {
    IsoCell var3 = IsoWorld.instance.getCell();
            if (!var3.getProcessWorldItems().contains(var2)) {
               var3.getProcessWorldItems().push_back(var2);
            }
         }
      } else {
         IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
      }
   }

    bool isAlarmSet() {
      return this.alarmSet;
   }

    void setHour(int var1) {
      this.alarmHour = var1;
      this.forceDontRing = -1;
   }

    void setMinute(int var1) {
      this.alarmMinutes = var1;
      this.forceDontRing = -1;
   }

    int getHour() {
      return this.alarmHour;
   }

    int getMinute() {
      return this.alarmMinutes;
   }

    void syncAlarmClock() {
    IsoPlayer var1 = this.getOwnerPlayer(this.container);
      if (var1 != nullptr) {
         this.syncAlarmClock_Player(var1);
      }

      if (this.worldItem != nullptr) {
         this.syncAlarmClock_World();
      }
   }

    IsoPlayer getOwnerPlayer(ItemContainer var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
    IsoObject var2 = var1.getParent();
         return dynamic_cast<IsoPlayer*>(var2) != nullptr ? (IsoPlayer)var2 : nullptr;
      }
   }

    void syncAlarmClock_Player(IsoPlayer var1) {
      if (GameClient.bClient) {
    ByteBufferWriter var2 = GameClient.connection.startPacket();
         PacketType.SyncAlarmClock.doPacket(var2);
         var2.putShort(PacketPlayer);
         var2.putShort((short)var1.getPlayerNum());
         var2.putInt(this.id);
         var2.putByte((byte)0);
         var2.putInt(this.alarmHour);
         var2.putInt(this.alarmMinutes);
         var2.putByte((byte)(this.alarmSet ? 1 : 0));
         PacketType.SyncAlarmClock.send(GameClient.connection);
      }
   }

    void syncAlarmClock_World() {
      if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.SyncAlarmClock.doPacket(var1);
         var1.putShort(PacketWorld);
         var1.putInt(this.worldItem.square.getX());
         var1.putInt(this.worldItem.square.getY());
         var1.putInt(this.worldItem.square.getZ());
         var1.putInt(this.id);
         var1.putByte((byte)0);
         var1.putInt(this.alarmHour);
         var1.putInt(this.alarmMinutes);
         var1.putByte((byte)(this.alarmSet ? 1 : 0));
         PacketType.SyncAlarmClock.send(GameClient.connection);
      }
   }

    void syncStopRinging() {
      if (GameClient.bClient) {
    ByteBufferWriter var1 = GameClient.connection.startPacket();
         PacketType.SyncAlarmClock.doPacket(var1);
    IsoPlayer var2 = this.getOwnerPlayer(this.container);
         if (var2 != nullptr) {
            var1.putShort(PacketPlayer);
            var1.putShort((short)var2.getPlayerNum());
         } else if (this.getWorldItem() != nullptr) {
            var1.putShort(PacketWorld);
            var1.putInt(this.worldItem.square.getX());
            var1.putInt(this.worldItem.square.getY());
            var1.putInt(this.worldItem.square.getZ());
         } else {
    assert false;
         }

         var1.putInt(this.id);
         var1.putByte((byte)1);
         PacketType.SyncAlarmClock.send(GameClient.connection);
      }
   }

    void stopRinging() {
      if (this.ringSound != -1L) {
         this.ringSound = -1L;
      }

      ItemSoundManager.removeItem(this);
      this.ringSince = -1.0;
      this.forceDontRing = GameTime.instance.getMinutes() / 10 * 10;
   }

    std::string getAlarmSound() {
      return this.alarmSound;
   }

    void setAlarmSound(const std::string& var1) {
      this.alarmSound = var1;
   }

    int getSoundRadius() {
      return this.soundRadius;
   }

    void setSoundRadius(int var1) {
      this.soundRadius = var1;
   }

    bool isDigital() {
      return this.isDigital;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
