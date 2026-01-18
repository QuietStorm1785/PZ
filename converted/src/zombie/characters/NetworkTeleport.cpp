#include "zombie/characters/NetworkTeleport.h"

namespace zombie {
namespace characters {

public NetworkTeleport::NetworkTeleport(IsoGameCharacter chr, NetworkTeleport.Type type, float x, float y, uint8_t z, float _duration) {
 // TODO: Implement NetworkTeleport
 return nullptr;
}

void NetworkTeleport::process(int playerIndex) {
 // TODO: Implement process
}

void NetworkTeleport::stop(int playerIndex) {
 // TODO: Implement stop
}

bool NetworkTeleport::teleport(IsoGameCharacter chr, NetworkTeleport.Type type, float x, float y, uint8_t z, float _duration) {
 // TODO: Implement teleport
 return false;
}

new NetworkTeleport::NetworkTeleport() {
 // TODO: Implement NetworkTeleport
 return nullptr;
}

bool NetworkTeleport::teleport(IsoGameCharacter chr, PlayerPacket packet, float _duration) {
 // TODO: Implement teleport
 return false;
}

void NetworkTeleport::update(IsoGameCharacter chr, PlayerPacket packet) {
 // TODO: Implement update
}

float NetworkTeleport::getDistance() {
 // TODO: Implement getDistance
 return 0;
}

} // namespace characters
} // namespace zombie
