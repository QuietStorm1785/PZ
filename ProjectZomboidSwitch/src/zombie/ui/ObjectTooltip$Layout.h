#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/ui/ObjectTooltip/LayoutItem.h"
#include <algorithm>

namespace zombie {
namespace ui {


class ObjectTooltip {
public:
   public std::vector<LayoutItem> items = std::make_unique<std::vector<>>();
    int minLabelWidth;
    int minValueWidth;
   public ObjectTooltip$Layout next;
    int nextPadY;
   private static std::stack<LayoutItem> freeItems = std::make_unique<std::stack<>>();

    LayoutItem addItem() {
    LayoutItem var1 = nullptr;
      if (freeItems.empty()) {
         var1 = std::make_unique<LayoutItem>();
      } else {
         var1 = freeItems.pop();
      }

      var1.reset();
      this.items.push_back(var1);
    return var1;
   }

    void setMinLabelWidth(int var1) {
      this.minLabelWidth = var1;
   }

    void setMinValueWidth(int var1) {
      this.minValueWidth = var1;
   }

    int render(int var1, int var2, ObjectTooltip var3) {
    int var4 = this.minLabelWidth;
    int var5 = this.minValueWidth;
    int var6 = this.minValueWidth;
    int var7 = 0;
    int var8 = 0;
    uint8_t var9 = 8;
    int var10 = 0;

      for (int var11 = 0; var11 < this.items.size(); var11++) {
    LayoutItem var12 = this.items.get(var11);
         var12.calcSizes();
         if (var12.hasValue) {
            var4 = Math.max(var4, var12.labelWidth);
            var5 = Math.max(var5, var12.valueWidth);
            var6 = Math.max(var6, var12.valueWidthRight);
            var7 = Math.max(var7, var12.progressWidth);
            var10 = Math.max(var10, Math.max(var12.labelWidth, this.minLabelWidth) + var9);
            var8 = Math.max(var8, var4 + var9 + Math.max(Math.max(var5, var6), var7));
         } else {
            var4 = Math.max(var4, var12.labelWidth);
            var8 = Math.max(var8, var12.labelWidth);
         }
      }

      if (var1 + var8 + var3.padRight > var3.width) {
         var3.setWidth(var1 + var8 + var3.padRight);
      }

      for (int var13 = 0; var13 < this.items.size(); var13++) {
    LayoutItem var14 = this.items.get(var13);
         var14.render(var1, var2, var10, var6, var3);
         var2 += var14.height;
      }

      return this.next != nullptr ? this.next.render(var1, var2 + this.next.nextPadY, var3) : var2;
   }

    void free() {
      freeItems.addAll(this.items);
      this.items.clear();
      this.minLabelWidth = 0;
      this.minValueWidth = 0;
      this.next = nullptr;
      this.nextPadY = 0;
   }
}
} // namespace ui
} // namespace zombie
