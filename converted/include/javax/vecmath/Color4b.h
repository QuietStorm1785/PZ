#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Color.h"
#include <fstream>
#include <iostream>

namespace javax {
namespace vecmath {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Color4b : public Tuple4b {
public:
 static const long serialVersionUID = -105080578052502155L;

 public Color4b(uint8_t byte0, uint8_t byte1, uint8_t byte2, uint8_t byte3) {
 super(byte0, byte1, byte2, byte3);
 }

 public Color4b(byte[] bytes) {
 super(bytes);
 }

 public Color4b(Color4b color4b1) {
 super(color4b1);
 }

 public Color4b(Tuple4b tuple4b) {
 super(tuple4b);
 }

 public Color4b(Color color) {
 super((byte)color.getRed(), (byte)color.getGreen(), (byte)color.getBlue(), (byte)color.getAlpha());
 }

 public Color4b() {
 }

 void set(Color color) {
 this->x = (byte)color.getRed();
 this->y = (byte)color.getGreen();
 this->z = (byte)color.getBlue();
 this->w = (byte)color.getAlpha();
 }

 Color get() {
 int int0 = this->x & 255;
 int int1 = this->y & 255;
 int int2 = this->z & 255;
 int int3 = this->w & 255;
 return new Color(int0, int1, int2, int3);
 }
}
} // namespace vecmath
} // namespace javax
