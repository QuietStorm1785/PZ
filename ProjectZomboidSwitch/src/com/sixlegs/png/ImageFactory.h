#pragma once

#include <memory>
#include <istream>
#include <opencv2/core.hpp>

namespace com {
namespace sixlegs {
namespace png {

class PngImage; // forward

// ImageFactory converts PNG image metadata + decoded pixel stream into a OpenCV image (cv::Mat).
// This is an incremental, C++-friendly reimplementation; full feature parity with the
// original Java version (source regions, subsampling, indexed palettes, gamma correction)
// will be implemented progressively.
class ImageFactory {
public:
    // Create an image from PNG metadata and pixel input stream. The stream should provide
    // raw, defiltered pixel data in row-major order according to the PNG image configuration.
    static cv::Mat createImage(PngImage& pngMeta, std::istream& pixelStream, const cv::Size& requestedSize);

private:
    // Internal helpers (to be implemented)
    static cv::Mat createColorModelImage(PngImage& pngMeta, const cv::Size& size);
};

} // namespace png
} // namespace sixlegs
} // namespace com
