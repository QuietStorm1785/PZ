#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/Translator.h"
#include "zombie/network/ServerOptions/ServerOption.h"

namespace zombie {
namespace network {


class ServerOptions {
public:
   public ServerOptions$BooleanServerOption(ServerOptions var1, std::string var2, boolean var3) {
      super(var2, var3);
      var1.addOption(this);
   }

    ConfigOption asConfigOption() {
    return this;
   }

    std::string getTooltip() {
      return Translator.getTextOrNull("UI_ServerOption_" + this.name + "_tooltip");
   }
}
} // namespace network
} // namespace zombie
