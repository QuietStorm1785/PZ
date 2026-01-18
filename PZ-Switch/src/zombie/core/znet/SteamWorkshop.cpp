#include "zombie/core/znet/SteamWorkshop.h"

namespace zombie {
namespace core {
namespace znet {

void SteamWorkshop::init() {
 // TODO: Implement init
}

void SteamWorkshop::shutdown() {
 // TODO: Implement shutdown
}

void SteamWorkshop::copyFile(File file0, File file1) {
 // TODO: Implement copyFile
}

void SteamWorkshop::copyFileOrFolder(File file0, File file1) {
 // TODO: Implement copyFileOrFolder
}

void SteamWorkshop::initWorkshopFolder() {
 // TODO: Implement initWorkshopFolder
}

std::string SteamWorkshop::getWorkshopFolder() {
 // TODO: Implement getWorkshopFolder
 return "";
}

bool SteamWorkshop::accept(Path path) {
 // TODO: Implement accept
 return false;
}

bool SteamWorkshop::CreateWorkshopItem(SteamWorkshopItem steamWorkshopItem) {
 // TODO: Implement CreateWorkshopItem
 return false;
}

bool SteamWorkshop::SubmitWorkshopItem(SteamWorkshopItem steamWorkshopItem) {
 // TODO: Implement SubmitWorkshopItem
 return false;
}

bool SteamWorkshop::GetItemUpdateProgress(long[] longs) {
 // TODO: Implement GetItemUpdateProgress
 return false;
}

long SteamWorkshop::GetItemState(long long0) {
 // TODO: Implement GetItemState
 return 0;
}

std::string SteamWorkshop::GetItemInstallFolder(long long0) {
 // TODO: Implement GetItemInstallFolder
 return "";
}

long SteamWorkshop::GetItemInstallTimeStamp(long long0) {
 // TODO: Implement GetItemInstallTimeStamp
 return 0;
}

bool SteamWorkshop::SubscribeItem(
 long long0, ISteamWorkshopCallback iSteamWorkshopCallback) {
 // TODO: Implement SubscribeItem
 return false;
}

bool SteamWorkshop::DownloadItem(
 long long0, bool boolean0, ISteamWorkshopCallback iSteamWorkshopCallback) {
 // TODO: Implement DownloadItem
 return false;
}

bool SteamWorkshop::GetItemDownloadInfo(long long0, long[] longs) {
 // TODO: Implement GetItemDownloadInfo
 return false;
}

long SteamWorkshop::CreateQueryUGCDetailsRequest(
 long[] longs, ISteamWorkshopCallback iSteamWorkshopCallback) {
 // TODO: Implement CreateQueryUGCDetailsRequest
 return 0;
}

SteamUGCDetails SteamWorkshop::GetQueryUGCResult(long long0, int int0) {
 // TODO: Implement GetQueryUGCResult
 return nullptr;
}

bool SteamWorkshop::ReleaseQueryUGCRequest(long long0) {
 // TODO: Implement ReleaseQueryUGCRequest
 return false;
}

void SteamWorkshop::RemoveCallback(
 ISteamWorkshopCallback iSteamWorkshopCallback) {
 // TODO: Implement RemoveCallback
}

std::string
SteamWorkshop::getIDFromItemInstallFolder(const std::string &string0) {
 // TODO: Implement getIDFromItemInstallFolder
 return "";
}

void SteamWorkshop::onItemCreated(long long0, bool boolean0) {
 // TODO: Implement onItemCreated
}

void SteamWorkshop::onItemNotCreated(int int0) {
 // TODO: Implement onItemNotCreated
}

void SteamWorkshop::onItemUpdated(bool boolean0) {
 // TODO: Implement onItemUpdated
}

void SteamWorkshop::onItemNotUpdated(int int0) {
 // TODO: Implement onItemNotUpdated
}

void SteamWorkshop::onItemSubscribed(long long0) {
 // TODO: Implement onItemSubscribed
}

void SteamWorkshop::onItemNotSubscribed(long long0, int int1) {
 // TODO: Implement onItemNotSubscribed
}

void SteamWorkshop::onItemDownloaded(long long0) {
 // TODO: Implement onItemDownloaded
}

void SteamWorkshop::onItemNotDownloaded(long long0, int int1) {
 // TODO: Implement onItemNotDownloaded
}

void SteamWorkshop::onItemQueryCompleted(long long0, int int1) {
 // TODO: Implement onItemQueryCompleted
}

void SteamWorkshop::onItemQueryNotCompleted(long long0, int int1) {
 // TODO: Implement onItemQueryNotCompleted
}

} // namespace znet
} // namespace core
} // namespace zombie
