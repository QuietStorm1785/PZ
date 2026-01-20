#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <fstream>
#include <iostream>

namespace de {
namespace jarnbjo {
namespace ogg {


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
