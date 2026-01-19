#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/PersistentOutfits/Data.h"
#include "zombie/PersistentOutfits/DataList.h"
#include "zombie/PersistentOutfits/IOutfitter.h"
#include "zombie/characters/AttachedItems/AttachedWeaponDefinitions.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/characters/ZombiesZoneDefinition.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/skinnedmodel/population/Outfit.h"
#include "zombie/core/skinnedmodel/population/OutfitManager.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/skinnedmodel/visual/ItemVisuals.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/SliceY.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RandomizedVehicleStoryBase.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {


class PersistentOutfits {
public:
    static auto instance = std::make_shared<PersistentOutfits>();
    static const int INVALID_ID = 0;
    static const int FEMALE_BIT = Integer.MIN_VALUE;
    static const int NO_HAT_BIT = 32768;
    static const int FILE_VERSION_1 = 1;
    static const int FILE_VERSION_LATEST = 1;
   private static final std::vector<byte> FILE_MAGIC = std::make_shared<std::vector<byte>>(){80, 83, 84, 90};
    static const int NUM_SEEDS = 500;
   private final std::vector<long> m_seeds = std::make_shared<std::array<long, 500>>();
   private final ArrayList<String> m_outfitNames = std::make_unique<ArrayList<>>();
    auto m_all = std::make_shared<DataList>();
    auto m_female = std::make_shared<DataList>();
    auto m_male = std::make_shared<DataList>();
   private final TreeMap<String, Data> m_outfitToData = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
   private final TreeMap<String, Data> m_outfitToFemale = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
   private final TreeMap<String, Data> m_outfitToMale = new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
    static auto tempItemVisuals = std::make_shared<ItemVisuals>();

    void init() {
      this.m_all.clear();
      this.m_female.clear();
      this.m_male.clear();
      this.m_outfitToData.clear();
      this.m_outfitToFemale.clear();
      this.m_outfitToMale.clear();
      this.m_outfitNames.clear();
      if (!GameClient.bClient) {
         for (int var1 = 0; var1 < 500; var1++) {
            this.m_seeds[var1] = Rand.Next(Integer.MAX_VALUE);
         }
      }

      this.initOutfitList(OutfitManager.instance.m_FemaleOutfits, true);
      this.initOutfitList(OutfitManager.instance.m_MaleOutfits, false);
      this.registerCustomOutfits();
      if (!GameClient.bClient) {
         this.load();
         this.save();
      }
   }

    void initOutfitList(ArrayList<Outfit> var1, bool var2) {
    std::vector var3 = new ArrayList(var1);
      var3.sort((var0, var1x) -> var0.m_Name.compareTo(var1x.m_Name));

    for (auto& var5 : var3)         this.initOutfit(var5.m_Name, var2, true, PersistentOutfits::ApplyOutfit);
      }
   }

    void initOutfit(const std::string& var1, bool var2, bool var3, IOutfitter var4) {
    TreeMap var5 = var2 ? this.m_outfitToFemale : this.m_outfitToMale;
    Data var6 = this.m_outfitToData.get(var1);
      if (var6 == nullptr) {
         var6 = std::make_unique<Data>();
         var6.m_index = (short)this.m_all.size();
         var6.m_outfitName = var1;
         var6.m_useSeed = var3;
         var6.m_outfitter = var4;
         this.m_outfitNames.add(var1);
         this.m_outfitToData.put(var1, var6);
         this.m_all.add(var6);
      }

    DataList var7 = var2 ? this.m_female : this.m_male;
      var7.add(var6);
      var5.put(var1, var6);
   }

    void registerCustomOutfits() {
    std::vector var1 = IsoWorld.instance.getRandomizedVehicleStoryList();

      for (int var2 = 0; var2 < var1.size(); var2++) {
    RandomizedVehicleStoryBase var3 = static_cast<RandomizedVehicleStoryBase>(var1).get(var2);
         var3.registerCustomOutfits();
      }

      ZombiesZoneDefinition.registerCustomOutfits();
      if (GameServer.bServer || GameClient.bClient) {
         this.registerOutfitter("ReanimatedPlayer", false, SharedDescriptors::ApplyReanimatedPlayerOutfit);
      }
   }

   public ArrayList<String> getOutfitNames() {
      return this.m_outfitNames;
   }

    int pickRandomFemale() {
      if (this.m_female.isEmpty()) {
    return 0;
      } else {
    std::string var1 = (static_cast<Data>(PZArrayUtil).pickRandom(this.m_female)).m_outfitName;
         return this.pickOutfitFemale(var1);
      }
   }

    int pickRandomMale() {
      if (this.m_male.isEmpty()) {
    return 0;
      } else {
    std::string var1 = (static_cast<Data>(PZArrayUtil).pickRandom(this.m_male)).m_outfitName;
         return this.pickOutfitMale(var1);
      }
   }

    int pickOutfitFemale(const std::string& var1) {
    Data var2 = this.m_outfitToFemale.get(var1);
      if (var2 == nullptr) {
    return 0;
      } else {
    short var3 = (short)var2.m_index;
    short var4 = var2.m_useSeed ? (short)Rand.Next(500) : 0;
         return -2147483648 | var3 << 16 | var4 + 1;
      }
   }

    int pickOutfitMale(const std::string& var1) {
    Data var2 = this.m_outfitToMale.get(var1);
      if (var2 == nullptr) {
    return 0;
      } else {
    short var3 = (short)var2.m_index;
    short var4 = var2.m_useSeed ? (short)Rand.Next(500) : 0;
         return var3 << 16 | var4 + 1;
      }
   }

    int pickOutfit(const std::string& var1, bool var2) {
      return var2 ? this.pickOutfitFemale(var1) : this.pickOutfitMale(var1);
   }

    int getOutfit(int var1) {
      if (var1 == 0) {
    return 0;
      } else {
    int var2 = var1 & -2147483648;
         var1 &= Integer.MAX_VALUE;
    int var3 = var1 & 32768;
         var1 &= -32769;
    short var4 = (short)(var1 >> 16);
    short var5 = (short)(var1 & 65535);
         if (var4 >= 0 && var4 < this.m_all.size()) {
    Data var6 = static_cast<Data>(this).m_all.get(var4);
            if (var6.m_useSeed && (var5 < 1 || var5 > 500)) {
               var5 = (short)(Rand.Next(500) + 1);
            }

            return var2 | var3 | var4 << 16 | var5;
         } else {
    return 0;
         }
      }
   }

    void save() {
      if (!Core.getInstance().isNoSave()) {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");

         try (
    auto var2 = std::make_shared<FileOutputStream>(var1);
    auto var3 = std::make_shared<BufferedOutputStream>(var2);
         ) {
            synchronized (SliceY.SliceBufferLock) {
               SliceY.SliceBuffer.clear();
    ByteBuffer var5 = SliceY.SliceBuffer;
               this.save(var5);
               var3.write(var5.array(), 0, var5.position());
            }
         } catch (Exception var12) {
            ExceptionLogger.logException(var12);
         }
      }
   }

    void save(ByteBuffer var1) {
      var1.put(FILE_MAGIC);
      var1.putInt(1);
      var1.putShort((short)500);

      for (int var2 = 0; var2 < 500; var2++) {
         var1.putLong(this.m_seeds[var2]);
      }
   }

    void load() {
    File var1 = ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");

      try (
    auto var2 = std::make_shared<FileInputStream>(var1);
    auto var3 = std::make_shared<BufferedInputStream>(var2);
      ) {
         synchronized (SliceY.SliceBufferLock) {
            SliceY.SliceBuffer.clear();
    ByteBuffer var5 = SliceY.SliceBuffer;
    int var6 = var3.read(var5.array());
            var5.limit(var6);
            this.load(var5);
         }
      } catch (FileNotFoundException var13) {
      } catch (Exception var14) {
         ExceptionLogger.logException(var14);
      }
   }

    void load(ByteBuffer var1) {
      std::vector<byte> var2 = std::make_shared<std::array<byte, 4>>();
      var1.get(var2);
      if (!Arrays == var2, FILE_MAGIC)) {
         throw new IOException("not magic");
      } else {
    int var3 = var1.getInt();
         if (var3 >= 1 && var3 <= 1) {
    short var4 = var1.getShort();

            for (int var5 = 0; var5 < var4; var5++) {
               if (var5 < 500) {
                  this.m_seeds[var5] = var1.getLong();
               }
            }
         }
      }
   }

    void registerOutfitter(const std::string& var1, bool var2, IOutfitter var3) {
      this.initOutfit(var1, true, var2, var3);
      this.initOutfit(var1, false, var2, var3);
   }

    static void ApplyOutfit(int var0, const std::string& var1, IsoGameCharacter var2) {
      instance.applyOutfit(var0, var1, var2);
   }

    void applyOutfit(int var1, const std::string& var2, IsoGameCharacter var3) {
    bool var4 = (var1 & -2147483648) != 0;
      var1 &= Integer.MAX_VALUE;
    short var5 = (short)(var1 >> 16);
    Data var6 = static_cast<Data>(this).m_all.get(var5);
    IsoZombie var7 = static_cast<IsoZombie>(Type).tryCastTo(var3, IsoZombie.class);
      if (var7 != nullptr) {
         var7.setFemaleEtc(var4);
      }

      var3.dressInNamedOutfit(var6.m_outfitName);
      if (var7 != nullptr && var3.doDirtBloodEtc) {
         AttachedWeaponDefinitions.instance.addRandomAttachedWeapon(var7);
         var7.addRandomBloodDirtHolesEtc();
      }

      this.removeFallenHat(var1, var3);
   }

    bool isHatFallen(IsoGameCharacter var1) {
      return this.isHatFallen(var1.getPersistentOutfitID());
   }

    bool isHatFallen(int var1) {
      return (var1 & 32768) != 0;
   }

    void setFallenHat(IsoGameCharacter var1, bool var2) {
    int var3 = var1.getPersistentOutfitID();
      if (var3 != 0) {
         if (var2) {
            var3 |= 32768;
         } else {
            var3 &= -32769;
         }

         var1.setPersistentOutfitID(var3, var1.isPersistentOutfitInit());
      }
   }

    bool removeFallenHat(int var1, IsoGameCharacter var2) {
      if ((var1 & 32768) == 0) {
    return false;
      } else if (var2.isUsingWornItems()) {
    return false;
      } else {
    bool var3 = false;
         var2.getItemVisuals(tempItemVisuals);

         for (int var4 = 0; var4 < tempItemVisuals.size(); var4++) {
    ItemVisual var5 = static_cast<ItemVisual>(tempItemVisuals).get(var4);
    Item var6 = var5.getScriptItem();
            if (var6 != nullptr && var6.getChanceToFall() > 0) {
               var2.getItemVisuals().remove(var5);
               var3 = true;
            }
         }

    return var3;
      }
   }

    void dressInOutfit(IsoGameCharacter var1, int var2) {
      var2 = this.getOutfit(var2);
      if (var2 != 0) {
    int var3 = var2 & 2147450879;
    short var4 = (short)(var3 >> 16);
    short var5 = (short)(var3 & 65535);
    Data var6 = static_cast<Data>(this).m_all.get(var4);
         if (var6.m_useSeed) {
            OutfitRNG.setSeed(this.m_seeds[var5 - 1]);
         }

         var6.m_outfitter.accept(var2, var6.m_outfitName, var1);
      }
   }
}
} // namespace zombie
