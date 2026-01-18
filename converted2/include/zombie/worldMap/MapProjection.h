#pragma once
#include "org/joml/Vector2d.h"
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

class MapProjection {
public:
  static const double EARTH_RADIUS_METERS = 6378137.0;
  static const double EARTH_HALF_CIRCUMFERENCE_METERS = 2.0037508342789244E7;
  static const double EARTH_CIRCUMFERENCE_METERS = 4.007501668557849E7;
  static const double MAX_LATITUDE_DEGREES = 85.05112878;
  static const double LOG_2 = Math.log(2.0);

  static MapProjection.ProjectedMeters
  lngLatToProjectedMeters(MapProjection.LngLat lngLat) {
    MapProjection.ProjectedMeters projectedMeters =
        new MapProjection.ProjectedMeters();
    projectedMeters.x = lngLat.longitude * 2.0037508342789244E7 / 180.0;
    projectedMeters.y =
        Math.log(Math.tan((Math.PI / 4) + lngLat.latitude * Math.PI / 360.0)) *
        6378137.0;
    return projectedMeters;
  }

  static double metersPerTileAtZoom(int int0) {
    return 4.007501668557849E7 / (1 << int0);
  }

  static double metersPerPixelAtZoom(double double1, double double0) {
    return 4.007501668557849E7 / (exp2(double1) * double0);
  }

  static double zoomAtMetersPerPixel(double double0, double double1) {
    return log2(4.007501668557849E7 /);
  }

  static MapProjection.BoundingBox mapLngLatBounds() {
    return new MapProjection.BoundingBox(new Vector2d(-180.0, -85.05112878),
                                         new Vector2d(180.0, 85.05112878));
  }

  static MapProjection.BoundingBox mapProjectedMetersBounds() {
    MapProjection.BoundingBox boundingBox = mapLngLatBounds();
    return new MapProjection.BoundingBox(
        lngLatToProjectedMeters(
            new MapProjection.LngLat(boundingBox.min.x, boundingBox.min.y)),
        lngLatToProjectedMeters(
            new MapProjection.LngLat(boundingBox.max.x, boundingBox.max.y)));
  }

  static double exp2(double double0) { return Math.pow(2.0, double0); }

  static double log2(double double0) { return Math.log(double0) / LOG_2; }

public
  static final class BoundingBox {
    Vector2d min;
    Vector2d max;

  public
    BoundingBox(Vector2d vector2d0, Vector2d vector2d1) {
      this.min = vector2d0;
      this.max = vector2d1;
    }
  }

  public static final class LngLat {
    double longitude = 0.0;
    double latitude = 0.0;

  public
    LngLat(double double0, double double1) {
      this.longitude = double0;
      this.latitude = double1;
    }
  }

  public static final class ProjectedMeters extends Vector2d {
  }
}
} // namespace worldMap
} // namespace zombie
