#pragma once
#include "zombie/GameTime.h"
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/iso/areas/IsoRoom.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/UIManager.h"
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace iso {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class IsoCamera {
public:
public
 static PlayerCamera[] cameras = new PlayerCamera[4];
 static IsoGameCharacter CamCharacter;
 static Vector2 FakePos;
 static Vector2 FakePosVec;
 static int TargetTileX;
 static int TargetTileY;
 static int PLAYER_OFFSET_X;
 static int PLAYER_OFFSET_Y;
public
 static IsoCamera.FrameState frameState;

 static void init() { PLAYER_OFFSET_Y = -56 / (2 / Core.TileScale); }

 static void update() {
 int int0 = IsoPlayer.getPlayerIndex();
 cameras[int0].update();
 }

 static void updateAll() {
 for (int int0 = 0; int0 < 4; int0++) {
 IsoPlayer player = IsoPlayer.players[int0];
 if (player != nullptr) {
 CamCharacter = player;
 cameras[int0].update();
 }
 }
 }

 static void SetCharacterToFollow(IsoGameCharacter GameChar) {
 if (!GameClient.bClient && !GameServer.bServer) {
 CamCharacter = GameChar;
 if (CamCharacter instanceof
 IsoPlayer && ((IsoPlayer)CamCharacter).isLocalPlayer() &&
 UIManager.getMoodleUI(((IsoPlayer)CamCharacter).getPlayerNum()) !=
 nullptr) {
 int int0 = ((IsoPlayer)CamCharacter).getPlayerNum();
 UIManager.getUI().remove(UIManager.getMoodleUI(int0);
 UIManager.setMoodleUI(int0, std::make_unique<MoodlesUI>());
 UIManager.getMoodleUI(int0).setCharacter(CamCharacter);
 UIManager.getUI().add(UIManager.getMoodleUI(int0);
 }
 }
 }

 static float getRightClickOffX() {
 return (int)cameras[IsoPlayer.getPlayerIndex()].RightClickX;
 }

 static float getRightClickOffY() {
 return (int)cameras[IsoPlayer.getPlayerIndex()].RightClickY;
 }

 /**
 * @return the OffX
 */
 static float getOffX() {
 return cameras[IsoPlayer.getPlayerIndex()].getOffX();
 }

 static float getTOffX() {
 return cameras[IsoPlayer.getPlayerIndex()].getTOffX();
 }

 /**
 *
 * @param aOffX the OffX to set
 */
 static void setOffX(float aOffX) {
 cameras[IsoPlayer.getPlayerIndex()].OffX = aOffX;
 }

 /**
 * @return the OffY
 */
 static float getOffY() {
 return cameras[IsoPlayer.getPlayerIndex()].getOffY();
 }

 static float getTOffY() {
 return cameras[IsoPlayer.getPlayerIndex()].getTOffY();
 }

 /**
 *
 * @param aOffY the OffY to set
 */
 static void setOffY(float aOffY) {
 cameras[IsoPlayer.getPlayerIndex()].OffY = aOffY;
 }

 /**
 * @return the lastOffX
 */
 static float getLastOffX() {
 return cameras[IsoPlayer.getPlayerIndex()].getLastOffX();
 }

 /**
 *
 * @param aLastOffX the lastOffX to set
 */
 static void setLastOffX(float aLastOffX) {
 cameras[IsoPlayer.getPlayerIndex()].lastOffX = aLastOffX;
 }

 /**
 * @return the lastOffY
 */
 static float getLastOffY() {
 return cameras[IsoPlayer.getPlayerIndex()].getLastOffY();
 }

 /**
 *
 * @param aLastOffY the lastOffY to set
 */
 static void setLastOffY(float aLastOffY) {
 cameras[IsoPlayer.getPlayerIndex()].lastOffY = aLastOffY;
 }

 /**
 * @return the CamCharacter
 */
 static IsoGameCharacter getCamCharacter() { return CamCharacter; }

 /**
 *
 * @param aCamCharacter the CamCharacter to set
 */
 static void setCamCharacter(IsoGameCharacter aCamCharacter) {
 CamCharacter = aCamCharacter;
 }

 /**
 * @return the FakePos
 */
 static Vector2 getFakePos() { return FakePos; }

 /**
 *
 * @param aFakePos the FakePos to set
 */
 static void setFakePos(Vector2 aFakePos) { FakePos = aFakePos; }

 /**
 * @return the FakePosVec
 */
 static Vector2 getFakePosVec() { return FakePosVec; }

 /**
 *
 * @param aFakePosVec the FakePosVec to set
 */
 static void setFakePosVec(Vector2 aFakePosVec) { FakePosVec = aFakePosVec; }

 /**
 * @return the TargetTileX
 */
 static int getTargetTileX() { return TargetTileX; }

 /**
 *
 * @param aTargetTileX the TargetTileX to set
 */
 static void setTargetTileX(int aTargetTileX) { TargetTileX = aTargetTileX; }

 /**
 * @return the TargetTileY
 */
 static int getTargetTileY() { return TargetTileY; }

 /**
 *
 * @param aTargetTileY the TargetTileY to set
 */
 static void setTargetTileY(int aTargetTileY) { TargetTileY = aTargetTileY; }

 static int getScreenLeft(int playerIndex) {
 return playerIndex != 1 && playerIndex != 3
 ? 0
 : Core.getInstance().getScreenWidth() / 2;
 }

 static int getScreenWidth(int playerIndex) {
 return IsoPlayer.numPlayers > 1 ? Core.getInstance().getScreenWidth() / 2
 : Core.getInstance().getScreenWidth();
 }

 static int getScreenTop(int playerIndex) {
 return playerIndex != 2 && playerIndex != 3
 ? 0
 : Core.getInstance().getScreenHeight() / 2;
 }

 static int getScreenHeight(int playerIndex) {
 return IsoPlayer.numPlayers > 2 ? Core.getInstance().getScreenHeight() / 2
 : Core.getInstance().getScreenHeight();
 }

 static int getOffscreenLeft(int playerIndex) {
 return playerIndex != 1 && playerIndex != 3
 ? 0
 : Core.getInstance().getScreenWidth() / 2;
 }

 static int getOffscreenWidth(int playerIndex) {
 return Core.getInstance().getOffscreenWidth(playerIndex);
 }

 static int getOffscreenTop(int playerIndex) {
 return playerIndex >= 2 ? Core.getInstance().getScreenHeight() / 2 : 0;
 }

 static int getOffscreenHeight(int playerIndex) {
 return Core.getInstance().getOffscreenHeight(playerIndex);
 }

 static {
 for (int int0 = 0; int0 < cameras.length; int0++) {
 cameras[int0] = new PlayerCamera(int0);
 }

 CamCharacter = nullptr;
 FakePos = std::make_unique<Vector2>();
 FakePosVec = std::make_unique<Vector2>();
 TargetTileX = 0;
 TargetTileY = 0;
 PLAYER_OFFSET_X = 0;
 PLAYER_OFFSET_Y = -56 / (2 / Core.TileScale);
 frameState = new IsoCamera.FrameState();
 }

public
 static class FrameState {
 int frameCount;
 bool Paused;
 int playerIndex;
 float CamCharacterX;
 float CamCharacterY;
 float CamCharacterZ;
 IsoGameCharacter CamCharacter;
 IsoGridSquare CamCharacterSquare;
 IsoRoom CamCharacterRoom;
 float OffX;
 float OffY;
 int OffscreenWidth;
 int OffscreenHeight;

 void set(int _playerIndex) {
 this->Paused = GameTime.isGamePaused();
 this->playerIndex = _playerIndex;
 this->CamCharacter = IsoPlayer.players[_playerIndex];
 this->CamCharacterX = this->CamCharacter.getX();
 this->CamCharacterY = this->CamCharacter.getY();
 this->CamCharacterZ = this->CamCharacter.getZ();
 this->CamCharacterSquare = this->CamCharacter.getCurrentSquare();
 this->CamCharacterRoom = this->CamCharacterSquare.empty()
 ? nullptr
 : this->CamCharacterSquare.getRoom();
 this->OffX = IsoCamera.getOffX();
 this->OffY = IsoCamera.getOffY();
 this->OffscreenWidth = IsoCamera.getOffscreenWidth(_playerIndex);
 this->OffscreenHeight = IsoCamera.getOffscreenHeight(_playerIndex);
 }
 }
}
} // namespace iso
} // namespace zombie
