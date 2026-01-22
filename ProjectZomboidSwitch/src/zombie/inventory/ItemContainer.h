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
   private static const std::vector<InventoryItem> tempList = std::make_unique<std::vector<>>();
   private static const std::vector<IsoObject> s_tempObjects = std::make_unique<std::vector<>>();
    bool active = false;
    bool dirty = true;
    bool IsDevice = false;
    float ageFactor = 1.0F;
    float CookingFactor = 1.0F;
    int Capacity = 50;
    InventoryItem containingItem = nullptr;
   public std::vector<InventoryItem> Items = std::make_unique<std::vector<>>();
   public std::vector<InventoryItem> IncludingObsoleteItems = std::make_unique<std::vector<>>();
    IsoObject parent = nullptr;
    IsoGridSquare SourceGrid = nullptr;
    VehiclePart vehiclePart = nullptr;
    InventoryContainer inventoryContainer = nullptr;
    bool bExplored = false;
    std::string type = "none";
    int ID = 0;
    bool drawDirty = true;
    float customTemperature = 0.0F;
    bool hasBeenLooted = false;
    std::string openSound = nullptr;
    std::string closeSound = nullptr;
    std::string putSound = nullptr;
    std::string OnlyAcceptCategory = nullptr;
    std::string AcceptItemFunction = nullptr;
    int weightReduction = 0;
    std::string containerPosition = nullptr;
    std::string freezerPosition = nullptr;
   private static const ThreadLocal<Comparators> TL_comparators = ThreadLocal.withInitial(Comparators::new);
   private static const ThreadLocal<InventoryItemListPool> TL_itemListPool = ThreadLocal.withInitial(InventoryItemListPool::new);
   private static const ThreadLocal<Predicates> TL_predicates = ThreadLocal.withInitial(Predicates::new);

    public ItemContainer(int var1, const std::string& var2, IsoGridSquare var3, IsoObject var4) {
      this.ID = var1;
      this.parent = var4;
      this.type = var2;
      this.SourceGrid = var3;
      if (var2 == "fridge")) {
         this.ageFactor = 0.02F;
         this.CookingFactor = 0.0F;
      }
   }

    public ItemContainer(const std::string& var1, IsoGridSquare var2, IsoObject var3) {
      this.ID = -1;
      this.parent = var3;
      this.type = var1;
      this.SourceGrid = var2;
      if (var1 == "fridge")) {
         this.ageFactor = 0.02F;
         this.CookingFactor = 0.0F;
      }
   }

    public ItemContainer(int var1) {
      this.ID = var1;
   }

    public ItemContainer() {
      this.ID = -1;
   }

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

   public std::vector<InventoryItem> AddItems(std::string var1, int var2) {
    std::vector var3 = new std::vector();

      for (int var4 = 0; var4 < var2; var4++) {
    InventoryItem var5 = this.AddItem(var1);
         if (var5 != nullptr) {
            var3.push_back(var5);
         }
      }

    return var3;
   }

    void AddItems(InventoryItem var1, int var2) {
      for (int var3 = 0; var3 < var2; var3++) {
         this.AddItem(var1.getFullType());
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

    InventoryItem addItem(InventoryItem var1) {
      return this.AddItem(var1);
   }

    InventoryItem AddItem(InventoryItem var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else if (this.containsID(var1.id)) {
         System.out.println("Error, container already has id");
         return this.getItemWithID(var1.id);
      } else {
         this.drawDirty = true;
         if (this.parent != nullptr) {
            this.dirty = true;
         }

         if (this.parent != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr)) {
            this.parent.DirtySlice();
         }

         if (var1.container != nullptr) {
            var1.container.Remove(var1);
         }

         var1.container = this;
         this.Items.push_back(var1);
         if (IsoWorld.instance.CurrentCell != nullptr) {
            IsoWorld.instance.CurrentCell.addToProcessItems(var1);
         }

    return var1;
      }
   }

    InventoryItem AddItemBlind(InventoryItem var1) {
      if (var1 == nullptr) {
    return nullptr;
      } else if (var1.getWeight() + this.getCapacityWeight() > this.getCapacity()) {
    return nullptr;
      } else {
         if (this.parent != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr)) {
            this.parent.DirtySlice();
         }

         this.Items.push_back(var1);
    return var1;
      }
   }

    InventoryItem AddItem(const std::string& var1) {
      this.drawDirty = true;
      if (this.parent != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr)) {
         this.dirty = true;
      }

    Item var2 = ScriptManager.instance.FindItem(var1);
      if (var2 == nullptr) {
         DebugLog.log("ERROR: ItemContainer.AddItem: can't find " + var1);
    return nullptr;
      } else if (var2.OBSOLETE) {
    return nullptr;
      } else {
    InventoryItem var3 = nullptr;
    int var4 = var2.getCount();

         for (int var5 = 0; var5 < var4; var5++) {
            var3 = InventoryItemFactory.CreateItem(var1);
            if (var3 == nullptr) {
    return nullptr;
            }

            var3.container = this;
            this.Items.push_back(var3);
            if (dynamic_cast<Food*>(var3) != nullptr) {
               ((Food)var3).setHeat(this.getTemprature());
            }

            if (IsoWorld.instance.CurrentCell != nullptr) {
               IsoWorld.instance.CurrentCell.addToProcessItems(var3);
            }
         }

    return var3;
      }
   }

    bool AddItem(const std::string& var1, float var2) {
      this.drawDirty = true;
      if (this.parent != nullptr && !(this.dynamic_cast<IsoGameCharacter*>(parent) != nullptr)) {
         this.dirty = true;
      }

    InventoryItem var3 = InventoryItemFactory.CreateItem(var1);
      if (var3 == nullptr) {
    return false;
      } else {
         if (dynamic_cast<Drainable*>(var3) != nullptr) {
            ((Drainable)var3).setUsedDelta(var2);
         }

         var3.container = this;
         this.Items.push_back(var3);
    return true;
      }
   }

    bool contains(InventoryItem var1) {
      return this.Items.contains(var1);
   }

    bool containsWithModule(const std::string& var1) {
      return this.containsWithModule(var1, false);
   }

    bool containsWithModule(const std::string& var1, bool var2) {
    std::string var3 = var1;
    std::string var4 = "Base";
      if (var1.contains(".")) {
         var4 = var1.split("\\.")[0];
         var3 = var1.split("\\.")[1];
      }

      for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
         if (var6 == nullptr) {
            this.Items.remove(var5);
            var5--;
         } else if (var6.type == var3.trim())
            && var4 == var6.getModule())
            && (!var2 || !(dynamic_cast<DrainableComboItem*>(var6) != nullptr) || !(((DrainableComboItem)var6).getUsedDelta() <= 0.0F))) {
    return true;
         }
      }

    return false;
   }

    void removeItemOnServer(InventoryItem var1) {
      if (GameClient.bClient) {
         if (this.containingItem != nullptr && this.containingItem.getWorldItem() != nullptr) {
            GameClient.instance.addToItemRemoveSendBuffer(this.containingItem.getWorldItem(), this, var1);
         } else {
            GameClient.instance.addToItemRemoveSendBuffer(this.parent, this, var1);
         }
      }
   }

    void addItemOnServer(InventoryItem var1) {
      if (GameClient.bClient) {
         if (this.containingItem != nullptr && this.containingItem.getWorldItem() != nullptr) {
            GameClient.instance.addToItemSendBuffer(this.containingItem.getWorldItem(), this, var1);
         } else {
            GameClient.instance.addToItemSendBuffer(this.parent, this, var1);
         }
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

    static InventoryItem getBestOf(InventoryItemList var0, Comparator<InventoryItem> var1) {
      if (var0 != nullptr && !var0.empty()) {
    InventoryItem var2 = (InventoryItem)var0.get(0);

         for (int var3 = 1; var3 < var0.size(); var3++) {
    InventoryItem var4 = (InventoryItem)var0.get(var3);
            if (var1.compare(var4, var2) > 0) {
               var2 = var4;
            }
         }

    return var2;
      } else {
    return nullptr;
      }
   }

    InventoryItem getBest(Predicate<InventoryItem> var1, Comparator<InventoryItem> var2) {
    InventoryItemList var3 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAll(var1, var3);
    InventoryItem var4 = getBestOf(var3, var2);
      TL_itemListPool.get().release(var3);
    return var4;
   }

    InventoryItem getBestRecurse(Predicate<InventoryItem> var1, Comparator<InventoryItem> var2) {
    InventoryItemList var3 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAllRecurse(var1, var3);
    InventoryItem var4 = getBestOf(var3, var2);
      TL_itemListPool.get().release(var3);
    return var4;
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

   public std::vector<InventoryItem> getSome(Predicate<InventoryItem> var1, int var2, std::vector<InventoryItem> var3) {
      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         if (var5 == nullptr) {
            this.Items.remove(var4);
            var4--;
         } else if (var1.test(var5)) {
            var3.push_back(var5);
            if (var3.size() >= var2) {
               break;
            }
         }
      }

    return var3;
   }

   public std::vector<InventoryItem> getSomeRecurse(Predicate<InventoryItem> var1, int var2, std::vector<InventoryItem> var3) {
    InventoryItemList var4 = (InventoryItemList)TL_itemListPool.get().alloc();

      for (int var5 = 0; var5 < this.Items.size(); var5++) {
    InventoryItem var6 = this.Items.get(var5);
         if (var6 == nullptr) {
            this.Items.remove(var5);
            var5--;
         } else {
            if (var1.test(var6)) {
               var3.push_back(var6);
               if (var3.size() >= var2) {
                  TL_itemListPool.get().release(var4);
    return var3;
               }
            }

            if (dynamic_cast<InventoryContainer*>(var6) != nullptr) {
               var4.push_back(var6);
            }
         }
      }

      for (int var7 = 0; var7 < var4.size(); var7++) {
    ItemContainer var8 = ((InventoryContainer)var4.get(var7)).getInventory();
         var8.getSomeRecurse(var1, var2, var3);
         if (var3.size() >= var2) {
            break;
         }
      }

      TL_itemListPool.get().release(var4);
    return var3;
   }

   public std::vector<InventoryItem> getAll(Predicate<InventoryItem> var1, std::vector<InventoryItem> var2) {
      for (int var3 = 0; var3 < this.Items.size(); var3++) {
    InventoryItem var4 = this.Items.get(var3);
         if (var4 == nullptr) {
            this.Items.remove(var3);
            var3--;
         } else if (var1.test(var4)) {
            var2.push_back(var4);
         }
      }

    return var2;
   }

   public std::vector<InventoryItem> getAllRecurse(Predicate<InventoryItem> var1, std::vector<InventoryItem> var2) {
    InventoryItemList var3 = (InventoryItemList)TL_itemListPool.get().alloc();

      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         if (var5 == nullptr) {
            this.Items.remove(var4);
            var4--;
         } else {
            if (var1.test(var5)) {
               var2.push_back(var5);
            }

            if (dynamic_cast<InventoryContainer*>(var5) != nullptr) {
               var3.push_back(var5);
            }
         }
      }

      for (int var6 = 0; var6 < var3.size(); var6++) {
    ItemContainer var7 = ((InventoryContainer)var3.get(var6)).getInventory();
         var7.getAllRecurse(var1, var2);
      }

      TL_itemListPool.get().release(var3);
    return var2;
   }

    int getCount(Predicate<InventoryItem> var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAll(var1, var2);
    int var3 = var2.size();
      TL_itemListPool.get().release(var2);
    return var3;
   }

    int getCountRecurse(Predicate<InventoryItem> var1) {
    InventoryItemList var2 = (InventoryItemList)TL_itemListPool.get().alloc();
      this.getAllRecurse(var1, var2);
    int var3 = var2.size();
      TL_itemListPool.get().release(var2);
    return var3;
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

   public std::vector<InventoryItem> getSomeCategory(std::string var1, int var2, std::vector<InventoryItem> var3) {
    CategoryPredicate var4 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    std::vector var5 = this.getSome(var4, var2, var3);
      TL_predicates.get().category.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeCategoryRecurse(std::string var1, int var2, std::vector<InventoryItem> var3) {
    CategoryPredicate var4 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    std::vector var5 = this.getSomeRecurse(var4, var2, var3);
      TL_predicates.get().category.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeTag(std::string var1, int var2, std::vector<InventoryItem> var3) {
    TagPredicate var4 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    std::vector var5 = this.getSome(var4, var2, var3);
      TL_predicates.get().tag.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeTagEval(std::string var1, LuaClosure var2, int var3, std::vector<InventoryItem> var4) {
    TagEvalPredicate var5 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    std::vector var6 = this.getSome(var5, var3, var4);
      TL_predicates.get().tagEval.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getSomeTagEvalArg(std::string var1, LuaClosure var2, Object var3, int var4, std::vector<InventoryItem> var5) {
    TagEvalArgPredicate var6 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    std::vector var7 = this.getSome(var6, var4, var5);
      TL_predicates.get().tagEvalArg.release(var6);
    return var7;
   }

   public std::vector<InventoryItem> getSomeTagRecurse(std::string var1, int var2, std::vector<InventoryItem> var3) {
    TagPredicate var4 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    std::vector var5 = this.getSomeRecurse(var4, var2, var3);
      TL_predicates.get().tag.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeTagEvalRecurse(std::string var1, LuaClosure var2, int var3, std::vector<InventoryItem> var4) {
    TagEvalPredicate var5 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    std::vector var6 = this.getSomeRecurse(var5, var3, var4);
      TL_predicates.get().tagEval.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getSomeTagEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, int var4, std::vector<InventoryItem> var5) {
    TagEvalArgPredicate var6 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    std::vector var7 = this.getSomeRecurse(var6, var4, var5);
      TL_predicates.get().tagEvalArg.release(var6);
    return var7;
   }

   public std::vector<InventoryItem> getSomeType(std::string var1, int var2, std::vector<InventoryItem> var3) {
    TypePredicate var4 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    std::vector var5 = this.getSome(var4, var2, var3);
      TL_predicates.get().type.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeTypeEval(std::string var1, LuaClosure var2, int var3, std::vector<InventoryItem> var4) {
    TypeEvalPredicate var5 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    std::vector var6 = this.getSome(var5, var3, var4);
      TL_predicates.get().typeEval.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getSomeTypeEvalArg(std::string var1, LuaClosure var2, Object var3, int var4, std::vector<InventoryItem> var5) {
    TypeEvalArgPredicate var6 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    std::vector var7 = this.getSome(var6, var4, var5);
      TL_predicates.get().typeEvalArg.release(var6);
    return var7;
   }

   public std::vector<InventoryItem> getSomeTypeRecurse(std::string var1, int var2, std::vector<InventoryItem> var3) {
    TypePredicate var4 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    std::vector var5 = this.getSomeRecurse(var4, var2, var3);
      TL_predicates.get().type.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeTypeEvalRecurse(std::string var1, LuaClosure var2, int var3, std::vector<InventoryItem> var4) {
    TypeEvalPredicate var5 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    std::vector var6 = this.getSomeRecurse(var5, var3, var4);
      TL_predicates.get().typeEval.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getSomeTypeEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, int var4, std::vector<InventoryItem> var5) {
    TypeEvalArgPredicate var6 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    std::vector var7 = this.getSomeRecurse(var6, var4, var5);
      TL_predicates.get().typeEvalArg.release(var6);
    return var7;
   }

   public std::vector<InventoryItem> getSomeEval(LuaClosure var1, int var2, std::vector<InventoryItem> var3) {
    EvalPredicate var4 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    std::vector var5 = this.getSome(var4, var2, var3);
      TL_predicates.get().eval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeEvalArg(LuaClosure var1, Object var2, int var3, std::vector<InventoryItem> var4) {
    EvalArgPredicate var5 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    std::vector var6 = this.getSome(var5, var3, var4);
      TL_predicates.get().evalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getSomeEvalRecurse(LuaClosure var1, int var2, std::vector<InventoryItem> var3) {
    EvalPredicate var4 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    std::vector var5 = this.getSomeRecurse(var4, var2, var3);
      TL_predicates.get().eval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeEvalArgRecurse(LuaClosure var1, Object var2, int var3, std::vector<InventoryItem> var4) {
    EvalArgPredicate var5 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    std::vector var6 = this.getSomeRecurse(var5, var3, var4);
      TL_predicates.get().evalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getAllCategory(std::string var1, std::vector<InventoryItem> var2) {
    CategoryPredicate var3 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    std::vector var4 = this.getAll(var3, var2);
      TL_predicates.get().category.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllCategoryRecurse(std::string var1, std::vector<InventoryItem> var2) {
    CategoryPredicate var3 = ((CategoryPredicate)TL_predicates.get().category.alloc()).init(var1);
    std::vector var4 = this.getAllRecurse(var3, var2);
      TL_predicates.get().category.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllTag(std::string var1, std::vector<InventoryItem> var2) {
    TagPredicate var3 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    std::vector var4 = this.getAll(var3, var2);
      TL_predicates.get().tag.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllTagEval(std::string var1, LuaClosure var2, std::vector<InventoryItem> var3) {
    TagEvalPredicate var4 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    std::vector var5 = this.getAll(var4, var3);
      TL_predicates.get().tagEval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getAllTagEvalArg(std::string var1, LuaClosure var2, Object var3, std::vector<InventoryItem> var4) {
    TagEvalArgPredicate var5 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    std::vector var6 = this.getAll(var5, var4);
      TL_predicates.get().tagEvalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getAllTagRecurse(std::string var1, std::vector<InventoryItem> var2) {
    TagPredicate var3 = ((TagPredicate)TL_predicates.get().tag.alloc()).init(var1);
    std::vector var4 = this.getAllRecurse(var3, var2);
      TL_predicates.get().tag.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllTagEvalRecurse(std::string var1, LuaClosure var2, std::vector<InventoryItem> var3) {
    TagEvalPredicate var4 = ((TagEvalPredicate)TL_predicates.get().tagEval.alloc()).init(var1, var2);
    std::vector var5 = this.getAllRecurse(var4, var3);
      TL_predicates.get().tagEval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getAllTagEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, std::vector<InventoryItem> var4) {
    TagEvalArgPredicate var5 = ((TagEvalArgPredicate)TL_predicates.get().tagEvalArg.alloc()).init(var1, var2, var3);
    std::vector var6 = this.getAllRecurse(var5, var4);
      TL_predicates.get().tagEvalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getAllType(std::string var1, std::vector<InventoryItem> var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    std::vector var4 = this.getAll(var3, var2);
      TL_predicates.get().type.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllTypeEval(std::string var1, LuaClosure var2, std::vector<InventoryItem> var3) {
    TypeEvalPredicate var4 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    std::vector var5 = this.getAll(var4, var3);
      TL_predicates.get().typeEval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getAllTypeEvalArg(std::string var1, LuaClosure var2, Object var3, std::vector<InventoryItem> var4) {
    TypeEvalArgPredicate var5 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    std::vector var6 = this.getAll(var5, var4);
      TL_predicates.get().typeEvalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getAllTypeRecurse(std::string var1, std::vector<InventoryItem> var2) {
    TypePredicate var3 = ((TypePredicate)TL_predicates.get().type.alloc()).init(var1);
    std::vector var4 = this.getAllRecurse(var3, var2);
      TL_predicates.get().type.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllTypeEvalRecurse(std::string var1, LuaClosure var2, std::vector<InventoryItem> var3) {
    TypeEvalPredicate var4 = ((TypeEvalPredicate)TL_predicates.get().typeEval.alloc()).init(var1, var2);
    std::vector var5 = this.getAllRecurse(var4, var3);
      TL_predicates.get().typeEval.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getAllTypeEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, std::vector<InventoryItem> var4) {
    TypeEvalArgPredicate var5 = ((TypeEvalArgPredicate)TL_predicates.get().typeEvalArg.alloc()).init(var1, var2, var3);
    std::vector var6 = this.getAllRecurse(var5, var4);
      TL_predicates.get().typeEvalArg.release(var5);
    return var6;
   }

   public std::vector<InventoryItem> getAllEval(LuaClosure var1, std::vector<InventoryItem> var2) {
    EvalPredicate var3 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    std::vector var4 = this.getAll(var3, var2);
      TL_predicates.get().eval.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllEvalArg(LuaClosure var1, Object var2, std::vector<InventoryItem> var3) {
    EvalArgPredicate var4 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    std::vector var5 = this.getAll(var4, var3);
      TL_predicates.get().evalArg.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getAllEvalRecurse(LuaClosure var1, std::vector<InventoryItem> var2) {
    EvalPredicate var3 = ((EvalPredicate)TL_predicates.get().eval.alloc()).init(var1);
    std::vector var4 = this.getAllRecurse(var3, var2);
      TL_predicates.get().eval.release(var3);
    return var4;
   }

   public std::vector<InventoryItem> getAllEvalArgRecurse(LuaClosure var1, Object var2, std::vector<InventoryItem> var3) {
    EvalArgPredicate var4 = ((EvalArgPredicate)TL_predicates.get().evalArg.alloc()).init(var1, var2);
    std::vector var5 = this.getAllRecurse(var4, var3);
      TL_predicates.get().evalArg.release(var4);
    return var5;
   }

   public std::vector<InventoryItem> getSomeCategory(std::string var1, int var2) {
      return this.getSomeCategory(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeEval(LuaClosure var1, int var2) {
      return this.getSomeEval(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeEvalArg(LuaClosure var1, Object var2, int var3) {
      return this.getSomeEvalArg(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTypeEval(std::string var1, LuaClosure var2, int var3) {
      return this.getSomeTypeEval(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTypeEvalArg(std::string var1, LuaClosure var2, Object var3, int var4) {
      return this.getSomeTypeEvalArg(var1, var2, var3, var4, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeEvalRecurse(LuaClosure var1, int var2) {
      return this.getSomeEvalRecurse(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeEvalArgRecurse(LuaClosure var1, Object var2, int var3) {
      return this.getSomeEvalArgRecurse(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTag(std::string var1, int var2) {
      return this.getSomeTag(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTagRecurse(std::string var1, int var2) {
      return this.getSomeTagRecurse(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTagEvalRecurse(std::string var1, LuaClosure var2, int var3) {
      return this.getSomeTagEvalRecurse(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTagEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, int var4) {
      return this.getSomeTagEvalArgRecurse(var1, var2, var3, var4, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeType(std::string var1, int var2) {
      return this.getSomeType(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTypeRecurse(std::string var1, int var2) {
      return this.getSomeTypeRecurse(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTypeEvalRecurse(std::string var1, LuaClosure var2, int var3) {
      return this.getSomeTypeEvalRecurse(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getSomeTypeEvalArgRecurse(std::string var1, LuaClosure var2, Object var3, int var4) {
      return this.getSomeTypeEvalArgRecurse(var1, var2, var3, var4, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAll(Predicate<InventoryItem> var1) {
      return this.getAll(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllCategory(std::string var1) {
      return this.getAllCategory(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllEval(LuaClosure var1) {
      return this.getAllEval(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllEvalArg(LuaClosure var1, Object var2) {
      return this.getAllEvalArg(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTagEval(std::string var1, LuaClosure var2) {
      return this.getAllTagEval(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTagEvalArg(std::string var1, LuaClosure var2, Object var3) {
      return this.getAllTagEvalArg(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTypeEval(std::string var1, LuaClosure var2) {
      return this.getAllTypeEval(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTypeEvalArg(std::string var1, LuaClosure var2, Object var3) {
      return this.getAllTypeEvalArg(var1, var2, var3, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllEvalRecurse(LuaClosure var1) {
      return this.getAllEvalRecurse(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllEvalArgRecurse(LuaClosure var1, Object var2) {
      return this.getAllEvalArgRecurse(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllType(std::string var1) {
      return this.getAllType(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTypeRecurse(std::string var1) {
      return this.getAllTypeRecurse(var1, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTypeEvalRecurse(std::string var1, LuaClosure var2) {
      return this.getAllTypeEvalRecurse(var1, var2, std::make_unique<std::vector<>>());
   }

   public std::vector<InventoryItem> getAllTypeEvalArgRecurse(std::string var1, LuaClosure var2, Object var3) {
      return this.getAllTypeEvalArgRecurse(var1, var2, var3, std::make_unique<std::vector<>>());
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

   public std::vector<InventoryItem> FindAndReturn(std::string var1, int var2) {
      return this.getSomeType(var1, var2);
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

   public std::vector<InventoryItem> FindAll(std::string var1) {
      return this.getAllType(var1);
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

   public std::vector<InventoryItem> save(ByteBuffer var1, IsoGameCharacter var2) throws IOException {
      GameWindow.WriteString(var1, this.type);
      var1.put((byte)(this.bExplored ? 1 : 0));
    std::vector var3 = CompressIdenticalItems.save(var1, this.Items, nullptr);
      var1.put((byte)(this.isHasBeenLooted() ? 1 : 0));
      var1.putInt(this.Capacity);
    return var3;
   }

   public std::vector<InventoryItem> save(ByteBuffer var1) throws IOException {
      return this.save(var1, nullptr);
   }

   public std::vector<InventoryItem> load(ByteBuffer var1, int var2) throws IOException {
      this.type = GameWindow.ReadString(var1);
      this.bExplored = var1.get() == 1;
    std::vector var3 = CompressIdenticalItems.load(var1, var2, this.Items, this.IncludingObsoleteItems);

      for (int var4 = 0; var4 < this.Items.size(); var4++) {
    InventoryItem var5 = this.Items.get(var4);
         var5.container = this;
      }

      this.setHasBeenLooted(var1.get() == 1);
      this.Capacity = var1.getInt();
      this.dirty = false;
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

   public std::vector<InventoryItem> getItems() {
      return this.Items;
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

   public std::vector<InventoryItem> getAllWaterFillables() {
      tempList.clear();

      for (int var1 = 0; var1 < this.Items.size(); var1++) {
    InventoryItem var2 = this.Items.get(var1);
         if (var2.CanStoreWater) {
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

   public std::vector<InventoryItem> getItemsFromType(std::string var1) {
      return this.getAllType(var1);
   }

   public std::vector<InventoryItem> getItemsFromFullType(std::string var1) {
      return var1 != nullptr && var1.contains(".") ? this.getAllType(var1) : std::make_unique<std::vector<>>();
   }

   public std::vector<InventoryItem> getItemsFromFullType(std::string var1, boolean var2) {
      if (var1 != nullptr && var1.contains(".")) {
         return var2 ? this.getAllTypeRecurse(var1) : this.getAllType(var1);
      } else {
         return std::make_unique<std::vector<>>();
      }
   }

   public std::vector<InventoryItem> getItemsFromType(std::string var1, boolean var2) {
      return var2 ? this.getAllTypeRecurse(var1) : this.getAllType(var1);
   }

   public std::vector<InventoryItem> getItemsFromCategory(std::string var1) {
      return this.getAllCategory(var1);
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

   public LinkedHashMap<std::string, InventoryItem> getItems4Admin() {
    LinkedHashMap var1 = std::make_shared<LinkedHashMap>();

      for (int var2 = 0; var2 < this.getItems().size(); var2++) {
    InventoryItem var3 = this.getItems().get(var2);
         var3.setCount(1);
         if (var3.getCat() != ItemType.Drainable
            && var3.getCat() != ItemType.Weapon
            && var1.get(var3.getFullType()) != nullptr
            && !(dynamic_cast<InventoryContainer*>(var3) != nullptr)) {
            ((InventoryItem)var1.get(var3.getFullType())).setCount(((InventoryItem)var1.get(var3.getFullType())).getCount() + 1);
         } else if (var1.get(var3.getFullType()) != nullptr) {
            var1.put(var3.getFullType() + Rand.Next(100000), var3);
         } else {
            var1.put(var3.getFullType(), var3);
         }
      }

    return var1;
   }

   public LinkedHashMap<std::string, InventoryItem> getAllItems(LinkedHashMap<std::string, InventoryItem> var1, boolean var2) {
      if (var1 == nullptr) {
         var1 = std::make_unique<LinkedHashMap>();
      }

      for (int var3 = 0; var3 < this.getItems().size(); var3++) {
    InventoryItem var4 = this.getItems().get(var3);
         if (var2) {
            var4.setWorker("inInv");
         }

         var4.setCount(1);
         if (var4.getCat() != ItemType.Drainable && var4.getCat() != ItemType.Weapon && var1.get(var4.getFullType()) != nullptr) {
            ((InventoryItem)var1.get(var4.getFullType())).setCount(((InventoryItem)var1.get(var4.getFullType())).getCount() + 1);
         } else if (var1.get(var4.getFullType()) != nullptr) {
            var1.put(var4.getFullType() + Rand.Next(100000), var4);
         } else {
            var1.put(var4.getFullType(), var4);
         }

         if (dynamic_cast<InventoryContainer*>(var4) != nullptr
            && ((InventoryContainer)var4).getItemContainer() != nullptr
            && !((InventoryContainer)var4).getItemContainer().getItems().empty()) {
            var1 = ((InventoryContainer)var4).getItemContainer().getAllItems(var1, true);
         }
      }

    return var1;
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
