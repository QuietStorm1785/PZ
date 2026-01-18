#include "zombie/core/textures/ImageData.h"

namespace zombie {
namespace core {
namespace textures {

public
ImageData::ImageData(TextureID texture, WrappedBuffer bb) {
 // TODO: Implement ImageData
 return nullptr;
}

public
ImageData::ImageData(const std::string &path) {
 // TODO: Implement ImageData
 return nullptr;
}

public
ImageData::ImageData(int _width, int _height) {
 // TODO: Implement ImageData
 return nullptr;
}

public
ImageData::ImageData(int _width, int _height, WrappedBuffer _data) {
 // TODO: Implement ImageData
 return nullptr;
}

public
ImageData::ImageData(BufferedInputStream b, bool bDoMask,
 Texture.PZFileformat format) {
 // TODO: Implement ImageData
 return nullptr;
}

public
ImageData::ImageData(InputStream b, bool bDoMask) {
 // TODO: Implement ImageData
 return nullptr;
}

ImageData ImageData::createSteamAvatar(long steamID) {
 // TODO: Implement createSteamAvatar
 return nullptr;
}

MipMapLevel ImageData::getData() {
 // TODO: Implement getData
 return nullptr;
}

void ImageData::makeTransp(uint8_t red, uint8_t green, uint8_t blue) {
 // TODO: Implement makeTransp
}

void ImageData::makeTransp(uint8_t red, uint8_t green, uint8_t blue,
 uint8_t alpha) {
 // TODO: Implement makeTransp
}

void ImageData::setData(BufferedImage image) {
 // TODO: Implement setData
}

void ImageData::setData(Raster rasterData) {
 // TODO: Implement setData
}

new ImageData::Exception() {
 // TODO: Implement Exception
 return nullptr;
}

new ImageData::Exception() {
 // TODO: Implement Exception
 return nullptr;
}

void ImageData::readObject(ObjectInputStream objectInputStream) {
 // TODO: Implement readObject
}

void ImageData::setData(Pcx pcx) {
 // TODO: Implement setData
}

new ImageData::Exception() {
 // TODO: Implement Exception
 return nullptr;
}

void ImageData::writeObject(ObjectOutputStream objectOutputStream) {
 // TODO: Implement writeObject
}

int ImageData::getHeight() {
 // TODO: Implement getHeight
 return 0;
}

int ImageData::getHeightHW() {
 // TODO: Implement getHeightHW
 return 0;
}

bool ImageData::isSolid() {
 // TODO: Implement isSolid
 return false;
}

int ImageData::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

int ImageData::getWidthHW() {
 // TODO: Implement getWidthHW
 return 0;
}

int ImageData::getMipMapCount() {
 // TODO: Implement getMipMapCount
 return 0;
}

MipMapLevel ImageData::getMipMapData(int idx) {
 // TODO: Implement getMipMapData
 return nullptr;
}

void ImageData::initMipMaps() {
 // TODO: Implement initMipMaps
}

void ImageData::dispose() {
 // TODO: Implement dispose
}

void ImageData::generateMipMaps() {
 // TODO: Implement generateMipMaps
}

void ImageData::scaleMipLevelMaxAlpha(MipMapLevel mipMapLevel1,
 MipMapLevel mipMapLevel0, int int6) {
 // TODO: Implement scaleMipLevelMaxAlpha
}

void ImageData::scaleMipLevelAverage(MipMapLevel mipMapLevel1,
 MipMapLevel mipMapLevel0, int int7) {
 // TODO: Implement scaleMipLevelAverage
}

int ImageData::calculateNumMips(int _widthHW, int _heightHW) {
 // TODO: Implement calculateNumMips
 return 0;
}

int ImageData::calculateNumMips(int int2) {
 // TODO: Implement calculateNumMips
 return 0;
}

void ImageData::performAlphaPadding() {
 // TODO: Implement performAlphaPadding
}

void ImageData::performAlphaPadding(MipMapLevel mipMapLevel) {
 // TODO: Implement performAlphaPadding
}

int ImageData::sampleNeighborPixelDiscard(ByteBuffer byteBuffer, int int3,
 int int1, int int2, int int0,
 int[] ints0, int[] ints1) {
 // TODO: Implement sampleNeighborPixelDiscard
 return 0;
}

int ImageData::getPixelDiscard(ByteBuffer byteBuffer, int int3, int int1,
 int int2, int int0, int[] ints) {
 // TODO: Implement getPixelDiscard
 return 0;
}

void ImageData::setPixel(ByteBuffer byteBuffer, int int3, int var2, int int1,
 int int2, int[] ints) {
 // TODO: Implement setPixel
}

int ImageData::getNextMipDimension(int dim) {
 // TODO: Implement getNextMipDimension
 return 0;
}

void ImageData::setMipmapDebugColors(int int0, int[] ints) {
 // TODO: Implement setMipmapDebugColors
}

} // namespace textures
} // namespace core
} // namespace zombie
