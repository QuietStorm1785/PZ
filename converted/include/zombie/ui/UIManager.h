#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaThread.h"
#include "zombie/GameTime.h"
#include "zombie/GameWindow.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/Styles/TransparentStyle.h"
#include "zombie/core/Styles/UIFBOStyle.h"
#include "zombie/core/Translator.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/textures/Texture.h"
#include "zombie/core/textures/TextureFBO.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/gameStates/GameLoadingState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace ui {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class UIManager {
public:
 static int lastMouseX = 0;
 static int lastMouseY = 0;
 public static IsoObjectPicker.ClickObject Picked = nullptr;
 static Clock clock;
 public static ArrayList<UIElement> UI = std::make_unique<ArrayList<>>();
 static ObjectTooltip toolTip = nullptr;
 static Texture mouseArrow;
 static Texture mouseExamine;
 static Texture mouseAttack;
 static Texture mouseGrab;
 static SpeedControls speedControls;
 static UIDebugConsole DebugConsole;
 static UIServerToolbox ServerToolbox;
 public static MoodlesUI[] MoodleUI = new MoodlesUI[4];
 static bool bFadeBeforeUI = false;
 public static ActionProgressBar[] ProgressBar = new ActionProgressBar[4];
 static float FadeAlpha = 1.0F;
 static int FadeInTimeMax = 180;
 static int FadeInTime = 180;
 static bool FadingOut = false;
 static Texture lastMouseTexture;
 static IsoObject LastPicked = nullptr;
 public static ArrayList<String> DoneTutorials = std::make_unique<ArrayList<>>();
 static float lastOffX = 0.0F;
 static float lastOffY = 0.0F;
 static ModalDialog Modal = nullptr;
 static bool KeyDownZoomIn = false;
 static bool KeyDownZoomOut = false;
 static bool doTick;
 static bool VisibleAllUI = true;
 static TextureFBO UIFBO;
 static bool useUIFBO = false;
 static Texture black = nullptr;
 static bool bSuspend = false;
 static float lastAlpha = 10000.0F;
 static const Vector2 PickedTileLocal = new Vector2();
 static const Vector2 PickedTile = new Vector2();
 static IsoObject RightDownObject = nullptr;
 static long uiUpdateTimeMS = 0L;
 static long uiUpdateIntervalMS = 0L;
 static long uiRenderTimeMS = 0L;
 static long uiRenderIntervalMS = 0L;
 private static ArrayList<UIElement> tutorialStack = std::make_unique<ArrayList<>>();
 public static ArrayList<UIElement> toTop = std::make_unique<ArrayList<>>();
 static KahluaThread defaultthread = nullptr;
 static KahluaThread previousThread = nullptr;
 static ArrayList<UIElement> toRemove = std::make_unique<ArrayList<>>();
 static ArrayList<UIElement> toAdd = std::make_unique<ArrayList<>>();
 static int wheel = 0;
 static int lastwheel = 0;
 static ArrayList<UIElement> debugUI = std::make_unique<ArrayList<>>();
 static bool bShowLuaDebuggerOnError = true;
 static std::string luaDebuggerAction = nullptr;
 static UIManager.Sync sync = new UIManager.Sync();
 static bool showPausedMessage = true;
 static UIElement playerInventoryUI;
 static UIElement playerLootUI;
 static UIElement playerInventoryTooltip;
 static UIElement playerLootTooltip;
 private static UIManager.FadeInfo[] playerFadeInfo = new UIManager.FadeInfo[4];

 static void AddUI(UIElement el) {
 toRemove.remove(el);
 toRemove.add(el);
 toAdd.remove(el);
 toAdd.add(el);
 }

 static void RemoveElement(UIElement el) {
 toAdd.remove(el);
 toRemove.remove(el);
 toRemove.add(el);
 }

 static void clearArrays() {
 toAdd.clear();
 toRemove.clear();
 UI.clear();
 }

 static void closeContainers() {
 }

 static void CloseContainers() {
 }

 static void DrawTexture(Texture tex, double x, double y) {
 double double0 = x + tex.offsetX;
 double double1 = y + tex.offsetY;
 SpriteRenderer.instance.renderi(tex, (int)double0, (int)double1, tex.getWidth(), tex.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
 }

 static void DrawTexture(Texture tex, double x, double y, double width, double height, double alpha) {
 double double0 = x + tex.offsetX;
 double double1 = y + tex.offsetY;
 SpriteRenderer.instance.renderi(tex, (int)double0, (int)double1, (int)width, (int)height, 1.0F, 1.0F, 1.0F, (float)alpha, nullptr);
 }

 static void FadeIn(double seconds) {
 setFadeInTimeMax((int)(seconds * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F);
 setFadeInTime(getFadeInTimeMax());
 setFadingOut(false);
 }

 static void FadeOut(double seconds) {
 setFadeInTimeMax((int)(seconds * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F);
 setFadeInTime(getFadeInTimeMax());
 setFadingOut(true);
 }

 static void CreateFBO(int width, int height) {
 if (Core.SafeMode) {
 useUIFBO = false;
 } else {
 if (useUIFBO && (UIFBO == nullptr || UIFBO.getTexture().getWidth() != width || UIFBO.getTexture().getHeight() != height) {
 if (UIFBO != nullptr) {
 RenderThread.invokeOnRenderContext(() -> UIFBO.destroy());
 }

 try {
 UIFBO = createTexture(width, height, false);
 } catch (Exception exception) {
 useUIFBO = false;
 exception.printStackTrace();
 }
 }
 }
 }

 static TextureFBO createTexture(float x, float y, bool test) {
 if (test) {
 Texture texture0 = new Texture((int)x, (int)y, 16);
 TextureFBO textureFBO = new TextureFBO(texture0);
 textureFBO.destroy();
 return nullptr;
 } else {
 Texture texture1 = new Texture((int)x, (int)y, 16);
 return new TextureFBO(texture1);
 }
 }

 static void init() {
 showPausedMessage = true;
 getUI().clear();
 debugUI.clear();
 clock = nullptr;

 for (int int0 = 0; int0 < 4; int0++) {
 MoodleUI[int0] = nullptr;
 }

 setSpeedControls(std::make_unique<SpeedControls>());
 SpeedControls.instance = getSpeedControls();
 setbFadeBeforeUI(false);
 VisibleAllUI = true;

 for (int int1 = 0; int1 < 4; int1++) {
 playerFadeInfo[int1].setFadeBeforeUI(false);
 playerFadeInfo[int1].setFadeTime(0);
 playerFadeInfo[int1].setFadingOut(false);
 }

 setPicked(nullptr);
 setLastPicked(nullptr);
 RightDownObject = nullptr;
 if (IsoPlayer.getInstance() != nullptr) {
 if (!Core.GameMode == "LastStand") && !GameClient.bClient) {
 getUI().add(getSpeedControls());
 }

 if (!GameServer.bServer) {
 setToolTip(std::make_unique<ObjectTooltip>());
 if (Core.getInstance().getOptionClockSize() == 2) {
 setClock(new Clock(Core.getInstance().getOffscreenWidth(0) - 166, 10);
 } else {
 setClock(new Clock(Core.getInstance().getOffscreenWidth(0) - 91, 10);
 }

 if (!Core.GameMode == "LastStand")) {
 getUI().add(getClock());
 }

 getUI().add(getToolTip());
 setDebugConsole(new UIDebugConsole(20, Core.getInstance().getScreenHeight() - 265);
 setServerToolbox(new UIServerToolbox(100, 200);
 if (Core.bDebug && DebugOptions.instance.UIDebugConsoleStartVisible.getValue()) {
 DebugConsole.setVisible(true);
 } else {
 DebugConsole.setVisible(false);
 }

 if (CoopMaster.instance.isRunning()) {
 ServerToolbox.setVisible(true);
 } else {
 ServerToolbox.setVisible(false);
 }

 for (int int2 = 0; int2 < 4; int2++) {
 MoodlesUI moodlesUI = new MoodlesUI();
 setMoodleUI(int2, moodlesUI);
 moodlesUI.setVisible(true);
 getUI().add(moodlesUI);
 }

 getUI().add(getDebugConsole());
 getUI().add(getServerToolbox());
 setLastMouseTexture(getMouseArrow());
 resize();

 for (int int3 = 0; int3 < 4; int3++) {
 ActionProgressBar actionProgressBar = new ActionProgressBar(0, 0);
 actionProgressBar.setRenderThisPlayerOnly(int3);
 setProgressBar(int3, actionProgressBar);
 getUI().add(actionProgressBar);
 actionProgressBar.setValue(1.0F);
 actionProgressBar.setVisible(false);
 }

 playerInventoryUI = nullptr;
 playerLootUI = nullptr;
 LuaEventManager.triggerEvent("OnCreateUI");
 }
 }
 }

 static void render() {
 if (!useUIFBO || Core.getInstance().UIRenderThisFrame) {
 if (!bSuspend) {
 long long0 = System.currentTimeMillis();
 uiRenderIntervalMS = Math.min(long0 - uiRenderTimeMS, 1000L);
 uiRenderTimeMS = long0;
 UIElement.StencilLevel = 0;
 if (useUIFBO) {
 SpriteRenderer.instance.setDefaultStyle(UIFBOStyle.instance);
 }

 UITransition.UpdateAll();
 if (getBlack() == nullptr) {
 setBlack(Texture.getSharedTexture("black.png"));
 }

 if (LuaManager.thread == defaultthread) {
 LuaEventManager.triggerEvent("OnPreUIDraw");
 }

 int int0 = Mouse.getXA();
 int int1 = Mouse.getYA();
 if (isbFadeBeforeUI()) {
 setFadeAlpha(getFadeInTime().floatValue() / getFadeInTimeMax().floatValue());
 if (getFadeAlpha() > 1.0) {
 setFadeAlpha(1.0);
 }

 if (getFadeAlpha() < 0.0) {
 setFadeAlpha(0.0);
 }

 if (isFadingOut()) {
 setFadeAlpha(1.0 - getFadeAlpha());
 }

 if (IsoCamera.CamCharacter != nullptr && getFadeAlpha() > 0.0) {
 DrawTexture(getBlack(), 0.0, 0.0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), getFadeAlpha());
 }
 }

 setLastAlpha(getFadeAlpha().floatValue());

 for (int int2 = 0; int2 < IsoPlayer.numPlayers; int2++) {
 if (IsoPlayer.players[int2] != nullptr && playerFadeInfo[int2].isFadeBeforeUI()) {
 playerFadeInfo[int2].render();
 }
 }

 for (int int3 = 0; int3 < getUI().size(); int3++) {
 if ((UI.get(int3).isIgnoreLossControl() || !TutorialManager.instance.StealControl) && !UI.get(int3).isFollowGameWorld()) {
 try {
 if (getUI().get(int3).isDefaultDraw()) {
 getUI().get(int3).render();
 }
 } catch (Exception exception) {
 Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, exception);
 }
 }
 }

 if (getToolTip() != nullptr) {
 getToolTip().render();
 }

 if (isShowPausedMessage() && GameTime.isGamePaused() && (getModal() == nullptr || !Modal.isVisible()) && VisibleAllUI) {
 std::string string = Translator.getText("IGUI_GamePaused");
 int int4 = TextManager.instance.MeasureStringX(UIFont.Small, string) + 32;
 int int5 = TextManager.instance.font.getLineHeight();
 int int6 = (int)Math.ceil(int5 * 1.5);
 SpriteRenderer.instance
 .renderi(
 nullptr,
 Core.getInstance().getScreenWidth() / 2 - int4 / 2,
 Core.getInstance().getScreenHeight() / 2 - int6 / 2,
 int4,
 int6,
 0.0F,
 0.0F,
 0.0F,
 0.75F,
 nullptr
 );
 TextManager.instance
 .DrawStringCentre(
 Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2 - int5 / 2, string, 1.0, 1.0, 1.0, 1.0
 );
 }

 if (!isbFadeBeforeUI()) {
 setFadeAlpha(getFadeInTime() / getFadeInTimeMax());
 if (getFadeAlpha() > 1.0) {
 setFadeAlpha(1.0);
 }

 if (getFadeAlpha() < 0.0) {
 setFadeAlpha(0.0);
 }

 if (isFadingOut()) {
 setFadeAlpha(1.0 - getFadeAlpha());
 }

 if (IsoCamera.CamCharacter != nullptr && getFadeAlpha() > 0.0) {
 DrawTexture(getBlack(), 0.0, 0.0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), getFadeAlpha());
 }
 }

 for (int int7 = 0; int7 < IsoPlayer.numPlayers; int7++) {
 if (IsoPlayer.players[int7] != nullptr && !playerFadeInfo[int7].isFadeBeforeUI()) {
 playerFadeInfo[int7].render();
 }
 }

 if (LuaManager.thread == defaultthread) {
 LuaEventManager.triggerEvent("OnPostUIDraw");
 }

 if (useUIFBO) {
 SpriteRenderer.instance.setDefaultStyle(TransparentStyle.instance);
 }
 }
 }
 }

 static void resize() {
 if (useUIFBO && UIFBO != nullptr) {
 CreateFBO(Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight());
 }

 if (getClock() != nullptr) {
 setLastOffX(Core.getInstance().getScreenWidth());
 setLastOffY(Core.getInstance().getScreenHeight());

 for (int int0 = 0; int0 < 4; int0++) {
 int int1 = Core.getInstance().getScreenWidth();
 int int2 = Core.getInstance().getScreenHeight();
 uint8_t byte0;
 if (!Clock.instance.isVisible()) {
 byte0 = 24;
 } else {
 byte0 = 64;
 }

 if (int0 == 0 && IsoPlayer.numPlayers > 1 || int0 == 2) {
 int1 /= 2;
 }

 MoodleUI[int0].setX(int1 - 50);
 if ((int0 == 0 || int0 == 1) && IsoPlayer.numPlayers > 1) {
 MoodleUI[int0].setY(byte0);
 }

 if (int0 == 2 || int0 == 3) {
 MoodleUI[int0].setY(int2 / 2 + byte0);
 }

 MoodleUI[int0].setVisible(VisibleAllUI && IsoPlayer.players[int0] != nullptr);
 }

 clock.resize();
 if (IsoPlayer.numPlayers == 1) {
 if (Core.getInstance().getOptionClockSize() == 2) {
 clock.setX(Core.getInstance().getScreenWidth() - 166);
 } else {
 clock.setX(Core.getInstance().getScreenWidth() - 91);
 }
 } else {
 if (Core.getInstance().getOptionClockSize() == 2) {
 clock.setX(Core.getInstance().getScreenWidth() / 2.0F - 83.0F);
 } else {
 clock.setX(Core.getInstance().getScreenWidth() / 2.0F - 45.5F);
 }

 clock.setY(Core.getInstance().getScreenHeight() - 70);
 }

 if (IsoPlayer.numPlayers == 1) {
 speedControls.setX(Core.getInstance().getScreenWidth() - 110);
 } else {
 speedControls.setX(Core.getInstance().getScreenWidth() / 2 - 50);
 }

 if (IsoPlayer.numPlayers == 1 && !clock.isVisible()) {
 speedControls.setY(clock.getY());
 } else {
 speedControls.setY(clock.getY() + clock.getHeight() + 6.0);
 }

 speedControls.setVisible(VisibleAllUI && !IsoPlayer.allPlayersDead());
 }
 }

 static Vector2 getTileFromMouse(double mx, double my, double z) {
 PickedTile.x = IsoUtils.XToIso((float)(mx - 0.0), (float)(my - 0.0), (float)z);
 PickedTile.y = IsoUtils.YToIso((float)(mx - 0.0), (float)(my - 0.0), (float)z);
 PickedTileLocal.x = getPickedTile().x - (int)getPickedTile().x;
 PickedTileLocal.y = getPickedTile().y - (int)getPickedTile().y;
 PickedTile.x = (int)getPickedTile().x;
 PickedTile.y = (int)getPickedTile().y;
 return getPickedTile();
 }

 static void update() {
 if (!bSuspend) {
 if (!toRemove.empty()) {
 UI.removeAll(toRemove);
 }

 toRemove.clear();
 if (!toAdd.empty()) {
 UI.addAll(toAdd);
 }

 toAdd.clear();
 setFadeInTime(getFadeInTime() - 1.0);

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 playerFadeInfo[int0].update();
 }

 long long0 = System.currentTimeMillis();
 if (long0 - uiUpdateTimeMS >= 100L) {
 doTick = true;
 uiUpdateIntervalMS = Math.min(long0 - uiUpdateTimeMS, 1000L);
 uiUpdateTimeMS = long0;
 } else {
 doTick = false;
 }

 bool boolean0 = false;
 bool boolean1 = false;
 bool boolean2 = false;
 int int1 = Mouse.getXA();
 int int2 = Mouse.getYA();
 int int3 = Mouse.getX();
 int int4 = Mouse.getY();
 tutorialStack.clear();

 for (int int5 = UI.size() - 1; int5 >= 0; int5--) {
 UIElement uIElement0 = UI.get(int5);
 if (uIElement0.getParent() != nullptr) {
 UI.remove(int5);
 throw std::make_unique<IllegalStateException>();
 }

 if (uIElement0.isFollowGameWorld()) {
 tutorialStack.add(uIElement0);
 }

 if (uIElement0 instanceof ObjectTooltip) {
 UIElement uIElement1 = UI.remove(int5);
 UI.add(uIElement1);
 }
 }

 for (int int6 = 0; int6 < UI.size(); int6++) {
 UIElement uIElement2 = UI.get(int6);
 if (uIElement2.alwaysOnTop || toTop.contains(uIElement2) {
 UIElement uIElement3 = UI.remove(int6);
 int6--;
 toAdd.add(uIElement3);
 }
 }

 if (!toAdd.empty()) {
 UI.addAll(toAdd);
 toAdd.clear();
 }

 toTop.clear();

 for (int int7 = 0; int7 < UI.size(); int7++) {
 UIElement uIElement4 = UI.get(int7);
 if (uIElement4.alwaysBack) {
 UIElement uIElement5 = UI.remove(int7);
 UI.add(0, uIElement5);
 }
 }

 for (int int8 = 0; int8 < tutorialStack.size(); int8++) {
 UI.remove(tutorialStack.get(int8);
 UI.add(0, tutorialStack.get(int8);
 }

 if (Mouse.isLeftPressed()) {
 Core.UnfocusActiveTextEntryBox();

 for (int int9 = UI.size() - 1; int9 >= 0; int9--) {
 UIElement uIElement6 = UI.get(int9);
 if ((getModal() == nullptr || getModal() == uIElement6 || !getModal().isVisible())
 && (uIElement6.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
 && uIElement6.isVisible()) {
 if ((
 !(int1 >= uIElement6.getX())
 || !(int2 >= uIElement6.getY())
 || !(int1 < uIElement6.getX() + uIElement6.getWidth())
 || !(int2 < uIElement6.getY() + uIElement6.getHeight())
 )
 && !uIElement6.isCapture()) {
 uIElement6.onMouseDownOutside(int1 - uIElement6.getX().intValue(), int2 - uIElement6.getY().intValue());
 } else if (uIElement6.onMouseDown(int1 - uIElement6.getX().intValue(), int2 - uIElement6.getY().intValue())) {
 boolean0 = true;
 break;
 }
 }
 }

 if (checkPicked() && !boolean0) {
 LuaEventManager.triggerEvent("OnObjectLeftMouseButtonDown", Picked.tile, BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2);
 }

 if (!boolean0) {
 LuaEventManager.triggerEvent("OnMouseDown", BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2);
 CloseContainers();
 if (IsoWorld.instance.CurrentCell != nullptr
 && !IsoWorld.instance.CurrentCell.DoBuilding(0, false)
 && getPicked() != nullptr
 && !GameTime.isGamePaused()
 && IsoPlayer.getInstance() != nullptr
 && !IsoPlayer.getInstance().isAiming()
 && !IsoPlayer.getInstance().isAsleep()) {
 getPicked().tile.onMouseLeftClick(getPicked().lx, getPicked().ly);
 }
 } else {
 Mouse.UIBlockButtonDown(0);
 }
 }

 if (Mouse.isLeftReleased()) {
 bool boolean3 = false;

 for (int int10 = UI.size() - 1; int10 >= 0; int10--) {
 UIElement uIElement7 = UI.get(int10);
 if ((uIElement7.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
 && uIElement7.isVisible()
 && (getModal() == nullptr || getModal() == uIElement7 || !getModal().isVisible())) {
 if ((
 !(int1 >= uIElement7.getX())
 || !(int2 >= uIElement7.getY())
 || !(int1 < uIElement7.getX() + uIElement7.getWidth())
 || !(int2 < uIElement7.getY() + uIElement7.getHeight())
 )
 && !uIElement7.isCapture()) {
 uIElement7.onMouseUpOutside(int1 - uIElement7.getX().intValue(), int2 - uIElement7.getY().intValue());
 } else if (uIElement7.onMouseUp(int1 - uIElement7.getX().intValue(), int2 - uIElement7.getY().intValue())) {
 boolean3 = true;
 break;
 }
 }
 }

 if (!boolean3) {
 LuaEventManager.triggerEvent("OnMouseUp", BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2);
 if (checkPicked() && !boolean0) {
 LuaEventManager.triggerEvent(
 "OnObjectLeftMouseButtonUp", Picked.tile, BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2)
 );
 }
 }
 }

 if (Mouse.isRightPressed()) {
 for (int int11 = UI.size() - 1; int11 >= 0; int11--) {
 UIElement uIElement8 = UI.get(int11);
 if (uIElement8.isVisible() && (getModal() == nullptr || getModal() == uIElement8 || !getModal().isVisible())) {
 if ((
 !(int1 >= uIElement8.getX())
 || !(int2 >= uIElement8.getY())
 || !(int1 < uIElement8.getX() + uIElement8.getWidth())
 || !(int2 < uIElement8.getY() + uIElement8.getHeight())
 )
 && !uIElement8.isCapture()) {
 uIElement8.onRightMouseDownOutside(int1 - uIElement8.getX().intValue(), int2 - uIElement8.getY().intValue());
 } else if (uIElement8.onRightMouseDown(int1 - uIElement8.getX().intValue(), int2 - uIElement8.getY().intValue())) {
 boolean1 = true;
 break;
 }
 }
 }

 if (!boolean1) {
 LuaEventManager.triggerEvent("OnRightMouseDown", BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2);
 if (checkPicked() && !boolean1) {
 LuaEventManager.triggerEvent(
 "OnObjectRightMouseButtonDown", Picked.tile, BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2)
 );
 }
 } else {
 Mouse.UIBlockButtonDown(1);
 }

 if (IsoWorld.instance.CurrentCell != nullptr
 && getPicked() != nullptr
 && getSpeedControls() != nullptr
 && !IsoPlayer.getInstance().isAiming()
 && !IsoPlayer.getInstance().isAsleep()
 && !GameTime.isGamePaused()) {
 getSpeedControls().SetCurrentGameSpeed(1);
 getPicked().tile.onMouseRightClick(getPicked().lx, getPicked().ly);
 setRightDownObject(getPicked().tile);
 }
 }

 if (Mouse.isRightReleased()) {
 bool boolean4 = false;
 bool boolean5 = false;

 for (int int12 = UI.size() - 1; int12 >= 0; int12--) {
 UIElement uIElement9 = UI.get(int12);
 if ((uIElement9.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
 && uIElement9.isVisible()
 && (getModal() == nullptr || getModal() == uIElement9 || !getModal().isVisible())) {
 if ((
 !(int1 >= uIElement9.getX())
 || !(int2 >= uIElement9.getY())
 || !(int1 < uIElement9.getX() + uIElement9.getWidth())
 || !(int2 < uIElement9.getY() + uIElement9.getHeight())
 )
 && !uIElement9.isCapture()) {
 uIElement9.onRightMouseUpOutside(int1 - uIElement9.getX().intValue(), int2 - uIElement9.getY().intValue());
 } else if (uIElement9.onRightMouseUp(int1 - uIElement9.getX().intValue(), int2 - uIElement9.getY().intValue())) {
 boolean5 = true;
 break;
 }
 }
 }

 if (!boolean5) {
 LuaEventManager.triggerEvent("OnRightMouseUp", BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2);
 if (checkPicked()) {
 bool boolean6 = true;
 if (GameClient.bClient && Picked.tile.getSquare() != nullptr) {
 SafeHouse safeHouse = SafeHouse.isSafeHouse(Picked.tile.getSquare(), IsoPlayer.getInstance().getUsername(), true);
 if (safeHouse != nullptr) {
 boolean6 = false;
 }
 }

 if (boolean6) {
 LuaEventManager.triggerEvent(
 "OnObjectRightMouseButtonUp", Picked.tile, BoxedStaticValues.toDouble(int1), BoxedStaticValues.toDouble(int2)
 );
 }
 }
 }

 if (IsoPlayer.getInstance() != nullptr) {
 IsoPlayer.getInstance().setDragObject(nullptr);
 }

 if (IsoWorld.instance.CurrentCell != nullptr
 && getRightDownObject() != nullptr
 && IsoPlayer.getInstance() != nullptr
 && !IsoPlayer.getInstance().IsAiming()
 && !IsoPlayer.getInstance().isAsleep()) {
 getRightDownObject().onMouseRightReleased();
 setRightDownObject(nullptr);
 }
 }

 lastwheel = 0;
 wheel = Mouse.getWheelState();
 bool boolean7 = false;
 if (wheel != lastwheel) {
 int int13 = wheel - lastwheel < 0 ? 1 : -1;

 for (int int14 = UI.size() - 1; int14 >= 0; int14--) {
 UIElement uIElement10 = UI.get(int14);
 if ((uIElement10.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
 && uIElement10.isVisible()
 && (uIElement10.isPointOver(int1, int2) || uIElement10.isCapture())
 && uIElement10.onMouseWheel(int13) {
 boolean7 = true;
 break;
 }
 }

 if (!boolean7) {
 Core.getInstance().doZoomScroll(0, int13);
 }
 }

 if (getLastMouseX() != int1 || getLastMouseY() != int2) {
 for (int int15 = UI.size() - 1; int15 >= 0; int15--) {
 UIElement uIElement11 = UI.get(int15);
 if ((uIElement11.isIgnoreLossControl() || !TutorialManager.instance.StealControl) && uIElement11.isVisible()) {
 if ((
 !(int1 >= uIElement11.getX())
 || !(int2 >= uIElement11.getY())
 || !(int1 < uIElement11.getX() + uIElement11.getWidth())
 || !(int2 < uIElement11.getY() + uIElement11.getHeight())
 )
 && !uIElement11.isCapture()) {
 uIElement11.onMouseMoveOutside(int1 - getLastMouseX(), int2 - getLastMouseY());
 } else if (!boolean2 && uIElement11.onMouseMove(int1 - getLastMouseX(), int2 - getLastMouseY())) {
 boolean2 = true;
 }
 }
 }
 }

 if (!boolean2 && IsoPlayer.players[0] != nullptr) {
 setPicked(IsoObjectPicker.Instance.ContextPick(int1, int2);
 if (IsoCamera.CamCharacter != nullptr) {
 setPickedTile(getTileFromMouse(int3, int4, (int)IsoPlayer.players[0].getZ()));
 }

 LuaEventManager.triggerEvent(
 "OnMouseMove",
 BoxedStaticValues.toDouble(int1),
 BoxedStaticValues.toDouble(int2),
 BoxedStaticValues.toDouble(int3),
 BoxedStaticValues.toDouble(int4)
 );
 } else {
 Mouse.UIBlockButtonDown(2);
 }

 setLastMouseX(int1);
 setLastMouseY(int2);

 for (int int16 = 0; int16 < UI.size(); int16++) {
 UI.get(int16).update();
 }

 updateTooltip(int1, int2);
 handleZoomKeys();
 IsoCamera.cameras[0].lastOffX = (int)IsoCamera.cameras[0].OffX;
 IsoCamera.cameras[0].lastOffY = (int)IsoCamera.cameras[0].OffY;
 }
 }

 static bool checkPicked() {
 return Picked != nullptr && Picked.tile != nullptr && Picked.tile.getObjectIndex() != -1;
 }

 static void handleZoomKeys() {
 bool boolean0 = true;
 if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.IsEditable && Core.CurrentTextEntryBox.DoingTextEntry) {
 boolean0 = false;
 }

 if (GameTime.isGamePaused()) {
 boolean0 = false;
 }

 if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Zoom in"))) {
 if (boolean0 && !KeyDownZoomIn) {
 Core.getInstance().doZoomScroll(0, -1);
 }

 KeyDownZoomIn = true;
 } else {
 KeyDownZoomIn = false;
 }

 if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Zoom out"))) {
 if (boolean0 && !KeyDownZoomOut) {
 Core.getInstance().doZoomScroll(0, 1);
 }

 KeyDownZoomOut = true;
 } else {
 KeyDownZoomOut = false;
 }
 }

 /**
 * @return the lastMouseX
 */
 static double getLastMouseX() {
 return BoxedStaticValues.toDouble(lastMouseX);
 }

 /**
 * 
 * @param aLastMouseX the lastMouseX to set
 */
 static void setLastMouseX(double aLastMouseX) {
 lastMouseX = (int)aLastMouseX;
 }

 /**
 * @return the lastMouseY
 */
 static double getLastMouseY() {
 return BoxedStaticValues.toDouble(lastMouseY);
 }

 /**
 * 
 * @param aLastMouseY the lastMouseY to set
 */
 static void setLastMouseY(double aLastMouseY) {
 lastMouseY = (int)aLastMouseY;
 }

 /**
 * @return the Picked
 */
 public static IsoObjectPicker.ClickObject getPicked() {
 return Picked;
 }

 /**
 * 
 * @param aPicked the Picked to set
 */
 static void setPicked(IsoObjectPicker.ClickObject aPicked) {
 Picked = aPicked;
 }

 /**
 * @return the clock
 */
 static Clock getClock() {
 return clock;
 }

 /**
 * 
 * @param aClock the clock to set
 */
 static void setClock(Clock aClock) {
 clock = aClock;
 }

 /**
 * @return the UI
 */
 public static ArrayList<UIElement> getUI() {
 return UI;
 }

 /**
 * 
 * @param aUI the UI to set
 */
 static void setUI(ArrayList<UIElement> aUI) {
 PZArrayUtil.copy(UI, aUI);
 }

 /**
 * @return the toolTip
 */
 static ObjectTooltip getToolTip() {
 return toolTip;
 }

 /**
 * 
 * @param aToolTip the toolTip to set
 */
 static void setToolTip(ObjectTooltip aToolTip) {
 toolTip = aToolTip;
 }

 /**
 * @return the mouseArrow
 */
 static Texture getMouseArrow() {
 return mouseArrow;
 }

 /**
 * 
 * @param aMouseArrow the mouseArrow to set
 */
 static void setMouseArrow(Texture aMouseArrow) {
 mouseArrow = aMouseArrow;
 }

 /**
 * @return the mouseExamine
 */
 static Texture getMouseExamine() {
 return mouseExamine;
 }

 /**
 * 
 * @param aMouseExamine the mouseExamine to set
 */
 static void setMouseExamine(Texture aMouseExamine) {
 mouseExamine = aMouseExamine;
 }

 /**
 * @return the mouseAttack
 */
 static Texture getMouseAttack() {
 return mouseAttack;
 }

 /**
 * 
 * @param aMouseAttack the mouseAttack to set
 */
 static void setMouseAttack(Texture aMouseAttack) {
 mouseAttack = aMouseAttack;
 }

 /**
 * @return the mouseGrab
 */
 static Texture getMouseGrab() {
 return mouseGrab;
 }

 /**
 * 
 * @param aMouseGrab the mouseGrab to set
 */
 static void setMouseGrab(Texture aMouseGrab) {
 mouseGrab = aMouseGrab;
 }

 /**
 * @return the speedControls
 */
 static SpeedControls getSpeedControls() {
 return speedControls;
 }

 /**
 * 
 * @param aSpeedControls the speedControls to set
 */
 static void setSpeedControls(SpeedControls aSpeedControls) {
 speedControls = aSpeedControls;
 }

 /**
 * @return the DebugConsole
 */
 static UIDebugConsole getDebugConsole() {
 return DebugConsole;
 }

 /**
 * 
 * @param aDebugConsole the DebugConsole to set
 */
 static void setDebugConsole(UIDebugConsole aDebugConsole) {
 DebugConsole = aDebugConsole;
 }

 /**
 * @return the ServerToolbox
 */
 static UIServerToolbox getServerToolbox() {
 return ServerToolbox;
 }

 /**
 * 
 * @param aServerToolbox the ServerToolbox to set
 */
 static void setServerToolbox(UIServerToolbox aServerToolbox) {
 ServerToolbox = aServerToolbox;
 }

 /**
 * @return the MoodleUI
 */
 static MoodlesUI getMoodleUI(double index) {
 return MoodleUI[(int)index];
 }

 /**
 * 
 * @param index
 * @param aMoodleUI the MoodleUI to set
 */
 static void setMoodleUI(double index, MoodlesUI aMoodleUI) {
 MoodleUI[(int)index] = aMoodleUI;
 }

 /**
 * @return the bFadeBeforeUI
 */
 static bool isbFadeBeforeUI() {
 return bFadeBeforeUI;
 }

 /**
 * 
 * @param abFadeBeforeUI the bFadeBeforeUI to set
 */
 static void setbFadeBeforeUI(bool abFadeBeforeUI) {
 bFadeBeforeUI = abFadeBeforeUI;
 }

 /**
 * @return the ProgressBar
 */
 static ActionProgressBar getProgressBar(double index) {
 return ProgressBar[(int)index];
 }

 /**
 * 
 * @param index
 * @param aProgressBar the ProgressBar to set
 */
 static void setProgressBar(double index, ActionProgressBar aProgressBar) {
 ProgressBar[(int)index] = aProgressBar;
 }

 /**
 * @return the FadeAlpha
 */
 static double getFadeAlpha() {
 return BoxedStaticValues.toDouble(FadeAlpha);
 }

 /**
 * 
 * @param aFadeAlpha the FadeAlpha to set
 */
 static void setFadeAlpha(double aFadeAlpha) {
 FadeAlpha = (float)aFadeAlpha;
 }

 /**
 * @return the FadeInTimeMax
 */
 static double getFadeInTimeMax() {
 return BoxedStaticValues.toDouble(FadeInTimeMax);
 }

 /**
 * 
 * @param aFadeInTimeMax the FadeInTimeMax to set
 */
 static void setFadeInTimeMax(double aFadeInTimeMax) {
 FadeInTimeMax = (int)aFadeInTimeMax;
 }

 /**
 * @return the FadeInTime
 */
 static double getFadeInTime() {
 return BoxedStaticValues.toDouble(FadeInTime);
 }

 /**
 * 
 * @param aFadeInTime the FadeInTime to set
 */
 static void setFadeInTime(double aFadeInTime) {
 FadeInTime = Math.max((int)aFadeInTime, 0);
 }

 /**
 * @return the FadingOut
 */
 static bool isFadingOut() {
 return FadingOut ? Boolean.TRUE : Boolean.FALSE;
 }

 /**
 * 
 * @param aFadingOut the FadingOut to set
 */
 static void setFadingOut(bool aFadingOut) {
 FadingOut = aFadingOut;
 }

 /**
 * @return the lastMouseTexture
 */
 static Texture getLastMouseTexture() {
 return lastMouseTexture;
 }

 /**
 * 
 * @param aLastMouseTexture the lastMouseTexture to set
 */
 static void setLastMouseTexture(Texture aLastMouseTexture) {
 lastMouseTexture = aLastMouseTexture;
 }

 /**
 * @return the LastPicked
 */
 static IsoObject getLastPicked() {
 return LastPicked;
 }

 /**
 * 
 * @param aLastPicked the LastPicked to set
 */
 static void setLastPicked(IsoObject aLastPicked) {
 LastPicked = aLastPicked;
 }

 /**
 * @return the DoneTutorials
 */
 public static ArrayList<String> getDoneTutorials() {
 return DoneTutorials;
 }

 /**
 * 
 * @param aDoneTutorials the DoneTutorials to set
 */
 static void setDoneTutorials(ArrayList<String> aDoneTutorials) {
 PZArrayUtil.copy(DoneTutorials, aDoneTutorials);
 }

 /**
 * @return the lastOffX
 */
 static float getLastOffX() {
 return lastOffX;
 }

 /**
 * 
 * @param aLastOffX the lastOffX to set
 */
 static void setLastOffX(float aLastOffX) {
 lastOffX = aLastOffX;
 }

 /**
 * @return the lastOffY
 */
 static float getLastOffY() {
 return lastOffY;
 }

 /**
 * 
 * @param aLastOffY the lastOffY to set
 */
 static void setLastOffY(float aLastOffY) {
 lastOffY = aLastOffY;
 }

 /**
 * @return the Modal
 */
 static ModalDialog getModal() {
 return Modal;
 }

 /**
 * 
 * @param aModal the Modal to set
 */
 static void setModal(ModalDialog aModal) {
 Modal = aModal;
 }

 /**
 * @return the black
 */
 static Texture getBlack() {
 return black;
 }

 /**
 * 
 * @param aBlack the black to set
 */
 static void setBlack(Texture aBlack) {
 black = aBlack;
 }

 /**
 * @return the lastAlpha
 */
 static float getLastAlpha() {
 return lastAlpha;
 }

 /**
 * 
 * @param aLastAlpha the lastAlpha to set
 */
 static void setLastAlpha(float aLastAlpha) {
 lastAlpha = aLastAlpha;
 }

 /**
 * @return the PickedTileLocal
 */
 static Vector2 getPickedTileLocal() {
 return PickedTileLocal;
 }

 /**
 * 
 * @param aPickedTileLocal the PickedTileLocal to set
 */
 static void setPickedTileLocal(Vector2 aPickedTileLocal) {
 PickedTileLocal.set(aPickedTileLocal);
 }

 /**
 * @return the PickedTile
 */
 static Vector2 getPickedTile() {
 return PickedTile;
 }

 /**
 * 
 * @param aPickedTile the PickedTile to set
 */
 static void setPickedTile(Vector2 aPickedTile) {
 PickedTile.set(aPickedTile);
 }

 /**
 * @return the RightDownObject
 */
 static IsoObject getRightDownObject() {
 return RightDownObject;
 }

 /**
 * 
 * @param aRightDownObject the RightDownObject to set
 */
 static void setRightDownObject(IsoObject aRightDownObject) {
 RightDownObject = aRightDownObject;
 }

 static void pushToTop(UIElement uIElement) {
 toTop.add(uIElement);
 }

 static bool isShowPausedMessage() {
 return showPausedMessage;
 }

 static void setShowPausedMessage(bool _showPausedMessage) {
 showPausedMessage = _showPausedMessage;
 }

 static void setShowLuaDebuggerOnError(bool show) {
 bShowLuaDebuggerOnError = show;
 }

 static bool isShowLuaDebuggerOnError() {
 return bShowLuaDebuggerOnError;
 }

 static void debugBreakpoint(const std::string& filename, long pc) {
 if (bShowLuaDebuggerOnError) {
 if (Core.CurrentTextEntryBox != nullptr) {
 Core.CurrentTextEntryBox.DoingTextEntry = false;
 Core.CurrentTextEntryBox = nullptr;
 }

 if (!GameServer.bServer) {
 if (!(GameWindow.states.current instanceof GameLoadingState) {
 previousThread = defaultthread;
 defaultthread = LuaManager.debugthread;
 int int0 = Core.getInstance().frameStage;
 if (int0 != 0) {
 if (int0 <= 1) {
 Core.getInstance().EndFrame(0);
 }

 if (int0 <= 2) {
 Core.getInstance().StartFrameUI();
 }

 if (int0 <= 3) {
 Core.getInstance().EndFrameUI();
 }
 }

 LuaManager.thread.bStep = false;
 LuaManager.thread.bStepInto = false;
 if (!toRemove.empty()) {
 UI.removeAll(toRemove);
 }

 toRemove.clear();
 if (!toAdd.empty()) {
 UI.addAll(toAdd);
 }

 toAdd.clear();
 std::vector arrayList = new ArrayList();
 bool boolean0 = bSuspend;
 arrayList.addAll(UI);
 UI.clear();
 bSuspend = false;
 setShowPausedMessage(false);
 bool boolean1 = false;
 boolean[] booleans = new boolean[11];

 for (int int1 = 0; int1 < 11; int1++) {
 booleans[int1] = true;
 }

 if (debugUI.size() == 0) {
 LuaManager.debugcaller.pcall(LuaManager.debugthread, LuaManager.env.rawget("DoLuaDebugger"), filename, pc);
 } else {
 UI.addAll(debugUI);
 LuaManager.debugcaller.pcall(LuaManager.debugthread, LuaManager.env.rawget("DoLuaDebuggerOnBreak"), filename, pc);
 }

 Mouse.setCursorVisible(true);
 sync.begin();

 while (!boolean1) {
 if (RenderThread.isCloseRequested()) {
 System.exit(0);
 }

 if (!GameWindow.bLuaDebuggerKeyDown && GameKeyboard.isKeyDown(Core.getInstance().getKey("Toggle Lua Debugger"))) {
 GameWindow.bLuaDebuggerKeyDown = true;
 executeGame(arrayList, boolean0, int0);
 return;
 }

 std::string string = luaDebuggerAction;
 luaDebuggerAction = nullptr;
 if ("StepInto".equalsIgnoreCase(string) {
 LuaManager.thread.bStep = true;
 LuaManager.thread.bStepInto = true;
 executeGame(arrayList, boolean0, int0);
 return;
 }

 if ("StepOver".equalsIgnoreCase(string) {
 LuaManager.thread.bStep = true;
 LuaManager.thread.bStepInto = false;
 LuaManager.thread.lastCallFrame = LuaManager.thread.getCurrentCoroutine().getCallframeTop();
 executeGame(arrayList, boolean0, int0);
 return;
 }

 if ("Resume".equalsIgnoreCase(string) {
 executeGame(arrayList, boolean0, int0);
 return;
 }

 sync.startFrame();

 for (int int2 = 0; int2 < 11; int2++) {
 bool boolean2 = GameKeyboard.isKeyDown(59 + int2);
 if (boolean2) {
 if (!booleans[int2]) {
 if (int2 + 1 == 5) {
 LuaManager.thread.bStep = true;
 LuaManager.thread.bStepInto = true;
 executeGame(arrayList, boolean0, int0);
 return;
 }

 if (int2 + 1 == 6) {
 LuaManager.thread.bStep = true;
 LuaManager.thread.bStepInto = false;
 LuaManager.thread.lastCallFrame = LuaManager.thread.getCurrentCoroutine().getCallframeTop();
 executeGame(arrayList, boolean0, int0);
 return;
 }
 }

 booleans[int2] = true;
 } else {
 booleans[int2] = false;
 }
 }

 Mouse.update();
 GameKeyboard.update();
 Core.getInstance().DoFrameReady();
 update();
 Core.getInstance().StartFrame(0, true);
 Core.getInstance().EndFrame(0);
 Core.getInstance().RenderOffScreenBuffer();
 if (Core.getInstance().StartFrameUI()) {
 render();
 }

 Core.getInstance().EndFrameUI();
 resize();
 if (!GameKeyboard.isKeyDown(Core.getInstance().getKey("Toggle Lua Debugger"))) {
 GameWindow.bLuaDebuggerKeyDown = false;
 }

 sync.endFrame();
 Core.getInstance().setScreenSize(RenderThread.getDisplayWidth(), RenderThread.getDisplayHeight());
 }
 }
 }
 }
 }

 static void executeGame(ArrayList<UIElement> arrayList, bool boolean0, int int0) {
 debugUI.clear();
 debugUI.addAll(UI);
 UI.clear();
 UI.addAll(arrayList);
 bSuspend = boolean0;
 setShowPausedMessage(true);
 if (!LuaManager.thread.bStep && int0 != 0) {
 if (int0 == 1) {
 Core.getInstance().StartFrame(0, true);
 }

 if (int0 == 2) {
 Core.getInstance().StartFrame(0, true);
 Core.getInstance().EndFrame(0);
 }

 if (int0 == 3) {
 Core.getInstance().StartFrame(0, true);
 Core.getInstance().EndFrame(0);
 Core.getInstance().StartFrameUI();
 }
 }

 defaultthread = previousThread;
 }

 static KahluaThread getDefaultThread() {
 if (defaultthread == nullptr) {
 defaultthread = LuaManager.thread;
 }

 return defaultthread;
 }

 static double getDoubleClickInterval() {
 return BoxedStaticValues.toDouble(500.0);
 }

 static double getDoubleClickDist() {
 return BoxedStaticValues.toDouble(5.0);
 }

 static bool isDoubleClick(double x1, double y1, double x2, double y2, double clickTime) {
 if (Math.abs(x2 - x1) > getDoubleClickDist()) {
 return false;
 } else if (Math.abs(y2 - y1) > getDoubleClickDist()) {
 return false;
 } else {
 return System.currentTimeMillis() - clickTime > getDoubleClickInterval() ? Boolean.FALSE : Boolean.TRUE;
 }
 }

 static void updateTooltip(double double1, double double0) {
 UIElement uIElement0 = nullptr;

 for (int int0 = getUI().size() - 1; int0 >= 0; int0--) {
 UIElement uIElement1 = getUI().get(int0);
 if (uIElement1 != toolTip
 && uIElement1.isVisible()
 && double1 >= uIElement1.getX()
 && double0 >= uIElement1.getY()
 && double1 < uIElement1.getX() + uIElement1.getWidth()
 && double0 < uIElement1.getY() + uIElement1.getHeight()
 && (uIElement1.maxDrawHeight == -1 || double0 < uIElement1.getY() + uIElement1.maxDrawHeight) {
 uIElement0 = uIElement1;
 break;
 }
 }

 IsoObject object = nullptr;
 if (uIElement0 == nullptr && getPicked() != nullptr) {
 object = getPicked().tile;
 if (object != getLastPicked() && toolTip != nullptr) {
 toolTip.targetAlpha = 0.0F;
 if (object.haveSpecialTooltip()) {
 if (getToolTip().Object != object) {
 getToolTip().show(object, (double)((int)double1 + 8), (double)((int)double0 + 16);
 if (toolTip.isVisible()) {
 toolTip.showDelay = 0;
 }
 } else {
 toolTip.targetAlpha = 1.0F;
 }
 }
 }
 }

 setLastPicked(object);
 if (toolTip != nullptr && (object == nullptr || toolTip.alpha <= 0.0F && toolTip.targetAlpha <= 0.0F) {
 toolTip.hide();
 }
 }

 static void setPlayerInventory(int playerIndex, UIElement inventory, UIElement loot) {
 if (playerIndex == 0) {
 playerInventoryUI = inventory;
 playerLootUI = loot;
 }
 }

 static void setPlayerInventoryTooltip(int playerIndex, UIElement inventory, UIElement loot) {
 if (playerIndex == 0) {
 playerInventoryTooltip = inventory;
 playerLootTooltip = loot;
 }
 }

 static bool isMouseOverInventory() {
 if (playerInventoryTooltip != nullptr && playerInventoryTooltip.isMouseOver()) {
 return true;
 } else if (playerLootTooltip != nullptr && playerLootTooltip.isMouseOver()) {
 return true;
 } else if (playerInventoryUI != nullptr && playerLootUI != nullptr) {
 return playerInventoryUI.getMaxDrawHeight() == -1.0 && playerInventoryUI.isMouseOver()
 ? true
 : playerLootUI.getMaxDrawHeight() == -1.0 && playerLootUI.isMouseOver();
 } else {
 return false;
 }
 }

 static void updateBeforeFadeOut() {
 if (!toRemove.empty()) {
 UI.removeAll(toRemove);
 toRemove.clear();
 }

 if (!toAdd.empty()) {
 UI.addAll(toAdd);
 toAdd.clear();
 }
 }

 static void setVisibleAllUI(bool visible) {
 VisibleAllUI = visible;
 }

 static void setFadeBeforeUI(int playerIndex, bool _bFadeBeforeUI) {
 playerFadeInfo[playerIndex].setFadeBeforeUI(_bFadeBeforeUI);
 }

 static float getFadeAlpha(double playerIndex) {
 return playerFadeInfo[(int)playerIndex].getFadeAlpha();
 }

 static void setFadeTime(double playerIndex, double FadeTime) {
 playerFadeInfo[(int)playerIndex].setFadeTime((int)FadeTime);
 }

 static void FadeIn(double playerIndex, double seconds) {
 playerFadeInfo[(int)playerIndex].FadeIn((int)seconds);
 }

 static void FadeOut(double playerIndex, double seconds) {
 playerFadeInfo[(int)playerIndex].FadeOut((int)seconds);
 }

 static bool isFBOActive() {
 return useUIFBO;
 }

 static double getMillisSinceLastUpdate() {
 return uiUpdateIntervalMS;
 }

 static double getSecondsSinceLastUpdate() {
 return uiUpdateIntervalMS / 1000.0;
 }

 static double getMillisSinceLastRender() {
 return uiRenderIntervalMS;
 }

 static double getSecondsSinceLastRender() {
 return uiRenderIntervalMS / 1000.0;
 }

 static bool onKeyPress(int key) {
 for (int int0 = UI.size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = UI.get(int0);
 if (uIElement.isVisible() && uIElement.isWantKeyEvents()) {
 uIElement.onKeyPress(key);
 if (uIElement.isKeyConsumed(key) {
 return true;
 }
 }
 }

 return false;
 }

 static bool onKeyRepeat(int key) {
 for (int int0 = UI.size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = UI.get(int0);
 if (uIElement.isVisible() && uIElement.isWantKeyEvents()) {
 uIElement.onKeyRepeat(key);
 if (uIElement.isKeyConsumed(key) {
 return true;
 }
 }
 }

 return false;
 }

 static bool onKeyRelease(int key) {
 for (int int0 = UI.size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = UI.get(int0);
 if (uIElement.isVisible() && uIElement.isWantKeyEvents()) {
 uIElement.onKeyRelease(key);
 if (uIElement.isKeyConsumed(key) {
 return true;
 }
 }
 }

 return false;
 }

 static bool isForceCursorVisible() {
 for (int int0 = UI.size() - 1; int0 >= 0; int0--) {
 UIElement uIElement = UI.get(int0);
 if (uIElement.isVisible() && (uIElement.isForceCursorVisible() || uIElement.isMouseOver())) {
 return true;
 }
 }

 return false;
 }

 static {
 for (int int0 = 0; int0 < 4; int0++) {
 playerFadeInfo[int0] = new UIManager.FadeInfo(int0);
 }
 }

 private static class FadeInfo {
 int playerIndex;
 bool bFadeBeforeUI = false;
 float FadeAlpha = 0.0F;
 int FadeTime = 2;
 int FadeTimeMax = 2;
 bool FadingOut = false;

 public FadeInfo(int arg0) {
 this->playerIndex = arg0;
 }

 bool isFadeBeforeUI() {
 return this->bFadeBeforeUI;
 }

 void setFadeBeforeUI(bool arg0) {
 this->bFadeBeforeUI = arg0;
 }

 float getFadeAlpha() {
 return this->FadeAlpha;
 }

 void setFadeAlpha(float arg0) {
 this->FadeAlpha = arg0;
 }

 int getFadeTime() {
 return this->FadeTime;
 }

 void setFadeTime(int arg0) {
 this->FadeTime = arg0;
 }

 int getFadeTimeMax() {
 return this->FadeTimeMax;
 }

 void setFadeTimeMax(int arg0) {
 this->FadeTimeMax = arg0;
 }

 bool isFadingOut() {
 return this->FadingOut;
 }

 void setFadingOut(bool arg0) {
 this->FadingOut = arg0;
 }

 void FadeIn(int arg0) {
 this->setFadeTimeMax((int)(arg0 * 30 * (PerformanceSettings.getLockFPS() / 30.0F);
 this->setFadeTime(this->getFadeTimeMax());
 this->setFadingOut(false);
 }

 void FadeOut(int arg0) {
 this->setFadeTimeMax((int)(arg0 * 30 * (PerformanceSettings.getLockFPS() / 30.0F);
 this->setFadeTime(this->getFadeTimeMax());
 this->setFadingOut(true);
 }

 void update() {
 this->setFadeTime(this->getFadeTime() - 1);
 }

 void render() {
 this->setFadeAlpha((float)this->getFadeTime() / this->getFadeTimeMax());
 if (this->getFadeAlpha() > 1.0F) {
 this->setFadeAlpha(1.0F);
 }

 if (this->getFadeAlpha() < 0.0F) {
 this->setFadeAlpha(0.0F);
 }

 if (this->isFadingOut()) {
 this->setFadeAlpha(1.0F - this->getFadeAlpha());
 }

 if (!(this->getFadeAlpha() <= 0.0F) {
 int int0 = IsoCamera.getScreenLeft(this->playerIndex);
 int int1 = IsoCamera.getScreenTop(this->playerIndex);
 int int2 = IsoCamera.getScreenWidth(this->playerIndex);
 int int3 = IsoCamera.getScreenHeight(this->playerIndex);
 UIManager.DrawTexture(UIManager.getBlack(), int0, int1, int2, int3, this->getFadeAlpha());
 }
 }
 }

 static class Sync {
 int fps = 30;
 long period = 1000000000L / this->fps;
 long excess;
 long beforeTime = System.nanoTime();
 long overSleepTime = 0L;

 void begin() {
 this->beforeTime = System.nanoTime();
 this->overSleepTime = 0L;
 }

 void startFrame() {
 this->excess = 0L;
 }

 void endFrame() {
 long long0 = System.nanoTime();
 long long1 = long0 - this->beforeTime;
 long long2 = this->period - long1 - this->overSleepTime;
 if (long2 > 0L) {
 try {
 Thread.sleep(long2 / 1000000L);
 } catch (InterruptedException interruptedException) {
 }

 this->overSleepTime = System.nanoTime() - long0 - long2;
 } else {
 this->excess -= long2;
 this->overSleepTime = 0L;
 }

 this->beforeTime = System.nanoTime();
 }
 }
}
} // namespace ui
} // namespace zombie
