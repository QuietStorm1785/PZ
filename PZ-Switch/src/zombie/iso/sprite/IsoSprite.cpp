#include "zombie/iso/sprite/IsoSprite.h"

namespace zombie {
namespace iso {
namespace sprite {

void IsoSprite::setHideForWaterRender() {
 // TODO: Implement setHideForWaterRender
}

public
IsoSprite::IsoSprite() {
 // TODO: Implement IsoSprite
 return nullptr;
}

public
IsoSprite::IsoSprite(IsoSpriteManager manager) {
 // TODO: Implement IsoSprite
 return nullptr;
}

IsoSprite IsoSprite::CreateSprite(IsoSpriteManager manager) {
 // TODO: Implement CreateSprite
 return nullptr;
}

IsoSprite IsoSprite::CreateSpriteUsingCache(const std::string &objectName,
 const std::string &animName,
 int numFrames) {
 // TODO: Implement CreateSpriteUsingCache
 return nullptr;
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager manager, int id) {
 // TODO: Implement getSprite
 return nullptr;
}

void IsoSprite::setSpriteID(IsoSpriteManager manager, int id, IsoSprite spr) {
 // TODO: Implement setSpriteID
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager manager, IsoSprite spr,
 int offset) {
 // TODO: Implement getSprite
 return nullptr;
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager manager,
 const std::string &_name, int offset) {
 // TODO: Implement getSprite
 return nullptr;
}

void IsoSprite::DisposeAll() {
 // TODO: Implement DisposeAll
}

bool IsoSprite::HasCache(const std::string &string) {
 // TODO: Implement HasCache
 return false;
}

IsoSpriteInstance IsoSprite::newInstance() {
 // TODO: Implement newInstance
 return nullptr;
}

PropertyContainer IsoSprite::getProperties() {
 // TODO: Implement getProperties
 return nullptr;
}

std::string IsoSprite::getParentObjectName() {
 // TODO: Implement getParentObjectName
 return "";
}

void IsoSprite::setParentObjectName(const std::string &val) {
 // TODO: Implement setParentObjectName
}

void IsoSprite::save(DataOutputStream output) {
 // TODO: Implement save
}

void IsoSprite::load(DataInputStream input) {
 // TODO: Implement load
}

void IsoSprite::Dispose() {
 // TODO: Implement Dispose
}

bool IsoSprite::isMaskClicked(IsoDirections dir, int x, int y) {
 // TODO: Implement isMaskClicked
 return false;
}

bool IsoSprite::isMaskClicked(IsoDirections dir, int x, int y, bool flip) {
 // TODO: Implement isMaskClicked
 return false;
}

float IsoSprite::getMaskClickedY(IsoDirections dir, int x, int y, bool flip) {
 // TODO: Implement getMaskClickedY
 return 0;
}

Texture IsoSprite::LoadFrameExplicit(const std::string &ObjectName) {
 // TODO: Implement LoadFrameExplicit
 return nullptr;
}

void IsoSprite::LoadFrames(const std::string &ObjectName,
 const std::string &AnimName, int nFrames) {
 // TODO: Implement LoadFrames
}

void IsoSprite::LoadFramesReverseAltName(const std::string &ObjectName,
 const std::string &AnimName,
 const std::string &AltName,
 int nFrames) {
 // TODO: Implement LoadFramesReverseAltName
}

void IsoSprite::LoadFramesNoDirPage(const std::string &ObjectName,
 const std::string &AnimName, int nFrames) {
 // TODO: Implement LoadFramesNoDirPage
}

void IsoSprite::LoadFramesNoDirPageDirect(const std::string &ObjectName,
 const std::string &AnimName,
 int nFrames) {
 // TODO: Implement LoadFramesNoDirPageDirect
}

void IsoSprite::LoadFramesNoDirPageSimple(const std::string &ObjectName) {
 // TODO: Implement LoadFramesNoDirPageSimple
}

void IsoSprite::ReplaceCurrentAnimFrames(const std::string &ObjectName) {
 // TODO: Implement ReplaceCurrentAnimFrames
}

void IsoSprite::LoadFramesPageSimple(const std::string &NObjectName,
 const std::string &SObjectName,
 const std::string &EObjectName,
 const std::string &WObjectName) {
 // TODO: Implement LoadFramesPageSimple
}

void IsoSprite::LoadFramesPcx(const std::string &ObjectName,
 const std::string &AnimName, int nFrames) {
 // TODO: Implement LoadFramesPcx
}

void IsoSprite::PlayAnim(IsoAnim anim) {
 // TODO: Implement PlayAnim
}

void IsoSprite::PlayAnim(const std::string &_name) {
 // TODO: Implement PlayAnim
}

void IsoSprite::PlayAnimUnlooped(const std::string &_name) {
 // TODO: Implement PlayAnimUnlooped
}

void IsoSprite::ChangeTintMod(ColorInfo NewTintMod) {
 // TODO: Implement ChangeTintMod
}

void IsoSprite::RenderGhostTile(int x, int y, int z) {
 // TODO: Implement RenderGhostTile
}

void IsoSprite::RenderGhostTileRed(int x, int y, int z) {
 // TODO: Implement RenderGhostTileRed
}

void IsoSprite::RenderGhostTileColor(int x, int y, int z, float r, float g,
 float b, float a) {
 // TODO: Implement RenderGhostTileColor
}

void IsoSprite::RenderGhostTileColor(int x, int y, int z, float offsetX,
 float offsetY, float r, float g, float b,
 float a) {
 // TODO: Implement RenderGhostTileColor
}

bool IsoSprite::hasActiveModel() {
 // TODO: Implement hasActiveModel
 return false;
}

IsoSpriteInstance IsoSprite::getSpriteInstance() {
 // TODO: Implement getSpriteInstance
 return nullptr;
}

void IsoSprite::initSpriteInstance() {
 // TODO: Implement initSpriteInstance
}

void IsoSprite::render(IsoObject obj, float x, float y, float z,
 IsoDirections dir, float offsetX, float offsetY,
 ColorInfo info2, bool bDoRenderPrep) {
 // TODO: Implement render
}

float IsoSprite::getCurrentSpriteFrame(IsoSpriteInstance spriteInstance) {
 // TODO: Implement getCurrentSpriteFrame
 return 0;
}

void IsoSprite::renderSpriteOutline(float float0, float float1, Texture texture,
 float float3, float float2) {
 // TODO: Implement renderSpriteOutline
}

void IsoSprite::renderActiveModel() {
 // TODO: Implement renderActiveModel
}

void IsoSprite::renderBloodSplat(float x, float y, float z, ColorInfo info2) {
 // TODO: Implement renderBloodSplat
}

void IsoSprite::renderObjectPicker(IsoSpriteInstance _def, IsoObject obj,
 IsoDirections dir) {
 // TODO: Implement renderObjectPicker
}

Texture IsoSprite::getTextureForFrame(int frame, IsoDirections dir) {
 // TODO: Implement getTextureForFrame
 return nullptr;
}

Texture IsoSprite::getTextureForCurrentFrame(IsoDirections dir) {
 // TODO: Implement getTextureForCurrentFrame
 return nullptr;
}

void IsoSprite::update() {
 // TODO: Implement update
}

void IsoSprite::update(IsoSpriteInstance _def) {
 // TODO: Implement update
}

void IsoSprite::CacheAnims(const std::string &key) {
 // TODO: Implement CacheAnims
}

void IsoSprite::LoadCache(const std::string &string) {
 // TODO: Implement LoadCache
}

IsoSprite IsoSprite::setFromCache(const std::string &objectName,
 const std::string &animName, int numFrames) {
 // TODO: Implement setFromCache
 return nullptr;
}

IsoObjectType IsoSprite::getType() {
 // TODO: Implement getType
 return nullptr;
}

void IsoSprite::setType(IsoObjectType ntype) {
 // TODO: Implement setType
}

void IsoSprite::AddProperties(IsoSprite sprite) {
 // TODO: Implement AddProperties
}

int IsoSprite::getID() {
 // TODO: Implement getID
 return 0;
}

std::string IsoSprite::getName() {
 // TODO: Implement getName
 return "";
}

void IsoSprite::setName(const std::string &string) {
 // TODO: Implement setName
}

ColorInfo IsoSprite::getTintMod() {
 // TODO: Implement getTintMod
 return nullptr;
}

void IsoSprite::setTintMod(ColorInfo _info) {
 // TODO: Implement setTintMod
}

void IsoSprite::setAnimate(bool animate) {
 // TODO: Implement setAnimate
}

IsoSpriteGrid IsoSprite::getSpriteGrid() {
 // TODO: Implement getSpriteGrid
 return nullptr;
}

void IsoSprite::setSpriteGrid(IsoSpriteGrid sGrid) {
 // TODO: Implement setSpriteGrid
}

bool IsoSprite::isMoveWithWind() {
 // TODO: Implement isMoveWithWind
 return false;
}

int IsoSprite::getSheetGridIdFromName() {
 // TODO: Implement getSheetGridIdFromName
 return 0;
}

int IsoSprite::getSheetGridIdFromName(const std::string &_name) {
 // TODO: Implement getSheetGridIdFromName
 return 0;
}

} // namespace sprite
} // namespace iso
} // namespace zombie
