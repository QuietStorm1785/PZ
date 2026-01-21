#include <string>
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

void SteamWorkshop::copyFile(File var1, File var2) {
    // TODO: Implement copyFile
}

void SteamWorkshop::copyFileOrFolder(File var1, File var2) {
    // TODO: Implement copyFileOrFolder
}

void SteamWorkshop::initWorkshopFolder() {
    // TODO: Implement initWorkshopFolder
}

std::string SteamWorkshop::getWorkshopFolder() {
    // TODO: Implement getWorkshopFolder
    return "";
}

bool SteamWorkshop::CreateWorkshopItem(SteamWorkshopItem var1) {
    // TODO: Implement CreateWorkshopItem
    return false;
}

bool SteamWorkshop::SubmitWorkshopItem(SteamWorkshopItem var1) {
    // TODO: Implement SubmitWorkshopItem
    return false;
}

bool SteamWorkshop::GetItemUpdateProgress(long[] var1) {
    // TODO: Implement GetItemUpdateProgress
    return false;
}

long SteamWorkshop::GetItemState(long var1) {
    // TODO: Implement GetItemState
    return 0;
}

std::string SteamWorkshop::GetItemInstallFolder(long var1) {
    // TODO: Implement GetItemInstallFolder
    return "";
}

long SteamWorkshop::GetItemInstallTimeStamp(long var1) {
    // TODO: Implement GetItemInstallTimeStamp
    return 0;
}

bool SteamWorkshop::SubscribeItem(long var1, ISteamWorkshopCallback var3) {
    // TODO: Implement SubscribeItem
    return false;
}

bool SteamWorkshop::DownloadItem(long var1, bool var3, ISteamWorkshopCallback var4) {
    // TODO: Implement DownloadItem
    return false;
}

bool SteamWorkshop::GetItemDownloadInfo(long var1, long[] var3) {
    // TODO: Implement GetItemDownloadInfo
    return false;
}

long SteamWorkshop::CreateQueryUGCDetailsRequest(long[] var1, ISteamWorkshopCallback var2) {
    // TODO: Implement CreateQueryUGCDetailsRequest
    return 0;
}

SteamUGCDetails SteamWorkshop::GetQueryUGCResult(long var1, int var3) {
    // TODO: Implement GetQueryUGCResult
    return nullptr;
}

bool SteamWorkshop::ReleaseQueryUGCRequest(long var1) {
    // TODO: Implement ReleaseQueryUGCRequest
    return false;
}

void SteamWorkshop::RemoveCallback(ISteamWorkshopCallback var1) {
    // TODO: Implement RemoveCallback
}

std::string SteamWorkshop::getIDFromItemInstallFolder(const std::string& var1) {
    // TODO: Implement getIDFromItemInstallFolder
    return "";
}

void SteamWorkshop::onItemCreated(long var1, bool var3) {
    // TODO: Implement onItemCreated
}

void SteamWorkshop::onItemNotCreated(int var1) {
    // TODO: Implement onItemNotCreated
}

void SteamWorkshop::onItemUpdated(bool var1) {
    // TODO: Implement onItemUpdated
}

void SteamWorkshop::onItemNotUpdated(int var1) {
    // TODO: Implement onItemNotUpdated
}

void SteamWorkshop::onItemSubscribed(long var1) {
    // TODO: Implement onItemSubscribed
}

void SteamWorkshop::onItemNotSubscribed(long var1, int var3) {
    // TODO: Implement onItemNotSubscribed
}

void SteamWorkshop::onItemDownloaded(long var1) {
    // TODO: Implement onItemDownloaded
}

void SteamWorkshop::onItemNotDownloaded(long var1, int var3) {
    // TODO: Implement onItemNotDownloaded
}

void SteamWorkshop::onItemQueryCompleted(long var1, int var3) {
    // TODO: Implement onItemQueryCompleted
}

void SteamWorkshop::onItemQueryNotCompleted(long var1, int var3) {
    // TODO: Implement onItemQueryNotCompleted
}

} // namespace znet
} // namespace core
} // namespace zombie
