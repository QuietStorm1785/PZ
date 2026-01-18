#pragma once
#include <cstdint>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace org {
namespace joml {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Matrix3x2dStack : public Matrix3x2d {
public:
 static const long serialVersionUID = 1L;
private
 Matrix3x2d[] mats;
 int curr;

public
 Matrix3x2dStack(int int0) {
 if (int0 < 1) {
 throw IllegalArgumentException("stackSize must be >= 1");
 } else {
 this->mats = new Matrix3x2d[int0 - 1];

 for (int int1 = 0; int1 < this->mats.length; int1++) {
 this->mats[int1] = std::make_unique<Matrix3x2d>();
 }
 }
 }

public
 Matrix3x2dStack() {}

 Matrix3x2dStack clear() {
 this->curr = 0;
 this->identity();
 return this;
 }

 Matrix3x2dStack pushMatrix() {
 if (this->curr == this->mats.length) {
 throw IllegalStateException("max stack size of " + (this->curr + 1) +
 " reached");
 } else {
 this->mats[this->curr++].set(this);
 return this;
 }
 }

 Matrix3x2dStack popMatrix() {
 if (this->curr == 0) {
 throw IllegalStateException("already at the buttom of the stack");
 } else {
 this->set(this->mats[--this->curr]);
 return this;
 }
 }

 int hashCode() {
 int int0 = super.hashCode();
 int0 = 31 * int0 + this->curr;

 for (int int1 = 0; int1 < this->curr; int1++) {
 int0 = 31 * int0 + this->mats[int1].hashCode();
 }

 return int0;
 }

 bool equals(void *object) {
 if (this == object) {
 return true;
 } else if (!super == object) {
 return false;
 }
 else {
 if (dynamic_cast<Matrix3x2dStac*>(object) != nullptrk matrix3x2dStack1) {
 if (this->curr != matrix3x2dStack1.curr) {
 return false;
 }

 for (int int0 = 0; int0 < this->curr; int0++) {
 if (!this->mats[int0] == matrix3x2dStack1.mats[int0])) {
 return false;
 }
 }
 }

 return true;
 }
 }

 void writeExternal(ObjectOutput objectOutput) {
 super.writeExternal(objectOutput);
 objectOutput.writeInt(this->curr);

 for (int int0 = 0; int0 < this->curr; int0++) {
 objectOutput.writeObject(this->mats[int0]);
 }
 }

 void readExternal(ObjectInput objectInput) {
 super.readExternal(objectInput);
 this->curr = objectInput.readInt();
 this->mats = new Matrix3x2dStack[this->curr];

 for (int int0 = 0; int0 < this->curr; int0++) {
 Matrix3x2d matrix3x2d = new Matrix3x2d();
 matrix3x2d.readExternal(objectInput);
 this->mats[int0] = matrix3x2d;
 }
 }
}
} // namespace joml
} // namespace org
