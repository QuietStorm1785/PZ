#include "zombie/gameStates/ConnectToServerState.h"

namespace zombie {
namespace gameStates {

void ConnectToServerState::noise(const std::string &string) {
  // TODO: Implement noise
}

public
ConnectToServerState::ConnectToServerState(ByteBuffer bb) {
  // TODO: Implement ConnectToServerState
  return nullptr;
}

void ConnectToServerState::enter() {
  // TODO: Implement enter
}

void ConnectToServerState::receiveStartLocation(ByteBuffer byteBuffer) {
  // TODO: Implement receiveStartLocation
}

void ConnectToServerState::receiveServerOptions(ByteBuffer byteBuffer) {
  // TODO: Implement receiveServerOptions
}

void ConnectToServerState::receiveSandboxOptions(ByteBuffer byteBuffer) {
  // TODO: Implement receiveSandboxOptions
}

void ConnectToServerState::receiveGameTime(ByteBuffer byteBuffer) {
  // TODO: Implement receiveGameTime
}

void ConnectToServerState::receiveErosionMain(ByteBuffer byteBuffer) {
  // TODO: Implement receiveErosionMain
}

void ConnectToServerState::receiveGlobalObjects(ByteBuffer byteBuffer) {
  // TODO: Implement receiveGlobalObjects
}

void ConnectToServerState::receiveResetID(ByteBuffer byteBuffer) {
  // TODO: Implement receiveResetID
}

void ConnectToServerState::receiveBerries(ByteBuffer byteBuffer) {
  // TODO: Implement receiveBerries
}

void ConnectToServerState::receiveWorldDictionary(ByteBuffer byteBuffer) {
  // TODO: Implement receiveWorldDictionary
}

void ConnectToServerState::Start() {
  // TODO: Implement Start
}

void ConnectToServerState::TestTCP() {
  // TODO: Implement TestTCP
}

void ConnectToServerState::WorkshopInit() {
  // TODO: Implement WorkshopInit
}

void ConnectToServerState::WorkshopConfirm() {
  // TODO: Implement WorkshopConfirm
}

void ConnectToServerState::WorkshopQuery() {
  // TODO: Implement WorkshopQuery
}

void ConnectToServerState::ServerWorkshopItemScreen() {
  // TODO: Implement ServerWorkshopItemScreen
}

void ConnectToServerState::WorkshopUpdate() {
  // TODO: Implement WorkshopUpdate
}

void ConnectToServerState::CheckMods() {
  // TODO: Implement CheckMods
}

void ConnectToServerState::Finish() {
  // TODO: Implement Finish
}

void ConnectToServerState::FromLua(const std::string &button) {
  // TODO: Implement FromLua
}

void ConnectToServerState::exit() {
  // TODO: Implement exit
}

bool ConnectToServerState::isCompleted() {
  // TODO: Implement isCompleted
  return false;
}

bool ConnectToServerState::isNotCompleted() {
  // TODO: Implement isNotCompleted
  return false;
}

void ConnectToServerState::onItemCreated(long arg0, bool arg1) {
  // TODO: Implement onItemCreated
}

void ConnectToServerState::onItemNotCreated(int arg0) {
  // TODO: Implement onItemNotCreated
}

void ConnectToServerState::onItemUpdated(bool arg0) {
  // TODO: Implement onItemUpdated
}

void ConnectToServerState::onItemNotUpdated(int arg0) {
  // TODO: Implement onItemNotUpdated
}

void ConnectToServerState::onItemSubscribed(long arg0) {
  // TODO: Implement onItemSubscribed
}

void ConnectToServerState::onItemNotSubscribed(long arg0, int arg1) {
  // TODO: Implement onItemNotSubscribed
}

void ConnectToServerState::onItemDownloaded(long arg0) {
  // TODO: Implement onItemDownloaded
}

void ConnectToServerState::onItemNotDownloaded(long arg0, int arg1) {
  // TODO: Implement onItemNotDownloaded
}

void ConnectToServerState::onItemQueryCompleted(long arg0, int arg1) {
  // TODO: Implement onItemQueryCompleted
}

void ConnectToServerState::onItemQueryNotCompleted(long arg0, int arg1) {
  // TODO: Implement onItemQueryNotCompleted
}

void ConnectToServerState::update() {
  // TODO: Implement update
}

void ConnectToServerState::setState(
    ConnectToServerState.WorkshopItemState workshopItemState) {
  // TODO: Implement setState
}

void ConnectToServerState::CheckItemState() {
  // TODO: Implement CheckItemState
}

void ConnectToServerState::SubscribePending() {
  // TODO: Implement SubscribePending
}

void ConnectToServerState::DownloadPending() {
  // TODO: Implement DownloadPending
}

void ConnectToServerState::onItemCreated(long var1, bool var3) {
  // TODO: Implement onItemCreated
}

void ConnectToServerState::onItemNotCreated(int var1) {
  // TODO: Implement onItemNotCreated
}

void ConnectToServerState::onItemUpdated(bool var1) {
  // TODO: Implement onItemUpdated
}

void ConnectToServerState::onItemNotUpdated(int var1) {
  // TODO: Implement onItemNotUpdated
}

void ConnectToServerState::onItemSubscribed(long long0) {
  // TODO: Implement onItemSubscribed
}

void ConnectToServerState::onItemNotSubscribed(long long0, int int0) {
  // TODO: Implement onItemNotSubscribed
}

void ConnectToServerState::onItemDownloaded(long long0) {
  // TODO: Implement onItemDownloaded
}

void ConnectToServerState::onItemNotDownloaded(long long0, int int0) {
  // TODO: Implement onItemNotDownloaded
}

void ConnectToServerState::onItemQueryCompleted(long var1, int var3) {
  // TODO: Implement onItemQueryCompleted
}

void ConnectToServerState::onItemQueryNotCompleted(long var1, int var3) {
  // TODO: Implement onItemQueryNotCompleted
}

} // namespace gameStates
} // namespace zombie
