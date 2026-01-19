package zombie.worldMap;

import org.joml.Vector2d;
import zombie.worldMap.MapProjection.BoundingBox;
import zombie.worldMap.MapProjection.LngLat;
import zombie.worldMap.MapProjection.ProjectedMeters;

public final class MapProjection {
   public static final double EARTH_RADIUS_METERS = 6378137.0;
   public static final double EARTH_HALF_CIRCUMFERENCE_METERS = 2.0037508342789244E7;
   public static final double EARTH_CIRCUMFERENCE_METERS = 4.007501668557849E7;
   public static final double MAX_LATITUDE_DEGREES = 85.05112878;
   private static final double LOG_2 = Math.log(2.0);

   static ProjectedMeters lngLatToProjectedMeters(LngLat var0) {
      ProjectedMeters var1 = new ProjectedMeters();
      var1.x = var0.longitude * 2.0037508342789244E7 / 180.0;
      var1.y = Math.log(Math.tan((Math.PI / 4) + var0.latitude * Math.PI / 360.0)) * 6378137.0;
      return var1;
   }

   static double metersPerTileAtZoom(int var0) {
      return 4.007501668557849E7 / (1 << var0);
   }

   static double metersPerPixelAtZoom(double var0, double var2) {
      return 4.007501668557849E7 / (exp2(var0) * var2);
   }

   static double zoomAtMetersPerPixel(double var0, double var2) {
      return log2(4.007501668557849E7 / (var0 * var2));
   }

   static BoundingBox mapLngLatBounds() {
      return new BoundingBox(new Vector2d(-180.0, -85.05112878), new Vector2d(180.0, 85.05112878));
   }

   static BoundingBox mapProjectedMetersBounds() {
      BoundingBox var0 = mapLngLatBounds();
      return new BoundingBox(lngLatToProjectedMeters(new LngLat(var0.min.x, var0.min.y)), lngLatToProjectedMeters(new LngLat(var0.max.x, var0.max.y)));
   }

   public static double exp2(double var0) {
      return Math.pow(2.0, var0);
   }

   public static double log2(double var0) {
      return Math.log(var0) / LOG_2;
   }
}
