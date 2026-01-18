#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"

namespace org {
namespace lwjglx {
namespace util {
namespace glu {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class Quadric {
public:
 int drawStyle = 100012;
 int orientation = 100020;
 bool textureFlag = false;
 int normals = 100000;

 void normal3f(float float3, float float2, float float1) {
 float float0 = (float)Math.sqrt(float3 * float3 + float2 * float2 + float1 * float1);
 if (float0 > 1.0E-5F) {
 float3 /= float0;
 float2 /= float0;
 float1 /= float0;
 }

 GL11.glNormal3f(float3, float2, float1);
 }

 void setDrawStyle(int int0) {
 this->drawStyle = int0;
 }

 void setNormals(int int0) {
 this->normals = int0;
 }

 void setOrientation(int int0) {
 this->orientation = int0;
 }

 void setTextureFlag(bool boolean0) {
 this->textureFlag = boolean0;
 }

 int getDrawStyle() {
 return this->drawStyle;
 }

 int getNormals() {
 return this->normals;
 }

 int getOrientation() {
 return this->orientation;
 }

 bool getTextureFlag() {
 return this->textureFlag;
 }

 void TXTR_COORD(float float0, float float1) {
 if (this->textureFlag) {
 GL11.glTexCoord2f(float0, float1);
 }
 }

 float sin(float float0) {
 return (float)Math.sin(float0);
 }

 float cos(float float0) {
 return (float)Math.cos(float0);
 }
}
} // namespace glu
} // namespace util
} // namespace lwjglx
} // namespace org
