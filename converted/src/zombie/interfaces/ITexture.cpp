#include "zombie/interfaces/ITexture.h"

namespace zombie {
namespace interfaces {

void ITexture::bind() {
 // TODO: Implement bind
}

void ITexture::bind(int unit) {
 // TODO: Implement bind
}

WrappedBuffer ITexture::getData() {
 // TODO: Implement getData
 return nullptr;
}

int ITexture::getHeight() {
 // TODO: Implement getHeight
 return 0;
}

int ITexture::getHeightHW() {
 // TODO: Implement getHeightHW
 return 0;
}

int ITexture::getID() {
 // TODO: Implement getID
 return 0;
}

int ITexture::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

int ITexture::getWidthHW() {
 // TODO: Implement getWidthHW
 return 0;
}

float ITexture::getXEnd() {
 // TODO: Implement getXEnd
 return 0;
}

float ITexture::getXStart() {
 // TODO: Implement getXStart
 return 0;
}

float ITexture::getYEnd() {
 // TODO: Implement getYEnd
 return 0;
}

float ITexture::getYStart() {
 // TODO: Implement getYStart
 return 0;
}

bool ITexture::isSolid() {
 // TODO: Implement isSolid
 return false;
}

void ITexture::makeTransp(int red, int green, int blue) {
 // TODO: Implement makeTransp
}

void ITexture::setAlphaForeach(int red, int green, int blue, int alpha) {
 // TODO: Implement setAlphaForeach
}

void ITexture::setData(ByteBuffer data) {
 // TODO: Implement setData
}

void ITexture::setMask(Mask mask) {
 // TODO: Implement setMask
}

void ITexture::setRegion(int x, int y, int width, int height) {
 // TODO: Implement setRegion
}

} // namespace interfaces
} // namespace zombie
