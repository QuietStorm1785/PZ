#include "zombie/core/properties/PropertyContainer.h"

namespace zombie {
namespace core {
namespace properties {

void PropertyContainer::CreateKeySet() {
 // TODO: Implement CreateKeySet
}

void PropertyContainer::AddProperties(PropertyContainer other) {
 // TODO: Implement AddProperties
}

void PropertyContainer::Clear() {
 // TODO: Implement Clear
}

bool PropertyContainer::Is(IsoFlagType flag) {
 // TODO: Implement Is
 return false;
}

bool PropertyContainer::Is(double flag) {
 // TODO: Implement Is
 return false;
}

void PropertyContainer::Set(const std::string& propName, const std::string& propName2) {
 // TODO: Implement Set
}

void PropertyContainer::Set(const std::string& propName, const std::string& propName2, bool checkIsoFlagType) {
 // TODO: Implement Set
}

void PropertyContainer::Set(IsoFlagType flag) {
 // TODO: Implement Set
}

void PropertyContainer::Set(IsoFlagType flag, const std::string& ignored) {
 // TODO: Implement Set
}

void PropertyContainer::UnSet(const std::string& propName) {
 // TODO: Implement UnSet
}

void PropertyContainer::UnSet(IsoFlagType flag) {
 // TODO: Implement UnSet
}

std::string PropertyContainer::Val(const std::string& property) {
 // TODO: Implement Val
 return "";
}

bool PropertyContainer::Is(const std::string& isoPropertyType) {
 // TODO: Implement Is
 return false;
}

void PropertyContainer::initSurface() {
 // TODO: Implement initSurface
}

int PropertyContainer::getSurface() {
 // TODO: Implement getSurface
 return 0;
}

bool PropertyContainer::isSurfaceOffset() {
 // TODO: Implement isSurfaceOffset
 return false;
}

bool PropertyContainer::isTable() {
 // TODO: Implement isTable
 return false;
}

bool PropertyContainer::isTableTop() {
 // TODO: Implement isTableTop
 return false;
}

int PropertyContainer::getStackReplaceTileOffset() {
 // TODO: Implement getStackReplaceTileOffset
 return 0;
}

int PropertyContainer::getItemHeight() {
 // TODO: Implement getItemHeight
 return 0;
}

public PropertyContainer::ProfileEntryComparitor() {
 // TODO: Implement ProfileEntryComparitor
 return nullptr;
}

int PropertyContainer::compare(void* object0, void* object1) {
 // TODO: Implement compare
 return 0;
}

} // namespace properties
} // namespace core
} // namespace zombie
