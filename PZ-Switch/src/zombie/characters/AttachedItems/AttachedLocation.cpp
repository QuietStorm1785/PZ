#include "zombie/characters/AttachedItems/AttachedLocation.h"
#include "zombie/characters/AttachedItems/AttachedLocationGroup.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

AttachedLocation::AttachedLocation(const AttachedLocationGroup* _group,
 const std::string &_id)
 : group(_group), id(_id), attachmentName("") {
 if (_id.empty()) {
 throw IllegalArgumentException("id is empty");
 }
}

void AttachedLocation::setAttachmentName(const std::string &_attachmentName) {
 if (_attachmentName.empty()) {
 throw IllegalArgumentException("attachmentName is empty");
 }
 attachmentName = _attachmentName;
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie
