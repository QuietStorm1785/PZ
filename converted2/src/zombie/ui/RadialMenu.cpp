#include "zombie/ui/RadialMenu.h"

namespace zombie {
namespace ui {

public
RadialMenu::RadialMenu(int x, int y, int _innerRadius, int _outerRadius) {
  // TODO: Implement RadialMenu
  return nullptr;
}

void RadialMenu::update() {
  // TODO: Implement update
}

void RadialMenu::render() {
  // TODO: Implement render
}

void RadialMenu::formatTextInsideCircle(const std::string &string) {
  // TODO: Implement formatTextInsideCircle
}

void RadialMenu::clear() {
  // TODO: Implement clear
}

void RadialMenu::addSlice(const std::string &text, Texture texture) {
  // TODO: Implement addSlice
}

void RadialMenu::setSliceText(int sliceIndex, const std::string &text) {
  // TODO: Implement setSliceText
}

void RadialMenu::setSliceTexture(int sliceIndex, Texture texture) {
  // TODO: Implement setSliceTexture
}

float RadialMenu::getStartAngle() {
  // TODO: Implement getStartAngle
  return 0;
}

int RadialMenu::getSliceIndexFromMouse(int mx, int my) {
  // TODO: Implement getSliceIndexFromMouse
  return 0;
}

int RadialMenu::getSliceIndexFromJoypad(int _joypad) {
  // TODO: Implement getSliceIndexFromJoypad
  return 0;
}

void RadialMenu::setJoypad(int _joypad) {
  // TODO: Implement setJoypad
}

bool RadialMenu::isEmpty() {
  // TODO: Implement isEmpty
  return false;
}

} // namespace ui
} // namespace zombie
