#pragma once
#include "org/w3c/dom/Element.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/SharedStrings.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace worldMap {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class WorldMapXML {
public:
  const SharedStrings m_sharedStrings = new SharedStrings();
  const WorldMapPoint m_point = new WorldMapPoint();
  const WorldMapProperties m_properties = new WorldMapProperties();
private
  final ArrayList<WorldMapProperties> m_sharedProperties =
      std::make_unique<ArrayList<>>();

  bool read(const std::string &string, WorldMapData worldMapData) {
    Element element = PZXmlUtil.parseXml(string);
    if (element.getNodeName() == "world")) {
        this.parseWorld(element, worldMapData);
        return true;
      }
    else {
      return false;
    }
  }

  void parseWorld(Element element, WorldMapData worldMapData) {
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapData,
        (elementx, worldMapDatax)->{
          if (!elementx.getNodeName() == "cell")) {
              DebugLog.General.warn("Warning: Unrecognised element '" +
                                    elementx.getNodeName());
            }
          else {
            WorldMapCell worldMapCell = this.parseCell(elementx);
            worldMapDatax.m_cells.add(worldMapCell);
          }
        });
  }

  WorldMapCell parseCell(Element element) {
    WorldMapCell worldMapCell = new WorldMapCell();
    worldMapCell.m_x = PZMath.tryParseInt(element.getAttribute("x"), 0);
    worldMapCell.m_y = PZMath.tryParseInt(element.getAttribute("y"), 0);
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapCell,
        (elementx, worldMapCell1)->{
          try {
            std::string string = elementx.getNodeName();
            if ("feature".equalsIgnoreCase(string)) {
              WorldMapFeature worldMapFeature =
                  this.parseFeature(worldMapCell, elementx);
              worldMapCell1.m_features.add(worldMapFeature);
            }
          } catch (Exception exception) {
            DebugLog.General.error("Error while parsing xml element: " +
                                   elementx.getNodeName());
            DebugLog.General.error(exception);
          }
        });
    return worldMapCell;
  }

  WorldMapFeature parseFeature(WorldMapCell worldMapCell, Element element) {
    WorldMapFeature worldMapFeature = new WorldMapFeature(worldMapCell);
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapFeature,
        (elementx, worldMapFeaturex)->{
          try {
            std::string string = elementx.getNodeName();
            if ("geometry".equalsIgnoreCase(string)) {
              WorldMapGeometry worldMapGeometry = this.parseGeometry(elementx);
              worldMapFeaturex.m_geometries.add(worldMapGeometry);
            }

            if ("properties".equalsIgnoreCase(string)) {
              this.parseFeatureProperties(elementx, worldMapFeaturex);
            }
          } catch (Exception exception) {
            DebugLog.General.error("Error while parsing xml element: " +
                                   elementx.getNodeName());
            DebugLog.General.error(exception);
          }
        });
    return worldMapFeature;
  }

  void parseFeatureProperties(Element element,
                              WorldMapFeature worldMapFeature) {
    this.m_properties.clear();
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapFeature,
        (elementx, var2x)->{
          try {
            std::string string0 = elementx.getNodeName();
            if ("property".equalsIgnoreCase(string0)) {
              std::string string1 =
                  this.m_sharedStrings.get(elementx.getAttribute("name"));
              std::string string2 =
                  this.m_sharedStrings.get(elementx.getAttribute("value"));
              this.m_properties.put(string1, string2);
            }
          } catch (Exception exception) {
            DebugLog.General.error("Error while parsing xml element: " +
                                   elementx.getNodeName());
            DebugLog.General.error(exception);
          }
        });
    worldMapFeature.m_properties =
        this.getOrCreateProperties(this.m_properties);
  }

  WorldMapProperties
  getOrCreateProperties(WorldMapProperties worldMapProperties0) {
    for (int int0 = 0; int0 < this.m_sharedProperties.size(); int0++) {
      if (this.m_sharedProperties.get(int0) == worldMapProperties0)) {
                return this.m_sharedProperties.get(int0);
            }
    }

    WorldMapProperties worldMapProperties1 = new WorldMapProperties();
    worldMapProperties1.putAll(worldMapProperties0);
    this.m_sharedProperties.add(worldMapProperties1);
    return worldMapProperties1;
  }

  WorldMapGeometry parseGeometry(Element element) {
    WorldMapGeometry worldMapGeometry = new WorldMapGeometry();
    worldMapGeometry.m_type =
        WorldMapGeometry.Type.valueOf(element.getAttribute("type"));
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapGeometry,
        (elementx, worldMapGeometryx)->{
          try {
            std::string string = elementx.getNodeName();
            if ("coordinates".equalsIgnoreCase(string)) {
              WorldMapPoints worldMapPoints = new WorldMapPoints();
              this.parseGeometryCoordinates(elementx, worldMapPoints);
              worldMapGeometryx.m_points.add(worldMapPoints);
            }
          } catch (Exception exception) {
            DebugLog.General.error("Error while parsing xml element: " +
                                   elementx.getNodeName());
            DebugLog.General.error(exception);
          }
        });
    worldMapGeometry.calculateBounds();
    return worldMapGeometry;
  }

  void parseGeometryCoordinates(Element element,
                                WorldMapPoints worldMapPoints) {
    Lambda.forEachFrom(
        PZXmlUtil::forEachElement, element, worldMapPoints,
        (elementx, worldMapPointsx)->{
          try {
            std::string string = elementx.getNodeName();
            if ("point".equalsIgnoreCase(string)) {
              WorldMapPoint worldMapPoint =
                  this.parsePoint(elementx, this.m_point);
              worldMapPointsx.add(worldMapPoint.x);
              worldMapPointsx.add(worldMapPoint.y);
            }
          } catch (Exception exception) {
            DebugLog.General.error("Error while parsing xml element: " +
                                   elementx.getNodeName());
            DebugLog.General.error(exception);
          }
        });
  }

  WorldMapPoint parsePoint(Element element, WorldMapPoint worldMapPoint) {
    worldMapPoint.x = PZMath.tryParseInt(element.getAttribute("x"), 0);
    worldMapPoint.y = PZMath.tryParseInt(element.getAttribute("y"), 0);
    return worldMapPoint;
  }
}
} // namespace worldMap
} // namespace zombie
