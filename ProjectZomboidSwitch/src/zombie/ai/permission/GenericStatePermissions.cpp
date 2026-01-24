#include "zombie/ai/permission/GenericStatePermissions.h"

namespace zombie {
namespace ai {
namespace permission {
GenericStatePermissions::GenericStatePermissions() {
	// Example: initialize custom permissions
	customPermissions_["deferredMovement"] = true;
	customPermissions_["playerInput"] = true;
}

GenericStatePermissions::~GenericStatePermissions() {}

bool GenericStatePermissions::isDeferredMovementAllowed(const IsoGameCharacter& character) const {
	// ...existing code...
}

bool GenericStatePermissions::isPlayerInputAllowed(const IsoGameCharacter& character) const {
	// ...existing code...
}

bool GenericStatePermissions::isPermissionAllowed(const IsoGameCharacter& character, const std::string& permissionName) const {
	auto it = customPermissions_.find(permissionName);
	if (it != customPermissions_.end()) {
		return it->second;
	}
	return false;
}

// Implementation now in header (inline)

} // namespace permission
} // namespace ai
} // namespace zombie
