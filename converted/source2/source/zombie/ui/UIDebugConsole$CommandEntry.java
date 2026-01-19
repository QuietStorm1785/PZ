package zombie.ui;

class UIDebugConsole$CommandEntry extends UITextBox2 {
   public UIDebugConsole$CommandEntry(UIDebugConsole var1, UIFont var2, int var3, int var4, int var5, int var6, String var7, boolean var8) {
      super(var2, var3, var4, var5, var6, var7, var8);
      this.this$0 = var1;
   }

   public void onPressUp() {
      this.this$0.historyPrev();
   }

   public void onPressDown() {
      this.this$0.historyNext();
   }

   public void onOtherKey(int var1) {
      this.this$0.onOtherKey(var1);
   }
}
