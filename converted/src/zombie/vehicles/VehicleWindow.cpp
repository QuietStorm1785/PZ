#include "zombie/vehicles/VehicleWindow.h"

namespace zombie {
namespace vehicles {

void VehicleWindow::init(VehicleScript.Window scriptWindow) {
 // TODO: Implement init
}

int VehicleWindow::getHealth() {
 // TODO: Implement getHealth
 return 0;
}

void VehicleWindow::setHealth(int _health) {
 // TODO: Implement setHealth
}

bool VehicleWindow::isDestroyed() {
 // TODO: Implement isDestroyed
 return false;
}

bool VehicleWindow::isOpenable() {
 // TODO: Implement isOpenable
 return false;
}

bool VehicleWindow::isOpen() {
 // TODO: Implement isOpen
 return false;
}

void VehicleWindow::setOpen(bool _open) {
 // TODO: Implement setOpen
}

void VehicleWindow::setOpenDelta(float delta) {
 // TODO: Implement setOpenDelta
}

float VehicleWindow::getOpenDelta() {
 // TODO: Implement getOpenDelta
 return 0;
}

bool VehicleWindow::isHittable() {
 // TODO: Implement isHittable
 return false;
}

void VehicleWindow::hit(IsoGameCharacter chr) {
 // TODO: Implement hit
}

void VehicleWindow::damage(int amount) {
 // TODO: Implement damage
}

void VehicleWindow::save(ByteBuffer output) {
 // TODO: Implement save
}

void VehicleWindow::load(ByteBuffer input, int WorldVersion) {
 // TODO: Implement load
}

} // namespace vehicles
} // namespace zombie
