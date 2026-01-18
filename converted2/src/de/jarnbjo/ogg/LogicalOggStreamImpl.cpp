#include "de/jarnbjo/ogg/LogicalOggStreamImpl.h"

namespace de {
namespace jarnbjo {
namespace ogg {

public
LogicalOggStreamImpl::LogicalOggStreamImpl(PhysicalOggStream physicalOggStream,
                                           int int0) {
  // TODO: Implement LogicalOggStreamImpl
  return nullptr;
}

void LogicalOggStreamImpl::addPageNumberMapping(int int0) {
  // TODO: Implement addPageNumberMapping
}

void LogicalOggStreamImpl::addGranulePosition(long long0) {
  // TODO: Implement addGranulePosition
}

bool LogicalOggStreamImpl::isOpen() {
  // TODO: Implement isOpen
  return false;
}

void LogicalOggStreamImpl::close() {
  // TODO: Implement close
}

long LogicalOggStreamImpl::getMaximumGranulePosition() {
  // TODO: Implement getMaximumGranulePosition
  return 0;
}

void LogicalOggStreamImpl::checkFormat(OggPage oggPage) {
  // TODO: Implement checkFormat
}

std::string LogicalOggStreamImpl::getFormat() {
  // TODO: Implement getFormat
  return "";
}

} // namespace ogg
} // namespace jarnbjo
} // namespace de
