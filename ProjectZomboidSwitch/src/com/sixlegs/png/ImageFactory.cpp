#include "com/sixlegs/png/ImageFactory.h"
#include "com/sixlegs/png/OpenCvPngShim.h"

namespace com {
namespace sixlegs {
namespace png {

cv::Mat ImageFactory::createImage(PngImage& pngMeta, std::istream& pixelStream, const cv::Size& requestedSize) {
    PngMetadata meta;
    cv::Mat img = OpenCvPngShim::decode(pixelStream, &meta);
    // If requested size differs, resize (nearest) — preserve channels
    if (!img.empty() && (img.cols != requestedSize.width || img.rows != requestedSize.height)) {
        cv::Mat resized;
        cv::resize(img, resized, requestedSize);
        return resized;
    }
    return img;
}

cv::Mat ImageFactory::createColorModelImage(PngImage& pngMeta, const cv::Size& size) {
    // Placeholder: in this shim, color model handling is left to OpenCV decode.
    return cv::Mat();
}

} // namespace png
} // namespace sixlegs
} // namespace com
#include <memory>
#include "com/sixlegs/png/ImageFactory.h"

namespace com {
namespace sixlegs {
namespace png {

BufferedImage ImageFactory::createImage(PngImage var0, InputStream var1) {
    // TODO: Implement createImage
    return nullptr;
}

return ImageFactory::createImage(std::make_shared<Dimension>(var0.getWidth() {
    // TODO: Implement createImage
    return nullptr;
}

BufferedImage ImageFactory::createImage(PngImage var0, InputStream var1, Dimension var2) {
    // TODO: Implement createImage
    return nullptr;
}

int ImageFactory::calcSubsamplingSize(int var0, int var1, int var2, char var3) {
    // TODO: Implement calcSubsamplingSize
    return 0;
}

bool ImageFactory::isIndexed(PngImage var0) {
    // TODO: Implement isIndexed
    return false;
}

ColorModel ImageFactory::createColorModel(PngImage var0, short[] var1, bool var2) {
    // TODO: Implement createColorModel
    return nullptr;
}

void ImageFactory::applyGamma(byte[] var0, short[] var1) {
    // TODO: Implement applyGamma
}

} // namespace png
} // namespace sixlegs
} // namespace com
