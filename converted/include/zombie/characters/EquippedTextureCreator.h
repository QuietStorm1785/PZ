#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "zombie/characterTextures/ItemSmartTexture.h"
#include "zombie/core/skinnedmodel/ModelManager.h"
#include "zombie/core/skinnedmodel/model/ModelInstance.h"
#include "zombie/core/textures/SmartTexture.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/popman/ObjectPool.h"

namespace zombie {
namespace characters {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class EquippedTextureCreator : public TextureDraw {
public:
 bool bRendered;
 ModelInstance modelInstance;
 float bloodLevel;
 private ArrayList<Texture> texturesNotReady = std::make_unique<ArrayList<>>();
 private static ObjectPool<EquippedTextureCreator> pool = new ObjectPool<>(EquippedTextureCreator::new);

 void init(ModelInstance _modelInstance, InventoryItem item) {
 float float0 = 0.0F;
 if (item instanceof HandWeapon) {
 float0 = ((HandWeapon)item).getBloodLevel();
 }

 this->init(_modelInstance, float0);
 }

 void init(ModelInstance _modelInstance, float _bloodLevel) {
 this->bRendered = false;
 this->texturesNotReady.clear();
 this->modelInstance = _modelInstance;
 this->bloodLevel = _bloodLevel;
 if (this->modelInstance != nullptr) {
 this->modelInstance.renderRefCount++;
 Texture texture = this->modelInstance.tex;
 if (texture instanceof SmartTexture) {
 texture = nullptr;
 }

 if (texture != nullptr && !texture.isReady()) {
 this->texturesNotReady.add(texture);
 }

 texture = Texture.getSharedTexture("media/textures/BloodTextures/BloodOverlayWeapon.png");
 if (texture != nullptr && !texture.isReady()) {
 this->texturesNotReady.add(texture);
 }

 texture = Texture.getSharedTexture("media/textures/BloodTextures/BloodOverlayWeaponMask.png");
 if (texture != nullptr && !texture.isReady()) {
 this->texturesNotReady.add(texture);
 }
 }
 }

 void render() {
 for (int int0 = 0; int0 < this->texturesNotReady.size(); int0++) {
 Texture texture = this->texturesNotReady.get(int0);
 if (!texture.isReady()) {
 return;
 }
 }

 GL11.glPushAttrib(2048);

 try {
 this->updateTexture(this->modelInstance, this->bloodLevel);
 } finally {
 GL11.glPopAttrib();
 }

 this->bRendered = true;
 }

 void updateTexture(ModelInstance modelInstancex, float float0) {
 if (modelInstancex != nullptr) {
 ItemSmartTexture itemSmartTexture = nullptr;
 if (float0 > 0.0F) {
 if (modelInstancex.tex instanceof ItemSmartTexture) {
 itemSmartTexture = (ItemSmartTexture)modelInstancex.tex;
 } else if (modelInstancex.tex != nullptr) {
 itemSmartTexture = new ItemSmartTexture(modelInstancex.tex.getName());
 }
 } else if (modelInstancex.tex instanceof ItemSmartTexture) {
 itemSmartTexture = (ItemSmartTexture)modelInstancex.tex;
 }

 if (itemSmartTexture != nullptr) {
 itemSmartTexture.setBlood(
 "media/textures/BloodTextures/BloodOverlayWeapon.png", "media/textures/BloodTextures/BloodOverlayWeaponMask.png", float0, 300
 );
 itemSmartTexture.calculate();
 modelInstancex.tex = itemSmartTexture;
 }
 }
 }

 void postRender() {
 ModelManager.instance.derefModelInstance(this->modelInstance);
 this->texturesNotReady.clear();
 if (!this->bRendered) {
 }

 pool.release(this);
 }

 bool isRendered() {
 return this->bRendered;
 }

 static EquippedTextureCreator alloc() {
 return pool.alloc();
 }
}
} // namespace characters
} // namespace zombie
