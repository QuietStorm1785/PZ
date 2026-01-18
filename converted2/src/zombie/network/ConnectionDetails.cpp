#include "zombie/network/ConnectionDetails.h"

namespace zombie {
namespace network {

void ConnectionDetails::write(UdpConnection udpConnection,
                              ServerWorldDatabase.LogonResult logonResult,
                              ByteBuffer byteBuffer) {
  // TODO: Implement write
}

void ConnectionDetails::parse(ByteBuffer byteBuffer) {
  // TODO: Implement parse
}

void ConnectionDetails::writeServerDetails(
    ByteBuffer byteBuffer, UdpConnection udpConnection,
    ServerWorldDatabase.LogonResult logonResult) {
  // TODO: Implement writeServerDetails
}

void ConnectionDetails::writeGameMap(ByteBuffer byteBuffer) {
  // TODO: Implement writeGameMap
}

void ConnectionDetails::writeWorkshopItems(ByteBuffer byteBuffer) {
  // TODO: Implement writeWorkshopItems
}

void ConnectionDetails::writeMods(ByteBuffer byteBuffer) {
  // TODO: Implement writeMods
}

void ConnectionDetails::writeStartLocation(ByteBuffer byteBuffer) {
  // TODO: Implement writeStartLocation
}

void ConnectionDetails::writeServerOptions(ByteBuffer byteBuffer) {
  // TODO: Implement writeServerOptions
}

void ConnectionDetails::writeSandboxOptions(ByteBuffer byteBuffer) {
  // TODO: Implement writeSandboxOptions
}

void ConnectionDetails::writeGameTime(ByteBuffer byteBuffer) {
  // TODO: Implement writeGameTime
}

void ConnectionDetails::writeErosionMain(ByteBuffer byteBuffer) {
  // TODO: Implement writeErosionMain
}

void ConnectionDetails::writeGlobalObjects(ByteBuffer byteBuffer) {
  // TODO: Implement writeGlobalObjects
}

void ConnectionDetails::writeResetID(ByteBuffer byteBuffer) {
  // TODO: Implement writeResetID
}

void ConnectionDetails::writeBerries(ByteBuffer byteBuffer) {
  // TODO: Implement writeBerries
}

void ConnectionDetails::writeWorldDictionary(ByteBuffer byteBuffer) {
  // TODO: Implement writeWorldDictionary
}

} // namespace network
} // namespace zombie
