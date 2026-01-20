#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace core {
namespace profiling {


class TriggerGameProfilerFile {
public:
    bool discard;
    bool isRecording;
}
} // namespace profiling
} // namespace core
} // namespace zombie
