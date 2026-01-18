#include "javax/vecmath/Matrix3d.h"

namespace javax {
namespace vecmath {

public Matrix3d::Matrix3d(double[] doubles) {
 // TODO: Implement Matrix3d
 return nullptr;
}

public Matrix3d::Matrix3d(Matrix3d matrix3d1) {
 // TODO: Implement Matrix3d
 return nullptr;
}

public Matrix3d::Matrix3d(Matrix3f matrix3f) {
 // TODO: Implement Matrix3d
 return nullptr;
}

public Matrix3d::Matrix3d() {
 // TODO: Implement Matrix3d
 return nullptr;
}

std::string Matrix3d::toString() {
 // TODO: Implement toString
 return "";
}

void Matrix3d::setIdentity() {
 // TODO: Implement setIdentity
}

void Matrix3d::setScale(double double0) {
 // TODO: Implement setScale
}

void Matrix3d::setElement(int int0, int int1, double double0) {
 // TODO: Implement setElement
}

double Matrix3d::getElement(int int0, int int1) {
 // TODO: Implement getElement
 return 0;
}

void Matrix3d::getRow(int int0, Vector3d vector3d) {
 // TODO: Implement getRow
}

void Matrix3d::getRow(int int0, double[] doubles) {
 // TODO: Implement getRow
}

void Matrix3d::getColumn(int int0, Vector3d vector3d) {
 // TODO: Implement getColumn
}

void Matrix3d::getColumn(int int0, double[] doubles) {
 // TODO: Implement getColumn
}

void Matrix3d::setRow(int int0, double double0, double double1, double double2) {
 // TODO: Implement setRow
}

void Matrix3d::setRow(int int0, Vector3d vector3d) {
 // TODO: Implement setRow
}

void Matrix3d::setRow(int int0, double[] doubles) {
 // TODO: Implement setRow
}

void Matrix3d::setColumn(int int0, double double0, double double1, double double2) {
 // TODO: Implement setColumn
}

void Matrix3d::setColumn(int int0, Vector3d vector3d) {
 // TODO: Implement setColumn
}

void Matrix3d::setColumn(int int0, double[] doubles) {
 // TODO: Implement setColumn
}

double Matrix3d::getScale() {
 // TODO: Implement getScale
 return 0;
}

return Matrix3d::max3() {
 // TODO: Implement max3
 return nullptr;
}

void Matrix3d::add(double double0) {
 // TODO: Implement add
}

void Matrix3d::add(double double0, Matrix3d matrix3d0) {
 // TODO: Implement add
}

void Matrix3d::add(Matrix3d matrix3d1, Matrix3d matrix3d0) {
 // TODO: Implement add
}

void Matrix3d::add(Matrix3d matrix3d0) {
 // TODO: Implement add
}

void Matrix3d::sub(Matrix3d matrix3d1, Matrix3d matrix3d0) {
 // TODO: Implement sub
}

void Matrix3d::sub(Matrix3d matrix3d0) {
 // TODO: Implement sub
}

void Matrix3d::transpose() {
 // TODO: Implement transpose
}

void Matrix3d::transpose(Matrix3d matrix3d1) {
 // TODO: Implement transpose
}

void Matrix3d::set(Quat4d quat4d) {
 // TODO: Implement set
}

void Matrix3d::set(AxisAngle4d axisAngle4d) {
 // TODO: Implement set
}

void Matrix3d::set(Quat4f quat4f) {
 // TODO: Implement set
}

void Matrix3d::set(AxisAngle4f axisAngle4f) {
 // TODO: Implement set
}

void Matrix3d::set(Matrix3f matrix3f) {
 // TODO: Implement set
}

void Matrix3d::set(Matrix3d matrix3d0) {
 // TODO: Implement set
}

void Matrix3d::set(double[] doubles) {
 // TODO: Implement set
}

void Matrix3d::invert(Matrix3d matrix3d1) {
 // TODO: Implement invert
}

void Matrix3d::invert() {
 // TODO: Implement invert
}

void Matrix3d::invertGeneral(Matrix3d matrix3d0) {
 // TODO: Implement invertGeneral
}

bool Matrix3d::luDecomposition(double[] doubles1, int[] ints) {
 // TODO: Implement luDecomposition
 return false;
}

void Matrix3d::luBacksubstitution(double[] doubles1, int[] ints, double[] doubles0) {
 // TODO: Implement luBacksubstitution
}

double Matrix3d::determinant() {
 // TODO: Implement determinant
 return 0;
}

void Matrix3d::set(double double0) {
 // TODO: Implement set
}

void Matrix3d::rotX(double double1) {
 // TODO: Implement rotX
}

void Matrix3d::rotY(double double1) {
 // TODO: Implement rotY
}

void Matrix3d::rotZ(double double1) {
 // TODO: Implement rotZ
}

void Matrix3d::mul(double double0) {
 // TODO: Implement mul
}

void Matrix3d::mul(double double0, Matrix3d matrix3d0) {
 // TODO: Implement mul
}

void Matrix3d::mul(Matrix3d matrix3d0) {
 // TODO: Implement mul
}

void Matrix3d::mul(Matrix3d matrix3d2, Matrix3d matrix3d1) {
 // TODO: Implement mul
}

void Matrix3d::mulNormalize(Matrix3d matrix3d0) {
 // TODO: Implement mulNormalize
}

void Matrix3d::mulNormalize(Matrix3d matrix3d1, Matrix3d matrix3d0) {
 // TODO: Implement mulNormalize
}

void Matrix3d::mulTransposeBoth(Matrix3d matrix3d2, Matrix3d matrix3d1) {
 // TODO: Implement mulTransposeBoth
}

void Matrix3d::mulTransposeRight(Matrix3d matrix3d2, Matrix3d matrix3d1) {
 // TODO: Implement mulTransposeRight
}

void Matrix3d::mulTransposeLeft(Matrix3d matrix3d2, Matrix3d matrix3d1) {
 // TODO: Implement mulTransposeLeft
}

void Matrix3d::normalize() {
 // TODO: Implement normalize
}

void Matrix3d::normalize(Matrix3d matrix3d0) {
 // TODO: Implement normalize
}

void Matrix3d::normalizeCP() {
 // TODO: Implement normalizeCP
}

void Matrix3d::normalizeCP(Matrix3d matrix3d0) {
 // TODO: Implement normalizeCP
}

bool Matrix3d::equals(Matrix3d matrix3d0) {
 // TODO: Implement equals
 return false;
}

bool Matrix3d::equals(void* object) {
 // TODO: Implement equals
 return false;
}

bool Matrix3d::epsilonEquals(Matrix3d matrix3d0, double double1) {
 // TODO: Implement epsilonEquals
 return false;
}

int Matrix3d::hashCode() {
 // TODO: Implement hashCode
 return 0;
}

void Matrix3d::setZero() {
 // TODO: Implement setZero
}

void Matrix3d::negate() {
 // TODO: Implement negate
}

void Matrix3d::negate(Matrix3d matrix3d0) {
 // TODO: Implement negate
}

void Matrix3d::transform(Tuple3d tuple3d) {
 // TODO: Implement transform
}

void Matrix3d::transform(Tuple3d tuple3d0, Tuple3d tuple3d1) {
 // TODO: Implement transform
}

void Matrix3d::getScaleRotate(double[] doubles1, double[] doubles2) {
 // TODO: Implement getScaleRotate
}

void Matrix3d::compute_svd(double[] doubles7, double[] doubles8, double[] doubles9) {
 // TODO: Implement compute_svd
}

void Matrix3d::svdReorder(double[] doubles7, double[] doubles4, double[] doubles3, double[] doubles2, double[] doubles5, double[] doubles6) {
 // TODO: Implement svdReorder
}

int Matrix3d::compute_qr(double[] doubles6, double[] doubles5, double[] doubles7, double[] doubles8) {
 // TODO: Implement compute_qr
 return 0;
}

double Matrix3d::max(double double0, double double1) {
 // TODO: Implement max
 return 0;
}

double Matrix3d::min(double double0, double double1) {
 // TODO: Implement min
 return 0;
}

double Matrix3d::d_sign(double double1, double double2) {
 // TODO: Implement d_sign
 return 0;
}

double Matrix3d::compute_shift(double double1, double double3, double double5) {
 // TODO: Implement compute_shift
 return 0;
}

double Matrix3d::compute_rot(double double4, double double3, double[] doubles0, double[] doubles1, int int4, int var7) {
 // TODO: Implement compute_rot
 return 0;
}

void Matrix3d::print_mat(double[] doubles) {
 // TODO: Implement print_mat
}

void Matrix3d::print_det(double[] doubles) {
 // TODO: Implement print_det
}

void Matrix3d::mat_mul(double[] doubles2, double[] doubles1, double[] doubles3) {
 // TODO: Implement mat_mul
}

void Matrix3d::transpose_mat(double[] doubles0, double[] doubles1) {
 // TODO: Implement transpose_mat
}

double Matrix3d::max3(double[] doubles) {
 // TODO: Implement max3
 return 0;
}

bool Matrix3d::almostEqual(double double0, double double1) {
 // TODO: Implement almostEqual
 return false;
}

void* Matrix3d::clone() {
 // TODO: Implement clone
 return nullptr;
}

double Matrix3d::getM00() {
 // TODO: Implement getM00
 return 0;
}

void Matrix3d::setM00(double double0) {
 // TODO: Implement setM00
}

double Matrix3d::getM01() {
 // TODO: Implement getM01
 return 0;
}

void Matrix3d::setM01(double double0) {
 // TODO: Implement setM01
}

double Matrix3d::getM02() {
 // TODO: Implement getM02
 return 0;
}

void Matrix3d::setM02(double double0) {
 // TODO: Implement setM02
}

double Matrix3d::getM10() {
 // TODO: Implement getM10
 return 0;
}

void Matrix3d::setM10(double double0) {
 // TODO: Implement setM10
}

double Matrix3d::getM11() {
 // TODO: Implement getM11
 return 0;
}

void Matrix3d::setM11(double double0) {
 // TODO: Implement setM11
}

double Matrix3d::getM12() {
 // TODO: Implement getM12
 return 0;
}

void Matrix3d::setM12(double double0) {
 // TODO: Implement setM12
}

double Matrix3d::getM20() {
 // TODO: Implement getM20
 return 0;
}

void Matrix3d::setM20(double double0) {
 // TODO: Implement setM20
}

double Matrix3d::getM21() {
 // TODO: Implement getM21
 return 0;
}

void Matrix3d::setM21(double double0) {
 // TODO: Implement setM21
}

double Matrix3d::getM22() {
 // TODO: Implement getM22
 return 0;
}

void Matrix3d::setM22(double double0) {
 // TODO: Implement setM22
}

} // namespace vecmath
} // namespace javax
