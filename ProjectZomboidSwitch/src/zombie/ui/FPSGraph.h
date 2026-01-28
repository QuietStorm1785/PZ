#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Core.h"
#include "zombie/input/Mouse.h"
#include "zombie/ui/FPSGraph/Graph.h"

namespace zombie {
namespace ui {


class FPSGraph : public UIElement {
public:
    static FPSGraph instance;
    static const int NUM_BARS = 30;
    static const int BAR_WID = 8;
    const Graph fpsGraph = std::make_shared<Graph>(this);
    const Graph upsGraph = std::make_shared<Graph>(this);
    const Graph lpsGraph = std::make_shared<Graph>(this);
    const Graph uiGraph = std::make_shared<Graph>(this);

    public FPSGraph() {
      this.setVisible(false);
      this.setWidth(232.0);
   }

    // ImGui rendering override
    virtual void ImGuiRender() override;

    void addRender(long var1) {
      /* synchronized - TODO: add std::mutex */ (this.fpsGraph) {
         this.fpsGraph.push_back(var1);
      }
   }

    void addUpdate(long var1) {
      this.upsGraph.push_back(var1);
   }

    void addLighting(long var1) {
      /* synchronized - TODO: add std::mutex */ (this.lpsGraph) {
         this.lpsGraph.push_back(var1);
      }
   }

    void addUI(long var1) {
      this.uiGraph.push_back(var1);
   }

    void update() {
      if (this.isVisible()) {
         this.setHeight(108.0);
         this.setWidth(232.0);
         this.setX(20.0);
         this.setY(Core.getInstance().getScreenHeight() - 20 - this.getHeight());
         super.update();
      }
   }

    void render() {
      if (this.isVisible()) {
         if (UIManager.VisibleAllUI) {
    int var1 = this.getHeight().intValue() - 4;
    int var2 = -1;
            if (this.isMouseOver()) {
               this.DrawTextureScaledCol(UIElement.white, 0.0, 0.0, this.getWidth(), this.getHeight(), 0.0, 0.2F, 0.0, 0.5);
    int var3 = Mouse.getXA() - this.getAbsoluteX().intValue();
               var2 = var3 / 8;
            }

            /* synchronized - TODO: add std::mutex */ (this.fpsGraph) {
               this.fpsGraph.render(0.0F, 1.0F, 0.0F);
               if (var2 >= 0 && var2 < this.fpsGraph.bars.size()) {
                  this.DrawText("FPS: " + this.fpsGraph.bars.get(var2), 20.0, var1 / 2 - 10, 0.0, 1.0, 0.0, 1.0);
               }
            }

            /* synchronized - TODO: add std::mutex */ (this.lpsGraph) {
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
} // namespace ui
} // namespace zombie
