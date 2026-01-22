#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Translator.h"
#include "zombie/network/ICoopServerMessageListener.h"

namespace zombie {
namespace ui {


class UIServerToolbox {
public:
   UIServerToolbox$2(UIServerToolbox var1) {
      this.this$0 = var1;
   }

    void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& var3) {
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
} // namespace ui
} // namespace zombie
