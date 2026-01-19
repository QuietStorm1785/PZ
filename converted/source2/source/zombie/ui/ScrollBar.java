package zombie.ui;

import zombie.core.Color;
import zombie.core.textures.Texture;
import zombie.input.Mouse;

public final class ScrollBar extends UIElement {
   public final Color BackgroundColour = new Color(255, 255, 255, 255);
   public final Color ButtonColour = new Color(255, 255, 255, 127);
   public final Color ButtonHighlightColour = new Color(255, 255, 255, 255);
   public boolean IsVerticle = true;
   private int FullLength = 114;
   private int InsideLength = 100;
   private int EndLength = 7;
   private float ButtonInsideLength = 30.0F;
   private int ButtonEndLength = 6;
   private int Thickness = 10;
   private int ButtonThickness = 9;
   private float ButtonOffset = 40.0F;
   private int MouseDragStartPos = 0;
   private float ButtonDragStartPos = 0.0F;
   private Texture BackVertical;
   private Texture TopVertical;
   private Texture BottomVertical;
   private Texture ButtonBackVertical;
   private Texture ButtonTopVertical;
   private Texture ButtonBottomVertical;
   private Texture BackHorizontal;
   private Texture LeftHorizontal;
   private Texture RightHorizontal;
   private Texture ButtonBackHorizontal;
   private Texture ButtonLeftHorizontal;
   private Texture ButtonRightHorizontal;
   private boolean mouseOver = false;
   private boolean BeingDragged = false;
   private UITextBox2 ParentTextBox = null;
   UIEventHandler messageParent;
   private String name;

   public ScrollBar(String var1, UIEventHandler var2, int var3, int var4, int var5, boolean var6) {
      this.messageParent = var2;
      this.name = var1;
      this.x = var3;
      this.y = var4;
      this.FullLength = var5;
      this.InsideLength = var5 - this.EndLength * 2;
      this.IsVerticle = true;
      this.width = this.Thickness;
      this.height = var5;
      this.ButtonInsideLength = this.height - this.ButtonEndLength * 2;
      this.ButtonOffset = 0.0F;
      this.BackVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Bkg_Middle.png");
      this.TopVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Bkg_Top.png");
      this.BottomVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Bkg_Bottom.png");
      this.ButtonBackVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Middle.png");
      this.ButtonTopVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Top.png");
      this.ButtonBottomVertical = Texture.getSharedTexture("media/ui/ScrollbarV_Bottom.png");
      this.BackHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Bkg_Middle.png");
      this.LeftHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Bkg_Bottom.png");
      this.RightHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Bkg_Top.png");
      this.ButtonBackHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Middle.png");
      this.ButtonLeftHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Bottom.png");
      this.ButtonRightHorizontal = Texture.getSharedTexture("media/ui/ScrollbarH_Top.png");
   }

   public void SetParentTextBox(UITextBox2 var1) {
      this.ParentTextBox = var1;
   }

   public void setHeight(double var1) {
      super.setHeight(var1);
      this.FullLength = (int)var1;
      this.InsideLength = (int)var1 - this.EndLength * 2;
   }

   public void render() {
      if (this.IsVerticle) {
         this.DrawTextureScaledCol(this.TopVertical, 0.0, 0.0, this.Thickness, this.EndLength, this.BackgroundColour);
         this.DrawTextureScaledCol(this.BackVertical, 0.0, 0 + this.EndLength, this.Thickness, this.InsideLength, this.BackgroundColour);
         this.DrawTextureScaledCol(this.BottomVertical, 0.0, 0 + this.EndLength + this.InsideLength, this.Thickness, this.EndLength, this.BackgroundColour);
         Color var1;
         if (this.mouseOver) {
            var1 = this.ButtonHighlightColour;
         } else {
            var1 = this.ButtonColour;
         }

         this.DrawTextureScaledCol(this.ButtonTopVertical, 1.0, (int)this.ButtonOffset + 1, this.ButtonThickness, this.ButtonEndLength, var1);
         this.DrawTextureScaledCol(
            this.ButtonBackVertical, 1.0, (int)this.ButtonOffset + 1 + this.ButtonEndLength, this.ButtonThickness, this.ButtonInsideLength, var1
         );
         this.DrawTextureScaledCol(
            this.ButtonBottomVertical,
            1.0,
            (int)this.ButtonOffset + 1 + this.ButtonEndLength + this.ButtonInsideLength,
            this.ButtonThickness,
            this.ButtonEndLength,
            var1
         );
      }
   }

   public Boolean onMouseMove(double var1, double var3) {
      this.mouseOver = true;
      return Boolean.TRUE;
   }

   public void onMouseMoveOutside(double var1, double var3) {
      this.mouseOver = false;
   }

   public Boolean onMouseUp(double var1, double var3) {
      this.BeingDragged = false;
      return Boolean.FALSE;
   }

   public Boolean onMouseDown(double var1, double var3) {
      boolean var5 = false;
      if (var3 >= this.ButtonOffset && var3 <= this.ButtonOffset + this.ButtonInsideLength + this.ButtonEndLength * 2) {
         var5 = true;
      }

      if (var5) {
         this.BeingDragged = true;
         this.MouseDragStartPos = Mouse.getY();
         this.ButtonDragStartPos = this.ButtonOffset;
      } else {
         this.ButtonOffset = (float)(var3 - (this.ButtonInsideLength + this.ButtonEndLength * 2) / 2.0F);
      }

      if (this.ButtonOffset < 0.0F) {
         this.ButtonOffset = 0.0F;
      }

      if (this.ButtonOffset > this.getHeight().intValue() - (this.ButtonInsideLength + this.ButtonEndLength * 2) - 1.0F) {
         this.ButtonOffset = this.getHeight().intValue() - (this.ButtonInsideLength + this.ButtonEndLength * 2) - 1.0F;
      }

      return Boolean.FALSE;
   }

   public void update() {
      super.update();
      if (this.BeingDragged) {
         int var1 = this.MouseDragStartPos - Mouse.getY();
         this.ButtonOffset = this.ButtonDragStartPos - var1;
         if (this.ButtonOffset < 0.0F) {
            this.ButtonOffset = 0.0F;
         }

         if (this.ButtonOffset > this.getHeight().intValue() - (this.ButtonInsideLength + this.ButtonEndLength * 2) - 0.0F) {
            this.ButtonOffset = this.getHeight().intValue() - (this.ButtonInsideLength + this.ButtonEndLength * 2) - 0.0F;
         }

         if (!Mouse.isButtonDown(0)) {
            this.BeingDragged = false;
         }
      }

      if (this.ParentTextBox != null) {
         int var11 = TextManager.instance.getFontFromEnum(this.ParentTextBox.font).getLineHeight();
         if (this.ParentTextBox.Lines.size() > this.ParentTextBox.NumVisibleLines) {
            if (this.ParentTextBox.Lines.size() > 0) {
               int var2 = this.ParentTextBox.NumVisibleLines;
               if (var2 * var11 > this.ParentTextBox.getHeight().intValue() - this.ParentTextBox.getInset() * 2) {
                  var2--;
               }

               float var3 = (float)var2 / this.ParentTextBox.Lines.size();
               this.ButtonInsideLength = (int)(this.getHeight().intValue() * var3) - this.ButtonEndLength * 2;
               this.ButtonInsideLength = Math.max(this.ButtonInsideLength, 0.0F);
               float var4 = this.ButtonInsideLength + this.ButtonEndLength * 2;
               if (this.ButtonOffset < 0.0F) {
                  this.ButtonOffset = 0.0F;
               }

               if (this.ButtonOffset > this.getHeight().intValue() - var4 - 0.0F) {
                  this.ButtonOffset = this.getHeight().intValue() - var4 - 0.0F;
               }

               float var5 = this.ButtonOffset / this.getHeight().intValue();
               this.ParentTextBox.TopLineIndex = (int)(this.ParentTextBox.Lines.size() * var5);
               int var6 = this.getHeight().intValue();
               int var7 = var6 - (int)var4;
               int var8 = var11 * (this.ParentTextBox.Lines.size() - var2);
               float var9 = (float)var7 / var8;
               float var10 = this.ButtonOffset / var9;
               this.ParentTextBox.TopLineIndex = (int)(var10 / var11);
            } else {
               this.ButtonOffset = 0.0F;
               this.ButtonInsideLength = this.getHeight().intValue() - this.ButtonEndLength * 2;
               this.ParentTextBox.TopLineIndex = 0;
            }
         } else {
            this.ButtonOffset = 0.0F;
            this.ButtonInsideLength = this.getHeight().intValue() - this.ButtonEndLength * 2;
            this.ParentTextBox.TopLineIndex = 0;
         }
      }
   }

   public void scrollToBottom() {
      this.ButtonOffset = this.getHeight().intValue() - (this.ButtonInsideLength + this.ButtonEndLength * 2) - 0.0F;
   }
}
