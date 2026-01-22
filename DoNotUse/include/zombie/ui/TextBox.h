#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace ui {


class TextBox : public UIElement {
public:
    bool ResizeParent;
    UIFont font;
   std::stack<std::string> Lines = std::make_unique<std::stack<>>();
    std::string Text;
    bool Centred = false;

    public TextBox(UIFont var1, int var2, int var3, int var4, const std::string& var5) {
      this.font = var1;
      this.x = var2;
      this.y = var3;
      this.Text = var5;
      this.width = var4;
      this.Paginate();
   }

    void onresize() {
      this.Paginate();
   }

    void render() {
      if (this.isVisible()) {
         super.render();
         this.Paginate();
    int var1 = 0;

         for (std::string var3 : this.Lines) {
            if (this.Centred) {
               TextManager.instance
                  .DrawStringCentre(
                     this.font, this.getAbsoluteX().intValue() + this.getWidth() / 2.0, this.getAbsoluteY().intValue() + var1, var3, 1.0, 1.0, 1.0, 1.0
                  );
            } else {
               TextManager.instance.DrawString(this.font, this.getAbsoluteX().intValue(), this.getAbsoluteY().intValue() + var1, var3, 1.0, 1.0, 1.0, 1.0);
            }

            var1 += TextManager.instance.MeasureStringY(this.font, this.Lines.get(0));
         }

         this.setHeight(var1);
      }
   }

    void update() {
      this.Paginate();
    int var1 = 0;

      for (std::string var3 : this.Lines) {
         var1 += TextManager.instance.MeasureStringY(this.font, this.Lines.get(0));
      }

      this.setHeight(var1);
   }

    void Paginate() {
    int var1 = 0;
      this.Lines.clear();
      std::string[] var2 = this.Text.split("<br>");

    for (auto& var6 : var2)         if (var6.length() == 0) {
            this.Lines.push_back(" ");
         } else {
            while (true) {
    int var7 = var6.indexOf(" ", var1 + 1);
    int var8 = var7;
               if (var7 == -1) {
                  var8 = var6.length();
               }

    int var9 = TextManager.instance.MeasureStringX(this.font, var6.substr(0, var8));
               if (var9 >= this.getWidth()) {
    std::string var10 = var6.substr(0, var1);
                  var6 = var6.substr(var1 + 1);
                  this.Lines.push_back(var10);
                  var7 = 0;
               } else if (var7 == -1) {
                  this.Lines.push_back(var6);
                  break;
               }

               var1 = var7;
               if (var6.length() <= 0) {
                  break;
               }
            }
         }
      }
   }

    void SetText(const std::string& var1) {
      this.Text = var1;
      this.Paginate();
   }
}
} // namespace ui
} // namespace zombie
