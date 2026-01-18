#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include "java/lang/exceptions.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

// Forward declaration
class AttachedLocationGroup;

// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class AttachedLocation {
public:
 const AttachedLocationGroup* group;
 const std::string id;
 std::string attachmentName;

 AttachedLocation(const AttachedLocationGroup* _group, const std::string &_id);
 
 void setAttachmentName(const std::string &_attachmentName);
 std::string getAttachmentName() const { return attachmentName; }
 std::string getId() const { return id; }

	// Convenience for converted call sites that expect an 'empty()' check
	// Returns true if both id and attachmentName are empty
	bool empty() const { return id.empty() && attachmentName.empty(); }
};

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
