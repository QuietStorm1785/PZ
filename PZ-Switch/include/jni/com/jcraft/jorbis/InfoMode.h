#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace jcraft {
namespace jorbis {

class InfoMode {
:
    int blockflag;
    int mapping;
    int transformtype;
    int windowtype;
}
} // namespace jorbis
} // namespace jcraft
} // namespace com
