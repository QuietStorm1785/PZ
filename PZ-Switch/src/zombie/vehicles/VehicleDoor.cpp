#include "zombie/vehicles/VehicleDoor.h"

namespace zombie {
namespace vehicles {

public
VehicleDoor::VehicleDoor(VehiclePart _part) {
 // TODO: Implement VehicleDoor
 return nullptr;
}

void VehicleDoor::init(VehicleScript.Door scriptDoor) {
 // TODO: Implement init
}

bool VehicleDoor::isOpen() {
 // TODO: Implement isOpen
 return false;
}

void VehicleDoor::setOpen(bool _open) {
 // TODO: Implement setOpen
}

bool VehicleDoor::isLocked() {
 // TODO: Implement isLocked
 return false;
}

void VehicleDoor::setLocked(bool _locked) {
 // TODO: Implement setLocked
}

bool VehicleDoor::isLockBroken() {
 // TODO: Implement isLockBroken
 return false;
}

void VehicleDoor::setLockBroken(bool broken) {
 // TODO: Implement setLockBroken
}

void VehicleDoor::save(ByteBuffer output) {
 // TODO: Implement save
}

void VehicleDoor::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

} // namespace vehicles
} // namespace zombie
