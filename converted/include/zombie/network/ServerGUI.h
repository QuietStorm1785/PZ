#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "org/lwjgl/opengl/GL11.h"
#include "org/lwjglx/opengl/Display.h"
#include "org/lwjglx/opengl/DisplayMode.h"
#include "org/lwjglx/opengl/PixelFormat.h"
#include "zombie/GameWindow.h"
#include "zombie/IndieGL.h"
#include "zombie/Lua/LuaEventManager.h"
#include "zombie/WorldSoundManager.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/Core.h"
#include "zombie/core/PerformanceSettings.h"
#include "zombie/core/SpriteRenderer.h"
#include "zombie/core/VBO/GLVertexBufferObject.h"
#include "zombie/core/opengl/RenderThread.h"
#include "zombie/core/physics/WorldSimulation.h"
#include "zombie/core/properties/PropertyContainer.h"
#include "zombie/core/raknet/UdpConnection.h"
#include "zombie/core/textures/ColorInfo.h"
#include "zombie/core/textures/TextureDraw.h"
#include "zombie/core/textures/TexturePackPage.h"
#include "zombie/debug/LineDrawer.h"
#include "zombie/gameStates/MainScreenState.h"
#include "zombie/input/GameKeyboard.h"
#include "zombie/input/Mouse.h"
#include "zombie/iso/IsoCamera.h"
#include "zombie/iso/IsoCell.h"
#include "zombie/iso/IsoChunk.h"
#include "zombie/iso/IsoDirections.h"
#include "zombie/iso/IsoGridSquare.h"
#include "zombie/iso/IsoMovingObject.h"
#include "zombie/iso/IsoObject.h"
#include "zombie/iso/IsoObjectPicker.h"
#include "zombie/iso/IsoUtils.h"
#include "zombie/iso/IsoWorld.h"
#include "zombie/iso/PlayerCamera.h"
#include "zombie/iso/SpriteDetails/IsoFlagType.h"
#include "zombie/iso/SpriteDetails/IsoObjectType.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/iso/objects/IsoBarricade.h"
#include "zombie/iso/objects/IsoCurtain.h"
#include "zombie/iso/objects/IsoDeadBody.h"
#include "zombie/iso/objects/IsoTree.h"
#include "zombie/iso/objects/IsoWindow.h"
#include "zombie/iso/sprite/IsoSprite.h"
#include "zombie/ui/TextManager.h"
#include "zombie/vehicles/BaseVehicle.h"

namespace zombie {
namespace network {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class ServerGUI {
public:
 static bool created;
 static int minX;
 static int minY;
 static int maxX;
 static int maxY;
 static int maxZ;
 private static ArrayList<IsoGridSquare> GridStack = std::make_unique<ArrayList<>>();
 private static ArrayList<IsoGridSquare> MinusFloorCharacters = new ArrayList<>(1000);
 private static ArrayList<IsoGridSquare> SolidFloor = new ArrayList<>(5000);
 private static ArrayList<IsoGridSquare> VegetationCorpses = new ArrayList<>(5000);
 static const ColorInfo defColorInfo = new ColorInfo();

 static bool isCreated() {
 return created;
 }

 static void init() {
 created = true;

 try {
 Display.setFullscreen(false);
 Display.setResizable(false);
 Display.setVSyncEnabled(false);
 Display.setTitle("Project Zomboid Server");
 System.setProperty("org.lwjgl.opengl.Window.undecorated", "false");
 Core.width = 1366;
 Core.height = 768;
 Display.setDisplayMode(new DisplayMode(Core.width, Core.height);
 Display.create(new PixelFormat(32, 0, 24, 8, 0);
 Display.setIcon(MainScreenState.loadIcons());
 GLVertexBufferObject.init();
 Display.makeCurrent();
 SpriteRenderer.instance.create();
 TextManager.instance.Init();

 while (TextManager.instance.font.empty()) {
 GameWindow.fileSystem.updateAsyncTransactions();

 try {
 Thread.sleep(10L);
 } catch (InterruptedException interruptedException) {
 }
 }

 TexturePackPage.bIgnoreWorldItemTextures = true;
 uint8_t byte0 = 2;
 GameWindow.LoadTexturePack("UI", byte0);
 GameWindow.LoadTexturePack("UI2", byte0);
 GameWindow.LoadTexturePack("IconsMoveables", byte0);
 GameWindow.LoadTexturePack("RadioIcons", byte0);
 GameWindow.LoadTexturePack("ApComUI", byte0);
 GameWindow.LoadTexturePack("WeatherFx", byte0);
 TexturePackPage.bIgnoreWorldItemTextures = false;
 byte0 = 0;
 GameWindow.LoadTexturePack("Tiles2x", byte0);
 GameWindow.LoadTexturePack("JumboTrees2x", byte0);
 GameWindow.LoadTexturePack("Overlays2x", byte0);
 GameWindow.LoadTexturePack("Tiles2x.floor", 0);
 GameWindow.DoLoadingText("");
 GameWindow.setTexturePackLookup();
 IsoObjectPicker.Instance.Init();
 Display.makeCurrent();
 GL11.glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
 Display.releaseContext();
 RenderThread.initServerGUI();
 RenderThread.startRendering();
 Core.getInstance().initFBOs();
 } catch (Exception exception) {
 exception.printStackTrace();
 created = false;
 }
 }

 static void init2() {
 if (created) {
 BaseVehicle.LoadAllVehicleTextures();
 }
 }

 static void shutdown() {
 if (created) {
 RenderThread.shutdown();
 }
 }

 static void update() {
 if (created) {
 Mouse.update();
 GameKeyboard.update();
 Display.processMessages();
 if (RenderThread.isCloseRequested()) {
 }

 int int0 = Mouse.getWheelState();
 if (int0 != 0) {
 int int1 = int0 - 0 < 0 ? 1 : -1;
 Core.getInstance().doZoomScroll(0, int1);
 }

 uint8_t byte0 = 0;
 IsoPlayer player = getPlayerToFollow();
 if (player.empty()) {
 Core.getInstance().StartFrame();
 Core.getInstance().EndFrame();
 Core.getInstance().StartFrameUI();
 SpriteRenderer.instance
 .renderi(nullptr, 0, 0, Core.getInstance().getScreenWidth(), Core.getInstance().getScreenHeight(), 0.0F, 0.0F, 0.0F, 1.0F, nullptr);
 Core.getInstance().EndFrameUI();
 } else {
 IsoPlayer.setInstance(player);
 IsoPlayer.players[byte0] = player;
 IsoCamera.CamCharacter = player;
 Core.getInstance().StartFrame(byte0, true);
 renderWorld();
 Core.getInstance().EndFrame(byte0);
 Core.getInstance().RenderOffScreenBuffer();
 Core.getInstance().StartFrameUI();
 renderUI();
 Core.getInstance().EndFrameUI();
 }
 }
 }

 static IsoPlayer getPlayerToFollow() {
 for (int int0 = 0; int0 < GameServer.udpEngine.connections.size(); int0++) {
 UdpConnection udpConnection = GameServer.udpEngine.connections.get(int0);
 if (udpConnection.isFullyConnected()) {
 for (int int1 = 0; int1 < 4; int1++) {
 IsoPlayer player = udpConnection.players[int1];
 if (player != nullptr && player.OnlineID != -1) {
 return player;
 }
 }
 }
 }

 return nullptr;
 }

 static void updateCamera(IsoPlayer player) {
 uint8_t byte0 = 0;
 PlayerCamera playerCamera = IsoCamera.cameras[byte0];
 float float0 = IsoUtils.XToScreen(player.x + playerCamera.DeferedX, player.y + playerCamera.DeferedY, player.z, 0);
 float float1 = IsoUtils.YToScreen(player.x + playerCamera.DeferedX, player.y + playerCamera.DeferedY, player.z, 0);
 float0 -= IsoCamera.getOffscreenWidth(byte0) / 2;
 float1 -= IsoCamera.getOffscreenHeight(byte0) / 2;
 float1 -= player.getOffsetY() * 1.5F;
 float0 += IsoCamera.PLAYER_OFFSET_X;
 float1 += IsoCamera.PLAYER_OFFSET_Y;
 playerCamera.OffX = float0;
 playerCamera.OffY = float1;
 IsoCamera.FrameState frameState = IsoCamera.frameState;
 frameState.Paused = false;
 frameState.playerIndex = byte0;
 frameState.CamCharacter = player;
 frameState.CamCharacterX = IsoCamera.CamCharacter.getX();
 frameState.CamCharacterY = IsoCamera.CamCharacter.getY();
 frameState.CamCharacterZ = IsoCamera.CamCharacter.getZ();
 frameState.CamCharacterSquare = IsoCamera.CamCharacter.getCurrentSquare();
 frameState.CamCharacterRoom = frameState.CamCharacterSquare.empty() ? nullptr : frameState.CamCharacterSquare.getRoom();
 frameState.OffX = IsoCamera.getOffX();
 frameState.OffY = IsoCamera.getOffY();
 frameState.OffscreenWidth = IsoCamera.getOffscreenWidth(byte0);
 frameState.OffscreenHeight = IsoCamera.getOffscreenHeight(byte0);
 }

 static void renderWorld() {
 IsoPlayer player = getPlayerToFollow();
 if (player != nullptr) {
 uint8_t byte0 = 0;
 IsoPlayer.setInstance(player);
 IsoPlayer.players[0] = player;
 IsoCamera.CamCharacter = player;
 updateCamera(player);
 SpriteRenderer.instance.doCoreIntParam(0, IsoCamera.CamCharacter.x);
 SpriteRenderer.instance.doCoreIntParam(1, IsoCamera.CamCharacter.y);
 SpriteRenderer.instance.doCoreIntParam(2, IsoCamera.CamCharacter.z);
 IsoWorld.instance.sceneCullZombies();
 IsoSprite.globalOffsetX = -1.0F;
 uint8_t byte1 = 0;
 uint8_t byte2 = 0;
 int int0 = byte1 + IsoCamera.getOffscreenWidth(byte0);
 int int1 = byte2 + IsoCamera.getOffscreenHeight(byte0);
 float float0 = IsoUtils.XToIso(byte1, byte2, 0.0F);
 float float1 = IsoUtils.YToIso(int0, byte2, 0.0F);
 float float2 = IsoUtils.XToIso(int0, int1, 6.0F);
 float float3 = IsoUtils.YToIso(byte1, int1, 6.0F);
 minY = (int)float1;
 maxY = (int)float3;
 minX = (int)float0;
 maxX = (int)float2;
 minX -= 2;
 minY -= 2;
 maxZ = (int)player.getZ();
 IsoCell cell = IsoWorld.instance.CurrentCell;
 cell.DrawStencilMask();
 IsoObjectPicker.Instance.StartRender();
 RenderTiles();

 for (int int2 = 0; int2 < cell.getObjectList().size(); int2++) {
 IsoMovingObject movingObject = cell.getObjectList().get(int2);
 movingObject.renderlast();
 }

 for (int int3 = 0; int3 < cell.getStaticUpdaterObjectList().size(); int3++) {
 IsoObject object = cell.getStaticUpdaterObjectList().get(int3);
 object.renderlast();
 }

 if (WorldSimulation.instance.created) {
 TextureDraw.GenericDrawer genericDrawer = WorldSimulation.getDrawer(byte0);
 SpriteRenderer.instance.drawGeneric(genericDrawer);
 }

 WorldSoundManager.instance.render();
 LineDrawer.clear();
 }
 }

 static void RenderTiles() {
 IsoCell cell = IsoWorld.instance.CurrentCell;
 if (IsoCell.perPlayerRender[0] == nullptr) {
 IsoCell.perPlayerRender[0] = new IsoCell.PerPlayerRender();
 }

 IsoCell.PerPlayerRender perPlayerRender = IsoCell.perPlayerRender[0];
 if (perPlayerRender.empty()) {
 IsoCell.perPlayerRender[0] = new IsoCell.PerPlayerRender();
 }

 perPlayerRender.setSize(maxX - minX + 1, maxY - minY + 1);
 short[][][] shorts = perPlayerRender.StencilValues;

 for (int int0 = 0; int0 <= maxZ; int0++) {
 GridStack.clear();

 for (int int1 = minY; int1 < maxY; int1++) {
 int int2 = minX;
 IsoGridSquare square0 = ServerMap.instance.getGridSquare(int2, int1, int0);
 int int3 = IsoDirections.E.index();

 while (int2 < maxX) {
 if (int0 == 0) {
 shorts[int2 - minX][int1 - minY][0] = 0;
 shorts[int2 - minX][int1 - minY][1] = 0;
 }

 if (square0 != nullptr && square0.getY() != int1) {
 square0 = nullptr;
 }

 if (square0.empty()) {
 square0 = ServerMap.instance.getGridSquare(int2, int1, int0);
 if (square0.empty()) {
 int2++;
 continue;
 }
 }

 IsoChunk chunk = square0.getChunk();
 if (chunk != nullptr && square0.IsOnScreen()) {
 GridStack.add(square0);
 }

 square0 = square0.nav[int3];
 int2++;
 }
 }

 SolidFloor.clear();
 VegetationCorpses.clear();
 MinusFloorCharacters.clear();

 for (int int4 = 0; int4 < GridStack.size(); int4++) {
 IsoGridSquare square1 = GridStack.get(int4);
 square1.setLightInfoServerGUIOnly(defColorInfo);
 int int5 = renderFloor(square1);
 if (!square1.getStaticMovingObjects().empty()) {
 int5 |= 2;
 }

 for (int int6 = 0; int6 < square1.getMovingObjects().size(); int6++) {
 IsoMovingObject movingObject = square1.getMovingObjects().get(int6);
 bool boolean0 = movingObject.isOnFloor();
 if (boolean0 && movingObject instanceof IsoZombie zombie0) {
 boolean0 = zombie0.bCrawling
 || zombie0.legsSprite.CurrentAnim != nullptr && zombie0.legsSprite.CurrentAnim.name == "ZombieDeath") && zombie0.def.isFinished();
 }

 if (boolean0) {
 int5 |= 2;
 } else {
 int5 |= 4;
 }
 }

 if ((int5 & 1) != 0) {
 SolidFloor.add(square1);
 }

 if ((int5 & 2) != 0) {
 VegetationCorpses.add(square1);
 }

 if ((int5 & 4) != 0) {
 MinusFloorCharacters.add(square1);
 }
 }

 LuaEventManager.triggerEvent("OnPostFloorLayerDraw", int0);

 for (int int7 = 0; int7 < VegetationCorpses.size(); int7++) {
 IsoGridSquare square2 = VegetationCorpses.get(int7);
 renderMinusFloor(square2, false, true);
 renderCharacters(square2, true);
 }

 for (int int8 = 0; int8 < MinusFloorCharacters.size(); int8++) {
 IsoGridSquare square3 = MinusFloorCharacters.get(int8);
 bool boolean1 = renderMinusFloor(square3, false, false);
 renderCharacters(square3, false);
 if (boolean1) {
 renderMinusFloor(square3, true, false);
 }
 }
 }

 MinusFloorCharacters.clear();
 SolidFloor.clear();
 VegetationCorpses.clear();
 }

 static int renderFloor(IsoGridSquare square) {
 uint8_t byte0 = 0;
 uint8_t byte1 = 0;

 for (int int0 = 0; int0 < square.getObjects().size(); int0++) {
 IsoObject object = square.getObjects().get(int0);
 bool boolean0 = true;
 if (object.sprite != nullptr && !object.sprite.Properties.Is(IsoFlagType.solidfloor) {
 boolean0 = false;
 byte0 |= 4;
 }

 if (boolean0) {
 IndieGL.glAlphaFunc(516, 0.0F);
 object.setAlphaAndTarget(byte1, 1.0F);
 object.render(square.x, square.y, square.z, defColorInfo, true, false, nullptr);
 object.renderObjectPicker(square.x, square.y, square.z, defColorInfo);
 if ((object.highlightFlags & 2) != 0) {
 object.highlightFlags &= -2;
 }

 byte0 |= 1;
 }

 if (!boolean0
 && object.sprite != nullptr
 && (object.sprite.Properties.Is(IsoFlagType.canBeRemoved) || object.sprite.Properties.Is(IsoFlagType.attachedFloor) {
 byte0 |= 2;
 }
 }

 return byte0;
 }

 static bool isSpriteOnSouthOrEastWall(IsoObject object) {
 if (object instanceof IsoBarricade) {
 return object.getDir() == IsoDirections.S || object.getDir() == IsoDirections.E;
 } else if (object instanceof IsoCurtain curtain) {
 return curtain.getType() == IsoObjectType.curtainS || curtain.getType() == IsoObjectType.curtainE;
 } else {
 PropertyContainer propertyContainer = object.getProperties();
 return propertyContainer != nullptr && (propertyContainer.Is(IsoFlagType.attachedE) || propertyContainer.Is(IsoFlagType.attachedS);
 }
 }

 static int DoWallLightingN(IsoGridSquare square, IsoObject object, int int0) {
 object.render(square.x, square.y, square.z, defColorInfo, true, false, nullptr);
 return int0;
 }

 static int DoWallLightingW(IsoGridSquare square, IsoObject object, int int0) {
 object.render(square.x, square.y, square.z, defColorInfo, true, false, nullptr);
 return int0;
 }

 static int DoWallLightingNW(IsoGridSquare square, IsoObject object, int int0) {
 object.render(square.x, square.y, square.z, defColorInfo, true, false, nullptr);
 return int0;
 }

 static bool renderMinusFloor(IsoGridSquare square0, bool boolean0, bool boolean4) {
 int int0 = boolean0 ? square0.getObjects().size() - 1 : 0;
 int int1 = boolean0 ? 0 : square0.getObjects().size() - 1;
 int int2 = IsoCamera.frameState.playerIndex;
 IsoGridSquare square1 = IsoCamera.frameState.CamCharacterSquare;
 IsoRoom room = IsoCamera.frameState.CamCharacterRoom;
 int int3 = (int)(IsoUtils.XToScreenInt(square0.x, square0.y, square0.z, 0) - IsoCamera.frameState.OffX);
 int int4 = (int)(IsoUtils.YToScreenInt(square0.x, square0.y, square0.z, 0) - IsoCamera.frameState.OffY);
 bool boolean1 = true;
 IsoCell cell = square0.getCell();
 if (int3 + 32 * Core.TileScale <= cell.StencilX1
 || int3 - 32 * Core.TileScale >= cell.StencilX2
 || int4 + 32 * Core.TileScale <= cell.StencilY1
 || int4 - 96 * Core.TileScale >= cell.StencilY2) {
 boolean1 = false;
 }

 int int5 = 0;
 bool boolean2 = false;

 for (int int6 = int0; boolean0 ? int6 >= int1 : int6 <= int1; int6 += boolean0 ? -1 : 1) {
 IsoObject object = square0.getObjects().get(int6);
 bool boolean3 = true;
 IsoGridSquare.CircleStencil = false;
 if (object.sprite != nullptr && object.sprite.getProperties().Is(IsoFlagType.solidfloor) {
 boolean3 = false;
 }

 if ((
 !boolean4
 || object.sprite.empty()
 || object.sprite.Properties.Is(IsoFlagType.canBeRemoved)
 || object.sprite.Properties.Is(IsoFlagType.attachedFloor)
 )
 && (
 boolean4
 || object.sprite.empty()
 || !object.sprite.Properties.Is(IsoFlagType.canBeRemoved) && !object.sprite.Properties.Is(IsoFlagType.attachedFloor)
 )) {
 if (object.sprite != nullptr
 && (
 object.sprite.getType() == IsoObjectType.WestRoofB
 || object.sprite.getType() == IsoObjectType.WestRoofM
 || object.sprite.getType() == IsoObjectType.WestRoofT
 )
 && square0.z == maxZ
 && square0.z == (int)IsoCamera.CamCharacter.getZ()) {
 boolean3 = false;
 }

 if (IsoCamera.CamCharacter.isClimbing() && object.sprite != nullptr && !object.sprite.getProperties().Is(IsoFlagType.solidfloor) {
 boolean3 = true;
 }

 if (isSpriteOnSouthOrEastWall(object) {
 if (!boolean0) {
 boolean3 = false;
 }

 boolean2 = true;
 } else if (boolean0) {
 boolean3 = false;
 }

 if (boolean3) {
 IndieGL.glAlphaFunc(516, 0.0F);
 if (object.sprite != nullptr
 && !square0.getProperties().Is(IsoFlagType.blueprint)
 && (
 object.sprite.getType() == IsoObjectType.doorFrW
 || object.sprite.getType() == IsoObjectType.doorFrN
 || object.sprite.getType() == IsoObjectType.doorW
 || object.sprite.getType() == IsoObjectType.doorN
 || object.sprite.getProperties().Is(IsoFlagType.cutW)
 || object.sprite.getProperties().Is(IsoFlagType.cutN)
 )
 && PerformanceSettings.LightingFrameSkip < 3) {
 if (object.getTargetAlpha(int2) < 1.0F) {
 bool boolean5 = false;
 if (boolean5) {
 if (object.sprite.getProperties().Is(IsoFlagType.cutW) && square0.getProperties().Is(IsoFlagType.WallSE) {
 IsoGridSquare square2 = square0.nav[IsoDirections.NW.index()];
 if (square2.empty() || square2.getRoom() == nullptr) {
 boolean5 = false;
 }
 } else if (object.sprite.getType() != IsoObjectType.doorFrW
 && object.sprite.getType() != IsoObjectType.doorW
 && !object.sprite.getProperties().Is(IsoFlagType.cutW) {
 if (object.sprite.getType() == IsoObjectType.doorFrN
 || object.sprite.getType() == IsoObjectType.doorN
 || object.sprite.getProperties().Is(IsoFlagType.cutN) {
 IsoGridSquare square3 = square0.nav[IsoDirections.N.index()];
 if (square3.empty() || square3.getRoom() == nullptr) {
 boolean5 = false;
 }
 }
 } else {
 IsoGridSquare square4 = square0.nav[IsoDirections.W.index()];
 if (square4.empty() || square4.getRoom() == nullptr) {
 boolean5 = false;
 }
 }
 }

 if (!boolean5) {
 IsoGridSquare.CircleStencil = boolean1;
 }

 object.setAlphaAndTarget(int2, 1.0F);
 }

 if (object.sprite.getProperties().Is(IsoFlagType.cutW) && object.sprite.getProperties().Is(IsoFlagType.cutN) {
 int5 = DoWallLightingNW(square0, object, int5);
 } else if (object.sprite.getType() == IsoObjectType.doorFrW
 || object.sprite.getType() == IsoObjectType.doorW
 || object.sprite.getProperties().Is(IsoFlagType.cutW) {
 int5 = DoWallLightingW(square0, object, int5);
 } else if (object.sprite.getType() == IsoObjectType.doorFrN
 || object.sprite.getType() == IsoObjectType.doorN
 || object.sprite.getProperties().Is(IsoFlagType.cutN) {
 int5 = DoWallLightingN(square0, object, int5);
 }
 } else {
 if (square1 != nullptr) {
 }

 object.setTargetAlpha(int2, 1.0F);
 if (IsoCamera.CamCharacter != nullptr
 && object.getProperties() != nullptr
 && (object.getProperties().Is(IsoFlagType.solid) || object.getProperties().Is(IsoFlagType.solidtrans) {
 int int7 = square0.getX() - (int)IsoCamera.CamCharacter.getX();
 int int8 = square0.getY() - (int)IsoCamera.CamCharacter.getY();
 if (int7 > 0 && int7 < 3 && int8 >= 0 && int8 < 3 || int8 > 0 && int8 < 3 && int7 >= 0 && int7 < 3) {
 object.setTargetAlpha(int2, 0.99F);
 }
 }

 if (object instanceof IsoWindow && object.getTargetAlpha(int2) < 1.0E-4F) {
 IsoWindow window = (IsoWindow)object;
 IsoGridSquare square5 = window.getOppositeSquare();
 if (square5 != nullptr && square5 != square0 && square5.lighting[int2].bSeen()) {
 object.setTargetAlpha(int2, square5.lighting[int2].darkMulti() * 2.0F);
 }
 }

 if (object instanceof IsoTree) {
 if (boolean1
 && square0.x >= (int)IsoCamera.frameState.CamCharacterX
 && square0.y >= (int)IsoCamera.frameState.CamCharacterY
 && square1 != nullptr
 && square1.Is(IsoFlagType.exterior) {
 ((IsoTree)object).bRenderFlag = true;
 } else {
 ((IsoTree)object).bRenderFlag = false;
 }
 }

 object.render(square0.x, square0.y, square0.z, defColorInfo, true, false, nullptr);
 }

 if (object.sprite != nullptr) {
 object.renderObjectPicker(square0.x, square0.y, square0.z, defColorInfo);
 }

 if ((object.highlightFlags & 2) != 0) {
 object.highlightFlags &= -2;
 }
 }
 }
 }

 return boolean2;
 }

 static void renderCharacters(IsoGridSquare square, bool boolean0) {
 int int0 = square.getStaticMovingObjects().size();

 for (int int1 = 0; int1 < int0; int1++) {
 IsoMovingObject movingObject0 = square.getStaticMovingObjects().get(int1);
 if (movingObject0.sprite != nullptr && (!boolean0 || movingObject0 instanceof IsoDeadBody) && (boolean0 || !(movingObject0 instanceof IsoDeadBody) {
 movingObject0.render(movingObject0.getX(), movingObject0.getY(), movingObject0.getZ(), defColorInfo, true, false, nullptr);
 movingObject0.renderObjectPicker(movingObject0.getX(), movingObject0.getY(), movingObject0.getZ(), defColorInfo);
 }
 }

 int0 = square.getMovingObjects().size();

 for (int int2 = 0; int2 < int0; int2++) {
 IsoMovingObject movingObject1 = square.getMovingObjects().get(int2);
 if (movingObject1 != nullptr && movingObject1.sprite != nullptr) {
 bool boolean1 = movingObject1.isOnFloor();
 if (boolean1 && movingObject1 instanceof IsoZombie zombie0) {
 boolean1 = zombie0.bCrawling
 || zombie0.legsSprite.CurrentAnim != nullptr && zombie0.legsSprite.CurrentAnim.name == "ZombieDeath") && zombie0.def.isFinished();
 }

 if ((!boolean0 || boolean1) && (boolean0 || !boolean1) {
 movingObject1.setAlphaAndTarget(0, 1.0F);
 if (movingObject1 instanceof IsoGameCharacter character) {
 character.renderServerGUI();
 } else {
 movingObject1.render(movingObject1.getX(), movingObject1.getY(), movingObject1.getZ(), defColorInfo, true, false, nullptr);
 }

 movingObject1.renderObjectPicker(movingObject1.getX(), movingObject1.getY(), movingObject1.getZ(), defColorInfo);
 }
 }
 }
 }

 static void renderUI() {
 }
}
} // namespace network
} // namespace zombie
