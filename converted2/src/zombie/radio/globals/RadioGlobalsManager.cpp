#include "zombie/radio/globals/RadioGlobalsManager.h"

namespace zombie {
namespace radio {
namespace globals {

RadioGlobalsManager RadioGlobalsManager::getInstance() {
  // TODO: Implement getInstance
  return nullptr;
}

private
RadioGlobalsManager::RadioGlobalsManager() {
  // TODO: Implement RadioGlobalsManager
  return nullptr;
}

void RadioGlobalsManager::reset() {
  // TODO: Implement reset
}

bool RadioGlobalsManager::exists(const std::string &string) {
  // TODO: Implement exists
  return false;
}

RadioGlobalType RadioGlobalsManager::getType(const std::string &string) {
  // TODO: Implement getType
  return nullptr;
}

std::string RadioGlobalsManager::getString(const std::string &string) {
  // TODO: Implement getString
  return "";
}

bool RadioGlobalsManager::addGlobal(const std::string &string,
                                    RadioGlobal radioGlobal) {
  // TODO: Implement addGlobal
  return false;
}

bool RadioGlobalsManager::addGlobalString(const std::string &string0,
                                          const std::string &string1) {
  // TODO: Implement addGlobalString
  return false;
}

bool RadioGlobalsManager::addGlobalBool(const std::string &string,
                                        bool boolean0) {
  // TODO: Implement addGlobalBool
  return false;
}

bool RadioGlobalsManager::addGlobalInt(const std::string &string, int int0) {
  // TODO: Implement addGlobalInt
  return false;
}

bool RadioGlobalsManager::addGlobalFloat(const std::string &string,
                                         float float0) {
  // TODO: Implement addGlobalFloat
  return false;
}

RadioGlobal RadioGlobalsManager::getGlobal(const std::string &string) {
  // TODO: Implement getGlobal
  return nullptr;
}

RadioGlobalString
RadioGlobalsManager::getGlobalString(const std::string &string) {
  // TODO: Implement getGlobalString
  return nullptr;
}

RadioGlobalInt RadioGlobalsManager::getGlobalInt(const std::string &string) {
  // TODO: Implement getGlobalInt
  return nullptr;
}

RadioGlobalFloat
RadioGlobalsManager::getGlobalFloat(const std::string &string) {
  // TODO: Implement getGlobalFloat
  return nullptr;
}

RadioGlobalBool RadioGlobalsManager::getGlobalBool(const std::string &string) {
  // TODO: Implement getGlobalBool
  return nullptr;
}

bool RadioGlobalsManager::setGlobal(const std::string &string,
                                    RadioGlobal radioGlobal1,
                                    EditGlobalOps editGlobalOps) {
  // TODO: Implement setGlobal
  return false;
}

bool RadioGlobalsManager::setGlobal(const std::string &string1,
                                    const std::string &string0) {
  // TODO: Implement setGlobal
  return false;
}

bool RadioGlobalsManager::setGlobal(const std::string &string, int int0) {
  // TODO: Implement setGlobal
  return false;
}

bool RadioGlobalsManager::setGlobal(const std::string &string, float float0) {
  // TODO: Implement setGlobal
  return false;
}

bool RadioGlobalsManager::setGlobal(const std::string &string, bool boolean0) {
  // TODO: Implement setGlobal
  return false;
}

CompareResult RadioGlobalsManager::compare(RadioGlobal radioGlobal0,
                                           RadioGlobal radioGlobal1,
                                           CompareMethod compareMethod) {
  // TODO: Implement compare
  return nullptr;
}

CompareResult RadioGlobalsManager::compare(const std::string &string1,
                                           const std::string &string0,
                                           CompareMethod compareMethod) {
  // TODO: Implement compare
  return nullptr;
}

} // namespace globals
} // namespace radio
} // namespace zombie
