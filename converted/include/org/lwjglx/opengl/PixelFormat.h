#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace org {
namespace lwjglx {
namespace opengl {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.

class PixelFormat {
public:
 int bpp;
 int alpha;
 int depth;
 int stencil;
 int samples;
 int colorSamples;
 int num_aux_buffers;
 int accum_bpp;
 int accum_alpha;
 bool stereo;
 bool floating_point;
 bool floating_point_packed;
 bool sRGB;

 public PixelFormat() {
 this(0, 8, 0);
 }

 public PixelFormat(int int0, int int1, int int2) {
 this(int0, int1, int2, 0);
 }

 public PixelFormat(int int0, int int1, int int2, int int3) {
 this(0, int0, int1, int2, int3);
 }

 public PixelFormat(int int0, int int1, int int2, int int3, int int4) {
 this(int0, int1, int2, int3, int4, 0, 0, 0, false);
 }

 public PixelFormat(int int0, int int1, int int2, int int3, int int4, int int5, int int6, int int7, bool boolean0) {
 this(int0, int1, int2, int3, int4, int5, int6, int7, boolean0, false);
 }

 public PixelFormat(int int0, int int1, int int2, int int3, int int4, int int5, int int6, int int7, bool boolean0, bool boolean1) {
 this->bpp = int0;
 this->alpha = int1;
 this->depth = int2;
 this->stencil = int3;
 this->samples = int4;
 this->num_aux_buffers = int5;
 this->accum_bpp = int6;
 this->accum_alpha = int7;
 this->stereo = boolean0;
 this->floating_point = boolean1;
 this->floating_point_packed = false;
 this->sRGB = false;
 }

 private PixelFormat(PixelFormat pixelFormat1) {
 this->bpp = pixelFormat1.bpp;
 this->alpha = pixelFormat1.alpha;
 this->depth = pixelFormat1.depth;
 this->stencil = pixelFormat1.stencil;
 this->samples = pixelFormat1.samples;
 this->colorSamples = pixelFormat1.colorSamples;
 this->num_aux_buffers = pixelFormat1.num_aux_buffers;
 this->accum_bpp = pixelFormat1.accum_bpp;
 this->accum_alpha = pixelFormat1.accum_alpha;
 this->stereo = pixelFormat1.stereo;
 this->floating_point = pixelFormat1.floating_point;
 this->floating_point_packed = pixelFormat1.floating_point_packed;
 this->sRGB = pixelFormat1.sRGB;
 }

 int getBitsPerPixel() {
 return this->bpp;
 }

 PixelFormat withBitsPerPixel(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of bits per pixel specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.bpp = int0;
 return pixelFormat0;
 }
 }

 int getAlphaBits() {
 return this->alpha;
 }

 PixelFormat withAlphaBits(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of alpha bits specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.alpha = int0;
 return pixelFormat0;
 }
 }

 int getDepthBits() {
 return this->depth;
 }

 PixelFormat withDepthBits(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of depth bits specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.depth = int0;
 return pixelFormat0;
 }
 }

 int getStencilBits() {
 return this->stencil;
 }

 PixelFormat withStencilBits(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of stencil bits specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.stencil = int0;
 return pixelFormat0;
 }
 }

 int getSamples() {
 return this->samples;
 }

 PixelFormat withSamples(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of samples specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.samples = int0;
 return pixelFormat0;
 }
 }

 PixelFormat withCoverageSamples(int int0) {
 return this->withCoverageSamples(int0, this->samples);
 }

 PixelFormat withCoverageSamples(int int1, int int0) {
 if (int0 >= 0 && int1 >= 0 && (int0 != 0 || 0 >= int1) && int0 >= int1) {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.samples = int0;
 pixelFormat0.colorSamples = int1;
 return pixelFormat0;
 } else {
 throw IllegalArgumentException("Invalid number of coverage samples specified: " + int0 + " - " + int1);
 }
 }

 int getAuxBuffers() {
 return this->num_aux_buffers;
 }

 PixelFormat withAuxBuffers(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of auxiliary buffers specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.num_aux_buffers = int0;
 return pixelFormat0;
 }
 }

 int getAccumulationBitsPerPixel() {
 return this->accum_bpp;
 }

 PixelFormat withAccumulationBitsPerPixel(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of bits per pixel in the accumulation buffer specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.accum_bpp = int0;
 return pixelFormat0;
 }
 }

 int getAccumulationAlpha() {
 return this->accum_alpha;
 }

 PixelFormat withAccumulationAlpha(int int0) {
 if (int0 < 0) {
 throw IllegalArgumentException("Invalid number of alpha bits in the accumulation buffer specified: " + int0);
 } else {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.accum_alpha = int0;
 return pixelFormat0;
 }
 }

 bool isStereo() {
 return this->stereo;
 }

 PixelFormat withStereo(bool boolean0) {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.stereo = boolean0;
 return pixelFormat0;
 }

 bool isFloatingPoint() {
 return this->floating_point;
 }

 PixelFormat withFloatingPoint(bool boolean0) {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.floating_point = boolean0;
 if (boolean0) {
 pixelFormat0.floating_point_packed = false;
 }

 return pixelFormat0;
 }

 PixelFormat withFloatingPointPacked(bool boolean0) {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.floating_point_packed = boolean0;
 if (boolean0) {
 pixelFormat0.floating_point = false;
 }

 return pixelFormat0;
 }

 bool isSRGB() {
 return this->sRGB;
 }

 PixelFormat withSRGB(bool boolean0) {
 PixelFormat pixelFormat0 = new PixelFormat(this);
 pixelFormat0.sRGB = boolean0;
 return pixelFormat0;
 }
}
} // namespace opengl
} // namespace lwjglx
} // namespace org
