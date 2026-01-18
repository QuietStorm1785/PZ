#include "com/sixlegs/png/PngImage.h"

namespace com {
namespace sixlegs {
namespace png {

public
PngImage::PngImage() {
  // TODO: Implement PngImage
  return nullptr;
}

public
PngImage::PngImage(PngConfig pngConfig) {
  // TODO: Implement PngImage
  return nullptr;
}

PngConfig PngImage::getConfig() {
  // TODO: Implement getConfig
  return nullptr;
}

BufferedImage PngImage::read(File file) {
  // TODO: Implement read
  return nullptr;
}

BufferedImage PngImage::read(InputStream inputStream, bool boolean0) {
  // TODO: Implement read
  return nullptr;
}

BufferedImage PngImage::createImage(InputStream inputStream,
                                    Dimension dimension) {
  // TODO: Implement createImage
  return nullptr;
}

bool PngImage::handlePass(BufferedImage var1, int var2) {
  // TODO: Implement handlePass
  return false;
}

bool PngImage::handleProgress(BufferedImage var1, float var2) {
  // TODO: Implement handleProgress
  return false;
}

void PngImage::handleWarning(PngException pngException) {
  // TODO: Implement handleWarning
}

int PngImage::getWidth() {
  // TODO: Implement getWidth
  return 0;
}

int PngImage::getHeight() {
  // TODO: Implement getHeight
  return 0;
}

int PngImage::getBitDepth() {
  // TODO: Implement getBitDepth
  return 0;
}

bool PngImage::isInterlaced() {
  // TODO: Implement isInterlaced
  return false;
}

int PngImage::getColorType() {
  // TODO: Implement getColorType
  return 0;
}

int PngImage::getTransparency() {
  // TODO: Implement getTransparency
  return 0;
}

int PngImage::getSamples() {
  // TODO: Implement getSamples
  return 0;
}

float PngImage::getGamma() {
  // TODO: Implement getGamma
  return 0;
}

return PngImage::createGammaTable() {
  // TODO: Implement createGammaTable
  return nullptr;
}

Color PngImage::getBackground() {
  // TODO: Implement getBackground
  return nullptr;
}

void *PngImage::getProperty(const std::string &string) {
  // TODO: Implement getProperty
  return nullptr;
}

void *PngImage::getProperty(const std::string &string, Class clazz,
                            bool boolean0) {
  // TODO: Implement getProperty
  return nullptr;
}

int PngImage::getInt(const std::string &string) {
  // TODO: Implement getInt
  return 0;
}

std::unordered_map PngImage::getProperties() {
  // TODO: Implement getProperties
  return {};
}

TextChunk PngImage::getTextChunk(const std::string &string) {
  // TODO: Implement getTextChunk
  return nullptr;
}

void PngImage::readChunk(int int0, DataInput dataInput, long var3, int int1) {
  // TODO: Implement readChunk
}

bool PngImage::isMultipleOK(int int0) {
  // TODO: Implement isMultipleOK
  return false;
}

void PngImage::assertRead() {
  // TODO: Implement assertRead
}

void PngImage::skipFully(InputStream inputStream, long long0) {
  // TODO: Implement skipFully
}

} // namespace png
} // namespace sixlegs
} // namespace com
