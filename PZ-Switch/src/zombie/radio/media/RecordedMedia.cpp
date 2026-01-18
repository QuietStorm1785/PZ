#include "zombie/radio/media/RecordedMedia.h"

namespace zombie {
namespace radio {
namespace media {

void RecordedMedia::init() {
 // TODO: Implement init
}

uint8_t RecordedMedia::getMediaTypeForCategory(const std::string &category) {
 // TODO: Implement getMediaTypeForCategory
 return 0;
}

MediaData RecordedMedia::register(const std::string &category,
 const std::string &id,
 const std::string &itemDisplayName,
 int spawning) {
 // TODO: Implement register
 return nullptr;
}

MediaData RecordedMedia::getMediaDataFromIndex(short index) {
 // TODO: Implement getMediaDataFromIndex
 return nullptr;
}

short RecordedMedia::getIndexForMediaData(MediaData data) {
 // TODO: Implement getIndexForMediaData
 return 0;
}

MediaData RecordedMedia::getMediaData(const std::string &id) {
 // TODO: Implement getMediaData
 return nullptr;
}

MediaData RecordedMedia::getRandomFromCategory(const std::string &cat) {
 // TODO: Implement getRandomFromCategory
 return nullptr;
}

void RecordedMedia::load() {
 // TODO: Implement load
}

void RecordedMedia::save() {
 // TODO: Implement save
}

std::string RecordedMedia::toAscii(const std::string &string) {
 // TODO: Implement toAscii
 return "";
}

bool RecordedMedia::hasListenedToLine(IsoPlayer player,
 const std::string &guid) {
 // TODO: Implement hasListenedToLine
 return false;
}

bool RecordedMedia::hasListenedToAll(IsoPlayer player, MediaData mediaData) {
 // TODO: Implement hasListenedToAll
 return false;
}

void RecordedMedia::sendRequestData(ByteBuffer bb) {
 // TODO: Implement sendRequestData
}

void RecordedMedia::receiveRequestData(ByteBuffer bb) {
 // TODO: Implement receiveRequestData
}

void RecordedMedia::handleLegacyListenedLines(IsoPlayer player) {
 // TODO: Implement handleLegacyListenedLines
}

int RecordedMedia::compare(MediaData mediaData1, MediaData mediaData0) {
 // TODO: Implement compare
 return 0;
}

} // namespace media
} // namespace radio
} // namespace zombie
