package zombie.ui;

import java.util.Stack;

public final class TextBox extends UIElement {
   public boolean ResizeParent;
   UIFont font;
   Stack<String> Lines = new Stack<>();
   String Text;
   public boolean Centred = false;

   public TextBox(UIFont var1, int var2, int var3, int var4, String var5) {
      this.font = var1;
      this.x = var2;
      this.y = var3;
      this.Text = var5;
      this.width = var4;
      this.Paginate();
   }

   public void onresize() {
      this.Paginate();
   }

   public void render() {
      if (this.isVisible()) {
         super.render();
         this.Paginate();
         int var1 = 0;

         for (String var3 : this.Lines) {
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

   public void update() {
      this.Paginate();
      int var1 = 0;

      for (String var3 : this.Lines) {
         var1 += TextManager.instance.MeasureStringY(this.font, this.Lines.get(0));
      }

      this.setHeight(var1);
   }

   private void Paginate() {
      int var1 = 0;
      this.Lines.clear();
      String[] var2 = this.Text.split("<br>");

      for (String var6 : var2) {
         if (var6.length() == 0) {
            this.Lines.add(" ");
         } else {
            while (true) {
               int var7 = var6.indexOf(" ", var1 + 1);
               int var8 = var7;
               if (var7 == -1) {
                  var8 = var6.length();
               }

               int var9 = TextManager.instance.MeasureStringX(this.font, var6.substring(0, var8));
               if (var9 >= this.getWidth()) {
                  String var10 = var6.substring(0, var1);
                  var6 = var6.substring(var1 + 1);
                  this.Lines.add(var10);
                  var7 = 0;
               } else if (var7 == -1) {
                  this.Lines.add(var6);
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

   public void SetText(String var1) {
      this.Text = var1;
      this.Paginate();
   }
}
