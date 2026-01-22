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


class AnimStateTriggerXmlFile {
public:
    bool forceAnim;
    std::string animSet;
    std::string stateName;
    std::string nodeName;
    bool setScalarValues;
    std::string scalarValue;
    std::string scalarValue2;
}
} // namespace characters
} // namespace zombie
