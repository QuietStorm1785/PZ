#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/config/ConfigOption.h"
#include "zombie/config/StringConfigOption.h"
#include "zombie/core/Translator.h"
#include "zombie/network/ServerOptions/ServerOption.h"

namespace zombie {
namespace network {


class ServerOptions {
public:
   public ServerOptions$TextServerOption(ServerOptions var1, std::string var2, std::string var3, int var4) {
      super(var2, var3, var4);
      var1.addOption(this);
   }

    std::string getType() {
      return "text";
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
