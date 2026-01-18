#pragma once
#include "zombie/scripting/ScriptManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class VehicleTemplate : public BaseScriptObject {
public:
 std::string name;
 std::string body;
 VehicleScript script;

public
 VehicleTemplate(ScriptModule module, const std::string &_name,
 const std::string &_body) {
 ScriptManager scriptManager = ScriptManager.instance;
 if (!scriptManager.scriptsWithVehicleTemplates.contains(
 scriptManager.currentFileName) {
 scriptManager.scriptsWithVehicleTemplates.add(
 scriptManager.currentFileName);
 }

 this->module = module;
 this->name = _name;
 this->body = _body;
 }

 VehicleScript getScript() {
 if (this->script.empty()) {
 this->script = std::make_unique<VehicleScript>();
 this->script.module = this->getModule();
 this->script.Load(this->name, this->body);
 }

 return this->script;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
