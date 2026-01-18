#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/GameTime.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/interfaces/IUpdater.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/InventoryItemFactory.h"
#include "zombie/inventory/ItemContainer.h"
#include "zombie/inventory/ItemUser.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/objects/RainManager.h"
#include "zombie/network/GameServer.h"
#include "zombie/scripting/ScriptManager.h"
#include "zombie/scripting/objects/Item.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace inventory {
namespace types {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DrainableComboItem : public InventoryItem {
public:
 bool bUseWhileEquiped = true;
 bool bUseWhileUnequiped = false;
 int ticksPerEquipUse = 30;
 float useDelta = 0.03125F;
 float delta = 1.0F;
 float ticks = 0.0F;
 std::string ReplaceOnDeplete = nullptr;
 std::string ReplaceOnDepleteFullType = nullptr;
 public List<String> ReplaceOnCooked = nullptr;
 std::string OnCooked = nullptr;
 float rainFactor = 0.0F;
 bool canConsolidate = true;
 float WeightEmpty = 0.0F;
 static const float MIN_HEAT = 0.2F;
 static const float MAX_HEAT = 3.0F;
 float Heat = 1.0F;
 int LastCookMinute = 0;

 public DrainableComboItem(const std::string& module, const std::string& name, const std::string& itemType, const std::string& texName) {
 super(module, name, itemType, texName);
 }

 public DrainableComboItem(const std::string& module, const std::string& name, const std::string& itemType, Item item) {
 super(module, name, itemType, item);
 }

 bool IsDrainable() {
 return true;
 }

 int getSaveType() {
 return Item.Type.Drainable.ordinal();
 }

 bool CanStack(InventoryItem item) {
 return false;
 }

 float getUsedDelta() {
 return this->delta;
 }

 int getDrainableUsesInt() {
 return (int)Math.floor((this->getUsedDelta() + 1.0E-4) / this->getUseDelta());
 }

 float getDrainableUsesFloat() {
 return this->getUsedDelta() / this->getUseDelta();
 }

 void render() {
 }

 void renderlast() {
 }

 void setUsedDelta(float usedDelta) {
 this->delta = PZMath.clamp(usedDelta, 0.0F, 1.0F);
 this->updateWeight();
 }

 bool shouldUpdateInWorld() {
 if (!GameServer.bServer && this->Heat != 1.0F) {
 return true;
 } else if (this->canStoreWater() && this->isWaterSource() && this->getUsedDelta() < 1.0F) {
 IsoGridSquare square = this->getWorldItem().getSquare();
 return square != nullptr && square.isOutside();
 } else {
 return false;
 }
 }

 void update() {
 ItemContainer container = this->getOutermostContainer();
 if (container != nullptr) {
 float float0 = container.getTemprature();
 if (this->Heat > float0) {
 this->Heat = this->Heat - 0.001F * GameTime.instance.getMultiplier();
 if (this->Heat < Math.max(0.2F, float0) {
 this->Heat = Math.max(0.2F, float0);
 }
 }

 if (this->Heat < float0) {
 this->Heat = this->Heat + float0 / 1000.0F * GameTime.instance.getMultiplier();
 if (this->Heat > Math.min(3.0F, float0) {
 this->Heat = Math.min(3.0F, float0);
 }
 }

 if (this->IsCookable) {
 if (this->Heat > 1.6F) {
 int int0 = GameTime.getInstance().getMinutes();
 if (int0 != this->LastCookMinute) {
 this->LastCookMinute = int0;
 float float1 = this->Heat / 1.5F;
 if (container.getTemprature() <= 1.6F) {
 float1 *= 0.05F;
 }

 float float2 = this->CookingTime;
 if (float2 < 1.0F) {
 float2 = 10.0F;
 }

 float2 += float1;
 if (this->isTaintedWater() && float2 > Math.min(this->MinutesToCook, 10.0F) {
 this->setTaintedWater(false);
 }

 if (!this->isCooked() && float2 > this->MinutesToCook) {
 this->setCooked(true);
 if (this->getReplaceOnCooked() != nullptr) {
 for (int int1 = 0; int1 < this->getReplaceOnCooked().size(); int1++) {
 InventoryItem item = this->container.AddItem(this->getReplaceOnCooked().get(int1);
 if (item != nullptr) {
 if (item instanceof DrainableComboItem) {
 ((DrainableComboItem)item).setUsedDelta(this->getUsedDelta());
 }

 item.copyConditionModData(this);
 }
 }

 this->container.Remove(this);
 IsoWorld.instance.CurrentCell.addToProcessItemsRemove(this);
 return;
 }

 if (this->getOnCooked() != nullptr) {
 LuaManager.caller.protectedCall(LuaManager.thread, LuaManager.env.rawget(this->getOnCooked()), this);
 return;
 }
 }

 if (this->CookingTime > this->MinutesToBurn) {
 this->Burnt = true;
 this->setCooked(false);
 }
 }
 }
 } else if (container != nullptr && container.isMicrowave() && this->isTaintedWater() && this->Heat > 1.6F) {
 int int2 = GameTime.getInstance().getMinutes();
 if (int2 != this->LastCookMinute) {
 this->LastCookMinute = int2;
 float float3 = 1.0F;
 if (container.getTemprature() <= 1.6F) {
 float3 = (float)(float3 * 0.2);
 }

 this->CookingTime += float3;
 if (this->CookingTime > 10.0F) {
 this->setTaintedWater(false);
 }
 }
 }
 }

 if (this->container == nullptr && this->Heat != 1.0F) {
 float float4 = 1.0F;
 if (this->Heat > float4) {
 this->Heat = this->Heat - 0.001F * GameTime.instance.getMultiplier();
 if (this->Heat < float4) {
 this->Heat = float4;
 }
 }

 if (this->Heat < float4) {
 this->Heat = this->Heat + float4 / 1000.0F * GameTime.instance.getMultiplier();
 if (this->Heat > float4) {
 this->Heat = float4;
 }
 }
 }

 if (this->bUseWhileEquiped && this->delta > 0.0F) {
 IsoPlayer player = nullptr;
 if (this->container != nullptr && this->container.parent instanceof IsoPlayer) {
 for (int int3 = 0; int3 < IsoPlayer.numPlayers; int3++) {
 if (this->container.parent == IsoPlayer.players[int3]) {
 player = IsoPlayer.players[int3];
 }
 }
 }

 if (player != nullptr
 && (this->canBeActivated() && this->isActivated() || !this->canBeActivated())
 && (player.isHandItem(this) || player.isAttachedItem(this) {
 this->ticks = this->ticks + GameTime.instance.getMultiplier();

 while (this->ticks >= this->ticksPerEquipUse) {
 this->ticks = this->ticks - this->ticksPerEquipUse;
 if (this->delta > 0.0F) {
 this->Use();
 }
 }
 }
 }

 if (this->bUseWhileUnequiped && this->delta > 0.0F && (this->canBeActivated() && this->isActivated() || !this->canBeActivated())) {
 this->ticks = this->ticks + GameTime.instance.getMultiplier();

 while (this->ticks >= this->ticksPerEquipUse) {
 this->ticks = this->ticks - this->ticksPerEquipUse;
 if (this->delta > 0.0F) {
 this->Use();
 }
 }
 }

 if (this->getWorldItem() != nullptr && this->canStoreWater() && this->isWaterSource() && RainManager.isRaining() && this->getRainFactor() > 0.0F) {
 IsoGridSquare square = this->getWorldItem().getSquare();
 if (square != nullptr && square.isOutside()) {
 this->setUsedDelta(this->getUsedDelta() + 0.001F * RainManager.getRainIntensity() * GameTime.instance.getMultiplier() * this->getRainFactor());
 if (this->getUsedDelta() > 1.0F) {
 this->setUsedDelta(1.0F);
 }

 this->setTaintedWater(true);
 this->updateWeight();
 }
 }
 }

 void Use() {
 if (this->getWorldItem() != nullptr) {
 ItemUser.UseItem(this);
 } else {
 this->delta = this->delta - this->useDelta;
 if (this->uses > 1) {
 int int0 = this->uses - 1;
 this->uses = 1;
 InventoryItem item0 = InventoryItemFactory.CreateItem(this->getFullType());
 item0.setUses(int0);
 this->container.AddItem(item0);
 }

 if (this->delta <= 1.0E-4F) {
 this->delta = 0.0F;
 if (this->getReplaceOnDeplete() != nullptr) {
 std::string string = this->getReplaceOnDepleteFullType();
 if (this->container != nullptr) {
 InventoryItem item1 = this->container.AddItem(string);
 if (this->container.parent instanceof IsoGameCharacter character) {
 if (character.getPrimaryHandItem() == this) {
 character.setPrimaryHandItem(item1);
 }

 if (character.getSecondaryHandItem() == this) {
 character.setSecondaryHandItem(item1);
 }
 }

 item1.setCondition(this->getCondition());
 item1.setFavorite(this->isFavorite());
 this->container.Remove(this);
 }
 } else {
 super.Use();
 }
 }

 this->updateWeight();
 }
 }

 void updateWeight() {
 if (this->getReplaceOnDeplete() != nullptr) {
 if (this->getUsedDelta() >= 1.0F) {
 this->setCustomWeight(true);
 this->setActualWeight(this->getScriptItem().getActualWeight());
 this->setWeight(this->getActualWeight());
 return;
 }

 Item item = ScriptManager.instance.getItem(this->ReplaceOnDepleteFullType);
 if (item != nullptr) {
 this->setCustomWeight(true);
 this->setActualWeight((this->getScriptItem().getActualWeight() - item.getActualWeight()) * this->getUsedDelta() + item.getActualWeight());
 this->setWeight(this->getActualWeight());
 }
 }

 if (this->getWeightEmpty() != 0.0F) {
 this->setCustomWeight(true);
 this->setActualWeight((this->getScriptItem().getActualWeight() - this->WeightEmpty) * this->getUsedDelta() + this->WeightEmpty);
 }
 }

 /**
 * @return the EmptyWeight
 */
 float getWeightEmpty() {
 return this->WeightEmpty;
 }

 /**
 * 
 * @param weight the EmptyWeight to set
 */
 void setWeightEmpty(float weight) {
 this->WeightEmpty = weight;
 }

 /**
 * @return the bUseWhileEquiped
 */
 bool isUseWhileEquiped() {
 return this->bUseWhileEquiped;
 }

 /**
 * 
 * @param _bUseWhileEquiped the bUseWhileEquiped to set
 */
 void setUseWhileEquiped(bool _bUseWhileEquiped) {
 this->bUseWhileEquiped = _bUseWhileEquiped;
 }

 /**
 * @return the bUseWhileUnequiped
 */
 bool isUseWhileUnequiped() {
 return this->bUseWhileUnequiped;
 }

 /**
 * 
 * @param _bUseWhileUnequiped the bUseWhileUnequiped to set
 */
 void setUseWhileUnequiped(bool _bUseWhileUnequiped) {
 this->bUseWhileUnequiped = _bUseWhileUnequiped;
 }

 /**
 * @return the ticksPerEquipUse
 */
 int getTicksPerEquipUse() {
 return this->ticksPerEquipUse;
 }

 /**
 * 
 * @param _ticksPerEquipUse the ticksPerEquipUse to set
 */
 void setTicksPerEquipUse(int _ticksPerEquipUse) {
 this->ticksPerEquipUse = _ticksPerEquipUse;
 }

 /**
 * @return the useDelta
 */
 float getUseDelta() {
 return this->useDelta;
 }

 /**
 * 
 * @param _useDelta the useDelta to set
 */
 void setUseDelta(float _useDelta) {
 this->useDelta = _useDelta;
 }

 /**
 * @return the delta
 */
 float getDelta() {
 return this->delta;
 }

 /**
 * 
 * @param _delta the delta to set
 */
 void setDelta(float _delta) {
 this->delta = _delta;
 }

 /**
 * @return the ticks
 */
 float getTicks() {
 return this->ticks;
 }

 /**
 * 
 * @param _ticks the ticks to set
 */
 void setTicks(float _ticks) {
 this->ticks = _ticks;
 }

 void setReplaceOnDeplete(const std::string& _ReplaceOnDeplete) {
 this->ReplaceOnDeplete = _ReplaceOnDeplete;
 this->ReplaceOnDepleteFullType = this->getReplaceOnDepleteFullType();
 }

 /**
 * @return the ReplaceOnDeplete
 */
 std::string getReplaceOnDeplete() {
 return this->ReplaceOnDeplete;
 }

 std::string getReplaceOnDepleteFullType() {
 return StringUtils.moduleDotType(this->getModule(), this->ReplaceOnDeplete);
 }

 void setHeat(float heat) {
 this->Heat = PZMath.clamp(heat, 0.0F, 3.0F);
 }

 float getHeat() {
 return this->Heat;
 }

 float getInvHeat() {
 return (1.0F - this->Heat) / 3.0F;
 }

 bool finishupdate() {
 if (this->canStoreWater() && this->isWaterSource() && this->getWorldItem() != nullptr && this->getWorldItem().getSquare() != nullptr) {
 return this->getUsedDelta() >= 1.0F;
 } else if (this->isTaintedWater()) {
 return false;
 } else {
 if (this->container != nullptr) {
 if (this->Heat != this->container.getTemprature() || this->container.isTemperatureChanging()) {
 return false;
 }

 if (this->container.type == "campfire") || this->container.type == "barbecue")) {
 return false;
 }
 }

 return true;
 }
 }

 int getRemainingUses() {
 return Math.round(this->getUsedDelta() / this->getUseDelta());
 }

 float getRainFactor() {
 return this->rainFactor;
 }

 void setRainFactor(float _rainFactor) {
 this->rainFactor = _rainFactor;
 }

 bool canConsolidate() {
 return this->canConsolidate;
 }

 void setCanConsolidate(bool _canConsolidate) {
 this->canConsolidate = _canConsolidate;
 }

 /**
 * @return the ReplaceOnCooked
 */
 public List<String> getReplaceOnCooked() {
 return this->ReplaceOnCooked;
 }

 /**
 * 
 * @param replaceOnCooked the ReplaceOnCooked to set
 */
 void setReplaceOnCooked(List<String> replaceOnCooked) {
 this->ReplaceOnCooked = replaceOnCooked;
 }

 /**
 * @return the OnCooked
 */
 std::string getOnCooked() {
 return this->OnCooked;
 }

 /**
 * 
 * @param onCooked the onCooked to set
 */
 void setOnCooked(const std::string& onCooked) {
 this->OnCooked = onCooked;
 }
}
} // namespace types
} // namespace inventory
} // namespace zombie
