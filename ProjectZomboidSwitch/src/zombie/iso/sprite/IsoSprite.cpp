#include <string>
#include "zombie\iso\sprite/IsoSprite.h"

namespace zombie {
namespace iso {
namespace sprite {

void IsoSprite::setHideForWaterRender() {
    // TODO: Implement setHideForWaterRender
}

public IsoSprite::IsoSprite() {
    // TODO: Implement IsoSprite
    return nullptr;
}

public IsoSprite::IsoSprite(IsoSpriteManager var1) {
    // TODO: Implement IsoSprite
    return nullptr;
}

IsoSprite IsoSprite::CreateSprite(IsoSpriteManager var0) {
    // TODO: Implement CreateSprite
    return nullptr;
}

IsoSprite IsoSprite::CreateSpriteUsingCache(const std::string& var0, const std::string& var1, int var2) {
    // TODO: Implement CreateSpriteUsingCache
    return nullptr;
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager var0, int var1) {
    // TODO: Implement getSprite
    return nullptr;
}

void IsoSprite::setSpriteID(IsoSpriteManager var0, int var1, IsoSprite var2) {
    // TODO: Implement setSpriteID
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager var0, IsoSprite var1, int var2) {
    // TODO: Implement getSprite
    return nullptr;
}

IsoSprite IsoSprite::getSprite(IsoSpriteManager var0, const std::string& var1, int var2) {
    // TODO: Implement getSprite
    return nullptr;
}

void IsoSprite::DisposeAll() {
    // TODO: Implement DisposeAll
}

bool IsoSprite::HasCache(const std::string& var0) {
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

void IsoSprite::setParentObjectName(const std::string& var1) {
    // TODO: Implement setParentObjectName
}

void IsoSprite::save(DataOutputStream var1) {
    // TODO: Implement save
}

void IsoSprite::load(DataInputStream var1) {
    // TODO: Implement load
}

void IsoSprite::Dispose() {
    // TODO: Implement Dispose
}

bool IsoSprite::isMaskClicked(IsoDirections var1, int var2, int var3) {
    // TODO: Implement isMaskClicked
    return false;
}

bool IsoSprite::isMaskClicked(IsoDirections var1, int var2, int var3, bool var4) {
    // TODO: Implement isMaskClicked
    return false;
}

float IsoSprite::getMaskClickedY(IsoDirections var1, int var2, int var3, bool var4) {
    // TODO: Implement getMaskClickedY
    return 0;
}

Texture IsoSprite::LoadFrameExplicit(const std::string& var1) {
    // TODO: Implement LoadFrameExplicit
    return nullptr;
}

void IsoSprite::LoadFrames(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement LoadFrames
}

void IsoSprite::LoadFramesReverseAltName(const std::string& var1, const std::string& var2, const std::string& var3, int var4) {
    // TODO: Implement LoadFramesReverseAltName
}

void IsoSprite::LoadFramesNoDirPage(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement LoadFramesNoDirPage
}

void IsoSprite::LoadFramesNoDirPageDirect(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement LoadFramesNoDirPageDirect
}

void IsoSprite::LoadFramesNoDirPageSimple(const std::string& var1) {
    // TODO: Implement LoadFramesNoDirPageSimple
}

void IsoSprite::ReplaceCurrentAnimFrames(const std::string& var1) {
    // TODO: Implement ReplaceCurrentAnimFrames
}

void IsoSprite::LoadFramesPageSimple(const std::string& var1, const std::string& var2, const std::string& var3, const std::string& var4) {
    // TODO: Implement LoadFramesPageSimple
}

void IsoSprite::LoadFramesPcx(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement LoadFramesPcx
}

void IsoSprite::PlayAnim(IsoAnim var1) {
    // TODO: Implement PlayAnim
}

void IsoSprite::PlayAnim(const std::string& var1) {
    // TODO: Implement PlayAnim
}

void IsoSprite::PlayAnimUnlooped(const std::string& var1) {
    // TODO: Implement PlayAnimUnlooped
}

void IsoSprite::ChangeTintMod(ColorInfo var1) {
    // TODO: Implement ChangeTintMod
}

void IsoSprite::RenderGhostTile(int var1, int var2, int var3) {
    // TODO: Implement RenderGhostTile
}

void IsoSprite::RenderGhostTileRed(int var1, int var2, int var3) {
    // TODO: Implement RenderGhostTileRed
}

void IsoSprite::RenderGhostTileColor(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    // TODO: Implement RenderGhostTileColor
}

void IsoSprite::RenderGhostTileColor(int var1, int var2, int var3, float var4, float var5, float var6, float var7, float var8, float var9) {
    // TODO: Implement RenderGhostTileColor
}

bool IsoSprite::hasActiveModel() {
    // TODO: Implement hasActiveModel
    return false;
}

void IsoSprite::renderVehicle(IsoSpriteInstance var1, IsoObject var2, float var3, float var4, float var5, float var6, float var7, ColorInfo var8, bool var9) {
    // TODO: Implement renderVehicle
}

IsoSpriteInstance IsoSprite::getSpriteInstance() {
    // TODO: Implement getSpriteInstance
    return nullptr;
}

void IsoSprite::initSpriteInstance() {
    // TODO: Implement initSpriteInstance
}

void IsoSprite::render(IsoObject var1, float var2, float var3, float var4, IsoDirections var5, float var6, float var7, ColorInfo var8, bool var9) {
    // TODO: Implement render
}

float IsoSprite::getCurrentSpriteFrame(IsoSpriteInstance var1) {
    // TODO: Implement getCurrentSpriteFrame
    return 0;
}

void IsoSprite::performRenderFrame(IsoSpriteInstance var1, IsoObject var2, IsoDirections var3, int var4, float var5, float var6, Consumer<TextureDraw> var7) {
    // TODO: Implement performRenderFrame
}

void IsoSprite::renderSpriteOutline(float var1, float var2, Texture var3, float var4, float var5) {
    // TODO: Implement renderSpriteOutline
}

void IsoSprite::renderActiveModel() {
    // TODO: Implement renderActiveModel
}

void IsoSprite::renderBloodSplat(float var1, float var2, float var3, ColorInfo var4) {
    // TODO: Implement renderBloodSplat
}

void IsoSprite::renderObjectPicker(IsoSpriteInstance var1, IsoObject var2, IsoDirections var3) {
    // TODO: Implement renderObjectPicker
}

Texture IsoSprite::getTextureForFrame(int var1, IsoDirections var2) {
    // TODO: Implement getTextureForFrame
    return nullptr;
}

Texture IsoSprite::getTextureForCurrentFrame(IsoDirections var1) {
    // TODO: Implement getTextureForCurrentFrame
    return nullptr;
}

void IsoSprite::update() {
    // TODO: Implement update
}

void IsoSprite::update(IsoSpriteInstance var1) {
    // TODO: Implement update
}

void IsoSprite::CacheAnims(const std::string& var1) {
    // TODO: Implement CacheAnims
}

void IsoSprite::LoadCache(const std::string& var1) {
    // TODO: Implement LoadCache
}

IsoSprite IsoSprite::setFromCache(const std::string& var1, const std::string& var2, int var3) {
    // TODO: Implement setFromCache
    return nullptr;
}

IsoObjectType IsoSprite::getType() {
    // TODO: Implement getType
    return nullptr;
}

void IsoSprite::setType(IsoObjectType var1) {
    // TODO: Implement setType
}

void IsoSprite::AddProperties(IsoSprite var1) {
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

void IsoSprite::setName(const std::string& var1) {
    // TODO: Implement setName
}

ColorInfo IsoSprite::getTintMod() {
    // TODO: Implement getTintMod
    return nullptr;
}

void IsoSprite::setTintMod(ColorInfo var1) {
    // TODO: Implement setTintMod
}

void IsoSprite::setAnimate(bool var1) {
    // TODO: Implement setAnimate
}

IsoSpriteGrid IsoSprite::getSpriteGrid() {
    // TODO: Implement getSpriteGrid
    return nullptr;
}

void IsoSprite::setSpriteGrid(IsoSpriteGrid var1) {
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

int IsoSprite::getSheetGridIdFromName(const std::string& var0) {
    // TODO: Implement getSheetGridIdFromName
    return 0;
}

} // namespace sprite
} // namespace iso
} // namespace zombie
