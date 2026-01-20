#pragma once

#include <opencv2/core.hpp>
#include <istream>
#include <vector>
#include <string>
#include <map>
#include <optional>
#include <vector>

#include <cstddef>

namespace com {
namespace sixlegs {
namespace png {

struct PngMetadata {
    int width = 0;
    int height = 0;
    int channels = 0;
    int depth = 0; // bits per channel (approx)
    std::map<std::string, std::string> textChunks;
    std::optional<double> gamma;
    std::optional<std::vector<uint8_t>> iccProfile;
    std::optional<std::vector<uint8_t>> palette; // raw palette bytes if present
    std::optional<std::vector<uint8_t>> transparency; // tRNS data
    // raw buffer size hint
    std::size_t rawSize = 0;
};

class OpenCvPngShim {
public:
    // Decode PNG data from a std::istream into a cv::Mat (unchanged depth & channels).
    // If meta is provided, basic metadata will be filled.
    static cv::Mat decode(std::istream& in, PngMetadata* meta = nullptr);

    // Convenience: decode from a byte buffer
    static cv::Mat decodeFromBytes(const std::vector<uint8_t>& buf, PngMetadata* meta = nullptr);
};

} // namespace png
} // namespace sixlegs
} // namespace com
