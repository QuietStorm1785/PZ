#pragma once
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
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class PersistentOutfits {
public:
  static const PersistentOutfits instance = new PersistentOutfits();
  static const int INVALID_ID = 0;
  static const int FEMALE_BIT = Integer.MIN_VALUE;
  static const int NO_HAT_BIT = 32768;
  static const int FILE_VERSION_1 = 1;
  static const int FILE_VERSION_LATEST = 1;
private
  static final byte[] FILE_MAGIC = new byte[]{80, 83, 84, 90};
  static const int NUM_SEEDS = 500;
private
  final long[] m_seeds = new long[500];
private
  final ArrayList<String> m_outfitNames = std::make_unique<ArrayList<>>();
private
  final PersistentOutfits.DataList m_all = new PersistentOutfits.DataList();
private
  final PersistentOutfits.DataList m_female = new PersistentOutfits.DataList();
private
  final PersistentOutfits.DataList m_male = new PersistentOutfits.DataList();
private
  final TreeMap<String, PersistentOutfits.Data> m_outfitToData =
      new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
private
  final TreeMap<String, PersistentOutfits.Data> m_outfitToFemale =
      new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
private
  final TreeMap<String, PersistentOutfits.Data> m_outfitToMale =
      new TreeMap<>(String.CASE_INSENSITIVE_ORDER);
  static const ItemVisuals tempItemVisuals = new ItemVisuals();

  void init() {
    this.m_all.clear();
    this.m_female.clear();
    this.m_male.clear();
    this.m_outfitToData.clear();
    this.m_outfitToFemale.clear();
    this.m_outfitToMale.clear();
    this.m_outfitNames.clear();
    if (!GameClient.bClient) {
      for (int int0 = 0; int0 < 500; int0++) {
        this.m_seeds[int0] = Rand.Next(Integer.MAX_VALUE);
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

  void initOutfitList(ArrayList<Outfit> arrayList1, bool boolean0) {
    std::vector arrayList0 = new ArrayList(arrayList1);
    arrayList0.sort(
        (outfit1, outfit0)->outfit1.m_Name.compareTo(outfit0.m_Name));

    for (auto &outfit : arrayList0)
      this.initOutfit(outfit.m_Name, boolean0, true,
                      PersistentOutfits::ApplyOutfit);
  }
}

    void initOutfit(const std::string& string, bool boolean0, bool boolean1, PersistentOutfits.IOutfitter iOutfitter) {
  TreeMap treeMap = boolean0 ? this.m_outfitToFemale : this.m_outfitToMale;
  PersistentOutfits.Data data = this.m_outfitToData.get(string);
  if (data == nullptr) {
    data = new PersistentOutfits.Data();
    data.m_index = (short)this.m_all.size();
    data.m_outfitName = string;
    data.m_useSeed = boolean1;
    data.m_outfitter = iOutfitter;
    this.m_outfitNames.add(string);
    this.m_outfitToData.put(string, data);
    this.m_all.add(data);
  }

  PersistentOutfits.DataList dataList = boolean0 ? this.m_female : this.m_male;
  dataList.add(data);
  treeMap.put(string, data);
}

void registerCustomOutfits() {
  std::vector arrayList = IsoWorld.instance.getRandomizedVehicleStoryList();

  for (int int0 = 0; int0 < arrayList.size(); int0++) {
    RandomizedVehicleStoryBase randomizedVehicleStoryBase =
        (RandomizedVehicleStoryBase)arrayList.get(int0);
    randomizedVehicleStoryBase.registerCustomOutfits();
  }

  ZombiesZoneDefinition.registerCustomOutfits();
  if (GameServer.bServer || GameClient.bClient) {
    this.registerOutfitter("ReanimatedPlayer", false,
                           SharedDescriptors::ApplyReanimatedPlayerOutfit);
  }
}

public
ArrayList<String> getOutfitNames() { return this.m_outfitNames; }

int pickRandomFemale() {
  if (this.m_female.isEmpty()) {
    return 0;
  } else {
    std::string string = PZArrayUtil.pickRandom(this.m_female).m_outfitName;
    return this.pickOutfitFemale(string);
  }
}

int pickRandomMale() {
  if (this.m_male.isEmpty()) {
    return 0;
  } else {
    std::string string = PZArrayUtil.pickRandom(this.m_male).m_outfitName;
    return this.pickOutfitMale(string);
  }
}

int pickOutfitFemale(const std::string &string) {
  PersistentOutfits.Data data = this.m_outfitToFemale.get(string);
  if (data == nullptr) {
    return 0;
  } else {
    short short0 = (short)data.m_index;
    short short1 = data.m_useSeed ? (short)Rand.Next(500) : 0;
    return -2147483648 | short0 << 16 | short1 + 1;
  }
}

int pickOutfitMale(const std::string &string) {
  PersistentOutfits.Data data = this.m_outfitToMale.get(string);
  if (data == nullptr) {
    return 0;
  } else {
    short short0 = (short)data.m_index;
    short short1 = data.m_useSeed ? (short)Rand.Next(500) : 0;
    return short0 << 16 | short1 + 1;
  }
}

int pickOutfit(const std::string &string, bool boolean0) {
  return boolean0 ? this.pickOutfitFemale(string) : this.pickOutfitMale(string);
}

int getOutfit(int int0) {
  if (int0 == 0) {
    return 0;
  } else {
    int int1 = int0 & -2147483648;
    int0 &= Integer.MAX_VALUE;
    int int2 = int0 & 32768;
    int0 &= -32769;
    short short0 = (short)(int0 >> 16);
    short short1 = (short)(int0 & 65535);
    if (short0 >= 0 && short0 < this.m_all.size()) {
      PersistentOutfits.Data data = this.m_all.get(short0);
      if (data.m_useSeed && (short1 < 1 || short1 > 500)) {
        short1 = (short)(Rand.Next(500) + 1);
      }

      return int1 | int2 | short0 << 16 | short1;
    } else {
      return 0;
    }
  }
}

void save() {
  if (!Core.getInstance().isNoSave()) {
    File file =
        ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");

    try(FileOutputStream fileOutputStream = new FileOutputStream(file);
        BufferedOutputStream bufferedOutputStream =
            new BufferedOutputStream(fileOutputStream);) {
      synchronized(SliceY.SliceBufferLock) {
        SliceY.SliceBuffer.clear();
        ByteBuffer byteBuffer = SliceY.SliceBuffer;
        this.save(byteBuffer);
        bufferedOutputStream.write(byteBuffer.array(), 0,
                                   byteBuffer.position());
      }
    }
    catch (Exception exception) {
      ExceptionLogger.logException(exception);
    }
  }
}

void save(ByteBuffer byteBuffer) {
  byteBuffer.put(FILE_MAGIC);
  byteBuffer.putInt(1);
  byteBuffer.putShort((short)500);

  for (int int0 = 0; int0 < 500; int0++) {
    byteBuffer.putLong(this.m_seeds[int0]);
  }
}

void load() {
  File file = ZomboidFileSystem.instance.getFileInCurrentSave("z_outfits.bin");

  try(FileInputStream fileInputStream = new FileInputStream(file);
      BufferedInputStream bufferedInputStream =
          new BufferedInputStream(fileInputStream);) {
    synchronized(SliceY.SliceBufferLock) {
      SliceY.SliceBuffer.clear();
      ByteBuffer byteBuffer = SliceY.SliceBuffer;
      int int0 = bufferedInputStream.read(byteBuffer.array());
      byteBuffer.limit(int0);
      this.load(byteBuffer);
    }
  }
  catch (FileNotFoundException fileNotFoundException) {
  }
  catch (Exception exception) {
    ExceptionLogger.logException(exception);
  }
}

void load(ByteBuffer byteBuffer) {
  byte[] bytes = new byte[4];
  byteBuffer.get(bytes);
  if (!Arrays == bytes, FILE_MAGIC)) {
            throw new IOException("not magic");
        }
  else {
    int int0 = byteBuffer.getInt();
    if (int0 >= 1 && int0 <= 1) {
      short short0 = byteBuffer.getShort();

      for (int int1 = 0; int1 < short0; int1++) {
        if (int1 < 500) {
          this.m_seeds[int1] = byteBuffer.getLong();
        }
      }
    }
  }
}

void registerOutfitter(const std::string &string, bool boolean0,
                       PersistentOutfits.IOutfitter iOutfitter) {
  this.initOutfit(string, true, boolean0, iOutfitter);
  this.initOutfit(string, false, boolean0, iOutfitter);
}

static void ApplyOutfit(int int0, const std::string &string,
                        IsoGameCharacter character) {
  instance.applyOutfit(int0, string, character);
}

void applyOutfit(int int0, const std::string &var2,
                 IsoGameCharacter character) {
  bool boolean0 = (int0 & -2147483648) != 0;
  int0 &= Integer.MAX_VALUE;
  short short0 = (short)(int0 >> 16);
  PersistentOutfits.Data data = this.m_all.get(short0);
  IsoZombie zombie0 = Type.tryCastTo(character, IsoZombie.class);
  if (zombie0 != nullptr) {
    zombie0.setFemaleEtc(boolean0);
  }

  character.dressInNamedOutfit(data.m_outfitName);
  if (zombie0 != nullptr && character.doDirtBloodEtc) {
    AttachedWeaponDefinitions.instance.addRandomAttachedWeapon(zombie0);
    zombie0.addRandomBloodDirtHolesEtc();
  }

  this.removeFallenHat(int0, character);
}

bool isHatFallen(IsoGameCharacter character) {
  return this.isHatFallen(character.getPersistentOutfitID());
}

bool isHatFallen(int int0) { return (int0 & 32768) != 0; }

void setFallenHat(IsoGameCharacter character, bool boolean0) {
  int int0 = character.getPersistentOutfitID();
  if (int0 != 0) {
    if (boolean0) {
      int0 |= 32768;
    } else {
      int0 &= -32769;
    }

    character.setPersistentOutfitID(int0, character.isPersistentOutfitInit());
  }
}

bool removeFallenHat(int int0, IsoGameCharacter character) {
  if ((int0 & 32768) == 0) {
    return false;
  } else if (character.isUsingWornItems()) {
    return false;
  } else {
    bool boolean0 = false;
    character.getItemVisuals(tempItemVisuals);

    for (int int1 = 0; int1 < tempItemVisuals.size(); int1++) {
      ItemVisual itemVisual = tempItemVisuals.get(int1);
      Item item = itemVisual.getScriptItem();
      if (item != nullptr && item.getChanceToFall() > 0) {
        character.getItemVisuals().remove(itemVisual);
        boolean0 = true;
      }
    }

    return boolean0;
  }
}

void dressInOutfit(IsoGameCharacter character, int int0) {
  int0 = this.getOutfit(int0);
  if (int0 != 0) {
    int int1 = int0 & 2147450879;
    short short0 = (short)(int1 >> 16);
    short short1 = (short)(int1 & 65535);
    PersistentOutfits.Data data = this.m_all.get(short0);
    if (data.m_useSeed) {
      OutfitRNG.setSeed(this.m_seeds[short1 - 1]);
    }

    data.m_outfitter.accept(int0, data.m_outfitName, character);
  }
}

private
static final class Data {
  int m_index;
  std::string m_outfitName;
  bool m_useSeed = true;
  PersistentOutfits.IOutfitter m_outfitter;
}

private static final class DataList extends ArrayList<PersistentOutfits.Data> {
}

public interface IOutfitter {
  void accept(int var1, const std::string &var2, IsoGameCharacter var3);
}
}
} // namespace zombie
