#include <string>
#include "zombie/ai/State.h"

namespace zombie {
namespace ai {

void State::enter(IsoGameCharacter var1) {
    // Default: no-op, override in subclasses for specific state logic
}

void State::execute(IsoGameCharacter var1) {
    // Default: no-op, override in subclasses for specific state logic
}

void State::exit(IsoGameCharacter var1) {
    // Default: no-op, override in subclasses for specific state logic
}

void State::animEvent(IsoGameCharacter var1, AnimEvent var2) {
    // Default: no-op, override in subclasses for specific state logic
}

bool State::isAttacking(IsoGameCharacter var1) {
    return false;
}

bool State::isMoving(IsoGameCharacter var1) {
    return false;
}

bool State::isDoingActionThatCanBeCancelled() {
    return false;
}

void State::getDeltaModifiers(IsoGameCharacter var1, MoveDeltaModifiers var2) {
    // Default: no-op, override in subclasses for specific state logic
}

bool State::isIgnoreCollide(IsoGameCharacter var1, int var2, int var3, int var4, int var5, int var6, int var7) {
    return false;
}

std::string State::getName() {
    // Mimic Java getClass().getSimpleName() using typeid
    std::string name = typeid(*this).name();
    // Optionally demangle if using GCC/Clang
#ifdef __GNUG__
    int status = 0;
    char* demangled = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);
    if (status == 0 && demangled) {
        name = demangled;
        free(demangled);
    }
#endif
    // Remove namespace if present
    size_t pos = name.rfind("::");
    if (pos != std::string::npos) {
        name = name.substr(pos + 2);
    }
    return name;
}
IStatePermissions* State::getStatePermissions() {
    // Return default permissions instance
    return &DefaultStatePermissions::Instance;
}

IStatePermissions State::getStatePermissions() {
    // Return default permissions instance (matches Java)
    DebugLog::AI.debug("State::getStatePermissions: returning DefaultStatePermissions::Instance");
    return &DefaultStatePermissions::Instance;
}

} // namespace ai
} // namespace zombie
