#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector3f.h"
#include "zombie/util/StringUtils.h"

namespace zombie {
namespace scripting {
namespace objects {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ModelAttachment {
public:
 std::string id;
 const Vector3f offset = new Vector3f();
 const Vector3f rotate = new Vector3f();
 std::string bone;
 private ArrayList<String> canAttach;
 float zoffset;
 bool updateConstraint = true;

 public ModelAttachment(const std::string& _id) {
 this->setId(_id);
 }

 std::string getId() {
 return this->id;
 }

 void setId(const std::string& _id) {
 if (StringUtils.isNullOrWhitespace(_id) {
 throw IllegalArgumentException("ModelAttachment id is nullptr or empty");
 } else {
 this->id = _id;
 }
 }

 Vector3f getOffset() {
 return this->offset;
 }

 Vector3f getRotate() {
 return this->rotate;
 }

 std::string getBone() {
 return this->bone;
 }

 void setBone(const std::string& _bone) {
 _bone = _bone.trim();
 this->bone = _bone.empty() ? nullptr : _bone;
 }

 public ArrayList<String> getCanAttach() {
 return this->canAttach;
 }

 void setCanAttach(ArrayList<String> _canAttach) {
 this->canAttach = _canAttach;
 }

 float getZOffset() {
 return this->zoffset;
 }

 void setZOffset(float _zoffset) {
 this->zoffset = _zoffset;
 }

 bool isUpdateConstraint() {
 return this->updateConstraint;
 }

 void setUpdateConstraint(bool _updateConstraint) {
 this->updateConstraint = _updateConstraint;
 }
}
} // namespace objects
} // namespace scripting
} // namespace zombie
