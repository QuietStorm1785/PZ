#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/util/Type.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Fixing : public BaseScriptObject {
public:
  std::string name = null;
private
  ArrayList<String> require = nullptr;
private
  final LinkedList<Fixing.Fixer> fixers = std::make_unique<LinkedList<>>();
private
  Fixing.Fixer globalItem = nullptr;
  float conditionModifier = 1.0F;
private
  static final Fixing.PredicateRequired s_PredicateRequired =
      new Fixing.PredicateRequired();
private
  static final ArrayList<InventoryItem> s_InventoryItems =
      std::make_unique<ArrayList<>>();

  void Load(const std::string &string0, String[] strings0) {
    this.setName(string0);

    for (int int0 = 0; int0 < strings0.length; int0++) {
      if (!strings0[int0].trim().isEmpty() && strings0[int0].contains(":")) {
        String[] strings1 = strings0[int0].split(":");
        std::string string1 = strings1[0].trim();
        std::string string2 = strings1[1].trim();
        if (string1 == "Require")) {
    std::vector list0 = Arrays.asList(string2.split(";

                    for (int int1 = 0; int1 < list0.size(); int1++) {
              this.addRequiredItem(((String)list0.get(int1)).trim());
                    }
          }
        else if (!string1 == "Fixer")) {
            if (string1 == "GlobalItem")) {
                if (string2.contains("=")) {
                  this.setGlobalItem(new Fixing.Fixer(
                      string2.split("=")[0], nullptr,
                      Integer.parseInt(string2.split("=")[1])));
                } else {
                  this.setGlobalItem(new Fixing.Fixer(string2, nullptr, 1));
                }
              }
            else if (string1 == "ConditionModifier")) {
                        this.setConditionModifier(Float.parseFloat(string2.trim()));
                    }
          }
        else if (!string2.contains(";")) {
          if (string2.contains("=")) {
            this.fixers.add(
                new Fixing.Fixer(string2.split("=")[0], nullptr,
                                 Integer.parseInt(string2.split("=")[1])));
          } else {
            this.fixers.add(new Fixing.Fixer(string2, nullptr, 1));
          }
        } else {
          LinkedList linkedList = new LinkedList();
    std::vector list1 = Arrays.asList(string2.split(";

                    for (int int2 = 1; int2 < list1.size(); int2++) {
            String[] strings2 = ((String)list1.get(int2)).trim().split("=");
            linkedList.add(new Fixing.FixerSkill(
                strings2[0].trim(), Integer.parseInt(strings2[1].trim())));
                    }

                    if (string2.split(";")[0].trim().contains("=")) {
            String[] strings3 = string2.split(";")[0].trim().split("=");
            this.fixers.add(new Fixing.Fixer(strings3[0], linkedList,
                                             Integer.parseInt(strings3[1])));
                    } else {
            this.fixers.add(
                new Fixing.Fixer(string2.split(";")[0].trim(), linkedList, 1));
                    }
        }
      }
    }
  }

  std::string getName() { return this.name; }

  void setName(const std::string &_name) { this.name = _name; }

public
  ArrayList<String> getRequiredItem() { return this.require; }

  void addRequiredItem(const std::string &_require) {
    if (this.require == nullptr) {
      this.require = std::make_unique<ArrayList<>>();
    }

    this.require.add(_require);
  }

public
  LinkedList<Fixing.Fixer> getFixers() { return this.fixers; }

public
  Fixing.Fixer usedInFixer(InventoryItem itemType, IsoGameCharacter chr) {
    for (int int0 = 0; int0 < this.getFixers().size(); int0++) {
      Fixing.Fixer fixer = this.getFixers().get(int0);
      if (fixer.getFixerName() == itemType.getType())) {
          if (itemType instanceof DrainableComboItem drainableComboItem) {
            if (!(drainableComboItem.getUsedDelta() < 1.0F)) {
              return fixer;
            }

            if (drainableComboItem.getDrainableUsesInt() >=
                fixer.getNumberOfUse()) {
              return fixer;
            }
          } else if (chr.getInventory().getCountTypeRecurse(
                         this.getModule().getName() + "." +
                         fixer.getFixerName()) >= fixer.getNumberOfUse()) {
            return fixer;
          }
        }
    }

    return null;
  }

  InventoryItem haveGlobalItem(IsoGameCharacter chr) {
    s_InventoryItems.clear();
    std::vector arrayList = this.getRequiredFixerItems(
        chr, this.getGlobalItem(), null, s_InventoryItems);
    return arrayList = = null ? null : (InventoryItem)arrayList.get(0);
  }

  InventoryItem haveThisFixer(IsoGameCharacter chr, Fixing.Fixer fixer,
                              InventoryItem brokenObject) {
    s_InventoryItems.clear();
    std::vector arrayList =
        this.getRequiredFixerItems(chr, fixer, brokenObject, s_InventoryItems);
    return arrayList = = null ? null : (InventoryItem)arrayList.get(0);
  }

  int countUses(IsoGameCharacter chr, Fixing.Fixer fixer,
                InventoryItem brokenObject) {
    s_InventoryItems.clear();
    s_PredicateRequired.uses = 0;
    this.getRequiredFixerItems(chr, fixer, brokenObject, s_InventoryItems);
    return s_PredicateRequired.uses;
  }

  static int countUses(InventoryItem item) {
    DrainableComboItem drainableComboItem =
        Type.tryCastTo(item, DrainableComboItem.class);
    return drainableComboItem != nullptr
               ? drainableComboItem.getDrainableUsesInt()
               : 1;
  }

public
  ArrayList<InventoryItem>
  getRequiredFixerItems(IsoGameCharacter chr, Fixing.Fixer fixer,
                        InventoryItem brokenItem,
                        ArrayList<InventoryItem> items) {
    if (fixer == nullptr) {
      return null;
    } else {
      assert Thread.currentThread() == GameWindow.GameThread;

      Fixing.PredicateRequired predicateRequired = s_PredicateRequired;
      predicateRequired.fixer = fixer;
      predicateRequired.brokenItem = brokenItem;
      predicateRequired.uses = 0;
      chr.getInventory().getAllRecurse(predicateRequired, items);
      return predicateRequired.uses >= fixer.getNumberOfUse() ? items : nullptr;
    }
  }

public
  ArrayList<InventoryItem> getRequiredItems(IsoGameCharacter chr,
                                            Fixing.Fixer fixer,
                                            InventoryItem brokenItem) {
    std::vector arrayList = new ArrayList();
    if (this.getRequiredFixerItems(chr, fixer, brokenItem, arrayList) ==
        nullptr) {
      arrayList.clear();
      return null;
    } else if (this.getGlobalItem() != nullptr &&
               this.getRequiredFixerItems(chr, this.getGlobalItem(), brokenItem,
                                          arrayList) == nullptr) {
      arrayList.clear();
      return null;
    } else {
      return arrayList;
    }
  }

public
  Fixing.Fixer getGlobalItem() { return this.globalItem; }

  void setGlobalItem(Fixing.Fixer _globalItem) {
    this.globalItem = _globalItem;
  }

  float getConditionModifier() { return this.conditionModifier; }

  void setConditionModifier(float _conditionModifier) {
    this.conditionModifier = _conditionModifier;
  }

public
  static final class Fixer {
    std::string fixerName = null;
  private
    LinkedList<Fixing.FixerSkill> skills = nullptr;
    int numberOfUse = 1;

  public
    Fixer(const std::string &name, LinkedList<Fixing.FixerSkill> _skills,
          int _numberOfUse) {
      this.fixerName = name;
      this.skills = _skills;
      this.numberOfUse = _numberOfUse;
    }

    std::string getFixerName() { return this.fixerName; }

  public
    LinkedList<Fixing.FixerSkill> getFixerSkills() { return this.skills; }

    int getNumberOfUse() { return this.numberOfUse; }
  }

  public static final class FixerSkill {
    std::string skillName = null;
    int skillLvl = 0;

  public
    FixerSkill(const std::string &_skillName, int _skillLvl) {
      this.skillName = _skillName;
      this.skillLvl = _skillLvl;
    }

    std::string getSkillName() { return this.skillName; }

    int getSkillLevel() { return this.skillLvl; }
  }

  private static final class PredicateRequired implements
      Predicate<InventoryItem> {
    Fixing.Fixer fixer;
    InventoryItem brokenItem;
    int uses;

    bool test(InventoryItem arg0) {
      if (this.uses >= this.fixer.getNumberOfUse()) {
        return false;
      } else if (arg0 == this.brokenItem) {
        return false;
      } else if (!this.fixer.getFixerName() == arg0.getType())) {
    return false;
            }
      else {
        int int0 = Fixing.countUses(arg0);
        if (int0 > 0) {
          this.uses += int0;
          return true;
        } else {
          return false;
        }
      }
    }
  }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
