#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/SandboxOptions.h"
#include "zombie/audio/BaseSoundEmitter.h"
#include "zombie/characterTextures/BloodBodyPartType.h"
#include "zombie/characterTextures/BloodClothingType.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/SurvivorDesc.h"
#include "zombie/core/Color.h"
#include "zombie/core/Colors.h"
#include "zombie/core/Core.h"
#include "zombie/core/Translator.h"
#include "zombie/core/logger/ExceptionLogger.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/skinnedmodel/model/WorldItemAtlas/ItemTexture.h"
#include "zombie/core/skinnedmodel/population/ClothingItem.h"
#include "zombie/core/skinnedmodel/visual/ItemVisual.h"
#include "zombie/core/stash/StashSystem.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/utils/Bits.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
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
#include "zombie/iso/objects/IsoWorldInventoryObject.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/network/GameClient.h"
#include "zombie/radio/ZomboidRadio.h"
#include "zombie/radio/media/MediaData.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/scripting/objects/ItemReplacement.h"
#include "zombie/ui/ObjectTooltip.h"
#include "zombie/ui/ObjectTooltip/Layout.h"
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIFont.h"
#include "zombie/util/StringUtils.h"
#include "zombie/util/Type.h"
#include "zombie/util/io/BitHeader.h"
#include "zombie/util/io/BitHeader/HeaderSize.h"
#include "zombie/util/io/BitHeaderRead.h"
#include "zombie/util/io/BitHeaderWrite.h"
#include "zombie/vehicles/VehiclePart.h"
#include "zombie/world/ItemInfo.h"
#include "zombie/world/WorldDictionary.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace inventory {


class InventoryItem {
public:
    IsoGameCharacter previousOwner = nullptr;
    Item ScriptItem = nullptr;
    ItemType cat = ItemType.None;
    ItemContainer container;
    int containerX = 0;
    int containerY = 0;
    std::string name;
    std::string replaceOnUse = nullptr;
    std::string replaceOnUseFullType = nullptr;
    int ConditionMax = 10;
    ItemContainer rightClickContainer = nullptr;
    Texture texture;
    Texture texturerotten;
    Texture textureCooked;
    Texture textureBurnt;
    std::string type;
    std::string fullType;
    int uses = 1;
    float Age = 0.0F;
    float LastAged = -1.0F;
    bool IsCookable = false;
    float CookingTime = 0.0F;
    float MinutesToCook = 60.0F;
    float MinutesToBurn = 120.0F;
    bool Cooked = false;
    bool Burnt = false;
    int OffAge = 1000000000;
    int OffAgeMax = 1000000000;
    float Weight = 1.0F;
    float ActualWeight = 1.0F;
    std::string WorldTexture;
    std::string Description;
    int Condition = 10;
    std::string OffString = Translator.getText("Tooltip_food_Rotten");
    std::string FreshString = Translator.getText("Tooltip_food_Fresh");
    std::string StaleString = Translator.getText("Tooltip_food_Stale");
    std::string CookedString = Translator.getText("Tooltip_food_Cooked");
    std::string UnCookedString = Translator.getText("Tooltip_food_Uncooked");
    std::string FrozenString = Translator.getText("Tooltip_food_Frozen");
    std::string BurntString = Translator.getText("Tooltip_food_Burnt");
    std::string brokenString = Translator.getText("Tooltip_broken");
    std::string module = "Base";
    float boredomChange = 0.0F;
    float unhappyChange = 0.0F;
    float stressChange = 0.0F;
   protected std::vector<IsoObject> Taken = std::make_unique<std::vector<>>();
    IsoDirections placeDir = IsoDirections.Max;
    IsoDirections newPlaceDir = IsoDirections.Max;
    KahluaTable table = nullptr;
    std::string ReplaceOnUseOn = nullptr;
    Color col = Color.white;
    bool IsWaterSource = false;
    bool CanStoreWater = false;
    bool CanStack = false;
    bool activated = false;
    bool isTorchCone = false;
    int lightDistance = 0;
    int Count = 1;
    float fatigueChange = 0.0F;
    IsoWorldInventoryObject worldItem = nullptr;
    std::string customMenuOption = nullptr;
    std::string tooltip = nullptr;
    std::string displayCategory = nullptr;
    int haveBeenRepaired = 1;
    bool broken = false;
    std::string originalName = nullptr;
    int id = 0;
    bool RequiresEquippedBothHands;
    ByteBuffer byteData;
   public std::vector<std::string> extraItems = nullptr;
    bool customName = false;
    std::string breakSound = nullptr;
    bool alcoholic = false;
    float alcoholPower = 0.0F;
    float bandagePower = 0.0F;
    float ReduceInfectionPower = 0.0F;
    bool customWeight = false;
    bool customColor = false;
    int keyId = -1;
    bool taintedWater = false;
    bool remoteController = false;
    bool canBeRemote = false;
    int remoteControlID = -1;
    int remoteRange = 0;
    float colorRed = 1.0F;
    float colorGreen = 1.0F;
    float colorBlue = 1.0F;
    std::string countDownSound = nullptr;
    std::string explosionSound = nullptr;
    IsoGameCharacter equipParent = nullptr;
    std::string evolvedRecipeName = nullptr;
    float metalValue = 0.0F;
    float itemHeat = 1.0F;
    float meltingTime = 0.0F;
    std::string worker;
    bool isWet = false;
    float wetCooldown = -1.0F;
    std::string itemWhenDry = nullptr;
    bool favorite = false;
   protected std::vector<std::string> requireInHandOrInventory = nullptr;
    std::string map = nullptr;
    std::string stashMap = nullptr;
    bool keepOnDeplete = false;
    bool zombieInfected = false;
    bool rainFactorZero = false;
    float itemCapacity = -1.0F;
    int maxCapacity = -1;
    float brakeForce = 0.0F;
    int chanceToSpawnDamaged = 0;
    float conditionLowerNormal = 0.0F;
    float conditionLowerOffroad = 0.0F;
    float wheelFriction = 0.0F;
    float suspensionDamping = 0.0F;
    float suspensionCompression = 0.0F;
    float engineLoudness = 0.0F;
    ItemVisual visual = nullptr;
    std::string staticModel = nullptr;
   private std::vector<std::string> iconsForTexture = nullptr;
   private std::vector<BloodClothingType> bloodClothingType = std::make_unique<std::vector<>>();
    int stashChance = 80;
    std::string ammoType = nullptr;
    int maxAmmo = 0;
    int currentAmmoCount = 0;
    std::string gunType = nullptr;
    std::string attachmentType = nullptr;
   private std::vector<std::string> attachmentsProvided = nullptr;
    int attachedSlot = -1;
    std::string attachedSlotType = nullptr;
    std::string attachmentReplacement = nullptr;
    std::string attachedToModel = nullptr;
    std::string m_alternateModelName = nullptr;
    short registry_id = -1;
    int worldZRotation = -1;
    float worldScale = 1.0F;
    short recordedMediaIndex = -1;
    uint8_t mediaType = -1;
    bool isInitialised = false;
    ItemTexture atlasTexture = nullptr;
    const int maxTextLength = 256;
    float jobDelta = 0.0F;
    std::string jobType = nullptr;
    static ByteBuffer tempBuffer = ByteBuffer.allocate(20000);
    std::string mainCategory = nullptr;
    bool canBeActivated;
    float lightStrength;
    std::string CloseKillMove = nullptr;
    bool beingFilled = false;

    int getSaveType() {
      throw RuntimeException("InventoryItem.getSaveType() not implemented for " + this.getClass().getName());
   }

    IsoWorldInventoryObject getWorldItem() {
      return this.worldItem;
   }

    void setEquipParent(IsoGameCharacter var1) {
      this.equipParent = var1;
   }

    IsoGameCharacter getEquipParent() {
      return this.equipParent == nullptr || this.equipParent.getPrimaryHandItem() != this && this.equipParent.getSecondaryHandItem() != this
         ? nullptr
         : this.equipParent;
   }

    std::string getBringToBearSound() {
      return this.getScriptItem().getBringToBearSound();
   }

    std::string getEquipSound() {
      return this.getScriptItem().getEquipSound();
   }

    std::string getUnequipSound() {
      return this.getScriptItem().getUnequipSound();
   }

    void setWorldItem(IsoWorldInventoryObject var1) {
      this.worldItem = var1;
   }

    void setJobDelta(float var1) {
      this.jobDelta = var1;
   }

    float getJobDelta() {
      return this.jobDelta;
   }

    void setJobType(const std::string& var1) {
      this.jobType = var1;
   }

    std::string getJobType() {
      return this.jobType;
   }

    bool hasModData() {
      return this.table != nullptr && !this.table.empty();
   }

    KahluaTable getModData() {
      if (this.table == nullptr) {
         this.table = LuaManager.platform.newTable();
      }

      return this.table;
   }

    void storeInByteData(IsoObject var1) {
      tempBuffer.clear();

      try {
         var1.save(tempBuffer, false);
      } catch (IOException var3) {
         var3.printStackTrace();
      }

      tempBuffer.flip();
      if (this.byteData == nullptr || this.byteData.capacity() < tempBuffer.limit() - 2 + 8) {
         this.byteData = ByteBuffer.allocate(tempBuffer.limit() - 2 + 8);
      }

      tempBuffer.get();
      tempBuffer.get();
      this.byteData.clear();
      this.byteData.put((byte)87);
      this.byteData.put((byte)86);
      this.byteData.put((byte)69);
      this.byteData.put((byte)82);
      this.byteData.putInt(195);
      this.byteData.put(tempBuffer);
      this.byteData.flip();
   }

    ByteBuffer getByteData() {
      return this.byteData;
   }

    bool isRequiresEquippedBothHands() {
      return this.RequiresEquippedBothHands;
   }

    float getA() {
      return this.col.a;
   }

    float getR() {
      return this.col.r;
   }

    float getG() {
      return this.col.g;
   }

    float getB() {
      return this.col.b;
   }

    public InventoryItem(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
      this.col = Color.white;
      this.texture = Texture.trygetTexture(var4);
      if (this.texture == nullptr) {
         this.texture = Texture.getSharedTexture("media/inventory/Question_On.png");
      }

      this.module = var1;
      this.name = var2;
      this.originalName = var2;
      this.type = var3;
      this.fullType = var1 + "." + var3;
      this.WorldTexture = var4.replace("Item_", "media/inventory/world/WItem_");
      this.WorldTexture = this.WorldTexture + ".png";
   }

    public InventoryItem(const std::string& var1, const std::string& var2, const std::string& var3, Item var4) {
      this.col = Color.white;
      this.texture = var4.NormalTexture;
      this.module = var1;
      this.name = var2;
      this.originalName = var2;
      this.type = var3;
      this.fullType = var1 + "." + var3;
      this.WorldTexture = var4.WorldTextureName;
   }

    std::string getType() {
      return this.type;
   }

    Texture getTex() {
      return this.texture;
   }

    std::string getCategory() {
      return this.mainCategory != nullptr ? this.mainCategory : "Item";
   }

    bool IsRotten() {
      return this.Age > this.OffAge;
   }

    float HowRotten() {
      if (this.OffAgeMax - this.OffAge == 0) {
         return this.Age > this.OffAge ? 1.0F : 0.0F;
      } else {
         return (this.Age - this.OffAge) / (this.OffAgeMax - this.OffAge);
      }
   }

    bool CanStack(InventoryItem var1) {
    return false;
   }

    bool ModDataMatches(InventoryItem var1) {
    KahluaTable var2 = var1.getModData();
    KahluaTable var3 = var1.getModData();
      if (var2 == nullptr && var3 == nullptr) {
    return true;
      } else if (var2 == nullptr) {
    return false;
      } else if (var3 == nullptr) {
    return false;
      } else if (var2.len() != var3.len()) {
    return false;
      } else {
    KahluaTableIterator var4 = var2.iterator();

         while (var4.advance()) {
    void* var5 = var3.rawget(var4.getKey());
    void* var6 = var4.getValue();
            if (!var5 == var6)) {
    return false;
            }
         }

    return true;
      }
   }

    void DoTooltip(ObjectTooltip var1) {
      var1.render();
    UIFont var2 = var1.getFont();
    int var3 = var1.getLineSpacing();
    int var4 = 5;
    std::string var5 = "";
      if (this.Burnt) {
         var5 = var5 + this.BurntString + " ";
      } else if (this.OffAge < 1000000000 && this.Age < this.OffAge) {
         var5 = var5 + this.FreshString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
         var5 = var5 + this.OffString + " ";
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAge) {
         var5 = var5 + this.StaleString + " ";
      }

      if (this.isCooked() && !this.Burnt && !this.hasTag("HideCooked")) {
         var5 = var5 + this.CookedString + " ";
      } else if (this.IsCookable && !this.Burnt && !(dynamic_cast<DrainableComboItem*>(this) != nullptr) && !this.hasTag("HideCooked")) {
         var5 = var5 + this.UnCookedString + " ";
      }

      if (dynamic_cast<Food*>(this) != nullptr && ((Food)this).isFrozen()) {
         var5 = var5 + this.FrozenString + " ";
      }

      var5 = var5.trim();
    std::string var6;
      if (var5.empty()) {
         var1.DrawText(var2, var6 = this.getName(), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
      } else if (this.OffAgeMax < 1000000000 && this.Age >= this.OffAgeMax) {
         var1.DrawText(var2, var6 = Translator.getText("IGUI_FoodNaming", var5, this.name), 5.0, var4, 1.0, 0.1F, 0.1F, 1.0);
      } else {
         var1.DrawText(var2, var6 = Translator.getText("IGUI_FoodNaming", var5, this.name), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
      }

      var1.adjustWidth(5, var6);
      var4 += var3 + 5;
      if (this.extraItems != nullptr) {
         var1.DrawText(var2, Translator.getText("Tooltip_item_Contains"), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
    int var7 = 5 + TextManager.instance.MeasureStringX(var2, Translator.getText("Tooltip_item_Contains")) + 4;
    int var8 = (var3 - 10) / 2;

         for (int var9 = 0; var9 < this.extraItems.size(); var9++) {
    InventoryItem var10 = InventoryItemFactory.CreateItem(this.extraItems.get(var9));
            if (!this.IsCookable && var10.IsCookable) {
               var10.setCooked(true);
            }

            if (this.isCooked() && var10.IsCookable) {
               var10.setCooked(true);
            }

            var1.DrawTextureScaled(var10.getTex(), var7, var4 + var8, 10.0, 10.0, 1.0);
            var7 += 11;
         }

         var4 = var4 + var3 + 5;
      }

      if (dynamic_cast<Food*>(this) != nullptr && ((Food)this).spices != nullptr) {
         var1.DrawText(var2, Translator.getText("Tooltip_item_Spices"), 5.0, var4, 1.0, 1.0, 0.8F, 1.0);
    int var18 = 5 + TextManager.instance.MeasureStringX(var2, Translator.getText("Tooltip_item_Spices")) + 4;
    int var20 = (var3 - 10) / 2;

         for (int var51 = 0; var51 < ((Food)this).spices.size(); var51++) {
    InventoryItem var53 = InventoryItemFactory.CreateItem((std::string)((Food)this).spices.get(var51));
            var1.DrawTextureScaled(var53.getTex(), var18, var4 + var20, 10.0, 10.0, 1.0);
            var18 += 11;
         }

         var4 = var4 + var3 + 5;
      }

    Layout var19 = var1.beginLayout();
      var19.setMinLabelWidth(80);
    LayoutItem var21 = var19.addItem();
      var21.setLabel(Translator.getText("Tooltip_item_Weight") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    bool var52 = this.isEquipped();
      if (!(dynamic_cast<HandWeapon*>(this) != nullptr) && !(dynamic_cast<Clothing*>(this) != nullptr) && !(dynamic_cast<DrainableComboItem*>(this) != nullptr) && !this.getFullType().contains("Walkie")) {
    float var54 = this.getUnequippedWeight();
         if (var54 > 0.0F && var54 < 0.01F) {
            var54 = 0.01F;
         }

         var21.setValueRightNoPlus(var54);
      } else if (var52) {
         var21.setValue(
            this.getCleanString(this.getEquippedWeight())
               + "    ("
               + this.getCleanString(this.getUnequippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Unequipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      } else if (this.getAttachedSlot() > -1) {
         var21.setValue(
            this.getCleanString(this.getHotbarEquippedWeight())
               + "    ("
               + this.getCleanString(this.getUnequippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Unequipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      } else {
         var21.setValue(
            this.getCleanString(this.getUnequippedWeight())
               + "    ("
               + this.getCleanString(this.getEquippedWeight())
               + " "
               + Translator.getText("Tooltip_item_Equipped")
               + ")",
            1.0F,
            1.0F,
            1.0F,
            1.0F
         );
      }

      if (var1.getWeightOfStack() > 0.0F) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_item_StackWeight") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    float var55 = var1.getWeightOfStack();
         if (var55 > 0.0F && var55 < 0.01F) {
            var55 = 0.01F;
         }

         var21.setValueRightNoPlus(var55);
      }

      if (this.getMaxAmmo() > 0 && !(dynamic_cast<HandWeapon*>(this) != nullptr)) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_AmmoCount") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(this.getCurrentAmmoCount() + " / " + this.getMaxAmmo(), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (!(dynamic_cast<HandWeapon*>(this) != nullptr) && this.getAmmoType() != nullptr) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("ContextMenu_AmmoType") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    std::string var56 = InventoryItemFactory.CreateItem(this.getAmmoType()).getDisplayName();
         var21.setValue(Translator.getText(var56), 1.0F, 1.0F, 1.0F, 1.0F);
      }

      if (this.gunType != nullptr) {
    Item var57 = ScriptManager.instance.FindItem(this.getGunType());
         if (var57 == nullptr) {
            var57 = ScriptManager.instance.FindItem(this.getModule() + "." + this.ammoType);
         }

         if (var57 != nullptr) {
            var21 = var19.addItem();
            var21.setLabel(Translator.getText("ContextMenu_GunType") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
            var21.setValue(var57.getDisplayName(), 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (Core.bDebug && DebugOptions.instance.TooltipInfo.getValue()) {
         var21 = var19.addItem();
         var21.setLabel("getActualWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getActualWeight());
         var21 = var19.addItem();
         var21.setLabel("getWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getWeight());
         var21 = var19.addItem();
         var21.setLabel("getEquippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getEquippedWeight());
         var21 = var19.addItem();
         var21.setLabel("getUnequippedWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getUnequippedWeight());
         var21 = var19.addItem();
         var21.setLabel("getContentsWeight()", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.getContentsWeight());
         if (dynamic_cast<Key*>(this) != nullptr || "Doorknob" == this.type)) {
            var21 = var19.addItem();
            var21.setLabel("DBG: keyId", 1.0F, 1.0F, 0.8F, 1.0F);
            var21.setValueRightNoPlus(this.getKeyId());
         }

         var21 = var19.addItem();
         var21.setLabel("ID", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.id);
         var21 = var19.addItem();
         var21.setLabel("DictionaryID", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRightNoPlus(this.registry_id);
    ClothingItem var58 = this.getClothingItem();
         if (var58 != nullptr) {
            var21 = var19.addItem();
            var21.setLabel("ClothingItem", 1.0F, 1.0F, 1.0F, 1.0F);
            var21.setValue(this.getClothingItem().m_Name, 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (this.getFatigueChange() != 0.0F) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_item_Fatigue") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValueRight((int)(this.getFatigueChange() * 100.0F), false);
      }

      if (dynamic_cast<DrainableComboItem*>(this) != nullptr) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("IGUI_invpanel_Remaining") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
    float var59 = ((DrainableComboItem)this).getUsedDelta();
    ColorInfo var11 = std::make_shared<ColorInfo>();
         Core.getInstance().getBadHighlitedColor().interp(Core.getInstance().getGoodHighlitedColor(), var59, var11);
         var21.setProgress(var59, var11.getR(), var11.getG(), var11.getB(), 1.0F);
      }

      if (this.isTaintedWater() && SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
         var21 = var19.addItem();
         if (this.isCookable()) {
            var21.setLabel(Translator.getText("Tooltip_item_TaintedWater"), 1.0F, 0.5F, 0.5F, 1.0F);
         } else {
            var21.setLabel(Translator.getText("Tooltip_item_TaintedWater_Plastic"), 1.0F, 0.5F, 0.5F, 1.0F);
         }
      }

      this.DoTooltip(var1, var19);
      if (this.getRemoteControlID() != -1) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_TrapControllerID"), 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(int.toString(this.getRemoteControlID()), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (!FixingManager.getFixes(this).empty()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_Repaired") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         if (this.getHaveBeenRepaired() == 1) {
            var21.setValue(Translator.getText("Tooltip_never"), 1.0F, 1.0F, 1.0F, 1.0F);
         } else {
            var21.setValue(this.getHaveBeenRepaired() - 1 + "x", 1.0F, 1.0F, 1.0F, 1.0F);
         }
      }

      if (this.isEquippedNoSprint()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_CantSprintEquipped"), 1.0F, 0.1F, 0.1F, 1.0F);
      }

      if (this.isWet()) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_Wetness") + ": ", 1.0F, 1.0F, 0.8F, 1.0F);
    float var60 = this.getWetCooldown() / 10000.0F;
    ColorInfo var64 = std::make_shared<ColorInfo>();
         Core.getInstance().getGoodHighlitedColor().interp(Core.getInstance().getBadHighlitedColor(), var60, var64);
         var21.setProgress(var60, var64.getR(), var64.getG(), var64.getB(), 1.0F);
      }

      if (this.getMaxCapacity() > 0) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_container_Capacity") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
    float var61 = this.getMaxCapacity();
         if (this.isConditionAffectsCapacity()) {
            var61 = VehiclePart.getNumberByCondition(this.getMaxCapacity(), this.getCondition(), 5.0F);
         }

         if (this.getItemCapacity() > -1.0F) {
            var21.setValue(this.getItemCapacity() + " / " + var61, 1.0F, 1.0F, 0.8F, 1.0F);
         } else {
            var21.setValue("0 / " + var61, 1.0F, 1.0F, 0.8F, 1.0F);
         }
      }

      if (this.getConditionMax() > 0 && this.getMechanicType() > 0) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText("Tooltip_weapon_Condition") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
         var21.setValue(this.getCondition() + " / " + this.getConditionMax(), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      if (this.isRecordedMedia()) {
    MediaData var62 = this.getMediaData();
         if (var62 != nullptr) {
            if (var62.getTranslatedTitle() != nullptr) {
               var21 = var19.addItem();
               var21.setLabel(Translator.getText("Tooltip_media_title") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               var21.setValue(var62.getTranslatedTitle(), 1.0F, 1.0F, 1.0F, 1.0F);
               if (var62.getTranslatedSubTitle() != nullptr) {
                  var21 = var19.addItem();
                  var21.setLabel("", 1.0F, 1.0F, 0.8F, 1.0F);
                  var21.setValue(var62.getTranslatedSubTitle(), 1.0F, 1.0F, 1.0F, 1.0F);
               }
            }

            if (var62.getTranslatedAuthor() != nullptr) {
               var21 = var19.addItem();
               var21.setLabel(Translator.getText("Tooltip_media_author") + ":", 1.0F, 1.0F, 0.8F, 1.0F);
               var21.setValue(var62.getTranslatedAuthor(), 1.0F, 1.0F, 1.0F, 1.0F);
            }
         }
      }

      if (Core.getInstance().getOptionShowItemModInfo() && !this.isVanilla()) {
         var21 = var19.addItem();
    Color var63 = Colors.CornFlowerBlue;
         var21.setLabel("Mod: " + this.getModName(), var63.r, var63.g, var63.b, 1.0F);
    ItemInfo var65 = WorldDictionary.getItemInfoFromID(this.registry_id);
         if (var65 != nullptr && var65.getModOverrides() != nullptr) {
            var21 = var19.addItem();
    float var12 = 0.5F;
            if (var65.getModOverrides().size() == 1) {
               var21.setLabel("This item overrides: " + WorldDictionary.getModNameFromID((std::string)var65.getModOverrides().get(0)), var12, var12, var12, 1.0F);
            } else {
               var21.setLabel("This item overrides:", var12, var12, var12, 1.0F);

               for (int var13 = 0; var13 < var65.getModOverrides().size(); var13++) {
                  var21 = var19.addItem();
                  var21.setLabel(" - " + WorldDictionary.getModNameFromID((std::string)var65.getModOverrides().get(var13)), var12, var12, var12, 1.0F);
               }
            }
         }
      }

      if (this.getTooltip() != nullptr) {
         var21 = var19.addItem();
         var21.setLabel(Translator.getText(this.tooltip), 1.0F, 1.0F, 0.8F, 1.0F);
      }

      var4 = var19.render(5, var4, var1);
      var1.endLayout(var19);
      var4 += var1.padBottom;
      var1.setHeight(var4);
      if (var1.getWidth() < 150.0) {
         var1.setWidth(150.0);
      }
   }

    std::string getCleanString(float var1) {
    float var2 = (int)((var1 + 0.005) * 100.0) / 100.0F;
      return float.toString(var2);
   }

    void DoTooltip(ObjectTooltip var1, Layout var2) {
   }

    void SetContainerPosition(int var1, int var2) {
      this.containerX = var1;
      this.containerY = var2;
   }

    void Use() {
      this.Use(false);
   }

    void UseItem() {
      this.Use(false);
   }

    void Use(bool var1) {
      this.Use(var1, false);
   }

    void Use(bool var1, bool var2) {
      if (this.isDisappearOnUse() || var1) {
         this.uses--;
         if (this.replaceOnUse != nullptr && !var2 && !var1 && this.container != nullptr) {
    std::string var3 = this.replaceOnUse;
            if (!this.replaceOnUse.contains(".")) {
               var3 = this.module + "." + var3;
            }

    InventoryItem var4 = this.container.AddItem(var3);
            if (var4 != nullptr) {
               var4.setConditionFromModData(this);
            }

            this.container.setDrawDirty(true);
            this.container.setDirty(true);
            var4.setFavorite(this.isFavorite());
         }

         if (this.uses <= 0) {
            if (this.keepOnDeplete) {
               return;
            }

            if (this.container != nullptr) {
               if (this.container.dynamic_cast<IsoGameCharacter*>(parent) != nullptr && !(dynamic_cast<HandWeapon*>(this) != nullptr)) {
    IsoGameCharacter var5 = (IsoGameCharacter)this.container.parent;
                  var5.removeFromHands(this);
               }

               this.container.Items.remove(this);
               this.container.setDirty(true);
               this.container.setDrawDirty(true);
               this.container = nullptr;
            }
         }
      }
   }

    bool shouldUpdateInWorld() {
      if (!GameClient.bClient && !this.rainFactorZero && this.canStoreWater() && this.hasReplaceType("WaterSource")) {
    IsoGridSquare var1 = this.getWorldItem().getSquare();
         return var1 != nullptr && var1.isOutside();
      } else {
    return false;
      }
   }

    void update() {
      if (this.isWet()) {
         this.wetCooldown = this.wetCooldown - 1.0F * GameTime.instance.getMultiplier();
         if (this.wetCooldown <= 0.0F) {
    InventoryItem var1 = InventoryItemFactory.CreateItem(this.itemWhenDry);
            if (this.isFavorite()) {
               var1.setFavorite(true);
            }

    IsoWorldInventoryObject var2 = this.getWorldItem();
            if (var2 != nullptr) {
    IsoGridSquare var3 = var2.getSquare();
               var3.AddWorldInventoryItem(var1, var2.getX() % 1.0F, var2.getY() % 1.0F, var2.getZ() % 1.0F);
               var3.transmitRemoveItemFromSquare(var2);
               if (this.getContainer() != nullptr) {
                  this.getContainer().setDirty(true);
                  this.getContainer().setDrawDirty(true);
               }

               var3.chunk.recalcHashCodeObjects();
               this.setWorldItem(nullptr);
            } else if (this.getContainer() != nullptr) {
               this.getContainer().addItem(var1);
               this.getContainer().Remove(this);
            }

            this.setWet(false);
            IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
            LuaEventManager.triggerEvent("OnContainerUpdate");
         }
      }

      if (!GameClient.bClient
         && !this.rainFactorZero
         && this.getWorldItem() != nullptr
         && this.canStoreWater()
         && this.hasReplaceType("WaterSource")
         && RainManager.isRaining()) {
    IsoWorldInventoryObject var4 = this.getWorldItem();
    IsoGridSquare var5 = var4.getSquare();
         if (var5 != nullptr && var5.isOutside()) {
    InventoryItem var6 = InventoryItemFactory.CreateItem(this.getReplaceType("WaterSource"));
            if (var6 == nullptr) {
               this.rainFactorZero = true;
               return;
            }

            var6.setCondition(this.getCondition());
            if (dynamic_cast<DrainableComboItem*>(var6) != nullptr && var6.canStoreWater()) {
               if (((DrainableComboItem)var6).getRainFactor() == 0.0F) {
                  this.rainFactorZero = true;
                  return;
               }

               ((DrainableComboItem)var6).setUsedDelta(0.0F);
               var4.swapItem(var6);
            }
         }
      }
   }

    bool finishupdate() {
      return !GameClient.bClient
            && !this.rainFactorZero
            && this.canStoreWater()
            && this.hasReplaceType("WaterSource")
            && this.getWorldItem() != nullptr
            && this.getWorldItem().getObjectIndex() != -1
         ? false
         : !this.isWet();
   }

    void updateSound(BaseSoundEmitter var1) {
   }

    std::string getFullType() {
      assert this.fullType != nullptr && this.fullType == this.module + "." + this.type);

      return this.fullType;
   }

    void save(ByteBuffer var1, bool var2) {
      var2 = false;
      if (GameWindow.DEBUG_SAVE) {
         DebugLog.log(this.getFullType());
      }

      var1.putShort(this.registry_id);
      var1.put((byte)this.getSaveType());
      var1.putInt(this.id);
    BitHeaderWrite var3 = BitHeader.allocWrite(HeaderSize.uint8_t, var1);
      if (this.uses != 1) {
         var3.addFlags(1);
         if (this.uses > 32767) {
            var1.putShort((short)32767);
         } else {
            var1.putShort((short)this.uses);
         }
      }

      if (this.IsDrainable() && ((DrainableComboItem)this).getUsedDelta() < 1.0F) {
         var3.addFlags(2);
    float var4 = ((DrainableComboItem)this).getUsedDelta();
    uint8_t var5 = (byte)((byte)(var4 * 255.0F) + -128);
         var1.put(var5);
      }

      if (this.Condition != this.ConditionMax) {
         var3.addFlags(4);
         var1.put((byte)this.getCondition());
      }

      if (this.visual != nullptr) {
         var3.addFlags(8);
         this.visual.save(var1);
      }

      if (this.isCustomColor() && (this.col.r != 1.0F || this.col.g != 1.0F || this.col.b != 1.0F || this.col.a != 1.0F)) {
         var3.addFlags(16);
         var1.put(Bits.packFloatUnitToByte(this.getColor().r));
         var1.put(Bits.packFloatUnitToByte(this.getColor().g));
         var1.put(Bits.packFloatUnitToByte(this.getColor().b));
         var1.put(Bits.packFloatUnitToByte(this.getColor().a));
      }

      if (this.itemCapacity != -1.0F) {
         var3.addFlags(32);
         var1.putFloat(this.itemCapacity);
      }

    BitHeaderWrite var7 = BitHeader.allocWrite(HeaderSize.int, var1);
      if (this.table != nullptr && !this.table.empty()) {
         var7.addFlags(1);
         this.table.save(var1);
      }

      if (this.isActivated()) {
         var7.addFlags(2);
      }

      if (this.haveBeenRepaired != 1) {
         var7.addFlags(4);
         var1.putShort((short)this.getHaveBeenRepaired());
      }

      if (this.name != nullptr && !this.name == this.originalName)) {
         var7.addFlags(8);
         GameWindow.WriteString(var1, this.name);
      }

      if (this.byteData != nullptr) {
         var7.addFlags(16);
         this.byteData.rewind();
         var1.putInt(this.byteData.limit());
         var1.put(this.byteData);
         this.byteData.flip();
      }

      if (this.extraItems != nullptr && this.extraItems.size() > 0) {
         var7.addFlags(32);
         var1.putInt(this.extraItems.size());

         for (int var8 = 0; var8 < this.extraItems.size(); var8++) {
            var1.putShort(WorldDictionary.getItemRegistryID(this.extraItems.get(var8)));
         }
      }

      if (this.isCustomName()) {
         var7.addFlags(64);
      }

      if (this.isCustomWeight()) {
         var7.addFlags(128);
         var1.putFloat(this.isCustomWeight() ? this.getActualWeight() : -1.0F);
      }

      if (this.keyId != -1) {
         var7.addFlags(256);
         var1.putInt(this.getKeyId());
      }

      if (this.isTaintedWater()) {
         var7.addFlags(512);
      }

      if (this.remoteControlID != -1 || this.remoteRange != 0) {
         var7.addFlags(1024);
         var1.putInt(this.getRemoteControlID());
         var1.putInt(this.getRemoteRange());
      }

      if (this.colorRed != 1.0F || this.colorGreen != 1.0F || this.colorBlue != 1.0F) {
         var7.addFlags(2048);
         var1.put(Bits.packFloatUnitToByte(this.colorRed));
         var1.put(Bits.packFloatUnitToByte(this.colorGreen));
         var1.put(Bits.packFloatUnitToByte(this.colorBlue));
      }

      if (this.worker != nullptr) {
         var7.addFlags(4096);
         GameWindow.WriteString(var1, this.getWorker());
      }

      if (this.wetCooldown != -1.0F) {
         var7.addFlags(8192);
         var1.putFloat(this.wetCooldown);
      }

      if (this.isFavorite()) {
         var7.addFlags(16384);
      }

      if (this.stashMap != nullptr) {
         var7.addFlags(32768);
         GameWindow.WriteString(var1, this.stashMap);
      }

      if (this.isInfected()) {
         var7.addFlags(65536);
      }

      if (this.currentAmmoCount != 0) {
         var7.addFlags(131072);
         var1.putInt(this.currentAmmoCount);
      }

      if (this.attachedSlot != -1) {
         var7.addFlags(262144);
         var1.putInt(this.attachedSlot);
      }

      if (this.attachedSlotType != nullptr) {
         var7.addFlags(524288);
         GameWindow.WriteString(var1, this.attachedSlotType);
      }

      if (this.attachedToModel != nullptr) {
         var7.addFlags(1048576);
         GameWindow.WriteString(var1, this.attachedToModel);
      }

      if (this.maxCapacity != -1) {
         var7.addFlags(2097152);
         var1.putInt(this.maxCapacity);
      }

      if (this.isRecordedMedia()) {
         var7.addFlags(4194304);
         var1.putShort(this.recordedMediaIndex);
      }

      if (this.worldZRotation > -1) {
         var7.addFlags(8388608);
         var1.putInt(this.worldZRotation);
      }

      if (this.worldScale != 1.0F) {
         var7.addFlags(16777216);
         var1.putFloat(this.worldScale);
      }

      if (this.isInitialised) {
         var7.addFlags(33554432);
      }

      if (!var7 == 0)) {
         var3.addFlags(64);
         var7.write();
      } else {
         var1.position(var7.getStartPosition());
      }

      var3.write();
      var3.release();
      var7.release();
   }

    static InventoryItem loadItem(ByteBuffer var0, int var1) {
    return loadItem();
   }

    static InventoryItem loadItem(ByteBuffer var0, int var1, bool var2) {
    int var3 = var0.getInt();
      if (var3 <= 0) {
         throw IOException("InventoryItem.loadItem() invalid item data length: " + var3);
      } else {
    int var4 = var0.position();
    short var5 = var0.getShort();
    uint8_t var6 = -1;
         if (var1 >= 70) {
            var6 = var0.get();
            if (var6 < 0) {
               DebugLog.log("InventoryItem.loadItem() invalid item save-type " + var6 + ", itemtype: " + WorldDictionary.getItemTypeDebugString(var5));
    return nullptr;
            }
         }

    InventoryItem var7 = InventoryItemFactory.CreateItem(var5);
         if (var2 && var6 != -1 && var7 != nullptr && var7.getSaveType() != var6) {
            DebugLog.log("InventoryItem.loadItem() ignoring \"" + var7.getFullType() + "\" because type changed from " + var6 + " to " + var7.getSaveType());
            var7 = nullptr;
         }

         if (var7 != nullptr) {
            try {
               var7.load(var0, var1);
            } catch (Exception var9) {
               ExceptionLogger.logException(var9);
               var7 = nullptr;
            }
         }

         if (var7 != nullptr) {
            if (var3 != -1 && var0.position() != var4 + var3) {
               var0.position(var4 + var3);
               DebugLog.log(
                  "InventoryItem.loadItem() data length not matching, resetting buffer position to '"
                     + (var4 + var3)
                     + "'. itemtype: "
                     + WorldDictionary.getItemTypeDebugString(var5)
               );
               if (Core.bDebug) {
                  throw IOException("InventoryItem.loadItem() read more data than save() wrote (" + WorldDictionary.getItemTypeDebugString(var5) + ")");
               }
            }

    return var7;
         } else {
            if (var0.position() >= var4 + var3) {
               if (var0.position() >= var4 + var3) {
                  var0.position(var4 + var3);
                  DebugLog.log(
                     "InventoryItem.loadItem() item == nullptr, resetting buffer position to '"
                        + (var4 + var3)
                        + "'. itemtype: "
                        + WorldDictionary.getItemTypeDebugString(var5)
                  );
               }
            } else {
               while (var0.position() < var4 + var3) {
                  var0.get();
               }

               DebugLog.log("InventoryItem.loadItem() item == nullptr, skipped bytes. itemtype: " + WorldDictionary.getItemTypeDebugString(var5));
            }

    return nullptr;
         }
      }
   }

    void load(ByteBuffer var1, int var2) {
      this.id = var1.getInt();
    BitHeaderRead var3 = BitHeader.allocRead(HeaderSize.uint8_t, var1);
      this.uses = 1;
      if (this.IsDrainable()) {
         ((DrainableComboItem)this).setUsedDelta(1.0F);
      }

      this.Condition = this.ConditionMax;
      this.customColor = false;
      this.col = Color.white;
      this.itemCapacity = -1.0F;
      this.activated = false;
      this.haveBeenRepaired = 1;
      this.customName = false;
      this.customWeight = false;
      this.keyId = -1;
      this.taintedWater = false;
      this.remoteControlID = -1;
      this.remoteRange = 0;
      this.colorRed = this.colorGreen = this.colorBlue = 1.0F;
      this.worker = nullptr;
      this.wetCooldown = -1.0F;
      this.favorite = false;
      this.stashMap = nullptr;
      this.zombieInfected = false;
      this.currentAmmoCount = 0;
      this.attachedSlot = -1;
      this.attachedSlotType = nullptr;
      this.attachedToModel = nullptr;
      this.maxCapacity = -1;
      this.recordedMediaIndex = -1;
      this.worldZRotation = -1;
      this.worldScale = 1.0F;
      this.isInitialised = false;
      if (!var3 == 0)) {
         if (var3.hasFlags(1)) {
            this.uses = var1.getShort();
         }

         if (var3.hasFlags(2)) {
    uint8_t var4 = var1.get();
    float var5 = PZMath.clamp((var4 - -128) / 255.0F, 0.0F, 1.0F);
            ((DrainableComboItem)this).setUsedDelta(var5);
         }

         if (var3.hasFlags(4)) {
            this.setCondition(var1.get(), false);
         }

         if (var3.hasFlags(8)) {
            this.visual = std::make_unique<ItemVisual>();
            this.visual.load(var1, var2);
         }

         if (var3.hasFlags(16)) {
    float var9 = Bits.unpackByteToFloatUnit(var1.get());
    float var11 = Bits.unpackByteToFloatUnit(var1.get());
    float var6 = Bits.unpackByteToFloatUnit(var1.get());
    float var7 = Bits.unpackByteToFloatUnit(var1.get());
            this.setColor(std::make_shared<Color>(var9, var11, var6, var7));
         }

         if (var3.hasFlags(32)) {
            this.itemCapacity = var1.getFloat();
         }

         if (var3.hasFlags(64)) {
    BitHeaderRead var10 = BitHeader.allocRead(HeaderSize.int, var1);
            if (var10.hasFlags(1)) {
               if (this.table == nullptr) {
                  this.table = LuaManager.platform.newTable();
               }

               this.table.load(var1, var2);
            }

            this.activated = var10.hasFlags(2);
            if (var10.hasFlags(4)) {
               this.setHaveBeenRepaired(var1.getShort());
            }

            if (var10.hasFlags(8)) {
               this.name = GameWindow.ReadString(var1);
            }

            if (var10.hasFlags(16)) {
    int var12 = var1.getInt();
               this.byteData = ByteBuffer.allocate(var12);

               for (int var17 = 0; var17 < var12; var17++) {
                  this.byteData.put(var1.get());
               }

               this.byteData.flip();
            }

            if (var10.hasFlags(32)) {
    int var13 = var1.getInt();
               if (var13 > 0) {
                  this.extraItems = std::make_unique<std::vector<>>();

                  for (int var18 = 0; var18 < var13; var18++) {
    short var20 = var1.getShort();
    std::string var8 = WorldDictionary.getItemTypeFromID(var20);
                     this.extraItems.push_back(var8);
                  }
               }
            }

            this.setCustomName(var10.hasFlags(64));
            if (var10.hasFlags(128)) {
    float var14 = var1.getFloat();
               if (var14 >= 0.0F) {
                  this.setActualWeight(var14);
                  this.setWeight(var14);
                  this.setCustomWeight(true);
               }
            }

            if (var10.hasFlags(256)) {
               this.setKeyId(var1.getInt());
            }

            this.setTaintedWater(var10.hasFlags(512));
            if (var10.hasFlags(1024)) {
               this.setRemoteControlID(var1.getInt());
               this.setRemoteRange(var1.getInt());
            }

            if (var10.hasFlags(2048)) {
    float var15 = Bits.unpackByteToFloatUnit(var1.get());
    float var19 = Bits.unpackByteToFloatUnit(var1.get());
    float var21 = Bits.unpackByteToFloatUnit(var1.get());
               this.setColorRed(var15);
               this.setColorGreen(var19);
               this.setColorBlue(var21);
               this.setColor(std::make_shared<Color>(this.colorRed, this.colorGreen, this.colorBlue));
            }

            if (var10.hasFlags(4096)) {
               this.setWorker(GameWindow.ReadString(var1));
            }

            if (var10.hasFlags(8192)) {
               this.setWetCooldown(var1.getFloat());
            }

            this.setFavorite(var10.hasFlags(16384));
            if (var10.hasFlags(32768)) {
               this.stashMap = GameWindow.ReadString(var1);
            }

            this.setInfected(var10.hasFlags(65536));
            if (var10.hasFlags(131072)) {
               this.setCurrentAmmoCount(var1.getInt());
            }

            if (var10.hasFlags(262144)) {
               this.attachedSlot = var1.getInt();
            }

            if (var10.hasFlags(524288)) {
               if (var2 < 179) {
    short var16 = var1.getShort();
                  this.attachedSlotType = nullptr;
               } else {
                  this.attachedSlotType = GameWindow.ReadString(var1);
               }
            }

            if (var10.hasFlags(1048576)) {
               this.attachedToModel = GameWindow.ReadString(var1);
            }

            if (var10.hasFlags(2097152)) {
               this.maxCapacity = var1.getInt();
            }

            if (var10.hasFlags(4194304)) {
               this.setRecordedMediaIndex(var1.getShort());
            }

            if (var10.hasFlags(8388608)) {
               this.setWorldZRotation(var1.getInt());
            }

            if (var10.hasFlags(16777216)) {
               this.worldScale = var1.getFloat();
            }

            this.setInitialised(var10.hasFlags(33554432));
            var10.release();
         }
      }

      var3.release();
   }

    bool IsFood() {
    return false;
   }

    bool IsWeapon() {
    return false;
   }

    bool IsDrainable() {
    return false;
   }

    bool IsLiterature() {
    return false;
   }

    bool IsClothing() {
    return false;
   }

    bool IsInventoryContainer() {
    return false;
   }

    bool IsMap() {
    return false;
   }

    static InventoryItem LoadFromFile(DataInputStream var0) {
      GameWindow.ReadString(var0);
    return nullptr;
   }

    ItemContainer getOutermostContainer() {
      if (this.container != nullptr && !"floor" == this.container.type)) {
    ItemContainer var1 = this.container;

         while (
            var1.getContainingItem() != nullptr
               && var1.getContainingItem().getContainer() != nullptr
               && !"floor" == var1.getContainingItem().getContainer().type)
         ) {
            var1 = var1.getContainingItem().getContainer();
         }

    return var1;
      } else {
    return nullptr;
      }
   }

    bool isInLocalPlayerInventory() {
      if (!GameClient.bClient) {
    return false;
      } else {
    ItemContainer var1 = this.getOutermostContainer();
         if (var1 == nullptr) {
    return false;
         } else {
            return var1.getParent() instanceof IsoPlayer ? ((IsoPlayer)var1.getParent()).isLocalPlayer() : false;
         }
      }
   }

    bool isInPlayerInventory() {
    ItemContainer var1 = this.getOutermostContainer();
    return var1 = = nullptr ? false : var1.getParent() instanceof IsoPlayer;
   }

    ItemReplacement getItemReplacementPrimaryHand() {
      return this.ScriptItem.replacePrimaryHand;
   }

    ItemReplacement getItemReplacementSecondHand() {
      return this.ScriptItem.replaceSecondHand;
   }

    ClothingItem getClothingItem() {
      if ("RightHand".equalsIgnoreCase(this.getAlternateModelName())) {
         return this.getItemReplacementPrimaryHand().clothingItem;
      } else {
         return "LeftHand".equalsIgnoreCase(this.getAlternateModelName())
            ? this.getItemReplacementSecondHand().clothingItem
            : this.ScriptItem.getClothingItemAsset();
      }
   }

    std::string getAlternateModelName() {
      if (this.getContainer() != nullptr && this.getContainer().getParent() instanceof IsoGameCharacter) {
    IsoGameCharacter var1 = (IsoGameCharacter)this.getContainer().getParent();
         if (var1.getPrimaryHandItem() == this && this.getItemReplacementPrimaryHand() != nullptr) {
            return "RightHand";
         }

         if (var1.getSecondaryHandItem() == this && this.getItemReplacementSecondHand() != nullptr) {
            return "LeftHand";
         }
      }

      return this.m_alternateModelName;
   }

    ItemVisual getVisual() {
    ClothingItem var1 = this.getClothingItem();
      if (var1 != nullptr && var1.isReady()) {
         if (this.visual == nullptr) {
            this.visual = std::make_unique<ItemVisual>();
            this.visual.setItemType(this.getFullType());
            this.visual.pickUninitializedValues(var1);
         }

         this.visual.setClothingItemName(var1.m_Name);
         this.visual.setAlternateModelName(this.getAlternateModelName());
         return this.visual;
      } else {
         this.visual = nullptr;
    return nullptr;
      }
   }

    bool allowRandomTint() {
    ClothingItem var1 = this.getClothingItem();
      return var1 != nullptr ? var1.m_AllowRandomTint : false;
   }

    void synchWithVisual() {
      if (dynamic_cast<Clothing*>(this) != nullptr || dynamic_cast<InventoryContainer*>(this) != nullptr) {
    ItemVisual var1 = this.getVisual();
         if (var1 != nullptr) {
            if (dynamic_cast<Clothing*>(this) != nullptr && this.getBloodClothingType() != nullptr) {
               BloodClothingType.calcTotalBloodLevel((Clothing)this);
            }

    ClothingItem var2 = this.getClothingItem();
            if (var2.m_AllowRandomTint) {
               this.setColor(std::make_shared<Color>(var1.m_Tint.r, var1.m_Tint.g, var1.m_Tint.b));
            } else {
               this.setColor(std::make_shared<Color>(this.getColorRed(), this.getColorGreen(), this.getColorBlue()));
            }

            if ((var2.m_BaseTextures.size() > 1 || var1.m_TextureChoice > -1) && this.getIconsForTexture() != nullptr) {
    std::string var3 = nullptr;
               if (var1.m_BaseTexture > -1 && this.getIconsForTexture().size() > var1.m_BaseTexture) {
                  var3 = this.getIconsForTexture().get(var1.m_BaseTexture);
               } else if (var1.m_TextureChoice > -1 && this.getIconsForTexture().size() > var1.m_TextureChoice) {
                  var3 = this.getIconsForTexture().get(var1.m_TextureChoice);
               }

               if (!StringUtils.isNullOrWhitespace(var3)) {
                  this.texture = Texture.trygetTexture("Item_" + var3);
                  if (this.texture == nullptr) {
                     this.texture = Texture.getSharedTexture("media/inventory/Question_On.png");
                  }
               }
            }
         }
      }
   }

    int getContainerX() {
      return this.containerX;
   }

    void setContainerX(int var1) {
      this.containerX = var1;
   }

    int getContainerY() {
      return this.containerY;
   }

    void setContainerY(int var1) {
      this.containerY = var1;
   }

    bool isDisappearOnUse() {
      return this.getScriptItem().isDisappearOnUse();
   }

    std::string getName() {
      if (this.isBroken()) {
         return Translator.getText("IGUI_ItemNaming", this.brokenString, this.name);
      } else if (this.isTaintedWater() && SandboxOptions.instance.EnableTaintedWaterText.getValue()) {
         return Translator.getText("IGUI_ItemNameTaintedWater", this.name);
      } else if (this.getRemoteControlID() != -1) {
         return Translator.getText("IGUI_ItemNameControllerLinked", this.name);
      } else {
         return this.getMechanicType() > 0
            ? Translator.getText("IGUI_ItemNameMechanicalType", this.name, Translator.getText("IGUI_VehicleType_" + this.getMechanicType()))
            : this.name;
      }
   }

    void setName(const std::string& var1) {
      if (var1.length() > 256) {
         var1 = var1.substr(0, Math.min(var1.length(), 256));
      }

      this.name = var1;
   }

    std::string getReplaceOnUse() {
      return this.replaceOnUse;
   }

    void setReplaceOnUse(const std::string& var1) {
      this.replaceOnUse = var1;
      this.replaceOnUseFullType = StringUtils.moduleDotType(this.getModule(), var1);
   }

    std::string getReplaceOnUseFullType() {
      return this.replaceOnUseFullType;
   }

    int getConditionMax() {
      return this.ConditionMax;
   }

    void setConditionMax(int var1) {
      this.ConditionMax = var1;
   }

    ItemContainer getRightClickContainer() {
      return this.rightClickContainer;
   }

    void setRightClickContainer(ItemContainer var1) {
      this.rightClickContainer = var1;
   }

    std::string getSwingAnim() {
      return this.getScriptItem().SwingAnim;
   }

    Texture getTexture() {
      return this.texture;
   }

    void setTexture(Texture var1) {
      this.texture = var1;
   }

    Texture getTexturerotten() {
      return this.texturerotten;
   }

    void setTexturerotten(Texture var1) {
      this.texturerotten = var1;
   }

    Texture getTextureCooked() {
      return this.textureCooked;
   }

    void setTextureCooked(Texture var1) {
      this.textureCooked = var1;
   }

    Texture getTextureBurnt() {
      return this.textureBurnt;
   }

    void setTextureBurnt(Texture var1) {
      this.textureBurnt = var1;
   }

    void setType(const std::string& var1) {
      this.type = var1;
      this.fullType = this.module + "." + var1;
   }

    int getCurrentUses() {
      return this.uses;
   }

    int getUses() {
    return 1;
   }

    void setUses(int var1) {
   }

    float getAge() {
      return this.Age;
   }

    void setAge(float var1) {
      this.Age = var1;
   }

    float getLastAged() {
      return this.LastAged;
   }

    void setLastAged(float var1) {
      this.LastAged = var1;
   }

    void updateAge() {
   }

    void setAutoAge() {
   }

    bool isIsCookable() {
      return this.IsCookable;
   }

    bool isCookable() {
      return this.IsCookable;
   }

    void setIsCookable(bool var1) {
      this.IsCookable = var1;
   }

    float getCookingTime() {
      return this.CookingTime;
   }

    void setCookingTime(float var1) {
      this.CookingTime = var1;
   }

    float getMinutesToCook() {
      return this.MinutesToCook;
   }

    void setMinutesToCook(float var1) {
      this.MinutesToCook = var1;
   }

    float getMinutesToBurn() {
      return this.MinutesToBurn;
   }

    void setMinutesToBurn(float var1) {
      this.MinutesToBurn = var1;
   }

    bool isCooked() {
      return this.Cooked;
   }

    void setCooked(bool var1) {
      this.Cooked = var1;
   }

    bool isBurnt() {
      return this.Burnt;
   }

    void setBurnt(bool var1) {
      this.Burnt = var1;
   }

    int getOffAge() {
      return this.OffAge;
   }

    void setOffAge(int var1) {
      this.OffAge = var1;
   }

    int getOffAgeMax() {
      return this.OffAgeMax;
   }

    void setOffAgeMax(int var1) {
      this.OffAgeMax = var1;
   }

    float getWeight() {
      return this.Weight;
   }

    void setWeight(float var1) {
      this.Weight = var1;
   }

    float getActualWeight() {
      return this.getDisplayName() == this.getFullType()) ? 0.0F : this.ActualWeight;
   }

    void setActualWeight(float var1) {
      this.ActualWeight = var1;
   }

    std::string getWorldTexture() {
      return this.WorldTexture;
   }

    void setWorldTexture(const std::string& var1) {
      this.WorldTexture = var1;
   }

    std::string getDescription() {
      return this.Description;
   }

    void setDescription(const std::string& var1) {
      this.Description = var1;
   }

    int getCondition() {
      return this.Condition;
   }

    void setCondition(int var1, bool var2) {
      var1 = Math.max(0, var1);
      if (this.Condition > 0 && var1 <= 0 && var2 && this.getBreakSound() != nullptr && !this.getBreakSound().empty() && IsoPlayer.getInstance() != nullptr) {
         IsoPlayer.getInstance().playSound(this.getBreakSound());
      }

      this.Condition = var1;
      this.setBroken(var1 <= 0);
   }

    void setCondition(int var1) {
      this.setCondition(var1, true);
   }

    std::string getOffString() {
      return this.OffString;
   }

    void setOffString(const std::string& var1) {
      this.OffString = var1;
   }

    std::string getCookedString() {
      return this.CookedString;
   }

    void setCookedString(const std::string& var1) {
      this.CookedString = var1;
   }

    std::string getUnCookedString() {
      return this.UnCookedString;
   }

    void setUnCookedString(const std::string& var1) {
      this.UnCookedString = var1;
   }

    std::string getBurntString() {
      return this.BurntString;
   }

    void setBurntString(const std::string& var1) {
      this.BurntString = var1;
   }

    std::string getModule() {
      return this.module;
   }

    void setModule(const std::string& var1) {
      this.module = var1;
      this.fullType = var1 + "." + this.type;
   }

    bool isAlwaysWelcomeGift() {
      return this.getScriptItem().isAlwaysWelcomeGift();
   }

    bool isCanBandage() {
      return this.getScriptItem().isCanBandage();
   }

    float getBoredomChange() {
      return this.boredomChange;
   }

    void setBoredomChange(float var1) {
      this.boredomChange = var1;
   }

    float getUnhappyChange() {
      return this.unhappyChange;
   }

    void setUnhappyChange(float var1) {
      this.unhappyChange = var1;
   }

    float getStressChange() {
      return this.stressChange;
   }

    void setStressChange(float var1) {
      this.stressChange = var1;
   }

   public std::vector<std::string> getTags() {
      return this.ScriptItem.getTags();
   }

    bool hasTag(const std::string& var1) {
    std::vector var2 = this.getTags();

      for (int var3 = 0; var3 < var2.size(); var3++) {
         if (((std::string)var2.get(var3)).equalsIgnoreCase(var1)) {
    return true;
         }
      }

    return false;
   }

   public std::vector<IsoObject> getTaken() {
      return this.Taken;
   }

    void setTaken(std::vector<IsoObject> var1) {
      this.Taken = var1;
   }

    IsoDirections getPlaceDir() {
      return this.placeDir;
   }

    void setPlaceDir(IsoDirections var1) {
      this.placeDir = var1;
   }

    IsoDirections getNewPlaceDir() {
      return this.newPlaceDir;
   }

    void setNewPlaceDir(IsoDirections var1) {
      this.newPlaceDir = var1;
   }

    void setReplaceOnUseOn(const std::string& var1) {
      this.ReplaceOnUseOn = var1;
   }

    std::string getReplaceOnUseOn() {
      return this.ReplaceOnUseOn;
   }

    std::string getReplaceOnUseOnString() {
    std::string var1 = this.getReplaceOnUseOn();
      if (var1.split("-")[0].trim().contains("WaterSource")) {
         var1 = var1.split("-")[1];
         if (!var1.contains(".")) {
            var1 = this.getModule() + "." + var1;
         }
      }

    return var1;
   }

    std::string getReplaceTypes() {
      return this.getScriptItem().getReplaceTypes();
   }

   public std::unordered_map<std::string, std::string> getReplaceTypesMap() {
      return this.getScriptItem().getReplaceTypesMap();
   }

    std::string getReplaceType(const std::string& var1) {
      return this.getScriptItem().getReplaceType(var1);
   }

    bool hasReplaceType(const std::string& var1) {
      return this.getScriptItem().hasReplaceType(var1);
   }

    void setIsWaterSource(bool var1) {
      this.IsWaterSource = var1;
   }

    bool isWaterSource() {
      return this.IsWaterSource;
   }

    bool CanStackNoTemp(InventoryItem var1) {
    return false;
   }

    void CopyModData(KahluaTable var1) {
      this.copyModData(var1);
   }

    void copyModData(KahluaTable var1) {
      if (this.table != nullptr) {
         this.table.wipe();
      }

      if (var1 != nullptr) {
         LuaManager.copyTable(this.getModData(), var1);
      }
   }

    int getCount() {
      return this.Count;
   }

    void setCount(int var1) {
      this.Count = var1;
   }

    bool isActivated() {
      return this.activated;
   }

    void setActivated(bool var1) {
      this.activated = var1;
      if (this.canEmitLight() && GameClient.bClient && this.getEquipParent() != nullptr) {
         if (this.getEquipParent().getPrimaryHandItem() == this) {
            this.getEquipParent().reportEvent("EventSetActivatedPrimary");
         } else if (this.getEquipParent().getSecondaryHandItem() == this) {
            this.getEquipParent().reportEvent("EventSetActivatedSecondary");
         }
      }
   }

    void setActivatedRemote(bool var1) {
      this.activated = var1;
   }

    void setCanBeActivated(bool var1) {
      this.canBeActivated = var1;
   }

    bool canBeActivated() {
      return this.canBeActivated;
   }

    void setLightStrength(float var1) {
      this.lightStrength = var1;
   }

    float getLightStrength() {
      return this.lightStrength;
   }

    bool isTorchCone() {
      return this.isTorchCone;
   }

    void setTorchCone(bool var1) {
      this.isTorchCone = var1;
   }

    float getTorchDot() {
      return this.getScriptItem().torchDot;
   }

    int getLightDistance() {
      return this.lightDistance;
   }

    void setLightDistance(int var1) {
      this.lightDistance = var1;
   }

    bool canEmitLight() {
      if (this.getLightStrength() <= 0.0F) {
    return false;
      } else {
    Drainable var1 = (Drainable)Type.tryCastTo(this, Drainable.class);
    return var1 = = nullptr || !(var1.getUsedDelta() <= 0.0F);
      }
   }

    bool isEmittingLight() {
      return !this.canEmitLight() ? false : !this.canBeActivated() || this.isActivated();
   }

    bool canStoreWater() {
      return this.CanStoreWater;
   }

    float getFatigueChange() {
      return this.fatigueChange;
   }

    void setFatigueChange(float var1) {
      this.fatigueChange = var1;
   }

    float getCurrentCondition() {
    float var1 = (float)this.Condition / this.ConditionMax;
      return float.valueOf(var1 * 100.0F);
   }

    void setColor(Color var1) {
      this.col = var1;
   }

    Color getColor() {
      return this.col;
   }

    ColorInfo getColorInfo() {
      return std::make_shared<ColorInfo>(this.col.getRedFloat(), this.col.getGreenFloat(), this.col.getBlueFloat(), this.col.getAlphaFloat());
   }

    bool isTwoHandWeapon() {
      return this.getScriptItem().TwoHandWeapon;
   }

    std::string getCustomMenuOption() {
      return this.customMenuOption;
   }

    void setCustomMenuOption(const std::string& var1) {
      this.customMenuOption = var1;
   }

    void setTooltip(const std::string& var1) {
      this.tooltip = var1;
   }

    std::string getTooltip() {
      return this.tooltip;
   }

    std::string getDisplayCategory() {
      return this.displayCategory;
   }

    void setDisplayCategory(const std::string& var1) {
      this.displayCategory = var1;
   }

    int getHaveBeenRepaired() {
      return this.haveBeenRepaired;
   }

    void setHaveBeenRepaired(int var1) {
      this.haveBeenRepaired = var1;
   }

    bool isBroken() {
      return this.broken;
   }

    void setBroken(bool var1) {
      this.broken = var1;
   }

    std::string getDisplayName() {
      return this.name;
   }

    bool isTrap() {
      return this.getScriptItem().Trap;
   }

    void addExtraItem(const std::string& var1) {
      if (this.extraItems == nullptr) {
         this.extraItems = std::make_unique<std::vector<>>();
      }

      this.extraItems.push_back(var1);
   }

    bool haveExtraItems() {
      return this.extraItems != nullptr;
   }

   public std::vector<std::string> getExtraItems() {
      return this.extraItems;
   }

    float getExtraItemsWeight() {
      if (!this.haveExtraItems()) {
         return 0.0F;
      } else {
    float var1 = 0.0F;

         for (int var2 = 0; var2 < this.extraItems.size(); var2++) {
    InventoryItem var3 = InventoryItemFactory.CreateItem(this.extraItems.get(var2));
            var1 += var3.getActualWeight();
         }

         return var1 * 0.6F;
      }
   }

    bool isCustomName() {
      return this.customName;
   }

    void setCustomName(bool var1) {
      this.customName = var1;
   }

    bool isFishingLure() {
      return this.getScriptItem().FishingLure;
   }

    void copyConditionModData(InventoryItem var1) {
      if (var1.hasModData()) {
    KahluaTableIterator var2 = var1.getModData().iterator();

         while (var2.advance()) {
            if (var2.getKey() instanceof std::string && ((std::string)var2.getKey()).startsWith("condition:")) {
               this.getModData().rawset(var2.getKey(), var2.getValue());
            }
         }
      }
   }

    void setConditionFromModData(InventoryItem var1) {
      if (var1.hasModData()) {
    void* var2 = var1.getModData().rawget("condition:" + this.getType());
         if (var2 != nullptr && dynamic_cast<double*>(var2) != nullptr) {
            this.setCondition((int)Math.round((double)var2 * this.getConditionMax()));
         }
      }
   }

    std::string getBreakSound() {
      return this.breakSound;
   }

    void setBreakSound(const std::string& var1) {
      this.breakSound = var1;
   }

    std::string getPlaceOneSound() {
      return this.getScriptItem().getPlaceOneSound();
   }

    std::string getPlaceMultipleSound() {
      return this.getScriptItem().getPlaceMultipleSound();
   }

    std::string getSoundByID(const std::string& var1) {
      return this.getScriptItem().getSoundByID(var1);
   }

    void setBeingFilled(bool var1) {
      this.beingFilled = var1;
   }

    bool isBeingFilled() {
      return this.beingFilled;
   }

    std::string getFillFromDispenserSound() {
      return this.getScriptItem().getFillFromDispenserSound();
   }

    std::string getFillFromTapSound() {
      return this.getScriptItem().getFillFromTapSound();
   }

    bool isAlcoholic() {
      return this.alcoholic;
   }

    void setAlcoholic(bool var1) {
      this.alcoholic = var1;
   }

    float getAlcoholPower() {
      return this.alcoholPower;
   }

    void setAlcoholPower(float var1) {
      this.alcoholPower = var1;
   }

    float getBandagePower() {
      return this.bandagePower;
   }

    void setBandagePower(float var1) {
      this.bandagePower = var1;
   }

    float getReduceInfectionPower() {
      return this.ReduceInfectionPower;
   }

    void setReduceInfectionPower(float var1) {
      this.ReduceInfectionPower = var1;
   }

    void saveWithSize(ByteBuffer var1, bool var2) {
    int var3 = var1.position();
      var1.putInt(0);
    int var4 = var1.position();
      this.save(var1, var2);
    int var5 = var1.position();
      var1.position(var3);
      var1.putInt(var5 - var4);
      var1.position(var5);
   }

    bool isCustomWeight() {
      return this.customWeight;
   }

    void setCustomWeight(bool var1) {
      this.customWeight = var1;
   }

    float getContentsWeight() {
      if (!StringUtils.isNullOrEmpty(this.getAmmoType())) {
    Item var1 = ScriptManager.instance.FindItem(this.getAmmoType());
         if (var1 != nullptr) {
            return var1.getActualWeight() * this.getCurrentAmmoCount();
         }
      }

      return 0.0F;
   }

    float getHotbarEquippedWeight() {
      return (this.getActualWeight() + this.getContentsWeight()) * 0.7F;
   }

    float getEquippedWeight() {
      return (this.getActualWeight() + this.getContentsWeight()) * 0.3F;
   }

    float getUnequippedWeight() {
      return this.getActualWeight() + this.getContentsWeight();
   }

    bool isEquipped() {
      return this.getContainer() != nullptr && this.getContainer().getParent() instanceof IsoGameCharacter
         ? ((IsoGameCharacter)this.getContainer().getParent()).isEquipped(this)
         : false;
   }

    int getKeyId() {
      return this.keyId;
   }

    void setKeyId(int var1) {
      this.keyId = var1;
   }

    bool isTaintedWater() {
      return this.taintedWater;
   }

    void setTaintedWater(bool var1) {
      this.taintedWater = var1;
   }

    bool isRemoteController() {
      return this.remoteController;
   }

    void setRemoteController(bool var1) {
      this.remoteController = var1;
   }

    bool canBeRemote() {
      return this.canBeRemote;
   }

    void setCanBeRemote(bool var1) {
      this.canBeRemote = var1;
   }

    int getRemoteControlID() {
      return this.remoteControlID;
   }

    void setRemoteControlID(int var1) {
      this.remoteControlID = var1;
   }

    int getRemoteRange() {
      return this.remoteRange;
   }

    void setRemoteRange(int var1) {
      this.remoteRange = var1;
   }

    std::string getExplosionSound() {
      return this.explosionSound;
   }

    void setExplosionSound(const std::string& var1) {
      this.explosionSound = var1;
   }

    std::string getCountDownSound() {
      return this.countDownSound;
   }

    void setCountDownSound(const std::string& var1) {
      this.countDownSound = var1;
   }

    float getColorRed() {
      return this.colorRed;
   }

    void setColorRed(float var1) {
      this.colorRed = var1;
   }

    float getColorGreen() {
      return this.colorGreen;
   }

    void setColorGreen(float var1) {
      this.colorGreen = var1;
   }

    float getColorBlue() {
      return this.colorBlue;
   }

    void setColorBlue(float var1) {
      this.colorBlue = var1;
   }

    std::string getEvolvedRecipeName() {
      return this.evolvedRecipeName;
   }

    void setEvolvedRecipeName(const std::string& var1) {
      this.evolvedRecipeName = var1;
   }

    float getMetalValue() {
      return this.metalValue;
   }

    void setMetalValue(float var1) {
      this.metalValue = var1;
   }

    float getItemHeat() {
      return this.itemHeat;
   }

    void setItemHeat(float var1) {
      if (var1 > 2.0F) {
         var1 = 2.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.itemHeat = var1;
   }

    float getInvHeat() {
      return 1.0F - this.itemHeat;
   }

    float getMeltingTime() {
      return this.meltingTime;
   }

    void setMeltingTime(float var1) {
      if (var1 > 100.0F) {
         var1 = 100.0F;
      }

      if (var1 < 0.0F) {
         var1 = 0.0F;
      }

      this.meltingTime = var1;
   }

    std::string getWorker() {
      return this.worker;
   }

    void setWorker(const std::string& var1) {
      this.worker = var1;
   }

    int getID() {
      return this.id;
   }

    void setID(int var1) {
      this.id = var1;
   }

    bool isWet() {
      return this.isWet;
   }

    void setWet(bool var1) {
      this.isWet = var1;
   }

    float getWetCooldown() {
      return this.wetCooldown;
   }

    void setWetCooldown(float var1) {
      this.wetCooldown = var1;
   }

    std::string getItemWhenDry() {
      return this.itemWhenDry;
   }

    void setItemWhenDry(const std::string& var1) {
      this.itemWhenDry = var1;
   }

    bool isFavorite() {
      return this.favorite;
   }

    void setFavorite(bool var1) {
      this.favorite = var1;
   }

   public std::vector<std::string> getRequireInHandOrInventory() {
      return this.requireInHandOrInventory;
   }

    void setRequireInHandOrInventory(std::vector<std::string> var1) {
      this.requireInHandOrInventory = var1;
   }

    bool isCustomColor() {
      return this.customColor;
   }

    void setCustomColor(bool var1) {
      this.customColor = var1;
   }

    void doBuildingStash() {
      if (this.stashMap != nullptr) {
         if (GameClient.bClient) {
            GameClient.sendBuildingStashToDo(this.stashMap);
         } else {
            StashSystem.prepareBuildingStash(this.stashMap);
         }
      }
   }

    void setStashMap(const std::string& var1) {
      this.stashMap = var1;
   }

    int getMechanicType() {
      return this.getScriptItem().vehicleType;
   }

    float getItemCapacity() {
      return this.itemCapacity;
   }

    void setItemCapacity(float var1) {
      this.itemCapacity = var1;
   }

    int getMaxCapacity() {
      return this.maxCapacity;
   }

    void setMaxCapacity(int var1) {
      this.maxCapacity = var1;
   }

    bool isConditionAffectsCapacity() {
      return this.ScriptItem != nullptr && this.ScriptItem.isConditionAffectsCapacity();
   }

    float getBrakeForce() {
      return this.brakeForce;
   }

    void setBrakeForce(float var1) {
      this.brakeForce = var1;
   }

    int getChanceToSpawnDamaged() {
      return this.chanceToSpawnDamaged;
   }

    void setChanceToSpawnDamaged(int var1) {
      this.chanceToSpawnDamaged = var1;
   }

    float getConditionLowerNormal() {
      return this.conditionLowerNormal;
   }

    void setConditionLowerNormal(float var1) {
      this.conditionLowerNormal = var1;
   }

    float getConditionLowerOffroad() {
      return this.conditionLowerOffroad;
   }

    void setConditionLowerOffroad(float var1) {
      this.conditionLowerOffroad = var1;
   }

    float getWheelFriction() {
      return this.wheelFriction;
   }

    void setWheelFriction(float var1) {
      this.wheelFriction = var1;
   }

    float getSuspensionDamping() {
      return this.suspensionDamping;
   }

    void setSuspensionDamping(float var1) {
      this.suspensionDamping = var1;
   }

    float getSuspensionCompression() {
      return this.suspensionCompression;
   }

    void setSuspensionCompression(float var1) {
      this.suspensionCompression = var1;
   }

    void setInfected(bool var1) {
      this.zombieInfected = var1;
   }

    bool isInfected() {
      return this.zombieInfected;
   }

    float getEngineLoudness() {
      return this.engineLoudness;
   }

    void setEngineLoudness(float var1) {
      this.engineLoudness = var1;
   }

    std::string getStaticModel() {
      return this.getScriptItem().getStaticModel();
   }

   public std::vector<std::string> getIconsForTexture() {
      return this.iconsForTexture;
   }

    void setIconsForTexture(std::vector<std::string> var1) {
      this.iconsForTexture = var1;
   }

    float getScore(SurvivorDesc var1) {
      return 0.0F;
   }

    IsoGameCharacter getPreviousOwner() {
      return this.previousOwner;
   }

    void setPreviousOwner(IsoGameCharacter var1) {
      this.previousOwner = var1;
   }

    Item getScriptItem() {
      return this.ScriptItem;
   }

    void setScriptItem(Item var1) {
      this.ScriptItem = var1;
   }

    ItemType getCat() {
      return this.cat;
   }

    void setCat(ItemType var1) {
      this.cat = var1;
   }

    ItemContainer getContainer() {
      return this.container;
   }

    void setContainer(ItemContainer var1) {
      this.container = var1;
   }

   public std::vector<BloodClothingType> getBloodClothingType() {
      return this.bloodClothingType;
   }

    void setBloodClothingType(std::vector<BloodClothingType> var1) {
      this.bloodClothingType = var1;
   }

    void setBlood(BloodBodyPartType var1, float var2) {
    ItemVisual var3 = this.getVisual();
      if (var3 != nullptr) {
         var3.setBlood(var1, var2);
      }
   }

    float getBlood(BloodBodyPartType var1) {
    ItemVisual var2 = this.getVisual();
      return var2 != nullptr ? var2.getBlood(var1) : 0.0F;
   }

    void setDirt(BloodBodyPartType var1, float var2) {
    ItemVisual var3 = this.getVisual();
      if (var3 != nullptr) {
         var3.setDirt(var1, var2);
      }
   }

    float getDirt(BloodBodyPartType var1) {
    ItemVisual var2 = this.getVisual();
      return var2 != nullptr ? var2.getDirt(var1) : 0.0F;
   }

    std::string getClothingItemName() {
      return this.getScriptItem().ClothingItem;
   }

    int getStashChance() {
      return this.stashChance;
   }

    void setStashChance(int var1) {
      this.stashChance = var1;
   }

    std::string getEatType() {
      return this.getScriptItem().eatType;
   }

    bool isUseWorldItem() {
      return this.getScriptItem().UseWorldItem;
   }

    bool isHairDye() {
      return this.getScriptItem().hairDye;
   }

    std::string getAmmoType() {
      return this.ammoType;
   }

    void setAmmoType(const std::string& var1) {
      this.ammoType = var1;
   }

    int getMaxAmmo() {
      return this.maxAmmo;
   }

    void setMaxAmmo(int var1) {
      this.maxAmmo = var1;
   }

    int getCurrentAmmoCount() {
      return this.currentAmmoCount;
   }

    void setCurrentAmmoCount(int var1) {
      this.currentAmmoCount = var1;
   }

    std::string getGunType() {
      return this.gunType;
   }

    void setGunType(const std::string& var1) {
      this.gunType = var1;
   }

    bool hasBlood() {
      if (dynamic_cast<Clothing*>(this) != nullptr) {
         if (this.getBloodClothingType() == nullptr || this.getBloodClothingType().empty()) {
    return false;
         }

    std::vector var1 = BloodClothingType.getCoveredParts(this.getBloodClothingType());
         if (var1 == nullptr) {
    return false;
         }

         for (int var2 = 0; var2 < var1.size(); var2++) {
            if (this.getBlood((BloodBodyPartType)var1.get(var2)) > 0.0F) {
    return true;
            }
         }
      } else {
         if (dynamic_cast<HandWeapon*>(this) != nullptr) {
            return ((HandWeapon)this).getBloodLevel() > 0.0F;
         }

         if (dynamic_cast<InventoryContainer*>(this) != nullptr) {
            return ((InventoryContainer)this).getBloodLevel() > 0.0F;
         }
      }

    return false;
   }

    bool hasDirt() {
      if (dynamic_cast<Clothing*>(this) != nullptr) {
         if (this.getBloodClothingType() == nullptr || this.getBloodClothingType().empty()) {
    return false;
         }

    std::vector var1 = BloodClothingType.getCoveredParts(this.getBloodClothingType());
         if (var1 == nullptr) {
    return false;
         }

         for (int var2 = 0; var2 < var1.size(); var2++) {
            if (this.getDirt((BloodBodyPartType)var1.get(var2)) > 0.0F) {
    return true;
            }
         }
      }

    return false;
   }

    std::string getAttachmentType() {
      return this.attachmentType;
   }

    void setAttachmentType(const std::string& var1) {
      this.attachmentType = var1;
   }

    int getAttachedSlot() {
      return this.attachedSlot;
   }

    void setAttachedSlot(int var1) {
      this.attachedSlot = var1;
   }

   public std::vector<std::string> getAttachmentsProvided() {
      return this.attachmentsProvided;
   }

    void setAttachmentsProvided(std::vector<std::string> var1) {
      this.attachmentsProvided = var1;
   }

    std::string getAttachedSlotType() {
      return this.attachedSlotType;
   }

    void setAttachedSlotType(const std::string& var1) {
      this.attachedSlotType = var1;
   }

    std::string getAttachmentReplacement() {
      return this.attachmentReplacement;
   }

    void setAttachmentReplacement(const std::string& var1) {
      this.attachmentReplacement = var1;
   }

    std::string getAttachedToModel() {
      return this.attachedToModel;
   }

    void setAttachedToModel(const std::string& var1) {
      this.attachedToModel = var1;
   }

    std::string getFabricType() {
      return this.getScriptItem().fabricType;
   }

    std::string getStringItemType() {
    Item var1 = ScriptManager.instance.FindItem(this.getFullType());
      if (var1 != nullptr && var1.getType() != nullptr) {
         if (var1.getType() == zombie.scripting.objects.Item.Type.Food) {
            return var1.CannedFood ? "CannedFood" : "Food";
         } else if ("Ammo" == var1.getDisplayCategory())) {
            return "Ammo";
         } else if (var1.getType() == zombie.scripting.objects.Item.Type.Weapon && !var1.isRanged()) {
            return "MeleeWeapon";
         } else if (var1.getType() != zombie.scripting.objects.Item.Type.WeaponPart
            && (var1.getType() != zombie.scripting.objects.Item.Type.Weapon || !var1.isRanged())
            && (var1.getType() != zombie.scripting.objects.Item.Type.Normal || StringUtils.isNullOrEmpty(var1.getAmmoType()))) {
            if (var1.getType() == zombie.scripting.objects.Item.Type.Literature) {
               return "Literature";
            } else if (var1.Medical) {
               return "Medical";
            } else if (var1.SurvivalGear) {
               return "SurvivalGear";
            } else {
               return var1.MechanicsItem ? "Mechanic" : "Other";
            }
         } else {
            return "RangedWeapon";
         }
      } else {
         return "Other";
      }
   }

    bool isProtectFromRainWhileEquipped() {
      return this.getScriptItem().ProtectFromRainWhenEquipped;
   }

    bool isEquippedNoSprint() {
      return this.getScriptItem().equippedNoSprint;
   }

    std::string getBodyLocation() {
      return this.getScriptItem().BodyLocation;
   }

    std::string getMakeUpType() {
      return this.getScriptItem().makeUpType;
   }

    bool isHidden() {
      return this.getScriptItem().isHidden();
   }

    std::string getConsolidateOption() {
      return this.getScriptItem().consolidateOption;
   }

   public std::vector<std::string> getClothingItemExtra() {
      return this.getScriptItem().clothingItemExtra;
   }

   public std::vector<std::string> getClothingItemExtraOption() {
      return this.getScriptItem().clothingItemExtraOption;
   }

    std::string getWorldStaticItem() {
      return this.getModData().rawget("Flatpack") == "true" ? "Flatpack" : this.getScriptItem().worldStaticModel;
   }

    void setRegistry_id(Item var1) {
      if (var1.getFullName() == this.getFullType())) {
         this.registry_id = var1.getRegistry_id();
      } else if (Core.bDebug) {
         WorldDictionary.DebugPrintItem(var1);
         throw RuntimeException("These types should always match");
      }
   }

    short getRegistry_id() {
      return this.registry_id;
   }

    std::string getModID() {
      return this.ScriptItem != nullptr && this.ScriptItem.getModID() != nullptr ? this.ScriptItem.getModID() : WorldDictionary.getItemModID(this.registry_id);
   }

    std::string getModName() {
      return WorldDictionary.getModNameFromID(this.getModID());
   }

    bool isVanilla() {
      if (this.getModID() != nullptr) {
         return this.getModID() == "pz-vanilla");
      } else if (Core.bDebug) {
         WorldDictionary.DebugPrintItem(this);
         throw RuntimeException("Item has no modID?");
      } else {
    return true;
      }
   }

    short getRecordedMediaIndex() {
      return this.recordedMediaIndex;
   }

    void setRecordedMediaIndex(short var1) {
      this.recordedMediaIndex = var1;
      if (this.recordedMediaIndex >= 0) {
    MediaData var2 = ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.recordedMediaIndex);
         this.mediaType = -1;
         if (var2 != nullptr) {
            this.name = var2.getTranslatedItemDisplayName();
            this.mediaType = var2.getMediaType();
         } else {
            this.recordedMediaIndex = -1;
         }
      } else {
         this.mediaType = -1;
         this.name = this.getScriptItem().getDisplayName();
      }
   }

    void setRecordedMediaIndexInteger(int var1) {
      this.setRecordedMediaIndex((short)var1);
   }

    bool isRecordedMedia() {
      return this.recordedMediaIndex >= 0;
   }

    MediaData getMediaData() {
      return this.isRecordedMedia() ? ZomboidRadio.getInstance().getRecordedMedia().getMediaDataFromIndex(this.recordedMediaIndex) : nullptr;
   }

    uint8_t getMediaType() {
      return this.mediaType;
   }

    void setMediaType(uint8_t var1) {
      this.mediaType = var1;
   }

    void setRecordedMediaData(MediaData var1) {
      if (var1 != nullptr && var1.getIndex() >= 0) {
         this.setRecordedMediaIndex(var1.getIndex());
      }
   }

    void setWorldZRotation(int var1) {
      this.worldZRotation = var1;
   }

    void setWorldScale(float var1) {
      this.worldScale = var1;
   }

    std::string getLuaCreate() {
      return this.getScriptItem().getLuaCreate();
   }

    bool isInitialised() {
      return this.isInitialised;
   }

    void setInitialised(bool var1) {
      this.isInitialised = var1;
   }

    void initialiseItem() {
      this.setInitialised(true);
      if (this.getLuaCreate() != nullptr) {
    void* var1 = LuaManager.getFunctionObject(this.getLuaCreate());
         if (var1 != nullptr) {
            LuaManager.caller.protectedCallVoid(LuaManager.thread, var1, this);
         }
      }
   }

    std::string getSoundParameter(const std::string& var1) {
      return this.getScriptItem().getSoundParameter(var1);
   }
}
} // namespace inventory
} // namespace zombie
