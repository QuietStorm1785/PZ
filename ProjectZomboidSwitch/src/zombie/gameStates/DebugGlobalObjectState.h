#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
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
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"

namespace zombie {
namespace gameStates {


class DebugGlobalObjectState : public GameState {
public:
    static DebugGlobalObjectState instance;
    LuaEnvironment m_luaEnv;
    bool bExit = false;
   private const std::vector<UIElement> m_gameUI = std::make_unique<std::vector<>>();
   private const std::vector<UIElement> m_selfUI = std::make_unique<std::vector<>>();
    bool m_bSuspendUI;
    KahluaTable m_table = nullptr;
    int m_playerIndex = 0;
    int m_z = 0;
    int gridX = -1;
    int gridY = -1;
    UIFont FONT = UIFont.DebugConsole;

    public DebugGlobalObjectState() {
      instance = this;
   }

    void enter() {
      instance = this;
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
    IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         this.m_z = var1 == nullptr ? 0 : (int)var1.z;
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("DebugGlobalObjectState_InitUI"), this);
      } else {
         UIManager.UI.addAll(this.m_selfUI);
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_table.rawget("showUI"), this.m_table);
      }

      this.bExit = false;
   }

    void yield() {
      this.restoreGameUI();
   }

    void reenter() {
      this.saveGameUI();
   }

    void exit() {
      this.restoreGameUI();

      for (int var1 = 0; var1 < IsoCamera.cameras.length; var1++) {
         IsoCamera.cameras[var1].DeferedX = IsoCamera.cameras[var1].DeferedY = 0.0F;
      }
   }

    void render() {
      IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
      IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
    bool var1 = true;

      for (int var2 = 0; var2 < IsoPlayer.numPlayers; var2++) {
         if (var2 != this.m_playerIndex && IsoPlayer.players[var2] != nullptr) {
            Core.getInstance().StartFrame(var2, var1);
            Core.getInstance().EndFrame(var2);
            var1 = false;
         }
      }

      Core.getInstance().StartFrame(this.m_playerIndex, var1);
      this.renderScene();
      Core.getInstance().EndFrame(this.m_playerIndex);
      Core.getInstance().RenderOffScreenBuffer();

      for (int var3 = 0; var3 < IsoPlayer.numPlayers; var3++) {
         TextDrawObject.NoRender(var3);
         ChatElement.NoRender(var3);
      }

      if (Core.getInstance().StartFrameUI()) {
         this.renderUI();
      }

      Core.getInstance().EndFrameUI();
   }

    StateAction update() {
      if (!this.bExit && !GameKeyboard.isKeyPressed(60)) {
    IsoChunkMap var1 = IsoWorld.instance.CurrentCell.ChunkMap[this.m_playerIndex];
         var1.ProcessChunkPos(IsoPlayer.players[this.m_playerIndex]);
         var1.update();
         return this.updateScene();
      } else {
         return StateAction.Continue;
      }
   }

    void renderScene() {
      IsoCamera.frameState.set(this.m_playerIndex);
      SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
      SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
      SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
      IsoSprite.globalOffsetX = -1.0F;
      IsoWorld.instance.CurrentCell.render();
    IsoChunkMap var1 = IsoWorld.instance.CurrentCell.ChunkMap[this.m_playerIndex];
    int var2 = var1.getWorldXMin();
    int var3 = var1.getWorldYMin();
    int var4 = var2 + IsoChunkMap.ChunkGridWidth;
    int var5 = var3 + IsoChunkMap.ChunkGridWidth;
    int var6 = CGlobalObjects.getSystemCount();

      for (int var7 = 0; var7 < var6; var7++) {
    CGlobalObjectSystem var8 = CGlobalObjects.getSystemByIndex(var7);

         for (int var9 = var3; var9 < var5; var9++) {
            for (int var10 = var2; var10 < var4; var10++) {
    std::vector var11 = var8.getObjectsInChunk(var10, var9);

               for (int var12 = 0; var12 < var11.size(); var12++) {
    GlobalObject var13 = (GlobalObject)var11.get(var12);
    float var14 = 1.0F;
    float var15 = 1.0F;
    float var16 = 1.0F;
                  if (var13.getZ() != this.m_z) {
                     var16 = 0.5F;
                     var15 = 0.5F;
                     var14 = 0.5F;
                  }

                  this.DrawIsoRect(var13.getX(), var13.getY(), var13.getZ(), 1.0F, 1.0F, var14, var15, var16, 1.0F, 1);
               }

               var8.finishedWithList(var11);
            }
         }
      }

      LineDrawer.render();
      LineDrawer.clear();
   }

    void renderUI() {
      UIManager.render();
   }

    void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

    StateAction updateScene() {
      IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
      IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
      UIManager.setPicked(IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA()));
    IsoObject var1 = UIManager.getPicked() == nullptr ? nullptr : UIManager.getPicked().tile;
      UIManager.setLastPicked(var1);
      IsoCamera.update();
      this.updateCursor();
      return StateAction.Remain;
   }

    void updateCursor() {
    int var1 = this.m_playerIndex;
    float var2 = Mouse.getXA();
    float var3 = Mouse.getYA();
      var2 -= IsoCamera.getScreenLeft(var1);
      var3 -= IsoCamera.getScreenTop(var1);
      var2 *= Core.getInstance().getZoom(var1);
      var3 *= Core.getInstance().getZoom(var1);
    int var4 = this.m_z;
      this.gridX = (int)IsoUtils.XToIso(var2, var3, var4);
      this.gridY = (int)IsoUtils.YToIso(var2, var3, var4);
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

    void DrawIsoLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, float var10, int var11) {
    float var12 = IsoUtils.XToScreenExact(var1, var2, var3, 0);
    float var13 = IsoUtils.YToScreenExact(var1, var2, var3, 0);
    float var14 = IsoUtils.XToScreenExact(var4, var5, var6, 0);
    float var15 = IsoUtils.YToScreenExact(var4, var5, var6, 0);
      LineDrawer.drawLine(var12, var13, var14, var15, var7, var8, var9, var10, var11);
   }

    void DrawIsoRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, float var9, int var10) {
      this.DrawIsoLine(var1, var2, var3, var1 + var4, var2, var3, var6, var7, var8, var9, var10);
      this.DrawIsoLine(var1 + var4, var2, var3, var1 + var4, var2 + var5, var3, var6, var7, var8, var9, var10);
      this.DrawIsoLine(var1 + var4, var2 + var5, var3, var1, var2 + var5, var3, var6, var7, var8, var9, var10);
      this.DrawIsoLine(var1, var2 + var5, var3, var1, var2, var3, var6, var7, var8, var9, var10);
   }

    void* fromLua0(const std::string& var1) {
      switch (var1) {
         case "exit":
            this.bExit = true;
    return nullptr;
         case "getCameraDragX":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedX);
         case "getCameraDragY":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedY);
         case "getPlayerIndex":
            return BoxedStaticValues.toDouble(this.m_playerIndex);
         case "getZ":
            return BoxedStaticValues.toDouble(this.m_z);
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\"", var1));
      }
   }

    void* fromLua1(const std::string& var1, void* var2) {
      switch (var1) {
         case "setPlayerIndex":
            this.m_playerIndex = PZMath.clamp(((double)var2).intValue(), 0, 3);
    return nullptr;
         case "setZ":
            this.m_z = PZMath.clamp(((double)var2).intValue(), 0, 7);
    return nullptr;
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\"", var1, var2));
      }
   }

    void* fromLua2(const std::string& var1, void* var2, void* var3) {
    uint8_t var5 = -1;
      switch (var1.hashCode()) {
         case -1879300743:
            if (var1 == "dragCamera")) {
               var5 = 0;
            }
         default:
            switch (var5) {
               case 0:
    float var6 = ((double)var2).floatValue();
    float var7 = ((double)var3).floatValue();
                  IsoCamera.cameras[this.m_playerIndex].DeferedX = -var6;
                  IsoCamera.cameras[this.m_playerIndex].DeferedY = -var7;
    return nullptr;
               default:
                  throw IllegalArgumentException(std::string.format("unhandled \"%s\" \"%s\" \\\"%s\\\"", var1, var2, var3));
            }
      }
   }
}
} // namespace gameStates
} // namespace zombie
