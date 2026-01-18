#pragma once
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/globalObjects/CGlobalObjectSystem.h"
#include "zombie/globalObjects/CGlobalObjects.h"
#include "zombie/globalObjects/GlobalObject.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/vehicles/EditVehicleState.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class DebugGlobalObjectState : public GameState {
public:
  static DebugGlobalObjectState instance;
private
  EditVehicleState.LuaEnvironment m_luaEnv;
  bool bExit = false;
private
  final ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
private
  final ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
  bool m_bSuspendUI;
  KahluaTable m_table = null;
  int m_playerIndex = 0;
  int m_z = 0;
  int gridX = -1;
  int gridY = -1;
  UIFont FONT = UIFont.DebugConsole;

public
  DebugGlobalObjectState() { instance = this; }

  void enter() {
    instance = this;
    if (this.m_luaEnv == nullptr) {
      this.m_luaEnv = new EditVehicleState.LuaEnvironment(
          LuaManager.platform, LuaManager.converterManager, LuaManager.env);
    }

    this.saveGameUI();
    if (this.m_selfUI.size() == 0) {
      IsoPlayer player = IsoPlayer.players[this.m_playerIndex];
      this.m_z = player == nullptr ? 0 : (int)player.z;
      this.m_luaEnv.caller.pcall(
          this.m_luaEnv.thread,
          this.m_luaEnv.env.rawget("DebugGlobalObjectState_InitUI"), this);
    } else {
      UIManager.UI.addAll(this.m_selfUI);
      this.m_luaEnv.caller.pcall(this.m_luaEnv.thread,
                                 this.m_table.rawget("showUI"), this.m_table);
    }

    this.bExit = false;
  }

  void yield() { this.restoreGameUI(); }

  void reenter() { this.saveGameUI(); }

  void exit() {
    this.restoreGameUI();

    for (int int0 = 0; int0 < IsoCamera.cameras.length; int0++) {
      IsoCamera.cameras[int0].DeferedX = IsoCamera.cameras[int0].DeferedY =
          0.0F;
    }
  }

  void render() {
    IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
    IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
    bool boolean0 = true;

    for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
      if (int0 != this.m_playerIndex && IsoPlayer.players[int0] != nullptr) {
        Core.getInstance().StartFrame(int0, boolean0);
        Core.getInstance().EndFrame(int0);
        boolean0 = false;
      }
    }

    Core.getInstance().StartFrame(this.m_playerIndex, boolean0);
    this.renderScene();
    Core.getInstance().EndFrame(this.m_playerIndex);
    Core.getInstance().RenderOffScreenBuffer();

    for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
      TextDrawObject.NoRender(int1);
      ChatElement.NoRender(int1);
    }

    if (Core.getInstance().StartFrameUI()) {
      this.renderUI();
    }

    Core.getInstance().EndFrameUI();
  }

public
  GameStateMachine.StateAction update() {
    if (!this.bExit && !GameKeyboard.isKeyPressed(60)) {
      IsoChunkMap chunkMap =
          IsoWorld.instance.CurrentCell.ChunkMap[this.m_playerIndex];
      chunkMap.ProcessChunkPos(IsoPlayer.players[this.m_playerIndex]);
      chunkMap.update();
      return this.updateScene();
    } else {
      return GameStateMachine.StateAction.Continue;
    }
  }

  void renderScene() {
    IsoCamera.frameState.set(this.m_playerIndex);
    SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
    SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
    SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
    IsoSprite.globalOffsetX = -1.0F;
    IsoWorld.instance.CurrentCell.render();
    IsoChunkMap chunkMap =
        IsoWorld.instance.CurrentCell.ChunkMap[this.m_playerIndex];
    int int0 = chunkMap.getWorldXMin();
    int int1 = chunkMap.getWorldYMin();
    int int2 = int0 + IsoChunkMap.ChunkGridWidth;
    int int3 = int1 + IsoChunkMap.ChunkGridWidth;
    int int4 = CGlobalObjects.getSystemCount();

    for (int int5 = 0; int5 < int4; int5++) {
      CGlobalObjectSystem cGlobalObjectSystem =
          CGlobalObjects.getSystemByIndex(int5);

      for (int int6 = int1; int6 < int3; int6++) {
        for (int int7 = int0; int7 < int2; int7++) {
          std::vector arrayList =
              cGlobalObjectSystem.getObjectsInChunk(int7, int6);

          for (int int8 = 0; int8 < arrayList.size(); int8++) {
            GlobalObject globalObject = (GlobalObject)arrayList.get(int8);
            float float0 = 1.0F;
            float float1 = 1.0F;
            float float2 = 1.0F;
            if (globalObject.getZ() != this.m_z) {
              float2 = 0.5F;
              float1 = 0.5F;
              float0 = 0.5F;
            }

            this.DrawIsoRect(globalObject.getX(), globalObject.getY(),
                             globalObject.getZ(), 1.0F, 1.0F, float0, float1,
                             float2, 1.0F, 1);
          }

          cGlobalObjectSystem.finishedWithList(arrayList);
        }
      }
    }

    LineDrawer.render();
    LineDrawer.clear();
  }

  void renderUI() { UIManager.render(); }

  void setTable(KahluaTable table) { this.m_table = table; }

public
  GameStateMachine.StateAction updateScene() {
    IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
    IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
    UIManager.setPicked(
        IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA()));
    IsoObject object =
        UIManager.getPicked() == null ? null : UIManager.getPicked().tile;
    UIManager.setLastPicked(object);
    IsoCamera.update();
    this.updateCursor();
    return GameStateMachine.StateAction.Remain;
  }

  void updateCursor() {
    int int0 = this.m_playerIndex;
    float float0 = Mouse.getXA();
    float float1 = Mouse.getYA();
    float0 -= IsoCamera.getScreenLeft(int0);
    float1 -= IsoCamera.getScreenTop(int0);
    float0 *= Core.getInstance().getZoom(int0);
    float1 *= Core.getInstance().getZoom(int0);
    int int1 = this.m_z;
    this.gridX = (int)IsoUtils.XToIso(float0, float1, int1);
    this.gridY = (int)IsoUtils.YToIso(float0, float1, int1);
  }

  void saveGameUI() {
    this.m_gameUI.clear();
    this.m_gameUI.addAll(UIManager.UI);
    UIManager.UI.clear();
    this.m_bSuspendUI = UIManager.bSuspend;
    UIManager.bSuspend = false;
    UIManager.setShowPausedMessage(false);
    UIManager.defaultthread = this.m_luaEnv.thread;
  }

  void restoreGameUI() {
    this.m_selfUI.clear();
    this.m_selfUI.addAll(UIManager.UI);
    UIManager.UI.clear();
    UIManager.UI.addAll(this.m_gameUI);
    UIManager.bSuspend = this.m_bSuspendUI;
    UIManager.setShowPausedMessage(true);
    UIManager.defaultthread = LuaManager.thread;
  }

private
  void DrawIsoLine(float float1, float float2, float float3, float float6,
                   float float7, float float8, float float10, float float11,
                   float float12, float float13, int int0) {
    float float0 = IsoUtils.XToScreenExact(float1, float2, float3, 0);
    float float4 = IsoUtils.YToScreenExact(float1, float2, float3, 0);
    float float5 = IsoUtils.XToScreenExact(float6, float7, float8, 0);
    float float9 = IsoUtils.YToScreenExact(float6, float7, float8, 0);
    LineDrawer.drawLine(float0, float4, float5, float9, float10, float11,
                        float12, float13, int0);
  }

private
  void DrawIsoRect(float float0, float float1, float float2, float float7,
                   float float8, float float3, float float4, float float5,
                   float float6, int int0) {
    this.DrawIsoLine(float0, float1, float2, float0 + float7, float1, float2,
                     float3, float4, float5, float6, int0);
    this.DrawIsoLine(float0 + float7, float1, float2, float0 + float7,
                     float1 + float8, float2, float3, float4, float5, float6,
                     int0);
    this.DrawIsoLine(float0 + float7, float1 + float8, float2, float0,
                     float1 + float8, float2, float3, float4, float5, float6,
                     int0);
    this.DrawIsoLine(float0, float1 + float8, float2, float0, float1, float2,
                     float3, float4, float5, float6, int0);
  }

  void *fromLua0(const std::string &func) {
    switch (func) {
    case "exit":
      this.bExit = true;
      return null;
    case "getCameraDragX":
      return BoxedStaticValues.toDouble(
          -IsoCamera.cameras[this.m_playerIndex].DeferedX);
    case "getCameraDragY":
      return BoxedStaticValues.toDouble(
          -IsoCamera.cameras[this.m_playerIndex].DeferedY);
    case "getPlayerIndex":
      return BoxedStaticValues.toDouble(this.m_playerIndex);
    case "getZ":
      return BoxedStaticValues.toDouble(this.m_z);
    default:
      throw new IllegalArgumentException(
          String.format("unhandled \"%s\"", func));
    }
  }

  void *fromLua1(const std::string &func, void *arg0) {
    switch (func) {
    case "setPlayerIndex":
      this.m_playerIndex = PZMath.clamp(((Double)arg0).intValue(), 0, 3);
      return null;
    case "setZ":
      this.m_z = PZMath.clamp(((Double)arg0).intValue(), 0, 7);
      return null;
    default:
      throw new IllegalArgumentException(
          String.format("unhandled \"%s\" \"%s\"", func, arg0));
    }
  }

  void *fromLua2(const std::string &func, void *arg0, void *arg1) {
    uint8_t byte0 = -1;
    switch (func.hashCode()) {
    case -1879300743:
      if (func == "dragCamera")) {
                    byte0 = 0;
                }
    default:
      switch (byte0) {
      case 0:
        float float0 = ((Double)arg0).floatValue();
        float float1 = ((Double)arg1).floatValue();
        IsoCamera.cameras[this.m_playerIndex].DeferedX = -float0;
        IsoCamera.cameras[this.m_playerIndex].DeferedY = -float1;
        return null;
      default:
        throw new IllegalArgumentException(String.format(
            "unhandled \"%s\" \"%s\" \\\"%s\\\"", func, arg0, arg1));
      }
    }
  }
}
} // namespace gameStates
} // namespace zombie
