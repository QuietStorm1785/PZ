package zombie.iso;

import zombie.core.profiling.PerformanceProfileProbe;

class IsoCell$s_performance$renderTiles$PperformRenderTilesLayer extends PerformanceProfileProbe {
   final PerformanceProfileProbe renderIsoWater = new PerformanceProfileProbe("renderIsoWater");
   final PerformanceProfileProbe renderFloor = new PerformanceProfileProbe("renderFloor");
   final PerformanceProfileProbe renderPuddles = new PerformanceProfileProbe("renderPuddles");
   final PerformanceProfileProbe renderShore = new PerformanceProfileProbe("renderShore");
   final PerformanceProfileProbe renderSnow = new PerformanceProfileProbe("renderSnow");
   final PerformanceProfileProbe renderBlood = new PerformanceProfileProbe("renderBlood");
   final PerformanceProfileProbe vegetationCorpses = new PerformanceProfileProbe("vegetationCorpses");
   final PerformanceProfileProbe renderFloorShading = new PerformanceProfileProbe("renderFloorShading");
   final PerformanceProfileProbe renderShadows = new PerformanceProfileProbe("renderShadows");
   final PerformanceProfileProbe luaOnPostFloorLayerDraw = new PerformanceProfileProbe("luaOnPostFloorLayerDraw");
   final PerformanceProfileProbe minusFloorCharacters = new PerformanceProfileProbe("minusFloorCharacters");

   IsoCell$s_performance$renderTiles$PperformRenderTilesLayer(String var1) {
      super(var1);
   }
}
