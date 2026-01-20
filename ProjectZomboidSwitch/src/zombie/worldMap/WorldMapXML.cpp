#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include "zombie\worldMap/WorldMapXML.h"

namespace zombie {
namespace worldMap {

using boost::property_tree::ptree;

bool WorldMapXML::read(const std::string& var1, WorldMapData var2) {
    try {
        ptree tree;
        boost::property_tree::read_xml(var1, tree);
        
        // Check if root is "world"
        if (tree.get_child_optional("world")) {
            parseWorld(tree.get_child("world"), var2);
            return true;
        }
        return false;
    } catch (const std::exception& e) {
        // Log error
        return false;
    }
}

void WorldMapXML::parseWorld(const ptree& var1, WorldMapData var2) {
    // Iterate through child elements named "cell"
    for (const auto& child : var1) {
        if (child.first == "cell") {
            WorldMapCell cell = parseCell(child.second);
            // var2.m_cells.push_back(cell);
        }
    }
}

WorldMapCell WorldMapXML::parseCell(const ptree& var1) {
    WorldMapCell var2; // = std::make_shared<WorldMapCell>();
    // var2.m_x = var1.get<int>("<xmlattr>.x", 0);
    // var2.m_y = var1.get<int>("<xmlattr>.y", 0);
    
    // Iterate through features
    for (const auto& child : var1) {
        if (child.first == "feature") {
            // WorldMapFeature feature = parseFeature(var2, child.second);
            // var2.m_features.push_back(feature);
        }
    }
    return var2;
}

WorldMapFeature WorldMapXML::parseFeature(WorldMapCell var1, const ptree& var2) {
    WorldMapFeature var3; // = std::make_shared<WorldMapFeature>(var1);
    
    for (const auto& child : var2) {
        if (child.first == "geometry") {
            // WorldMapGeometry geom = parseGeometry(child.second);
            // var3.m_geometries.push_back(geom);
        }
        if (child.first == "properties") {
            parseFeatureProperties(child.second, var3);
        }
    }
    return var3;
}

void WorldMapXML::parseFeatureProperties(const ptree& var1, WorldMapFeature var2) {
    // m_properties.clear();
    
    for (const auto& child : var1) {
        if (child.first == "property") {
            // std::string name = m_sharedStrings.get(child.second.get<std::string>("<xmlattr>.name", ""));
            // std::string value = m_sharedStrings.get(child.second.get<std::string>("<xmlattr>.value", ""));
            // m_properties.put(name, value);
        }
    }
    // var2.m_properties = getOrCreateProperties(m_properties);
}

WorldMapProperties WorldMapXML::getOrCreateProperties(WorldMapProperties var1) {
    // TODO: Implement getOrCreateProperties with shared properties pool
    return var1;
}

WorldMapGeometry WorldMapXML::parseGeometry(const ptree& var1) {
    WorldMapGeometry var2; // = std::make_shared<WorldMapGeometry>();
    // var2.m_type = Type.valueOf(var1.get<std::string>("<xmlattr>.type", ""));
    
    for (const auto& child : var1) {
        if (child.first == "coordinates") {
            // WorldMapPoints points = std::make_shared<WorldMapPoints>();
            // parseGeometryCoordinates(child.second, points);
            // var2.m_points.push_back(points);
        }
    }
    // var2.calculateBounds();
    return var2;
}

void WorldMapXML::parseGeometryCoordinates(const ptree& var1, WorldMapPoints var2) {
    for (const auto& child : var1) {
        if (child.first == "point") {
            // WorldMapPoint point = parsePoint(child.second, m_point);
            // var2.push_back(point.x);
            // var2.push_back(point.y);
        }
    }
}

WorldMapPoint WorldMapXML::parsePoint(const ptree& var1, WorldMapPoint var2) {
    // var2.x = var1.get<int>("<xmlattr>.x", 0);
    // var2.y = var1.get<int>("<xmlattr>.y", 0);
    return var2;
}

} // namespace worldMap
} // namespace zombie
