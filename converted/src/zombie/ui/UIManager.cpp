#include "zombie/ui/UIManager.h"

namespace zombie {
namespace ui {

void UIManager::AddUI(UIElement el) {
  // TODO: Implement AddUI
}

void UIManager::RemoveElement(UIElement el) {
  // TODO: Implement RemoveElement
}

void UIManager::clearArrays() {
  // TODO: Implement clearArrays
}

void UIManager::closeContainers() {
  // TODO: Implement closeContainers
}

void UIManager::CloseContainers() {
  // TODO: Implement CloseContainers
}

void UIManager::DrawTexture(Texture tex, double x, double y) {
  // TODO: Implement DrawTexture
}

void UIManager::DrawTexture(Texture tex, double x, double y, double width,
                            double height, double alpha) {
  // TODO: Implement DrawTexture
}

void UIManager::FadeIn(double seconds) {
  // TODO: Implement FadeIn
}

void UIManager::FadeOut(double seconds) {
  // TODO: Implement FadeOut
}

void UIManager::CreateFBO(int width, int height) {
  // TODO: Implement CreateFBO
}

TextureFBO UIManager::createTexture(float x, float y, bool test) {
  // TODO: Implement createTexture
  return nullptr;
}

void UIManager::init() {
  // TODO: Implement init
}

void UIManager::render() {
  // TODO: Implement render
}

void UIManager::resize() {
  // TODO: Implement resize
}

Vector2 UIManager::getTileFromMouse(double mx, double my, double z) {
  // TODO: Implement getTileFromMouse
  return nullptr;
}

return UIManager::getPickedTile() {
  // TODO: Implement getPickedTile
  return nullptr;
}

void UIManager::update() {
  // TODO: Implement update
}

bool UIManager::checkPicked() {
  // TODO: Implement checkPicked
  return false;
}

void UIManager::handleZoomKeys() {
  // TODO: Implement handleZoomKeys
}

double UIManager::getLastMouseX() {
  // TODO: Implement getLastMouseX
  return 0;
}

void UIManager::setLastMouseX(double aLastMouseX) {
  // TODO: Implement setLastMouseX
}

double UIManager::getLastMouseY() {
  // TODO: Implement getLastMouseY
  return 0;
}

void UIManager::setLastMouseY(double aLastMouseY) {
  // TODO: Implement setLastMouseY
}

void UIManager::setPicked(IsoObjectPicker.ClickObject aPicked) {
  // TODO: Implement setPicked
}

Clock UIManager::getClock() {
  // TODO: Implement getClock
  return nullptr;
}

void UIManager::setClock(Clock aClock) {
  // TODO: Implement setClock
}

void UIManager::setUI(ArrayList<UIElement> aUI) {
  // TODO: Implement setUI
}

ObjectTooltip UIManager::getToolTip() {
  // TODO: Implement getToolTip
  return nullptr;
}

void UIManager::setToolTip(ObjectTooltip aToolTip) {
  // TODO: Implement setToolTip
}

Texture UIManager::getMouseArrow() {
  // TODO: Implement getMouseArrow
  return nullptr;
}

void UIManager::setMouseArrow(Texture aMouseArrow) {
  // TODO: Implement setMouseArrow
}

Texture UIManager::getMouseExamine() {
  // TODO: Implement getMouseExamine
  return nullptr;
}

void UIManager::setMouseExamine(Texture aMouseExamine) {
  // TODO: Implement setMouseExamine
}

Texture UIManager::getMouseAttack() {
  // TODO: Implement getMouseAttack
  return nullptr;
}

void UIManager::setMouseAttack(Texture aMouseAttack) {
  // TODO: Implement setMouseAttack
}

Texture UIManager::getMouseGrab() {
  // TODO: Implement getMouseGrab
  return nullptr;
}

void UIManager::setMouseGrab(Texture aMouseGrab) {
  // TODO: Implement setMouseGrab
}

SpeedControls UIManager::getSpeedControls() {
  // TODO: Implement getSpeedControls
  return nullptr;
}

void UIManager::setSpeedControls(SpeedControls aSpeedControls) {
  // TODO: Implement setSpeedControls
}

UIDebugConsole UIManager::getDebugConsole() {
  // TODO: Implement getDebugConsole
  return nullptr;
}

void UIManager::setDebugConsole(UIDebugConsole aDebugConsole) {
  // TODO: Implement setDebugConsole
}

UIServerToolbox UIManager::getServerToolbox() {
  // TODO: Implement getServerToolbox
  return nullptr;
}

void UIManager::setServerToolbox(UIServerToolbox aServerToolbox) {
  // TODO: Implement setServerToolbox
}

MoodlesUI UIManager::getMoodleUI(double index) {
  // TODO: Implement getMoodleUI
  return nullptr;
}

void UIManager::setMoodleUI(double index, MoodlesUI aMoodleUI) {
  // TODO: Implement setMoodleUI
}

bool UIManager::isbFadeBeforeUI() {
  // TODO: Implement isbFadeBeforeUI
  return false;
}

void UIManager::setbFadeBeforeUI(bool abFadeBeforeUI) {
  // TODO: Implement setbFadeBeforeUI
}

ActionProgressBar UIManager::getProgressBar(double index) {
  // TODO: Implement getProgressBar
  return nullptr;
}

void UIManager::setProgressBar(double index, ActionProgressBar aProgressBar) {
  // TODO: Implement setProgressBar
}

double UIManager::getFadeAlpha() {
  // TODO: Implement getFadeAlpha
  return 0;
}

void UIManager::setFadeAlpha(double aFadeAlpha) {
  // TODO: Implement setFadeAlpha
}

double UIManager::getFadeInTimeMax() {
  // TODO: Implement getFadeInTimeMax
  return 0;
}

void UIManager::setFadeInTimeMax(double aFadeInTimeMax) {
  // TODO: Implement setFadeInTimeMax
}

double UIManager::getFadeInTime() {
  // TODO: Implement getFadeInTime
  return 0;
}

void UIManager::setFadeInTime(double aFadeInTime) {
  // TODO: Implement setFadeInTime
}

bool UIManager::isFadingOut() {
  // TODO: Implement isFadingOut
  return false;
}

void UIManager::setFadingOut(bool aFadingOut) {
  // TODO: Implement setFadingOut
}

Texture UIManager::getLastMouseTexture() {
  // TODO: Implement getLastMouseTexture
  return nullptr;
}

void UIManager::setLastMouseTexture(Texture aLastMouseTexture) {
  // TODO: Implement setLastMouseTexture
}

IsoObject UIManager::getLastPicked() {
  // TODO: Implement getLastPicked
  return nullptr;
}

void UIManager::setLastPicked(IsoObject aLastPicked) {
  // TODO: Implement setLastPicked
}

void UIManager::setDoneTutorials(ArrayList<String> aDoneTutorials) {
  // TODO: Implement setDoneTutorials
}

float UIManager::getLastOffX() {
  // TODO: Implement getLastOffX
  return 0;
}

void UIManager::setLastOffX(float aLastOffX) {
  // TODO: Implement setLastOffX
}

float UIManager::getLastOffY() {
  // TODO: Implement getLastOffY
  return 0;
}

void UIManager::setLastOffY(float aLastOffY) {
  // TODO: Implement setLastOffY
}

ModalDialog UIManager::getModal() {
  // TODO: Implement getModal
  return nullptr;
}

void UIManager::setModal(ModalDialog aModal) {
  // TODO: Implement setModal
}

Texture UIManager::getBlack() {
  // TODO: Implement getBlack
  return nullptr;
}

void UIManager::setBlack(Texture aBlack) {
  // TODO: Implement setBlack
}

float UIManager::getLastAlpha() {
  // TODO: Implement getLastAlpha
  return 0;
}

void UIManager::setLastAlpha(float aLastAlpha) {
  // TODO: Implement setLastAlpha
}

Vector2 UIManager::getPickedTileLocal() {
  // TODO: Implement getPickedTileLocal
  return nullptr;
}

void UIManager::setPickedTileLocal(Vector2 aPickedTileLocal) {
  // TODO: Implement setPickedTileLocal
}

Vector2 UIManager::getPickedTile() {
  // TODO: Implement getPickedTile
  return nullptr;
}

void UIManager::setPickedTile(Vector2 aPickedTile) {
  // TODO: Implement setPickedTile
}

IsoObject UIManager::getRightDownObject() {
  // TODO: Implement getRightDownObject
  return nullptr;
}

void UIManager::setRightDownObject(IsoObject aRightDownObject) {
  // TODO: Implement setRightDownObject
}

void UIManager::pushToTop(UIElement uIElement) {
  // TODO: Implement pushToTop
}

bool UIManager::isShowPausedMessage() {
  // TODO: Implement isShowPausedMessage
  return false;
}

void UIManager::setShowPausedMessage(bool _showPausedMessage) {
  // TODO: Implement setShowPausedMessage
}

void UIManager::setShowLuaDebuggerOnError(bool show) {
  // TODO: Implement setShowLuaDebuggerOnError
}

bool UIManager::isShowLuaDebuggerOnError() {
  // TODO: Implement isShowLuaDebuggerOnError
  return false;
}

void UIManager::debugBreakpoint(const std::string &filename, long pc) {
  // TODO: Implement debugBreakpoint
}

void UIManager::executeGame(ArrayList<UIElement> arrayList, bool boolean0,
                            int int0) {
  // TODO: Implement executeGame
}

KahluaThread UIManager::getDefaultThread() {
  // TODO: Implement getDefaultThread
  return nullptr;
}

double UIManager::getDoubleClickInterval() {
  // TODO: Implement getDoubleClickInterval
  return 0;
}

double UIManager::getDoubleClickDist() {
  // TODO: Implement getDoubleClickDist
  return 0;
}

bool UIManager::isDoubleClick(double x1, double y1, double x2, double y2,
                              double clickTime) {
  // TODO: Implement isDoubleClick
  return false;
}

void UIManager::updateTooltip(double double1, double double0) {
  // TODO: Implement updateTooltip
}

void UIManager::setPlayerInventory(int playerIndex, UIElement inventory,
                                   UIElement loot) {
  // TODO: Implement setPlayerInventory
}

void UIManager::setPlayerInventoryTooltip(int playerIndex, UIElement inventory,
                                          UIElement loot) {
  // TODO: Implement setPlayerInventoryTooltip
}

bool UIManager::isMouseOverInventory() {
  // TODO: Implement isMouseOverInventory
  return false;
}

void UIManager::updateBeforeFadeOut() {
  // TODO: Implement updateBeforeFadeOut
}

void UIManager::setVisibleAllUI(bool visible) {
  // TODO: Implement setVisibleAllUI
}

void UIManager::setFadeBeforeUI(int playerIndex, bool _bFadeBeforeUI) {
  // TODO: Implement setFadeBeforeUI
}

float UIManager::getFadeAlpha(double playerIndex) {
  // TODO: Implement getFadeAlpha
  return 0;
}

void UIManager::setFadeTime(double playerIndex, double FadeTime) {
  // TODO: Implement setFadeTime
}

void UIManager::FadeIn(double playerIndex, double seconds) {
  // TODO: Implement FadeIn
}

void UIManager::FadeOut(double playerIndex, double seconds) {
  // TODO: Implement FadeOut
}

bool UIManager::isFBOActive() {
  // TODO: Implement isFBOActive
  return false;
}

double UIManager::getMillisSinceLastUpdate() {
  // TODO: Implement getMillisSinceLastUpdate
  return 0;
}

double UIManager::getSecondsSinceLastUpdate() {
  // TODO: Implement getSecondsSinceLastUpdate
  return 0;
}

double UIManager::getMillisSinceLastRender() {
  // TODO: Implement getMillisSinceLastRender
  return 0;
}

double UIManager::getSecondsSinceLastRender() {
  // TODO: Implement getSecondsSinceLastRender
  return 0;
}

bool UIManager::onKeyPress(int key) {
  // TODO: Implement onKeyPress
  return false;
}

bool UIManager::onKeyRepeat(int key) {
  // TODO: Implement onKeyRepeat
  return false;
}

bool UIManager::onKeyRelease(int key) {
  // TODO: Implement onKeyRelease
  return false;
}

bool UIManager::isForceCursorVisible() {
  // TODO: Implement isForceCursorVisible
  return false;
}

public
UIManager::FadeInfo(int arg0) {
  // TODO: Implement FadeInfo
  return nullptr;
}

bool UIManager::isFadeBeforeUI() {
  // TODO: Implement isFadeBeforeUI
  return false;
}

void UIManager::setFadeBeforeUI(bool arg0) {
  // TODO: Implement setFadeBeforeUI
}

float UIManager::getFadeAlpha() {
  // TODO: Implement getFadeAlpha
  return 0;
}

void UIManager::setFadeAlpha(float arg0) {
  // TODO: Implement setFadeAlpha
}

int UIManager::getFadeTime() {
  // TODO: Implement getFadeTime
  return 0;
}

void UIManager::setFadeTime(int arg0) {
  // TODO: Implement setFadeTime
}

int UIManager::getFadeTimeMax() {
  // TODO: Implement getFadeTimeMax
  return 0;
}

void UIManager::setFadeTimeMax(int arg0) {
  // TODO: Implement setFadeTimeMax
}

bool UIManager::isFadingOut() {
  // TODO: Implement isFadingOut
  return false;
}

void UIManager::setFadingOut(bool arg0) {
  // TODO: Implement setFadingOut
}

void UIManager::FadeIn(int arg0) {
  // TODO: Implement FadeIn
}

void UIManager::FadeOut(int arg0) {
  // TODO: Implement FadeOut
}

void UIManager::update() {
  // TODO: Implement update
}

void UIManager::render() {
  // TODO: Implement render
}

void UIManager::begin() {
  // TODO: Implement begin
}

void UIManager::startFrame() {
  // TODO: Implement startFrame
}

void UIManager::endFrame() {
  // TODO: Implement endFrame
}

} // namespace ui
} // namespace zombie
