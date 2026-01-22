#pragma once
#include <stack>
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
#include "zombie/iso/IsoObjectPicker/ClickObject.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/Vector2.h"
#include "zombie/iso/areas/SafeHouse.h"
#include "zombie/network/CoopMaster.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/UIManager/FadeInfo.h"
#include "zombie/ui/UIManager/Sync.h"
#include "zombie/util/list/PZArrayUtil.h"
#include <algorithm>

namespace zombie {
namespace ui {


class UIManager {
public:
    static int lastMouseX = 0;
    static int lastMouseY = 0;
    static ClickObject Picked = nullptr;
    static Clock clock;
   public static const std::vector<UIElement> UI = std::make_unique<std::vector<>>();
    static ObjectTooltip toolTip = nullptr;
    static Texture mouseArrow;
    static Texture mouseExamine;
    static Texture mouseAttack;
    static Texture mouseGrab;
    static SpeedControls speedControls;
    static UIDebugConsole DebugConsole;
    static UIServerToolbox ServerToolbox;
   public static const MoodlesUI[] MoodleUI = new MoodlesUI[4];
    static bool bFadeBeforeUI = false;
   public static const ActionProgressBar[] ProgressBar = new ActionProgressBar[4];
    static float FadeAlpha = 1.0F;
    static int FadeInTimeMax = 180;
    static int FadeInTime = 180;
    static bool FadingOut = false;
    static Texture lastMouseTexture;
    static IsoObject LastPicked = nullptr;
   public static const std::vector<std::string> DoneTutorials = std::make_unique<std::vector<>>();
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
    static const Vector2 PickedTileLocal = std::make_shared<Vector2>();
    static const Vector2 PickedTile = std::make_shared<Vector2>();
    static IsoObject RightDownObject = nullptr;
    static long uiUpdateTimeMS = 0L;
    static long uiUpdateIntervalMS = 0L;
    static long uiRenderTimeMS = 0L;
    static long uiRenderIntervalMS = 0L;
   private static const std::vector<UIElement> tutorialStack = std::make_unique<std::vector<>>();
   public static const std::vector<UIElement> toTop = std::make_unique<std::vector<>>();
    static KahluaThread defaultthread = nullptr;
    static KahluaThread previousThread = nullptr;
   static const std::vector<UIElement> toRemove = std::make_unique<std::vector<>>();
   static const std::vector<UIElement> toAdd = std::make_unique<std::vector<>>();
    static int wheel = 0;
    static int lastwheel = 0;
   static const std::vector<UIElement> debugUI = std::make_unique<std::vector<>>();
    static bool bShowLuaDebuggerOnError = true;
    static std::string luaDebuggerAction = nullptr;
    static const Sync sync = std::make_shared<Sync>();
    static bool showPausedMessage = true;
    static UIElement playerInventoryUI;
    static UIElement playerLootUI;
    static UIElement playerInventoryTooltip;
    static UIElement playerLootTooltip;
   private static const FadeInfo[] playerFadeInfo = new FadeInfo[4];

    static void AddUI(UIElement var0) {
      toRemove.remove(var0);
      toRemove.push_back(var0);
      toAdd.remove(var0);
      toAdd.push_back(var0);
   }

    static void RemoveElement(UIElement var0) {
      toAdd.remove(var0);
      toRemove.remove(var0);
      toRemove.push_back(var0);
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

    static void DrawTexture(Texture var0, double var1, double var3) {
    double var5 = var1 + var0.offsetX;
    double var7 = var3 + var0.offsetY;
      SpriteRenderer.instance.renderi(var0, (int)var5, (int)var7, var0.getWidth(), var0.getHeight(), 1.0F, 1.0F, 1.0F, 1.0F, nullptr);
   }

    static void DrawTexture(Texture var0, double var1, double var3, double var5, double var7, double var9) {
    double var11 = var1 + var0.offsetX;
    double var13 = var3 + var0.offsetY;
      SpriteRenderer.instance.renderi(var0, (int)var11, (int)var13, (int)var5, (int)var7, 1.0F, 1.0F, 1.0F, (float)var9, nullptr);
   }

    static void FadeIn(double var0) {
      setFadeInTimeMax((int)(var0 * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F)));
      setFadeInTime(getFadeInTimeMax());
      setFadingOut(false);
   }

    static void FadeOut(double var0) {
      setFadeInTimeMax((int)(var0 * 30.0 * (PerformanceSettings.getLockFPS() / 30.0F)));
      setFadeInTime(getFadeInTimeMax());
      setFadingOut(true);
   }

    static void CreateFBO(int var0, int var1) {
      if (Core.SafeMode) {
         useUIFBO = false;
      } else {
         if (useUIFBO && (UIFBO == nullptr || UIFBO.getTexture().getWidth() != var0 || UIFBO.getTexture().getHeight() != var1)) {
            if (UIFBO != nullptr) {
               RenderThread.invokeOnRenderContext(() -> UIFBO.destroy());
            }

            try {
               UIFBO = createTexture(var0, var1, false);
            } catch (Exception var3) {
               useUIFBO = false;
               var3.printStackTrace();
            }
         }
      }
   }

    static TextureFBO createTexture(float var0, float var1, bool var2) {
      if (var2) {
    Texture var5 = std::make_shared<Texture>((int)var0, (int)var1, 16);
    TextureFBO var4 = std::make_shared<TextureFBO>(var5);
         var4.destroy();
    return nullptr;
      } else {
    Texture var3 = std::make_shared<Texture>((int)var0, (int)var1, 16);
         return std::make_shared<TextureFBO>(var3);
      }
   }

    static void init() {
      showPausedMessage = true;
      getUI().clear();
      debugUI.clear();
      clock = nullptr;

      for (int var0 = 0; var0 < 4; var0++) {
         MoodleUI[var0] = nullptr;
      }

      setSpeedControls(std::make_unique<SpeedControls>());
      SpeedControls.instance = getSpeedControls();
      setbFadeBeforeUI(false);
      VisibleAllUI = true;

      for (int var2 = 0; var2 < 4; var2++) {
         playerFadeInfo[var2].setFadeBeforeUI(false);
         playerFadeInfo[var2].setFadeTime(0);
         playerFadeInfo[var2].setFadingOut(false);
      }

      setPicked(nullptr);
      setLastPicked(nullptr);
      RightDownObject = nullptr;
      if (IsoPlayer.getInstance() != nullptr) {
         if (!Core.GameMode == "LastStand") && !GameClient.bClient) {
            getUI().push_back(getSpeedControls());
         }

         if (!GameServer.bServer) {
            setToolTip(std::make_unique<ObjectTooltip>());
            if (Core.getInstance().getOptionClockSize() == 2) {
               setClock(std::make_shared<Clock>(Core.getInstance().getOffscreenWidth(0) - 166, 10));
            } else {
               setClock(std::make_shared<Clock>(Core.getInstance().getOffscreenWidth(0) - 91, 10));
            }

            if (!Core.GameMode == "LastStand")) {
               getUI().push_back(getClock());
            }

            getUI().push_back(getToolTip());
            setDebugConsole(std::make_shared<UIDebugConsole>(20, Core.getInstance().getScreenHeight() - 265));
            setServerToolbox(std::make_shared<UIServerToolbox>(100, 200));
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

            for (int var3 = 0; var3 < 4; var3++) {
    MoodlesUI var1 = std::make_shared<MoodlesUI>();
               setMoodleUI(var3, var1);
               var1.setVisible(true);
               getUI().push_back(var1);
            }

            getUI().push_back(getDebugConsole());
            getUI().push_back(getServerToolbox());
            setLastMouseTexture(getMouseArrow());
            resize();

            for (int var4 = 0; var4 < 4; var4++) {
    ActionProgressBar var5 = std::make_shared<ActionProgressBar>(0, 0);
               var5.setRenderThisPlayerOnly(var4);
               setProgressBar(var4, var5);
               getUI().push_back(var5);
               var5.setValue(1.0F);
               var5.setVisible(false);
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
    long var0 = System.currentTimeMillis();
            uiRenderIntervalMS = Math.min(var0 - uiRenderTimeMS, 1000L);
            uiRenderTimeMS = var0;
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

    int var2 = Mouse.getXA();
    int var3 = Mouse.getYA();
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

            for (int var4 = 0; var4 < IsoPlayer.numPlayers; var4++) {
               if (IsoPlayer.players[var4] != nullptr && playerFadeInfo[var4].isFadeBeforeUI()) {
                  playerFadeInfo[var4].render();
               }
            }

            for (int var9 = 0; var9 < getUI().size(); var9++) {
               if ((UI.get(var9).isIgnoreLossControl() || !TutorialManager.instance.StealControl) && !UI.get(var9).isFollowGameWorld()) {
                  try {
                     if (getUI().get(var9).isDefaultDraw()) {
                        getUI().get(var9).render();
                     }
                  } catch (Exception var8) {
                     Logger.getLogger(GameWindow.class.getName()).log(Level.SEVERE, nullptr, var8);
                  }
               }
            }

            if (getToolTip() != nullptr) {
               getToolTip().render();
            }

            if (isShowPausedMessage() && GameTime.isGamePaused() && (getModal() == nullptr || !Modal.isVisible()) && VisibleAllUI) {
    std::string var10 = Translator.getText("IGUI_GamePaused");
    int var5 = TextManager.instance.MeasureStringX(UIFont.Small, var10) + 32;
    int var6 = TextManager.instance.font.getLineHeight();
    int var7 = (int)Math.ceil(var6 * 1.5);
               SpriteRenderer.instance
                  .renderi(
                     nullptr,
                     Core.getInstance().getScreenWidth() / 2 - var5 / 2,
                     Core.getInstance().getScreenHeight() / 2 - var7 / 2,
                     var5,
                     var7,
                     0.0F,
                     0.0F,
                     0.0F,
                     0.75F,
                     nullptr
                  );
               TextManager.instance
                  .DrawStringCentre(Core.getInstance().getScreenWidth() / 2, Core.getInstance().getScreenHeight() / 2 - var6 / 2, var10, 1.0, 1.0, 1.0, 1.0);
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

            for (int var11 = 0; var11 < IsoPlayer.numPlayers; var11++) {
               if (IsoPlayer.players[var11] != nullptr && !playerFadeInfo[var11].isFadeBeforeUI()) {
                  playerFadeInfo[var11].render();
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

         for (int var0 = 0; var0 < 4; var0++) {
    int var1 = Core.getInstance().getScreenWidth();
    int var2 = Core.getInstance().getScreenHeight();
    uint8_t var3;
            if (!Clock.instance.isVisible()) {
               var3 = 24;
            } else {
               var3 = 64;
            }

            if (var0 == 0 && IsoPlayer.numPlayers > 1 || var0 == 2) {
               var1 /= 2;
            }

            MoodleUI[var0].setX(var1 - 50);
            if ((var0 == 0 || var0 == 1) && IsoPlayer.numPlayers > 1) {
               MoodleUI[var0].setY(var3);
            }

            if (var0 == 2 || var0 == 3) {
               MoodleUI[var0].setY(var2 / 2 + var3);
            }

            MoodleUI[var0].setVisible(VisibleAllUI && IsoPlayer.players[var0] != nullptr);
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

    static Vector2 getTileFromMouse(double var0, double var2, double var4) {
      PickedTile.x = IsoUtils.XToIso((float)(var0 - 0.0), (float)(var2 - 0.0), (float)var4);
      PickedTile.y = IsoUtils.YToIso((float)(var0 - 0.0), (float)(var2 - 0.0), (float)var4);
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

         for (int var0 = 0; var0 < IsoPlayer.numPlayers; var0++) {
            playerFadeInfo[var0].update();
         }

    long var13 = System.currentTimeMillis();
         if (var13 - uiUpdateTimeMS >= 100L) {
            doTick = true;
            uiUpdateIntervalMS = Math.min(var13 - uiUpdateTimeMS, 1000L);
            uiUpdateTimeMS = var13;
         } else {
            doTick = false;
         }

    bool var2 = false;
    bool var3 = false;
    bool var4 = false;
    int var5 = Mouse.getXA();
    int var6 = Mouse.getYA();
    int var7 = Mouse.getX();
    int var8 = Mouse.getY();
         tutorialStack.clear();

         for (int var9 = UI.size() - 1; var9 >= 0; var9--) {
    UIElement var10 = UI.get(var9);
            if (var10.getParent() != nullptr) {
               UI.remove(var9);
               throw std::make_unique<IllegalStateException>();
            }

            if (var10.isFollowGameWorld()) {
               tutorialStack.push_back(var10);
            }

            if (dynamic_cast<ObjectTooltip*>(var10) != nullptr) {
    UIElement var11 = UI.remove(var9);
               UI.push_back(var11);
            }
         }

         for (int var14 = 0; var14 < UI.size(); var14++) {
    UIElement var23 = UI.get(var14);
            if (var23.alwaysOnTop || toTop.contains(var23)) {
    UIElement var32 = UI.remove(var14);
               var14--;
               toAdd.push_back(var32);
            }
         }

         if (!toAdd.empty()) {
            UI.addAll(toAdd);
            toAdd.clear();
         }

         toTop.clear();

         for (int var15 = 0; var15 < UI.size(); var15++) {
    UIElement var24 = UI.get(var15);
            if (var24.alwaysBack) {
    UIElement var33 = UI.remove(var15);
               UI.push_back(0, var33);
            }
         }

         for (int var16 = 0; var16 < tutorialStack.size(); var16++) {
            UI.remove(tutorialStack.get(var16));
            UI.push_back(0, tutorialStack.get(var16));
         }

         if (Mouse.isLeftPressed()) {
            Core.UnfocusActiveTextEntryBox();

            for (int var17 = UI.size() - 1; var17 >= 0; var17--) {
    UIElement var25 = UI.get(var17);
               if ((getModal() == nullptr || getModal() == var25 || !getModal().isVisible())
                  && (var25.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
                  && var25.isVisible()) {
                  if ((
                        !(var5 >= var25.getX())
                           || !(var6 >= var25.getY())
                           || !(var5 < var25.getX() + var25.getWidth())
                           || !(var6 < var25.getY() + var25.getHeight())
                     )
                     && !var25.isCapture()) {
                     var25.onMouseDownOutside(var5 - var25.getX().intValue(), var6 - var25.getY().intValue());
                  } else if (var25.onMouseDown(var5 - var25.getX().intValue(), var6 - var25.getY().intValue())) {
                     var2 = true;
                     break;
                  }
               }
            }

            if (checkPicked() && !var2) {
               LuaEventManager.triggerEvent("OnObjectLeftMouseButtonDown", Picked.tile, BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
            }

            if (!var2) {
               LuaEventManager.triggerEvent("OnMouseDown", BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
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
    bool var18 = false;

            for (int var26 = UI.size() - 1; var26 >= 0; var26--) {
    UIElement var34 = UI.get(var26);
               if ((var34.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
                  && var34.isVisible()
                  && (getModal() == nullptr || getModal() == var34 || !getModal().isVisible())) {
                  if ((
                        !(var5 >= var34.getX())
                           || !(var6 >= var34.getY())
                           || !(var5 < var34.getX() + var34.getWidth())
                           || !(var6 < var34.getY() + var34.getHeight())
                     )
                     && !var34.isCapture()) {
                     var34.onMouseUpOutside(var5 - var34.getX().intValue(), var6 - var34.getY().intValue());
                  } else if (var34.onMouseUp(var5 - var34.getX().intValue(), var6 - var34.getY().intValue())) {
                     var18 = true;
                     break;
                  }
               }
            }

            if (!var18) {
               LuaEventManager.triggerEvent("OnMouseUp", BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
               if (checkPicked() && !var2) {
                  LuaEventManager.triggerEvent("OnObjectLeftMouseButtonUp", Picked.tile, BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
               }
            }
         }

         if (Mouse.isRightPressed()) {
            for (int var19 = UI.size() - 1; var19 >= 0; var19--) {
    UIElement var27 = UI.get(var19);
               if (var27.isVisible() && (getModal() == nullptr || getModal() == var27 || !getModal().isVisible())) {
                  if ((
                        !(var5 >= var27.getX())
                           || !(var6 >= var27.getY())
                           || !(var5 < var27.getX() + var27.getWidth())
                           || !(var6 < var27.getY() + var27.getHeight())
                     )
                     && !var27.isCapture()) {
                     var27.onRightMouseDownOutside(var5 - var27.getX().intValue(), var6 - var27.getY().intValue());
                  } else if (var27.onRightMouseDown(var5 - var27.getX().intValue(), var6 - var27.getY().intValue())) {
                     var3 = true;
                     break;
                  }
               }
            }

            if (!var3) {
               LuaEventManager.triggerEvent("OnRightMouseDown", BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
               if (checkPicked() && !var3) {
                  LuaEventManager.triggerEvent("OnObjectRightMouseButtonDown", Picked.tile, BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
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
    bool var20 = false;
    bool var28 = false;

            for (int var21 = UI.size() - 1; var21 >= 0; var21--) {
    UIElement var35 = UI.get(var21);
               if ((var35.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
                  && var35.isVisible()
                  && (getModal() == nullptr || getModal() == var35 || !getModal().isVisible())) {
                  if ((
                        !(var5 >= var35.getX())
                           || !(var6 >= var35.getY())
                           || !(var5 < var35.getX() + var35.getWidth())
                           || !(var6 < var35.getY() + var35.getHeight())
                     )
                     && !var35.isCapture()) {
                     var35.onRightMouseUpOutside(var5 - var35.getX().intValue(), var6 - var35.getY().intValue());
                  } else if (var35.onRightMouseUp(var5 - var35.getX().intValue(), var6 - var35.getY().intValue())) {
                     var28 = true;
                     break;
                  }
               }
            }

            if (!var28) {
               LuaEventManager.triggerEvent("OnRightMouseUp", BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
               if (checkPicked()) {
    bool var36 = true;
                  if (GameClient.bClient && Picked.tile.getSquare() != nullptr) {
    SafeHouse var12 = SafeHouse.isSafeHouse(Picked.tile.getSquare(), IsoPlayer.getInstance().getUsername(), true);
                     if (var12 != nullptr) {
                        var36 = false;
                     }
                  }

                  if (var36) {
                     LuaEventManager.triggerEvent("OnObjectRightMouseButtonUp", Picked.tile, BoxedStaticValues.toDouble(var5), BoxedStaticValues.toDouble(var6));
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
    bool var22 = false;
         if (wheel != lastwheel) {
    int var29 = wheel - lastwheel < 0 ? 1 : -1;

            for (int var37 = UI.size() - 1; var37 >= 0; var37--) {
    UIElement var39 = UI.get(var37);
               if ((var39.isIgnoreLossControl() || !TutorialManager.instance.StealControl)
                  && var39.isVisible()
                  && (var39.isPointOver(var5, var6) || var39.isCapture())
                  && var39.onMouseWheel(var29)) {
                  var22 = true;
                  break;
               }
            }

            if (!var22) {
               Core.getInstance().doZoomScroll(0, var29);
            }
         }

         if (getLastMouseX() != var5 || getLastMouseY() != var6) {
            for (int var30 = UI.size() - 1; var30 >= 0; var30--) {
    UIElement var38 = UI.get(var30);
               if ((var38.isIgnoreLossControl() || !TutorialManager.instance.StealControl) && var38.isVisible()) {
                  if ((
                        !(var5 >= var38.getX())
                           || !(var6 >= var38.getY())
                           || !(var5 < var38.getX() + var38.getWidth())
                           || !(var6 < var38.getY() + var38.getHeight())
                     )
                     && !var38.isCapture()) {
                     var38.onMouseMoveOutside(var5 - getLastMouseX(), var6 - getLastMouseY());
                  } else if (!var4 && var38.onMouseMove(var5 - getLastMouseX(), var6 - getLastMouseY())) {
                     var4 = true;
                  }
               }
            }
         }

         if (!var4 && IsoPlayer.players[0] != nullptr) {
            setPicked(IsoObjectPicker.Instance.ContextPick(var5, var6));
            if (IsoCamera.CamCharacter != nullptr) {
               setPickedTile(getTileFromMouse(var7, var8, (int)IsoPlayer.players[0].getZ()));
            }

            LuaEventManager.triggerEvent(
               "OnMouseMove",
               BoxedStaticValues.toDouble(var5),
               BoxedStaticValues.toDouble(var6),
               BoxedStaticValues.toDouble(var7),
               BoxedStaticValues.toDouble(var8)
            );
         } else {
            Mouse.UIBlockButtonDown(2);
         }

         setLastMouseX(var5);
         setLastMouseY(var6);

         for (int var31 = 0; var31 < UI.size(); var31++) {
            UI.get(var31).update();
         }

         updateTooltip(var5, var6);
         handleZoomKeys();
         IsoCamera.cameras[0].lastOffX = (int)IsoCamera.cameras[0].OffX;
         IsoCamera.cameras[0].lastOffY = (int)IsoCamera.cameras[0].OffY;
      }
   }

    static bool checkPicked() {
      return Picked != nullptr && Picked.tile != nullptr && Picked.tile.getObjectIndex() != -1;
   }

    static void handleZoomKeys() {
    bool var0 = true;
      if (Core.CurrentTextEntryBox != nullptr && Core.CurrentTextEntryBox.IsEditable && Core.CurrentTextEntryBox.DoingTextEntry) {
         var0 = false;
      }

      if (GameTime.isGamePaused()) {
         var0 = false;
      }

      if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Zoom in"))) {
         if (var0 && !KeyDownZoomIn) {
            Core.getInstance().doZoomScroll(0, -1);
         }

         KeyDownZoomIn = true;
      } else {
         KeyDownZoomIn = false;
      }

      if (GameKeyboard.isKeyDown(Core.getInstance().getKey("Zoom out"))) {
         if (var0 && !KeyDownZoomOut) {
            Core.getInstance().doZoomScroll(0, 1);
         }

         KeyDownZoomOut = true;
      } else {
         KeyDownZoomOut = false;
      }
   }

    static double getLastMouseX() {
      return BoxedStaticValues.toDouble(lastMouseX);
   }

    static void setLastMouseX(double var0) {
      lastMouseX = (int)var0;
   }

    static double getLastMouseY() {
      return BoxedStaticValues.toDouble(lastMouseY);
   }

    static void setLastMouseY(double var0) {
      lastMouseY = (int)var0;
   }

    static ClickObject getPicked() {
    return Picked;
   }

    static void setPicked(ClickObject var0) {
      Picked = var0;
   }

    static Clock getClock() {
    return clock;
   }

    static void setClock(Clock var0) {
      clock = var0;
   }

   public static std::vector<UIElement> getUI() {
    return UI;
   }

    static void setUI(std::vector<UIElement> var0) {
      PZArrayUtil.copy(UI, var0);
   }

    static ObjectTooltip getToolTip() {
    return toolTip;
   }

    static void setToolTip(ObjectTooltip var0) {
      toolTip = var0;
   }

    static Texture getMouseArrow() {
    return mouseArrow;
   }

    static void setMouseArrow(Texture var0) {
      mouseArrow = var0;
   }

    static Texture getMouseExamine() {
    return mouseExamine;
   }

    static void setMouseExamine(Texture var0) {
      mouseExamine = var0;
   }

    static Texture getMouseAttack() {
    return mouseAttack;
   }

    static void setMouseAttack(Texture var0) {
      mouseAttack = var0;
   }

    static Texture getMouseGrab() {
    return mouseGrab;
   }

    static void setMouseGrab(Texture var0) {
      mouseGrab = var0;
   }

    static SpeedControls getSpeedControls() {
    return speedControls;
   }

    static void setSpeedControls(SpeedControls var0) {
      speedControls = var0;
   }

    static UIDebugConsole getDebugConsole() {
    return DebugConsole;
   }

    static void setDebugConsole(UIDebugConsole var0) {
      DebugConsole = var0;
   }

    static UIServerToolbox getServerToolbox() {
    return ServerToolbox;
   }

    static void setServerToolbox(UIServerToolbox var0) {
      ServerToolbox = var0;
   }

    static MoodlesUI getMoodleUI(double var0) {
      return MoodleUI[(int)var0];
   }

    static void setMoodleUI(double var0, MoodlesUI var2) {
      MoodleUI[(int)var0] = var2;
   }

    static bool isbFadeBeforeUI() {
    return bFadeBeforeUI;
   }

    static void setbFadeBeforeUI(bool var0) {
      bFadeBeforeUI = var0;
   }

    static ActionProgressBar getProgressBar(double var0) {
      return ProgressBar[(int)var0];
   }

    static void setProgressBar(double var0, ActionProgressBar var2) {
      ProgressBar[(int)var0] = var2;
   }

    static double getFadeAlpha() {
      return BoxedStaticValues.toDouble(FadeAlpha);
   }

    static void setFadeAlpha(double var0) {
      FadeAlpha = (float)var0;
   }

    static double getFadeInTimeMax() {
      return BoxedStaticValues.toDouble(FadeInTimeMax);
   }

    static void setFadeInTimeMax(double var0) {
      FadeInTimeMax = (int)var0;
   }

    static double getFadeInTime() {
      return BoxedStaticValues.toDouble(FadeInTime);
   }

    static void setFadeInTime(double var0) {
      FadeInTime = Math.max((int)var0, 0);
   }

    static bool isFadingOut() {
      return FadingOut ? bool.TRUE : bool.FALSE;
   }

    static void setFadingOut(bool var0) {
      FadingOut = var0;
   }

    static Texture getLastMouseTexture() {
    return lastMouseTexture;
   }

    static void setLastMouseTexture(Texture var0) {
      lastMouseTexture = var0;
   }

    static IsoObject getLastPicked() {
    return LastPicked;
   }

    static void setLastPicked(IsoObject var0) {
      LastPicked = var0;
   }

   public static std::vector<std::string> getDoneTutorials() {
    return DoneTutorials;
   }

    static void setDoneTutorials(std::vector<std::string> var0) {
      PZArrayUtil.copy(DoneTutorials, var0);
   }

    static float getLastOffX() {
    return lastOffX;
   }

    static void setLastOffX(float var0) {
      lastOffX = var0;
   }

    static float getLastOffY() {
    return lastOffY;
   }

    static void setLastOffY(float var0) {
      lastOffY = var0;
   }

    static ModalDialog getModal() {
    return Modal;
   }

    static void setModal(ModalDialog var0) {
      Modal = var0;
   }

    static Texture getBlack() {
    return black;
   }

    static void setBlack(Texture var0) {
      black = var0;
   }

    static float getLastAlpha() {
    return lastAlpha;
   }

    static void setLastAlpha(float var0) {
      lastAlpha = var0;
   }

    static Vector2 getPickedTileLocal() {
    return PickedTileLocal;
   }

    static void setPickedTileLocal(Vector2 var0) {
      PickedTileLocal.set(var0);
   }

    static Vector2 getPickedTile() {
    return PickedTile;
   }

    static void setPickedTile(Vector2 var0) {
      PickedTile.set(var0);
   }

    static IsoObject getRightDownObject() {
    return RightDownObject;
   }

    static void setRightDownObject(IsoObject var0) {
      RightDownObject = var0;
   }

    static void pushToTop(UIElement var0) {
      toTop.push_back(var0);
   }

    static bool isShowPausedMessage() {
    return showPausedMessage;
   }

    static void setShowPausedMessage(bool var0) {
      showPausedMessage = var0;
   }

    static void setShowLuaDebuggerOnError(bool var0) {
      bShowLuaDebuggerOnError = var0;
   }

    static bool isShowLuaDebuggerOnError() {
    return bShowLuaDebuggerOnError;
   }

    static void debugBreakpoint(const std::string& var0, long var1) {
      if (bShowLuaDebuggerOnError) {
         if (Core.CurrentTextEntryBox != nullptr) {
            Core.CurrentTextEntryBox.DoingTextEntry = false;
            Core.CurrentTextEntryBox = nullptr;
         }

         if (!GameServer.bServer) {
            if (!(GameWindow.states.dynamic_cast<GameLoadingState*>(current) != nullptr)) {
               previousThread = defaultthread;
               defaultthread = LuaManager.debugthread;
    int var3 = Core.getInstance().frameStage;
               if (var3 != 0) {
                  if (var3 <= 1) {
                     Core.getInstance().EndFrame(0);
                  }

                  if (var3 <= 2) {
                     Core.getInstance().StartFrameUI();
                  }

                  if (var3 <= 3) {
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
    std::vector var4 = new std::vector();
    bool var5 = bSuspend;
               var4.addAll(UI);
               UI.clear();
               bSuspend = false;
               setShowPausedMessage(false);
    bool var6 = false;
               boolean[] var7 = new boolean[11];

               for (int var8 = 0; var8 < 11; var8++) {
                  var7[var8] = true;
               }

               if (debugUI.size() == 0) {
                  LuaManager.debugcaller.pcall(LuaManager.debugthread, LuaManager.env.rawget("DoLuaDebugger"), new Object[]{var0, var1});
               } else {
                  UI.addAll(debugUI);
                  LuaManager.debugcaller.pcall(LuaManager.debugthread, LuaManager.env.rawget("DoLuaDebuggerOnBreak"), new Object[]{var0, var1});
               }

               Mouse.setCursorVisible(true);
               sync.begin();

               while (!var6) {
                  if (RenderThread.isCloseRequested()) {
                     System.exit(0);
                  }

                  if (!GameWindow.bLuaDebuggerKeyDown && GameKeyboard.isKeyDown(Core.getInstance().getKey("Toggle Lua Debugger"))) {
                     GameWindow.bLuaDebuggerKeyDown = true;
                     executeGame(var4, var5, var3);
                     return;
                  }

    std::string var11 = luaDebuggerAction;
                  luaDebuggerAction = nullptr;
                  if ("StepInto".equalsIgnoreCase(var11)) {
                     LuaManager.thread.bStep = true;
                     LuaManager.thread.bStepInto = true;
                     executeGame(var4, var5, var3);
                     return;
                  }

                  if ("StepOver".equalsIgnoreCase(var11)) {
                     LuaManager.thread.bStep = true;
                     LuaManager.thread.bStepInto = false;
                     LuaManager.thread.lastCallFrame = LuaManager.thread.getCurrentCoroutine().getCallframeTop();
                     executeGame(var4, var5, var3);
                     return;
                  }

                  if ("Resume".equalsIgnoreCase(var11)) {
                     executeGame(var4, var5, var3);
                     return;
                  }

                  sync.startFrame();

                  for (int var9 = 0; var9 < 11; var9++) {
    bool var10 = GameKeyboard.isKeyDown(59 + var9);
                     if (var10) {
                        if (!var7[var9]) {
                           if (var9 + 1 == 5) {
                              LuaManager.thread.bStep = true;
                              LuaManager.thread.bStepInto = true;
                              executeGame(var4, var5, var3);
                              return;
                           }

                           if (var9 + 1 == 6) {
                              LuaManager.thread.bStep = true;
                              LuaManager.thread.bStepInto = false;
                              LuaManager.thread.lastCallFrame = LuaManager.thread.getCurrentCoroutine().getCallframeTop();
                              executeGame(var4, var5, var3);
                              return;
                           }
                        }

                        var7[var9] = true;
                     } else {
                        var7[var9] = false;
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

    static void executeGame(std::vector<UIElement> var0, bool var1, int var2) {
      debugUI.clear();
      debugUI.addAll(UI);
      UI.clear();
      UI.addAll(var0);
      bSuspend = var1;
      setShowPausedMessage(true);
      if (!LuaManager.thread.bStep && var2 != 0) {
         if (var2 == 1) {
            Core.getInstance().StartFrame(0, true);
         }

         if (var2 == 2) {
            Core.getInstance().StartFrame(0, true);
            Core.getInstance().EndFrame(0);
         }

         if (var2 == 3) {
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

    static bool isDoubleClick(double var0, double var2, double var4, double var6, double var8) {
      if (Math.abs(var4 - var0) > getDoubleClickDist()) {
    return false;
      } else if (Math.abs(var6 - var2) > getDoubleClickDist()) {
    return false;
      } else {
         return System.currentTimeMillis() - var8 > getDoubleClickInterval() ? bool.FALSE : bool.TRUE;
      }
   }

    static void updateTooltip(double var0, double var2) {
    UIElement var4 = nullptr;

      for (int var5 = getUI().size() - 1; var5 >= 0; var5--) {
    UIElement var6 = getUI().get(var5);
         if (var6 != toolTip
            && var6.isVisible()
            && var0 >= var6.getX()
            && var2 >= var6.getY()
            && var0 < var6.getX() + var6.getWidth()
            && var2 < var6.getY() + var6.getHeight()
            && (var6.maxDrawHeight == -1 || var2 < var6.getY() + var6.maxDrawHeight)) {
            var4 = var6;
            break;
         }
      }

    IsoObject var7 = nullptr;
      if (var4 == nullptr && getPicked() != nullptr) {
         var7 = getPicked().tile;
         if (var7 != getLastPicked() && toolTip != nullptr) {
            toolTip.targetAlpha = 0.0F;
            if (var7.haveSpecialTooltip()) {
               if (getToolTip().Object != var7) {
                  getToolTip().show(var7, (int)var0 + 8, (int)var2 + 16);
                  if (toolTip.isVisible()) {
                     toolTip.showDelay = 0;
                  }
               } else {
                  toolTip.targetAlpha = 1.0F;
               }
            }
         }
      }

      setLastPicked(var7);
      if (toolTip != nullptr && (var7 == nullptr || toolTip.alpha <= 0.0F && toolTip.targetAlpha <= 0.0F)) {
         toolTip.hide();
      }
   }

    static void setPlayerInventory(int var0, UIElement var1, UIElement var2) {
      if (var0 == 0) {
         playerInventoryUI = var1;
         playerLootUI = var2;
      }
   }

    static void setPlayerInventoryTooltip(int var0, UIElement var1, UIElement var2) {
      if (var0 == 0) {
         playerInventoryTooltip = var1;
         playerLootTooltip = var2;
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

    static void setVisibleAllUI(bool var0) {
      VisibleAllUI = var0;
   }

    static void setFadeBeforeUI(int var0, bool var1) {
      playerFadeInfo[var0].setFadeBeforeUI(var1);
   }

    static float getFadeAlpha(double var0) {
      return playerFadeInfo[(int)var0].getFadeAlpha();
   }

    static void setFadeTime(double var0, double var2) {
      playerFadeInfo[(int)var0].setFadeTime((int)var2);
   }

    static void FadeIn(double var0, double var2) {
      playerFadeInfo[(int)var0].FadeIn((int)var2);
   }

    static void FadeOut(double var0, double var2) {
      playerFadeInfo[(int)var0].FadeOut((int)var2);
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

    static bool onKeyPress(int var0) {
      for (int var1 = UI.size() - 1; var1 >= 0; var1--) {
    UIElement var2 = UI.get(var1);
         if (var2.isVisible() && var2.isWantKeyEvents()) {
            var2.onKeyPress(var0);
            if (var2.isKeyConsumed(var0)) {
    return true;
            }
         }
      }

    return false;
   }

    static bool onKeyRepeat(int var0) {
      for (int var1 = UI.size() - 1; var1 >= 0; var1--) {
    UIElement var2 = UI.get(var1);
         if (var2.isVisible() && var2.isWantKeyEvents()) {
            var2.onKeyRepeat(var0);
            if (var2.isKeyConsumed(var0)) {
    return true;
            }
         }
      }

    return false;
   }

    static bool onKeyRelease(int var0) {
      for (int var1 = UI.size() - 1; var1 >= 0; var1--) {
    UIElement var2 = UI.get(var1);
         if (var2.isVisible() && var2.isWantKeyEvents()) {
            var2.onKeyRelease(var0);
            if (var2.isKeyConsumed(var0)) {
    return true;
            }
         }
      }

    return false;
   }

    static bool isForceCursorVisible() {
      for (int var0 = UI.size() - 1; var0 >= 0; var0--) {
    UIElement var1 = UI.get(var0);
         if (var1.isVisible() && (var1.isForceCursorVisible() || var1.isMouseOver())) {
    return true;
         }
      }

    return false;
   }

   static {
      for (int var0 = 0; var0 < 4; var0++) {
         playerFadeInfo[var0] = std::make_shared<FadeInfo>(var0);
      }
   }
}
} // namespace ui
} // namespace zombie
