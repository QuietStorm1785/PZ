#include "com/sixlegs/png/OpenCvPngShim.h"
#include <opencv2/imgcodecs.hpp>
#include <iterator>
#include <png.h>
#include <cstring>

// Helper read callback for libpng when reading from an in-memory buffer
struct PngBufferReader {
    const uint8_t* data;
    size_t size;
    size_t offset;
};

static void pngReadCallback(png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead) {
    PngBufferReader* reader = reinterpret_cast<PngBufferReader*>(png_get_io_ptr(png_ptr));
    if (!reader) {
        png_error(png_ptr, "Invalid read buffer");
        return;
    }
    if (reader->offset + byteCountToRead > reader->size) {
        // Ask libpng to signal error
        png_error(png_ptr, "Read beyond end of buffer");
        return;
    }
    std::memcpy(outBytes, reader->data + reader->offset, byteCountToRead);
    reader->offset += byteCountToRead;
}

// Extract selected metadata (text chunks, gamma, icc, palette, tRNS) using libpng
static void extractMetadataFromBuffer(const std::vector<uint8_t>& buf, PngMetadata* meta) {
    if (!meta) return;
    if (buf.size() < 8) return;
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
    if (!png_ptr) return;
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) { png_destroy_read_struct(&png_ptr, nullptr, nullptr); return; }
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
        return;
    }

    PngBufferReader reader{ buf.data(), buf.size(), 0 };
    png_set_read_fn(png_ptr, &reader, pngReadCallback);

    // Read info only
    png_read_info(png_ptr, info_ptr);

    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type, compression_type, filter_method;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_method);
    meta->width = static_cast<int>(width);
    meta->height = static_cast<int>(height);
    meta->depth = bit_depth;
    // approximate channels from color_type
    int channels = png_get_channels(png_ptr, info_ptr);
    meta->channels = channels;

    // text chunks
    png_textp text_ptr = nullptr;
    int num_text = 0;
    if (png_get_text(png_ptr, info_ptr, &text_ptr, &num_text) && num_text > 0 && text_ptr) {
        for (int i = 0; i < num_text; ++i) {
            std::string key = text_ptr[i].key ? text_ptr[i].key : std::string();
            std::string text = text_ptr[i].text ? text_ptr[i].text : std::string();
            if (!key.empty()) meta->textChunks[key] = text;
        }
    }

    // gamma
    double gamma_val;
    if (png_get_gAMA(png_ptr, info_ptr, &gamma_val) == 1) {
        meta->gamma = gamma_val;
    }

    // iCCP
    png_charp name = nullptr;
    int compression_type;
    png_bytep profile = nullptr;
    png_uint_32 profile_len = 0;
    if (png_get_iCCP(png_ptr, info_ptr, &name, &compression_type, &profile, &profile_len) && profile && profile_len > 0) {
        meta->iccProfile = std::vector<uint8_t>(profile, profile + profile_len);
    }

    // PLTE palette
    png_colorp palette = nullptr;
    int num_palette = 0;
    if (png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette) && palette && num_palette > 0) {
        meta->palette = std::vector<uint8_t>(num_palette * 3);
        for (int i = 0; i < num_palette; ++i) {
            (*meta->palette)[i*3 + 0] = palette[i].red;
            (*meta->palette)[i*3 + 1] = palette[i].green;
            (*meta->palette)[i*3 + 2] = palette[i].blue;
        }
    }

    // tRNS
    png_bytep trans = nullptr;
    int num_trans = 0;
    png_color_16p trans_values = nullptr;
    if (png_get_tRNS(png_ptr, info_ptr, &trans, &num_trans, &trans_values)) {
        if (trans && num_trans > 0) {
            meta->transparency = std::vector<uint8_t>(trans, trans + num_trans);
        }
    }

    meta->rawSize = buf.size();

    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

namespace com {
namespace sixlegs {
namespace png {

cv::Mat OpenCvPngShim::decode(std::istream& in, PngMetadata* meta) {
    // Read all bytes from stream
    std::vector<uint8_t> buf((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    return decodeFromBytes(buf, meta);
}

cv::Mat OpenCvPngShim::decodeFromBytes(const std::vector<uint8_t>& buf, PngMetadata* meta) {
    if (buf.empty()) return {};
    // extract metadata first (optional)
    if (meta) extractMetadataFromBuffer(buf, meta);
    cv::Mat data(1, static_cast<int>(buf.size()), CV_8U, const_cast<uint8_t*>(buf.data()));
    cv::Mat img = cv::imdecode(data, cv::IMREAD_UNCHANGED);
    if (img.empty()) return img;
    if (meta) {
        meta->width = img.cols;
        meta->height = img.rows;
        meta->channels = img.channels();
        meta->depth = img.elemSize1() * 8;
    }
    return img;
}

} // namespace png
} // namespace sixlegs
} // namespace com
