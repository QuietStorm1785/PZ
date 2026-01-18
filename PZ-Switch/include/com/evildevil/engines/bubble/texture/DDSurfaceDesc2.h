#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace com {
namespace evildevil {
namespace engines {
namespace bubble {
namespace texture {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DDSurfaceDesc2 {
public:
 const std::string DDS_IDENTIFIER = "DDS ";
 long identifier = 0L;
 std::string identifierString = "";
 long size = 0L;
 long flags = 0L;
 long height = 0L;
 long width = 0L;
 long pitchOrLinearSize = 0L;
 long depth = 0L;
 long mipMapCount = 0L;
 long reserved = 0L;
 DDPixelFormat pixelFormat = nullptr;
 DDSCaps2 caps2 = nullptr;
 int reserved2 = 0;

public
 DDSurfaceDesc2() {
 this->pixelFormat = std::make_unique<DDPixelFormat>();
 this->caps2 = std::make_unique<DDSCaps2>();
 }

 void setIdentifier(long long0) {
 this->identifier = long0;
 this->createIdentifierString();
 }

 void createIdentifierString() {
 byte[] bytes = new byte[]{
 (byte)this->identifier, (byte)(this->identifier >> 8),
 (byte)(this->identifier >> 16), (byte)(this->identifier >> 24)};
 this->identifierString = new String(bytes);
 if (!this->identifierString.equalsIgnoreCase("DDS ")) {
 throw TextureFormatException(
 "The DDS Identifier is wrong. Have to be \"DDS \"!");
 }
 }

 void setSize(long long0) {
 if (long0 != 124L) {
 throw TextureFormatException(
 "Wrong DDSurfaceDesc2 size. DDSurfaceDesc2 size must be 124!");
 } else {
 this->size = long0;
 }
 }

 void setFlags(long long0) {
 this->flags = long0;
 if ((long0 & 1L) != 1L || (long0 & 4096L) != 4096L || (long0 & 4L) != 4L ||
 (long0 & 2L) != 2L) {
 throw TextureFormatException(
 "One or more required flag bits are set wrong\nflags have to include "
 "\"DDSD_CAPS, DDSD_PIXELFORMAT, DDSD_WIDTH, DDSD_HEIGHT\"");
 }
 }

 void setHeight(long long0) { this->height = Math.abs(long0); }

 void setWidth(long long0) { this->width = long0; }

 void setPitchOrLinearSize(long long0) {
 this->pitchOrLinearSize = long0;
 this->pitchOrLinearSize =
 (this->width + 3L) / 4L * ((this->height + 3L) / 4L) * 16L;
 if (this->pitchOrLinearSize > 1000000L) {
 this->pitchOrLinearSize =
 (this->width + 3L) / 4L * ((this->height + 3L) / 4L) * 16L;
 }
 }

 void setDepth(long long0) { this->depth = long0; }

 void setMipMapCount(long long0) { this->mipMapCount = long0; }

 void setDDPixelFormat(DDPixelFormat dDPixelFormat) {
 if (dDPixelFormat.empty()) {
 throw NullPointerException(
 "DDPixelFormat can't be nullptr. DDSurfaceDesc2 needs a valid "
 "DDPixelFormat.");
 } else {
 this->pixelFormat = dDPixelFormat;
 }
 }

 DDPixelFormat getDDPixelformat() { return this->pixelFormat; }

 void setDDSCaps2(DDSCaps2 dDSCaps2) {
 if (dDSCaps2.empty()) {
 throw NullPointerException(
 "DDSCaps can't be nullptr. DDSurfaceDesc2 needs a valid DDSCaps2.");
 } else {
 this->caps2 = dDSCaps2;
 }
 }

 DDSCaps2 getDDSCaps2() { return this->caps2; }
}
} // namespace texture
} // namespace bubble
} // namespace engines
} // namespace evildevil
} // namespace com
