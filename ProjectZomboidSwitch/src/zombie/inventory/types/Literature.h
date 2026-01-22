#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameWindow.h"
#include "zombie/characters/professions/ProfessionFactory.h"
#include "zombie/characters/professions/ProfessionFactory/Profession.h"
#include "zombie/characters/traits/TraitCollection.h"
#include "zombie/characters/traits/TraitFactory.h"
#include "zombie/characters/traits/TraitFactory/Trait.h"
#include "zombie/core/Translator.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/ItemType.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/Item/Type.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {
namespace types {


class Literature : public InventoryItem {
public:
    bool bAlreadyRead = false;
    std::string requireInHandOrInventory = nullptr;
    std::string useOnConsume = nullptr;
    int numberOfPages = -1;
    std::string bookName = "";
    int LvlSkillTrained = -1;
    int NumLevelsTrained;
    std::string SkillTrained = "None";
    int alreadyReadPages = 0;
    bool canBeWrite = false;
   private std::unordered_map<int, std::string> customPages = nullptr;
    std::string lockedBy = nullptr;
    int pageToWrite;
   private List<std::string> teachedRecipes = nullptr;
    const int maxTextLength = 16384;

    public Literature(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      super(var1, var2, var3, var4);
      this.setBookName(var2);
      this.cat = ItemType.Literature;
      if (this.staticModel == nullptr) {
         this.staticModel = "Book";
      }
   }

    public Literature(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      super(var1, var2, var3, var4);
      this.setBookName(var2);
      this.cat = ItemType.Literature;
      if (this.staticModel == nullptr) {
         this.staticModel = "Book";
      }
   }

    bool IsLiterature() {
    return true;
   }

    int getSaveType() {
      return Type.Literature.ordinal();
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Literature";
   }

    void update() {
      if (this.container != nullptr) {
      }
   }

    bool finishupdate() {
    return true;
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
      if (this.getLvlSkillTrained() != -1) {
    LayoutItem var3 = var2.addItem();
         var3.setLabel(Translator.getText("Tooltip_BookTitle") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var3.setValue(
            Translator.getText("Tooltip_BookTitle_" + this.getLvlSkillTrained(), Translator.getText("Tooltip_BookTitle_" + this.getSkillTrained())),
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      }

      if (this.getBoredomChange() != 0.0F) {
    LayoutItem var13 = var2.addItem();
    int var4 = (int)this.getBoredomChange();
         var13.setLabel(Translator.getText("Tooltip_literature_Boredom_Reduction") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var13.setValueRight(var4, false);
      }

      if (this.getStressChange() != 0.0F) {
    LayoutItem var14 = var2.addItem();
    int var21 = (int)(this.getStressChange() * 100.0F);
         var14.setLabel(Translator.getText("Tooltip_literature_Stress_Reduction") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var14.setValueRight(var21, false);
      }

      if (this.getUnhappyChange() != 0.0F) {
    LayoutItem var15 = var2.addItem();
    int var22 = (int)this.getUnhappyChange();
         var15.setLabel(Translator.getText("Tooltip_food_Unhappiness") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var15.setValueRight(var22, false);
      }

      if (this.getNumberOfPages() != -1) {
    LayoutItem var16 = var2.addItem();
    int var23 = this.getAlreadyReadPages();
         if (var1.getCharacter() != nullptr) {
            var23 = var1.getCharacter().getAlreadyReadPages(this.getFullType());
         }

         var16.setLabel(Translator.getText("Tooltip_literature_Number_of_Pages") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var16.setValue(var23 + " / " + this.getNumberOfPages(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.getLvlSkillTrained() != -1) {
    LayoutItem var17 = var2.addItem();
    std::string var24 = this.getLvlSkillTrained() + "";
         if (this.getLvlSkillTrained() != this.getMaxLevelTrained()) {
            var24 = var24 + "-" + this.getMaxLevelTrained();
         }

         var17.setLabel(Translator.getText("Tooltip_Literature_XpMultiplier", var24), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (this.getTeachedRecipes() != nullptr) {
         for (std::string var5 : this.getTeachedRecipes()) {
    LayoutItem var18 = var2.addItem();
    std::string var6 = Translator.getRecipeName(var5);
            var18.setLabel(Translator.getText("Tooltip_Literature_TeachedRecipes", var6), 1.0F, 1.0F, 0.8F, 1.0F);
         }

         if (var1.getCharacter() != nullptr) {
    LayoutItem var19 = var2.addItem();
    std::string var26 = Translator.getText("Tooltip_literature_NotBeenRead");
            if (var1.getCharacter().getKnownRecipes().containsAll(this.getTeachedRecipes())) {
               var26 = Translator.getText("Tooltip_literature_HasBeenRead");
            }

            var19.setLabel(var26, 1.0F, 1.0F, 0.8F, 1.0F);
            if (var1.getCharacter().getKnownRecipes().containsAll(this.getTeachedRecipes())) {
    Profession var27 = ProfessionFactory.getProfession(var1.getCharacter().getDescriptor().getProfession());
    TraitCollection var28 = var1.getCharacter().getTraits();
    int var7 = 0;
    int var8 = 0;

               for (int var9 = 0; var9 < this.getTeachedRecipes().size(); var9++) {
    std::string var10 = this.getTeachedRecipes().get(var9);
                  if (var27 != nullptr && var27.getFreeRecipes().contains(var10)) {
                     var7++;
                  }

                  for (int var11 = 0; var11 < var28.size(); var11++) {
    Trait var12 = TraitFactory.getTrait(var28.get(var11));
                     if (var12 != nullptr && var12.getFreeRecipes().contains(var10)) {
                        var8++;
                     }
                  }
               }

               if (var7 > 0 || var8 > 0) {
                  var19 = var2.addItem();
                  var19.setLabel(Translator.getText("Tooltip_literature_AlreadyKnown"), 0.0F, 1.0F, 0.8F, 1.0F);
               }
            }
         }
      }
   }

    void save(ByteBuffer var1, bool var2) {
      super.save(var1, var2);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
    uint8_t var4 = 0;
      if (this.numberOfPages >= 127 && this.numberOfPages < 32767) {
         var4 = 1;
      } else if (this.numberOfPages >= 32767) {
         var4 = 2;
      }

      if (this.numberOfPages != -1) {
         var3.addFlags(1);
         if (var4 == 1) {
            var3.addFlags(2);
            var1.putShort((short)this.numberOfPages);
         } else if (var4 == 2) {
            var3.addFlags(4);
            var1.putInt(this.numberOfPages);
         } else {
            var1.put((byte)this.numberOfPages);
         }
      }

      if (this.alreadyReadPages != 0) {
         var3.addFlags(8);
         if (var4 == 1) {
            var1.putShort((short)this.alreadyReadPages);
         } else if (var4 == 2) {
            var1.putInt(this.alreadyReadPages);
         } else {
            var1.put((byte)this.alreadyReadPages);
         }
      }

      if (this.canBeWrite) {
         var3.addFlags(16);
      }

      if (this.customPages != nullptr && this.customPages.size() > 0) {
         var3.addFlags(32);
         var1.putInt(this.customPages.size());

         for (std::string var6 : this.customPages.values()) {
            GameWindow.WriteString(var1, var6);
         }
      }

      if (this.lockedBy != nullptr) {
         var3.addFlags(64);
         GameWindow.WriteString(var1, this.getLockedBy());
      }

      var3.write();
      var3.release();
   }

    void load(ByteBuffer var1, int var2) {
      super.load(var1, var2);
      this.numberOfPages = -1;
      this.alreadyReadPages = 0;
      this.canBeWrite = false;
      this.customPages = nullptr;
      this.lockedBy = nullptr;
    BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      if (!var3 == 0)) {
    uint8_t var4 = 0;
         if (var3.hasFlags(1)) {
            if (var3.hasFlags(2)) {
               var4 = 1;
               this.numberOfPages = var1.getShort();
            } else if (var3.hasFlags(4)) {
               var4 = 2;
               this.numberOfPages = var1.getInt();
            } else {
               this.numberOfPages = var1.get();
            }
         }

         if (var3.hasFlags(8)) {
            if (var4 == 1) {
               this.alreadyReadPages = var1.getShort();
            } else if (var4 == 2) {
               this.alreadyReadPages = var1.getInt();
            } else {
               this.alreadyReadPages = var1.get();
            }
         }

         this.canBeWrite = var3.hasFlags(16);
         if (var3.hasFlags(32)) {
    int var5 = var1.getInt();
            if (var5 > 0) {
               this.customPages = std::make_unique<std::unordered_map<>>();

               for (int var6 = 0; var6 < var5; var6++) {
                  this.customPages.put(var6 + 1, GameWindow.ReadString(var1));
               }
            }
         }

         if (var3.hasFlags(64)) {
            this.setLockedBy(GameWindow.ReadString(var1));
         }
      }

      var3.release();
   }

    float getBoredomChange() {
      return !this.bAlreadyRead ? this.boredomChange : 0.0F;
   }

    float getUnhappyChange() {
      return !this.bAlreadyRead ? this.unhappyChange : 0.0F;
   }

    float getStressChange() {
      return !this.bAlreadyRead ? this.stressChange : 0.0F;
   }

    int getNumberOfPages() {
      return this.numberOfPages;
   }

    void setNumberOfPages(int var1) {
      this.numberOfPages = var1;
   }

    std::string getBookName() {
      return this.bookName;
   }

    void setBookName(const std::string& var1) {
      this.bookName = var1;
   }

    int getLvlSkillTrained() {
      return this.LvlSkillTrained;
   }

    void setLvlSkillTrained(int var1) {
      this.LvlSkillTrained = var1;
   }

    int getNumLevelsTrained() {
      return this.NumLevelsTrained;
   }

    void setNumLevelsTrained(int var1) {
      this.NumLevelsTrained = var1;
   }

    int getMaxLevelTrained() {
      return this.getLvlSkillTrained() + this.getNumLevelsTrained() - 1;
   }

    std::string getSkillTrained() {
      return this.SkillTrained;
   }

    void setSkillTrained(const std::string& var1) {
      this.SkillTrained = var1;
   }

    int getAlreadyReadPages() {
      return this.alreadyReadPages;
   }

    void setAlreadyReadPages(int var1) {
      this.alreadyReadPages = var1;
   }

    bool canBeWrite() {
      return this.canBeWrite;
   }

    void setCanBeWrite(bool var1) {
      this.canBeWrite = var1;
   }

   public std::unordered_map<int, std::string> getCustomPages() {
      if (this.customPages == nullptr) {
         this.customPages = std::make_unique<std::unordered_map<>>();
         this.customPages.put(1, "");
      }

      return this.customPages;
   }

    void setCustomPages(std::string> var1) {
      this.customPages = var1;
   }

    void addPage(int var1, const std::string& var2) {
      if (var2.length() > 16384) {
         var2 = var2.substr(0, Math.min(var2.length(), 16384));
      }

      if (this.customPages == nullptr) {
         this.customPages = std::make_unique<std::unordered_map<>>();
      }

      this.customPages.put(var1, var2);
   }

    std::string seePage(int var1) {
      if (this.customPages == nullptr) {
         this.customPages = std::make_unique<std::unordered_map<>>();
         this.customPages.put(1, "");
      }

      return this.customPages.get(var1);
   }

    std::string getLockedBy() {
      return this.lockedBy;
   }

    void setLockedBy(const std::string& var1) {
      this.lockedBy = var1;
   }

    int getPageToWrite() {
      return this.pageToWrite;
   }

    void setPageToWrite(int var1) {
      this.pageToWrite = var1;
   }

   public List<std::string> getTeachedRecipes() {
      return this.teachedRecipes;
   }

    void setTeachedRecipes(List<std::string> var1) {
      this.teachedRecipes = var1;
   }
}
} // namespace types
} // namespace inventory
} // namespace zombie
