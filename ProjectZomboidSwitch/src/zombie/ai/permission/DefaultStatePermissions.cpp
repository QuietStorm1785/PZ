#include "zombie/ai/permission/DefaultStatePermissions.h"

namespace zombie {
namespace ai {
namespace permission {
DefaultStatePermissions::DefaultStatePermissions() {}
DefaultStatePermissions::~DefaultStatePermissions() {}

DefaultStatePermissions& DefaultStatePermissions::instance() {
	static DefaultStatePermissions instance_;
	return instance_;
}

bool DefaultStatePermissions::isDeferredMovementAllowed(const IsoGameCharacter& character) const {
	// ...existing code...
}

bool DefaultStatePermissions::isPlayerInputAllowed(const IsoGameCharacter& character) const {
	// ...existing code...
}

bool DefaultStatePermissions::isPermissionAllowed(const IsoGameCharacter& character, const std::string& permissionName) const {
	if (permissionName == "deferredMovement") return isDeferredMovementAllowed(character);
	if (permissionName == "playerInput") return isPlayerInputAllowed(character);
	return false;
}

// Implementation now in header (inline)

} // namespace permission
} // namespace ai
} // namespace zombie
