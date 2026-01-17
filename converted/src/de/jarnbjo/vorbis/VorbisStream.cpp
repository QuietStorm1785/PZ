#include "de/jarnbjo/vorbis/VorbisStream.h"

namespace de {
namespace jarnbjo {
namespace vorbis {

public
VorbisStream::VorbisStream() {
  // TODO: Implement VorbisStream
  return nullptr;
}

public
VorbisStream::VorbisStream(LogicalOggStream logicalOggStream) {
  // TODO: Implement VorbisStream
  return nullptr;
}

IdentificationHeader VorbisStream::getIdentificationHeader() {
  // TODO: Implement getIdentificationHeader
  return nullptr;
}

CommentHeader VorbisStream::getCommentHeader() {
  // TODO: Implement getCommentHeader
  return nullptr;
}

SetupHeader VorbisStream::getSetupHeader() {
  // TODO: Implement getSetupHeader
  return nullptr;
}

bool VorbisStream::isOpen() {
  // TODO: Implement isOpen
  return false;
}

void VorbisStream::close() {
  // TODO: Implement close
}

int VorbisStream::readPcm(byte[] bytes, int int5, int int4) {
  // TODO: Implement readPcm
  return 0;
}

AudioPacket VorbisStream::getNextAudioPacket() {
  // TODO: Implement getNextAudioPacket
  return nullptr;
}

long VorbisStream::getCurrentGranulePosition() {
  // TODO: Implement getCurrentGranulePosition
  return 0;
}

int VorbisStream::getCurrentBitRate() {
  // TODO: Implement getCurrentBitRate
  return 0;
}

} // namespace vorbis
} // namespace jarnbjo
} // namespace de
