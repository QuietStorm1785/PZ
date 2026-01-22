#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/LuaClosure.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/SystemDisabler.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Core.h"
#include "zombie/core/Rand.h"
#include "zombie/core/network/ByteBufferWriter.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/inventory/ItemContainer/CategoryPredicate.h"
#include "zombie/inventory/ItemContainer/Comparators.h"
#include "zombie/inventory/ItemContainer/ConditionComparator.h"
#include "zombie/inventory/ItemContainer/EvalArgComparator.h"
#include "zombie/inventory/ItemContainer/EvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/EvalComparator.h"
#include "zombie/inventory/ItemContainer/EvalPredicate.h"
#include "zombie/inventory/ItemContainer/InventoryItemList.h"
#include "zombie/inventory/ItemContainer/InventoryItemListPool.h"
#include "zombie/inventory/ItemContainer/Predicates.h"
#include "zombie/inventory/ItemContainer/TagEvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/TagEvalPredicate.h"
#include "zombie/inventory/ItemContainer/TagPredicate.h"
#include "zombie/inventory/ItemContainer/TypeEvalArgPredicate.h"
#include "zombie/inventory/ItemContainer/TypeEvalPredicate.h"
#include "zombie/inventory/ItemContainer/TypePredicate.h"
#include "zombie/inventory/types/AlarmClock.h"
#include "zombie/inventory/types/AlarmClockClothing.h"
#include "zombie/inventory/types/Clothing.h"
#include "zombie/inventory/types/Drainable.h"
#include "zombie/inventory/types/DrainableComboItem.h"
#include "zombie/inventory/types/Food.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/inventory/types/InventoryContainer.h"
#include "zombie/inventory/types/Key.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/IsoBarbecue.h"
#include "zombie/iso/objects/IsoCompost.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoFireplace.h"
#include "zombie/iso/objects/IsoMannequin.h"
#include "zombie/iso/objects/IsoStove.h"
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/PacketTypes/PacketType.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/BaseVehicle.h"
#include "zombie/vehicles/VehiclePart.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {


class ItemContainer {

public:
   static inline std::vector<std::shared_ptr<InventoryItem>> tempList;
   static inline std::vector<std::shared_ptr<IsoObject>> s_tempObjects;
   bool active = false;
   bool dirty = true;
   bool isDevice = false;
   float ageFactor = 1.0f;
   float cookingFactor = 1.0f;
   int capacity = 50;
   std::shared_ptr<InventoryItem> containingItem;
   std::vector<std::shared_ptr<InventoryItem>> items;
   std::vector<std::shared_ptr<InventoryItem>> includingObsoleteItems;
   std::shared_ptr<IsoObject> parent;
   std::shared_ptr<IsoGridSquare> sourceGrid;
   std::shared_ptr<VehiclePart> vehiclePart;
   std::shared_ptr<InventoryContainer> inventoryContainer;
   bool explored = false;
   std::string type = "none";
   int id = 0;
   bool drawDirty = true;
   float customTemperature = 0.0f;
   bool hasBeenLooted = false;
   std::string openSound;
   std::string closeSound;
   std::string putSound;
   std::string onlyAcceptCategory;
   std::string acceptItemFunction;
   int weightReduction = 0;
   std::string containerPosition;
   std::string freezerPosition;
   // ThreadLocal and Java-specific static members removed for idiomatic C++


   ItemContainer(int id_, const std::string& type_, std::shared_ptr<IsoGridSquare> grid, std::shared_ptr<IsoObject> obj)
      : id(id_), parent(obj), type(type_), sourceGrid(grid) {
      if (type_ == "fridge") {
         ageFactor = 0.02f;
         cookingFactor = 0.0f;
      }
   }

   ItemContainer(const std::string& type_, std::shared_ptr<IsoGridSquare> grid, std::shared_ptr<IsoObject> obj)
      : id(-1), parent(obj), type(type_), sourceGrid(grid) {
      if (type_ == "fridge") {
         ageFactor = 0.02f;
         cookingFactor = 0.0f;
      }
   }

   ItemContainer(int id_) : id(id_) {}
   ItemContainer() : id(-1) {}

    static float floatingPointCorrection(float var0) {
    uint8_t var1 = 100;
    float var2 = var0 * var1;
      return (float)((int)(var2 - (int)var2 >= 0.5F ? var2 + 1.0F : var2)) / var1;
   }

    int getCapacity() {
      return this.Capacity;
   }

    void setCapacity(int var1) {
      this.Capacity = var1;
   }

    InventoryItem FindAndReturnWaterItem(int var1) {
      for (int var2 = 0; var2 < this.getItems().size(); var2++) {
    InventoryItem var3 = this.getItems().get(var2);
         if (dynamic_cast<DrainableComboItem*>(var3) != nullptr && var3.isWaterSource()) {
    DrainableComboItem var4 = (DrainableComboItem)var3;
            if (var4.getDrainableUsesInt() >= var1) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    InventoryItem getItemFromTypeRecurse(const std::string& var1) {
      return this.getFirstTypeRecurse(var1);
   }

    int getEffectiveCapacity(IsoGameCharacter var1) {
      if (var1 != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr) && !(this.dynamic_cast<IsoDeadBody*>(parent) != nullptr) && !"floor" == this.getType())) {
         if (var1.Traits.Organized.isSet()) {
            return (int)Math.max(this.Capacity * 1.3F, (float)(this.Capacity + 1));
         }

         if (var1.Traits.Disorganized.isSet()) {
            return (int)Math.max(this.Capacity * 0.7F, 1.0F);
         }
      }

      return this.Capacity;
   }

    bool hasRoomFor(IsoGameCharacter var1, InventoryItem var2) {
      if (this.vehiclePart != nullptr && this.vehiclePart.getId().contains("Seat") && this.Items.empty() && var2.getUnequippedWeight() <= 50.0F) {
    return true;
      } else if (floatingPointCorrection(this.getCapacityWeight()) + var2.getUnequippedWeight() <= this.getEffectiveCapacity(var1)) {
         return this.getContainingItem() != nullptr
               && this.getContainingItem().getEquipParent() != nullptr
               && this.getContainingItem().getEquipParent().getInventory() != nullptr
               && !this.getContainingItem().getEquipParent().getInventory().contains(var2)
            ? floatingPointCorrection(this.getContainingItem().getEquipParent().getInventory().getCapacityWeight()) + var2.getUnequippedWeight()
               <= this.getContainingItem().getEquipParent().getInventory().getEffectiveCapacity(var1)
            : true;
      } else {
    return false;
      }
   }

    bool hasRoomFor(IsoGameCharacter var1, float var2) {
    return floatingPointCorrection();
   }

    bool isItemAllowed(InventoryItem var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    std::string var2 = this.getOnlyAcceptCategory();
         if (var2 != nullptr && !var2.equalsIgnoreCase(var1.getCategory())) {
    return false;
         } else {
    std::string var3 = this.getAcceptItemFunction();
            if (var3 != nullptr) {
    void* var4 = LuaManager.getFunctionObject(var3);
               if (var4 != nullptr) {
    bool var5 = LuaManager.caller.protectedCallBoolean(LuaManager.thread, var4, this, var1);
                  if (var5 != bool.TRUE) {
    return false;
                  }
               }
            }

            if (this.parent != nullptr && !this.parent.isItemAllowedInContainer(this, var1)) {
    return false;
            } else if (this.getType() == "clothingrack") && !(dynamic_cast<Clothing*>(var1) != nullptr)) {
    return false;
            } else if (this.getParent() != nullptr
               && this.getParent().getProperties() != nullptr
               && this.getParent().getProperties().Val("CustomName") != nullptr
               && this.getParent().getProperties().Val("CustomName") == "Toaster")
               && !var1.hasTag("FitsToaster")) {
    return false;
            } else {
               if (this.getParent() != nullptr && this.getParent().getProperties() != nullptr && this.getParent().getProperties().Val("GroupName") != nullptr) {
                  boolean var6 = this.getParent().getProperties().Val("GroupName") == "Coffee")
                     || this.getParent().getProperties().Val("GroupName") == "Espresso");
                  if (var6 && !var1.hasTag("CoffeeMaker")) {
    return false;
                  }
               }

    return true;
            }
         }
      }
   }

    bool isRemoveItemAllowed(InventoryItem var1) {
    return var1 = = nullptr ? false : this.parent == nullptr || this.parent.isRemoveItemAllowedFromContainer(this, var1);
   }

    bool isExplored() {
      return this.bExplored;
   }

    void setExplored(bool var1) {
      this.bExplored = var1;
   }

    bool isInCharacterInventory(IsoGameCharacter var1) {
      if (var1.getInventory() == this) {
    return true;
      } else {
         if (this.containingItem != nullptr) {
            if (var1.getInventory().contains(this.containingItem, true)) {
    return true;
            }

            if (this.containingItem.getContainer() != nullptr) {
               return this.containingItem.getContainer().isInCharacterInventory(var1);
            }
         }

    return false;
      }
   }

    bool isInside(InventoryItem var1) {
      if (this.containingItem == nullptr) {
    return false;
      } else {
         return this.containingItem == var1 ? true : this.containingItem.getContainer() != nullptr && this.containingItem.getContainer().isInside(var1);
      }
   }

    InventoryItem getContainingItem() {
      return this.containingItem;
   }

    InventoryItem DoAddItem(InventoryItem var1) {
      return this.AddItem(var1);
   }

    InventoryItem DoAddItemBlind(InventoryItem var1) {
      return this.AddItem(var1);
   }

    // Adds multiple items of the same type and returns them
    std::vector<std::shared_ptr<InventoryItem>> AddItems(const std::string& type, int count) {
        std::vector<std::shared_ptr<InventoryItem>> addedItems;

        for (int i = 0; i < count; ++i) {
            auto item = AddItem(type);
            if (item) {
                addedItems.push_back(item);
            }
        }

        return addedItems;
    }


   void addItems(const std::shared_ptr<InventoryItem>& item, int count) {
      for (int i = 0; i < count; ++i) {
         addItem(item->getFullType());
      }
   }

    int getNumberOfItem(const std::string& var1, bool var2) {
      return this.getNumberOfItem(var1, var2, false);
   }

    int getNumberOfItem(const std::string& var1) {
      return this.getNumberOfItem(var1, false);
   }

    int getNumberOfItem(const std::string& var1, bool var2, std::vector<ItemContainer> var3) {
    int var4 = this.getNumberOfItem(var1, var2);
      if (var3 != nullptr) {
    for (auto& var6 : var3)            if (var6 != this) {
               var4 += var6.getNumberOfItem(var1, var2);
            }
         }
      }

    return var4;
   }

    int getNumberOfItem(const std::string& var1, bool var2, bool var3) {
    int var4 = 0;

      for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
         if (var6.getFullType() == var1) || var6.getType() == var1)) {
            var4++;
         } else if (var3 && dynamic_cast<InventoryContainer*>(var6) != nullptr) {
            var4 += ((InventoryContainer)var6).getItemContainer().getNumberOfItem(var1);
         } else if (var2 && dynamic_cast<DrainableComboItem*>(var6) != nullptr && ((DrainableComboItem)var6).getReplaceOnDeplete() != nullptr) {
    DrainableComboItem var7 = (DrainableComboItem)var6;
            if (var7.getReplaceOnDepleteFullType() == var1) || var7.getReplaceOnDeplete() == var1)) {
               var4++;
            }
         }
      }

    return var4;
   }


    std::shared_ptr<InventoryItem> addItem(const std::shared_ptr<InventoryItem>& item) {
        return addItemImpl(item);
    }

    std::shared_ptr<InventoryItem> addItemImpl(const std::shared_ptr<InventoryItem>& item) {
        if (!item) return nullptr;
        // containsID and getItemWithID logic omitted for brevity; implement as needed
        drawDirty = true;
        if (parent) dirty = true;
        // parent->DirtySlice() if not IsoGameCharacter
        if (item->container) item->container->remove(item);
        item->container = this;
        items.push_back(item);
        // IsoWorld::instance->CurrentCell->addToProcessItems(item) if needed
        return item;
    }


      std::shared_ptr<InventoryItem> addItemBlind(const std::shared_ptr<InventoryItem>& item) {
            if (!item) return nullptr;
            if (item->getWeight() + getCapacityWeight() > getCapacity()) return nullptr;
            // parent->DirtySlice() if not IsoGameCharacter
            items.push_back(item);
            return item;
      }


    std::shared_ptr<InventoryItem> addItem(const std::string& type) {
        drawDirty = true;
        if (parent) dirty = true;
        auto* itemDef = ScriptManager::instance.FindItem(type);
        if (!itemDef) {
            DebugLog::log("ERROR: ItemContainer.addItem: can't find " + type);
            return nullptr;
        }
        if (itemDef->OBSOLETE) return nullptr;
        std::shared_ptr<InventoryItem> lastItem;
        int count = itemDef->getCount();
        for (int i = 0; i < count; ++i) {
            lastItem = InventoryItemFactory::CreateItem(type);
            if (!lastItem) return nullptr;
            lastItem->container = this;
            items.push_back(lastItem);
            if (auto* food = dynamic_cast<Food*>(lastItem.get()))
                food->setHeat(getTemperature());
            // IsoWorld::instance->CurrentCell->addToProcessItems(lastItem) if needed
        }
        return lastItem;
    }


      bool addItem(const std::string& type, float usedDelta) {
            drawDirty = true;
            if (parent) dirty = true;
            auto item = InventoryItemFactory::CreateItem(type);
            if (!item) return false;
            if (auto* drainable = dynamic_cast<Drainable*>(item.get()))
                  drainable->setUsedDelta(usedDelta);
            item->container = this;
            items.push_back(item);
            return true;
      }


   bool contains(const std::shared_ptr<InventoryItem>& item) const {
      return std::find(items.begin(), items.end(), item) != items.end();
   }


      bool containsWithModule(const std::string& type, bool checkDrainable = false) const {
            std::string module = "Base";
            std::string itemType = type;
            auto dot = type.find('.');
            if (dot != std::string::npos) {
                  module = type.substr(0, dot);
                  itemType = type.substr(dot + 1);
            }
            for (const auto& item : items) {
                  if (!item) continue;
                  if (item->type == itemType && item->getModule() == module && (!checkDrainable || !(dynamic_cast<DrainableComboItem*>(item.get())) || static_cast<DrainableComboItem*>(item.get())->getUsedDelta() > 0.0f))
                        return true;
            }
            return false;
      }


   void removeItemOnServer(const std::shared_ptr<InventoryItem>& item) {
      if (GameClient::bClient) {
         if (containingItem && containingItem->getWorldItem())
            GameClient::instance->addToItemRemoveSendBuffer(containingItem->getWorldItem(), this, item);
         else
            GameClient::instance->addToItemRemoveSendBuffer(parent, this, item);
      }
   }


   void addItemOnServer(const std::shared_ptr<InventoryItem>& item) {
      if (GameClient::bClient) {
         if (containingItem && containingItem->getWorldItem())
            GameClient::instance->addToItemSendBuffer(containingItem->getWorldItem(), this, item);
         else
            GameClient::instance->addToItemSendBuffer(parent, this, item);
      }
   }

    bool contains(InventoryItem var1, bool var2) {
    InventoryItemList var3 = (InventoryItemList)TL_itemListPool.get().alloc();

      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         if (var5 == nullptr) {
            this.Items.remove(var4);
            var4--;
         } else {
            if (var5 == var1) {
               TL_itemListPool.get().release(var3);
    return true;
            }

            if (var2 && dynamic_cast<InventoryContainer*>(var5) != nullptr && ((InventoryContainer)var5).getInventory() != nullptr && !var3.contains(var5)) {
               var3.push_back(var5);
            }
         }
      }

      for (int var6 = 0; var6 < var3.size(); var6++) {
    ItemContainer var7 = ((InventoryContainer)var3.get(var6)).getInventory();
         if (var7.contains(var1, var2)) {
            TL_itemListPool.get().release(var3);
    return true;
         }
      }

      TL_itemListPool.get().release(var3);
    return false;
   }

    bool contains(const std::string& var1, bool var2) {
      return this.contains(var1, var2, false);
   }

    bool containsType(const std::string& var1) {
      return this.contains(var1, false, false);
   }

    bool containsTypeRecurse(const std::string& var1) {
      return this.contains(var1, true, false);
   }

    bool testBroken(bool var1, InventoryItem var2) {
      return !var1 ? true : !var2.isBroken();
   }

    bool contains(const std::string& var1, bool var2, bool var3) {
    InventoryItemList var4 = (InventoryItemList)TL_itemListPool.get().alloc();
      if (var1.contains("Type:")) {
         for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
            if (var1.contains("Food") && dynamic_cast<Food*>(var6) != nullptr) {
               TL_itemListPool.get().release(var4);
    return true;
            }

            if (var1.contains("Weapon") && dynamic_cast<HandWeapon*>(var6) != nullptr && this.testBroken(var3, var6)) {
               TL_itemListPool.get().release(var4);
    return true;
            }

            if (var1.contains("AlarmClock") && dynamic_cast<AlarmClock*>(var6) != nullptr) {
               TL_itemListPool.get().release(var4);
    return true;
            }

            if (var1.contains("AlarmClockClothing") && dynamic_cast<AlarmClockClothing*>(var6) != nullptr) {
               TL_itemListPool.get().release(var4);
    return true;
            }

            if (var2 && dynamic_cast<InventoryContainer*>(var6) != nullptr && ((InventoryContainer)var6).getInventory() != nullptr && !var4.contains(var6)) {
               var4.push_back(var6);
            }
         }
      } else if (var1.contains("/")) {
         std::string[] var12 = var1.split("/");

    for (auto& var9 : var12)            for (int var10 = 0; var10 < this.Items.size(); var10++) {
    InventoryItem var11 = this.Items.get(var10);
               if (compareType(var9.trim(), var11) && this.testBroken(var3, var11)) {
                  TL_itemListPool.get().release(var4);
    return true;
               }

               if (var2 && dynamic_cast<InventoryContainer*>(var11) != nullptr && ((InventoryContainer)var11).getInventory() != nullptr && !var4.contains(var11)) {
                  var4.push_back(var11);
               }
            }
         }
      } else {
         for (int var13 = 0; var13 < this.Items.size(); var13++) {
    InventoryItem var16 = this.Items.get(var13);
            if (var16 == nullptr) {
               this.Items.remove(var13);
               var13--;
            } else {
               if (compareType(var1.trim(), var16) && this.testBroken(var3, var16)) {
                  TL_itemListPool.get().release(var4);
    return true;
               }

               if (var2 && dynamic_cast<InventoryContainer*>(var16) != nullptr && ((InventoryContainer)var16).getInventory() != nullptr && !var4.contains(var16)) {
                  var4.push_back(var16);
               }
            }
         }
      }

      for (int var14 = 0; var14 < var4.size(); var14++) {
    ItemContainer var17 = ((InventoryContainer)var4.get(var14)).getInventory();
         if (var17.contains(var1, var2, var3)) {
            TL_itemListPool.get().release(var4);
    return true;
         }
      }

      TL_itemListPool.get().release(var4);
    return false;
   }

    bool contains(const std::string& var1) {
      return this.contains(var1, false);
   }


      static std::shared_ptr<InventoryItem> getBestOf(const std::vector<std::shared_ptr<InventoryItem>>& items, const std::function<int(const std::shared_ptr<InventoryItem>&, const std::shared_ptr<InventoryItem>&)>& comparator) {
            if (items.empty()) return nullptr;
            auto best = items[0];
            for (size_t i = 1; i < items.size(); ++i) {
                  if (comparator(items[i], best) > 0) best = items[i];
            }
            return best;
      }


      std::shared_ptr<InventoryItem> getBest(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& predicate,
                                                                const std::function<int(const std::shared_ptr<InventoryItem>&, const std::shared_ptr<InventoryItem>&)>& comparator) {
            std::vector<std::shared_ptr<InventoryItem>> matches;
            getAll(predicate, matches);
            return getBestOf(matches, comparator);
      }


      std::shared_ptr<InventoryItem> getBestRecurse(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& predicate,
                                                                           const std::function<int(const std::shared_ptr<InventoryItem>&, const std::shared_ptr<InventoryItem>&)>& comparator) {
            std::vector<std::shared_ptr<InventoryItem>> matches;
            getAllRecurse(predicate, matches);
            return getBestOf(matches, comparator);
      }

    InventoryItem getBestType(const std::string& var1, Comparator<InventoryItem> var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);

    InventoryItem var4;
      try {
         var4 = this.getBest(var3, var2);
      } finally {
         TL_predicates.get().type.release(var3);
      }

    return var4;
   }

    InventoryItem getBestTypeRecurse(const std::string& var1, Comparator<InventoryItem> var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);

    InventoryItem var4;
      try {
         var4 = this.getBestRecurse(var3, var2);
      } finally {
         TL_predicates.get().type.release(var3);
      }

    return var4;
   }

    InventoryItem getBestEval(LuaClosure var1, LuaClosure var2) {
    EvalPredicate var3 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    EvalComparator var4 = ((EvalComparator)TL_comparators.get().eval.alloc()).init(var2);

    InventoryItem var5;
      try {
         var5 = this.getBest(var3, var4);
      } finally {
         TL_predicates.get().eval.release(var3);
         TL_comparators.get().eval.release(var4);
      }

    return var5;
   }

    InventoryItem getBestEvalRecurse(LuaClosure var1, LuaClosure var2) {
    EvalPredicate var3 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    EvalComparator var4 = ((EvalComparator)TL_comparators.get().eval.alloc()).init(var2);

    InventoryItem var5;
      try {
         var5 = this.getBestRecurse(var3, var4);
      } finally {
         TL_predicates.get().eval.release(var3);
         TL_comparators.get().eval.release(var4);
      }

    return var5;
   }

    InventoryItem getBestEvalArg(LuaClosure var1, LuaClosure var2, void* var3) {
    EvalArgPredicate var4 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var3);
    EvalArgComparator var5 = ((EvalArgComparator)TL_comparators.get().evalArg.alloc()).init(var2, var3);

    InventoryItem var6;
      try {
         var6 = this.getBest(var4, var5);
      } finally {
         TL_predicates.get().evalArg.release(var4);
         TL_comparators.get().evalArg.release(var5);
      }

    return var6;
   }

    InventoryItem getBestEvalArgRecurse(LuaClosure var1, LuaClosure var2, void* var3) {
    EvalArgPredicate var4 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var3);
    EvalArgComparator var5 = ((EvalArgComparator)TL_comparators.get().evalArg.alloc()).init(var2, var3);

    InventoryItem var6;
      try {
         var6 = this.getBestRecurse(var4, var5);
      } finally {
         TL_predicates.get().evalArg.release(var4);
         TL_comparators.get().evalArg.release(var5);
      }

    return var6;
   }

    InventoryItem getBestTypeEval(const std::string& var1, LuaClosure var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    EvalComparator var4 = ((EvalComparator)TL_comparators.get().eval.alloc()).init(var2);

    InventoryItem var5;
      try {
         var5 = this.getBest(var3, var4);
      } finally {
         TL_predicates.get().type.release(var3);
         TL_comparators.get().eval.release(var4);
      }

    return var5;
   }

    InventoryItem getBestTypeEvalRecurse(const std::string& var1, LuaClosure var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    EvalComparator var4 = ((EvalComparator)TL_comparators.get().eval.alloc()).init(var2);

    InventoryItem var5;
      try {
         var5 = this.getBestRecurse(var3, var4);
      } finally {
         TL_predicates.get().type.release(var3);
         TL_comparators.get().eval.release(var4);
      }

    return var5;
   }

    InventoryItem getBestTypeEvalArg(const std::string& var1, LuaClosure var2, void* var3) {
    TypePredicate var4 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    EvalArgComparator var5 = ((EvalArgComparator)TL_comparators.get().evalArg.alloc()).init(var2, var3);

    InventoryItem var6;
      try {
         var6 = this.getBest(var4, var5);
      } finally {
         TL_predicates.get().type.release(var4);
         TL_comparators.get().evalArg.release(var5);
      }

    return var6;
   }

    InventoryItem getBestTypeEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
    TypePredicate var4 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    EvalArgComparator var5 = ((EvalArgComparator)TL_comparators.get().evalArg.alloc()).init(var2, var3);

    InventoryItem var6;
      try {
         var6 = this.getBestRecurse(var4, var5);
      } finally {
         TL_predicates.get().type.release(var4);
         TL_comparators.get().evalArg.release(var5);
      }

    return var6;
   }

    InventoryItem getBestCondition(Predicate<InventoryItem> var1) {
    ConditionComparator var2 = (ConditionComparator)TL_comparators.get().condition.alloc();
    InventoryItem var3 = this.getBest(var1, var2);
      TL_comparators.get().condition.release(var2);
      if (var3 != nullptr && var3.getCondition() <= 0) {
         var3 = nullptr;
      }

    return var3;
   }

    InventoryItem getBestConditionRecurse(Predicate<InventoryItem> var1) {
    ConditionComparator var2 = (ConditionComparator)TL_comparators.get().condition.alloc();
    InventoryItem var3 = this.getBestRecurse(var1, var2);
      TL_comparators.get().condition.release(var2);
      if (var3 != nullptr && var3.getCondition() <= 0) {
         var3 = nullptr;
      }

    return var3;
   }

    InventoryItem getBestCondition(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    InventoryItem var3 = this.getBestCondition(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    InventoryItem getBestConditionRecurse(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    InventoryItem var3 = this.getBestConditionRecurse(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    InventoryItem getBestConditionEval(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    InventoryItem var3 = this.getBestCondition(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    InventoryItem getBestConditionEvalRecurse(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    InventoryItem var3 = this.getBestConditionRecurse(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    InventoryItem getBestConditionEvalArg(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    InventoryItem var4 = this.getBestCondition(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    InventoryItem getBestConditionEvalArgRecurse(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    InventoryItem var4 = this.getBestConditionRecurse(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    InventoryItem getFirstEval(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    InventoryItem var3 = this.getFirst(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    InventoryItem getFirstEvalArg(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirst(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    bool containsEval(LuaClosure var1) {
      return this.getFirstEval(var1) != nullptr;
   }

    bool containsEvalArg(LuaClosure var1, void* var2) {
      return this.getFirstEvalArg(var1, var2) != nullptr;
   }

    bool containsEvalRecurse(LuaClosure var1) {
      return this.getFirstEvalRecurse(var1) != nullptr;
   }

    bool containsEvalArgRecurse(LuaClosure var1, void* var2) {
      return this.getFirstEvalArgRecurse(var1, var2) != nullptr;
   }

    bool containsTag(const std::string& var1) {
      return this.getFirstTag(var1) != nullptr;
   }

    bool containsTagEval(const std::string& var1, LuaClosure var2) {
      return this.getFirstTagEval(var1, var2) != nullptr;
   }

    bool containsTagRecurse(const std::string& var1) {
      return this.getFirstTagRecurse(var1) != nullptr;
   }

    bool containsTagEvalRecurse(const std::string& var1, LuaClosure var2) {
      return this.getFirstTagEvalRecurse(var1, var2) != nullptr;
   }

    bool containsTagEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
      return this.getFirstTagEvalArgRecurse(var1, var2, var3) != nullptr;
   }

    bool containsTypeEvalRecurse(const std::string& var1, LuaClosure var2) {
      return this.getFirstTypeEvalRecurse(var1, var2) != nullptr;
   }

    bool containsTypeEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
      return this.getFirstTypeEvalArgRecurse(var1, var2, var3) != nullptr;
   }

    static bool compareType(const std::string& var0, const std::string& var1) {
      if (var0 != nullptr && var0.contains("/")) {
    int var2 = var0.indexOf(var1);
         if (var2 == -1) {
    return false;
         } else {
    char var3 = var2 > 0 ? var0.charAt(var2 - 1) : 0;
    char var4 = var2 + var1.length() < var0.length() ? var0.charAt(var2 + var1.length()) : 0;
    return var3 = = 0 && var4 == '/' || var3 == '/' && var4 == 0 || var3 == '/' && var4 == '/';
         }
      } else {
         return var0 == var1);
      }
   }

    static bool compareType(const std::string& var0, InventoryItem var1) {
      return var0 != nullptr && var0.indexOf(46) == -1
         ? compareType(var0, var1.getType())
         : compareType(var0, var1.getFullType()) || compareType(var0, var1.getType());
   }

    InventoryItem getFirst(Predicate<InventoryItem> var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3 == nullptr) {
            this.Items.remove(var2);
            var2--;
         } else if (var1.test(var3)) {
    return var3;
         }
      }

    return nullptr;
   }

    InventoryItem getFirstRecurse(Predicate<InventoryItem> var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (var4 == nullptr) {
            this.Items.remove(var3);
            var3--;
         } else {
            if (var1.test(var4)) {
               TL_itemListPool.get().release(var2);
    return var4;
            }

            if (dynamic_cast<InventoryContainer*>(var4) != nullptr) {
               var2.push_back(var4);
            }
         }
      }

      for (int var6 = 0; var6 < var2.size(); var6++) {
    ItemContainer var7 = ((InventoryContainer)var2.get(var6)).getInventory();
    InventoryItem var5 = var7.getFirstRecurse(var1);
         if (var5 != nullptr) {
            TL_itemListPool.get().release(var2);
    return var5;
         }
      }

      TL_itemListPool.get().release(var2);
    return nullptr;
   }

    // Gets up to 'count' items matching the predicate, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSome(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& pred, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        for (size_t i = 0; i < Items.size(); ++i) {
            auto item = Items[i];
            if (!item) {
                Items.erase(Items.begin() + i);
                --i;
            } else if (pred(item)) {
                result.push_back(item);
                if (static_cast<int>(result.size()) >= count) {
                    break;
                }
            }
        }

        return result;
    }

    // Gets up to 'count' items matching the predicate recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeRecurse(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& pred, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        std::vector<std::shared_ptr<InventoryItem>> containers;

        for (size_t i = 0; i < Items.size(); ++i) {
            auto item = Items[i];
            if (!item) {
                Items.erase(Items.begin() + i);
                --i;
            } else {
                if (pred(item)) {
                    result.push_back(item);
                    if (static_cast<int>(result.size()) >= count) {
                        return result;
                    }
                }

                if (auto container = std::dynamic_pointer_cast<InventoryContainer>(item)) {
                    containers.push_back(item);
                }
            }
        }

        for (const auto& container : containers) {
            auto subContainer = std::dynamic_pointer_cast<InventoryContainer>(container)->getInventory();
            result = subContainer->getSomeRecurse(pred, count, std::move(result));
            if (static_cast<int>(result.size()) >= count) {
                break;
            }
        }

        return result;
    }

    // Gets all items matching the predicate, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAll(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& pred, std::vector<std::shared_ptr<InventoryItem>> result) {
        for (size_t i = 0; i < Items.size(); ++i) {
            auto item = Items[i];
            if (!item) {
                Items.erase(Items.begin() + i);
                --i;
            } else if (pred(item)) {
                result.push_back(item);
            }
        }

        return result;
    }


    std::vector<std::shared_ptr<InventoryItem>> getAllRecurse(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& predicate, std::vector<std::shared_ptr<InventoryItem>>& out) {
        std::vector<std::shared_ptr<InventoryItem>> containers;
        for (auto it = items.begin(); it != items.end(); ) {
            if (!*it) { it = items.erase(it); continue; }
            if (predicate(*it)) out.push_back(*it);
            if (auto invCont = std::dynamic_pointer_cast<InventoryContainer>(*it))
                containers.push_back(*it);
            ++it;
        }
        for (const auto& cont : containers) {
            auto inv = std::dynamic_pointer_cast<InventoryContainer>(cont);
            if (inv && inv->getInventory())
                inv->getInventory()->getAllRecurse(predicate, out);
        }
        return out;
    }


      int getCount(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& predicate) {
            std::vector<std::shared_ptr<InventoryItem>> matches;
            getAll(predicate, matches);
            return static_cast<int>(matches.size());
      }


      int getCountRecurse(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& predicate) {
            std::vector<std::shared_ptr<InventoryItem>> matches;
            getAllRecurse(predicate, matches);
            return static_cast<int>(matches.size());
      }

    int getCountTag(const std::string& var1) {
    TagPredicate var2 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    int var3 = this.getCount(var2);
      TL_predicates.get().tag.release(var2);
    return var3;
   }

    int getCountTagEval(const std::string& var1, LuaClosure var2) {
    TagEvalPredicate var3 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    int var4 = this.getCount(var3);
      TL_predicates.get().tagEval.release(var3);
    return var4;
   }

    int getCountTagEvalArg(const std::string& var1, LuaClosure var2, void* var3) {
    TagEvalArgPredicate var4 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    int var5 = this.getCount(var4);
      TL_predicates.get().tagEvalArg.release(var4);
    return var5;
   }

    int getCountTagRecurse(const std::string& var1) {
    TagPredicate var2 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    int var3 = this.getCountRecurse(var2);
      TL_predicates.get().tag.release(var2);
    return var3;
   }

    int getCountTagEvalRecurse(const std::string& var1, LuaClosure var2) {
    TagEvalPredicate var3 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    int var4 = this.getCountRecurse(var3);
      TL_predicates.get().tagEval.release(var3);
    return var4;
   }

    int getCountTagEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
    TagEvalArgPredicate var4 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    int var5 = this.getCountRecurse(var4);
      TL_predicates.get().tagEvalArg.release(var4);
    return var5;
   }

    int getCountType(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    int var3 = this.getCount(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    int getCountTypeEval(const std::string& var1, LuaClosure var2) {
    TypeEvalPredicate var3 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    int var4 = this.getCount(var3);
      TL_predicates.get().typeEval.release(var3);
    return var4;
   }

    int getCountTypeEvalArg(const std::string& var1, LuaClosure var2, void* var3) {
    TypeEvalArgPredicate var4 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    int var5 = this.getCount(var4);
      TL_predicates.get().typeEvalArg.release(var4);
    return var5;
   }

    int getCountTypeRecurse(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    int var3 = this.getCountRecurse(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    int getCountTypeEvalRecurse(const std::string& var1, LuaClosure var2) {
    TypeEvalPredicate var3 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    int var4 = this.getCountRecurse(var3);
      TL_predicates.get().typeEval.release(var3);
    return var4;
   }

    int getCountTypeEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
    TypeEvalArgPredicate var4 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    int var5 = this.getCountRecurse(var4);
      TL_predicates.get().typeEvalArg.release(var4);
    return var5;
   }

    int getCountEval(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    int var3 = this.getCount(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    int getCountEvalArg(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    int var4 = this.getCount(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    int getCountEvalRecurse(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    int var3 = this.getCountRecurse(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    int getCountEvalArgRecurse(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    int var4 = this.getCountRecurse(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    InventoryItem getFirstCategory(const std::string& var1) {
    CategoryPredicate var2 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    InventoryItem var3 = this.getFirst(var2);
      TL_predicates.get().category.release(var2);
    return var3;
   }

    InventoryItem getFirstCategoryRecurse(const std::string& var1) {
    CategoryPredicate var2 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    InventoryItem var3 = this.getFirstRecurse(var2);
      TL_predicates.get().category.release(var2);
    return var3;
   }

    InventoryItem getFirstEvalRecurse(LuaClosure var1) {
    EvalPredicate var2 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    InventoryItem var3 = this.getFirstRecurse(var2);
      TL_predicates.get().eval.release(var2);
    return var3;
   }

    InventoryItem getFirstEvalArgRecurse(LuaClosure var1, void* var2) {
    EvalArgPredicate var3 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirstRecurse(var3);
      TL_predicates.get().evalArg.release(var3);
    return var4;
   }

    InventoryItem getFirstTag(const std::string& var1) {
    TagPredicate var2 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    InventoryItem var3 = this.getFirst(var2);
      TL_predicates.get().tag.release(var2);
    return var3;
   }

    InventoryItem getFirstTagRecurse(const std::string& var1) {
    TagPredicate var2 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    InventoryItem var3 = this.getFirstRecurse(var2);
      TL_predicates.get().tag.release(var2);
    return var3;
   }

    InventoryItem getFirstTagEval(const std::string& var1, LuaClosure var2) {
    TagEvalPredicate var3 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirstRecurse(var3);
      TL_predicates.get().tagEval.release(var3);
    return var4;
   }

    InventoryItem getFirstTagEvalRecurse(const std::string& var1, LuaClosure var2) {
    TagEvalPredicate var3 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirstRecurse(var3);
      TL_predicates.get().tagEval.release(var3);
    return var4;
   }

    InventoryItem getFirstTagEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
    TagEvalArgPredicate var4 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    InventoryItem var5 = this.getFirstRecurse(var4);
      TL_predicates.get().tagEvalArg.release(var4);
    return var5;
   }

    InventoryItem getFirstType(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    InventoryItem var3 = this.getFirst(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    InventoryItem getFirstTypeRecurse(const std::string& var1) {
    TypePredicate var2 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    InventoryItem var3 = this.getFirstRecurse(var2);
      TL_predicates.get().type.release(var2);
    return var3;
   }

    InventoryItem getFirstTypeEval(const std::string& var1, LuaClosure var2) {
    TypeEvalPredicate var3 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirstRecurse(var3);
      TL_predicates.get().typeEval.release(var3);
    return var4;
   }

    InventoryItem getFirstTypeEvalRecurse(const std::string& var1, LuaClosure var2) {
    TypeEvalPredicate var3 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    InventoryItem var4 = this.getFirstRecurse(var3);
      TL_predicates.get().typeEval.release(var3);
    return var4;
   }

    InventoryItem getFirstTypeEvalArgRecurse(const std::string& var1, LuaClosure var2, void* var3) {
    TypeEvalArgPredicate var4 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    InventoryItem var5 = this.getFirstRecurse(var4);
      TL_predicates.get().typeEvalArg.release(var4);
    return var5;
   }

    // Gets up to 'count' items of the given category, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeCategory(const std::string& category, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&category](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getCategory() == category;
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given category recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeCategoryRecurse(const std::string& category, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&category](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getCategory() == category;
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTag(const std::string& tag, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag);
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEval(const std::string& tag, LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get());
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure with argument, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEvalArg(const std::string& tag, LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get(), arg);
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagRecurse(const std::string& tag, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag);
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEvalRecurse(const std::string& tag, LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get());
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure with argument, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEvalArgRecurse(const std::string& tag, LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get(), arg);
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeType(const std::string& type, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type;
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEval(const std::string& type, LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type && closure && (*closure)(item.get());
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure with argument, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalArg(const std::string& type, LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type && closure && (*closure)(item.get(), arg);
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeRecurse(const std::string& type, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type;
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalRecurse(const std::string& type, LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type && closure && (*closure)(item.get());
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure with argument, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalArgRecurse(const std::string& type, LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&type, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getType() == type && closure && (*closure)(item.get(), arg);
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items matching a Lua closure, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeEval(LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [closure](const std::shared_ptr<InventoryItem>& item) {
            return closure && (*closure)(item.get());
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items matching a Lua closure with argument, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalArg(LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return closure && (*closure)(item.get(), arg);
        };
        return getSome(pred, count, std::move(result));
    }

    // Gets up to 'count' items matching a Lua closure recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalRecurse(LuaClosure* closure, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [closure](const std::shared_ptr<InventoryItem>& item) {
            return closure && (*closure)(item.get());
        };
        return getSomeRecurse(pred, count, std::move(result));
    }

    // Gets up to 'count' items matching a Lua closure with argument recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalArgRecurse(LuaClosure* closure, void* arg, int count, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return closure && (*closure)(item.get(), arg);
        };
        return getSomeRecurse(pred, count, std::move(result));
    }


      std::vector<std::shared_ptr<InventoryItem>> getAllCategory(const std::string& category, std::vector<std::shared_ptr<InventoryItem>>& out) {
         auto pred = [&category](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getCategory() == category;
         };
         return getAll(pred, out);
      }


      std::vector<std::shared_ptr<InventoryItem>> getAllCategoryRecurse(const std::string& category, std::vector<std::shared_ptr<InventoryItem>>& out) {
         auto pred = [&category](const std::shared_ptr<InventoryItem>& item) {
            return item && item->getCategory() == category;
         };
         return getAllRecurse(pred, out);
      }


      std::vector<std::shared_ptr<InventoryItem>> getAllTag(const std::string& tag, std::vector<std::shared_ptr<InventoryItem>>& out) {
         auto pred = [&tag](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag);
         };
         return getAll(pred, out);
      }

    // Returns all items with the given tag, filtered by a Lua closure, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEval(const std::string& tag, LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get());
        };
        return getAll(pred, std::move(result));
    }

    // Returns all items with the given tag, filtered by a Lua closure with argument, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEvalArg(const std::string& tag, LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get(), arg);
        };
        return getAll(pred, std::move(result));
    }

    // Returns all items with the given tag recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllTagRecurse(const std::string& tag, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag);
        };
        return getAllRecurse(pred, std::move(result));
    }

    // Returns all items with the given tag, filtered by Lua closure, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEvalRecurse(const std::string& tag, LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get());
        };
        return getAllRecurse(pred, std::move(result));
    }

    // Returns all items with the given tag, filtered by Lua closure with argument, recursively, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEvalArgRecurse(const std::string& tag, LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
        auto pred = [&tag, closure, arg](const std::shared_ptr<InventoryItem>& item) {
            return item && item->hasTag(tag) && closure && (*closure)(item.get(), arg);
        };
        return getAllRecurse(pred, std::move(result));
    }


    // Returns all items of a given type, appending to result
    std::vector<std::shared_ptr<InventoryItem>> getAllType(const std::string& type, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type;
          };
          return getAll(pred, std::move(result));
    }


    // Returns all items of a given type, filtered by a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEval(const std::string& type, LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type, closure](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type && closure && (*closure)(item.get());
          };
          return getAll(pred, std::move(result));
    }


    // Returns all items of a given type, filtered by a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalArg(const std::string& type, LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type, closure, arg](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type && closure && (*closure)(item.get(), arg);
          };
          return getAll(pred, std::move(result));
    }


    // Returns all items of a given type, recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeRecurse(const std::string& type, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type;
          };
          return getAllRecurse(pred, std::move(result));
    }


    // Returns all items of a given type, filtered by Lua closure, recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalRecurse(const std::string& type, LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type, closure](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type && closure && (*closure)(item.get());
          };
          return getAllRecurse(pred, std::move(result));
    }


    // Returns all items of a given type, filtered by Lua closure with argument, recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalArgRecurse(const std::string& type, LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [&type, closure, arg](const std::shared_ptr<InventoryItem>& item) {
                return item && item->getType() == type && closure && (*closure)(item.get(), arg);
          };
          return getAllRecurse(pred, std::move(result));
    }


    // Returns all items matching a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getAllEval(LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [closure](const std::shared_ptr<InventoryItem>& item) {
                return closure && (*closure)(item.get());
          };
          return getAll(pred, std::move(result));
    }


    // Returns all items matching a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalArg(LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [closure, arg](const std::shared_ptr<InventoryItem>& item) {
                return closure && (*closure)(item.get(), arg);
          };
          return getAll(pred, std::move(result));
    }


    // Returns all items matching a Lua closure, recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalRecurse(LuaClosure* closure, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [closure](const std::shared_ptr<InventoryItem>& item) {
                return closure && (*closure)(item.get());
          };
          return getAllRecurse(pred, std::move(result));
    }


    // Returns all items matching a Lua closure with argument, recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalArgRecurse(LuaClosure* closure, void* arg, std::vector<std::shared_ptr<InventoryItem>> result) {
          auto pred = [closure, arg](const std::shared_ptr<InventoryItem>& item) {
                return closure && (*closure)(item.get(), arg);
          };
          return getAllRecurse(pred, std::move(result));
    }

    // Gets up to 'count' items of the given category
    std::vector<std::shared_ptr<InventoryItem>> getSomeCategory(const std::string& category, int count) {
        return getSomeCategory(category, count, {});
    }

    // Gets up to 'count' items matching a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getSomeEval(LuaClosure* closure, int count) {
        return getSomeEval(closure, count, {});
    }

    // Gets up to 'count' items matching a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalArg(LuaClosure* closure, void* arg, int count) {
        return getSomeEvalArg(closure, arg, count, {});
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEval(const std::string& type, LuaClosure* closure, int count) {
        return getSomeTypeEval(type, closure, count, {});
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalArg(const std::string& type, LuaClosure* closure, void* arg, int count) {
        return getSomeTypeEvalArg(type, closure, arg, count, {});
    }

    // Gets up to 'count' items matching a Lua closure recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalRecurse(LuaClosure* closure, int count) {
        return getSomeEvalRecurse(closure, count, {});
    }

    // Gets up to 'count' items matching a Lua closure with argument recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeEvalArgRecurse(LuaClosure* closure, void* arg, int count) {
        return getSomeEvalArgRecurse(closure, arg, count, {});
    }

    // Gets up to 'count' items with the given tag
    std::vector<std::shared_ptr<InventoryItem>> getSomeTag(const std::string& tag, int count) {
        return getSomeTag(tag, count, {});
    }

    // Gets up to 'count' items with the given tag recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagRecurse(const std::string& tag, int count) {
        return getSomeTagRecurse(tag, count, {});
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure, recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEvalRecurse(const std::string& tag, LuaClosure* closure, int count) {
        return getSomeTagEvalRecurse(tag, closure, count, {});
    }

    // Gets up to 'count' items with the given tag, filtered by Lua closure with argument, recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTagEvalArgRecurse(const std::string& tag, LuaClosure* closure, void* arg, int count) {
        return getSomeTagEvalArgRecurse(tag, closure, arg, count, {});
    }

    // Gets up to 'count' items of the given type
    std::vector<std::shared_ptr<InventoryItem>> getSomeType(const std::string& type, int count) {
        return getSomeType(type, count, {});
    }

    // Gets up to 'count' items of the given type recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeRecurse(const std::string& type, int count) {
        return getSomeTypeRecurse(type, count, {});
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure, recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalRecurse(const std::string& type, LuaClosure* closure, int count) {
        return getSomeTypeEvalRecurse(type, closure, count, {});
    }

    // Gets up to 'count' items of the given type, filtered by Lua closure with argument, recursively
    std::vector<std::shared_ptr<InventoryItem>> getSomeTypeEvalArgRecurse(const std::string& type, LuaClosure* closure, void* arg, int count) {
        return getSomeTypeEvalArgRecurse(type, closure, arg, count, {});
    }

    // Gets all items matching the predicate
    std::vector<std::shared_ptr<InventoryItem>> getAll(const std::function<bool(const std::shared_ptr<InventoryItem>&)>& pred) {
        return getAll(pred, {});
    }

    // Gets all items of the given category
    std::vector<std::shared_ptr<InventoryItem>> getAllCategory(const std::string& category) {
        return getAllCategory(category, {});
    }

    // Gets all items matching a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getAllEval(LuaClosure* closure) {
        return getAllEval(closure, {});
    }

    // Gets all items matching a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalArg(LuaClosure* closure, void* arg) {
        return getAllEvalArg(closure, arg, {});
    }

    // Gets all items with the given tag, filtered by a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEval(const std::string& tag, LuaClosure* closure) {
        return getAllTagEval(tag, closure, {});
    }

    // Gets all items with the given tag, filtered by a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getAllTagEvalArg(const std::string& tag, LuaClosure* closure, void* arg) {
        return getAllTagEvalArg(tag, closure, arg, {});
    }

    // Gets all items of the given type, filtered by a Lua closure
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEval(const std::string& type, LuaClosure* closure) {
        return getAllTypeEval(type, closure, {});
    }

    // Gets all items of the given type, filtered by a Lua closure with argument
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalArg(const std::string& type, LuaClosure* closure, void* arg) {
        return getAllTypeEvalArg(type, closure, arg, {});
    }

    // Gets all items matching a Lua closure recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalRecurse(LuaClosure* closure) {
        return getAllEvalRecurse(closure, {});
    }

    // Gets all items matching a Lua closure with argument recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllEvalArgRecurse(LuaClosure* closure, void* arg) {
        return getAllEvalArgRecurse(closure, arg, {});
    }

    // Gets all items of the given type
    std::vector<std::shared_ptr<InventoryItem>> getAllType(const std::string& type) {
        return getAllType(type, {});
    }

    // Gets all items of the given type recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeRecurse(const std::string& type) {
        return getAllTypeRecurse(type, {});
    }

    // Gets all items of the given type that match the evaluation function recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalRecurse(const std::string& type, LuaClosure* closure) {
        return getAllTypeEvalRecurse(type, closure, {});
    }

    // Gets all items of the given type that match the evaluation function with argument recursively
    std::vector<std::shared_ptr<InventoryItem>> getAllTypeEvalArgRecurse(const std::string& type, LuaClosure* closure, void* arg) {
        return getAllTypeEvalArgRecurse(type, closure, arg, {});
    }

    InventoryItem FindAndReturnCategory(const std::string& var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.getCategory() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    // Finds and returns up to 'count' items of the given type
    std::vector<std::shared_ptr<InventoryItem>> FindAndReturn(const std::string& type, int count) {
        return getSomeType(type, count);
    }

    InventoryItem FindAndReturn(const std::string& var1, std::vector<InventoryItem> var2) {
      if (var1 == nullptr) {
    return nullptr;
      } else {
         for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
            if (var4.type != nullptr && compareType(var1, var4) && !var2.contains(var4)) {
    return var4;
            }
         }

    return nullptr;
      }
   }

    InventoryItem FindAndReturn(const std::string& var1) {
      return this.getFirstType(var1);
   }

    // Finds all items of the given type
    std::vector<std::shared_ptr<InventoryItem>> FindAll(const std::string& type) {
        return getAllType(type);
    }

    InventoryItem FindAndReturnStack(const std::string& var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (compareType(var1, var3)) {
    InventoryItem var4 = InventoryItemFactory.CreateItem(var3.module + "." + var1);
            if (var3.CanStack(var4)) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    InventoryItem FindAndReturnStack(InventoryItem var1) {
    std::string var2 = var1.type;

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if ((var4.type == nullptr ? var2 == nullptr : var4.type == var2)) && var4.CanStack(var1)) {
    return var4;
         }
      }

    return nullptr;
   }

    bool HasType(ItemType var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.cat == var1) {
    return true;
         }
      }

    return false;
   }

    void Remove(InventoryItem var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3 == var1) {
            if (var1.uses > 1) {
               var1.uses--;
            } else {
               this.Items.remove(var1);
            }

            var1.container = nullptr;
            this.drawDirty = true;
            this.dirty = true;
            if (this.parent != nullptr) {
               this.dirty = true;
            }

            if (this.dynamic_cast<IsoDeadBody*>(parent) != nullptr) {
               ((IsoDeadBody)this.parent).checkClothing(var1);
            }

            if (this.dynamic_cast<IsoMannequin*>(parent) != nullptr) {
               ((IsoMannequin)this.parent).checkClothing(var1);
            }

            return;
         }
      }
   }

    void DoRemoveItem(InventoryItem var1) {
      this.drawDirty = true;
      if (this.parent != nullptr) {
         this.dirty = true;
      }

      this.Items.remove(var1);
      var1.container = nullptr;
      if (this.dynamic_cast<IsoDeadBody*>(parent) != nullptr) {
         ((IsoDeadBody)this.parent).checkClothing(var1);
      }

      if (this.dynamic_cast<IsoMannequin*>(parent) != nullptr) {
         ((IsoMannequin)this.parent).checkClothing(var1);
      }
   }

    void Remove(const std::string& var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.type == var1)) {
            if (var3.uses > 1) {
               var3.uses--;
            } else {
               this.Items.remove(var3);
            }

            var3.container = nullptr;
            this.drawDirty = true;
            this.dirty = true;
            if (this.parent != nullptr) {
               this.dirty = true;
            }

            return;
         }
      }
   }

    InventoryItem Remove(ItemType var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.cat == var1) {
            this.Items.remove(var3);
            var3.container = nullptr;
            this.drawDirty = true;
            this.dirty = true;
            if (this.parent != nullptr) {
               this.dirty = true;
            }

    return var3;
         }
      }

    return nullptr;
   }

    InventoryItem Find(ItemType var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.cat == var1) {
    return var3;
         }
      }

    return nullptr;
   }

    void RemoveAll(const std::string& var1) {
      this.drawDirty = true;
      if (this.parent != nullptr) {
         this.dirty = true;
      }

    std::vector var2 = new std::vector();

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (var4.type == var1)) {
            var4.container = nullptr;
            var2.push_back(var4);
            this.dirty = true;
         }
      }

    for (auto& var6 : var2)         this.Items.remove(var6);
      }
   }

    bool RemoveOneOf(const std::string& var1, bool var2) {
      this.drawDirty = true;
      if (this.parent != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr)) {
         this.dirty = true;
      }

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (var4.getFullType() == var1) || var4.type == var1)) {
            if (var4.uses > 1) {
               var4.uses--;
            } else {
               var4.container = nullptr;
               this.Items.remove(var4);
            }

            this.dirty = true;
    return true;
         }
      }

      if (var2) {
         for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
            if (dynamic_cast<InventoryContainer*>(var6) != nullptr
               && ((InventoryContainer)var6).getItemContainer() != nullptr
               && ((InventoryContainer)var6).getItemContainer().RemoveOneOf(var1, var2)) {
    return true;
            }
         }
      }

    return false;
   }

    void RemoveOneOf(const std::string& var1) {
      this.RemoveOneOf(var1, true);
   }

   /** @deprecated */
    int getWeight() {
      if (this.dynamic_cast<IsoPlayer*>(parent) != nullptr && ((IsoPlayer)this.parent).isGhostMode()) {
    return 0;
      } else {
    float var1 = 0.0F;

         for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
            var1 += var3.ActualWeight * var3.uses;
         }

         return (int)(var1 * (this.weightReduction / 0.01F));
      }
   }

    float getContentsWeight() {
    float var1 = 0.0F;

      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         var1 += var3.getUnequippedWeight();
      }

    return var1;
   }

    float getMaxWeight() {
      return this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr ? ((IsoGameCharacter)this.parent).getMaxWeight() : this.Capacity;
   }

    float getCapacityWeight() {
      if (this.dynamic_cast<IsoPlayer*>(parent) != nullptr) {
         if (Core.bDebug && ((IsoPlayer)this.parent).isGhostMode()
            || !((IsoPlayer)this.parent).isAccessLevel("None") && ((IsoPlayer)this.parent).isUnlimitedCarry()) {
            return 0.0F;
         }

         if (((IsoPlayer)this.parent).isUnlimitedCarry()) {
            return 0.0F;
         }
      }

      return this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr ? ((IsoGameCharacter)this.parent).getInventoryWeight() : this.getContentsWeight();
   }

    bool isEmpty() {
      return this.Items == nullptr || this.Items.empty();
   }

    bool isMicrowave() {
      return "microwave" == this.getType());
   }

    bool isSquareInRoom(IsoGridSquare var1) {
    return var1 = = nullptr ? false : var1.getRoom() != nullptr;
   }

    bool isSquarePowered(IsoGridSquare var1) {
      if (var1 == nullptr) {
    return false;
      } else {
    bool var2 = IsoWorld.instance.isHydroPowerOn();
         if (var2 && var1.getRoom() != nullptr) {
    return true;
         } else if (var1.haveElectricity()) {
    return true;
         } else {
            if (var2 && var1.getRoom() == nullptr) {
    IsoGridSquare var3 = var1.nav[IsoDirections.N.index()];
    IsoGridSquare var4 = var1.nav[IsoDirections.S.index()];
    IsoGridSquare var5 = var1.nav[IsoDirections.W.index()];
    IsoGridSquare var6 = var1.nav[IsoDirections.E.index()];
               if (this.isSquareInRoom(var3) || this.isSquareInRoom(var4) || this.isSquareInRoom(var5) || this.isSquareInRoom(var6)) {
    return true;
               }
            }

    return false;
         }
      }
   }

    bool isPowered() {
      if (this.parent != nullptr && this.parent.getObjectIndex() != -1) {
    IsoGridSquare var1 = this.parent.getSquare();
         if (this.isSquarePowered(var1)) {
    return true;
         } else {
            this.parent.getSpriteGridObjects(s_tempObjects);

            for (int var2 = 0; var2 < s_tempObjects.size(); var2++) {
    IsoObject var3 = s_tempObjects.get(var2);
               if (var3 != this.parent) {
    IsoGridSquare var4 = var3.getSquare();
                  if (this.isSquarePowered(var4)) {
    return true;
                  }
               }
            }

    return false;
         }
      } else {
    return false;
      }
   }

    float getTemprature() {
      if (this.customTemperature != 0.0F) {
         return this.customTemperature;
      } else {
    bool var1 = false;
         if (this.getParent() != nullptr && this.getParent().getSprite() != nullptr) {
            var1 = this.getParent().getSprite().getProperties().Is("IsFridge");
         }

         if (this.isPowered()) {
            if (this.type == "fridge") || this.type == "freezer") || var1) {
               return 0.2F;
            }

            if (("stove" == this.type) || "microwave" == this.type)) && this.dynamic_cast<IsoStove*>(parent) != nullptr) {
               return ((IsoStove)this.parent).getCurrentTemperature() / 100.0F;
            }
         }

         if ("barbecue" == this.type) && this.dynamic_cast<IsoBarbecue*>(parent) != nullptr) {
            return ((IsoBarbecue)this.parent).getTemperature();
         } else if ("fireplace" == this.type) && this.dynamic_cast<IsoFireplace*>(parent) != nullptr) {
            return ((IsoFireplace)this.parent).getTemperature();
         } else if ("woodstove" == this.type) && this.dynamic_cast<IsoFireplace*>(parent) != nullptr) {
            return ((IsoFireplace)this.parent).getTemperature();
         } else if ((this.type == "fridge") || this.type == "freezer") || var1)
            && GameTime.instance.NightsSurvived == SandboxOptions.instance.getElecShutModifier()
            && GameTime.instance.getTimeOfDay() < 13.0F) {
    float var2 = (GameTime.instance.getTimeOfDay() - 7.0F) / 6.0F;
            return GameTime.instance.Lerp(0.2F, 1.0F, var2);
         } else {
            return 1.0F;
         }
      }
   }

    bool isTemperatureChanging() {
      return this.dynamic_cast<IsoStove*>(parent) != nullptr ? ((IsoStove)this.parent).isTemperatureChanging() : false;
   }

    // Saves the container to a byte buffer
    std::vector<std::shared_ptr<InventoryItem>> save(ByteBuffer* buffer, IsoGameCharacter* character) {
        GameWindow.WriteString(buffer, this->type);
        buffer->put((byte)(this->bExplored ? 1 : 0));
        std::vector<std::shared_ptr<InventoryItem>> var3 = CompressIdenticalItems.save(buffer, this->Items, nullptr);
        buffer->put((byte)(this->isHasBeenLooted() ? 1 : 0));
        buffer->putInt(this->Capacity);
        return var3;
    }

    // Saves the container to a byte buffer
    std::vector<std::shared_ptr<InventoryItem>> save(ByteBuffer* buffer) {
        return this->save(buffer, nullptr);
    }

    // Loads the container from a byte buffer
    std::vector<std::shared_ptr<InventoryItem>> load(ByteBuffer* buffer, int version) {
        this->type = GameWindow.ReadString(buffer);
        this->bExplored = buffer->get() == 1;
        std::vector<std::shared_ptr<InventoryItem>> var3 = CompressIdenticalItems.load(buffer, version, this->Items, this->IncludingObsoleteItems);

        for (size_t var4 = 0; var4 < this->Items.size(); var4++) {
            std::shared_ptr<InventoryItem> var5 = this->Items[var4];
            var5->container = this;
        }

        this->setHasBeenLooted(buffer->get() == 1);
        this->Capacity = buffer->getInt();
        this->dirty = false;
        return var3;
    }

    bool isDrawDirty() {
      return this.drawDirty;
   }

    void setDrawDirty(bool var1) {
      this.drawDirty = var1;
   }

    InventoryItem getBestWeapon(SurvivorDesc var1) {
    InventoryItem var2 = nullptr;
    float var3 = -1.0E7F;

      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         if (dynamic_cast<HandWeapon*>(var5) != nullptr) {
    float var6 = var5.getScore(var1);
            if (var6 >= var3) {
               var3 = var6;
               var2 = var5;
            }
         }
      }

    return var2;
   }

    InventoryItem getBestWeapon() {
    InventoryItem var1 = nullptr;
    float var2 = 0.0F;

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (dynamic_cast<HandWeapon*>(var4) != nullptr) {
    float var5 = var4.getScore(nullptr);
            if (var5 >= var2) {
               var2 = var5;
               var1 = var4;
            }
         }
      }

    return var1;
   }

    float getTotalFoodScore(SurvivorDesc var1) {
    float var2 = 0.0F;

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (dynamic_cast<Food*>(var4) != nullptr) {
            var2 += var4.getScore(var1);
         }
      }

    return var2;
   }

    float getTotalWeaponScore(SurvivorDesc var1) {
    float var2 = 0.0F;

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (dynamic_cast<HandWeapon*>(var4) != nullptr) {
            var2 += var4.getScore(var1);
         }
      }

    return var2;
   }

    InventoryItem getBestFood(SurvivorDesc var1) {
    InventoryItem var2 = nullptr;
    float var3 = 0.0F;

      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         if (dynamic_cast<Food*>(var5) != nullptr) {
    float var6 = var5.getScore(var1);
            if (((Food)var5).isbDangerousUncooked() && !var5.isCooked()) {
               var6 *= 0.2F;
            }

            if (((Food)var5).Age > var5.OffAge) {
               var6 *= 0.2F;
            }

            if (var6 >= var3) {
               var3 = var6;
               var2 = var5;
            }
         }
      }

    return var2;
   }

    InventoryItem getBestBandage(SurvivorDesc var1) {
    InventoryItem var2 = nullptr;

      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (var4.isCanBandage()) {
            var2 = var4;
            break;
         }
      }

    return var2;
   }

    int getNumItems(const std::string& var1) {
    int var2 = 0;
      if (var1.contains("Type:")) {
         for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
            if (dynamic_cast<Food*>(var4) != nullptr && var1.contains("Food")) {
               var2 += var4.uses;
            }

            if (dynamic_cast<HandWeapon*>(var4) != nullptr && var1.contains("Weapon")) {
               var2 += var4.uses;
            }
         }
      } else {
         for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
            if (var6.type == var1)) {
               var2 += var6.uses;
            }
         }
      }

    return var2;
   }

    bool isActive() {
      return this.active;
   }

    void setActive(bool var1) {
      this.active = var1;
   }

    bool isDirty() {
      return this.dirty;
   }

    void setDirty(bool var1) {
      this.dirty = var1;
   }

    bool isIsDevice() {
      return this.IsDevice;
   }

    void setIsDevice(bool var1) {
      this.IsDevice = var1;
   }

    float getAgeFactor() {
      return this.ageFactor;
   }

    void setAgeFactor(float var1) {
      this.ageFactor = var1;
   }

    float getCookingFactor() {
      return this.CookingFactor;
   }

    void setCookingFactor(float var1) {
      this.CookingFactor = var1;
   }

    // Gets all items in the container
    std::vector<std::shared_ptr<InventoryItem>> getItems() {
        return this->Items;
    }

    void setItems(std::vector<InventoryItem> var1) {
      this.Items = var1;
   }

    IsoObject getParent() {
      return this.parent;
   }

    void setParent(IsoObject var1) {
      this.parent = var1;
   }

    IsoGridSquare getSourceGrid() {
      return this.SourceGrid;
   }

    void setSourceGrid(IsoGridSquare var1) {
      this.SourceGrid = var1;
   }

    std::string getType() {
      return this.type;
   }

    void setType(const std::string& var1) {
      this.type = var1;
   }

    void clear() {
      this.Items.clear();
      this.dirty = true;
      this.drawDirty = true;
   }

    int getWaterContainerCount() {
    int var1 = 0;

      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.CanStoreWater) {
            var1++;
         }
      }

    return var1;
   }

    InventoryItem FindWaterSource() {
      for (int var1 = 0; var1 < this.Items.size(); var1++) {
    InventoryItem var2 = this.Items.get(var1);
         if (var2.isWaterSource()) {
            if (!(dynamic_cast<Drainable*>(var2) != nullptr)) {
    return var2;
            }

            if (((Drainable)var2).getUsedDelta() > 0.0F) {
    return var2;
            }
         }
      }

    return nullptr;
   }

    // Gets all items that can store water
    std::vector<std::shared_ptr<InventoryItem>> getAllWaterFillables() {
        tempList.clear();

        for (size_t var1 = 0; var1 < this->Items.size(); var1++) {
            std::shared_ptr<InventoryItem> var2 = this->Items[var1];
            if (var2->CanStoreWater) {
                tempList.push_back(var2);
            }
        }

        return tempList;
    }

    int getItemCount(const std::string& var1) {
      return this.getCountType(var1);
   }

    int getItemCountRecurse(const std::string& var1) {
      return this.getCountTypeRecurse(var1);
   }

    int getItemCount(const std::string& var1, bool var2) {
      return var2 ? this.getCountTypeRecurse(var1) : this.getCountType(var1);
   }

    static int getUses(InventoryItemList var0) {
    int var1 = 0;

      for (int var2 = 0; var2 < var0.size(); var2++) {
    DrainableComboItem var3 = (DrainableComboItem)Type.tryCastTo((InventoryItem)var0.get(var2), DrainableComboItem.class);
         if (var3 != nullptr) {
            var1 += var3.getDrainableUsesInt();
         } else {
            var1++;
         }
      }

    return var1;
   }

    int getUsesRecurse(Predicate<InventoryItem> var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAllRecurse(var1, var2);
    int var3 = getUses(var2);
      TL_itemListPool.get().release(var2);
    return var3;
   }

    int getUsesType(const std::string& var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAllType(var1, var2);
    int var3 = getUses(var2);
      TL_itemListPool.get().release(var2);
    return var3;
   }

    int getUsesTypeRecurse(const std::string& var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAllTypeRecurse(var1, var2);
    int var3 = getUses(var2);
      TL_itemListPool.get().release(var2);
    return var3;
   }

    int getWeightReduction() {
      return this.weightReduction;
   }

    void setWeightReduction(int var1) {
      var1 = Math.min(var1, 100);
      var1 = Math.max(var1, 0);
      this.weightReduction = var1;
   }

    void removeAllItems() {
      this.drawDirty = true;
      if (this.parent != nullptr) {
         this.dirty = true;
      }

      for (int var1 = 0; var1 < this.Items.size(); var1++) {
    InventoryItem var2 = this.Items.get(var1);
         var2.container = nullptr;
      }

      this.Items.clear();
      if (this.dynamic_cast<IsoDeadBody*>(parent) != nullptr) {
         ((IsoDeadBody)this.parent).checkClothing(nullptr);
      }

      if (this.dynamic_cast<IsoMannequin*>(parent) != nullptr) {
         ((IsoMannequin)this.parent).checkClothing(nullptr);
      }
   }

    bool containsRecursive(InventoryItem var1) {
      for (int var2 = 0; var2 < this.getItems().size(); var2++) {
    InventoryItem var3 = this.getItems().get(var2);
         if (var3 == var1) {
    return true;
         }

         if (dynamic_cast<InventoryContainer*>(var3) != nullptr && ((InventoryContainer)var3).getInventory().containsRecursive(var1)) {
    return true;
         }
      }

    return false;
   }

    int getItemCountFromTypeRecurse(const std::string& var1) {
    int var2 = 0;

      for (int var3 = 0; var3 < this.getItems().size(); var3++) {
    InventoryItem var4 = this.getItems().get(var3);
         if (var4.getFullType() == var1)) {
            var2++;
         }

         if (dynamic_cast<InventoryContainer*>(var4) != nullptr) {
    int var5 = ((InventoryContainer)var4).getInventory().getItemCountFromTypeRecurse(var1);
            var2 += var5;
         }
      }

    return var2;
   }

    float getCustomTemperature() {
      return this.customTemperature;
   }

    void setCustomTemperature(float var1) {
      this.customTemperature = var1;
   }

    InventoryItem getItemFromType(const std::string& var1, IsoGameCharacter var2, bool var3, bool var4, bool var5) {
    InventoryItemList var6 = (InventoryItemList)TL_itemListPool.get().alloc();
      if (var1.contains(".")) {
         var1 = var1.split("\\.")[1];
      }

      for (int var7 = 0; var7 < this.getItems().size(); var7++) {
    InventoryItem var8 = this.getItems().get(var7);
         if (!var8.getFullType() == var1) && !var8.getType() == var1)) {
            if (var5 && dynamic_cast<InventoryContainer*>(var8) != nullptr && ((InventoryContainer)var8).getInventory() != nullptr && !var6.contains(var8)) {
               var6.push_back(var8);
            }
         } else if ((!var3 || var2 == nullptr || !var2.isEquippedClothing(var8)) && this.testBroken(var4, var8)) {
            TL_itemListPool.get().release(var6);
    return var8;
         }
      }

      for (int var10 = 0; var10 < var6.size(); var10++) {
    ItemContainer var11 = ((InventoryContainer)var6.get(var10)).getInventory();
    InventoryItem var9 = var11.getItemFromType(var1, var2, var3, var4, var5);
         if (var9 != nullptr) {
            TL_itemListPool.get().release(var6);
    return var9;
         }
      }

      TL_itemListPool.get().release(var6);
    return nullptr;
   }

    InventoryItem getItemFromType(const std::string& var1, bool var2, bool var3) {
      return this.getItemFromType(var1, nullptr, false, var2, var3);
   }

    InventoryItem getItemFromType(const std::string& var1) {
      return this.getFirstType(var1);
   }

    // Gets all items of the given type
    std::vector<std::shared_ptr<InventoryItem>> getItemsFromType(const std::string& type) {
        return getAllType(type);
    }

    // Gets all items of the given full type
    std::vector<std::shared_ptr<InventoryItem>> getItemsFromFullType(const std::string& type) {
        return !type.empty() && type.find('.') != std::string::npos ? getAllType(type) : std::vector<std::shared_ptr<InventoryItem>>{};
    }

    // Gets all items of the given full type, optionally recursively
    std::vector<std::shared_ptr<InventoryItem>> getItemsFromFullType(const std::string& type, bool recurse) {
        if (!type.empty() && type.find('.') != std::string::npos) {
            return recurse ? getAllTypeRecurse(type) : getAllType(type);
        } else {
            return {};
        }
    }

    // Gets all items of the given type, optionally recursively
    std::vector<std::shared_ptr<InventoryItem>> getItemsFromType(const std::string& type, bool recurse) {
        return recurse ? getAllTypeRecurse(type) : getAllType(type);
    }

    // Gets all items of the given category
    std::vector<std::shared_ptr<InventoryItem>> getItemsFromCategory(const std::string& category) {
        return getAllCategory(category);
    }

    void sendContentsToRemoteContainer() {
      if (GameClient.bClient) {
         this.sendContentsToRemoteContainer(GameClient.connection);
      }
   }

    void requestSync() {
      if (GameClient.bClient) {
         if (this.parent == nullptr || this.parent.square == nullptr || this.parent.square.chunk == nullptr) {
            return;
         }

         GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(this.parent.square.chunk);
      }
   }

    void requestServerItemsForContainer() {
      if (this.parent != nullptr && this.parent.square != nullptr) {
    UdpConnection var1 = GameClient.connection;
    ByteBufferWriter var2 = var1.startPacket();
         PacketType.RequestItemsForContainer.doPacket(var2);
         var2.putShort(IsoPlayer.getInstance().OnlineID);
         var2.putUTF(this.type);
         if (this.parent.square.getRoom() != nullptr) {
            var2.putUTF(this.parent.square.getRoom().getName());
         } else {
            var2.putUTF("all");
         }

         var2.putInt(this.parent.square.getX());
         var2.putInt(this.parent.square.getY());
         var2.putInt(this.parent.square.getZ());
    int var3 = this.parent.square.getObjects().indexOf(this.parent);
         if (var3 == -1 && this.parent.square.getStaticMovingObjects().indexOf(this.parent) != -1) {
            var2.putShort((short)0);
            var3 = this.parent.square.getStaticMovingObjects().indexOf(this.parent);
            var2.putByte((byte)var3);
         } else if (this.dynamic_cast<IsoWorldInventoryObject*>(parent) != nullptr) {
            var2.putShort((short)1);
            var2.putInt(((IsoWorldInventoryObject)this.parent).getItem().id);
         } else if (this.dynamic_cast<BaseVehicle*>(parent) != nullptr) {
            var2.putShort((short)3);
            var2.putShort(((BaseVehicle)this.parent).VehicleID);
            var2.putByte((byte)this.vehiclePart.getIndex());
         } else {
            var2.putShort((short)2);
            var2.putByte((byte)var3);
            var2.putByte((byte)this.parent.getContainerIndex(this));
         }

         PacketType.RequestItemsForContainer.send(var1);
      }
   }

    void sendContentsToRemoteContainer(UdpConnection var1) {
    ByteBufferWriter var2 = var1.startPacket();
      PacketType.AddInventoryItemToContainer.doPacket(var2);
      var2.putInt(0);
    bool var3 = false;
      var2.putInt(this.parent.square.getX());
      var2.putInt(this.parent.square.getY());
      var2.putInt(this.parent.square.getZ());
      var2.putByte((byte)this.parent.square.getObjects().indexOf(this.parent));

      try {
         CompressIdenticalItems.save(var2.bb, this.Items, nullptr);
      } catch (Exception var5) {
         var5.printStackTrace();
      }

      PacketType.AddInventoryItemToContainer.send(var1);
   }

    InventoryItem getItemWithIDRecursiv(int var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.id == var1) {
    return var3;
         }

         if (dynamic_cast<InventoryContainer*>(var3) != nullptr
            && ((InventoryContainer)var3).getItemContainer() != nullptr
            && !((InventoryContainer)var3).getItemContainer().getItems().empty()) {
            var3 = ((InventoryContainer)var3).getItemContainer().getItemWithIDRecursiv(var1);
            if (var3 != nullptr) {
    return var3;
            }
         }
      }

    return nullptr;
   }

    InventoryItem getItemWithID(int var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.id == var1) {
    return var3;
         }
      }

    return nullptr;
   }

    bool removeItemWithID(int var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.id == var1) {
            this.Remove(var3);
    return true;
         }
      }

    return false;
   }

    bool containsID(int var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.id == var1) {
    return true;
         }
      }

    return false;
   }

    bool removeItemWithIDRecurse(int var1) {
      for (int var2 = 0; var2 < this.Items.size(); var2++) {
    InventoryItem var3 = this.Items.get(var2);
         if (var3.id == var1) {
            this.Remove(var3);
    return true;
         }

         if (dynamic_cast<InventoryContainer*>(var3) != nullptr && ((InventoryContainer)var3).getInventory().removeItemWithIDRecurse(var1)) {
    return true;
         }
      }

    return false;
   }

    bool isHasBeenLooted() {
      return this.hasBeenLooted;
   }

    void setHasBeenLooted(bool var1) {
      this.hasBeenLooted = var1;
   }

    std::string getOpenSound() {
      return this.openSound;
   }

    void setOpenSound(const std::string& var1) {
      this.openSound = var1;
   }

    std::string getCloseSound() {
      return this.closeSound;
   }

    void setCloseSound(const std::string& var1) {
      this.closeSound = var1;
   }

    std::string getPutSound() {
      return this.putSound;
   }

    void setPutSound(const std::string& var1) {
      this.putSound = var1;
   }

    InventoryItem haveThisKeyId(int var1) {
      for (int var2 = 0; var2 < this.getItems().size(); var2++) {
    InventoryItem var3 = this.getItems().get(var2);
         if (dynamic_cast<Key*>(var3) != nullptr var4) {
            if (var4.getKeyId() == var1) {
    return var4;
            }
         } else if (var3.getType() == "KeyRing") && ((InventoryContainer)var3).getInventory().haveThisKeyId(var1) != nullptr) {
            return ((InventoryContainer)var3).getInventory().haveThisKeyId(var1);
         }
      }

    return nullptr;
   }

    std::string getOnlyAcceptCategory() {
      return this.OnlyAcceptCategory;
   }

    void setOnlyAcceptCategory(const std::string& var1) {
      this.OnlyAcceptCategory = StringUtils.discardNullOrWhitespace(var1);
   }

    std::string getAcceptItemFunction() {
      return this.AcceptItemFunction;
   }

    void setAcceptItemFunction(const std::string& var1) {
      this.AcceptItemFunction = StringUtils.discardNullOrWhitespace(var1);
   }

    IsoGameCharacter getCharacter() {
      if (this.getParent() instanceof IsoGameCharacter) {
         return (IsoGameCharacter)this.getParent();
      } else {
         return this.containingItem != nullptr && this.containingItem.getContainer() != nullptr ? this.containingItem.getContainer().getCharacter() : nullptr;
      }
   }

    void emptyIt() {
      this.Items = std::make_unique<std::vector<>>();
   }

    // Gets items for admin purposes
    std::unordered_map<std::string, std::shared_ptr<InventoryItem>> getItems4Admin() {
        std::unordered_map<std::string, std::shared_ptr<InventoryItem>> var1;

        for (size_t var2 = 0; var2 < this->getItems().size(); var2++) {
            std::shared_ptr<InventoryItem> var3 = this->getItems()[var2];
            var3->setCount(1);
            if (var3->getCat() != ItemType.Drainable
                && var3->getCat() != ItemType.Weapon
                && var1.find(var3->getFullType()) != var1.end()
                && !(std::dynamic_pointer_cast<InventoryContainer>(var3) != nullptr)) {
                var1[var3->getFullType()]->setCount(var1[var3->getFullType()]->getCount() + 1);
            } else if (var1.find(var3->getFullType()) != var1.end()) {
                var1[var3->getFullType() + std::to_string(Rand.Next(100000))] = var3;
            } else {
                var1[var3->getFullType()] = var3;
            }
        }

        return var1;
    }

    // Gets all items, optionally setting worker and recursing into containers
    std::unordered_map<std::string, std::shared_ptr<InventoryItem>>& getAllItems(std::unordered_map<std::string, std::shared_ptr<InventoryItem>>& items, bool setWorker) {
        for (size_t var3 = 0; var3 < this->getItems().size(); var3++) {
            std::shared_ptr<InventoryItem> var4 = this->getItems()[var3];
            if (setWorker) {
                var4->setWorker("inInv");
            }

            var4->setCount(1);
            if (var4->getCat() != ItemType.Drainable && var4->getCat() != ItemType.Weapon && items.find(var4->getFullType()) != items.end()) {
                items[var4->getFullType()]->setCount(items[var4->getFullType()]->getCount() + 1);
            } else if (items.find(var4->getFullType()) != items.end()) {
                items[var4->getFullType() + std::to_string(Rand.Next(100000))] = var4;
            } else {
                items[var4->getFullType()] = var4;
            }

            if (std::shared_ptr<InventoryContainer> container = std::dynamic_pointer_cast<InventoryContainer>(var4);
                container != nullptr && container->getItemContainer() != nullptr && !container->getItemContainer()->getItems().empty()) {
                items = container->getItemContainer()->getAllItems(items, true);
            }
        }

        return items;
    }

    InventoryItem getItemById(long var1) {
      for (int var3 = 0; var3 < this.getItems().size(); var3++) {
    InventoryItem var4 = this.getItems().get(var3);
         if (var4.getID() == var1) {
    return var4;
         }

         if (dynamic_cast<InventoryContainer*>(var4) != nullptr
            && ((InventoryContainer)var4).getItemContainer() != nullptr
            && !((InventoryContainer)var4).getItemContainer().getItems().empty()) {
            var4 = ((InventoryContainer)var4).getItemContainer().getItemById(var1);
            if (var4 != nullptr) {
    return var4;
            }
         }
      }

    return nullptr;
   }

    void addItemsToProcessItems() {
      IsoWorld.instance.CurrentCell.addToProcessItems(this.Items);
   }

    void removeItemsFromProcessItems() {
      IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this.Items);
      if (!"floor" == this.type)) {
         ItemSoundManager.removeItems(this.Items);
      }
   }

    bool isExistYet() {
      if (!SystemDisabler.doWorldSyncEnable) {
    return true;
      } else if (this.getCharacter() != nullptr) {
    return true;
      } else if (this.getParent() instanceof BaseVehicle) {
    return true;
      } else if (this.dynamic_cast<IsoDeadBody*>(parent) != nullptr) {
         return this.parent.getStaticMovingObjectIndex() != -1;
      } else if (this.dynamic_cast<IsoCompost*>(parent) != nullptr) {
         return this.parent.getObjectIndex() != -1;
      } else if (this.containingItem != nullptr && this.containingItem.worldItem != nullptr) {
         return this.containingItem.worldItem.getWorldObjectIndex() != -1;
      } else if (this.getType() == "floor")) {
    return true;
      } else if (this.SourceGrid == nullptr) {
    return false;
      } else {
    IsoGridSquare var1 = this.SourceGrid;
         return !var1.getObjects().contains(this.parent) ? false : this.parent.getContainerIndex(this) != -1;
      }
   }

    std::string getContainerPosition() {
      return this.containerPosition;
   }

    void setContainerPosition(const std::string& var1) {
      this.containerPosition = var1;
   }

    std::string getFreezerPosition() {
      return this.freezerPosition;
   }

    void setFreezerPosition(const std::string& var1) {
      this.freezerPosition = var1;
   }

    VehiclePart getVehiclePart() {
      return this.vehiclePart;
   }
}
} // namespace inventory
} // namespace zombie
