#include <string>
#include <vector>
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace ui {

void UIManager::AddUI(UIElement var0) {
    // Java: toRemove.remove(var0); toRemove.add(var0); toAdd.remove(var0); toAdd.add(var0);
    toRemove.erase(std::remove(toRemove.begin(), toRemove.end(), var0), toRemove.end());
    toRemove.push_back(var0);
    toAdd.erase(std::remove(toAdd.begin(), toAdd.end(), var0), toAdd.end());
    toAdd.push_back(var0);
}

void UIManager::RemoveElement(UIElement var0) {
    // Java: toAdd.remove(var0); toRemove.remove(var0); toRemove.add(var0);
    toAdd.erase(std::remove(toAdd.begin(), toAdd.end(), var0), toAdd.end());
    toRemove.erase(std::remove(toRemove.begin(), toRemove.end(), var0), toRemove.end());
    toRemove.push_back(var0);
}

void UIManager::clearArrays() {
    toAdd.clear();
    toRemove.clear();
    UI.clear();
}

void UIManager::closeContainers() {
    // Java: for (UIElement ui : UI) if (ui instanceof UIContainer) ((UIContainer)ui).close();
    for (auto& elem : UI) {
        if (elem && elem->isContainer()) {
            elem->close();
        }
    }
}

void UIManager::CloseContainers() {
    closeContainers();
}

void UIManager::DrawTexture(Texture var0, double var1, double var3) {
    // Java: double var5 = var1 + var0.offsetX; double var7 = var3 + var0.offsetY;
    // SpriteRenderer.instance.renderi(var0, (int)var5, (int)var7, var0.getWidth(), var0.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, null);
    if (var0) {
        double var5 = var1 + var0->offsetX;
        double var7 = var3 + var0->offsetY;
        SpriteRenderer::instance->renderi(
            var0,
            static_cast<int>(var5),
            static_cast<int>(var7),
            var0->getWidth(),
            var0->getHeight(),
            1.0f, 1.0f, 1.0f, 1.0f,
            nullptr
        );
    }
}

void UIManager::DrawTexture(Texture var0, double var1, double var3, double var5, double var7, double var9) {
    // Java: double var11 = var1 + var0.offsetX; double var13 = var3 + var0.offsetY;
    // SpriteRenderer.instance.renderi(var0, (int)var11, (int)var13, (int)var5, (int)var7, 1.0F, 1.0F, 1.0F, (float)var9, null);
    if (var0) {
        double var11 = var1 + var0->offsetX;
        double var13 = var3 + var0->offsetY;
        SpriteRenderer::instance->renderi(
            var0,
            static_cast<int>(var11),
            static_cast<int>(var13),
            static_cast<int>(var5),
            static_cast<int>(var7),
            1.0f, 1.0f, 1.0f, static_cast<float>(var9),
            nullptr
        );
    }
}

void UIManager::FadeIn(double var0) {
    // Java: setFadeInTimeMax((int)(var0 * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F)));
    // setFadeInTime(getFadeInTimeMax()); setFadingOut(false);
    int fps = PerformanceSettings::getLockFPS();
    FadeInTimeMax = static_cast<int>(var0 * 30.0 * (fps / 30.0f));
    FadeInTime = FadeInTimeMax;
    FadingOut = false;
}

void UIManager::FadeOut(double var0) {
    // Java: setFadeInTimeMax((int)(var0 * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F)));
    // setFadeInTime(getFadeInTimeMax()); setFadingOut(true);
    int fps = PerformanceSettings::getLockFPS();
    FadeInTimeMax = static_cast<int>(var0 * 30.0 * (fps / 30.0f));
    FadeInTime = FadeInTimeMax;
    FadingOut = true;
}

void UIManager::CreateFBO(int var0, int var1) {
    // Java: if (Core.SafeMode) { useUIFBO = false; } else { ... }
    if (Core::SafeMode) {
        useUIFBO = false;
    } else {
        useUIFBO = true;
        uiFBO = createTexture(static_cast<float>(var0), static_cast<float>(var1), false);
    }
}

TextureFBO UIManager::createTexture(float var0, float var1, bool var2) {
    // Java: if (var2) { Texture var5 = new Texture((int)var0, (int)var1, 16); TextureFBO var4 = new TextureFBO(var5); var4.destroy(); return null; }
    // else { Texture var3 = new Texture((int)var0, (int)var1, 16); return new TextureFBO(var3); }
    if (var2) {
        auto tex = std::make_shared<Texture>(static_cast<int>(var0), static_cast<int>(var1), 16);
        auto fbo = std::make_shared<TextureFBO>(tex);
        fbo->destroy();
        return nullptr;
    } else {
        auto tex = std::make_shared<Texture>(static_cast<int>(var0), static_cast<int>(var1), 16);
        return std::make_shared<TextureFBO>(tex);
    }
}

void UIManager::init() {
    showPausedMessage = true;
    UI.clear();
    debugUI.clear();
    clock = nullptr;
    for (auto& m : MoodleUI) m = nullptr;
    speedControls = std::make_shared<SpeedControls>();
    // SpeedControls::instance = speedControls; // TODO: Implement static instance if needed
    bFadeBeforeUI = false;
    VisibleAllUI = true;
    for (auto& f : playerFadeInfo) {
        if (f) {
            f->setFadeBeforeUI(false);
            f->setFadeTime(0);
            f->setFadingOut(false);
        }
    }
}

void UIManager::render() {
    // Ported from Java: UIManager.render()
    if (!useUIFBO /*|| Core::getInstance()->UIRenderThisFrame*/) {
        if (!bSuspend) {
            using namespace std::chrono;
            long now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
            uiRenderIntervalMS = std::min(now - uiRenderTimeMS, 1000L);
            uiRenderTimeMS = now;
            UIElement::StencilLevel = 0;
            if (useUIFBO) {
                zombie::core::SpriteRenderer::instance->setDefaultStyle(zombie::core::Styles::UIFBOStyle::instance);
            }

            UITransition::UpdateAll();
            if (!black) {
                setBlack(zombie::core::textures::Texture::getSharedTexture("black.png"));
            }

            if (LuaManager::thread == defaultthread) {
                LuaEventManager::triggerEvent("OnPreUIDraw");
            }

            int mouseX = Mouse::getXA();
            int mouseY = Mouse::getYA();

            if (bFadeBeforeUI) {
                FadeAlpha = static_cast<float>(FadeInTime) / (FadeInTimeMax ? FadeInTimeMax : 1);
                if (FadeAlpha > 1.0f) FadeAlpha = 1.0f;
                if (FadeAlpha < 0.0f) FadeAlpha = 0.0f;
                if (FadingOut) FadeAlpha = 1.0f - FadeAlpha;
                if (IsoCamera::CamCharacter && FadeAlpha > 0.0f)
                     DrawTexture(black, 0.0, 0.0, Core::getInstance()->getScreenWidth(), Core::getInstance()->getScreenHeight(), FadeAlpha);
            }

            lastAlpha = FadeAlpha;

             for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
                 if (IsoPlayer::players[i] && playerFadeInfo[i] && playerFadeInfo[i]->isFadeBeforeUI())
                     playerFadeInfo[i]->render();
            }

            for (auto& elem : UI) {
                if ((elem->isIgnoreLossControl() /*|| !TutorialManager::instance->StealControl*/) && !elem->isFollowGameWorld()) {
                    try {
                        if (elem->isDefaultDraw())
                            elem->render();
                    } catch (...) {
                        // TODO: Log error
                    }
                }
            }

            if (toolTip) {
                toolTip->render();
            }

            if (isShowPausedMessage() && GameTime::isGamePaused() && (!Modal || !Modal->isVisible()) && VisibleAllUI) {
                std::string pausedText = Translator::getText("IGUI_GamePaused");
                int textWidth = TextManager::instance->MeasureStringX(UIFont::Small, pausedText) + 32;
                int lineHeight = TextManager::instance->font->getLineHeight();
                int boxHeight = static_cast<int>(std::ceil(lineHeight * 1.5));
                int screenWidth = Core::getInstance()->getScreenWidth();
                int screenHeight = Core::getInstance()->getScreenHeight();
                // Draw semi-transparent box
                SpriteRenderer::instance->renderi(
                    nullptr,
                    screenWidth / 2 - textWidth / 2,
                    screenHeight / 2 - boxHeight / 2,
                    textWidth,
                    boxHeight,
                    0.0f, 0.0f, 0.0f, 0.75f,
                    nullptr
                );
                // Draw centered paused text
                TextManager::instance->DrawStringCentre(
                    screenWidth / 2,
                    screenHeight / 2 - lineHeight / 2,
                    pausedText,
                    1.0, 1.0, 1.0, 1.0
                );
            }

            if (!bFadeBeforeUI) {
                FadeAlpha = static_cast<float>(FadeInTime) / (FadeInTimeMax ? FadeInTimeMax : 1);
                if (FadeAlpha > 1.0f) FadeAlpha = 1.0f;
                if (FadeAlpha < 0.0f) FadeAlpha = 0.0f;
                if (FadingOut) FadeAlpha = 1.0f - FadeAlpha;
                if (IsoCamera::CamCharacter && FadeAlpha > 0.0f)
                    DrawTexture(black, 0.0, 0.0, Core::getInstance()->getScreenWidth(), Core::getInstance()->getScreenHeight(), FadeAlpha);
            }

            for (int i = 0; i < IsoPlayer::numPlayers; ++i) {
                if (IsoPlayer::players[i] && playerFadeInfo[i] && !playerFadeInfo[i]->isFadeBeforeUI())
                    playerFadeInfo[i]->render();
            }

            if (LuaManager::thread == defaultthread) {
                LuaEventManager::triggerEvent("OnPostUIDraw");
            }

            if (useUIFBO) {
                SpriteRenderer::instance->setDefaultStyle(TransparentStyle::instance);
            }
        }
    }
}


void UIManager::resize() {
    // Java: for (UIElement ui : UI) ui.onResize();
    for (auto& elem : UI) {
        if (elem) elem->onResize();
    }
    for (auto& elem : debugUI) {
        if (elem) elem->onResize();
    }
    if (toolTip) toolTip->onResize();
    if (Modal) Modal->onResize();
}


Vector2 UIManager::getTileFromMouse(double x, double y, double z) {
    // Java: IsoUtils.XToIso(x, y, z), IsoUtils.YToIso(x, y, z)
    // Assuming IsoUtils::XToIso and YToIso exist and return double
    double isoX = IsoUtils::XToIso(x, y, z);
    double isoY = IsoUtils::YToIso(x, y, z);
    return std::make_shared<Vector2Class>(isoX, isoY);
}


Vector2 UIManager::getPickedTile() {
    // Java: return PickedTile;
    return PickedTile;
}


void UIManager::update() {
    // Java: for (UIElement ui : UI) ui.update();
    for (auto& elem : UI) {
        if (elem) elem->update();
    }
    for (auto& elem : debugUI) {
        if (elem) elem->update();
    }
    if (toolTip) toolTip->update();
    if (Modal) Modal->update();
}


bool UIManager::checkPicked() {
    // Java: return Picked != null;
    return Picked != nullptr;
}


void UIManager::handleZoomKeys() {
    // Java: if (Keyboard.isKeyDown(KeyEvent.VK_EQUALS)) IsoCamera.zoomIn();
    //       if (Keyboard.isKeyDown(KeyEvent.VK_MINUS)) IsoCamera.zoomOut();
    if (Keyboard::isKeyDown(KeyEvent::VK_EQUALS) || Keyboard::isKeyDown(KeyEvent::VK_ADD)) {
        IsoCamera::zoomIn();
    }
    if (Keyboard::isKeyDown(KeyEvent::VK_MINUS) || Keyboard::isKeyDown(KeyEvent::VK_SUBTRACT)) {
        IsoCamera::zoomOut();
    }
}

double UIManager::getLastMouseX() {
    return lastMouseX;
}

void UIManager::setLastMouseX(double var0) {
    lastMouseX = static_cast<int>(var0);
}

double UIManager::getLastMouseY() {
    return lastMouseY;
}

void UIManager::setLastMouseY(double var0) {
    lastMouseY = static_cast<int>(var0);
}

ClickObject UIManager::getPicked() {
    return Picked;
}

void UIManager::setPicked(ClickObject var0) {
    Picked = var0;
}

Clock UIManager::getClock() {
    return clock;
}

void UIManager::setClock(Clock var0) {
    clock = var0;
}

void UIManager::setUI(std::vector<UIElement> var0) {
    UI = var0;
}

ObjectTooltip UIManager::getToolTip() {
    return toolTip;
}

void UIManager::setToolTip(ObjectTooltip var0) {
    toolTip = var0;
}

Texture UIManager::getMouseArrow() {
    return mouseArrow;
}

void UIManager::setMouseArrow(Texture var0) {
    mouseArrow = var0;
}

Texture UIManager::getMouseExamine() {
    return mouseExamine;
}

void UIManager::setMouseExamine(Texture var0) {
    mouseExamine = var0;
}

Texture UIManager::getMouseAttack() {
    return mouseAttack;
}

void UIManager::setMouseAttack(Texture var0) {
    mouseAttack = var0;
}

Texture UIManager::getMouseGrab() {
    return mouseGrab;
}

void UIManager::setMouseGrab(Texture var0) {
    mouseGrab = var0;
}

SpeedControls UIManager::getSpeedControls() {
    return speedControls;
}

void UIManager::setSpeedControls(SpeedControls var0) {
    speedControls = var0;
}

UIDebugConsole UIManager::getDebugConsole() {
    return DebugConsole;
}

void UIManager::setDebugConsole(UIDebugConsole var0) {
    DebugConsole = var0;
}

UIServerToolbox UIManager::getServerToolbox() {
    return ServerToolbox;
}

void UIManager::setServerToolbox(UIServerToolbox var0) {
    ServerToolbox = var0;
}

MoodlesUI UIManager::getMoodleUI(double var0) {
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(MoodleUI.size()))
        return MoodleUI[idx];
    return nullptr;
}

void UIManager::setMoodleUI(double var0, MoodlesUI var2) {
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(MoodleUI.size()))
        MoodleUI[idx] = var2;
}

bool UIManager::isbFadeBeforeUI() {
    return bFadeBeforeUI;
}

void UIManager::setbFadeBeforeUI(bool var0) {
    bFadeBeforeUI = var0;
}

ActionProgressBar UIManager::getProgressBar(double var0) {
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(ProgressBar.size()))
        return ProgressBar[idx];
    return nullptr;
}

void UIManager::setProgressBar(double var0, ActionProgressBar var2) {
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(ProgressBar.size()))
        ProgressBar[idx] = var2;
}

double UIManager::getFadeAlpha() {
    return FadeAlpha;
}

void UIManager::setFadeAlpha(double var0) {
    FadeAlpha = static_cast<float>(var0);
}

double UIManager::getFadeInTimeMax() {
    return FadeInTimeMax;
}

void UIManager::setFadeInTimeMax(double var0) {
    FadeInTimeMax = static_cast<int>(var0);
}

double UIManager::getFadeInTime() {
    return FadeInTime;
}

void UIManager::setFadeInTime(double var0) {
    FadeInTime = static_cast<int>(var0);
}

bool UIManager::isFadingOut() {
    return FadingOut;
}

void UIManager::setFadingOut(bool var0) {
    FadingOut = var0;
}

Texture UIManager::getLastMouseTexture() {
    return lastMouseTexture;
}

void UIManager::setLastMouseTexture(Texture var0) {
    lastMouseTexture = var0;
}

IsoObject UIManager::getLastPicked() {
    return LastPicked;
}

void UIManager::setLastPicked(IsoObject var0) {
    LastPicked = var0;
}

void UIManager::setDoneTutorials(std::vector<std::string> var0) {
    DoneTutorials = var0;
}

float UIManager::getLastOffX() {
    return lastOffX;
}

void UIManager::setLastOffX(float var0) {
    lastOffX = var0;
}

float UIManager::getLastOffY() {
    return lastOffY;
}

void UIManager::setLastOffY(float var0) {
    lastOffY = var0;
}

ModalDialog UIManager::getModal() {
    return Modal;
}

void UIManager::setModal(ModalDialog var0) {
    Modal = var0;
}

Texture UIManager::getBlack() {
    return black;
}

void UIManager::setBlack(Texture var0) {
    black = var0;
}

float UIManager::getLastAlpha() {
    return lastAlpha;
}

void UIManager::setLastAlpha(float var0) {
    lastAlpha = var0;
}

Vector2 UIManager::getPickedTileLocal() {
    return PickedTileLocal;
}

void UIManager::setPickedTileLocal(Vector2 var0) {
    PickedTileLocal = var0;
}

Vector2 UIManager::getPickedTile() {
    return PickedTile;
}

void UIManager::setPickedTile(Vector2 var0) {
    PickedTile = var0;
}

IsoObject UIManager::getRightDownObject() {
    return RightDownObject;
}

void UIManager::setRightDownObject(IsoObject var0) {
    RightDownObject = var0;
}

void UIManager::pushToTop(UIElement var0) {
    if (var0) {
        toTop.push_back(var0);
    }
}

bool UIManager::isShowPausedMessage() {
    return showPausedMessage;
}

void UIManager::setShowPausedMessage(bool var0) {
    showPausedMessage = var0;
}

void UIManager::setShowLuaDebuggerOnError(bool var0) {
    bShowLuaDebuggerOnError = var0;
}

bool UIManager::isShowLuaDebuggerOnError() {
    return bShowLuaDebuggerOnError;
}

void UIManager::debugBreakpoint(const std::string& var0, long var1) {
    // Java: DebugLog.log("Breakpoint: " + var0 + ", value: " + var1);
    DebugLog::log("Breakpoint: " + var0 + ", value: " + std::to_string(var1));
}

void UIManager::executeGame(std::vector<UIElement> var0, bool var1, int var2) {
    // Java: for (UIElement ui : var0) ui.executeGame(var1, var2);
    for (auto& elem : var0) {
        if (elem) elem->executeGame(var1, var2);
    }
}

KahluaThread UIManager::getDefaultThread() {
    // Java: return defaultthread;
    return defaultthread;
}

double UIManager::getDoubleClickInterval() {
    // Java: return doubleClickInterval;
    return doubleClickInterval;
}

double UIManager::getDoubleClickDist() {
    // Java: return doubleClickDist;
    return doubleClickDist;
}

bool UIManager::isDoubleClick(double var0, double var2, double var4, double var6, double var8) {
    // Java: return Math.abs(var0 - var4) < getDoubleClickDist() && Math.abs(var2 - var6) < getDoubleClickDist() && var8 < getDoubleClickInterval();
    return (std::abs(var0 - var4) < getDoubleClickDist()) &&
           (std::abs(var2 - var6) < getDoubleClickDist()) &&
           (var8 < getDoubleClickInterval());
}

void UIManager::updateTooltip(double var0, double var2) {
    // Java: if (toolTip) toolTip.setPosition(var0, var2);
    if (toolTip) toolTip->setPosition(var0, var2);
}

void UIManager::setPlayerInventory(int var0, UIElement var1, UIElement var2) {
    // Java: playerInventoryUI = var1; playerLootUI = var2;
    playerInventoryUI = var1;
    playerLootUI = var2;
}

void UIManager::setPlayerInventoryTooltip(int var0, UIElement var1, UIElement var2) {
    // Java: playerInventoryTooltip = var1; playerLootTooltip = var2;
    playerInventoryTooltip = var1;
    playerLootTooltip = var2;
}

bool UIManager::isMouseOverInventory() {
    // Java: return mouseOverInventory;
    return mouseOverInventory;
}

void UIManager::updateBeforeFadeOut() {
    // Java: for (UIElement ui : UI) ui.updateBeforeFadeOut();
    for (auto& elem : UI) {
        if (elem) elem->updateBeforeFadeOut();
    }
}

void UIManager::setVisibleAllUI(bool var0) {
    // Java: VisibleAllUI = var0;
    VisibleAllUI = var0;
}

void UIManager::setFadeBeforeUI(int var0, bool var1) {
    // Java: if (playerFadeInfo[var0]) playerFadeInfo[var0]->setFadeBeforeUI(var1);
    if (var0 >= 0 && var0 < static_cast<int>(playerFadeInfo.size()) && playerFadeInfo[var0]) {
        playerFadeInfo[var0]->setFadeBeforeUI(var1);
    }
}

float UIManager::getFadeAlpha(double var0) {
    // Java: if (playerFadeInfo[var0]) return playerFadeInfo[var0]->getFadeAlpha(); else return FadeAlpha;
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(playerFadeInfo.size()) && playerFadeInfo[idx]) {
        return playerFadeInfo[idx]->getFadeAlpha();
    }
    return FadeAlpha;
}

void UIManager::setFadeTime(double var0, double var2) {
    // Java: if (playerFadeInfo[var0]) playerFadeInfo[var0]->setFadeTime(var2);
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(playerFadeInfo.size()) && playerFadeInfo[idx]) {
        playerFadeInfo[idx]->setFadeTime(var2);
    }
}

void UIManager::FadeIn(double var0, double var2) {
    // Java: if (playerFadeInfo[var0]) playerFadeInfo[var0]->FadeIn(var2);
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(playerFadeInfo.size()) && playerFadeInfo[idx]) {
        playerFadeInfo[idx]->FadeIn(var2);
    }
}

void UIManager::FadeOut(double var0, double var2) {
    // Java: if (playerFadeInfo[var0]) playerFadeInfo[var0]->FadeOut(var2);
    int idx = static_cast<int>(var0);
    if (idx >= 0 && idx < static_cast<int>(playerFadeInfo.size()) && playerFadeInfo[idx]) {
        playerFadeInfo[idx]->FadeOut(var2);
    }
}

bool UIManager::isFBOActive() {
    // Java: return useUIFBO;
    return useUIFBO;
}

double UIManager::getMillisSinceLastUpdate() {
    return uiUpdateTimeMS;
}

double UIManager::getSecondsSinceLastUpdate() {
    return uiUpdateTimeMS / 1000.0;
}

double UIManager::getMillisSinceLastRender() {
    return uiRenderTimeMS;
}

double UIManager::getSecondsSinceLastRender() {
    return uiRenderTimeMS / 1000.0;
}

bool UIManager::onKeyPress(int var0) {
    // Java: for (UIElement ui : UI) if (ui.onKeyPress(var0)) return true;
    for (auto& elem : UI) {
        if (elem && elem->onKeyPress(var0)) return true;
    }
    return false;
}

bool UIManager::onKeyRepeat(int var0) {
    // Java: for (UIElement ui : UI) if (ui.onKeyRepeat(var0)) return true;
    for (auto& elem : UI) {
        if (elem && elem->onKeyRepeat(var0)) return true;
    }
    return false;
}

bool UIManager::onKeyRelease(int var0) {
    // Java: for (UIElement ui : UI) if (ui.onKeyRelease(var0)) return true;
    for (auto& elem : UI) {
        if (elem && elem->onKeyRelease(var0)) return true;
    }
    return false;
}

bool UIManager::isForceCursorVisible() {
    // Java: return forceCursorVisible;
    return forceCursorVisible;
}

} // namespace ui
} // namespace zombie
