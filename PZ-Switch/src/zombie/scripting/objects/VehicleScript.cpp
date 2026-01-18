#include "zombie/scripting/objects/VehicleScript.h"

namespace zombie {
namespace scripting {
namespace objects {

public
VehicleScript::VehicleScript() {
 // TODO: Implement VehicleScript
 return nullptr;
}

void VehicleScript::Load(const std::string &_name,
 const std::string &totalFile) {
 // TODO: Implement Load
}

std::string VehicleScript::getFileName() {
 // TODO: Implement getFileName
 return "";
}

void VehicleScript::Loaded() {
 // TODO: Implement Loaded
}

void VehicleScript::toBullet() {
 // TODO: Implement toBullet
}

void VehicleScript::LoadVector2f(const std::string &string, Vector2f vector2f) {
 // TODO: Implement LoadVector2f
}

void VehicleScript::LoadVector3f(const std::string &string, Vector3f vector3f) {
 // TODO: Implement LoadVector3f
}

void VehicleScript::LoadVector4f(const std::string &string, Vector4f vector4f) {
 // TODO: Implement LoadVector4f
}

void VehicleScript::LoadVector2i(const std::string &string, Vector2i vector2i) {
 // TODO: Implement LoadVector2i
}

ModelAttachment VehicleScript::LoadAttachment(ScriptParser.Block block) {
 // TODO: Implement LoadAttachment
 return nullptr;
}

void *VehicleScript::checkIntegerKey(void *object) {
 // TODO: Implement checkIntegerKey
 return nullptr;
}

KahluaTable VehicleScript::LoadTable(ScriptParser.Block block0,
 KahluaTable table1) {
 // TODO: Implement LoadTable
 return nullptr;
}

void VehicleScript::LoadTemplate(const std::string &string0) {
 // TODO: Implement LoadTemplate
}

void VehicleScript::copyAreasFrom(VehicleScript other,
 const std::string &spec) {
 // TODO: Implement copyAreasFrom
}

void VehicleScript::copyPartsFrom(VehicleScript other,
 const std::string &spec) {
 // TODO: Implement copyPartsFrom
}

void VehicleScript::copyPassengersFrom(VehicleScript other,
 const std::string &spec) {
 // TODO: Implement copyPassengersFrom
}

void VehicleScript::copyWheelsFrom(VehicleScript other,
 const std::string &spec) {
 // TODO: Implement copyWheelsFrom
}

void VehicleScript::initCrawlOffsets() {
 // TODO: Implement initCrawlOffsets
}

void VehicleScript::initCrawlOffsets(VehicleScript.Wheel wheel) {
 // TODO: Implement initCrawlOffsets
}

bool VehicleScript::isOverlappingWheel(float float2) {
 // TODO: Implement isOverlappingWheel
 return false;
}

std::string VehicleScript::getName() {
 // TODO: Implement getName
 return "";
}

std::string VehicleScript::getFullName() {
 // TODO: Implement getFullName
 return "";
}

Vector3f VehicleScript::getModelOffset() {
 // TODO: Implement getModelOffset
 return nullptr;
}

float VehicleScript::getModelScale() {
 // TODO: Implement getModelScale
 return 0;
}

void VehicleScript::setModelScale(float scale) {
 // TODO: Implement setModelScale
}

int VehicleScript::getModelCount() {
 // TODO: Implement getModelCount
 return 0;
}

int VehicleScript::getAttachmentCount() {
 // TODO: Implement getAttachmentCount
 return 0;
}

ModelAttachment VehicleScript::getAttachment(int index) {
 // TODO: Implement getAttachment
 return nullptr;
}

ModelAttachment VehicleScript::getAttachmentById(const std::string &id) {
 // TODO: Implement getAttachmentById
 return nullptr;
}

ModelAttachment VehicleScript::addAttachment(ModelAttachment attach) {
 // TODO: Implement addAttachment
 return nullptr;
}

ModelAttachment VehicleScript::removeAttachment(ModelAttachment attach) {
 // TODO: Implement removeAttachment
 return nullptr;
}

ModelAttachment VehicleScript::addAttachmentAt(int index,
 ModelAttachment attach) {
 // TODO: Implement addAttachmentAt
 return nullptr;
}

ModelAttachment VehicleScript::removeAttachment(int index) {
 // TODO: Implement removeAttachment
 return nullptr;
}

bool VehicleScript::getHasSiren() {
 // TODO: Implement getHasSiren
 return false;
}

Vector3f VehicleScript::getExtents() {
 // TODO: Implement getExtents
 return nullptr;
}

Vector3f VehicleScript::getPhysicsChassisShape() {
 // TODO: Implement getPhysicsChassisShape
 return nullptr;
}

Vector2f VehicleScript::getShadowExtents() {
 // TODO: Implement getShadowExtents
 return nullptr;
}

Vector2f VehicleScript::getShadowOffset() {
 // TODO: Implement getShadowOffset
 return nullptr;
}

Vector2f VehicleScript::getExtentsOffset() {
 // TODO: Implement getExtentsOffset
 return nullptr;
}

float VehicleScript::getMass() {
 // TODO: Implement getMass
 return 0;
}

Vector3f VehicleScript::getCenterOfMassOffset() {
 // TODO: Implement getCenterOfMassOffset
 return nullptr;
}

float VehicleScript::getEngineForce() {
 // TODO: Implement getEngineForce
 return 0;
}

float VehicleScript::getEngineIdleSpeed() {
 // TODO: Implement getEngineIdleSpeed
 return 0;
}

int VehicleScript::getEngineQuality() {
 // TODO: Implement getEngineQuality
 return 0;
}

int VehicleScript::getEngineLoudness() {
 // TODO: Implement getEngineLoudness
 return 0;
}

float VehicleScript::getRollInfluence() {
 // TODO: Implement getRollInfluence
 return 0;
}

float VehicleScript::getSteeringIncrement() {
 // TODO: Implement getSteeringIncrement
 return 0;
}

float VehicleScript::getSteeringClamp(float speed) {
 // TODO: Implement getSteeringClamp
 return 0;
}

float VehicleScript::getSuspensionStiffness() {
 // TODO: Implement getSuspensionStiffness
 return 0;
}

float VehicleScript::getSuspensionDamping() {
 // TODO: Implement getSuspensionDamping
 return 0;
}

float VehicleScript::getSuspensionCompression() {
 // TODO: Implement getSuspensionCompression
 return 0;
}

float VehicleScript::getSuspensionRestLength() {
 // TODO: Implement getSuspensionRestLength
 return 0;
}

float VehicleScript::getSuspensionTravel() {
 // TODO: Implement getSuspensionTravel
 return 0;
}

float VehicleScript::getWheelFriction() {
 // TODO: Implement getWheelFriction
 return 0;
}

int VehicleScript::getWheelCount() {
 // TODO: Implement getWheelCount
 return 0;
}

int VehicleScript::getIndexOfWheelById(const std::string &id) {
 // TODO: Implement getIndexOfWheelById
 return 0;
}

int VehicleScript::getPassengerCount() {
 // TODO: Implement getPassengerCount
 return 0;
}

int VehicleScript::getPassengerIndex(const std::string &id) {
 // TODO: Implement getPassengerIndex
 return 0;
}

int VehicleScript::getPhysicsShapeCount() {
 // TODO: Implement getPhysicsShapeCount
 return 0;
}

int VehicleScript::getFrontEndHealth() {
 // TODO: Implement getFrontEndHealth
 return 0;
}

int VehicleScript::getRearEndHealth() {
 // TODO: Implement getRearEndHealth
 return 0;
}

int VehicleScript::getStorageCapacity() {
 // TODO: Implement getStorageCapacity
 return 0;
}

int VehicleScript::getSkinCount() {
 // TODO: Implement getSkinCount
 return 0;
}

int VehicleScript::getAreaCount() {
 // TODO: Implement getAreaCount
 return 0;
}

int VehicleScript::getIndexOfAreaById(const std::string &id) {
 // TODO: Implement getIndexOfAreaById
 return 0;
}

int VehicleScript::getPartCount() {
 // TODO: Implement getPartCount
 return 0;
}

int VehicleScript::getIndexOfPartById(const std::string &id) {
 // TODO: Implement getIndexOfPartById
 return 0;
}

bool VehicleScript::globMatch(const std::string &pattern,
 const std::string &str) {
 // TODO: Implement globMatch
 return false;
}

int VehicleScript::getGearRatioCount() {
 // TODO: Implement getGearRatioCount
 return 0;
}

int VehicleScript::getSeats() {
 // TODO: Implement getSeats
 return 0;
}

void VehicleScript::setSeats(int _seats) {
 // TODO: Implement setSeats
}

int VehicleScript::getMechanicType() {
 // TODO: Implement getMechanicType
 return 0;
}

void VehicleScript::setMechanicType(int _mechanicType) {
 // TODO: Implement setMechanicType
}

int VehicleScript::getEngineRepairLevel() {
 // TODO: Implement getEngineRepairLevel
 return 0;
}

int VehicleScript::getHeadlightConfigLevel() {
 // TODO: Implement getHeadlightConfigLevel
 return 0;
}

void VehicleScript::setEngineRepairLevel(int _engineRepairLevel) {
 // TODO: Implement setEngineRepairLevel
}

float VehicleScript::getPlayerDamageProtection() {
 // TODO: Implement getPlayerDamageProtection
 return 0;
}

void VehicleScript::setPlayerDamageProtection(float _playerDamageProtection) {
 // TODO: Implement setPlayerDamageProtection
}

float VehicleScript::getForcedHue() {
 // TODO: Implement getForcedHue
 return 0;
}

void VehicleScript::setForcedHue(float _forcedHue) {
 // TODO: Implement setForcedHue
}

float VehicleScript::getForcedSat() {
 // TODO: Implement getForcedSat
 return 0;
}

void VehicleScript::setForcedSat(float _forcedSat) {
 // TODO: Implement setForcedSat
}

float VehicleScript::getForcedVal() {
 // TODO: Implement getForcedVal
 return 0;
}

void VehicleScript::setForcedVal(float _forcedVal) {
 // TODO: Implement setForcedVal
}

std::string VehicleScript::getEngineRPMType() {
 // TODO: Implement getEngineRPMType
 return "";
}

void VehicleScript::setEngineRPMType(const std::string &_engineRPMType) {
 // TODO: Implement setEngineRPMType
}

float VehicleScript::getOffroadEfficiency() {
 // TODO: Implement getOffroadEfficiency
 return 0;
}

void VehicleScript::setOffroadEfficiency(float _offroadEfficiency) {
 // TODO: Implement setOffroadEfficiency
}

TFloatArrayList VehicleScript::getCrawlOffsets() {
 // TODO: Implement getCrawlOffsets
 return nullptr;
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

double VehicleScript::getX() {
 // TODO: Implement getX
 return 0;
}

double VehicleScript::getY() {
 // TODO: Implement getY
 return 0;
}

double VehicleScript::getW() {
 // TODO: Implement getW
 return 0;
}

double VehicleScript::getH() {
 // TODO: Implement getH
 return 0;
}

void VehicleScript::setX(double d) {
 // TODO: Implement setX
}

void VehicleScript::setY(double d) {
 // TODO: Implement setY
}

void VehicleScript::setW(double d) {
 // TODO: Implement setW
}

void VehicleScript::setH(double d) {
 // TODO: Implement setH
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

Vector3f VehicleScript::getOffset() {
 // TODO: Implement getOffset
 return nullptr;
}

Vector3f VehicleScript::getRotate() {
 // TODO: Implement getRotate
 return nullptr;
}

bool VehicleScript::isMechanicRequireKey() {
 // TODO: Implement isMechanicRequireKey
 return false;
}

void VehicleScript::setMechanicRequireKey(bool _mechanicRequireKey) {
 // TODO: Implement setMechanicRequireKey
}

bool VehicleScript::isRepairMechanic() {
 // TODO: Implement isRepairMechanic
 return false;
}

void VehicleScript::setRepairMechanic(bool _repairMechanic) {
 // TODO: Implement setRepairMechanic
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

int VehicleScript::getPositionCount() {
 // TODO: Implement getPositionCount
 return 0;
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

std::string VehicleScript::getTypeString() {
 // TODO: Implement getTypeString
 return "";
}

Vector3f VehicleScript::getOffset() {
 // TODO: Implement getOffset
 return nullptr;
}

Vector3f VehicleScript::getExtents() {
 // TODO: Implement getExtents
 return nullptr;
}

Vector3f VehicleScript::getRotate() {
 // TODO: Implement getRotate
 return nullptr;
}

float VehicleScript::getRadius() {
 // TODO: Implement getRadius
 return 0;
}

void VehicleScript::setRadius(float _radius) {
 // TODO: Implement setRadius
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

Vector3f VehicleScript::getOffset() {
 // TODO: Implement getOffset
 return nullptr;
}

Vector3f VehicleScript::getRotate() {
 // TODO: Implement getRotate
 return nullptr;
}

std::string VehicleScript::getArea() {
 // TODO: Implement getArea
 return "";
}

void VehicleScript::copyMissingFrom(VehicleScript.Skin other) {
 // TODO: Implement copyMissingFrom
}

std::string VehicleScript::getId() {
 // TODO: Implement getId
 return "";
}

Vector3f VehicleScript::getOffset() {
 // TODO: Implement getOffset
 return nullptr;
}

} // namespace objects
} // namespace scripting
} // namespace zombie
