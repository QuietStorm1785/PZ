package zombie.ui;

import zombie.core.Translator;
import zombie.network.ICoopServerMessageListener;

class UIServerToolbox$1 implements ICoopServerMessageListener {
   UIServerToolbox$1(UIServerToolbox var1) {
      this.this$0 = var1;
   }

   public void OnCoopServerMessage(String var1, String var2, String var3) {
      this.this$0.externalAddress = var3;
      String var4 = "null".equals(this.this$0.externalAddress) ? Translator.getText("IGUI_ServerToolBox_IPUnknown") : this.this$0.externalAddress;
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_ServerAddress", var4));
      this.this$0.PrintLine("");
   }
}
