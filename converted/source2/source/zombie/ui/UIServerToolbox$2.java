package zombie.ui;

import zombie.core.Translator;
import zombie.network.ICoopServerMessageListener;

class UIServerToolbox$2 implements ICoopServerMessageListener {
   UIServerToolbox$2(UIServerToolbox var1) {
      this.this$0 = var1;
   }

   public void OnCoopServerMessage(String var1, String var2, String var3) {
      this.this$0.steamID = var3;
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_SteamID", this.this$0.steamID));
      this.this$0.PrintLine("");
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_Invite1"));
      this.this$0.PrintLine("");
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_Invite2"));
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_Invite3"));
      this.this$0.PrintLine("");
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_Invite4"));
      this.this$0.PrintLine("");
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_Invite5"));
   }
}
