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
   UIServerToolbox$1(UIServerToolbox var1) {
      this.this$0 = var1;
   }

    void OnCoopServerMessage(const std::string& var1, const std::string& var2, const std::string& var3) {
      this.this$0.externalAddress = var3;
    std::string var4 = "nullptr" == this.this$0.externalAddress) ? Translator.getText("IGUI_ServerToolBox_IPUnknown") : this.this$0.externalAddress;
      this.this$0.PrintLine(Translator.getText("IGUI_ServerToolBox_ServerAddress", var4));
      this.this$0.PrintLine("");
   }
}
} // namespace ui
} // namespace zombie
