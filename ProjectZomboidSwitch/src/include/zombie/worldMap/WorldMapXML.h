#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/worldMap/WorldMapGeometry/Type.h"

namespace zombie {
namespace worldMap {

using boost::property_tree::ptree;

class WorldMapXML {
public:
    const SharedStrings m_sharedStrings = std::make_shared<SharedStrings>();
    const WorldMapPoint m_point = std::make_shared<WorldMapPoint>();
    const WorldMapProperties m_properties = std::make_shared<WorldMapProperties>();
   private const std::vector<WorldMapProperties> m_sharedProperties = std::make_unique<std::vector<>>();

    bool read(const std::string& var1, WorldMapData var2);
    void parseWorld(const ptree& var1, WorldMapData var2);
    WorldMapCell parseCell(const ptree& var1);
    WorldMapFeature parseFeature(WorldMapCell var1, const ptree& var2);
    void parseFeatureProperties(const ptree& var1, WorldMapFeature var2);
    WorldMapProperties getOrCreateProperties(WorldMapProperties var1);
    WorldMapGeometry parseGeometry(const ptree& var1);
    void parseGeometryCoordinates(const ptree& var1, WorldMapPoints var2);
    WorldMapPoint parsePoint(const ptree& var1, WorldMapPoint var2);
}
} // namespace worldMap
} // namespace zombie
