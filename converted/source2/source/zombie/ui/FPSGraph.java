package zombie.ui;

import zombie.core.Core;
import zombie.input.Mouse;
import zombie.ui.FPSGraph.Graph;

public final class FPSGraph extends UIElement {
   public static FPSGraph instance;
   private static final int NUM_BARS = 30;
   private static final int BAR_WID = 8;
   private final Graph fpsGraph = new Graph(this);
   private final Graph upsGraph = new Graph(this);
   private final Graph lpsGraph = new Graph(this);
   private final Graph uiGraph = new Graph(this);

   public FPSGraph() {
      this.setVisible(false);
      this.setWidth(232.0);
   }

   public void addRender(long var1) {
      synchronized (this.fpsGraph) {
         this.fpsGraph.add(var1);
      }
   }

   public void addUpdate(long var1) {
      this.upsGraph.add(var1);
   }

   public void addLighting(long var1) {
      synchronized (this.lpsGraph) {
         this.lpsGraph.add(var1);
      }
   }

   public void addUI(long var1) {
      this.uiGraph.add(var1);
   }

   public void update() {
      if (this.isVisible()) {
         this.setHeight(108.0);
         this.setWidth(232.0);
         this.setX(20.0);
         this.setY(Core.getInstance().getScreenHeight() - 20 - this.getHeight());
         super.update();
      }
   }

   public void render() {
      if (this.isVisible()) {
         if (UIManager.VisibleAllUI) {
            int var1 = this.getHeight().intValue() - 4;
            int var2 = -1;
            if (this.isMouseOver()) {
               this.DrawTextureScaledCol(UIElement.white, 0.0, 0.0, this.getWidth(), this.getHeight(), 0.0, 0.2F, 0.0, 0.5);
               int var3 = Mouse.getXA() - this.getAbsoluteX().intValue();
               var2 = var3 / 8;
            }

            synchronized (this.fpsGraph) {
               this.fpsGraph.render(0.0F, 1.0F, 0.0F);
               if (var2 >= 0 && var2 < this.fpsGraph.bars.size()) {
                  this.DrawText("FPS: " + this.fpsGraph.bars.get(var2), 20.0, var1 / 2 - 10, 0.0, 1.0, 0.0, 1.0);
               }
            }

            synchronized (this.lpsGraph) {
               this.lpsGraph.render(1.0F, 1.0F, 0.0F);
               if (var2 >= 0 && var2 < this.lpsGraph.bars.size()) {
                  this.DrawText("LPS: " + this.lpsGraph.bars.get(var2), 20.0, var1 / 2 + 20, 1.0, 1.0, 0.0, 1.0);
               }
            }

            this.upsGraph.render(0.0F, 1.0F, 1.0F);
            if (var2 >= 0 && var2 < this.upsGraph.bars.size()) {
               this.DrawText("UPS: " + this.upsGraph.bars.get(var2), 20.0, var1 / 2 + 5, 0.0, 1.0, 1.0, 1.0);
               this.DrawTextureScaledCol(UIElement.white, var2 * 8 + 4, 0.0, 1.0, this.getHeight(), 1.0, 1.0, 1.0, 0.5);
            }

            this.uiGraph.render(1.0F, 0.0F, 1.0F);
            if (var2 >= 0 && var2 < this.uiGraph.bars.size()) {
               this.DrawText("UI: " + this.uiGraph.bars.get(var2), 20.0, var1 / 2 - 26, 1.0, 0.0, 1.0, 1.0);
            }
         }
      }
   }
}
