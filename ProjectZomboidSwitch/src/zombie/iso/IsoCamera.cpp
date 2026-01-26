#include "zombie/iso/IsoCamera.h"

namespace zombie {
namespace iso {

void IsoCamera::init() {
    PLAYER_OFFSET_Y = -56 / (2 / Core::TileScale);
}

void IsoCamera::update() {
    int idx = IsoPlayer::getPlayerIndex();
    cameras[idx]->update();
}

void IsoCamera::updateAll() {
    for (int i = 0; i < 4; ++i) {
        auto player = IsoPlayer::players[i];
        if (player) {
            CamCharacter = player;
            cameras[i]->update();
        }
    }
}

void IsoCamera::SetCharacterToFollow(std::shared_ptr<IsoGameCharacter> character) {
    if (!GameClient::bClient && !GameServer::bServer) {
        CamCharacter = character;
        auto player = std::dynamic_pointer_cast<IsoPlayer>(CamCharacter);
        if (player && player->isLocalPlayer() && UIManager::getMoodleUI(player->getPlayerNum())) {
            int idx = player->getPlayerNum();
            UIManager::getUI()->remove(UIManager::getMoodleUI(idx));
            UIManager::setMoodleUI(idx, std::make_shared<MoodlesUI>());
            UIManager::getMoodleUI(idx)->setCharacter(CamCharacter);
            UIManager::getUI()->push_back(UIManager::getMoodleUI(idx));
        }
    }
}

float IsoCamera::getRightClickOffX() {
    return cameras[IsoPlayer::getPlayerIndex()]->RightClickX;
}

float IsoCamera::getRightClickOffY() {
    return cameras[IsoPlayer::getPlayerIndex()]->RightClickY;
}

float IsoCamera::getOffX() {
    return cameras[IsoPlayer::getPlayerIndex()]->OffX;
}

float IsoCamera::getTOffX() {
    return cameras[IsoPlayer::getPlayerIndex()]->TOffX;
}

void IsoCamera::setOffX(float v) {
    cameras[IsoPlayer::getPlayerIndex()]->OffX = v;
}

float IsoCamera::getOffY() {
    return cameras[IsoPlayer::getPlayerIndex()]->OffY;
}

float IsoCamera::getTOffY() {
    return cameras[IsoPlayer::getPlayerIndex()]->TOffY;
}

void IsoCamera::setOffY(float v) {
    cameras[IsoPlayer::getPlayerIndex()]->OffY = v;
}

float IsoCamera::getLastOffX() {
    return cameras[IsoPlayer::getPlayerIndex()]->lastOffX;
}

void IsoCamera::setLastOffX(float v) {
    cameras[IsoPlayer::getPlayerIndex()]->lastOffX = v;
}

float IsoCamera::getLastOffY() {
    return cameras[IsoPlayer::getPlayerIndex()]->lastOffY;
}

void IsoCamera::setLastOffY(float v) {
    cameras[IsoPlayer::getPlayerIndex()]->lastOffY = v;
}

std::shared_ptr<IsoGameCharacter> IsoCamera::getCamCharacter() {
    return CamCharacter;
}

void IsoCamera::setCamCharacter(std::shared_ptr<IsoGameCharacter> c) {
    CamCharacter = c;
}

std::shared_ptr<Vector2> IsoCamera::getFakePos() {
    return FakePos;
}

void IsoCamera::setFakePos(std::shared_ptr<Vector2> v) {
    FakePos = v;
}

std::shared_ptr<Vector2> IsoCamera::getFakePosVec() {
    return FakePosVec;
}

void IsoCamera::setFakePosVec(std::shared_ptr<Vector2> v) {
    FakePosVec = v;
}

int IsoCamera::getTargetTileX() {
    return TargetTileX;
}

void IsoCamera::setTargetTileX(int v) {
    TargetTileX = v;
}

int IsoCamera::getTargetTileY() {
    return TargetTileY;
}

void IsoCamera::setTargetTileY(int v) {
    TargetTileY = v;
}

int IsoCamera::getScreenLeft(int idx) {
    return (idx != 1 && idx != 3) ? 0 : Core::getInstance()->getScreenWidth() / 2;
}

int IsoCamera::getScreenWidth(int idx) {
    return (IsoPlayer::numPlayers > 1) ? Core::getInstance()->getScreenWidth() / 2 : Core::getInstance()->getScreenWidth();
}

int IsoCamera::getScreenTop(int idx) {
    return (idx != 2 && idx != 3) ? 0 : Core::getInstance()->getScreenHeight() / 2;
}

int IsoCamera::getScreenHeight(int idx) {
    return (IsoPlayer::numPlayers > 2) ? Core::getInstance()->getScreenHeight() / 2 : Core::getInstance()->getScreenHeight();
}

int IsoCamera::getOffscreenLeft(int idx) {
    return (idx != 1 && idx != 3) ? 0 : Core::getInstance()->getScreenWidth() / 2;
}

int IsoCamera::getOffscreenWidth(int idx) {
    return Core::getInstance()->getOffscreenWidth(idx);
}

int IsoCamera::getOffscreenTop(int idx) {
    return (idx >= 2) ? Core::getInstance()->getScreenHeight() / 2 : 0;
}

int IsoCamera::getOffscreenHeight(int idx) {
    return Core::getInstance()->getOffscreenHeight(idx);
}

} // namespace iso
} // namespace zombie
