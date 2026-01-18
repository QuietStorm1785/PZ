#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/joml/Vector2f.h"
#include "se/krka/kahlua/vm/KahluaTable.h"
#include "se/krka/kahlua/vm/KahluaTableIterator.h"
#include "zombie/AmbientStreamManager.h"
#include "zombie/FliesSound.h"
#include "zombie/Lua/LuaManager.h"
#include "zombie/VirtualZombieManager.h"
#include "zombie/ZomboidFileSystem.h"
#include "zombie/ai/astar/Mover.h"
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
#include "zombie/core/utils/BooleanGrid.h"
#include "zombie/debug/DebugLog.h"
#include "zombie/debug/DebugOptions.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/erosion/ErosionData.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/BuildingDef.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoChunkMap.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoLightSource.h"
#include "zombie/iso/IsoMetaGrid.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoRoomLight.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/LosUtil.h"
#include "zombie/iso/NearestWalls.h"
#include "zombie/iso/ParticlesFire.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoBuilding.h"
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
#include "zombie/vehicles/EditVehicleState.h"
#include "zombie/vehicles/PolygonalMap2.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace zombie {
namespace gameStates {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class DebugChunkState : public GameState {
public:
 static DebugChunkState instance;
 private EditVehicleState.LuaEnvironment m_luaEnv;
 bool bExit = false;
 private ArrayList<UIElement> m_gameUI = std::make_unique<ArrayList<>>();
 private ArrayList<UIElement> m_selfUI = std::make_unique<ArrayList<>>();
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
 private ArrayList<ConfigOption> options = std::make_unique<ArrayList<>>();
 private DebugChunkState.BooleanDebugOption BuildingRect = new DebugChunkState.BooleanDebugOption("BuildingRect", true);
 private DebugChunkState.BooleanDebugOption ChunkGrid = new DebugChunkState.BooleanDebugOption("ChunkGrid", true);
 private DebugChunkState.BooleanDebugOption ClosestRoomSquare = new DebugChunkState.BooleanDebugOption("ClosestRoomSquare", true);
 private DebugChunkState.BooleanDebugOption EmptySquares = new DebugChunkState.BooleanDebugOption("EmptySquares", true);
 private DebugChunkState.BooleanDebugOption FlyBuzzEmitters = new DebugChunkState.BooleanDebugOption("FlyBuzzEmitters", true);
 private DebugChunkState.BooleanDebugOption LightSquares = new DebugChunkState.BooleanDebugOption("LightSquares", true);
 private DebugChunkState.BooleanDebugOption LineClearCollide = new DebugChunkState.BooleanDebugOption("LineClearCollide", true);
 private DebugChunkState.BooleanDebugOption NearestWallsOpt = new DebugChunkState.BooleanDebugOption("NearestWalls", true);
 private DebugChunkState.BooleanDebugOption ObjectPicker = new DebugChunkState.BooleanDebugOption("ObjectPicker", true);
 private DebugChunkState.BooleanDebugOption RoomLightRects = new DebugChunkState.BooleanDebugOption("RoomLightRects", true);
 private DebugChunkState.BooleanDebugOption VehicleStory = new DebugChunkState.BooleanDebugOption("VehicleStory", true);
 private DebugChunkState.BooleanDebugOption RandomSquareInZone = new DebugChunkState.BooleanDebugOption("RandomSquareInZone", true);
 private DebugChunkState.BooleanDebugOption ZoneRect = new DebugChunkState.BooleanDebugOption("ZoneRect", true);

 public DebugChunkState() {
 instance = this;
 }

 void enter() {
 instance = this;
 this->load();
 if (this->m_luaEnv == nullptr) {
 this->m_luaEnv = new EditVehicleState.LuaEnvironment(LuaManager.platform, LuaManager.converterManager, LuaManager.env);
 }

 this->saveGameUI();
 if (this->m_selfUI.size() == 0) {
 IsoPlayer player = IsoPlayer.players[this->m_playerIndex];
 this->m_z = player == nullptr ? 0 : (int)player.z;
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_luaEnv.env.rawget("DebugChunkState_InitUI"), this);
 if (this->m_table != nullptr && this->m_table.getMetatable() != nullptr) {
 this->m_table.getMetatable().rawset("_LUA_RELOADED_CHECK", Boolean.FALSE);
 }
 } else {
 UIManager.UI.addAll(this->m_selfUI);
 this->m_luaEnv.caller.pcall(this->m_luaEnv.thread, this->m_table.rawget("showUI"), this->m_table);
 }

 this->bExit = false;
 }

 void yield() {
 this->restoreGameUI();
 }

 void reenter() {
 this->saveGameUI();
 }

 void exit() {
 this->save();
 this->restoreGameUI();

 for (int int0 = 0; int0 < IsoCamera.cameras.length; int0++) {
 IsoCamera.cameras[int0].DeferedX = IsoCamera.cameras[int0].DeferedY = 0.0F;
 }
 }

 void render() {
 IsoPlayer.setInstance(IsoPlayer.players[this->m_playerIndex]);
 IsoCamera.CamCharacter = IsoPlayer.players[this->m_playerIndex];
 bool boolean0 = true;

 for (int int0 = 0; int0 < IsoPlayer.numPlayers; int0++) {
 if (int0 != this->m_playerIndex && IsoPlayer.players[int0] != nullptr) {
 Core.getInstance().StartFrame(int0, boolean0);
 Core.getInstance().EndFrame(int0);
 boolean0 = false;
 }
 }

 Core.getInstance().StartFrame(this->m_playerIndex, boolean0);
 this->renderScene();
 Core.getInstance().EndFrame(this->m_playerIndex);
 Core.getInstance().RenderOffScreenBuffer();

 for (int int1 = 0; int1 < IsoPlayer.numPlayers; int1++) {
 TextDrawObject.NoRender(int1);
 ChatElement.NoRender(int1);
 }

 if (Core.getInstance().StartFrameUI()) {
 this->renderUI();
 }

 Core.getInstance().EndFrameUI();
 }

 public GameStateMachine.StateAction update() {
 return !this->bExit && !GameKeyboard.isKeyPressed(60) ? this->updateScene() : GameStateMachine.StateAction.Continue;
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

 return instance = = nullptr ? new DebugChunkState() : instance;
 }

 void renderScene() {
 IsoCamera.frameState.set(this->m_playerIndex);
 SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
 SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
 SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
 IsoSprite.globalOffsetX = -1.0F;
 IsoWorld.instance.CurrentCell.render();
 if (this->ChunkGrid.getValue()) {
 this->drawGrid();
 }

 this->drawCursor();
 if (this->LightSquares.getValue()) {
 std::stack stack = IsoWorld.instance.getCell().getLamppostPositions();

 for (int int0 = 0; int0 < stack.size(); int0++) {
 IsoLightSource lightSource = (IsoLightSource)stack.get(int0);
 if (lightSource.z == this->m_z) {
 this->paintSquare(lightSource.x, lightSource.y, lightSource.z, 1.0F, 1.0F, 0.0F, 0.5F);
 }
 }
 }

 if (this->ZoneRect.getValue()) {
 this->drawZones();
 }

 if (this->BuildingRect.getValue()) {
 IsoGridSquare square0 = IsoWorld.instance.getCell().getGridSquare(this->gridX, this->gridY, this->m_z);
 if (square0 != nullptr && square0.getBuilding() != nullptr) {
 BuildingDef buildingDef0 = square0.getBuilding().getDef();
 this->DrawIsoLine(buildingDef0.getX(), buildingDef0.getY(), buildingDef0.getX2(), buildingDef0.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
 this->DrawIsoLine(buildingDef0.getX2(), buildingDef0.getY(), buildingDef0.getX2(), buildingDef0.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
 this->DrawIsoLine(buildingDef0.getX2(), buildingDef0.getY2(), buildingDef0.getX(), buildingDef0.getY2(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
 this->DrawIsoLine(buildingDef0.getX(), buildingDef0.getY2(), buildingDef0.getX(), buildingDef0.getY(), 1.0F, 1.0F, 1.0F, 1.0F, 2);
 }
 }

 if (this->RoomLightRects.getValue()) {
 std::vector arrayList = IsoWorld.instance.CurrentCell.roomLights;

 for (int int1 = 0; int1 < arrayList.size(); int1++) {
 IsoRoomLight roomLight = (IsoRoomLight)arrayList.get(int1);
 if (roomLight.z == this->m_z) {
 this->DrawIsoRect(roomLight.x, roomLight.y, roomLight.width, roomLight.height, 0.0F, 1.0F, 1.0F, 1.0F, 1);
 }
 }
 }

 if (this->FlyBuzzEmitters.getValue()) {
 FliesSound.instance.render();
 }

 if (this->ClosestRoomSquare.getValue()) {
 float float0 = IsoPlayer.players[this->m_playerIndex].getX();
 float float1 = IsoPlayer.players[this->m_playerIndex].getY();
 Vector2f vector2f = new Vector2f();
 BuildingDef buildingDef1 = ((AmbientStreamManager)AmbientStreamManager.getInstance()).getNearestBuilding(float0, float1, vector2f);
 if (buildingDef1 != nullptr) {
 this->DrawIsoLine(float0, float1, vector2f.x, vector2f.y, 1.0F, 1.0F, 1.0F, 1.0F, 1);
 }
 }

 if (this->m_table != nullptr && this->m_table.rawget("selectedSquare") != nullptr) {
 IsoGridSquare square1 = Type.tryCastTo(this->m_table.rawget("selectedSquare"), IsoGridSquare.class);
 if (square1 != nullptr) {
 this->DrawIsoRect(square1.x, square1.y, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 1.0F, 2);
 }
 }

 LineDrawer.render();
 LineDrawer.clear();
 }

 void renderUI() {
 int int0 = this->m_playerIndex;
 std::stack stack = IsoWorld.instance.getCell().getLamppostPositions();
 int int1 = 0;

 for (int int2 = 0; int2 < stack.size(); int2++) {
 IsoLightSource lightSource = (IsoLightSource)stack.get(int2);
 if (lightSource.bActive) {
 int1++;
 }
 }

 UIManager.render();
 }

 void setTable(KahluaTable table) {
 this->m_table = table;
 }

 public GameStateMachine.StateAction updateScene() {
 IsoPlayer.setInstance(IsoPlayer.players[this->m_playerIndex]);
 IsoCamera.CamCharacter = IsoPlayer.players[this->m_playerIndex];
 UIManager.setPicked(IsoObjectPicker.Instance.ContextPick(Mouse.getXA(), Mouse.getYA()));
 IsoObject object = UIManager.getPicked() == nullptr ? nullptr : UIManager.getPicked().tile;
 UIManager.setLastPicked(object);
 if (GameKeyboard.isKeyDown(16) {
 if (!keyQpressed) {
 IsoGridSquare square = IsoWorld.instance.getCell().getGridSquare(this->gridX, this->gridY, 0);
 if (square != nullptr) {
 GameClient.instance.worldObjectsSyncReq.putRequestSyncIsoChunk(square.chunk);
 DebugLog.General.debugln("Requesting sync IsoChunk %s", square.chunk);
 }

 keyQpressed = true;
 }
 } else {
 keyQpressed = false;
 }

 if (GameKeyboard.isKeyDown(19) {
 if (!keyQpressed) {
 DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(true);
 keyQpressed = true;
 DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
 }
 } else {
 keyQpressed = false;
 }

 if (GameKeyboard.isKeyDown(20) {
 if (!keyQpressed) {
 DebugOptions.instance.Terrain.RenderTiles.NewRender.setValue(false);
 keyQpressed = true;
 DebugLog.General.debugln("IsoCell.newRender = %s", DebugOptions.instance.Terrain.RenderTiles.NewRender.getValue());
 }
 } else {
 keyQpressed = false;
 }

 if (GameKeyboard.isKeyDown(31) {
 if (!keyQpressed) {
 ParticlesFire.getInstance().reloadShader();
 keyQpressed = true;
 DebugLog.General.debugln("ParticlesFire.reloadShader");
 }
 } else {
 keyQpressed = false;
 }

 IsoCamera.update();
 this->updateCursor();
 return GameStateMachine.StateAction.Remain;
 }

 void saveGameUI() {
 this->m_gameUI.clear();
 this->m_gameUI.addAll(UIManager.UI);
 UIManager.UI.clear();
 this->m_bSuspendUI = UIManager.bSuspend;
 UIManager.bSuspend = false;
 UIManager.setShowPausedMessage(false);
 UIManager.defaultthread = this->m_luaEnv.thread;
 }

 void restoreGameUI() {
 this->m_selfUI.clear();
 this->m_selfUI.addAll(UIManager.UI);
 UIManager.UI.clear();
 UIManager.UI.addAll(this->m_gameUI);
 UIManager.bSuspend = this->m_bSuspendUI;
 UIManager.setShowPausedMessage(true);
 UIManager.defaultthread = LuaManager.thread;
 }

 void* fromLua0(const std::string& func) {
 switch (func) {
 case "exit":
 this->bExit = true;
 return nullptr;
 case "getCameraDragX":
 return BoxedStaticValues.toDouble(-IsoCamera.cameras[this->m_playerIndex].DeferedX);
 case "getCameraDragY":
 return BoxedStaticValues.toDouble(-IsoCamera.cameras[this->m_playerIndex].DeferedY);
 case "getPlayerIndex":
 return BoxedStaticValues.toDouble(this->m_playerIndex);
 case "getVehicleStory":
 return this->m_vehicleStory;
 case "getZ":
 return BoxedStaticValues.toDouble(this->m_z);
 default:
 throw IllegalArgumentException(String.format("unhandled \"%s\"", func);
 }
 }

 void* fromLua1(const std::string& func, void* arg0) {
 switch (func) {
 case "getCameraDragX":
 return BoxedStaticValues.toDouble(-IsoCamera.cameras[this->m_playerIndex].DeferedX);
 case "getCameraDragY":
 return BoxedStaticValues.toDouble(-IsoCamera.cameras[this->m_playerIndex].DeferedY);
 case "setPlayerIndex":
 this->m_playerIndex = PZMath.clamp(((Double)arg0).intValue(), 0, 3);
 return nullptr;
 case "setVehicleStory":
 this->m_vehicleStory = (String)arg0;
 return nullptr;
 case "setZ":
 this->m_z = PZMath.clamp(((Double)arg0).intValue(), 0, 7);
 return nullptr;
 default:
 throw IllegalArgumentException(String.format("unhandled \"%s\" \"%s\"", func, arg0);
 }
 }

 void* fromLua2(const std::string& func, void* arg0, void* arg1) {
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
 IsoCamera.cameras[this->m_playerIndex].DeferedX = -float0;
 IsoCamera.cameras[this->m_playerIndex].DeferedY = -float1;
 return nullptr;
 default:
 throw IllegalArgumentException(String.format("unhandled \"%s\" \"%s\" \\\"%s\\\"", func, arg0, arg1);
 }
 }
 }

 void updateCursor() {
 int int0 = this->m_playerIndex;
 int int1 = Core.TileScale;
 float float0 = Mouse.getXA();
 float float1 = Mouse.getYA();
 float0 -= IsoCamera.getScreenLeft(int0);
 float1 -= IsoCamera.getScreenTop(int0);
 float0 *= Core.getInstance().getZoom(int0);
 float1 *= Core.getInstance().getZoom(int0);
 int int2 = this->m_z;
 this->gridX = (int)IsoUtils.XToIso(float0, float1, int2);
 this->gridY = (int)IsoUtils.YToIso(float0, float1, int2);
 }

 void DrawIsoLine(float float2, float float3, float float6, float float7, float float9, float float10, float float11, float float12, int int0) {
 float float0 = this->m_z;
 float float1 = IsoUtils.XToScreenExact(float2, float3, float0, 0);
 float float4 = IsoUtils.YToScreenExact(float2, float3, float0, 0);
 float float5 = IsoUtils.XToScreenExact(float6, float7, float0, 0);
 float float8 = IsoUtils.YToScreenExact(float6, float7, float0, 0);
 LineDrawer.drawLine(float1, float4, float5, float8, float9, float10, float11, float12, int0);
 }

 void DrawIsoRect(float float0, float float1, float float6, float float7, float float2, float float3, float float4, float float5, int int0) {
 this->DrawIsoLine(float0, float1, float0 + float6, float1, float2, float3, float4, float5, int0);
 this->DrawIsoLine(float0 + float6, float1, float0 + float6, float1 + float7, float2, float3, float4, float5, int0);
 this->DrawIsoLine(float0 + float6, float1 + float7, float0, float1 + float7, float2, float3, float4, float5, int0);
 this->DrawIsoLine(float0, float1 + float7, float0, float1, float2, float3, float4, float5, int0);
 }

 void drawGrid() {
 int int0 = this->m_playerIndex;
 float float0 = IsoUtils.XToIso(-128.0F, -256.0F, 0.0F);
 float float1 = IsoUtils.YToIso(Core.getInstance().getOffscreenWidth(int0) + 128, -256.0F, 0.0F);
 float float2 = IsoUtils.XToIso(Core.getInstance().getOffscreenWidth(int0) + 128, Core.getInstance().getOffscreenHeight(int0) + 256, 6.0F);
 float float3 = IsoUtils.YToIso(-128.0F, Core.getInstance().getOffscreenHeight(int0) + 256, 6.0F);
 int int1 = (int)float1;
 int int2 = (int)float3;
 int int3 = (int)float0;
 int int4 = (int)float2;
 int3 -= 2;
 int1 -= 2;

 for (int int5 = int1; int5 <= int2; int5++) {
 if (int5 % 10 == 0) {
 this->DrawIsoLine(int3, int5, int4, int5, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 }
 }

 for (int int6 = int3; int6 <= int4; int6++) {
 if (int6 % 10 == 0) {
 this->DrawIsoLine(int6, int1, int6, int2, 1.0F, 1.0F, 1.0F, 0.5F, 1);
 }
 }

 for (int int7 = int1; int7 <= int2; int7++) {
 if (int7 % 300 == 0) {
 this->DrawIsoLine(int3, int7, int4, int7, 0.0F, 1.0F, 0.0F, 0.5F, 1);
 }
 }

 for (int int8 = int3; int8 <= int4; int8++) {
 if (int8 % 300 == 0) {
 this->DrawIsoLine(int8, int1, int8, int2, 0.0F, 1.0F, 0.0F, 0.5F, 1);
 }
 }

 if (GameClient.bClient) {
 for (int int9 = int1; int9 <= int2; int9++) {
 if (int9 % 50 == 0) {
 this->DrawIsoLine(int3, int9, int4, int9, 1.0F, 0.0F, 0.0F, 0.5F, 1);
 }
 }

 for (int int10 = int3; int10 <= int4; int10++) {
 if (int10 % 50 == 0) {
 this->DrawIsoLine(int10, int1, int10, int2, 1.0F, 0.0F, 0.0F, 0.5F, 1);
 }
 }
 }
 }

 void drawCursor() {
 int int0 = this->m_playerIndex;
 int int1 = Core.TileScale;
 float float0 = this->m_z;
 int int2 = (int)IsoUtils.XToScreenExact(this->gridX, this->gridY + 1, float0, 0);
 int int3 = (int)IsoUtils.YToScreenExact(this->gridX, this->gridY + 1, float0, 0);
 SpriteRenderer.instance
 .renderPoly(int2, int3, int2 + 32 * int1, int3 - 16 * int1, int2 + 64 * int1, int3, int2 + 32 * int1, int3 + 16 * int1, 0.0F, 0.0F, 1.0F, 0.5F);
 IsoChunkMap chunkMap = IsoWorld.instance.getCell().ChunkMap[int0];

 for (int int4 = chunkMap.getWorldYMinTiles(); int4 < chunkMap.getWorldYMaxTiles(); int4++) {
 for (int int5 = chunkMap.getWorldXMinTiles(); int5 < chunkMap.getWorldXMaxTiles(); int5++) {
 IsoGridSquare square0 = IsoWorld.instance.getCell().getGridSquare((double)int5, (double)int4, (double)float0);
 if (square0 != nullptr) {
 if (square0 != chunkMap.getGridSquare(int5, int4, (int)float0) {
 int2 = (int)IsoUtils.XToScreenExact(int5, int4 + 1, float0, 0);
 int3 = (int)IsoUtils.YToScreenExact(int5, int4 + 1, float0, 0);
 SpriteRenderer.instance.renderPoly(int2, int3, int2 + 32, int3 - 16, int2 + 64, int3, int2 + 32, int3 + 16, 1.0F, 0.0F, 0.0F, 0.8F);
 }

 if (square0 == nullptr
 || square0.getX() != int5
 || square0.getY() != int4
 || square0.getZ() != float0
 || square0.e != nullptr && square0.e.w != nullptr && square0.e.w != square0
 || square0.w != nullptr && square0.w.e != nullptr && square0.w.e != square0
 || square0.n != nullptr && square0.n.s != nullptr && square0.n.s != square0
 || square0.s != nullptr && square0.s.n != nullptr && square0.s.n != square0
 || square0.nw != nullptr && square0.nw.se != nullptr && square0.nw.se != square0
 || square0.se != nullptr && square0.se.nw != nullptr && square0.se.nw != square0) {
 int2 = (int)IsoUtils.XToScreenExact(int5, int4 + 1, float0, 0);
 int3 = (int)IsoUtils.YToScreenExact(int5, int4 + 1, float0, 0);
 SpriteRenderer.instance.renderPoly(int2, int3, int2 + 32, int3 - 16, int2 + 64, int3, int2 + 32, int3 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
 }

 if (square0 != nullptr) {
 IsoGridSquare square1 = square0.testPathFindAdjacent(nullptr, -1, 0, 0) ? nullptr : square0.nav[IsoDirections.W.index()];
 IsoGridSquare square2 = square0.testPathFindAdjacent(nullptr, 0, -1, 0) ? nullptr : square0.nav[IsoDirections.N.index()];
 IsoGridSquare square3 = square0.testPathFindAdjacent(nullptr, 1, 0, 0) ? nullptr : square0.nav[IsoDirections.E.index()];
 IsoGridSquare square4 = square0.testPathFindAdjacent(nullptr, 0, 1, 0) ? nullptr : square0.nav[IsoDirections.S.index()];
 IsoGridSquare square5 = square0.testPathFindAdjacent(nullptr, -1, -1, 0) ? nullptr : square0.nav[IsoDirections.NW.index()];
 IsoGridSquare square6 = square0.testPathFindAdjacent(nullptr, 1, -1, 0) ? nullptr : square0.nav[IsoDirections.NE.index()];
 IsoGridSquare square7 = square0.testPathFindAdjacent(nullptr, -1, 1, 0) ? nullptr : square0.nav[IsoDirections.SW.index()];
 IsoGridSquare square8 = square0.testPathFindAdjacent(nullptr, 1, 1, 0) ? nullptr : square0.nav[IsoDirections.SE.index()];
 if (square1 != square0.w
 || square2 != square0.n
 || square3 != square0.e
 || square4 != square0.s
 || square5 != square0.nw
 || square6 != square0.ne
 || square7 != square0.sw
 || square8 != square0.se) {
 this->paintSquare(int5, int4, (int)float0, 1.0F, 0.0F, 0.0F, 0.5F);
 }
 }

 if (square0 != nullptr
 && (
 square0.nav[IsoDirections.NW.index()] != nullptr && square0.nav[IsoDirections.NW.index()].nav[IsoDirections.SE.index()] != square0
 || square0.nav[IsoDirections.NE.index()] != nullptr
 && square0.nav[IsoDirections.NE.index()].nav[IsoDirections.SW.index()] != square0
 || square0.nav[IsoDirections.SW.index()] != nullptr
 && square0.nav[IsoDirections.SW.index()].nav[IsoDirections.NE.index()] != square0
 || square0.nav[IsoDirections.SE.index()] != nullptr
 && square0.nav[IsoDirections.SE.index()].nav[IsoDirections.NW.index()] != square0
 || square0.nav[IsoDirections.N.index()] != nullptr && square0.nav[IsoDirections.N.index()].nav[IsoDirections.S.index()] != square0
 || square0.nav[IsoDirections.S.index()] != nullptr && square0.nav[IsoDirections.S.index()].nav[IsoDirections.N.index()] != square0
 || square0.nav[IsoDirections.W.index()] != nullptr && square0.nav[IsoDirections.W.index()].nav[IsoDirections.E.index()] != square0
 || square0.nav[IsoDirections.E.index()] != nullptr && square0.nav[IsoDirections.E.index()].nav[IsoDirections.W.index()] != square0
 )) {
 int2 = (int)IsoUtils.XToScreenExact(int5, int4 + 1, float0, 0);
 int3 = (int)IsoUtils.YToScreenExact(int5, int4 + 1, float0, 0);
 SpriteRenderer.instance.renderPoly(int2, int3, int2 + 32, int3 - 16, int2 + 64, int3, int2 + 32, int3 + 16, 1.0F, 0.0F, 0.0F, 0.5F);
 }

 if (this->EmptySquares.getValue() && square0.getObjects().empty()) {
 this->paintSquare(int5, int4, (int)float0, 1.0F, 1.0F, 0.0F, 0.5F);
 }

 if (square0.getRoom() != nullptr && square0.isFree(false) && !VirtualZombieManager.instance.canSpawnAt(int5, int4, (int)float0) {
 this->paintSquare(int5, int4, (int)float0, 1.0F, 1.0F, 1.0F, 1.0F);
 }

 if (square0.roofHideBuilding != nullptr) {
 this->paintSquare(int5, int4, (int)float0, 0.0F, 0.0F, 1.0F, 0.25F);
 }
 }
 }
 }

 if (IsoCamera.CamCharacter.getCurrentSquare() != nullptr
 && Math.abs(this->gridX - (int)IsoCamera.CamCharacter.x) <= 1
 && Math.abs(this->gridY - (int)IsoCamera.CamCharacter.y) <= 1) {
 IsoGridSquare square9 = IsoWorld.instance.CurrentCell.getGridSquare(this->gridX, this->gridY, this->m_z);
 IsoObject object = IsoCamera.CamCharacter.getCurrentSquare().testCollideSpecialObjects(square9);
 if (object != nullptr) {
 object.getSprite().RenderGhostTileRed((int)object.getX(), (int)object.getY(), (int)object.getZ());
 }
 }

 if (this->LineClearCollide.getValue()) {
 this->lineClearCached(
 IsoWorld.instance.CurrentCell,
 this->gridX,
 this->gridY,
 (int)float0,
 (int)IsoCamera.CamCharacter.getX(),
 (int)IsoCamera.CamCharacter.getY(),
 this->m_z,
 false
 );
 }

 if (this->NearestWallsOpt.getValue()) {
 NearestWalls.render(this->gridX, this->gridY, this->m_z);
 }

 if (this->VehicleStory.getValue()) {
 this->drawVehicleStory();
 }
 }

 void drawZones() {
 std::vector arrayList = IsoWorld.instance.MetaGrid.getZonesAt(this->gridX, this->gridY, this->m_z, new ArrayList<>());
 IsoMetaGrid.Zone zone0 = nullptr;

 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoMetaGrid.Zone zone1 = (IsoMetaGrid.Zone)arrayList.get(int0);
 if (zone1.isPreferredZoneForSquare) {
 zone0 = zone1;
 }

 if (!zone1.isPolyline()) {
 if (!zone1.points.empty()) {
 for (byte byte0 = 0; byte0 < zone1.points.size(); byte0 += 2) {
 int int1 = zone1.points.get(byte0);
 int int2 = zone1.points.get(byte0 + 1);
 int int3 = zone1.points.get((byte0 + 2) % zone1.points.size());
 int int4 = zone1.points.get((byte0 + 3) % zone1.points.size());
 this->DrawIsoLine(int1, int2, int3, int4, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }
 } else {
 this->DrawIsoLine(zone1.x, zone1.y, zone1.x + zone1.w, zone1.y, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 this->DrawIsoLine(zone1.x, zone1.y + zone1.h, zone1.x + zone1.w, zone1.y + zone1.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 this->DrawIsoLine(zone1.x, zone1.y, zone1.x, zone1.y + zone1.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 this->DrawIsoLine(zone1.x + zone1.w, zone1.y, zone1.x + zone1.w, zone1.y + zone1.h, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }
 }
 }

 arrayList = IsoWorld.instance.MetaGrid.getZonesIntersecting(this->gridX - 1, this->gridY - 1, this->m_z, 3, 3, std::make_unique<ArrayList<>>());
 PolygonalMap2.LiangBarsky liangBarsky = new PolygonalMap2.LiangBarsky();
 double[] doubles = new double[2];
 IsoChunk chunk = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this->gridX, this->gridY, this->m_z);

 for (int int5 = 0; int5 < arrayList.size(); int5++) {
 IsoMetaGrid.Zone zone2 = (IsoMetaGrid.Zone)arrayList.get(int5);
 if (zone2 != nullptr && zone2.isPolyline() && !zone2.points.empty()) {
 for (byte byte1 = 0; byte1 < zone2.points.size() - 2; byte1 += 2) {
 int int6 = zone2.points.get(byte1);
 int int7 = zone2.points.get(byte1 + 1);
 int int8 = zone2.points.get(byte1 + 2);
 int int9 = zone2.points.get(byte1 + 3);
 this->DrawIsoLine(int6, int7, int8, int9, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 float float0 = int8 - int6;
 float float1 = int9 - int7;
 if (chunk != nullptr
 && liangBarsky.lineRectIntersect(
 int6, int7, float0, float1, chunk.wx * 10, chunk.wy * 10, chunk.wx * 10 + 10, chunk.wy * 10 + 10, doubles
 )) {
 this->DrawIsoLine(
 int6 + (float)doubles[0] * float0,
 int7 + (float)doubles[0] * float1,
 int6 + (float)doubles[1] * float0,
 int7 + (float)doubles[1] * float1,
 0.0F,
 1.0F,
 0.0F,
 1.0F,
 1
 );
 }
 }

 if (zone2.polylineOutlinePoints != nullptr) {
 float[] floats0 = zone2.polylineOutlinePoints;

 for (byte byte2 = 0; byte2 < floats0.length; byte2 += 2) {
 float float2 = floats0[byte2];
 float float3 = floats0[byte2 + 1];
 float float4 = floats0[(byte2 + 2) % floats0.length];
 float float5 = floats0[(byte2 + 3) % floats0.length];
 this->DrawIsoLine(float2, float3, float4, float5, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }
 }
 }
 }

 IsoMetaGrid.VehicleZone vehicleZone = IsoWorld.instance.MetaGrid.getVehicleZoneAt(this->gridX, this->gridY, this->m_z);
 if (vehicleZone != nullptr) {
 float float6 = 0.5F;
 float float7 = 1.0F;
 float float8 = 0.5F;
 float float9 = 1.0F;
 if (vehicleZone.isPolygon()) {
 for (byte byte3 = 0; byte3 < vehicleZone.points.size(); byte3 += 2) {
 int int10 = vehicleZone.points.get(byte3);
 int int11 = vehicleZone.points.get(byte3 + 1);
 int int12 = vehicleZone.points.get((byte3 + 2) % vehicleZone.points.size());
 int int13 = vehicleZone.points.get((byte3 + 3) % vehicleZone.points.size());
 this->DrawIsoLine(int10, int11, int12, int13, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }
 } else if (vehicleZone.isPolyline()) {
 for (byte byte4 = 0; byte4 < vehicleZone.points.size() - 2; byte4 += 2) {
 int int14 = vehicleZone.points.get(byte4);
 int int15 = vehicleZone.points.get(byte4 + 1);
 int int16 = vehicleZone.points.get(byte4 + 2);
 int int17 = vehicleZone.points.get(byte4 + 3);
 this->DrawIsoLine(int14, int15, int16, int17, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }

 if (vehicleZone.polylineOutlinePoints != nullptr) {
 float[] floats1 = vehicleZone.polylineOutlinePoints;

 for (byte byte5 = 0; byte5 < floats1.length; byte5 += 2) {
 float float10 = floats1[byte5];
 float float11 = floats1[byte5 + 1];
 float float12 = floats1[(byte5 + 2) % floats1.length];
 float float13 = floats1[(byte5 + 3) % floats1.length];
 this->DrawIsoLine(float10, float11, float12, float13, 1.0F, 1.0F, 0.0F, 1.0F, 1);
 }
 }
 } else {
 this->DrawIsoLine(vehicleZone.x, vehicleZone.y, vehicleZone.x + vehicleZone.w, vehicleZone.y, float6, float7, float8, float9, 1);
 this->DrawIsoLine(
 vehicleZone.x,
 vehicleZone.y + vehicleZone.h,
 vehicleZone.x + vehicleZone.w,
 vehicleZone.y + vehicleZone.h,
 float6,
 float7,
 float8,
 float9,
 1
 );
 this->DrawIsoLine(vehicleZone.x, vehicleZone.y, vehicleZone.x, vehicleZone.y + vehicleZone.h, float6, float7, float8, float9, 1);
 this->DrawIsoLine(
 vehicleZone.x + vehicleZone.w,
 vehicleZone.y,
 vehicleZone.x + vehicleZone.w,
 vehicleZone.y + vehicleZone.h,
 float6,
 float7,
 float8,
 float9,
 1
 );
 }
 }

 if (this->RandomSquareInZone.getValue() && zone0 != nullptr) {
 IsoGridSquare square = zone0.getRandomSquareInZone();
 if (square != nullptr) {
 this->paintSquare(square.x, square.y, square.z, 0.0F, 1.0F, 0.0F, 0.5F);
 }
 }
 }

 void drawVehicleStory() {
 std::vector arrayList = IsoWorld.instance.MetaGrid.getZonesIntersecting(this->gridX - 1, this->gridY - 1, this->m_z, 3, 3, new ArrayList<>());
 if (!arrayList.empty()) {
 IsoChunk chunk = IsoWorld.instance.CurrentCell.getChunkForGridSquare(this->gridX, this->gridY, this->m_z);
 if (chunk != nullptr) {
 for (int int0 = 0; int0 < arrayList.size(); int0++) {
 IsoMetaGrid.Zone zone = (IsoMetaGrid.Zone)arrayList.get(int0);
 if ("Nav" == zone.type) {
 VehicleStorySpawner vehicleStorySpawner = VehicleStorySpawner.getInstance();
 RandomizedVehicleStoryBase randomizedVehicleStoryBase = IsoWorld.instance.getRandomizedVehicleStoryByName(this->m_vehicleStory);
 if (randomizedVehicleStoryBase != nullptr
 && randomizedVehicleStoryBase.isValid(zone, chunk, true)
 && randomizedVehicleStoryBase.initVehicleStorySpawner(zone, chunk, true) {
 int int1 = randomizedVehicleStoryBase.getMinZoneWidth();
 int int2 = randomizedVehicleStoryBase.getMinZoneHeight();
 float[] floats = new float[3];
 if (randomizedVehicleStoryBase.getSpawnPoint(zone, chunk, floats) {
 float float0 = floats[0];
 float float1 = floats[1];
 float float2 = floats[2] + (float) (Math.PI / 2);
 vehicleStorySpawner.spawn(float0, float1, 0.0F, float2, (var0, var1x) -> {});
 vehicleStorySpawner.render(float0, float1, 0.0F, int1, int2, floats[2]);
 }
 }
 }
 }
 }
 }
 }

 void DrawBehindStuff() {
 this->IsBehindStuff(IsoCamera.CamCharacter.getCurrentSquare());
 }

 bool IsBehindStuff(IsoGridSquare square) {
 for (int int0 = 1; int0 < 8 && square.getZ() + int0 < 8; int0++) {
 for (int int1 = -5; int1 <= 6; int1++) {
 for (int int2 = -5; int2 <= 6; int2++) {
 if (int2 >= int1 - 5 && int2 <= int1 + 5) {
 this->paintSquare(square.getX() + int2 + int0 * 3, square.getY() + int1 + int0 * 3, square.getZ() + int0, 1.0F, 1.0F, 0.0F, 0.25F);
 }
 }
 }
 }

 return true;
 }

 bool IsBehindStuffRecY(int int0, int int1, int int2) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (int2 >= 15) {
 return false;
 } else {
 this->paintSquare(int0, int1, int2, 1.0F, 1.0F, 0.0F, 0.25F);
 return this->IsBehindStuffRecY(int0, int1 + 1, int2 + 1);
 }
 }

 bool IsBehindStuffRecXY(int int0, int int1, int int2, int int3) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (int2 >= 15) {
 return false;
 } else {
 this->paintSquare(int0, int1, int2, 1.0F, 1.0F, 0.0F, 0.25F);
 return this->IsBehindStuffRecXY(int0 + int3, int1 + int3, int2 + 1, int3);
 }
 }

 bool IsBehindStuffRecX(int int0, int int1, int int2) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, int2);
 if (int2 >= 15) {
 return false;
 } else {
 this->paintSquare(int0, int1, int2, 1.0F, 1.0F, 0.0F, 0.25F);
 return this->IsBehindStuffRecX(int0 + 1, int1, int2 + 1);
 }
 }

 void paintSquare(int int4, int int3, int int2, float float0, float float1, float float2, float float3) {
 int int0 = Core.TileScale;
 int int1 = (int)IsoUtils.XToScreenExact(int4, int3 + 1, int2, 0);
 int int5 = (int)IsoUtils.YToScreenExact(int4, int3 + 1, int2, 0);
 SpriteRenderer.instance
 .renderPoly(
 int1, int5, int1 + 32 * int0, int5 - 16 * int0, int1 + 64 * int0, int5, int1 + 32 * int0, int5 + 16 * int0, float0, float1, float2, float3
 );
 }

 void drawModData() {
 int int0 = this->m_z;
 IsoGridSquare square0 = IsoWorld.instance.getCell().getGridSquare(this->gridX, this->gridY, int0);
 int int1 = Core.getInstance().getScreenWidth() - 250;
 int int2 = 10;
 int int3 = TextManager.instance.getFontFromEnum(this->FONT).getLineHeight();
 if (square0 != nullptr && square0.getModData() != nullptr) {
 KahluaTable table = square0.getModData();
 int int4;
 this->DrawString(int1, int4 = int2 + int3, "MOD DATA x,y,z=" + square0.getX() + "," + square0.getY() + "," + square0.getZ());
 KahluaTableIterator kahluaTableIterator0 = table.iterator();

 while (kahluaTableIterator0.advance()) {
 this->DrawString(int1, int4 += int3, kahluaTableIterator0.getKey().toString() + " = " + kahluaTableIterator0.getValue().toString());
 if (kahluaTableIterator0.getValue() instanceof KahluaTable) {
 KahluaTableIterator kahluaTableIterator1 = ((KahluaTable)kahluaTableIterator0.getValue()).iterator();

 while (kahluaTableIterator1.advance()) {
 this->DrawString(int1 + 8, int4 += int3, kahluaTableIterator1.getKey().toString() + " = " + kahluaTableIterator1.getValue().toString());
 }
 }
 }

 int2 = int4 + int3;
 }

 if (square0 != nullptr) {
 PropertyContainer propertyContainer = square0.getProperties();
 std::vector arrayList = propertyContainer.getPropertyNames();
 if (!arrayList.empty()) {
 this->DrawString(int1, int2 += int3, "PROPERTIES x,y,z=" + square0.getX() + "," + square0.getY() + "," + square0.getZ());
 Collections.sort(arrayList);

 for (auto& string : arrayList) this->DrawString(int1, int2 += int3, string + " = \"" + propertyContainer.Val(string) + "\"");
 }
 }

 for (IsoFlagType flagType : IsoFlagType.values()) {
 if (propertyContainer.Is(flagType) {
 this->DrawString(int1, int2 += int3, flagType.toString());
 }
 }
 }

 if (square0 != nullptr) {
 ErosionData.Square square1 = square0.getErosionData();
 if (square1 != nullptr) {
 int2 += int3;
 int int5;
 this->DrawString(int1, int5 = int2 + int3, "EROSION x,y,z=" + square0.getX() + "," + square0.getY() + "," + square0.getZ());
 this->DrawString(int1, int2 = int5 + int3, "init=" + square1.init);
 int int6;
 this->DrawString(int1, int6 = int2 + int3, "doNothing=" + square1.doNothing);
 this->DrawString(int1, int2 = int6 + int3, "chunk.init=" + square0.chunk.getErosionData().init);
 }
 }
 }

 void drawPlayerInfo() {
 int int0 = Core.getInstance().getScreenWidth() - 250;
 int int1 = Core.getInstance().getScreenHeight() / 2;
 int int2 = TextManager.instance.getFontFromEnum(this->FONT).getLineHeight();
 IsoGameCharacter character = IsoCamera.CamCharacter;
 int int3;
 this->DrawString(int0, int3 = int1 + int2, "bored = " + character.getBodyDamage().getBoredomLevel());
 this->DrawString(int0, int1 = int3 + int2, "endurance = " + character.getStats().endurance);
 int int4;
 this->DrawString(int0, int4 = int1 + int2, "fatigue = " + character.getStats().fatigue);
 this->DrawString(int0, int1 = int4 + int2, "hunger = " + character.getStats().hunger);
 int int5;
 this->DrawString(int0, int5 = int1 + int2, "pain = " + character.getStats().Pain);
 this->DrawString(int0, int1 = int5 + int2, "panic = " + character.getStats().Panic);
 int int6;
 this->DrawString(int0, int6 = int1 + int2, "stress = " + character.getStats().getStress());
 this->DrawString(int0, int1 = int6 + int2, "clothingTemp = " + ((IsoPlayer)character).getPlayerClothingTemperature());
 int int7;
 this->DrawString(int0, int7 = int1 + int2, "temperature = " + character.getTemperature());
 this->DrawString(int0, int1 = int7 + int2, "thirst = " + character.getStats().thirst);
 int int8;
 this->DrawString(int0, int8 = int1 + int2, "foodPoison = " + character.getBodyDamage().getFoodSicknessLevel());
 this->DrawString(int0, int1 = int8 + int2, "poison = " + character.getBodyDamage().getPoisonLevel());
 int int9;
 this->DrawString(int0, int9 = int1 + int2, "unhappy = " + character.getBodyDamage().getUnhappynessLevel());
 this->DrawString(int0, int1 = int9 + int2, "infected = " + character.getBodyDamage().isInfected());
 int int10;
 this->DrawString(int0, int10 = int1 + int2, "InfectionLevel = " + character.getBodyDamage().getInfectionLevel());
 this->DrawString(int0, int1 = int10 + int2, "FakeInfectionLevel = " + character.getBodyDamage().getFakeInfectionLevel());
 int1 += int2;
 int int11;
 this->DrawString(int0, int11 = int1 + int2, "WORLD");
 this->DrawString(int0, int1 = int11 + int2, "globalTemperature = " + IsoWorld.instance.getGlobalTemperature());
 }

 public LosUtil.TestResults lineClearCached(IsoCell cell, int x1, int y1, int z1, int x0, int y0, int z0, boolean bIgnoreDoors) {
 int int0 = y1 - y0;
 int int1 = x1 - x0;
 int int2 = z1 - z0;
 int int3 = int1 + 100;
 int int4 = int0 + 100;
 int int5 = int2 + 16;
 if (int3 >= 0 && int4 >= 0 && int5 >= 0 && int3 < 200 && int4 < 200) {
 LosUtil.TestResults testResults = LosUtil.TestResults.Clear;
 uint8_t byte0 = 1;
 float float0 = 0.5F;
 float float1 = 0.5F;
 IsoGridSquare square0 = cell.getGridSquare(x0, y0, z0);
 if (Math.abs(int1) > Math.abs(int0) && Math.abs(int1) > Math.abs(int2) {
 float float2 = (float)int0 / int1;
 float float3 = (float)int2 / int1;
 float0 += y0;
 float1 += z0;
 int1 = int1 < 0 ? -1 : 1;
 float2 *= int1;
 float3 *= int1;

 while (x0 != x1) {
 x0 += int1;
 float0 += float2;
 float1 += float3;
 IsoGridSquare square1 = cell.getGridSquare(x0, (int)float0, (int)float1);
 this->paintSquare(x0, (int)float0, (int)float1, 1.0F, 1.0F, 1.0F, 0.5F);
 if (square1 != nullptr
 && square0 != nullptr
 && square1.testVisionAdjacent(
 square0.getX() - square1.getX(), square0.getY() - square1.getY(), square0.getZ() - square1.getZ(), true, bIgnoreDoors
 )
 == LosUtil.TestResults.Blocked) {
 this->paintSquare(x0, (int)float0, (int)float1, 1.0F, 0.0F, 0.0F, 0.5F);
 this->paintSquare(square0.getX(), square0.getY(), square0.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
 byte0 = 4;
 }

 square0 = square1;
 int int6 = (int)float0;
 int int7 = (int)float1;
 }
 } else if (Math.abs(int0) >= Math.abs(int1) && Math.abs(int0) > Math.abs(int2) {
 float float4 = (float)int1 / int0;
 float float5 = (float)int2 / int0;
 float0 += x0;
 float1 += z0;
 int0 = int0 < 0 ? -1 : 1;
 float4 *= int0;
 float5 *= int0;

 while (y0 != y1) {
 y0 += int0;
 float0 += float4;
 float1 += float5;
 IsoGridSquare square2 = cell.getGridSquare((int)float0, y0, (int)float1);
 this->paintSquare((int)float0, y0, (int)float1, 1.0F, 1.0F, 1.0F, 0.5F);
 if (square2 != nullptr
 && square0 != nullptr
 && square2.testVisionAdjacent(
 square0.getX() - square2.getX(), square0.getY() - square2.getY(), square0.getZ() - square2.getZ(), true, bIgnoreDoors
 )
 == LosUtil.TestResults.Blocked) {
 this->paintSquare((int)float0, y0, (int)float1, 1.0F, 0.0F, 0.0F, 0.5F);
 this->paintSquare(square0.getX(), square0.getY(), square0.getZ(), 1.0F, 0.0F, 0.0F, 0.5F);
 byte0 = 4;
 }

 square0 = square2;
 int int8 = (int)float0;
 int int9 = (int)float1;
 }
 } else {
 float float6 = (float)int1 / int2;
 float float7 = (float)int0 / int2;
 float0 += x0;
 float1 += y0;
 int2 = int2 < 0 ? -1 : 1;
 float6 *= int2;
 float7 *= int2;

 while (z0 != z1) {
 z0 += int2;
 float0 += float6;
 float1 += float7;
 IsoGridSquare square3 = cell.getGridSquare((int)float0, (int)float1, z0);
 this->paintSquare((int)float0, (int)float1, z0, 1.0F, 1.0F, 1.0F, 0.5F);
 if (square3 != nullptr
 && square0 != nullptr
 && square3.testVisionAdjacent(
 square0.getX() - square3.getX(), square0.getY() - square3.getY(), square0.getZ() - square3.getZ(), true, bIgnoreDoors
 )
 == LosUtil.TestResults.Blocked) {
 byte0 = 4;
 }

 square0 = square3;
 int int10 = (int)float0;
 int int11 = (int)float1;
 }
 }

 if (byte0 == 1) {
 return LosUtil.TestResults.Clear;
 } else if (byte0 == 2) {
 return LosUtil.TestResults.ClearThroughOpenDoor;
 } else if (byte0 == 3) {
 return LosUtil.TestResults.ClearThroughWindow;
 } else {
 return byte0 = = 4 ? LosUtil.TestResults.Blocked : LosUtil.TestResults.Blocked;
 }
 } else {
 return LosUtil.TestResults.Blocked;
 }
 }

 void DrawString(int int3, int int2, const std::string& string) {
 int int0 = TextManager.instance.MeasureStringX(this->FONT, string);
 int int1 = TextManager.instance.getFontFromEnum(this->FONT).getLineHeight();
 SpriteRenderer.instance.renderi(nullptr, int3 - 1, int2, int0 + 2, int1, 0.0F, 0.0F, 0.0F, 0.8F, nullptr);
 TextManager.instance.DrawString(this->FONT, int3, int2, string, 1.0, 1.0, 1.0, 1.0);
 }

 ConfigOption getOptionByName(const std::string& name) {
 for (int int0 = 0; int0 < this->options.size(); int0++) {
 ConfigOption configOption = this->options.get(int0);
 if (configOption.getName() == name) {
 return configOption;
 }
 }

 return nullptr;
 }

 int getOptionCount() {
 return this->options.size();
 }

 ConfigOption getOptionByIndex(int index) {
 return this->options.get(index);
 }

 void setBoolean(const std::string& name, bool value) {
 ConfigOption configOption = this->getOptionByName(name);
 if (configOption instanceof BooleanConfigOption) {
 ((BooleanConfigOption)configOption).setValue(value);
 }
 }

 bool getBoolean(const std::string& name) {
 ConfigOption configOption = this->getOptionByName(name);
 return configOption instanceof BooleanConfigOption ? ((BooleanConfigOption)configOption).getValue() : false;
 }

 void save() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
 ConfigFile configFile = new ConfigFile();
 configFile.write(string, 1, this->options);
 }

 void load() {
 std::string string = ZomboidFileSystem.instance.getCacheDir() + File.separator + "debugChunkState-options.ini";
 ConfigFile configFile = new ConfigFile();
 if (configFile.read(string) {
 for (int int0 = 0; int0 < configFile.getOptions().size(); int0++) {
 ConfigOption configOption0 = configFile.getOptions().get(int0);
 ConfigOption configOption1 = this->getOptionByName(configOption0.getName());
 if (configOption1 != nullptr) {
 configOption1.parse(configOption0.getValueAsString());
 }
 }
 }
 }

 public class BooleanDebugOption extends BooleanConfigOption {
 public BooleanDebugOption(const std::string& string, bool boolean0) {
 super(string, boolean0);
 DebugChunkState.this->options.add(this);
 }
 }

 private class FloodFill {
 IsoGridSquare start = nullptr;
 const int FLOOD_SIZE = 11;
 BooleanGrid visited = new BooleanGrid(11, 11);
 private Stack<IsoGridSquare> stack = std::make_unique<Stack<>>();
 IsoBuilding building = nullptr;
 Mover mover = nullptr;

 void calculate(Mover moverx, IsoGridSquare square) {
 this->start = square;
 this->mover = moverx;
 if (this->start.getRoom() != nullptr) {
 this->building = this->start.getRoom().getBuilding();
 }

 bool boolean0 = false;
 bool boolean1 = false;
 if (this->push(this->start.getX(), this->start.getY())) {
 while ((square = this->pop()) != nullptr) {
 int int0 = square.getX();
 int int1 = square.getY();

 while (this->shouldVisit(int0, int1, int0, int1 - 1) {
 int1--;
 }

 boolean1 = false;
 boolean0 = false;

 do {
 this->visited.setValue(this->gridX(int0), this->gridY(int1), true);
 if (!boolean0 && this->shouldVisit(int0, int1, int0 - 1, int1) {
 if (!this->push(int0 - 1, int1) {
 return;
 }

 boolean0 = true;
 } else if (boolean0 && !this->shouldVisit(int0, int1, int0 - 1, int1) {
 boolean0 = false;
 } else if (boolean0 && !this->shouldVisit(int0 - 1, int1, int0 - 1, int1 - 1) && !this->push(int0 - 1, int1) {
 return;
 }

 if (!boolean1 && this->shouldVisit(int0, int1, int0 + 1, int1) {
 if (!this->push(int0 + 1, int1) {
 return;
 }

 boolean1 = true;
 } else if (boolean1 && !this->shouldVisit(int0, int1, int0 + 1, int1) {
 boolean1 = false;
 } else if (boolean1 && !this->shouldVisit(int0 + 1, int1, int0 + 1, int1 - 1) && !this->push(int0 + 1, int1) {
 return;
 }

 int1++;
 } while (!this->shouldVisit(int0, int1 - 1, int0, int1);
 }
 }
 }

 bool shouldVisit(int int2, int int3, int int0, int int1) {
 if (this->gridX(int0) < 11 && this->gridX(int0) >= 0) {
 if (this->gridY(int1) < 11 && this->gridY(int1) >= 0) {
 if (this->visited.getValue(this->gridX(int0), this->gridY(int1) {
 return false;
 } else {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, this->start.getZ());
 if (square == nullptr) {
 return false;
 } else if (square.Has(IsoObjectType.stairsBN) || square.Has(IsoObjectType.stairsMN) || square.Has(IsoObjectType.stairsTN) {
 return false;
 } else if (square.Has(IsoObjectType.stairsBW) || square.Has(IsoObjectType.stairsMW) || square.Has(IsoObjectType.stairsTW) {
 return false;
 } else if (square.getRoom() != nullptr && this->building == nullptr) {
 return false;
 } else {
 return square.getRoom() == nullptr && this->building != nullptr
 ? false
 : !IsoWorld.instance.CurrentCell.blocked(this->mover, int0, int1, this->start.getZ(), int2, int3, this->start.getZ());
 }
 }
 } else {
 return false;
 }
 } else {
 return false;
 }
 }

 bool push(int int0, int int1) {
 IsoGridSquare square = IsoWorld.instance.CurrentCell.getGridSquare(int0, int1, this->start.getZ());
 this->stack.push(square);
 return true;
 }

 IsoGridSquare pop() {
 return this->stack.empty() ? nullptr : this->stack.pop();
 }

 int gridX(int int0) {
 return int0 - (this->start.getX() - 5);
 }

 int gridY(int int0) {
 return int0 - (this->start.getY() - 5);
 }

 int gridX(IsoGridSquare square) {
 return square.getX() - (this->start.getX() - 5);
 }

 int gridY(IsoGridSquare square) {
 return square.getY() - (this->start.getY() - 5);
 }

 void draw() {
 int int0 = this->start.getX() - 5;
 int int1 = this->start.getY() - 5;

 for (int int2 = 0; int2 < 11; int2++) {
 for (int int3 = 0; int3 < 11; int3++) {
 if (this->visited.getValue(int3, int2) {
 int int4 = (int)IsoUtils.XToScreenExact(int0 + int3, int1 + int2 + 1, this->start.getZ(), 0);
 int int5 = (int)IsoUtils.YToScreenExact(int0 + int3, int1 + int2 + 1, this->start.getZ(), 0);
 SpriteRenderer.instance.renderPoly(int4, int5, int4 + 32, int5 - 16, int4 + 64, int5, int4 + 32, int5 + 16, 1.0F, 1.0F, 0.0F, 0.5F);
 }
 }
 }
 }
 }
}
} // namespace gameStates
} // namespace zombie
