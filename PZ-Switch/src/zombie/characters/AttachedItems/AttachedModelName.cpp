#include "zombie/characters/AttachedItems/AttachedModelName.h"

namespace zombie {
namespace characters {
namespace AttachedItems {

AttachedModelName::AttachedModelName(const AttachedModelName& other)
 : attachmentNameSelf(other.attachmentNameSelf),
 attachmentNameParent(other.attachmentNameParent),
 modelName(other.modelName),
 bloodLevel(other.bloodLevel) {
 for (int i = 0; i < other.getChildCount(); i++) {
 auto child = other.getChildByIndex(i);
 if (child) {
 addChild(std::make_shared<AttachedModelName>(*child));
 }
 }
}

AttachedModelName::AttachedModelName(const std::string &attachmentName,
 const std::string &_modelName, 
 float _bloodLevel)
 : attachmentNameSelf(attachmentName),
 attachmentNameParent(attachmentName),
 modelName(_modelName),
 bloodLevel(_bloodLevel) {
}

AttachedModelName::AttachedModelName(const std::string &_attachmentNameSelf,
 const std::string &_attachmentNameParent,
 const std::string &_modelName, 
 float _bloodLevel)
 : attachmentNameSelf(_attachmentNameSelf),
 attachmentNameParent(_attachmentNameParent),
 modelName(_modelName),
 bloodLevel(_bloodLevel) {
}

void AttachedModelName::addChild(std::shared_ptr<AttachedModelName> child) {
 if (child) {
 children.push_back(child);
 }
}

int AttachedModelName::getChildCount() const {
 return children.size();
}

std::shared_ptr<AttachedModelName> AttachedModelName::getChildByIndex(int index) const {
 if (index >= 0 && index < (int)children.size()) {
 return children[index];
 }
 return nullptr;
}

} // namespace AttachedItems
} // namespace characters
} // namespace zombie

