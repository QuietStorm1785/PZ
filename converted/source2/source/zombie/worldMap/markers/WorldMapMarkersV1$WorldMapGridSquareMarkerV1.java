package zombie.worldMap.markers;

import zombie.worldMap.markers.WorldMapMarkersV1.WorldMapMarkerV1;

public final class WorldMapMarkersV1$WorldMapGridSquareMarkerV1 extends WorldMapMarkerV1 {
   final WorldMapGridSquareMarker m_gridSquareMarker;

   WorldMapMarkersV1$WorldMapGridSquareMarkerV1(WorldMapGridSquareMarker var1) {
      super(var1);
      this.m_gridSquareMarker = var1;
   }

   public void setBlink(boolean var1) {
      this.m_gridSquareMarker.setBlink(var1);
   }

   public void setMinScreenRadius(int var1) {
      this.m_gridSquareMarker.setMinScreenRadius(var1);
   }
}
