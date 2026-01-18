#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/EquippedTextureCreator.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/inventory/InventoryItem.h"
#include "zombie/inventory/types/HandWeapon.h"
#include "zombie/popman/ObjectPool.h"
#include "zombie/util/Type.h"

namespace zombie {
namespace core {
namespace skinnedmodel {
namespace model {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModelInstanceTextureInitializer {
public:
 bool m_bRendered;
 ModelInstance m_modelInstance;
 InventoryItem m_item;
 float m_bloodLevel;
 int m_changeNumberMain = 0;
 int m_changeNumberThread = 0;
 private ModelInstanceTextureInitializer.RenderData[] m_renderData = new ModelInstanceTextureInitializer.RenderData[3];
 private static ObjectPool<ModelInstanceTextureInitializer> pool = new ObjectPool<>(ModelInstanceTextureInitializer::new);

 void init(ModelInstance modelInstance, InventoryItem item) {
 this->m_item = item;
 this->m_modelInstance = modelInstance;
 HandWeapon weapon = Type.tryCastTo(item, HandWeapon.class);
 this->m_bloodLevel = weapon == nullptr ? 0.0F : weapon.getBloodLevel();
 this->setDirty();
 }

 void init(ModelInstance modelInstance, float bloodLevel) {
 this->m_item = nullptr;
 this->m_modelInstance = modelInstance;
 this->m_bloodLevel = bloodLevel;
 this->setDirty();
 }

 void setDirty() {
 this->m_changeNumberMain++;
 this->m_bRendered = false;
 }

 bool isDirty() {
 return !this->m_bRendered;
 }

 void renderMain() {
 if (!this->m_bRendered) {
 int int0 = SpriteRenderer.instance.getMainStateIndex();
 if (this->m_renderData[int0] == nullptr) {
 this->m_renderData[int0] = new ModelInstanceTextureInitializer.RenderData();
 }

 ModelInstanceTextureInitializer.RenderData renderData = this->m_renderData[int0];
 if (renderData.m_textureCreator == nullptr) {
 renderData.m_changeNumber = this->m_changeNumberMain;
 renderData.m_textureCreator = EquippedTextureCreator.alloc();
 if (this->m_item == nullptr) {
 renderData.m_textureCreator.init(this->m_modelInstance, this->m_bloodLevel);
 } else {
 renderData.m_textureCreator.init(this->m_modelInstance, this->m_item);
 }

 renderData.m_bRendered = false;
 }
 }
 }

 void render() {
 int int0 = SpriteRenderer.instance.getRenderStateIndex();
 ModelInstanceTextureInitializer.RenderData renderData = this->m_renderData[int0];
 if (renderData != nullptr) {
 if (renderData.m_textureCreator != nullptr) {
 if (!renderData.m_bRendered) {
 if (renderData.m_changeNumber == this->m_changeNumberThread) {
 renderData.m_bRendered = true;
 } else {
 renderData.m_textureCreator.render();
 if (renderData.m_textureCreator.isRendered()) {
 this->m_changeNumberThread = renderData.m_changeNumber;
 renderData.m_bRendered = true;
 }
 }
 }
 }
 }
 }

 void postRender() {
 int int0 = SpriteRenderer.instance.getMainStateIndex();
 ModelInstanceTextureInitializer.RenderData renderData = this->m_renderData[int0];
 if (renderData != nullptr) {
 if (renderData.m_textureCreator != nullptr) {
 if (renderData.m_textureCreator.isRendered() && renderData.m_changeNumber == this->m_changeNumberMain) {
 this->m_bRendered = true;
 }

 if (renderData.m_bRendered) {
 renderData.m_textureCreator.postRender();
 renderData.m_textureCreator = nullptr;
 }
 }
 }
 }

 bool isRendered() {
 int int0 = SpriteRenderer.instance.getRenderStateIndex();
 ModelInstanceTextureInitializer.RenderData renderData = this->m_renderData[int0];
 if (renderData == nullptr) {
 return true;
 } else {
 return renderData.m_textureCreator == nullptr ? true : renderData.m_bRendered;
 }
 }

 static ModelInstanceTextureInitializer alloc() {
 return pool.alloc();
 }

 void release() {
 pool.release(this);
 }

 private static class RenderData {
 int m_changeNumber = 0;
 bool m_bRendered;
 EquippedTextureCreator m_textureCreator;
 }
}
} // namespace model
} // namespace skinnedmodel
} // namespace core
} // namespace zombie
