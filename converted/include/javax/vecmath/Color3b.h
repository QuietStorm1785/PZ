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


class Color3b : public Tuple3b {
public:
 static const long serialVersionUID = 6632576088353444794L;

 public Color3b(uint8_t byte0, uint8_t byte1, uint8_t byte2) {
 super(byte0, byte1, byte2);
 }

 public Color3b(byte[] bytes) {
 super(bytes);
 }

 public Color3b(Color3b color3b1) {
 super(color3b1);
 }

 public Color3b(Tuple3b tuple3b) {
 super(tuple3b);
 }

 public Color3b(Color color) {
 super((byte)color.getRed(), (byte)color.getGreen(), (byte)color.getBlue());
 }

 public Color3b() {
 }

 void set(Color color) {
 this->x = (byte)color.getRed();
 this->y = (byte)color.getGreen();
 this->z = (byte)color.getBlue();
 }

 Color get() {
 int int0 = this->x & 255;
 int int1 = this->y & 255;
 int int2 = this->z & 255;
 return new Color(int0, int1, int2);
 }
}
} // namespace vecmath
} // namespace javax
