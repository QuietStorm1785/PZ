package zombie.chat;

import zombie.network.GameServer;
import zombie.ui.TextDrawObject;
import zombie.ui.UIFont;

class ChatElement$PlayerLines {
   protected int lineDisplayTime;
   protected int renderX;
   protected int renderY;
   protected boolean ignoreRadioLines;
   protected TextDrawObject[] chatLines;

   public ChatElement$PlayerLines(ChatElement var1, int var2) {
      this.this$0 = var1;
      this.lineDisplayTime = 314;
      this.renderX = 0;
      this.renderY = 0;
      this.ignoreRadioLines = false;
      this.chatLines = new TextDrawObject[var2];

      for (int var3 = 0; var3 < this.chatLines.length; var3++) {
         this.chatLines[var3] = new TextDrawObject(0, 0, 0, true, true, true, true, true, true);
         this.chatLines[var3].setDefaultFont(UIFont.Medium);
      }
   }

   public void setMaxCharsPerLine(int var1) {
      for (int var2 = 0; var2 < this.chatLines.length; var2++) {
         this.chatLines[var2].setMaxCharsPerLine(var1);
      }
   }

   public TextDrawObject getNewLineObject() {
      if (this.chatLines != null && this.chatLines.length > 0) {
         TextDrawObject var1 = this.chatLines[this.chatLines.length - 1];
         var1.Clear();

         for (int var2 = this.chatLines.length - 1; var2 > 0; var2--) {
            this.chatLines[var2] = this.chatLines[var2 - 1];
         }

         this.chatLines[0] = var1;
         return this.chatLines[0];
      } else {
         return null;
      }
   }

   public void render() {
      if (!GameServer.bServer) {
         if (this.this$0.hasChatToDisplay) {
            int var3 = 0;

            for (TextDrawObject var7 : this.chatLines) {
               if (var7.getEnabled()) {
                  if (var7.getWidth() > 0 && var7.getHeight() > 0) {
                     float var1 = var7.getInternalClock();
                     if (!(var1 <= 0.0F) && (!var7.getCustomTag().equals("radio") || !this.ignoreRadioLines)) {
                        float var2 = var1 / (this.lineDisplayTime / 4.0F);
                        if (var2 > 1.0F) {
                           var2 = 1.0F;
                        }

                        this.renderY = this.renderY - (var7.getHeight() + 1);
                        boolean var8 = var7.getDefaultFontEnum() != UIFont.Dialogue;
                        if (ChatElement.doBackDrop && ChatElement.backdropTexture != null) {
                           ChatElement.backdropTexture
                              .renderInnerBased(this.renderX - var7.getWidth() / 2, this.renderY, var7.getWidth(), var7.getHeight(), 0.0F, 0.0F, 0.0F, 0.4F);
                        }

                        if (var3 == 0) {
                           var7.Draw(this.renderX, this.renderY, var8, var2);
                        } else if (this.this$0.historyVal > 0.0F) {
                           var7.Draw(this.renderX, this.renderY, var8, var2 * this.this$0.historyVal);
                        }

                        var3++;
                     }
                  } else {
                     var3++;
                  }
               }
            }
         }
      }
   }

   void clear() {
      if (this.this$0.hasChatToDisplay) {
         this.this$0.hasChatToDisplay = false;

         for (int var1 = 0; var1 < this.chatLines.length; var1++) {
            if (!(this.chatLines[var1].getInternalClock() <= 0.0F)) {
               this.chatLines[var1].Clear();
               this.chatLines[var1].updateInternalTickClock(this.chatLines[var1].getInternalClock());
            }
         }

         this.this$0.historyInRange = false;
         this.this$0.historyVal = 0.0F;
      }
   }
}
