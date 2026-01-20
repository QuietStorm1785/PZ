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


class PhysicalOggStream {
public:
    virtual ~PhysicalOggStream() = default;
    Collection getLogicalStreams();

    OggPage getOggPage(int var1);

    bool isOpen();

    void close();

    void setTime(long var1);

    bool isSeekable();
}
} // namespace ogg
} // namespace jarnbjo
} // namespace de
