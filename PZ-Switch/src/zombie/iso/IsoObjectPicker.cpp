#include "zombie/iso/IsoObjectPicker.h"

namespace zombie {
namespace iso {

int IsoObjectPicker::compare(IsoObjectPicker.ClickObject clickObject0,
 IsoObjectPicker.ClickObject clickObject1) {
 // TODO: Implement compare
 return 0;
}

IsoObjectPicker IsoObjectPicker::getInstance() {
 // TODO: Implement getInstance
 return nullptr;
}

void IsoObjectPicker::Add(int x, int y, int width, int height,
 IsoGridSquare gridSquare, IsoObject tile, bool flip,
 float scaleX, float scaleY) {
 // TODO: Implement Add
}

void IsoObjectPicker::Init() {
 // TODO: Implement Init
}

void IsoObjectPicker::StartRender() {
 // TODO: Implement StartRender
}

IsoMovingObject IsoObjectPicker::PickTarget(int xx, int yy) {
 // TODO: Implement PickTarget
 return nullptr;
}

IsoObject IsoObjectPicker::PickDoor(int screenX, int screenY,
 bool bTransparent) {
 // TODO: Implement PickDoor
 return nullptr;
}

IsoObject IsoObjectPicker::PickWindow(int screenX, int screenY) {
 // TODO: Implement PickWindow
 return nullptr;
}

IsoObject IsoObjectPicker::PickWindowFrame(int screenX, int screenY) {
 // TODO: Implement PickWindowFrame
 return nullptr;
}

IsoObject IsoObjectPicker::PickThumpable(int screenX, int screenY) {
 // TODO: Implement PickThumpable
 return nullptr;
}

IsoObject IsoObjectPicker::PickHoppable(int screenX, int screenY) {
 // TODO: Implement PickHoppable
 return nullptr;
}

IsoObject IsoObjectPicker::PickCorpse(int screenX, int screenY) {
 // TODO: Implement PickCorpse
 return nullptr;
}

IsoObject IsoObjectPicker::PickTree(int screenX, int screenY) {
 // TODO: Implement PickTree
 return nullptr;
}

BaseVehicle IsoObjectPicker::PickVehicle(int screenX, int screenY) {
 // TODO: Implement PickVehicle
 return nullptr;
}

int IsoObjectPicker::calculateScore() {
 // TODO: Implement calculateScore
 return 0;
}

int IsoObjectPicker::getScore() {
 // TODO: Implement getScore
 return 0;
}

} // namespace iso
} // namespace zombie
