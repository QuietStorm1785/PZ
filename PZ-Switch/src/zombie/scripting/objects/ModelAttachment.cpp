#include "zombie/scripting/objects/ModelAttachment.h"

namespace zombie {
namespace scripting {
namespace objects {

public
ModelAttachment::ModelAttachment(const std::string &_id) {
 // TODO: Implement ModelAttachment
 return nullptr;
}

std::string ModelAttachment::getId() {
 // TODO: Implement getId
 return "";
}

void ModelAttachment::setId(const std::string &_id) {
 // TODO: Implement setId
}

Vector3f ModelAttachment::getOffset() {
 // TODO: Implement getOffset
 return nullptr;
}

Vector3f ModelAttachment::getRotate() {
 // TODO: Implement getRotate
 return nullptr;
}

std::string ModelAttachment::getBone() {
 // TODO: Implement getBone
 return "";
}

void ModelAttachment::setBone(const std::string &_bone) {
 // TODO: Implement setBone
}

void ModelAttachment::setCanAttach(ArrayList<String> _canAttach) {
 // TODO: Implement setCanAttach
}

float ModelAttachment::getZOffset() {
 // TODO: Implement getZOffset
 return 0;
}

void ModelAttachment::setZOffset(float _zoffset) {
 // TODO: Implement setZOffset
}

bool ModelAttachment::isUpdateConstraint() {
 // TODO: Implement isUpdateConstraint
 return false;
}

void ModelAttachment::setUpdateConstraint(bool _updateConstraint) {
 // TODO: Implement setUpdateConstraint
}

} // namespace objects
} // namespace scripting
} // namespace zombie
