#pragma once

#include <memory>
#include <string>
#include <cstdint>

namespace java {
namespace awt {
namespace image {

class BufferedImage {
public:
 // Image types
 static const int TYPE_INT_RGB = 1;
 static const int TYPE_INT_ARGB = 2;
 static const int TYPE_INT_ARGB_PRE = 3;
 static const int TYPE_3BYTE_BGR = 4;
 static const int TYPE_4BYTE_ABGR = 6;

 BufferedImage(int width, int height, int imageType);
 virtual ~BufferedImage() = default;

 int getWidth() const { return width_; }
 int getHeight() const { return height_; }
 int getType() const { return type_; }

 // Pixel manipulation
 int getRGB(int x, int y) const;
 void setRGB(int x, int y, int rgb);

 // Data access
 int* getData() { return data_.get(); }
 const int* getData() const { return data_.get(); }

private:
 int width_;
 int height_;
 int type_;
 std::unique_ptr<int[]> data_;
};

} // namespace image
} // namespace awt
} // namespace java
