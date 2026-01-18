#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace radio {
namespace globals {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class EditGlobal {
public:
 RadioGlobal global;
 RadioGlobal value;
 EditGlobalOps operator;

public
 EditGlobal(RadioGlobal radioGlobal0, EditGlobalOps editGlobalOps,
 RadioGlobal radioGlobal1) {
 this->global = radioGlobal0;
 this->operator= editGlobalOps;
 this->value = radioGlobal1;
 }

 RadioGlobal getGlobal() { return this->global; }

 EditGlobalOps getOperator() { return this->operator; }

 RadioGlobal getValue() { return this->value; }
}
} // namespace globals
} // namespace radio
} // namespace zombie
