#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "javax/xml/bind/annotation/XmlRootElement.h"

namespace zombie {
namespace characters {


class TriggerSetAnimationRecorderFile {
public:
    bool isRecording;
    bool discard;
}
} // namespace characters
} // namespace zombie
