#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

namespace zombie {
namespace popman {


class ZombieTriggerXmlFile {
public:
    int spawnHorde = 0;
    bool setDebugLoggingEnabled = false;
    bool bDebugLoggingEnabled = false;
}
} // namespace popman
} // namespace zombie
