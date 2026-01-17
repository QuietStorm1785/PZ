#pragma once
#include "zombie/GameWindow.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
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
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Literature : public InventoryItem {
public:
  bool bAlreadyRead = false;
  std::string requireInHandOrInventory = null;
  std::string useOnConsume = null;
  int numberOfPages = -1;
  std::string bookName = "";
  int LvlSkillTrained = -1;
  int NumLevelsTrained;
  std::string SkillTrained = "None";
  int alreadyReadPages = 0;
  bool canBeWrite = false;
private
  HashMap<Integer, String> customPages = nullptr;
  std::string lockedBy = null;
  int pageToWrite;
private
  List<String> teachedRecipes = nullptr;
  const int maxTextLength = 16384;

public
  Literature(const std::string &module, const std::string &name,
             const std::string &itemType, const std::string &texName) {
    super(module, name, itemType, texName);
    this.setBookName(name);
    this.cat = ItemType.Literature;
    if (this.staticModel == nullptr) {
      this.staticModel = "Book";
    }
  }

public
  Literature(const std::string &module, const std::string &name,
             const std::string &itemType, Item item) {
    super(module, name, itemType, item);
    this.setBookName(name);
    this.cat = ItemType.Literature;
    if (this.staticModel == nullptr) {
      this.staticModel = "Book";
    }
  }

  bool IsLiterature() { return true; }

  int getSaveType() { return Item.Type.Literature.ordinal(); }

  std::string getCategory() {
    return this.mainCategory != nullptr ? this.mainCategory : "Literature";
  }

  void update() {
    if (this.container != nullptr) {
    }
  }

  bool finishupdate() { return true; }

  void DoTooltip(ObjectTooltip tooltipUI, ObjectTooltip.Layout layout) {
    if (this.getLvlSkillTrained() != -1) {
      ObjectTooltip.LayoutItem layoutItem0 = layout.addItem();
      layoutItem0.setLabel(Translator.getText("Tooltip_BookTitle") + ":", 1.0F,
                           1.0F, 0.8F, 1.0F);
      layoutItem0.setValue(
          Translator.getText("Tooltip_BookTitle_" + this.getLvlSkillTrained(),
                             Translator.getText("Tooltip_BookTitle_" +
                                                this.getSkillTrained())),
          1.0F, 1.0F, 1.0F, 1.0F);
    }

    if (this.getBoredomChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem1 = layout.addItem();
      int int0 = (int)this.getBoredomChange();
      layoutItem1.setLabel(
          Translator.getText("Tooltip_literature_Boredom_Reduction") + ":",
          1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem1.setValueRight(int0, false);
    }

    if (this.getStressChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem2 = layout.addItem();
      int int1 = (int)(this.getStressChange() * 100.0F);
      layoutItem2.setLabel(
          Translator.getText("Tooltip_literature_Stress_Reduction") + ":", 1.0F,
          1.0F, 0.8F, 1.0F);
      layoutItem2.setValueRight(int1, false);
    }

    if (this.getUnhappyChange() != 0.0F) {
      ObjectTooltip.LayoutItem layoutItem3 = layout.addItem();
      int int2 = (int)this.getUnhappyChange();
      layoutItem3.setLabel(Translator.getText("Tooltip_food_Unhappiness") + ":",
                           1.0F, 1.0F, 0.8F, 1.0F);
      layoutItem3.setValueRight(int2, false);
    }

    if (this.getNumberOfPages() != -1) {
      ObjectTooltip.LayoutItem layoutItem4 = layout.addItem();
      int int3 = this.getAlreadyReadPages();
      if (tooltipUI.getCharacter() != nullptr) {
        int3 = tooltipUI.getCharacter().getAlreadyReadPages(this.getFullType());
      }

      layoutItem4.setLabel(
          Translator.getText("Tooltip_literature_Number_of_Pages") + ":", 1.0F,
          1.0F, 0.8F, 1.0F);
      layoutItem4.setValue(int3 + " / " + this.getNumberOfPages(), 1.0F, 1.0F,
                           1.0F, 1.0F);
    }

    if (this.getLvlSkillTrained() != -1) {
      ObjectTooltip.LayoutItem layoutItem5 = layout.addItem();
      std::string string0 = this.getLvlSkillTrained() + "";
      if (this.getLvlSkillTrained() != this.getMaxLevelTrained()) {
        string0 = string0 + "-" + this.getMaxLevelTrained();
      }

      layoutItem5.setLabel(
          Translator.getText("Tooltip_Literature_XpMultiplier", string0), 1.0F,
          1.0F, 0.8F, 1.0F);
    }

    if (this.getTeachedRecipes() != nullptr) {
      for (String string1 : this.getTeachedRecipes()) {
        ObjectTooltip.LayoutItem layoutItem6 = layout.addItem();
        std::string string2 = Translator.getRecipeName(string1);
        layoutItem6.setLabel(
            Translator.getText("Tooltip_Literature_TeachedRecipes", string2),
            1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (tooltipUI.getCharacter() != nullptr) {
        ObjectTooltip.LayoutItem layoutItem7 = layout.addItem();
        std::string string3 =
            Translator.getText("Tooltip_literature_NotBeenRead");
        if (tooltipUI.getCharacter().getKnownRecipes().containsAll(
                this.getTeachedRecipes())) {
          string3 = Translator.getText("Tooltip_literature_HasBeenRead");
        }

        layoutItem7.setLabel(string3, 1.0F, 1.0F, 0.8F, 1.0F);
        if (tooltipUI.getCharacter().getKnownRecipes().containsAll(
                this.getTeachedRecipes())) {
          ProfessionFactory.Profession profession =
              ProfessionFactory.getProfession(
                  tooltipUI.getCharacter().getDescriptor().getProfession());
          TraitCollection traitCollection =
              tooltipUI.getCharacter().getTraits();
          int int4 = 0;
          int int5 = 0;

          for (int int6 = 0; int6 < this.getTeachedRecipes().size(); int6++) {
            std::string string4 = this.getTeachedRecipes().get(int6);
            if (profession != nullptr &&
                profession.getFreeRecipes().contains(string4)) {
              int4++;
            }

            for (int int7 = 0; int7 < traitCollection.size(); int7++) {
              TraitFactory.Trait trait =
                  TraitFactory.getTrait(traitCollection.get(int7));
              if (trait != nullptr &&
                  trait.getFreeRecipes().contains(string4)) {
                int5++;
              }
            }
          }

          if (int4 > 0 || int5 > 0) {
            layoutItem7 = layout.addItem();
            layoutItem7.setLabel(
                Translator.getText("Tooltip_literature_AlreadyKnown"), 0.0F,
                1.0F, 0.8F, 1.0F);
          }
        }
      }
    }
  }

  void save(ByteBuffer output, bool net) {
    super.save(output, net);
    BitHeaderWrite bitHeaderWrite =
        BitHeader.allocWrite(BitHeader.HeaderSize.Byte, output);
    uint8_t byte0 = 0;
    if (this.numberOfPages >= 127 && this.numberOfPages < 32767) {
      byte0 = 1;
    } else if (this.numberOfPages >= 32767) {
      byte0 = 2;
    }

    if (this.numberOfPages != -1) {
      bitHeaderWrite.addFlags(1);
      if (byte0 == 1) {
        bitHeaderWrite.addFlags(2);
        output.putShort((short)this.numberOfPages);
      } else if (byte0 == 2) {
        bitHeaderWrite.addFlags(4);
        output.putInt(this.numberOfPages);
      } else {
        output.put((byte)this.numberOfPages);
      }
    }

    if (this.alreadyReadPages != 0) {
      bitHeaderWrite.addFlags(8);
      if (byte0 == 1) {
        output.putShort((short)this.alreadyReadPages);
      } else if (byte0 == 2) {
        output.putInt(this.alreadyReadPages);
      } else {
        output.put((byte)this.alreadyReadPages);
      }
    }

    if (this.canBeWrite) {
      bitHeaderWrite.addFlags(16);
    }

    if (this.customPages != nullptr && this.customPages.size() > 0) {
      bitHeaderWrite.addFlags(32);
      output.putInt(this.customPages.size());

      for (String string : this.customPages.values()) {
        GameWindow.WriteString(output, string);
      }
    }

    if (this.lockedBy != nullptr) {
      bitHeaderWrite.addFlags(64);
      GameWindow.WriteString(output, this.getLockedBy());
    }

    bitHeaderWrite.write();
    bitHeaderWrite.release();
  }

  void load(ByteBuffer input, int WorldVersion) {
    super.load(input, WorldVersion);
    this.numberOfPages = -1;
    this.alreadyReadPages = 0;
    this.canBeWrite = false;
    this.customPages = nullptr;
    this.lockedBy = nullptr;
    BitHeaderRead bitHeaderRead =
        BitHeader.allocRead(BitHeader.HeaderSize.Byte, input);
    if (!bitHeaderRead == 0)) {
        uint8_t byte0 = 0;
        if (bitHeaderRead.hasFlags(1)) {
          if (bitHeaderRead.hasFlags(2)) {
            byte0 = 1;
            this.numberOfPages = input.getShort();
          } else if (bitHeaderRead.hasFlags(4)) {
            byte0 = 2;
            this.numberOfPages = input.getInt();
          } else {
            this.numberOfPages = input.get();
          }
        }

        if (bitHeaderRead.hasFlags(8)) {
          if (byte0 == 1) {
            this.alreadyReadPages = input.getShort();
          } else if (byte0 == 2) {
            this.alreadyReadPages = input.getInt();
          } else {
            this.alreadyReadPages = input.get();
          }
        }

        this.canBeWrite = bitHeaderRead.hasFlags(16);
        if (bitHeaderRead.hasFlags(32)) {
          int int0 = input.getInt();
          if (int0 > 0) {
            this.customPages = std::make_unique<HashMap<>>();

            for (int int1 = 0; int1 < int0; int1++) {
              this.customPages.put(int1 + 1, GameWindow.ReadString(input));
            }
          }
        }

        if (bitHeaderRead.hasFlags(64)) {
          this.setLockedBy(GameWindow.ReadString(input));
        }
      }

    bitHeaderRead.release();
  }

  /**
   * @return the boredomChange
   */
  float getBoredomChange() {
    return !this.bAlreadyRead ? this.boredomChange : 0.0F;
  }

  /**
   * @return the unhappyChange
   */
  float getUnhappyChange() {
    return !this.bAlreadyRead ? this.unhappyChange : 0.0F;
  }

  /**
   * @return the stressChange
   */
  float getStressChange() {
    return !this.bAlreadyRead ? this.stressChange : 0.0F;
  }

  int getNumberOfPages() { return this.numberOfPages; }

  void setNumberOfPages(int _numberOfPages) {
    this.numberOfPages = _numberOfPages;
  }

  std::string getBookName() { return this.bookName; }

  void setBookName(const std::string &_bookName) { this.bookName = _bookName; }

  int getLvlSkillTrained() { return this.LvlSkillTrained; }

  void setLvlSkillTrained(int lvlSkillTrained) {
    this.LvlSkillTrained = lvlSkillTrained;
  }

  int getNumLevelsTrained() { return this.NumLevelsTrained; }

  void setNumLevelsTrained(int numLevelsTrained) {
    this.NumLevelsTrained = numLevelsTrained;
  }

  int getMaxLevelTrained() {
    return this.getLvlSkillTrained() + this.getNumLevelsTrained() - 1;
  }

  std::string getSkillTrained() { return this.SkillTrained; }

  void setSkillTrained(const std::string &skillTrained) {
    this.SkillTrained = skillTrained;
  }

  int getAlreadyReadPages() { return this.alreadyReadPages; }

  void setAlreadyReadPages(int _alreadyReadPages) {
    this.alreadyReadPages = _alreadyReadPages;
  }

  bool canBeWrite() { return this.canBeWrite; }

  void setCanBeWrite(bool _canBeWrite) { this.canBeWrite = _canBeWrite; }

public
  HashMap<Integer, String> getCustomPages() {
    if (this.customPages == nullptr) {
      this.customPages = std::make_unique<HashMap<>>();
      this.customPages.put(1, "");
    }

    return this.customPages;
  }

  void setCustomPages(String > _customPages) {
    this.customPages = _customPages;
  }

  void addPage(int index, const std::string &text) {
    if (text.length() > 16384) {
      text = text.substring(0, Math.min(text.length(), 16384));
    }

    if (this.customPages == nullptr) {
      this.customPages = std::make_unique<HashMap<>>();
    }

    this.customPages.put(index, text);
  }

  std::string seePage(int index) {
    if (this.customPages == nullptr) {
      this.customPages = std::make_unique<HashMap<>>();
      this.customPages.put(1, "");
    }

    return this.customPages.get(index);
  }

  std::string getLockedBy() { return this.lockedBy; }

  void setLockedBy(const std::string &_lockedBy) { this.lockedBy = _lockedBy; }

  int getPageToWrite() { return this.pageToWrite; }

  void setPageToWrite(int _pageToWrite) { this.pageToWrite = _pageToWrite; }

public
  List<String> getTeachedRecipes() { return this.teachedRecipes; }

  void setTeachedRecipes(List<String> _teachedRecipes) {
    this.teachedRecipes = _teachedRecipes;
  }
}
} // namespace types
} // namespace inventory
} // namespace zombie
