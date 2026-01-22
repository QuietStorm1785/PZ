#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/ConfigOption.h"
#include "zombie/config/DoubleConfigOption.h"
#include "zombie/core/Translator.h"
#include "zombie/network/ServerOptions/ServerOption.h"

namespace zombie {
namespace network {


class ServerOptions {
public:
   public ServerOptions$DoubleServerOption(ServerOptions var1, std::string var2, double var3, double var5, double var7) {
      super(var2, var3, var5, var7);
      var1.addOption(this);
   }

    ConfigOption asConfigOption() {
    return this;
   }

    std::string getTooltip() {
    std::string var1 = Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
      std::string var2 = Translator.getText(
         "Sandbox_MinMaxDefault", std::string.format("%.02f", this.min), std::string.format("%.02f", this.max), std::string.format("%.02f", this.defaultValue)
      );
      if (var1 == nullptr) {
    return var2;
      } else {
    return var2 = = nullptr ? var1 : var1 + "\\n" + var2;
      }
   }
}
} // namespace network
} // namespace zombie
