#pragma once

#include <string>

namespace javax {
namespace imageio {

class ImageIO {
public:
 static void* read(const std::string& filename);
 static void write(void* image, const std::string& format, const std::string& filename);
};

} // namespace imageio
} // namespace javax
