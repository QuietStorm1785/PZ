
// NAMESPACE WRAP BEGIN
namespace zombie {
namespace network {

#include "GameServerWorkshopItems.h"

GameServerWorkshopItems::GameServerWorkshopItems() {}
GameServerWorkshopItems::~GameServerWorkshopItems() {}
// TODO: Implement GameServerWorkshopItems methods from Java

GameServerWorkshopItems::Inner1::Inner1() {}
GameServerWorkshopItems::Inner1::~Inner1() {}
GameServerWorkshopItems::ItemQuery::ItemQuery() {}
GameServerWorkshopItems::ItemQuery::~ItemQuery() {}
GameServerWorkshopItems::WorkshopInstallState::WorkshopInstallState() {}
GameServerWorkshopItems::WorkshopInstallState::~WorkshopInstallState() {}
GameServerWorkshopItems::WorkshopItem::WorkshopItem() {}
GameServerWorkshopItems::WorkshopItem::~WorkshopItem() {}

#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

GameServerWorkshopItems::WorkshopItem::Inner1::Inner1() {}
GameServerWorkshopItems::WorkshopItem::Inner1::~Inner1() {}

int GameServerWorkshopItems::WorkshopItem::Inner1::visitFile(const std::string& path) {
	try {
		if (fs::remove(path)) {
			// File deleted
		} else {
			// File did not exist
		}
	} catch (const fs::filesystem_error& e) {
		// Handle error if needed
		return -1; // TERMINATE or error code
	}
	return 0; // CONTINUE
}

int GameServerWorkshopItems::WorkshopItem::Inner1::postVisitDirectory(const std::string& path) {
	try {
		if (fs::remove(path)) {
			// Directory deleted
		} else {
			// Directory did not exist
		}
	} catch (const fs::filesystem_error& e) {
		// Handle error if needed
		return -1; // TERMINATE or error code
	}
	return 0; // CONTINUE
}
// ================== WorkshopInstallState ==================
// Enum logic is in header; nothing to implement in cpp.

// ================== ItemQuery ==================
bool GameServerWorkshopItems::ItemQuery::isCompleted() const {
	return bCompleted;
}

bool GameServerWorkshopItems::ItemQuery::isNotCompleted() const {
	return bNotCompleted;
}

void GameServerWorkshopItems::ItemQuery::onItemCreated(int64_t /*id*/, bool /*success*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemNotCreated(int /*result*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemUpdated(bool /*success*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemNotUpdated(int /*result*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemSubscribed(int64_t /*id*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemNotSubscribed(int64_t /*id*/, int /*result*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemDownloaded(int64_t /*id*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemNotDownloaded(int64_t /*id*/, int /*result*/) {
	// No-op in Java
}

void GameServerWorkshopItems::ItemQuery::onItemQueryCompleted(int64_t handle, int numResult) {
	GameServerWorkshopItems::noise(std::string("onItemQueryCompleted handle=") + std::to_string(handle) + " numResult=" + std::to_string(numResult));
	if (handle == this->handle) {
		// RemoveCallback(this); // TODO: Implement callback removal if needed
		std::vector<SteamUGCDetails> detailsVec;
		for (int i = 0; i < numResult; ++i) {
			SteamUGCDetails details = SteamWorkshop::instance().GetQueryUGCResult(handle, i);
			// If details is valid, add to vector (simulate Java null check)
			detailsVec.push_back(details);
		}
		this->details = detailsVec;
		// SteamWorkshop::instance().ReleaseQueryUGCRequest(handle); // TODO: Implement if needed
		bCompleted = true;
	}
}

void GameServerWorkshopItems::ItemQuery::onItemQueryNotCompleted(int64_t handle, int result) {
	GameServerWorkshopItems::noise(std::string("onItemQueryNotCompleted handle=") + std::to_string(handle) + " result=" + std::to_string(result));
	if (handle == this->handle) {
		// RemoveCallback(this); // TODO: Implement callback removal if needed
		// SteamWorkshop::instance().ReleaseQueryUGCRequest(handle); // TODO: Implement if needed
		bNotCompleted = true;
	}
}

// ================== WorkshopItem ==================
void GameServerWorkshopItems::WorkshopItem::update() {
	switch (state) {
		case WorkshopInstallState::CheckItemState:
			CheckItemState();
			break;
		case WorkshopInstallState::DownloadPending:
			DownloadPending();
			break;
		case WorkshopInstallState::Ready:
		case WorkshopInstallState::Fail:
		default:
			break;
	}
}

void GameServerWorkshopItems::WorkshopItem::setState(WorkshopInstallState newState) {
	GameServerWorkshopItems::noise("item state " + std::to_string(static_cast<int>(state)) + " -> " + std::to_string(static_cast<int>(newState)) + " ID=" + std::to_string(ID));
	state = newState;
}

void GameServerWorkshopItems::WorkshopItem::CheckItemState() {
	int64_t itemState = SteamWorkshop::instance().GetItemState(ID);
	GameServerWorkshopItems::noise("GetItemState()=" + SteamWorkshopItem::ItemState::toString(itemState) + " ID=" + std::to_string(ID));
	if (SteamWorkshopItem::ItemState::Installed_and(itemState)
		&& details.has_value()
		&& details->getTimeCreated() != 0
		&& details->getTimeUpdated() != SteamWorkshop::instance().GetItemInstallTimeStamp(ID)) {
		GameServerWorkshopItems::noise("Installed status but timeUpdated doesn't match!!!");
		RemoveFolderForReinstall();
		itemState |= SteamWorkshopItem::ItemState::NeedsUpdate_value();
	}
	if (itemState != SteamWorkshopItem::ItemState::None_value() && !SteamWorkshopItem::ItemState::NeedsUpdate_and(itemState)) {
		if (SteamWorkshopItem::ItemState::Installed_and(itemState)) {
			setState(WorkshopInstallState::Ready);
		} else {
			error = "UnknownItemState";
			setState(WorkshopInstallState::Fail);
		}
	} else if (SteamWorkshop::instance().DownloadItem(ID, true, this)) {
		setState(WorkshopInstallState::DownloadPending);
		downloadStartTime = std::chrono::system_clock::now();
	} else {
		error = "DownloadItemFalse";
		setState(WorkshopInstallState::Fail);
	}
}

void GameServerWorkshopItems::WorkshopItem::RemoveFolderForReinstall() {
	std::string folder = SteamWorkshop::instance().GetItemInstallFolder(ID);
	if (folder.empty()) {
		GameServerWorkshopItems::noise("not removing install folder because GetItemInstallFolder() failed ID=" + std::to_string(ID));
		return;
	}
	fs::path p(folder);
	if (!fs::exists(p)) {
		GameServerWorkshopItems::noise("not removing install folder because it does not exist : \"" + folder + "\"");
		return;
	}
	try {
		// Use Inner1 visitor
		Inner1 visitor;
		for (auto& entry : fs::recursive_directory_iterator(p)) {
			if (fs::is_regular_file(entry)) visitor.visitFile(entry.path().string());
		}
		visitor.postVisitDirectory(p.string());
	} catch (const std::exception& e) {
		// Log exception if needed
	}
}

void GameServerWorkshopItems::WorkshopItem::DownloadPending() {
	auto now = std::chrono::system_clock::now();
	auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
	if (downloadQueryTime + 100 <= ms) {
		downloadQueryTime = ms;
		int64_t itemState = SteamWorkshop::instance().GetItemState(ID);
		GameServerWorkshopItems::noise("DownloadPending GetItemState()=" + SteamWorkshopItem::ItemState::toString(itemState) + " ID=" + std::to_string(ID));
		if (SteamWorkshopItem::ItemState::NeedsUpdate_and(itemState)) {
			int64_t progress[2] = {0, 0};
			if (SteamWorkshop::instance().GetItemDownloadInfo(ID, progress)) {
				GameServerWorkshopItems::noise("download " + std::to_string(progress[0]) + "/" + std::to_string(progress[1]) + " ID=" + std::to_string(ID));
			}
		}
	}
}

void GameServerWorkshopItems::WorkshopItem::onItemCreated(int64_t /*id*/, bool /*success*/) {}
void GameServerWorkshopItems::WorkshopItem::onItemNotCreated(int /*result*/) {}
void GameServerWorkshopItems::WorkshopItem::onItemUpdated(bool /*success*/) {}
void GameServerWorkshopItems::WorkshopItem::onItemNotUpdated(int /*result*/) {}

void GameServerWorkshopItems::WorkshopItem::onItemSubscribed(int64_t id) {
	GameServerWorkshopItems::noise("onItemSubscribed itemID=" + std::to_string(id));
}

void GameServerWorkshopItems::WorkshopItem::onItemNotSubscribed(int64_t id, int result) {
	GameServerWorkshopItems::noise("onItemNotSubscribed itemID=" + std::to_string(id) + " result=" + std::to_string(result));
}

void GameServerWorkshopItems::WorkshopItem::onItemDownloaded(int64_t id) {
	GameServerWorkshopItems::noise("onItemDownloaded itemID=" + std::to_string(id) + " time=" + std::to_string(/* TODO: time diff */ 0) + " ms");
	if (id == ID) {
		// SteamWorkshop::instance().RemoveCallback(this); // TODO: Implement if needed
		setState(WorkshopInstallState::CheckItemState);
	}
}

void GameServerWorkshopItems::WorkshopItem::onItemNotDownloaded(int64_t id, int result) {
	GameServerWorkshopItems::noise("onItemNotDownloaded itemID=" + std::to_string(id) + " result=" + std::to_string(result));
	if (id == ID) {
		// SteamWorkshop::instance().RemoveCallback(this); // TODO: Implement if needed
		error = "ItemNotDownloaded";
		setState(WorkshopInstallState::Fail);
	}
}

void GameServerWorkshopItems::WorkshopItem::onItemQueryCompleted(int64_t handle, int numResult) {
	GameServerWorkshopItems::noise("onItemQueryCompleted handle=" + std::to_string(handle) + " numResult=" + std::to_string(numResult));
}

void GameServerWorkshopItems::WorkshopItem::onItemQueryNotCompleted(int64_t handle, int result) {
	GameServerWorkshopItems::noise("onItemQueryNotCompleted handle=" + std::to_string(handle) + " result=" + std::to_string(result));
}

} // namespace network
} // namespace zombie
// NAMESPACE WRAP END
