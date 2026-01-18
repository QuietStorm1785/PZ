#include "zombie/world/moddata/ModData.h"

namespace zombie {
namespace world {
namespace moddata {

bool ModData::exists(const std::string& tag) {
 // TODO: Implement exists
 return false;
}

KahluaTable ModData::getOrCreate(const std::string& tag) {
 // TODO: Implement getOrCreate
 return nullptr;
}

KahluaTable ModData::get(const std::string& tag) {
 // TODO: Implement get
 return nullptr;
}

std::string ModData::create() {
 // TODO: Implement create
 return "";
}

KahluaTable ModData::create(const std::string& tag) {
 // TODO: Implement create
 return nullptr;
}

KahluaTable ModData::remove(const std::string& tag) {
 // TODO: Implement remove
 return nullptr;
}

void ModData::add(const std::string& tag, KahluaTable table) {
 // TODO: Implement add
}

void ModData::transmit(const std::string& tag) {
 // TODO: Implement transmit
}

void ModData::request(const std::string& tag) {
 // TODO: Implement request
}

} // namespace moddata
} // namespace world
} // namespace zombie
