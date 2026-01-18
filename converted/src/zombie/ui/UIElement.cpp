#include "zombie/ui/UIElement.h"

namespace zombie {
namespace ui {

public UIElement::UIElement() {
 // TODO: Implement UIElement
 return nullptr;
}

public UIElement::UIElement(KahluaTable _table) {
 // TODO: Implement UIElement
 return nullptr;
}

double UIElement::getMaxDrawHeight() {
 // TODO: Implement getMaxDrawHeight
 return 0;
}

void UIElement::setMaxDrawHeight(double _height) {
 // TODO: Implement setMaxDrawHeight
}

void UIElement::clearMaxDrawHeight() {
 // TODO: Implement clearMaxDrawHeight
}

double UIElement::getXScroll() {
 // TODO: Implement getXScroll
 return 0;
}

void UIElement::setXScroll(double _x) {
 // TODO: Implement setXScroll
}

double UIElement::getYScroll() {
 // TODO: Implement getYScroll
 return 0;
}

void UIElement::setYScroll(double _y) {
 // TODO: Implement setYScroll
}

void UIElement::setAlwaysOnTop(bool b) {
 // TODO: Implement setAlwaysOnTop
}

void UIElement::backMost() {
 // TODO: Implement backMost
}

void UIElement::AddChild(UIElement el) {
 // TODO: Implement AddChild
}

void UIElement::RemoveChild(UIElement el) {
 // TODO: Implement RemoveChild
}

double UIElement::getScrollHeight() {
 // TODO: Implement getScrollHeight
 return 0;
}

void UIElement::setScrollHeight(double h) {
 // TODO: Implement setScrollHeight
}

bool UIElement::isConsumeMouseEvents() {
 // TODO: Implement isConsumeMouseEvents
 return false;
}

void UIElement::setConsumeMouseEvents(bool bConsume) {
 // TODO: Implement setConsumeMouseEvents
}

void UIElement::ClearChildren() {
 // TODO: Implement ClearChildren
}

void UIElement::ButtonClicked(const std::string& name) {
 // TODO: Implement ButtonClicked
}

void UIElement::DrawText(UIFont font, const std::string& text, double _x, double _y, double zoom, double r, double g, double b, double alpha) {
 // TODO: Implement DrawText
}

void UIElement::DrawText(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawText
}

void UIElement::DrawText(const std::string& text, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 // TODO: Implement DrawText
}

void UIElement::DrawText(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawText
}

void UIElement::DrawTextUntrimmed(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextUntrimmed
}

void UIElement::DrawTextCentre(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextCentre
}

void UIElement::DrawTextCentre(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextCentre
}

void UIElement::DrawTextRight(const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextRight
}

void UIElement::DrawTextRight(UIFont font, const std::string& text, double _x, double _y, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextRight
}

void UIElement::DrawTextureAngle(Texture tex, double centerX, double centerY, double angle, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureAngle
}

void UIElement::DrawTextureAngle(Texture tex, double centerX, double centerY, double angle) {
 // TODO: Implement DrawTextureAngle
}

void UIElement::DrawTexture(Texture tex, double _x, double _y, double alpha) {
 // TODO: Implement DrawTexture
}

void UIElement::DrawTextureCol(Texture tex, double _x, double _y, Color col) {
 // TODO: Implement DrawTextureCol
}

void UIElement::DrawTextureScaled(Texture tex, double _x, double _y, double _width, double _height, double alpha) {
 // TODO: Implement DrawTextureScaled
}

void UIElement::DrawTextureScaledUniform(Texture tex, double _x, double _y, double scale, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextureScaledUniform
}

void UIElement::DrawTextureScaledAspect(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextureScaledAspect
}

void UIElement::DrawTextureScaledAspect2(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double alpha) {
 // TODO: Implement DrawTextureScaledAspect2
}

void UIElement::DrawTextureScaledCol(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureScaledCol
}

void UIElement::DrawTextureScaledCol(Texture tex, double _x, double _y, double _width, double _height, Color col) {
 // TODO: Implement DrawTextureScaledCol
}

void UIElement::DrawTextureScaledColor(Texture tex, double _x, double _y, double _width, double _height, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureScaledColor
}

void UIElement::DrawTextureColor(Texture tex, double _x, double _y, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureColor
}

void UIElement::DrawTextureTiled(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureTiled
}

void UIElement::DrawTextureTiledX(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureTiledX
}

void UIElement::DrawTextureTiledY(Texture tex, double _x, double _y, double w, double h, double r, double g, double b, double a) {
 // TODO: Implement DrawTextureTiledY
}

void UIElement::DrawTextureIgnoreOffset(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 // TODO: Implement DrawTextureIgnoreOffset
}

void UIElement::DrawTexture_FlippedX(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 // TODO: Implement DrawTexture_FlippedX
}

void UIElement::DrawTexture_FlippedXIgnoreOffset(Texture tex, double _x, double _y, int _width, int _height, Color col) {
 // TODO: Implement DrawTexture_FlippedXIgnoreOffset
}

bool UIElement::getScrollChildren() {
 // TODO: Implement getScrollChildren
 return false;
}

void UIElement::setScrollChildren(bool bScroll) {
 // TODO: Implement setScrollChildren
}

bool UIElement::getScrollWithParent() {
 // TODO: Implement getScrollWithParent
 return false;
}

void UIElement::setScrollWithParent(bool bScroll) {
 // TODO: Implement setScrollWithParent
}

void UIElement::setRenderClippedChildren(bool b) {
 // TODO: Implement setRenderClippedChildren
}

double UIElement::getAbsoluteX() {
 // TODO: Implement getAbsoluteX
 return 0;
}

double UIElement::getAbsoluteY() {
 // TODO: Implement getAbsoluteY
 return 0;
}

std::string UIElement::getClickedValue() {
 // TODO: Implement getClickedValue
 return "";
}

void UIElement::setClickedValue(const std::string& _clickedValue) {
 // TODO: Implement setClickedValue
}

void UIElement::bringToTop() {
 // TODO: Implement bringToTop
}

void UIElement::onRightMouseUpOutside(double double1, double double0) {
 // TODO: Implement onRightMouseUpOutside
}

void UIElement::onRightMouseDownOutside(double double1, double double0) {
 // TODO: Implement onRightMouseDownOutside
}

void UIElement::onMouseUpOutside(double _x, double _y) {
 // TODO: Implement onMouseUpOutside
}

void UIElement::onMouseDownOutside(double double1, double double0) {
 // TODO: Implement onMouseDownOutside
}

bool UIElement::onMouseDown(double _x, double _y) {
 // TODO: Implement onMouseDown
 return false;
}

bool UIElement::onMouseDoubleClick(double double1, double double0) {
 // TODO: Implement onMouseDoubleClick
 return false;
}

bool UIElement::onMouseWheel(double del) {
 // TODO: Implement onMouseWheel
 return false;
}

bool UIElement::onMouseMove(double dx, double dy) {
 // TODO: Implement onMouseMove
 return false;
}

void UIElement::onMouseMoveOutside(double dx, double dy) {
 // TODO: Implement onMouseMoveOutside
}

bool UIElement::onMouseUp(double _x, double _y) {
 // TODO: Implement onMouseUp
 return false;
}

void UIElement::onresize() {
 // TODO: Implement onresize
}

void UIElement::onResize() {
 // TODO: Implement onResize
}

bool UIElement::onRightMouseDown(double _x, double _y) {
 // TODO: Implement onRightMouseDown
 return false;
}

bool UIElement::onRightMouseUp(double _x, double _y) {
 // TODO: Implement onRightMouseUp
 return false;
}

void UIElement::RemoveControl(UIElement el) {
 // TODO: Implement RemoveControl
}

void UIElement::render() {
 // TODO: Implement render
}

void UIElement::update() {
 // TODO: Implement update
}

void UIElement::BringToTop(UIElement el) {
 // TODO: Implement BringToTop
}

bool UIElement::isCapture() {
 // TODO: Implement isCapture
 return false;
}

void UIElement::setCapture(bool _capture) {
 // TODO: Implement setCapture
}

bool UIElement::isIgnoreLossControl() {
 // TODO: Implement isIgnoreLossControl
 return false;
}

void UIElement::setIgnoreLossControl(bool _IgnoreLossControl) {
 // TODO: Implement setIgnoreLossControl
}

void UIElement::setControls(Vector<UIElement> _Controls) {
 // TODO: Implement setControls
}

bool UIElement::isDefaultDraw() {
 // TODO: Implement isDefaultDraw
 return false;
}

void UIElement::setDefaultDraw(bool _defaultDraw) {
 // TODO: Implement setDefaultDraw
}

bool UIElement::isFollowGameWorld() {
 // TODO: Implement isFollowGameWorld
 return false;
}

void UIElement::setFollowGameWorld(bool _followGameWorld) {
 // TODO: Implement setFollowGameWorld
}

int UIElement::getRenderThisPlayerOnly() {
 // TODO: Implement getRenderThisPlayerOnly
 return 0;
}

void UIElement::setRenderThisPlayerOnly(int playerIndex) {
 // TODO: Implement setRenderThisPlayerOnly
}

double UIElement::getHeight() {
 // TODO: Implement getHeight
 return 0;
}

void UIElement::setHeight(double _height) {
 // TODO: Implement setHeight
}

UIElement UIElement::getParent() {
 // TODO: Implement getParent
 return nullptr;
}

void UIElement::setParent(UIElement _Parent) {
 // TODO: Implement setParent
}

bool UIElement::isVisible() {
 // TODO: Implement isVisible
 return false;
}

void UIElement::setVisible(bool _visible) {
 // TODO: Implement setVisible
}

double UIElement::getWidth() {
 // TODO: Implement getWidth
 return 0;
}

void UIElement::setWidth(double _width) {
 // TODO: Implement setWidth
}

double UIElement::getX() {
 // TODO: Implement getX
 return 0;
}

void UIElement::setX(double _x) {
 // TODO: Implement setX
}

double UIElement::getXScrolled(UIElement parent) {
 // TODO: Implement getXScrolled
 return 0;
}

double UIElement::getYScrolled(UIElement parent) {
 // TODO: Implement getYScrolled
 return 0;
}

bool UIElement::isEnabled() {
 // TODO: Implement isEnabled
 return false;
}

void UIElement::setEnabled(bool en) {
 // TODO: Implement setEnabled
}

double UIElement::getY() {
 // TODO: Implement getY
 return 0;
}

void UIElement::setY(double _y) {
 // TODO: Implement setY
}

void UIElement::suspendStencil() {
 // TODO: Implement suspendStencil
}

void UIElement::resumeStencil() {
 // TODO: Implement resumeStencil
}

void UIElement::setStencilRect(double _x, double _y, double _width, double _height) {
 // TODO: Implement setStencilRect
}

void UIElement::clearStencilRect() {
 // TODO: Implement clearStencilRect
}

void UIElement::repaintStencilRect(double _x, double _y, double _width, double _height) {
 // TODO: Implement repaintStencilRect
}

KahluaTable UIElement::getTable() {
 // TODO: Implement getTable
 return nullptr;
}

void UIElement::setTable(KahluaTable _table) {
 // TODO: Implement setTable
}

void UIElement::setHeightSilent(double _height) {
 // TODO: Implement setHeightSilent
}

void UIElement::setWidthSilent(double _width) {
 // TODO: Implement setWidthSilent
}

void UIElement::setHeightOnly(double _height) {
 // TODO: Implement setHeightOnly
}

void UIElement::setWidthOnly(double _width) {
 // TODO: Implement setWidthOnly
}

bool UIElement::isAnchorTop() {
 // TODO: Implement isAnchorTop
 return false;
}

void UIElement::setAnchorTop(bool _anchorTop) {
 // TODO: Implement setAnchorTop
}

void UIElement::ignoreWidthChange() {
 // TODO: Implement ignoreWidthChange
}

void UIElement::ignoreHeightChange() {
 // TODO: Implement ignoreHeightChange
}

bool UIElement::isAnchorLeft() {
 // TODO: Implement isAnchorLeft
 return false;
}

void UIElement::setAnchorLeft(bool _anchorLeft) {
 // TODO: Implement setAnchorLeft
}

bool UIElement::isAnchorRight() {
 // TODO: Implement isAnchorRight
 return false;
}

void UIElement::setAnchorRight(bool _anchorRight) {
 // TODO: Implement setAnchorRight
}

bool UIElement::isAnchorBottom() {
 // TODO: Implement isAnchorBottom
 return false;
}

void UIElement::setAnchorBottom(bool _anchorBottom) {
 // TODO: Implement setAnchorBottom
}

void UIElement::addBringToTop(UIElement uIElement0) {
 // TODO: Implement addBringToTop
}

int UIElement::getPlayerContext() {
 // TODO: Implement getPlayerContext
 return 0;
}

void UIElement::setPlayerContext(int nPlayer) {
 // TODO: Implement setPlayerContext
}

std::string UIElement::getUIName() {
 // TODO: Implement getUIName
 return "";
}

void UIElement::setUIName(const std::string& name) {
 // TODO: Implement setUIName
}

double UIElement::clampToParentX(double _x) {
 // TODO: Implement clampToParentX
 return 0;
}

double UIElement::clampToParentY(double _y) {
 // TODO: Implement clampToParentY
 return 0;
}

bool UIElement::isPointOver(double screenX, double screenY) {
 // TODO: Implement isPointOver
 return false;
}

bool UIElement::isMouseOver() {
 // TODO: Implement isMouseOver
 return false;
}

void* UIElement::tryGetTableValue(const std::string& string) {
 // TODO: Implement tryGetTableValue
 return nullptr;
}

void UIElement::setWantKeyEvents(bool want) {
 // TODO: Implement setWantKeyEvents
}

bool UIElement::isWantKeyEvents() {
 // TODO: Implement isWantKeyEvents
 return false;
}

bool UIElement::isKeyConsumed(int key) {
 // TODO: Implement isKeyConsumed
 return false;
}

void UIElement::onKeyPress(int key) {
 // TODO: Implement onKeyPress
}

void UIElement::onKeyRepeat(int key) {
 // TODO: Implement onKeyRepeat
}

void UIElement::onKeyRelease(int key) {
 // TODO: Implement onKeyRelease
}

bool UIElement::isForceCursorVisible() {
 // TODO: Implement isForceCursorVisible
 return false;
}

void UIElement::setForceCursorVisible(bool force) {
 // TODO: Implement setForceCursorVisible
}

} // namespace ui
} // namespace zombie
