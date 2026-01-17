#include "zombie/ui/ObjectTooltip.h"

namespace zombie {
namespace ui {

public
ObjectTooltip::ObjectTooltip() {
  // TODO: Implement ObjectTooltip
  return nullptr;
}

void ObjectTooltip::checkFont() {
  // TODO: Implement checkFont
}

UIFont ObjectTooltip::getFont() {
  // TODO: Implement getFont
  return nullptr;
}

int ObjectTooltip::getLineSpacing() {
  // TODO: Implement getLineSpacing
  return 0;
}

void ObjectTooltip::DrawText(UIFont _font, const std::string &text, double x,
                             double y, double r, double g, double b,
                             double _alpha) {
  // TODO: Implement DrawText
}

void ObjectTooltip::DrawTextCentre(UIFont _font, const std::string &text,
                                   double x, double y, double r, double g,
                                   double b, double _alpha) {
  // TODO: Implement DrawTextCentre
}

void ObjectTooltip::DrawTextRight(UIFont _font, const std::string &text,
                                  double x, double y, double r, double g,
                                  double b, double _alpha) {
  // TODO: Implement DrawTextRight
}

void ObjectTooltip::DrawValueRight(int value, int x, int y, bool highGood) {
  // TODO: Implement DrawValueRight
}

void ObjectTooltip::DrawValueRightNoPlus(int value, int x, int y) {
  // TODO: Implement DrawValueRightNoPlus
}

void ObjectTooltip::DrawValueRightNoPlus(float value, int x, int y) {
  // TODO: Implement DrawValueRightNoPlus
}

void ObjectTooltip::DrawTextureScaled(Texture tex, double x, double y,
                                      double width, double height,
                                      double _alpha) {
  // TODO: Implement DrawTextureScaled
}

void ObjectTooltip::DrawTextureScaledAspect(Texture tex, double x, double y,
                                            double width, double height,
                                            double r, double g, double b,
                                            double _alpha) {
  // TODO: Implement DrawTextureScaledAspect
}

void ObjectTooltip::DrawProgressBar(int x, int y, int w, int h, float f,
                                    double r, double g, double b, double a) {
  // TODO: Implement DrawProgressBar
}

bool ObjectTooltip::onMouseMove(double dx, double dy) {
  // TODO: Implement onMouseMove
  return false;
}

void ObjectTooltip::onMouseMoveOutside(double dx, double dy) {
  // TODO: Implement onMouseMoveOutside
}

void ObjectTooltip::render() {
  // TODO: Implement render
}

void ObjectTooltip::show(IsoObject obj, double x, double y) {
  // TODO: Implement show
}

void ObjectTooltip::hide() {
  // TODO: Implement hide
}

void ObjectTooltip::update() {
  // TODO: Implement update
}

void ObjectTooltip::show(InventoryItem item, int var2, int var3) {
  // TODO: Implement show
}

void ObjectTooltip::adjustWidth(int textX, const std::string &text) {
  // TODO: Implement adjustWidth
}

void ObjectTooltip::endLayout(ObjectTooltip.Layout layout) {
  // TODO: Implement endLayout
}

Texture ObjectTooltip::getTexture() {
  // TODO: Implement getTexture
  return nullptr;
}

void ObjectTooltip::setCharacter(IsoGameCharacter chr) {
  // TODO: Implement setCharacter
}

IsoGameCharacter ObjectTooltip::getCharacter() {
  // TODO: Implement getCharacter
  return nullptr;
}

void ObjectTooltip::setMeasureOnly(bool b) {
  // TODO: Implement setMeasureOnly
}

bool ObjectTooltip::isMeasureOnly() {
  // TODO: Implement isMeasureOnly
  return false;
}

float ObjectTooltip::getWeightOfStack() {
  // TODO: Implement getWeightOfStack
  return 0;
}

void ObjectTooltip::setWeightOfStack(float weight) {
  // TODO: Implement setWeightOfStack
}

void ObjectTooltip::setMinLabelWidth(int minWidth) {
  // TODO: Implement setMinLabelWidth
}

void ObjectTooltip::setMinValueWidth(int minWidth) {
  // TODO: Implement setMinValueWidth
}

int ObjectTooltip::render(int left, int top, ObjectTooltip ui) {
  // TODO: Implement render
  return 0;
}

void ObjectTooltip::free() {
  // TODO: Implement free
}

void ObjectTooltip::reset() {
  // TODO: Implement reset
}

void ObjectTooltip::setLabel(const std::string &_label, float r, float g,
                             float b, float a) {
  // TODO: Implement setLabel
}

void ObjectTooltip::setValue(const std::string &_label, float r, float g,
                             float b, float a) {
  // TODO: Implement setValue
}

void ObjectTooltip::setValueRight(int _value, bool highGood) {
  // TODO: Implement setValueRight
}

void ObjectTooltip::setValueRightNoPlus(float _value) {
  // TODO: Implement setValueRightNoPlus
}

void ObjectTooltip::setValueRightNoPlus(int _value) {
  // TODO: Implement setValueRightNoPlus
}

void ObjectTooltip::setProgress(float fraction, float r, float g, float b,
                                float a) {
  // TODO: Implement setProgress
}

void ObjectTooltip::calcSizes() {
  // TODO: Implement calcSizes
}

void ObjectTooltip::render(int x, int y, int mid, int right, ObjectTooltip ui) {
  // TODO: Implement render
}

} // namespace ui
} // namespace zombie
