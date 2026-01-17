#include "zombie/characters/traits/ObservationFactory.h"

namespace zombie {
namespace characters {
namespace traits {

void ObservationFactory::init() {
  // TODO: Implement init
}

void ObservationFactory::setMutualExclusive(const std::string &a,
                                            const std::string &b) {
  // TODO: Implement setMutualExclusive
}

void ObservationFactory::addObservation(const std::string &type,
                                        const std::string &name,
                                        const std::string &desc) {
  // TODO: Implement addObservation
}

public
ObservationFactory::Observation(const std::string &tr, const std::string &_name,
                                const std::string &desc) {
  // TODO: Implement Observation
  return nullptr;
}

std::string ObservationFactory::getLabel() {
  // TODO: Implement getLabel
  return "";
}

std::string ObservationFactory::getLeftLabel() {
  // TODO: Implement getLeftLabel
  return "";
}

std::string ObservationFactory::getRightLabel() {
  // TODO: Implement getRightLabel
  return "";
}

std::string ObservationFactory::getDescription() {
  // TODO: Implement getDescription
  return "";
}

void ObservationFactory::setDescription(const std::string &_description) {
  // TODO: Implement setDescription
}

std::string ObservationFactory::getTraitID() {
  // TODO: Implement getTraitID
  return "";
}

void ObservationFactory::setTraitID(const std::string &_traitID) {
  // TODO: Implement setTraitID
}

std::string ObservationFactory::getName() {
  // TODO: Implement getName
  return "";
}

void ObservationFactory::setName(const std::string &_name) {
  // TODO: Implement setName
}

} // namespace traits
} // namespace characters
} // namespace zombie
