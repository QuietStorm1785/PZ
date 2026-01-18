#include "zombie/world/ItemInfo.h"

namespace zombie {
namespace world {

std::string ItemInfo::getFullType() {
  // TODO: Implement getFullType
  return "";
}

short ItemInfo::getRegistryID() {
  // TODO: Implement getRegistryID
  return 0;
}

bool ItemInfo::isExistsAsVanilla() {
  // TODO: Implement isExistsAsVanilla
  return false;
}

bool ItemInfo::isModded() {
  // TODO: Implement isModded
  return false;
}

std::string ItemInfo::getModID() {
  // TODO: Implement getModID
  return "";
}

bool ItemInfo::isObsolete() {
  // TODO: Implement isObsolete
  return false;
}

bool ItemInfo::isRemoved() {
  // TODO: Implement isRemoved
  return false;
}

bool ItemInfo::isLoaded() {
  // TODO: Implement isLoaded
  return false;
}

Item ItemInfo::getScriptItem() {
  // TODO: Implement getScriptItem
  return nullptr;
}

ItemInfo ItemInfo::copy() {
  // TODO: Implement copy
  return nullptr;
}

bool ItemInfo::isValid() {
  // TODO: Implement isValid
  return false;
}

void ItemInfo::DebugPrint() {
  // TODO: Implement DebugPrint
}

std::string ItemInfo::GetDebugString() {
  // TODO: Implement GetDebugString
  return "";
}

std::string ItemInfo::ToString() {
  // TODO: Implement ToString
  return "";
}

void ItemInfo::saveAsText(FileWriter fileWriter, const std::string &string0) {
  // TODO: Implement saveAsText
}

void ItemInfo::save(ByteBuffer byteBuffer, List<String> list1,
                    List<String> list0) {
  // TODO: Implement save
}

void ItemInfo::load(ByteBuffer byteBuffer, int var2, List<String> list1,
                    List<String> list0) {
  // TODO: Implement load
}

} // namespace world
} // namespace zombie
