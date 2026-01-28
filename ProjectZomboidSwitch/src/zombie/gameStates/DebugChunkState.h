#pragma once
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <glm/vec2.hpp>
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/FliesSound.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/chat/ChatElement.h"
#include "zombie/config/BooleanConfigOption.h"
#include "zombie/config/ConfigFile.h"
#include "zombie/config/ConfigOption.h"
#include "zombie/core/BoxedStaticValues.h"
#include "zombie/core/Core.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/math/PZMath.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionData/Square.h"
#include "zombie/gameStates/DebugChunkState/BooleanDebugOption.h"
#include "zombie/gameStates/GameStateMachine/StateAction.h"
#include "zombie/input/InputGlobals.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMetaGrid/VehicleZone.h"
#include "zombie/iso/IsoMetaGrid/Zone.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil/TestResults.h"
#include "zombie/iso/NearestWalls.h"
#include "zombie/iso/ParticlesFire.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/network/GameClient.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/RandomizedVehicleStoryBase.h"
#include "zombie/randomizedWorld/randomizedVehicleStory/VehicleStorySpawner.h"
#include "zombie/ui/TextDrawObject.h"
#include "zombie/ui/TextManager.h"
#include "zombie/ui/UIElement.h"
#include "zombie/ui/UIFont.h"
#include "zombie/ui/UIManager.h"
#include "zombie/util/Type.h"
#include "zombie/vehicles/ClipperOffset.h"
#include "zombie/vehicles/EditVehicleState/LuaEnvironment.h"
#include "zombie/vehicles/PolygonalMap2/LiangBarsky.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {


class DebugChunkState : public GameState {
public:
    static DebugChunkState instance;
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
    std::string m_vehicleStory = "Basic Car Crash";
    static bool keyQpressed = false;
    static ClipperOffset m_clipperOffset = nullptr;
    static ByteBuffer m_clipperBuffer;
    static const int VERSION = 1;
   private const std::vector<ConfigOption> options = std::make_unique<std::vector<>>();
    BooleanDebugOption BuildingRect = std::make_shared<BooleanDebugOption>(this, "BuildingRect", true);
    BooleanDebugOption ChunkGrid = std::make_shared<BooleanDebugOption>(this, "ChunkGrid", true);
    BooleanDebugOption ClosestRoomSquare = std::make_shared<BooleanDebugOption>(this, "ClosestRoomSquare", true);
    BooleanDebugOption EmptySquares = std::make_shared<BooleanDebugOption>(this, "EmptySquares", true);
    BooleanDebugOption FlyBuzzEmitters = std::make_shared<BooleanDebugOption>(this, "FlyBuzzEmitters", true);
    BooleanDebugOption LightSquares = std::make_shared<BooleanDebugOption>(this, "LightSquares", true);
    BooleanDebugOption LineClearCollide = std::make_shared<BooleanDebugOption>(this, "LineClearCollide", true);
    BooleanDebugOption NearestWallsOpt = std::make_shared<BooleanDebugOption>(this, "NearestWalls", true);
    BooleanDebugOption ObjectPicker = std::make_shared<BooleanDebugOption>(this, "ObjectPicker", true);
    BooleanDebugOption RoomLightRects = std::make_shared<BooleanDebugOption>(this, "RoomLightRects", true);
    BooleanDebugOption VehicleStory = std::make_shared<BooleanDebugOption>(this, "VehicleStory", true);
    BooleanDebugOption RandomSquareInZone = std::make_shared<BooleanDebugOption>(this, "RandomSquareInZone", true);
    BooleanDebugOption ZoneRect = std::make_shared<BooleanDebugOption>(this, "ZoneRect", true);

    public DebugChunkState() {
      instance = this;
   }

    void enter() {
      instance = this;
      this.load();
      if (this.m_luaEnv == nullptr) {
         this.m_luaEnv = std::make_shared<LuaEnvironment>(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
      }

      this.saveGameUI();
      if (this.m_selfUI.size() == 0) {
    IsoPlayer var1 = IsoPlayer.players[this.m_playerIndex];
         this.m_z = var1 == nullptr ? 0 : (int)var1.z;
         this.m_luaEnv.caller.pcall(this.m_luaEnv.thread, this.m_luaEnv.env.rawget("DebugChunkState_InitUI"), this);
         if (this.m_table != nullptr && this.m_table.getMetatable() != nullptr) {
            this.m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", bool.FALSE);
         }
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
      this.save();
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
      return !this.bExit && !g_keyboard.isKeyPressed(SDL_SCANCODE_F2) ? this.updateScene() : StateAction.Continue;
   }

    static DebugChunkState checkInstance() {
      instance = nullptr;
      if (instance != nullptr) {
         if (instance.m_table != nullptr && instance.m_table.getMetatable() != nullptr) {
            if (instance.m_table.getMetatable().rawget("_LUA_RELOADED_CHECK") == nullptr) {
               instance = nullptr;
            }
         } else {
            instance = nullptr;
         }
      }

    return instance = = nullptr ? std::make_shared<DebugChunkState>() : instance;
   }

    void renderScene() {
      IsoCamera.frameState.set(this.m_playerIndex);
      SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
      SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
      SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
      IsoSprite.globalOffsetX = -1.0F;
      IsoWorld.instance.CurrentCell.render();
      if (this.ChunkGrid.getValue()) {
         this.drawGrid();
      }

      this.drawCursor();
      if (this.LightSquares.getValue()) {
    std::stack var1 = IsoWorld.instance.getCell().getLamppostPositions();

         for (int var2 = 0; var2 < var1.size(); var2++) {
    IsoLightSource var3 = (IsoLightSource)var1.get(var2);
            if (var3.z == this.m_z) {
               this.paintSquare(var3.x, var3.y, var3.z, 1.0F, 1.0F, 0.0F, 0.5F);
            }
         }
      }

      if (this.ZoneRect.getValue()) {
         this.drawZones();
      }

      if (this.BuildingRect.getValue()) {
    IsoGridSquare var5 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, this.m_z);
         if (var5 != nullptr && var5.getBuilding() != nullptr) {
    BuildingDef var9 = var5.getBuilding().getDef();
            this.DrawIsoLine(var9.getX(), var9.getY(), var9.getX2(), var9.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX2(), var9.getY(), var9.getX2(), var9.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX2(), var9.getY2(), var9.getX(), var9.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
            this.DrawIsoLine(var9.getX(), var9.getY2(), var9.getX(), var9.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
         }
      }

      if (this.RoomLightRects.getValue()) {
    std::vector var6 = IsoWorld.instance.CurrentCell.roomLights;

         for (int var10 = 0; var10 < var6.size(); var10++) {
    IsoRoomLight var12 = (IsoRoomLight)var6.get(var10);
            if (var12.z == this.m_z) {
               this.DrawIsoRect(var12.x, var12.y, var12.width, var12.height, 0.0F, 1.0F, 1.0F, 1.0F, 1);
            }
         }
      }

      if (this.FlyBuzzEmitters.getValue()) {
         FliesSound.instance.render();
      }

      if (this.ClosestRoomSquare.getValue()) {
    float var7 = IsoPlayer.players[this.m_playerIndex].getX();
    float var11 = IsoPlayer.players[this.m_playerIndex].getY();
    Vector2f var13 = std::make_shared<Vector2f>();
    BuildingDef var4 = ((AmbientStreamManager)AmbientStreamManager.getInstance()).getNearestBuilding(var7, var11, var13);
         if (var4 != nullptr) {
            this.DrawIsoLine(var7, var11, var13.x, var13.y, 1.0F, 1.0F, 1.0F, 1.0F, 1);
         }
      }

      if (this.m_table != nullptr && this.m_table.rawget("selectedSquare") != nullptr) {
    IsoGridSquare var8 = (IsoGridSquare)Type.tryCastTo(this.m_table.rawget("selectedSquare"), IsoGridSquare.class);
         if (var8 != nullptr) {
            this.DrawIsoRect(var8.x, var8.y, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 2);
         }
      }

      LineDrawer.render();
      LineDrawer.clear();
   }

    void renderUI() {
    int var1 = this.m_playerIndex;
    std::stack var2 = IsoWorld.instance.getCell().getLamppostPositions();
    int var3 = 0;

      for (int var4 = 0; var4 < var2.size(); var4++) {
    IsoLightSource var5 = (IsoLightSource)var2.get(var4);
         if (var5.bActive) {
            var3++;
         }
      }

      UIManager.render();
   }

    void setTable(KahluaTable var1) {
      this.m_table = var1;
   }

    StateAction updateScene() {
      IsoPlayer.setInstance(IsoPlayer.players[this.m_playerIndex]);
      IsoCamera.CamCharacter = IsoPlayer.players[this.m_playerIndex];
      UIManager.setPicked(IsoObjectPicker.Instance.ContextPick(g_mouse.getX(), g_mouse.getY()));
    IsoObject var1 = UIManager.getPicked() == nullptr ? nullptr : UIManager.getPicked().tile;
      UIManager.setLastPicked(var1);
      if (g_keyboard.isKeyDown(SDL_SCANCODE_LSHIFT)) {
         if (!keyQpressed) {
    IsoGridSquare var2 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, 0);
            if (var2 != nullptr) {
               GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(var2.chunk);
               DebugLog.General.debugln("Requesting sync IsoChunk %s", var2.chunk);
            }

            keyQpressed = true;
         }
      } else {
         keyQpressed = false;
      }

      if (g_keyboard.isKeyDown(SDL_SCANCODE_PAUSE)) {
         if (!keyQpressed) {
            DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(true);
            keyQpressed = true;
            DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
         }
      } else {
         keyQpressed = false;
      }

      if (g_keyboard.isKeyDown(SDL_SCANCODE_CAPSLOCK)) {
         if (!keyQpressed) {
            DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(false);
            keyQpressed = true;
            DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
         }
      } else {
         keyQpressed = false;
      }

      if (g_keyboard.isKeyDown(SDL_SCANCODE_S)) {
         if (!keyQpressed) {
            ParticlesFire.getInstance().reloadShader();
            keyQpressed = true;
            DebugLog.General.debugln("ParticlesFire.reloadShader");
         }
      } else {
         keyQpressed = false;
      }

      IsoCamera.update();
      this.updateCursor();
      return StateAction.Remain;
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
         case "getVehicleStory":
            return this.m_vehicleStory;
         case "getZ":
            return BoxedStaticValues.toDouble(this.m_z);
         default:
            throw IllegalArgumentException(std::string.format("unhandled \"%s\"", var1));
      }
   }

    void* fromLua1(const std::string& var1, void* var2) {
      switch (var1) {
         case "getCameraDragX":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedX);
         case "getCameraDragY":
            return BoxedStaticValues.toDouble(-IsoCamera.cameras[this.m_playerIndex].DeferedY);
         case "setPlayerIndex":
            this.m_playerIndex = PZMath.clamp(((double)var2).intValue(), 0, 3);
    return nullptr;
         case "setVehicleStory":
            this.m_vehicleStory = (std::string)var2;
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

    void updateCursor() {
    int var1 = this.m_playerIndex;
    int var2 = Core.TileScale;
   float var3 = g_mouse.getX();
   float var4 = g_mouse.getY();
      var3 -= IsoCamera.getScreenLeft(var1);
      var4 -= IsoCamera.getScreenTop(var1);
      var3 *= Core.getInstance().getZoom(var1);
      var4 *= Core.getInstance().getZoom(var1);
    int var5 = this.m_z;
      this.gridX = (int)IsoUtils.XToIso(var3, var4, var5);
      this.gridY = (int)IsoUtils.YToIso(var3, var4, var5);
   }

    void DrawIsoLine(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
    float var10 = this.m_z;
    float var11 = IsoUtils.XToScreenExact(var1, var2, var10, 0);
    float var12 = IsoUtils.YToScreenExact(var1, var2, var10, 0);
    float var13 = IsoUtils.XToScreenExact(var3, var4, var10, 0);
    float var14 = IsoUtils.YToScreenExact(var3, var4, var10, 0);
      LineDrawer.drawLine(var11, var12, var13, var14, var5, var6, var7, var8, var9);
   }

    void DrawIsoRect(float var1, float var2, float var3, float var4, float var5, float var6, float var7, float var8, int var9) {
      this.DrawIsoLine(var1, var2, var1 + var3, var2, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1 + var3, var2, var1 + var3, var2 + var4, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1 + var3, var2 + var4, var1, var2 + var4, var5, var6, var7, var8, var9);
      this.DrawIsoLine(var1, var2 + var4, var1, var2, var5, var6, var7, var8, var9);
   }

    void drawGrid() {
    int var1 = this.m_playerIndex;
    float var2 = IsoUtils.XToIso(-128.0F, -256.0F, 0.0F);
    float var3 = IsoUtils.YToIso(Core.getInstance().getOffscreenWidth(var1) + 128, -256.0F, 0.0F);
    float var4 = IsoUtils.XToIso(Core.getInstance().getOffscreenWidth(var1) + 128, Core.getInstance().getOffscreenHeight(var1) + 256, 6.0F);
    float var5 = IsoUtils.YToIso(-128.0F, Core.getInstance().getOffscreenHeight(var1) + 256, 6.0F);
    int var7 = (int)var3;
    int var9 = (int)var5;
    int var6 = (int)var2;
    int var8 = (int)var4;
      var6 -= 2;
      var7 -= 2;

      for (int var10 = var7; var10 <= var9; var10++) {
         if (var10 % 10 == 0) {
            this.DrawIsoLine(var6, var10, var8, var10, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         }
      }

      for (int var13 = var6; var13 <= var8; var13++) {
         if (var13 % 10 == 0) {
            this.DrawIsoLine(var13, var7, var13, var9, 1.0F, 1.0F, 1.0F, 0.5F, 1);
         }
      }

      for (int var14 = var7; var14 <= var9; var14++) {
         if (var14 % 300 == 0) {
            this.DrawIsoLine(var6, var14, var8, var14, 0.0F, 1.0F, 0.0F, 0.5F, 1);
         }
      }

      for (int var15 = var6; var15 <= var8; var15++) {
         if (var15 % 300 == 0) {
            this.DrawIsoLine(var15, var7, var15, var9, 0.0F, 1.0F, 0.0F, 0.5F, 1);
         }
      }

      if (GameClient.bClient) {
         for (int var16 = var7; var16 <= var9; var16++) {
            if (var16 % 50 == 0) {
               this.DrawIsoLine(var6, var16, var8, var16, 1.0F, 0.0F, 0.0F, 0.5F, 1);
            }
         }

         for (int var17 = var6; var17 <= var8; var17++) {
            if (var17 % 50 == 0) {
               this.DrawIsoLine(var17, var7, var17, var9, 1.0F, 0.0F, 0.0F, 0.5F, 1);
            }
         }
      }
   }

    void drawCursor() {
    int var1 = this.m_playerIndex;
    int var2 = Core.TileScale;
    float var3 = this.m_z;
    int var4 = (int)IsoUtils.XToScreenExact(this.gridX, this.gridY + 1, var3, 0);
    int var5 = (int)IsoUtils.YToScreenExact(this.gridX, this.gridY + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var4, var5, var4 + 32 * var2, var5 - 16 * var2, var4 + 64 * var2, var5, var4 + 32 * var2, var5 + 16 * var2, 0.0F, 0.0F, 1.0F, 0.5F);
    IsoChunkMap var6 = IsoWorld.instance.getCell().ChunkMap[var1];

      for (int var7 = var6.getWorldYMinTiles(); var7 < var6.getWorldYMaxTiles(); var7++) {
         for (int var8 = var6.getWorldXMinTiles(); var8 < var6.getWorldXMaxTiles(); var8++) {
    IsoGridSquare var9 = IsoWorld.instance.getCell().getGridSquare(var8, var7, var3);
            if (var9 != nullptr) {
               if (var9 != var6.getGridSquare(var8, var7, (int)var3)) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.8F);
               }

               if (var9 == nullptr
                  || var9.getX() != var8
                  || var9.getY() != var7
                  || var9.getZ() != var3
                  || var9.e != nullptr && var9.e.w != nullptr && var9.e.w != var9
                  || var9.w != nullptr && var9.w.e != nullptr && var9.w.e != var9
                  || var9.n != nullptr && var9.n.s != nullptr && var9.n.s != var9
                  || var9.s != nullptr && var9.s.n != nullptr && var9.s.n != var9
                  || var9.nw != nullptr && var9.nw.se != nullptr && var9.nw.se != var9
                  || var9.se != nullptr && var9.se.nw != nullptr && var9.se.nw != var9) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
               }

               if (var9 != nullptr) {
    IsoGridSquare var10 = var9.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : var9.nav[IsoDirections.W.index()];
    IsoGridSquare var11 = var9.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : var9.nav[IsoDirections.N.index()];
    IsoGridSquare var12 = var9.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : var9.nav[IsoDirections.E.index()];
    IsoGridSquare var13 = var9.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : var9.nav[IsoDirections.S.index()];
    IsoGridSquare var14 = var9.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : var9.nav[IsoDirections.NW.index()];
    IsoGridSquare var15 = var9.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : var9.nav[IsoDirections.NE.index()];
    IsoGridSquare var16 = var9.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : var9.nav[IsoDirections.SW.index()];
    IsoGridSquare var17 = var9.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : var9.nav[IsoDirections.SE.index()];
                  if (var10 != var9.w
                     || var11 != var9.n
                     || var12 != var9.e
                     || var13 != var9.s
                     || var14 != var9.nw
                     || var15 != var9.ne
                     || var16 != var9.sw
                     || var17 != var9.se) {
                     this.paintSquare(var8, var7, (int)var3, 1.0F, 0.0F, 0.0F, 0.5F);
                  }
               }

               if (var9 != nullptr
                  && (
                     var9.nav[IsoDirections.NW.index()] != nullptr && var9.nav[IsoDirections.NW.index()].nav[IsoDirections.SE.index()] != var9
                        || var9.nav[IsoDirections.NE.index()] != nullptr && var9.nav[IsoDirections.NE.index()].nav[IsoDirections.SW.index()] != var9
                        || var9.nav[IsoDirections.SW.index()] != nullptr && var9.nav[IsoDirections.SW.index()].nav[IsoDirections.NE.index()] != var9
                        || var9.nav[IsoDirections.SE.index()] != nullptr && var9.nav[IsoDirections.SE.index()].nav[IsoDirections.NW.index()] != var9
                        || var9.nav[IsoDirections.N.index()] != nullptr && var9.nav[IsoDirections.N.index()].nav[IsoDirections.S.index()] != var9
                        || var9.nav[IsoDirections.S.index()] != nullptr && var9.nav[IsoDirections.S.index()].nav[IsoDirections.N.index()] != var9
                        || var9.nav[IsoDirections.W.index()] != nullptr && var9.nav[IsoDirections.W.index()].nav[IsoDirections.E.index()] != var9
                        || var9.nav[IsoDirections.E.index()] != nullptr && var9.nav[IsoDirections.E.index()].nav[IsoDirections.W.index()] != var9
                  )) {
                  var4 = (int)IsoUtils.XToScreenExact(var8, var7 + 1, var3, 0);
                  var5 = (int)IsoUtils.YToScreenExact(var8, var7 + 1, var3, 0);
                  SpriteRenderer.instance.renderPoly(var4, var5, var4 + 32, var5 - 16, var4 + 64, var5, var4 + 32, var5 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
               }

               if (this.EmptySquares.getValue() && var9.getObjects().empty()) {
                  this.paintSquare(var8, var7, (int)var3, 1.0F, 1.0F, 0.0F, 0.5F);
               }

               if (var9.getRoom() != nullptr && var9.isFree(false) && !VirtualZombieManager.instance.canSpawnAt(var8, var7, (int)var3)) {
                  this.paintSquare(var8, var7, (int)var3, 1.0F, 1.0F, 1.0F, 1.0F);
               }

               if (var9.roofHideBuilding != nullptr) {
                  this.paintSquare(var8, var7, (int)var3, 0.0F, 0.0F, 1.0F, 0.25F);
               }
            }
         }
      }

      if (IsoCamera.CamCharacter.getCurrentSquare() != nullptr
         && Math.abs(this.gridX - (int)IsoCamera.CamCharacter.x) <= 1
         && Math.abs(this.gridY - (int)IsoCamera.CamCharacter.y) <= 1) {
    IsoGridSquare var24 = IsoWorld.instance.CurrentCell.getGridSquare(this.gridX, this.gridY, this.m_z);
    IsoObject var25 = IsoCamera.CamCharacter.getCurrentSquare().testCollideSpecialObjects(var24);
         if (var25 != nullptr) {
            var25.getSprite().RenderGhostTileRed((int)var25.getX(), (int)var25.getY(), (int)var25.getZ());
         }
      }

      if (this.LineClearCollide.getValue()) {
         this.lineClearCached(
            IsoWorld.instance.CurrentCell,
            this.gridX,
            this.gridY,
            (int)var3,
            (int)IsoCamera.CamCharacter.getX(),
            (int)IsoCamera.CamCharacter.getY(),
            this.m_z,
            false
         );
      }

      if (this.NearestWallsOpt.getValue()) {
         NearestWalls.render(this.gridX, this.gridY, this.m_z);
      }

      if (this.VehicleStory.getValue()) {
         this.drawVehicleStory();
      }
   }

    void drawZones() {
    std::vector var1 = IsoWorld.instance.MetaGrid.getZonesAt(this.gridX, this.gridY, this.m_z, new std::vector());
    Zone var2 = nullptr;

      for (int var3 = 0; var3 < var1.size(); var3++) {
    Zone var4 = (Zone)var1.get(var3);
         if (var4.isPreferredZoneForSquare) {
            var2 = var4;
         }

         if (!var4.isPolyline()) {
            if (!var4.points.empty()) {
               for (byte var5 = 0; var5 < var4.points.size(); var5 += 2) {
    int var6 = var4.points.get(var5);
    int var7 = var4.points.get(var5 + 1);
    int var8 = var4.points.get((var5 + 2) % var4.points.size());
    int var9 = var4.points.get((var5 + 3) % var4.points.size());
                  this.DrawIsoLine(var6, var7, var8, var9, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            } else {
               this.DrawIsoLine(var4.x, var4.y, var4.x + var4.w, var4.y, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x, var4.y + var4.h, var4.x + var4.w, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x, var4.y, var4.x, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               this.DrawIsoLine(var4.x + var4.w, var4.y, var4.x + var4.w, var4.y + var4.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }
         }
      }

      var1 = IsoWorld.instance.MetaGrid.getZonesIntersecting(this.gridX - 1, this.gridY - 1, this.m_z, 3, 3, std::make_unique<std::vector>());
    LiangBarsky var18 = std::make_shared<LiangBarsky>();
      double[] var19 = new double[2];
    IsoChunk var20 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this.gridX, this.gridY, this.m_z);

      for (int var21 = 0; var21 < var1.size(); var21++) {
    Zone var23 = (Zone)var1.get(var21);
         if (var23 != nullptr && var23.isPolyline() && !var23.points.empty()) {
            for (byte var26 = 0; var26 < var23.points.size() - 2; var26 += 2) {
    int var29 = var23.points.get(var26);
    int var10 = var23.points.get(var26 + 1);
    int var11 = var23.points.get(var26 + 2);
    int var12 = var23.points.get(var26 + 3);
               this.DrawIsoLine(var29, var10, var11, var12, 1.0F, 1.0F, 0.0F, 1.0F, 1);
    float var13 = var11 - var29;
    float var14 = var12 - var10;
               if (var20 != nullptr
                  && var18.lineRectIntersect(var29, var10, var13, var14, var20.wx * 10, var20.wy * 10, var20.wx * 10 + 10, var20.wy * 10 + 10, var19)) {
                  this.DrawIsoLine(
                     var29 + (float)var19[0] * var13,
                     var10 + (float)var19[0] * var14,
                     var29 + (float)var19[1] * var13,
                     var10 + (float)var19[1] * var14,
                     0.0F,
                     1.0F,
                     0.0F,
                     1.0F,
                     1
                  );
               }
            }

            if (var23.polylineOutlinePoints != nullptr) {
               float[] var27 = var23.polylineOutlinePoints;

               for (byte var30 = 0; var30 < var27.length; var30 += 2) {
    float var32 = var27[var30];
    float var34 = var27[var30 + 1];
    float var38 = var27[(var30 + 2) % var27.length];
    float var42 = var27[(var30 + 3) % var27.length];
                  this.DrawIsoLine(var32, var34, var38, var42, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            }
         }
      }

    VehicleZone var22 = IsoWorld.instance.MetaGrid.getVehicleZoneAt(this.gridX, this.gridY, this.m_z);
      if (var22 != nullptr) {
    float var24 = 0.5F;
    float var28 = 1.0F;
    float var31 = 0.5F;
    float var33 = 1.0F;
         if (var22.isPolygon()) {
            for (byte var35 = 0; var35 < var22.points.size(); var35 += 2) {
    int var39 = var22.points.get(var35);
    int var43 = var22.points.get(var35 + 1);
    int var46 = var22.points.get((var35 + 2) % var22.points.size());
    int var15 = var22.points.get((var35 + 3) % var22.points.size());
               this.DrawIsoLine(var39, var43, var46, var15, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }
         } else if (var22.isPolyline()) {
            for (byte var36 = 0; var36 < var22.points.size() - 2; var36 += 2) {
    int var40 = var22.points.get(var36);
    int var44 = var22.points.get(var36 + 1);
    int var47 = var22.points.get(var36 + 2);
    int var49 = var22.points.get(var36 + 3);
               this.DrawIsoLine(var40, var44, var47, var49, 1.0F, 1.0F, 0.0F, 1.0F, 1);
            }

            if (var22.polylineOutlinePoints != nullptr) {
               float[] var37 = var22.polylineOutlinePoints;

               for (byte var41 = 0; var41 < var37.length; var41 += 2) {
    float var45 = var37[var41];
    float var48 = var37[var41 + 1];
    float var50 = var37[(var41 + 2) % var37.length];
    float var16 = var37[(var41 + 3) % var37.length];
                  this.DrawIsoLine(var45, var48, var50, var16, 1.0F, 1.0F, 0.0F, 1.0F, 1);
               }
            }
         } else {
            this.DrawIsoLine(var22.x, var22.y, var22.x + var22.w, var22.y, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x, var22.y + var22.h, var22.x + var22.w, var22.y + var22.h, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x, var22.y, var22.x, var22.y + var22.h, var24, var28, var31, var33, 1);
            this.DrawIsoLine(var22.x + var22.w, var22.y, var22.x + var22.w, var22.y + var22.h, var24, var28, var31, var33, 1);
         }
      }

      if (this.RandomSquareInZone.getValue() && var2 != nullptr) {
    IsoGridSquare var25 = var2.getRandomSquareInZone();
         if (var25 != nullptr) {
            this.paintSquare(var25.x, var25.y, var25.z, 0.0F, 1.0F, 0.0F, 0.5F);
         }
      }
   }

    void drawVehicleStory() {
    std::vector var1 = IsoWorld.instance.MetaGrid.getZonesIntersecting(this.gridX - 1, this.gridY - 1, this.m_z, 3, 3, new std::vector());
      if (!var1.empty()) {
    IsoChunk var2 = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this.gridX, this.gridY, this.m_z);
         if (var2 != nullptr) {
            for (int var3 = 0; var3 < var1.size(); var3++) {
    Zone var4 = (Zone)var1.get(var3);
               if ("Nav" == var4.type)) {
    VehicleStorySpawner var5 = VehicleStorySpawner.getInstance();
    RandomizedVehicleStoryBase var6 = IsoWorld.instance.getRandomizedVehicleStoryByName(this.m_vehicleStory);
                  if (var6 != nullptr && var6.isValid(var4, var2, true) && var6.initVehicleStorySpawner(var4, var2, true)) {
    int var7 = var6.getMinZoneWidth();
    int var8 = var6.getMinZoneHeight();
                     float[] var9 = new float[3];
                     if (var6.getSpawnPoint(var4, var2, var9)) {
    float var10 = var9[0];
    float var11 = var9[1];
    float var12 = var9[2] + (float) (Math.PI / 2);
                        var5.spawn(var10, var11, 0.0F, var12, (var0, var1x) -> {});
                        var5.render(var10, var11, 0.0F, var7, var8, var9[2]);
                     }
                  }
               }
            }
         }
      }
   }

    void DrawBehindStuff() {
      this.IsBehindStuff(IsoCamera.CamCharacter.getCurrentSquare());
   }

    bool IsBehindStuff(IsoGridSquare var1) {
      for (int var2 = 1; var2 < 8 && var1.getZ() + var2 < 8; var2++) {
         for (int var3 = -5; var3 <= 6; var3++) {
            for (int var4 = -5; var4 <= 6; var4++) {
               if (var4 >= var3 - 5 && var4 <= var3 + 5) {
                  this.paintSquare(var1.getX() + var4 + var2 * 3, var1.getY() + var3 + var2 * 3, var1.getZ() + var2, 1.0F, 1.0F, 0.0F, 0.25F);
               }
            }
         }
      }

    return true;
   }

    bool IsBehindStuffRecY(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
    return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecY(var1, var2 + 1, var3 + 1);
      }
   }

    bool IsBehindStuffRecXY(int var1, int var2, int var3, int var4) {
    IsoGridSquare var5 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
    return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecXY(var1 + var4, var2 + var4, var3 + 1, var4);
      }
   }

    bool IsBehindStuffRecX(int var1, int var2, int var3) {
    IsoGridSquare var4 = IsoWorld.instance.CurrentCell.getGridSquare(var1, var2, var3);
      if (var3 >= 15) {
    return false;
      } else {
         this.paintSquare(var1, var2, var3, 1.0F, 1.0F, 0.0F, 0.25F);
         return this.IsBehindStuffRecX(var1 + 1, var2, var3 + 1);
      }
   }

    void paintSquare(int var1, int var2, int var3, float var4, float var5, float var6, float var7) {
    int var8 = Core.TileScale;
    int var9 = (int)IsoUtils.XToScreenExact(var1, var2 + 1, var3, 0);
    int var10 = (int)IsoUtils.YToScreenExact(var1, var2 + 1, var3, 0);
      SpriteRenderer.instance
         .renderPoly(var9, var10, var9 + 32 * var8, var10 - 16 * var8, var9 + 64 * var8, var10, var9 + 32 * var8, var10 + 16 * var8, var4, var5, var6, var7);
   }

    void drawModData() {
    int var1 = this.m_z;
    IsoGridSquare var2 = IsoWorld.instance.getCell().getGridSquare(this.gridX, this.gridY, var1);
    int var3 = Core.getInstance().getScreenWidth() - 250;
    int var4 = 10;
    int var5 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
      if (var2 != nullptr && var2.getModData() != nullptr) {
    KahluaTable var6 = var2.getModData();
    int var12;
         this.DrawString(var3, var12 = var4 + var5, "MOD DATA x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
    KahluaTableIterator var7 = var6.iterator();

         while (var7.advance()) {
            this.DrawString(var3, var12 += var5, var7.getKey() + " = " + var7.getValue());
            if (var7.getValue() instanceof KahluaTable) {
    KahluaTableIterator var8 = ((KahluaTable)var7.getValue()).iterator();

               while (var8.advance()) {
                  this.DrawString(var3 + 8, var12 += var5, var8.getKey() + " = " + var8.getValue());
               }
            }
         }

         var4 = var12 + var5;
      }

      if (var2 != nullptr) {
    PropertyContainer var18 = var2.getProperties();
    std::vector var20 = var18.getPropertyNames();
         if (!var20.empty()) {
            this.DrawString(var3, var4 += var5, "PROPERTIES x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
            Collections.sort(var20);

    for (auto& var9 : var20)               this.DrawString(var3, var4 += var5, var9 + " = \"" + var18.Val(var9) + "\"");
            }
         }

         for (IsoFlagType var11 : IsoFlagType.values()) {
            if (var18.Is(var11)) {
               this.DrawString(var3, var4 += var5, var11);
            }
         }
      }

      if (var2 != nullptr) {
    Square var19 = var2.getErosionData();
         if (var19 != nullptr) {
            var4 += var5;
    int var14;
            this.DrawString(var3, var14 = var4 + var5, "EROSION x,y,z=" + var2.getX() + "," + var2.getY() + "," + var2.getZ());
            this.DrawString(var3, var4 = var14 + var5, "init=" + var19.init);
    int var16;
            this.DrawString(var3, var16 = var4 + var5, "doNothing=" + var19.doNothing);
            this.DrawString(var3, var4 = var16 + var5, "chunk.init=" + var2.chunk.getErosionData().init);
         }
      }
   }

    void drawPlayerInfo() {
    int var1 = Core.getInstance().getScreenWidth() - 250;
    int var2 = Core.getInstance().getScreenHeight() / 2;
    int var3 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
    IsoGameCharacter var4 = IsoCamera.CamCharacter;
    int var5;
      this.DrawString(var1, var5 = var2 + var3, "bored = " + var4.getBodyDamage().getBoredomLevel());
      this.DrawString(var1, var2 = var5 + var3, "endurance = " + var4.getStats().endurance);
    int var7;
      this.DrawString(var1, var7 = var2 + var3, "fatigue = " + var4.getStats().fatigue);
      this.DrawString(var1, var2 = var7 + var3, "hunger = " + var4.getStats().hunger);
    int var9;
      this.DrawString(var1, var9 = var2 + var3, "pain = " + var4.getStats().Pain);
      this.DrawString(var1, var2 = var9 + var3, "panic = " + var4.getStats().Panic);
    int var11;
      this.DrawString(var1, var11 = var2 + var3, "stress = " + var4.getStats().getStress());
      this.DrawString(var1, var2 = var11 + var3, "clothingTemp = " + ((IsoPlayer)var4).getPlayerClothingTemperature());
    int var13;
      this.DrawString(var1, var13 = var2 + var3, "temperature = " + var4.getTemperature());
      this.DrawString(var1, var2 = var13 + var3, "thirst = " + var4.getStats().thirst);
    int var15;
      this.DrawString(var1, var15 = var2 + var3, "foodPoison = " + var4.getBodyDamage().getFoodSicknessLevel());
      this.DrawString(var1, var2 = var15 + var3, "poison = " + var4.getBodyDamage().getPoisonLevel());
    int var17;
      this.DrawString(var1, var17 = var2 + var3, "unhappy = " + var4.getBodyDamage().getUnhappynessLevel());
      this.DrawString(var1, var2 = var17 + var3, "infected = " + var4.getBodyDamage().isInfected());
    int var19;
      this.DrawString(var1, var19 = var2 + var3, "InfectionLevel = " + var4.getBodyDamage().getInfectionLevel());
      this.DrawString(var1, var2 = var19 + var3, "FakeInfectionLevel = " + var4.getBodyDamage().getFakeInfectionLevel());
      var2 += var3;
    int var22;
      this.DrawString(var1, var22 = var2 + var3, "WORLD");
      this.DrawString(var1, var2 = var22 + var3, "globalTemperature = " + IsoWorld.instance.getGlobalTemperature());
   }

    TestResults lineClearCached(IsoCell var1, int var2, int var3, int var4, int var5, int var6, int var7, bool var8) {
    int var12 = var3 - var6;
    int var13 = var2 - var5;
    int var14 = var4 - var7;
    int var15 = var13 + 100;
    int var16 = var12 + 100;
    int var17 = var14 + 16;
      if (var15 >= 0 && var16 >= 0 && var17 >= 0 && var15 < 200 && var16 < 200) {
    TestResults var18 = TestResults.Clear;
    uint8_t var19 = 1;
    float var20 = 0.5F;
    float var21 = 0.5F;
    IsoGridSquare var25 = var1.getGridSquare(var5, var6, var7);
         if (Math.abs(var13) > Math.abs(var12) && Math.abs(var13) > Math.abs(var14)) {
    float var44 = (float)var12 / var13;
    float var49 = (float)var14 / var13;
            var20 += var6;
            var21 += var7;
            var13 = var13 < 0 ? -1 : 1;
            var44 *= var13;
            var49 *= var13;

            while (var5 != var2) {
               var5 += var13;
               var20 += var44;
               var21 += var49;
    IsoGridSquare var52 = var1.getGridSquare(var5, (int)var20, (int)var21);
               this.paintSquare(var5, (int)var20, (int)var21, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var52 != nullptr
                  && var25 != nullptr
                  && var52.testVisionAdjacent(var25.getX() - var52.getX(), var25.getY() - var52.getY(), var25.getZ() - var52.getZ(), true, var8)
                     == TestResults.Blocked) {
                  this.paintSquare(var5, (int)var20, (int)var21, 1.0F, 0.0F, 0.0F, 0.5F);
                  this.paintSquare(var25.getX(), var25.getY(), var25.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
                  var19 = 4;
               }

               var25 = var52;
    int var39 = (int)var20;
    int var40 = (int)var21;
            }
         } else if (Math.abs(var12) >= Math.abs(var13) && Math.abs(var12) > Math.abs(var14)) {
    float var42 = (float)var13 / var12;
    float var47 = (float)var14 / var12;
            var20 += var5;
            var21 += var7;
            var12 = var12 < 0 ? -1 : 1;
            var42 *= var12;
            var47 *= var12;

            while (var6 != var3) {
               var6 += var12;
               var20 += var42;
               var21 += var47;
    IsoGridSquare var51 = var1.getGridSquare((int)var20, var6, (int)var21);
               this.paintSquare((int)var20, var6, (int)var21, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var51 != nullptr
                  && var25 != nullptr
                  && var51.testVisionAdjacent(var25.getX() - var51.getX(), var25.getY() - var51.getY(), var25.getZ() - var51.getZ(), true, var8)
                     == TestResults.Blocked) {
                  this.paintSquare((int)var20, var6, (int)var21, 1.0F, 0.0F, 0.0F, 0.5F);
                  this.paintSquare(var25.getX(), var25.getY(), var25.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
                  var19 = 4;
               }

               var25 = var51;
    int var38 = (int)var20;
    int var24 = (int)var21;
            }
         } else {
    float var26 = (float)var13 / var14;
    float var27 = (float)var12 / var14;
            var20 += var5;
            var21 += var6;
            var14 = var14 < 0 ? -1 : 1;
            var26 *= var14;
            var27 *= var14;

            while (var7 != var4) {
               var7 += var14;
               var20 += var26;
               var21 += var27;
    IsoGridSquare var28 = var1.getGridSquare((int)var20, (int)var21, var7);
               this.paintSquare((int)var20, (int)var21, var7, 1.0F, 1.0F, 1.0F, 0.5F);
               if (var28 != nullptr
                  && var25 != nullptr
                  && var28.testVisionAdjacent(var25.getX() - var28.getX(), var25.getY() - var28.getY(), var25.getZ() - var28.getZ(), true, var8)
                     == TestResults.Blocked) {
                  var19 = 4;
               }

               var25 = var28;
    int var22 = (int)var20;
    int var23 = (int)var21;
            }
         }

         if (var19 == 1) {
            return TestResults.Clear;
         } else if (var19 == 2) {
            return TestResults.ClearThroughOpenDoor;
         } else if (var19 == 3) {
            return TestResults.ClearThroughWindow;
         } else {
    return var19 = = 4 ? TestResults.Blocked : TestResults.Blocked;
         }
      } else {
         return TestResults.Blocked;
      }
   }

    void DrawString(int var1, int var2, const std::string& var3) {
    int var4 = TextManager.instance.MeasureStringX(this.FONT, var3);
    int var5 = TextManager.instance.getFontFromEnum(this.FONT).getLineHeight();
      SpriteRenderer.instance.renderi(nullptr, var1 - 1, var2, var4 + 2, var5, 0.0F, 0.0F, 0.0F, 0.8F, nullptr);
      TextManager.instance.DrawString(this.FONT, var1, var2, var3, 1.0, 1.0, 1.0, 1.0);
   }

    ConfigOption getOptionByName(const std::string& var1) {
      for (int var2 = 0; var2 < this.options.size(); var2++) {
    ConfigOption var3 = this.options.get(var2);
         if (var3.getName() == var1)) {
    return var3;
         }
      }

    return nullptr;
   }

    int getOptionCount() {
      return this.options.size();
   }

    ConfigOption getOptionByIndex(int var1) {
      return this.options.get(var1);
   }

    void setBoolean(const std::string& var1, bool var2) {
    ConfigOption var3 = this.getOptionByName(var1);
      if (dynamic_cast<BooleanConfigOption*>(var3) != nullptr) {
         ((BooleanConfigOption)var3).setValue(var2);
      }
   }

    bool getBoolean(const std::string& var1) {
    ConfigOption var2 = this.getOptionByName(var1);
      return dynamic_cast<BooleanConfigOption*>(var2) != nullptr ? ((BooleanConfigOption)var2).getValue() : false;
   }

    void save() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      var2.write(var1, 1, this.options);
   }

    void load() {
    std::string var1 = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
    ConfigFile var2 = std::make_shared<ConfigFile>();
      if (var2.read(var1)) {
         for (int var3 = 0; var3 < var2.getOptions().size(); var3++) {
    ConfigOption var4 = (ConfigOption)var2.getOptions().get(var3);
    ConfigOption var5 = this.getOptionByName(var4.getName());
            if (var5 != nullptr) {
               var5.parse(var4.getValueAsString());
            }
         }
      }
   }
}
} // namespace gameStates
} // namespace zombie
