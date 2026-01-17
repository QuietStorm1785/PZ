#include "de/jarnbjo/ogg/FileStream.h"

namespace de {
namespace jarnbjo {
namespace ogg {

public
FileStream::FileStream(RandomAccessFile randomAccessFile) {
  // TODO: Implement FileStream
  return nullptr;
}

Collection FileStream::getLogicalStreams() {
  // TODO: Implement getLogicalStreams
  return nullptr;
}

bool FileStream::isOpen() {
  // TODO: Implement isOpen
  return false;
}

void FileStream::close() {
  // TODO: Implement close
}

OggPage FileStream::getNextPage() {
  // TODO: Implement getNextPage
  return nullptr;
}

OggPage FileStream::getNextPage(bool boolean0) {
  // TODO: Implement getNextPage
  return nullptr;
}

OggPage FileStream::getOggPage(int int0) {
  // TODO: Implement getOggPage
  return nullptr;
}

LogicalOggStream FileStream::getLogicalStream(int int0) {
  // TODO: Implement getLogicalStream
  return nullptr;
}

void FileStream::setTime(long long0) {
  // TODO: Implement setTime
}

bool FileStream::isSeekable() {
  // TODO: Implement isSeekable
  return false;
}

} // namespace ogg
} // namespace jarnbjo
} // namespace de
