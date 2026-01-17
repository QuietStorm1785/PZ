#pragma once
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/input/Mouse.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class FPSGraph : public UIElement {
public:
  static FPSGraph instance;
  static const int NUM_BARS = 30;
  static const int BAR_WID = 8;
private
  final FPSGraph.Graph fpsGraph = new FPSGraph.Graph();
private
  final FPSGraph.Graph upsGraph = new FPSGraph.Graph();
private
  final FPSGraph.Graph lpsGraph = new FPSGraph.Graph();
private
  final FPSGraph.Graph uiGraph = new FPSGraph.Graph();

public
  FPSGraph() {
    this.setVisible(false);
    this.setWidth(232.0);
  }

  void addRender(long long0) {
    synchronized(this.fpsGraph) { this.fpsGraph.add(long0); }
  }

  void addUpdate(long long0) { this.upsGraph.add(long0); }

  void addLighting(long long0) {
    synchronized(this.lpsGraph) { this.lpsGraph.add(long0); }
  }

  void addUI(long long0) { this.uiGraph.add(long0); }

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
        int int0 = this.getHeight().intValue() - 4;
        int int1 = -1;
        if (this.isMouseOver()) {
          this.DrawTextureScaledCol(UIElement.white, 0.0, 0.0, this.getWidth(),
                                    this.getHeight(), 0.0, 0.2F, 0.0, 0.5);
          int int2 = Mouse.getXA() - this.getAbsoluteX().intValue();
          int1 = int2 / 8;
        }

        synchronized(this.fpsGraph) {
          this.fpsGraph.render(0.0F, 1.0F, 0.0F);
          if (int1 >= 0 && int1 < this.fpsGraph.bars.size()) {
            this.DrawText("FPS: " + this.fpsGraph.bars.get(int1), 20.0,
                          int0 / 2 - 10, 0.0, 1.0, 0.0, 1.0);
          }
        }

        synchronized(this.lpsGraph) {
          this.lpsGraph.render(1.0F, 1.0F, 0.0F);
          if (int1 >= 0 && int1 < this.lpsGraph.bars.size()) {
            this.DrawText("LPS: " + this.lpsGraph.bars.get(int1), 20.0,
                          int0 / 2 + 20, 1.0, 1.0, 0.0, 1.0);
          }
        }

        this.upsGraph.render(0.0F, 1.0F, 1.0F);
        if (int1 >= 0 && int1 < this.upsGraph.bars.size()) {
          this.DrawText("UPS: " + this.upsGraph.bars.get(int1), 20.0,
                        int0 / 2 + 5, 0.0, 1.0, 1.0, 1.0);
          this.DrawTextureScaledCol(UIElement.white, int1 * 8 + 4, 0.0, 1.0,
                                    this.getHeight(), 1.0, 1.0, 1.0, 0.5);
        }

        this.uiGraph.render(1.0F, 0.0F, 1.0F);
        if (int1 >= 0 && int1 < this.uiGraph.bars.size()) {
          this.DrawText("UI: " + this.uiGraph.bars.get(int1), 20.0,
                        int0 / 2 - 26, 1.0, 0.0, 1.0, 1.0);
        }
      }
    }
  }

private
  final class Graph {
  private
    final ArrayList<Long> times = std::make_unique<ArrayList<>>();
  private
    final ArrayList<Integer> bars = std::make_unique<ArrayList<>>();

    void add(long long0) {
      this.times.add(long0);
      this.bars.clear();
      long long1 = this.times.get(0);
      int int0 = 1;

      for (int int1 = 1; int1 < this.times.size(); int1++) {
        if (int1 != this.times.size() - 1 &&
            this.times.get(int1) - long1 <= 1000L) {
          int0++;
        } else {
          long long2 = (this.times.get(int1) - long1) / 1000L - 1L;

          for (int int2 = 0; int2 < long2; int2++) {
            this.bars.add(0);
          }

          this.bars.add(int0);
          int0 = 1;
          long1 = this.times.get(int1);
        }
      }

      while (this.bars.size() > 30) {
        int int3 = this.bars.get(0);

        for (int int4 = 0; int4 < int3; int4++) {
          this.times.remove(0);
        }

        this.bars.remove(0);
      }
    }

    void render(float float4, float float5, float float6) {
      if (!this.bars.isEmpty()) {
        float float0 = FPSGraph.this.getHeight().intValue() - 4;
        float float1 = FPSGraph.this.getHeight().intValue() - 2;
        int int0 = Math.max(PerformanceSettings.getLockFPS(),
                            PerformanceSettings.LightingFPS);
        uint8_t byte0 = 8;
        float float2 =
            float0 * ((float)Math.min(int0, this.bars.get(0)) / int0);

        for (int int1 = 1; int1 < this.bars.size() - 1; int1++) {
          float float3 =
              float0 * ((float)Math.min(int0, this.bars.get(int1)) / int0);
          SpriteRenderer.instance.renderline(
              nullptr, FPSGraph.this.getAbsoluteX().intValue() + byte0 - 8 + 4,
              FPSGraph.this.getAbsoluteY().intValue() + (int)(float1 - float2),
              FPSGraph.this.getAbsoluteX().intValue() + byte0 + 4,
              FPSGraph.this.getAbsoluteY().intValue() + (int)(float1 - float3),
              float4, float5, float6, 0.35F, 1);
          byte0 += 8;
          float2 = float3;
        }
      }
    }
  }
}
} // namespace ui
} // namespace zombie
