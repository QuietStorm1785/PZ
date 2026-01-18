#include "zombie/worldMap/ImagePyramid.h"

namespace zombie {
namespace worldMap {

void ImagePyramid::setDirectory(const std::string &directory) {
  // TODO: Implement setDirectory
}

void ImagePyramid::setZipFile(const std::string &zipFile) {
  // TODO: Implement setZipFile
}

Texture ImagePyramid::getImage(int x, int y, int z) {
  // TODO: Implement getImage
  return nullptr;
}

TextureID ImagePyramid::getTexture(int x, int y, int z) {
  // TODO: Implement getTexture
  return nullptr;
}

void ImagePyramid::replaceTextureData(
    ImagePyramid.PyramidTexture pyramidTexture, ImageData imageData) {
  // TODO: Implement replaceTextureData
}

void ImagePyramid::generateFiles(const std::string &imageFile,
                                 const std::string &outputDirectory) {
  // TODO: Implement generateFiles
}

FileSystem ImagePyramid::openZipFile() {
  // TODO: Implement openZipFile
  return nullptr;
}

void ImagePyramid::generateZip(const std::string &imageFile,
                               const std::string &zipFile) {
  // TODO: Implement generateZip
}

BufferedImage ImagePyramid::getBufferedImage(MipMapLevel mipMapLevel, int int3,
                                             int int2, int int0) {
  // TODO: Implement getBufferedImage
  return nullptr;
}

void ImagePyramid::writeImageToFile(BufferedImage bufferedImage,
                                    const std::string &string, int int2,
                                    int int1, int int0) {
  // TODO: Implement writeImageToFile
}

void ImagePyramid::writeImageToZip(BufferedImage bufferedImage,
                                   ZipOutputStream zipOutputStream, int int1,
                                   int int0, int int2) {
  // TODO: Implement writeImageToZip
}

void ImagePyramid::resetRequestNumbers() {
  // TODO: Implement resetRequestNumbers
}

void ImagePyramid::readInfoFile() {
  // TODO: Implement readInfoFile
}

void ImagePyramid::destroy() {
  // TODO: Implement destroy
}

} // namespace worldMap
} // namespace zombie
