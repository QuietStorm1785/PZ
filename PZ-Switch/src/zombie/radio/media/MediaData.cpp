#include "zombie/radio/media/MediaData.h"

namespace zombie {
namespace radio {
namespace media {

public
MediaData::MediaData(const std::string &_id,
 const std::string &_itemDisplayName, int _spawning) {
 // TODO: Implement MediaData
 return nullptr;
}

void MediaData::addLine(const std::string &text, float r, float g, float b,
 const std::string &codes) {
 // TODO: Implement addLine
}

int MediaData::getLineCount() {
 // TODO: Implement getLineCount
 return 0;
}

std::string MediaData::getTranslatedItemDisplayName() {
 // TODO: Implement getTranslatedItemDisplayName
 return "";
}

bool MediaData::hasTitle() {
 // TODO: Implement hasTitle
 return false;
}

void MediaData::setTitle(const std::string &_title) {
 // TODO: Implement setTitle
}

std::string MediaData::getTitleEN() {
 // TODO: Implement getTitleEN
 return "";
}

std::string MediaData::getTranslatedTitle() {
 // TODO: Implement getTranslatedTitle
 return "";
}

bool MediaData::hasSubTitle() {
 // TODO: Implement hasSubTitle
 return false;
}

void MediaData::setSubtitle(const std::string &_subtitle) {
 // TODO: Implement setSubtitle
}

std::string MediaData::getSubtitleEN() {
 // TODO: Implement getSubtitleEN
 return "";
}

std::string MediaData::getTranslatedSubTitle() {
 // TODO: Implement getTranslatedSubTitle
 return "";
}

bool MediaData::hasAuthor() {
 // TODO: Implement hasAuthor
 return false;
}

void MediaData::setAuthor(const std::string &_author) {
 // TODO: Implement setAuthor
}

std::string MediaData::getAuthorEN() {
 // TODO: Implement getAuthorEN
 return "";
}

std::string MediaData::getTranslatedAuthor() {
 // TODO: Implement getTranslatedAuthor
 return "";
}

bool MediaData::hasExtra() {
 // TODO: Implement hasExtra
 return false;
}

void MediaData::setExtra(const std::string &_extra) {
 // TODO: Implement setExtra
}

std::string MediaData::getExtraEN() {
 // TODO: Implement getExtraEN
 return "";
}

std::string MediaData::getTranslatedExtra() {
 // TODO: Implement getTranslatedExtra
 return "";
}

std::string MediaData::getId() {
 // TODO: Implement getId
 return "";
}

short MediaData::getIndex() {
 // TODO: Implement getIndex
 return 0;
}

void MediaData::setIndex(short short0) {
 // TODO: Implement setIndex
}

std::string MediaData::getCategory() {
 // TODO: Implement getCategory
 return "";
}

void MediaData::setCategory(const std::string &string) {
 // TODO: Implement setCategory
}

int MediaData::getSpawning() {
 // TODO: Implement getSpawning
 return 0;
}

uint8_t MediaData::getMediaType() {
 // TODO: Implement getMediaType
 return 0;
}

public
MediaData::MediaLineData(const std::string &_text, float r, float g, float b,
 const std::string &_codes) {
 // TODO: Implement MediaLineData
 return nullptr;
}

std::string MediaData::getTranslatedText() {
 // TODO: Implement getTranslatedText
 return "";
}

Color MediaData::getColor() {
 // TODO: Implement getColor
 return nullptr;
}

float MediaData::getR() {
 // TODO: Implement getR
 return 0;
}

float MediaData::getG() {
 // TODO: Implement getG
 return 0;
}

float MediaData::getB() {
 // TODO: Implement getB
 return 0;
}

std::string MediaData::getCodes() {
 // TODO: Implement getCodes
 return "";
}

std::string MediaData::getTextGuid() {
 // TODO: Implement getTextGuid
 return "";
}

} // namespace media
} // namespace radio
} // namespace zombie
