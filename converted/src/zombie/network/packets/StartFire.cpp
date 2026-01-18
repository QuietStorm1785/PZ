#include "zombie/network/packets/StartFire.h"

namespace zombie {
namespace network {
namespace packets {

void StartFire::set(IsoGridSquare squarex, bool boolean0, int int0, int int1, bool boolean1) {
 // TODO: Implement set
}

void StartFire::parse(ByteBuffer byteBuffer, UdpConnection udpConnection) {
 // TODO: Implement parse
}

void StartFire::write(ByteBufferWriter byteBufferWriter) {
 // TODO: Implement write
}

void StartFire::process() {
 // TODO: Implement process
}

bool StartFire::isConsistent() {
 // TODO: Implement isConsistent
 return false;
}

bool StartFire::validate(UdpConnection udpConnection) {
 // TODO: Implement validate
 return false;
}

std::string StartFire::getDescription() {
 // TODO: Implement getDescription
 return "";
}

} // namespace packets
} // namespace network
} // namespace zombie
