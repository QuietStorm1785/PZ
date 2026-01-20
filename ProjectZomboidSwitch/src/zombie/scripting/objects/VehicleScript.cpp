#include <string>
#include <vector>
#include "zombie\scripting\objects/VehicleScript.h"

namespace zombie {
namespace scripting {
namespace objects {

public VehicleScript::VehicleScript() {
    // TODO: Implement VehicleScript
    return nullptr;
}

void VehicleScript::Load(const std::string& var1, const std::string& var2) {
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

void VehicleScript::LoadVector2f(const std::string& var1, Vector2f var2) {
    // TODO: Implement LoadVector2f
}

void VehicleScript::LoadVector3f(const std::string& var1, Vector3f var2) {
    // TODO: Implement LoadVector3f
}

void VehicleScript::LoadVector4f(const std::string& var1, Vector4f var2) {
    // TODO: Implement LoadVector4f
}

void VehicleScript::LoadVector2i(const std::string& var1, Vector2i var2) {
    // TODO: Implement LoadVector2i
}

ModelAttachment VehicleScript::LoadAttachment(Block var1) {
    // TODO: Implement LoadAttachment
    return nullptr;
}

Model VehicleScript::LoadModel(Block var1, std::vector<Model> var2) {
    // TODO: Implement LoadModel
    return nullptr;
}

Skin VehicleScript::LoadSkin(Block var1) {
    // TODO: Implement LoadSkin
    return nullptr;
}

Wheel VehicleScript::LoadWheel(Block var1) {
    // TODO: Implement LoadWheel
    return nullptr;
}

Passenger VehicleScript::LoadPassenger(Block var1) {
    // TODO: Implement LoadPassenger
    return nullptr;
}

Anim VehicleScript::LoadAnim(Block var1, std::vector<Anim> var2) {
    // TODO: Implement LoadAnim
    return nullptr;
}

SwitchSeat VehicleScript::LoadPassengerSwitchSeat(Block var1, Passenger var2) {
    // TODO: Implement LoadPassengerSwitchSeat
    return nullptr;
}

Area VehicleScript::LoadArea(Block var1) {
    // TODO: Implement LoadArea
    return nullptr;
}

Part VehicleScript::LoadPart(Block var1) {
    // TODO: Implement LoadPart
    return nullptr;
}

PhysicsShape VehicleScript::LoadPhysicsShape(Block var1) {
    // TODO: Implement LoadPhysicsShape
    return nullptr;
}

Door VehicleScript::LoadDoor(Block var1) {
    // TODO: Implement LoadDoor
    return nullptr;
}

Window VehicleScript::LoadWindow(Block var1) {
    // TODO: Implement LoadWindow
    return nullptr;
}

Container VehicleScript::LoadContainer(Block var1, Container var2) {
    // TODO: Implement LoadContainer
    return nullptr;
}

void* VehicleScript::checkIntegerKey(void* var1) {
    // TODO: Implement checkIntegerKey
    return nullptr;
}

KahluaTable VehicleScript::LoadTable(Block var1, KahluaTable var2) {
    // TODO: Implement LoadTable
    return nullptr;
}

void VehicleScript::LoadTemplate(const std::string& var1) {
    // TODO: Implement LoadTemplate
}

void VehicleScript::copyAreasFrom(VehicleScript var1, const std::string& var2) {
    // TODO: Implement copyAreasFrom
}

void VehicleScript::copyPartsFrom(VehicleScript var1, const std::string& var2) {
    // TODO: Implement copyPartsFrom
}

void VehicleScript::copyPassengersFrom(VehicleScript var1, const std::string& var2) {
    // TODO: Implement copyPassengersFrom
}

void VehicleScript::copyWheelsFrom(VehicleScript var1, const std::string& var2) {
    // TODO: Implement copyWheelsFrom
}

Position VehicleScript::LoadPosition(Block var1, std::vector<Position> var2) {
    // TODO: Implement LoadPosition
    return nullptr;
}

void VehicleScript::initCrawlOffsets() {
    // TODO: Implement initCrawlOffsets
}

void VehicleScript::initCrawlOffsets(Wheel var1) {
    // TODO: Implement initCrawlOffsets
}

bool VehicleScript::isOverlappingWheel(float var1) {
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

Model VehicleScript::getModel() {
    // TODO: Implement getModel
    return nullptr;
}

Vector3f VehicleScript::getModelOffset() {
    // TODO: Implement getModelOffset
    return nullptr;
}

float VehicleScript::getModelScale() {
    // TODO: Implement getModelScale
    return 0;
}

void VehicleScript::setModelScale(float var1) {
    // TODO: Implement setModelScale
}

int VehicleScript::getModelCount() {
    // TODO: Implement getModelCount
    return 0;
}

Model VehicleScript::getModelByIndex(int var1) {
    // TODO: Implement getModelByIndex
    return nullptr;
}

Model VehicleScript::getModelById(const std::string& var1, std::vector<Model> var2) {
    // TODO: Implement getModelById
    return nullptr;
}

Model VehicleScript::getModelById(const std::string& var1) {
    // TODO: Implement getModelById
    return nullptr;
}

int VehicleScript::getAttachmentCount() {
    // TODO: Implement getAttachmentCount
    return 0;
}

ModelAttachment VehicleScript::getAttachment(int var1) {
    // TODO: Implement getAttachment
    return nullptr;
}

ModelAttachment VehicleScript::getAttachmentById(const std::string& var1) {
    // TODO: Implement getAttachmentById
    return nullptr;
}

ModelAttachment VehicleScript::addAttachment(ModelAttachment var1) {
    // TODO: Implement addAttachment
    return nullptr;
}

ModelAttachment VehicleScript::removeAttachment(ModelAttachment var1) {
    // TODO: Implement removeAttachment
    return nullptr;
}

ModelAttachment VehicleScript::addAttachmentAt(int var1, ModelAttachment var2) {
    // TODO: Implement addAttachmentAt
    return nullptr;
}

ModelAttachment VehicleScript::removeAttachment(int var1) {
    // TODO: Implement removeAttachment
    return nullptr;
}

LightBar VehicleScript::getLightbar() {
    // TODO: Implement getLightbar
    return nullptr;
}

Sounds VehicleScript::getSounds() {
    // TODO: Implement getSounds
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

float VehicleScript::getSteeringClamp(float var1) {
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

Wheel VehicleScript::getWheel(int var1) {
    // TODO: Implement getWheel
    return nullptr;
}

Wheel VehicleScript::getWheelById(const std::string& var1) {
    // TODO: Implement getWheelById
    return nullptr;
}

int VehicleScript::getIndexOfWheelById(const std::string& var1) {
    // TODO: Implement getIndexOfWheelById
    return 0;
}

int VehicleScript::getPassengerCount() {
    // TODO: Implement getPassengerCount
    return 0;
}

Passenger VehicleScript::getPassenger(int var1) {
    // TODO: Implement getPassenger
    return nullptr;
}

Passenger VehicleScript::getPassengerById(const std::string& var1) {
    // TODO: Implement getPassengerById
    return nullptr;
}

int VehicleScript::getPassengerIndex(const std::string& var1) {
    // TODO: Implement getPassengerIndex
    return 0;
}

int VehicleScript::getPhysicsShapeCount() {
    // TODO: Implement getPhysicsShapeCount
    return 0;
}

PhysicsShape VehicleScript::getPhysicsShape(int var1) {
    // TODO: Implement getPhysicsShape
    return nullptr;
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

Skin VehicleScript::getTextures() {
    // TODO: Implement getTextures
    return nullptr;
}

int VehicleScript::getSkinCount() {
    // TODO: Implement getSkinCount
    return 0;
}

Skin VehicleScript::getSkin(int var1) {
    // TODO: Implement getSkin
    return nullptr;
}

int VehicleScript::getAreaCount() {
    // TODO: Implement getAreaCount
    return 0;
}

Area VehicleScript::getArea(int var1) {
    // TODO: Implement getArea
    return nullptr;
}

Area VehicleScript::getAreaById(const std::string& var1) {
    // TODO: Implement getAreaById
    return nullptr;
}

int VehicleScript::getIndexOfAreaById(const std::string& var1) {
    // TODO: Implement getIndexOfAreaById
    return 0;
}

int VehicleScript::getPartCount() {
    // TODO: Implement getPartCount
    return 0;
}

Part VehicleScript::getPart(int var1) {
    // TODO: Implement getPart
    return nullptr;
}

Part VehicleScript::getPartById(const std::string& var1) {
    // TODO: Implement getPartById
    return nullptr;
}

int VehicleScript::getIndexOfPartById(const std::string& var1) {
    // TODO: Implement getIndexOfPartById
    return 0;
}

Anim VehicleScript::getAnimationById(const std::string& var1, std::vector<Anim> var2) {
    // TODO: Implement getAnimationById
    return nullptr;
}

Position VehicleScript::getPositionById(const std::string& var1, std::vector<Position> var2) {
    // TODO: Implement getPositionById
    return nullptr;
}

bool VehicleScript::globMatch(const std::string& var1, const std::string& var2) {
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

void VehicleScript::setSeats(int var1) {
    // TODO: Implement setSeats
}

int VehicleScript::getMechanicType() {
    // TODO: Implement getMechanicType
    return 0;
}

void VehicleScript::setMechanicType(int var1) {
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

void VehicleScript::setEngineRepairLevel(int var1) {
    // TODO: Implement setEngineRepairLevel
}

float VehicleScript::getPlayerDamageProtection() {
    // TODO: Implement getPlayerDamageProtection
    return 0;
}

void VehicleScript::setPlayerDamageProtection(float var1) {
    // TODO: Implement setPlayerDamageProtection
}

float VehicleScript::getForcedHue() {
    // TODO: Implement getForcedHue
    return 0;
}

void VehicleScript::setForcedHue(float var1) {
    // TODO: Implement setForcedHue
}

float VehicleScript::getForcedSat() {
    // TODO: Implement getForcedSat
    return 0;
}

void VehicleScript::setForcedSat(float var1) {
    // TODO: Implement setForcedSat
}

float VehicleScript::getForcedVal() {
    // TODO: Implement getForcedVal
    return 0;
}

void VehicleScript::setForcedVal(float var1) {
    // TODO: Implement setForcedVal
}

std::string VehicleScript::getEngineRPMType() {
    // TODO: Implement getEngineRPMType
    return "";
}

void VehicleScript::setEngineRPMType(const std::string& var1) {
    // TODO: Implement setEngineRPMType
}

float VehicleScript::getOffroadEfficiency() {
    // TODO: Implement getOffroadEfficiency
    return 0;
}

void VehicleScript::setOffroadEfficiency(float var1) {
    // TODO: Implement setOffroadEfficiency
}

std::vector<float> VehicleScript::getCrawlOffsets() {
    // TODO: Implement getCrawlOffsets
    return nullptr;
}

} // namespace objects
} // namespace scripting
} // namespace zombie
