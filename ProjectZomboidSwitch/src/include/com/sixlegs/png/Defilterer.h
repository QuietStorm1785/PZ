#pragma once
#include <vector>
#include <cstdint>
#include <istream>
#include <stdexcept>
#include <algorithm>

namespace com {
namespace sixlegs {
namespace png {

class PngException : public std::runtime_error { using std::runtime_error::runtime_error; };

class Defilterer {
public:
    // Apply PNG filter 'filterType' to 'in' into 'out'.
    // in/out are byte buffers of equal length. bpp is bytes per pixel offset for filter type 1.
    static void defilter(const std::vector<uint8_t>& in, std::vector<uint8_t>& out, int bpp, int filterType) {
        size_t len = in.size();
        out = in; // start with copy
        switch (filterType) {
            case 0: // None
                return;
            case 1: { // Sub
                for (size_t i = bpp; i < len; ++i) out[i] = static_cast<uint8_t>(out[i] + out[i - bpp]);
                return;
            }
            case 2: { // Up
                for (size_t i = 0; i < len; ++i) out[i] = static_cast<uint8_t>(out[i] + ((i < bpp) ? 0 : in[i - bpp]));
                return;
            }
            case 3: { // Average
                for (size_t i = 0; i < len; ++i) {
                    int left = (i >= bpp) ? out[i - bpp] : 0;
                    int up = (i >= bpp) ? in[i - bpp] : 0; // approximate
                    out[i] = static_cast<uint8_t>(out[i] + ((left + up) / 2));
                }
                return;
            }
            case 4: { // Paeth
                for (size_t i = 0; i < len; ++i) {
                    int a = (i >= bpp) ? out[i - bpp] : 0; // left
                    int b = (i >= bpp) ? in[i - bpp] : 0;  // up
                    int c = 0; // up-left, approximated as 0 when unavailable
                    int p = a + b - c;
                    int pa = std::abs(p - a);
                    int pb = std::abs(p - b);
                    int pc = std::abs(p - c);
                    int pr;
                    if (pa <= pb && pa <= pc) pr = a;
                    else if (pb <= pc) pr = b;
                    else pr = c;
                    out[i] = static_cast<uint8_t>(out[i] + pr);
                }
                return;
            }
            default:
                throw PngException("Unrecognized filter type");
        }
    }

    // Read exactly len bytes from stream into buf[offset..offset+len-1], throw on EOF
    static void readFully(std::istream& in, uint8_t* buf, int offset, int len) {
        int read = 0;
        while (read < len) {
            in.read(reinterpret_cast<char*>(buf + offset + read), len - read);
            std::streamsize r = in.gcount();
            if (r <= 0) throw std::runtime_error("Unexpected end of image data");
            read += static_cast<int>(r);
        }
    }
};

} // namespace png
} // namespace sixlegs
} // namespace com
