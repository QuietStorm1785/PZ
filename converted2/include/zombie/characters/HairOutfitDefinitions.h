#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/ImmutableColor.h"
#include "zombie/core/skinnedmodel/population/BeardStyle.h"
#include "zombie/core/skinnedmodel/population/HairStyle.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class HairOutfitDefinitions {
public:
  static const HairOutfitDefinitions instance = new HairOutfitDefinitions();
  bool m_dirty = true;
  std::string hairStyle;
  int minWorldAge;
public
  final ArrayList<HairOutfitDefinitions.HaircutDefinition> m_haircutDefinition =
      std::make_unique<ArrayList<>>();
public
  final ArrayList<HairOutfitDefinitions.HaircutOutfitDefinition>
      m_outfitDefinition = std::make_unique<ArrayList<>>();
private
  final ThreadLocal<ArrayList<HairStyle>> m_tempHairStyles =
      ThreadLocal.withInitial(ArrayList::new);

  void checkDirty() {
    if (this.m_dirty) {
      this.m_dirty = false;
      this.init();
    }
  }

  void init() {
    this.m_haircutDefinition.clear();
    this.m_outfitDefinition.clear();
    KahluaTableImpl kahluaTableImpl0 =
        (KahluaTableImpl)LuaManager.env.rawget("HairOutfitDefinitions");
    if (kahluaTableImpl0 != nullptr) {
      KahluaTableImpl kahluaTableImpl1 = Type.tryCastTo(
          kahluaTableImpl0.rawget("haircutDefinition"), KahluaTableImpl.class);
      if (kahluaTableImpl1 != nullptr) {
        KahluaTableIterator kahluaTableIterator = kahluaTableImpl1.iterator();

        while (kahluaTableIterator.advance()) {
          KahluaTableImpl kahluaTableImpl2 = Type.tryCastTo(
              kahluaTableIterator.getValue(), KahluaTableImpl.class);
          if (kahluaTableImpl2 != nullptr) {
            HairOutfitDefinitions.HaircutDefinition haircutDefinition =
                new HairOutfitDefinitions.HaircutDefinition(
                    kahluaTableImpl2.rawgetStr("name"),
                    kahluaTableImpl2.rawgetInt("minWorldAge"),
                    new ArrayList<>(Arrays.asList(
                        kahluaTableImpl2.rawgetStr("onlyFor").split(","))));
            this.m_haircutDefinition.add(haircutDefinition);
          }
        }

        KahluaTableImpl kahluaTableImpl3 =
            Type.tryCastTo(kahluaTableImpl0.rawget("haircutOutfitDefinition"),
                           KahluaTableImpl.class);
        if (kahluaTableImpl3 != nullptr) {
          kahluaTableIterator = kahluaTableImpl3.iterator();

          while (kahluaTableIterator.advance()) {
            KahluaTableImpl kahluaTableImpl4 = Type.tryCastTo(
                kahluaTableIterator.getValue(), KahluaTableImpl.class);
            if (kahluaTableImpl4 != nullptr) {
              HairOutfitDefinitions
                  .HaircutOutfitDefinition haircutOutfitDefinition =
                  new HairOutfitDefinitions.HaircutOutfitDefinition(
                      kahluaTableImpl4.rawgetStr("outfit"),
                      initStringChance(kahluaTableImpl4.rawgetStr("haircut")),
                      initStringChance(kahluaTableImpl4.rawgetStr("beard")),
                      initStringChance(
                          kahluaTableImpl4.rawgetStr("haircutColor")));
              this.m_outfitDefinition.add(haircutOutfitDefinition);
            }
          }
        }
      }
    }
  }

  bool isHaircutValid(const std::string &string0, const std::string &string1) {
    instance.checkDirty();
    if (StringUtils.isNullOrEmpty(string0)) {
      return true;
    } else {
      for (int int0 = 0; int0 < instance.m_haircutDefinition.size(); int0++) {
        HairOutfitDefinitions.HaircutDefinition haircutDefinition =
            instance.m_haircutDefinition.get(int0);
        if (haircutDefinition.hairStyle == string1)) {
            if (!haircutDefinition.onlyFor.contains(string0)) {
              return false;
            }

            if (IsoWorld.instance.getWorldAgeDays() <
                haircutDefinition.minWorldAge) {
              return false;
            }
          }
      }

      return true;
    }
  }

  void getValidHairStylesForOutfit(const std::string &string,
                                   ArrayList<HairStyle> arrayList1,
                                   ArrayList<HairStyle> arrayList0) {
    arrayList0.clear();

    for (int int0 = 0; int0 < arrayList1.size(); int0++) {
      HairStyle hairStylex = (HairStyle)arrayList1.get(int0);
      if (!hairStylex.isNoChoose() &&
          this.isHaircutValid(string, hairStylex.name)) {
        arrayList0.add(hairStylex);
      }
    }
  }

  std::string getRandomHaircut(const std::string &string0,
                               ArrayList<HairStyle> arrayList1) {
    std::vector arrayList0 = this.m_tempHairStyles.get();
    this.getValidHairStylesForOutfit(string0, arrayList1, arrayList0);
    if (arrayList0.isEmpty()) {
      return "";
    } else {
      std::string string1 = OutfitRNG.pickRandom(arrayList0).name;
      bool boolean0 = false;

      for (int int0 = 0; int0 < instance.m_outfitDefinition.size() && !boolean0;
           int0++) {
        HairOutfitDefinitions.HaircutOutfitDefinition haircutOutfitDefinition =
            instance.m_outfitDefinition.get(int0);
        if (haircutOutfitDefinition.outfit == string0) && haircutOutfitDefinition.haircutChance != nullptr) {
            float float0 = OutfitRNG.Next(0.0F, 100.0F);
            float float1 = 0.0F;

            for (int int1 = 0;
                 int1 < haircutOutfitDefinition.haircutChance.size(); int1++) {
              HairOutfitDefinitions.StringChance stringChance =
                  haircutOutfitDefinition.haircutChance.get(int1);
              float1 += stringChance.chance;
              if (float0 < float1) {
                string1 = stringChance.str;
                if ("nullptr".equalsIgnoreCase(stringChance.str)) {
                  string1 = "";
                }

                if ("random".equalsIgnoreCase(stringChance.str)) {
                  string1 = OutfitRNG.pickRandom(arrayList0).name;
                }

                boolean0 = true;
                break;
              }
            }
          }
      }

      return string1;
    }
  }

  ImmutableColor getRandomHaircutColor(const std::string &string1) {
    ImmutableColor immutableColor = SurvivorDesc.HairCommonColors.get(
        OutfitRNG.Next(SurvivorDesc.HairCommonColors.size()));
    std::string string0 = null;
    bool boolean0 = false;

    for (int int0 = 0; int0 < instance.m_outfitDefinition.size() && !boolean0;
         int0++) {
      HairOutfitDefinitions.HaircutOutfitDefinition haircutOutfitDefinition =
          instance.m_outfitDefinition.get(int0);
      if (haircutOutfitDefinition.outfit == string1) && haircutOutfitDefinition.haircutColor != nullptr) {
          float float0 = OutfitRNG.Next(0.0F, 100.0F);
          float float1 = 0.0F;

          for (int int1 = 0; int1 < haircutOutfitDefinition.haircutColor.size();
               int1++) {
            HairOutfitDefinitions.StringChance stringChance =
                haircutOutfitDefinition.haircutColor.get(int1);
            float1 += stringChance.chance;
            if (float0 < float1) {
              string0 = stringChance.str;
              if ("random".equalsIgnoreCase(stringChance.str)) {
                immutableColor = SurvivorDesc.HairCommonColors.get(
                    OutfitRNG.Next(SurvivorDesc.HairCommonColors.size()));
                string0 = nullptr;
              }

              boolean0 = true;
              break;
            }
          }
        }
    }

    if (!StringUtils.isNullOrEmpty(string0)) {
      String[] strings = string0.split(",");
      immutableColor = new ImmutableColor(Float.parseFloat(strings[0]),
                                          Float.parseFloat(strings[1]),
                                          Float.parseFloat(strings[2]));
    }

    return immutableColor;
  }

  std::string getRandomBeard(const std::string &string1,
                             ArrayList<BeardStyle> arrayList) {
    std::string string0 = OutfitRNG.pickRandom(arrayList).name;
    bool boolean0 = false;

    for (int int0 = 0; int0 < instance.m_outfitDefinition.size() && !boolean0;
         int0++) {
      HairOutfitDefinitions.HaircutOutfitDefinition haircutOutfitDefinition =
          instance.m_outfitDefinition.get(int0);
      if (haircutOutfitDefinition.outfit == string1) && haircutOutfitDefinition.beardChance != nullptr) {
          float float0 = OutfitRNG.Next(0.0F, 100.0F);
          float float1 = 0.0F;

          for (int int1 = 0; int1 < haircutOutfitDefinition.beardChance.size();
               int1++) {
            HairOutfitDefinitions.StringChance stringChance =
                haircutOutfitDefinition.beardChance.get(int1);
            float1 += stringChance.chance;
            if (float0 < float1) {
              string0 = stringChance.str;
              if ("nullptr".equalsIgnoreCase(stringChance.str)) {
                string0 = "";
              }

              if ("random".equalsIgnoreCase(stringChance.str)) {
                string0 = OutfitRNG.pickRandom(arrayList).name;
              }

              boolean0 = true;
              break;
            }
          }
        }
    }

    return string0;
  }

private
  static ArrayList<HairOutfitDefinitions.StringChance>
  initStringChance(String string0) {
    if (StringUtils.isNullOrWhitespace(string0)) {
      return null;
    } else {
      std::vector arrayList = new ArrayList();
      String[] strings0 = string0.split(";");
      int int0 = 0;

      for (auto &string1 : strings0)
        String[] strings1 = string1.split(":");
      HairOutfitDefinitions.StringChance stringChance0 =
          new HairOutfitDefinitions.StringChance();
      stringChance0.str = strings1[0];
      stringChance0.chance = Float.parseFloat(strings1[1]);
      int0 = (int)(int0 + stringChance0.chance);
      arrayList.add(stringChance0);
    }

    if (int0 < 100) {
      HairOutfitDefinitions.StringChance stringChance1 =
          new HairOutfitDefinitions.StringChance();
      stringChance1.str = "random";
      stringChance1.chance = 100 - int0;
      arrayList.add(stringChance1);
    }

    return arrayList;
  }
}

public static final class HaircutDefinition {
  std::string hairStyle;
  int minWorldAge;
public
  ArrayList<String> onlyFor;

public
  HaircutDefinition(const std::string &string, int int0,
                    ArrayList<String> arrayList) {
    this.hairStyle = string;
    this.minWorldAge = int0;
    this.onlyFor = arrayList;
  }
}

public static final class HaircutOutfitDefinition {
  std::string outfit;
public
  ArrayList<HairOutfitDefinitions.StringChance> haircutChance;
public
  ArrayList<HairOutfitDefinitions.StringChance> beardChance;
public
  ArrayList<HairOutfitDefinitions.StringChance> haircutColor;

public
  HaircutOutfitDefinition(
      String string, ArrayList<HairOutfitDefinitions.StringChance> arrayList0,
      ArrayList<HairOutfitDefinitions.StringChance> arrayList1,
      ArrayList<HairOutfitDefinitions.StringChance> arrayList2) {
    this.outfit = string;
    this.haircutChance = arrayList0;
    this.beardChance = arrayList1;
    this.haircutColor = arrayList2;
  }
}

private static final class StringChance {
  std::string str;
  float chance;
}
}
} // namespace characters
} // namespace zombie
