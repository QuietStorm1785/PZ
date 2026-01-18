#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace core {
namespace textures {

public
Texture::Texture(AssetPath path, AssetManager manager,
 Texture.TextureAssetParams params) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(TextureID data, const std::string &_name) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &file) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &_name, BufferedInputStream b, bool bDoMask,
 Texture.PZFileformat format) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &_name, BufferedInputStream b,
 bool bDoMask) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &file, bool bDelete, bool bUseAlpha) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &_name, const std::string &palette) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &string, int[] ints) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &file, bool useAlphaChannel) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(int _width, int _height, const std::string &_name, int flags) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(int _width, int _height, int flags) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(const std::string &file, int red, int green, int blue) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture(Texture t) {
 // TODO: Implement Texture
 return nullptr;
}

public
Texture::Texture() {
 // TODO: Implement Texture
 return nullptr;
}

std::string Texture::processFilePath(const std::string &filePath) {
 // TODO: Implement processFilePath
 return "";
}

void Texture::bindNone() {
 // TODO: Implement bindNone
}

Texture Texture::getWhite() {
 // TODO: Implement getWhite
 return nullptr;
}

Texture Texture::getErrorTexture() {
 // TODO: Implement getErrorTexture
 return nullptr;
}

void Texture::initEngineMipmapTextureLevel(int int7, int int0, int int1,
 int int3, int int4, int int5,
 int int6) {
 // TODO: Implement initEngineMipmapTextureLevel
}

Texture Texture::getEngineMipmapTexture() {
 // TODO: Implement getEngineMipmapTexture
 return nullptr;
}

void Texture::clearTextures() {
 // TODO: Implement clearTextures
}

Texture Texture::getSharedTexture(const std::string &_name) {
 // TODO: Implement getSharedTexture
 return nullptr;
}

return Texture::getSharedTexture() {
 // TODO: Implement getSharedTexture
 return nullptr;
}

Texture Texture::getSharedTexture(const std::string &_name, int flags) {
 // TODO: Implement getSharedTexture
 return nullptr;
}

return Texture::getSharedTextureInternal() {
 // TODO: Implement getSharedTextureInternal
 return nullptr;
}

Texture Texture::trygetTexture(const std::string &_name) {
 // TODO: Implement trygetTexture
 return nullptr;
}

void Texture::onTextureFileChanged(const std::string &string) {
 // TODO: Implement onTextureFileChanged
}

void Texture::onTexturePacksChanged() {
 // TODO: Implement onTexturePacksChanged
}

void Texture::setSharedTextureInternal(const std::string &string,
 Texture texture) {
 // TODO: Implement setSharedTextureInternal
}

Texture Texture::getSharedTextureInternal(const std::string &string0,
 int int0) {
 // TODO: Implement getSharedTextureInternal
 return nullptr;
}

Texture Texture::getSharedTexture(const std::string &_name,
 const std::string &palette) {
 // TODO: Implement getSharedTexture
 return nullptr;
}

Texture Texture::getSharedTexture(const std::string &string0, int[] ints,
 const std::string &string1) {
 // TODO: Implement getSharedTexture
 return nullptr;
}

Texture Texture::getTexture(const std::string &_name) {
 // TODO: Implement getTexture
 return nullptr;
}

Texture Texture::getSteamAvatar(long steamID) {
 // TODO: Implement getSteamAvatar
 return nullptr;
}

void Texture::steamAvatarChanged(long steamID) {
 // TODO: Implement steamAvatarChanged
}

void Texture::forgetTexture(const std::string &_name) {
 // TODO: Implement forgetTexture
}

void Texture::reload(const std::string &_name) {
 // TODO: Implement reload
}

void Texture::reloadFromFile(const std::string &_name) {
 // TODO: Implement reloadFromFile
}

void Texture::bind() {
 // TODO: Implement bind
}

void Texture::bind(int unit) {
 // TODO: Implement bind
}

void Texture::copyMaskRegion(Texture from, int x, int y, int _width,
 int _height) {
 // TODO: Implement copyMaskRegion
}

new Texture::Mask() {
 // TODO: Implement Mask
 return nullptr;
}

void Texture::createMask() {
 // TODO: Implement createMask
}

new Texture::Mask() {
 // TODO: Implement Mask
 return nullptr;
}

void Texture::createMask(boolean[] booleans) {
 // TODO: Implement createMask
}

new Texture::Mask() {
 // TODO: Implement Mask
 return nullptr;
}

void Texture::createMask(BooleanGrid _mask) {
 // TODO: Implement createMask
}

new Texture::Mask() {
 // TODO: Implement Mask
 return nullptr;
}

void Texture::createMask(WrappedBuffer buf) {
 // TODO: Implement createMask
}

new Texture::Mask() {
 // TODO: Implement Mask
 return nullptr;
}

void Texture::destroy() {
 // TODO: Implement destroy
}

bool Texture::equals(Texture other) {
 // TODO: Implement equals
 return false;
}

WrappedBuffer Texture::getData() {
 // TODO: Implement getData
 return nullptr;
}

void Texture::setData(ByteBuffer data) {
 // TODO: Implement setData
}

int Texture::getHeight() {
 // TODO: Implement getHeight
 return 0;
}

void Texture::setHeight(int _height) {
 // TODO: Implement setHeight
}

int Texture::getHeightHW() {
 // TODO: Implement getHeightHW
 return 0;
}

int Texture::getHeightOrig() {
 // TODO: Implement getHeightOrig
 return 0;
}

int Texture::getID() {
 // TODO: Implement getID
 return 0;
}

Mask Texture::getMask() {
 // TODO: Implement getMask
 return nullptr;
}

void Texture::setMask(Mask _mask) {
 // TODO: Implement setMask
}

std::string Texture::getName() {
 // TODO: Implement getName
 return "";
}

void Texture::setName(const std::string &_name) {
 // TODO: Implement setName
}

TextureID Texture::getTextureId() {
 // TODO: Implement getTextureId
 return nullptr;
}

bool Texture::getUseAlphaChannel() {
 // TODO: Implement getUseAlphaChannel
 return false;
}

void Texture::setUseAlphaChannel(bool value) {
 // TODO: Implement setUseAlphaChannel
}

int Texture::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

void Texture::setWidth(int _width) {
 // TODO: Implement setWidth
}

int Texture::getWidthHW() {
 // TODO: Implement getWidthHW
 return 0;
}

int Texture::getWidthOrig() {
 // TODO: Implement getWidthOrig
 return 0;
}

float Texture::getXEnd() {
 // TODO: Implement getXEnd
 return 0;
}

float Texture::getXStart() {
 // TODO: Implement getXStart
 return 0;
}

float Texture::getYEnd() {
 // TODO: Implement getYEnd
 return 0;
}

float Texture::getYStart() {
 // TODO: Implement getYStart
 return 0;
}

float Texture::getOffsetX() {
 // TODO: Implement getOffsetX
 return 0;
}

void Texture::setOffsetX(int offset) {
 // TODO: Implement setOffsetX
}

float Texture::getOffsetY() {
 // TODO: Implement getOffsetY
 return 0;
}

void Texture::setOffsetY(int offset) {
 // TODO: Implement setOffsetY
}

bool Texture::isCollisionable() {
 // TODO: Implement isCollisionable
 return false;
}

bool Texture::isDestroyed() {
 // TODO: Implement isDestroyed
 return false;
}

bool Texture::isSolid() {
 // TODO: Implement isSolid
 return false;
}

bool Texture::isValid() {
 // TODO: Implement isValid
 return false;
}

void Texture::makeTransp(int red, int green, int blue) {
 // TODO: Implement makeTransp
}

void Texture::render(float x, float y, float _width, float _height) {
 // TODO: Implement render
}

void Texture::render(float x, float y) {
 // TODO: Implement render
}

void Texture::render(float x, float y, float _width, float _height, float r,
 float g, float b, float a,
 Consumer<TextureDraw> texdModifier) {
 // TODO: Implement render
}

void Texture::renderdiamond(float x, float y, float _width, float _height,
 int l, int u, int r, int d) {
 // TODO: Implement renderdiamond
}

void Texture::renderwallnw(float x, float y, float _width, float _height, int u,
 int d, int u2, int d2, int r, int r2) {
 // TODO: Implement renderwallnw
}

void Texture::renderwallw(float x, float y, float _width, float _height, int u,
 int d, int u2, int d2) {
 // TODO: Implement renderwallw
}

void Texture::renderwalln(float x, float y, float _width, float _height, int u,
 int d, int u2, int d2) {
 // TODO: Implement renderwalln
}

void Texture::renderstrip(int x, int y, int _width, int _height, float r,
 float g, float b, float a,
 Consumer<TextureDraw> texdModifier) {
 // TODO: Implement renderstrip
}

void Texture::setAlphaForeach(int red, int green, int blue, int alpha) {
 // TODO: Implement setAlphaForeach
}

void Texture::setCustomizedTexture() {
 // TODO: Implement setCustomizedTexture
}

void Texture::setNameOnly(const std::string &_name) {
 // TODO: Implement setNameOnly
}

void Texture::setRegion(int x, int y, int _width, int _height) {
 // TODO: Implement setRegion
}

Texture Texture::splitIcon() {
 // TODO: Implement splitIcon
 return nullptr;
}

Texture Texture::split(int xOffset, int yOffset, int _width, int _height) {
 // TODO: Implement split
 return nullptr;
}

Texture Texture::split(const std::string &_name, int xOffset, int yOffset,
 int _width, int _height) {
 // TODO: Implement split
 return nullptr;
}

std::string Texture::toString() {
 // TODO: Implement toString
 return "";
}

void Texture::saveMask(const std::string &_name) {
 // TODO: Implement saveMask
}

void Texture::saveToZomboidDirectory(const std::string &filename) {
 // TODO: Implement saveToZomboidDirectory
}

void Texture::saveToCurrentSavefileDirectory(const std::string &filename) {
 // TODO: Implement saveToCurrentSavefileDirectory
}

void Texture::saveOnRenderThread(const std::string &filename) {
 // TODO: Implement saveOnRenderThread
}

void Texture::loadMaskRegion(ByteBuffer cache) {
 // TODO: Implement loadMaskRegion
}

void Texture::saveMaskRegion(ByteBuffer cache) {
 // TODO: Implement saveMaskRegion
}

int Texture::getRealWidth() {
 // TODO: Implement getRealWidth
 return 0;
}

void Texture::setRealWidth(int _realWidth) {
 // TODO: Implement setRealWidth
}

int Texture::getRealHeight() {
 // TODO: Implement getRealHeight
 return 0;
}

void Texture::setRealHeight(int _realHeight) {
 // TODO: Implement setRealHeight
}

Vector2 Texture::getUVScale(Vector2 uvScale) {
 // TODO: Implement getUVScale
 return nullptr;
}

void Texture::syncReadSize() {
 // TODO: Implement syncReadSize
}

AssetType Texture::getType() {
 // TODO: Implement getType
 return {};
}

void Texture::onBeforeReady() {
 // TODO: Implement onBeforeReady
}

void Texture::collectAllIcons(String > map, String > mapFull) {
 // TODO: Implement collectAllIcons
}

} // namespace textures
} // namespace core
} // namespace zombie
