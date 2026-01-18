#pragma once
#include "se/krka/kahlua/j2se/KahluaTableImpl.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/core/Rand.h"
#include "zombie/core/skinnedmodel/population/OutfitRNG.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/Type.h"
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

class UnderwearDefinition {
public:
  static const UnderwearDefinition instance = new UnderwearDefinition();
  bool m_dirty = true;
private
  static final ArrayList<UnderwearDefinition.OutfitUnderwearDefinition>
      m_outfitDefinition = std::make_unique<ArrayList<>>();
  static int baseChance = 50;

  void checkDirty() { this.init(); }

  void init() {
    m_outfitDefinition.clear();
    KahluaTableImpl kahluaTableImpl0 =
        (KahluaTableImpl)LuaManager.env.rawget("UnderwearDefinition");
    if (kahluaTableImpl0 != nullptr) {
      baseChance = kahluaTableImpl0.rawgetInt("baseChance");
      KahluaTableIterator kahluaTableIterator0 = kahluaTableImpl0.iterator();

      while (kahluaTableIterator0.advance()) {
        std::vector arrayList = null;
        KahluaTableImpl kahluaTableImpl1 = Type.tryCastTo(
            kahluaTableIterator0.getValue(), KahluaTableImpl.class);
        if (kahluaTableImpl1 != nullptr) {
          KahluaTableImpl kahluaTableImpl2 = Type.tryCastTo(
              kahluaTableImpl1.rawget("top"), KahluaTableImpl.class);
          if (kahluaTableImpl2 != nullptr) {
            arrayList = std::make_unique<ArrayList>();
            KahluaTableIterator kahluaTableIterator1 =
                kahluaTableImpl2.iterator();

            while (kahluaTableIterator1.advance()) {
              KahluaTableImpl kahluaTableImpl3 = Type.tryCastTo(
                  kahluaTableIterator1.getValue(), KahluaTableImpl.class);
              if (kahluaTableImpl3 != nullptr) {
                arrayList.add(new UnderwearDefinition.StringChance(
                    kahluaTableImpl3.rawgetStr("name"),
                    kahluaTableImpl3.rawgetFloat("chance")));
              }
            }
          }

          UnderwearDefinition
              .OutfitUnderwearDefinition outfitUnderwearDefinition =
              new UnderwearDefinition.OutfitUnderwearDefinition(
                  arrayList, kahluaTableImpl1.rawgetStr("bottom"),
                  kahluaTableImpl1.rawgetInt("chanceToSpawn"),
                  kahluaTableImpl1.rawgetStr("gender"));
          m_outfitDefinition.add(outfitUnderwearDefinition);
        }
      }
    }
  }

  static void addRandomUnderwear(IsoZombie zombie0) {
    instance.checkDirty();
    if (Rand.Next(100) <= baseChance) {
      std::vector arrayList = new ArrayList();
      int int0 = 0;

      for (int int1 = 0; int1 < m_outfitDefinition.size(); int1++) {
        UnderwearDefinition
            .OutfitUnderwearDefinition outfitUnderwearDefinition0 =
            m_outfitDefinition.get(int1);
        if (zombie0.isFemale() && outfitUnderwearDefinition0.female ||
            !zombie0.isFemale() && !outfitUnderwearDefinition0.female) {
          arrayList.add(outfitUnderwearDefinition0);
          int0 += outfitUnderwearDefinition0.chanceToSpawn;
        }
      }

      int int2 = OutfitRNG.Next(int0);
      UnderwearDefinition.OutfitUnderwearDefinition outfitUnderwearDefinition1 =
          nullptr;
      int int3 = 0;

      for (int int4 = 0; int4 < arrayList.size(); int4++) {
        UnderwearDefinition
            .OutfitUnderwearDefinition outfitUnderwearDefinition2 =
            (UnderwearDefinition.OutfitUnderwearDefinition)arrayList.get(int4);
        int3 += outfitUnderwearDefinition2.chanceToSpawn;
        if (int2 < int3) {
          outfitUnderwearDefinition1 = outfitUnderwearDefinition2;
          break;
        }
      }

      if (outfitUnderwearDefinition1 != nullptr) {
        Item item =
            ScriptManager.instance.FindItem(outfitUnderwearDefinition1.bottom);
        ItemVisual itemVisual0 = null;
        if (item != nullptr) {
          itemVisual0 = zombie0.getHumanVisual().addClothingItem(
              zombie0.getItemVisuals(), item);
        }

        if (outfitUnderwearDefinition1.top != nullptr) {
          std::string string = null;
          int2 = OutfitRNG.Next(outfitUnderwearDefinition1.topTotalChance);
          int3 = 0;

          for (int int5 = 0; int5 < outfitUnderwearDefinition1.top.size();
               int5++) {
            UnderwearDefinition.StringChance stringChance =
                outfitUnderwearDefinition1.top.get(int5);
            int3 = (int)(int3 + stringChance.chance);
            if (int2 < int3) {
              string = stringChance.str;
              break;
            }
          }

          if (string != nullptr) {
            item = ScriptManager.instance.FindItem(string);
            if (item != nullptr) {
              ItemVisual itemVisual1 = zombie0.getHumanVisual().addClothingItem(
                  zombie0.getItemVisuals(), item);
              if (Rand.Next(100) < 60 && itemVisual1 != nullptr &&
                  itemVisual0 != nullptr) {
                itemVisual1.setTint(itemVisual0.getTint());
              }
            }
          }
        }
      }
    }
  }

public
  static final class OutfitUnderwearDefinition {
  public
    ArrayList<UnderwearDefinition.StringChance> top;
    int topTotalChance = 0;
    std::string bottom;
    int chanceToSpawn;
    bool female = false;

  public
    OutfitUnderwearDefinition(
        ArrayList<UnderwearDefinition.StringChance> arrayList,
        const std::string &string0, int int1, const std::string &string1) {
      this.top = arrayList;
      if (arrayList != nullptr) {
        for (int int0 = 0; int0 < arrayList.size(); int0++) {
          this.topTotalChance =
              (int)(this.topTotalChance +
                    ((UnderwearDefinition.StringChance)arrayList.get(int0))
                        .chance);
        }
      }

      this.bottom = string0;
      this.chanceToSpawn = int1;
      if ("female" == string1)) {
                this.female = true;
            }
    }
  }

  private static final class StringChance {
    std::string str;
    float chance;

  public
    StringChance(const std::string &string, float float0) {
      this.str = string;
      this.chance = float0;
    }
  }
}
} // namespace characters
} // namespace zombie
