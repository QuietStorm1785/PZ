#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoGameCharacter.h"
#include "zombie/characters/IsoPlayer.h"
#include "zombie/core/Core.h"
#include "zombie/iso/IsoCamera/FrameState.h"
#include "zombie/network/GameClient.h"
#include "zombie/network/GameServer.h"
#include "zombie/ui/MoodlesUI.h"
#include "zombie/ui/UIManager.h"

namespace zombie {
namespace iso {


class IsoCamera {
public:
   public static const PlayerCamera[] cameras = new PlayerCamera[4];
    static IsoGameCharacter CamCharacter;
    static Vector2 FakePos;
    static Vector2 FakePosVec;
    static int TargetTileX;
    static int TargetTileY;
    static int PLAYER_OFFSET_X;
    static int PLAYER_OFFSET_Y;
    static const FrameState frameState;

    static void init() {
      PLAYER_OFFSET_Y = -56 / (2 / Core.TileScale);
   }

    static void update() {
    int var0 = IsoPlayer.getPlayerIndex();
      cameras[var0].update();
   }

    static void updateAll() {
      for (int var0 = 0; var0 < 4; var0++) {
    IsoPlayer var1 = IsoPlayer.players[var0];
         if (var1 != nullptr) {
            CamCharacter = var1;
            cameras[var0].update();
         }
      }
   }

    static void SetCharacterToFollow(IsoGameCharacter var0) {
      if (!GameClient.bClient && !GameServer.bServer) {
         CamCharacter = var0;
         if (dynamic_cast<IsoPlayer*>(CamCharacter) != nullptr
            && ((IsoPlayer)CamCharacter).isLocalPlayer()
            && UIManager.getMoodleUI(((IsoPlayer)CamCharacter).getPlayerNum()) != nullptr) {
    int var1 = ((IsoPlayer)CamCharacter).getPlayerNum();
            UIManager.getUI().remove(UIManager.getMoodleUI(var1));
            UIManager.setMoodleUI(var1, std::make_unique<MoodlesUI>());
            UIManager.getMoodleUI(var1).setCharacter(CamCharacter);
            UIManager.getUI().push_back(UIManager.getMoodleUI(var1));
         }
      }
   }

    static float getRightClickOffX() {
      return (int)cameras[IsoPlayer.getPlayerIndex()].RightClickX;
   }

    static float getRightClickOffY() {
      return (int)cameras[IsoPlayer.getPlayerIndex()].RightClickY;
   }

    static float getOffX() {
      return cameras[IsoPlayer.getPlayerIndex()].getOffX();
   }

    static float getTOffX() {
      return cameras[IsoPlayer.getPlayerIndex()].getTOffX();
   }

    static void setOffX(float var0) {
      cameras[IsoPlayer.getPlayerIndex()].OffX = var0;
   }

    static float getOffY() {
      return cameras[IsoPlayer.getPlayerIndex()].getOffY();
   }

    static float getTOffY() {
      return cameras[IsoPlayer.getPlayerIndex()].getTOffY();
   }

    static void setOffY(float var0) {
      cameras[IsoPlayer.getPlayerIndex()].OffY = var0;
   }

    static float getLastOffX() {
      return cameras[IsoPlayer.getPlayerIndex()].getLastOffX();
   }

    static void setLastOffX(float var0) {
      cameras[IsoPlayer.getPlayerIndex()].lastOffX = var0;
   }

    static float getLastOffY() {
      return cameras[IsoPlayer.getPlayerIndex()].getLastOffY();
   }

    static void setLastOffY(float var0) {
      cameras[IsoPlayer.getPlayerIndex()].lastOffY = var0;
   }

    static IsoGameCharacter getCamCharacter() {
    return CamCharacter;
   }

    static void setCamCharacter(IsoGameCharacter var0) {
      CamCharacter = var0;
   }

    static Vector2 getFakePos() {
    return FakePos;
   }

    static void setFakePos(Vector2 var0) {
      FakePos = var0;
   }

    static Vector2 getFakePosVec() {
    return FakePosVec;
   }

    static void setFakePosVec(Vector2 var0) {
      FakePosVec = var0;
   }

    static int getTargetTileX() {
    return TargetTileX;
   }

    static void setTargetTileX(int var0) {
      TargetTileX = var0;
   }

    static int getTargetTileY() {
    return TargetTileY;
   }

    static void setTargetTileY(int var0) {
      TargetTileY = var0;
   }

    static int getScreenLeft(int var0) {
      return var0 != 1 && var0 != 3 ? 0 : Core.getInstance().getScreenWidth() / 2;
   }

    static int getScreenWidth(int var0) {
      return IsoPlayer.numPlayers > 1 ? Core.getInstance().getScreenWidth() / 2 : Core.getInstance().getScreenWidth();
   }

    static int getScreenTop(int var0) {
      return var0 != 2 && var0 != 3 ? 0 : Core.getInstance().getScreenHeight() / 2;
   }

    static int getScreenHeight(int var0) {
      return IsoPlayer.numPlayers > 2 ? Core.getInstance().getScreenHeight() / 2 : Core.getInstance().getScreenHeight();
   }

    static int getOffscreenLeft(int var0) {
      return var0 != 1 && var0 != 3 ? 0 : Core.getInstance().getScreenWidth() / 2;
   }

    static int getOffscreenWidth(int var0) {
      return Core.getInstance().getOffscreenWidth(var0);
   }

    static int getOffscreenTop(int var0) {
      return var0 >= 2 ? Core.getInstance().getScreenHeight() / 2 : 0;
   }

    static int getOffscreenHeight(int var0) {
      return Core.getInstance().getOffscreenHeight(var0);
   }

   static {
      for (int var0 = 0; var0 < cameras.length; var0++) {
         cameras[var0] = std::make_shared<PlayerCamera>(var0);
      }

      CamCharacter = nullptr;
      FakePos = std::make_unique<Vector2>();
      FakePosVec = std::make_unique<Vector2>();
      TargetTileX = 0;
      TargetTileY = 0;
      PLAYER_OFFSET_X = 0;
      PLAYER_OFFSET_Y = -56 / (2 / Core.TileScale);
      frameState = std::make_unique<FrameState>();
   }
}
} // namespace iso
} // namespace zombie
