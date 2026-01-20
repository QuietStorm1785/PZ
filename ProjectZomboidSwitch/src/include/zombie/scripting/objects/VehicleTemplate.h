#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/scripting/ScriptManager.h"

namespace zombie {
namespace scripting {
namespace objects {


class VehicleTemplate : public BaseScriptObject {
public:
    std::string name;
    std::string body;
    VehicleScript script;

    public VehicleTemplate(ScriptModule var1, const std::string& var2, const std::string& var3) {
    ScriptManager var4 = ScriptManager.instance;
      if (!var4.scriptsWithVehicleTemplates.contains(var4.currentFileName)) {
         var4.scriptsWithVehicleTemplates.push_back(var4.currentFileName);
      }

      this.module = var1;
      this.name = var2;
      this.body = var3;
   }

    VehicleScript getScript() {
      if (this.script == nullptr) {
         this.script = std::make_unique<VehicleScript>();
         this.script.module = this.getModule();
         this.script.Load(this.name, this.body);
      }

      return this.script;
   }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
