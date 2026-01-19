#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/w3c/dom/Element.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/util/Lambda.h"
#include "zombie/util/PZXmlParserException.h"
#include "zombie/util/PZXmlUtil.h"
#include "zombie/util/SharedStrings.h"
#include "zombie/worldMap/WorldMapGeometry/Type.h"

namespace zombie {
namespace worldMap {


class WorldMapXML {
:
    const SharedStrings m_sharedStrings = new SharedStrings();
    const WorldMapPoint m_point = new WorldMapPoint();
    const WorldMapProperties m_properties = new WorldMapProperties();
   private ArrayList<WorldMapProperties> m_sharedProperties = std::make_unique<ArrayList<>>();

    bool read(const std::string& var1, WorldMapData var2) {
    Element var3 = PZXmlUtil.parseXml(var1);
      if (var3.getNodeName() == "world")) {
         this.parseWorld(var3, var2);
    return true;
      } else {
    return false;
      }
   }

    void parseWorld(Element var1, WorldMapData var2) {
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var1, var2, (var1x, var2x) -> {
         if (!var1x.getNodeName() == "cell")) {
            DebugLog.General.warn("Warning: Unrecognised element '" + var1x.getNodeName());
         } else {
    WorldMapCell var3 = this.parseCell(var1x);
            var2x.m_cells.add(var3);
         }
      });
   }

    WorldMapCell parseCell(Element var1) {
    WorldMapCell var2 = new WorldMapCell();
      var2.m_x = PZMath.tryParseInt(var1.getAttribute("x"), 0);
      var2.m_y = PZMath.tryParseInt(var1.getAttribute("y"), 0);
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var1, var2, (var2x, var3) -> {
         try {
    std::string var4 = var2x.getNodeName();
            if ("feature".equalsIgnoreCase(var4)) {
    WorldMapFeature var5 = this.parseFeature(var2, var2x);
               var3.m_features.add(var5);
            }
         } catch (Exception var6) {
            DebugLog.General.error("Error while parsing xml element: " + var2x.getNodeName());
            DebugLog.General.error(var6);
         }
      });
    return var2;
   }

    WorldMapFeature parseFeature(WorldMapCell var1, Element var2) {
    WorldMapFeature var3 = new WorldMapFeature(var1);
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var2, var3, (var1x, var2x) -> {
         try {
    std::string var3x = var1x.getNodeName();
            if ("geometry".equalsIgnoreCase(var3x)) {
    WorldMapGeometry var4 = this.parseGeometry(var1x);
               var2x.m_geometries.add(var4);
            }

            if ("properties".equalsIgnoreCase(var3x)) {
               this.parseFeatureProperties(var1x, var2x);
            }
         } catch (Exception var5) {
            DebugLog.General.error("Error while parsing xml element: " + var1x.getNodeName());
            DebugLog.General.error(var5);
         }
      });
    return var3;
   }

    void parseFeatureProperties(Element var1, WorldMapFeature var2) {
      this.m_properties.clear();
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var1, var2, (var1x, var2x) -> {
         try {
    std::string var3 = var1x.getNodeName();
            if ("property".equalsIgnoreCase(var3)) {
    std::string var4 = this.m_sharedStrings.get(var1x.getAttribute("name"));
    std::string var5 = this.m_sharedStrings.get(var1x.getAttribute("value"));
               this.m_properties.put(var4, var5);
            }
         } catch (Exception var6) {
            DebugLog.General.error("Error while parsing xml element: " + var1x.getNodeName());
            DebugLog.General.error(var6);
         }
      });
      var2.m_properties = this.getOrCreateProperties(this.m_properties);
   }

    WorldMapProperties getOrCreateProperties(WorldMapProperties var1) {
      for (int var2 = 0; var2 < this.m_sharedProperties.size(); var2++) {
         if (this.m_sharedProperties.get(var2) == var1)) {
            return this.m_sharedProperties.get(var2);
         }
      }

    WorldMapProperties var3 = new WorldMapProperties();
      var3.putAll(var1);
      this.m_sharedProperties.add(var3);
    return var3;
   }

    WorldMapGeometry parseGeometry(Element var1) {
    WorldMapGeometry var2 = new WorldMapGeometry();
      var2.m_type = Type.valueOf(var1.getAttribute("type"));
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var1, var2, (var1x, var2x) -> {
         try {
    std::string var3 = var1x.getNodeName();
            if ("coordinates".equalsIgnoreCase(var3)) {
    WorldMapPoints var4 = new WorldMapPoints();
               this.parseGeometryCoordinates(var1x, var4);
               var2x.m_points.add(var4);
            }
         } catch (Exception var5) {
            DebugLog.General.error("Error while parsing xml element: " + var1x.getNodeName());
            DebugLog.General.error(var5);
         }
      });
      var2.calculateBounds();
    return var2;
   }

    void parseGeometryCoordinates(Element var1, WorldMapPoints var2) {
      Lambda.forEachFrom(PZXmlUtil::forEachElement, var1, var2, (var1x, var2x) -> {
         try {
    std::string var3 = var1x.getNodeName();
            if ("point".equalsIgnoreCase(var3)) {
    WorldMapPoint var4 = this.parsePoint(var1x, this.m_point);
               var2x.add(var4.x);
               var2x.add(var4.y);
            }
         } catch (Exception var5) {
            DebugLog.General.error("Error while parsing xml element: " + var1x.getNodeName());
            DebugLog.General.error(var5);
         }
      });
   }

    WorldMapPoint parsePoint(Element var1, WorldMapPoint var2) {
      var2.x = PZMath.tryParseInt(var1.getAttribute("x"), 0);
      var2.y = PZMath.tryParseInt(var1.getAttribute("y"), 0);
    return var2;
   }
}
} // namespace worldMap
} // namespace zombie
