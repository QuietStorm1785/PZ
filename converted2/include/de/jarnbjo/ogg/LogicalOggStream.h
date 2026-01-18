#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace de {
namespace jarnbjo {
namespace ogg {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class LogicalOggStream {
public:
  virtual ~LogicalOggStream() = default;
  std::string FORMAT_UNKNOWN = "application/octet-stream";
  std::string FORMAT_VORBIS = "audio/x-vorbis";
  std::string FORMAT_FLAC = "audio/x-flac";
  std::string FORMAT_THEORA = "video/x-theora";

  OggPage getNextOggPage();

  byte[] getNextOggPacket() throws OggFormatException, IOException;

  bool isOpen();

  void close();

  void reset();

  long getMaximumGranulePosition();

  void setTime(long var1);

  long getTime();

  std::string getFormat();
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
