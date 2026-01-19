#pragma once

#include <string>
#include <string_view>

namespace javax {
namespace imageio {

class ImageIO {
public:
 static void* read(std::string_view filename);
 static void write(void* image, std::string_view format, std::string_view filename);
};

} // namespace imageio
} // namespace javax
