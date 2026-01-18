#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/characters/IsoZombie.h"
#include "zombie/core/raknet/UdpConnection.h"
#include <algorithm>

namespace zombie {
namespace popman {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3 using Vineflower.


class NetworkZombieList {
public:
 LinkedList<NetworkZombieList.NetworkZombie> networkZombies = std::make_unique<LinkedList<>>();
 void* lock = new Object();

 public NetworkZombieList.NetworkZombie getNetworkZombie(UdpConnection udpConnection) {
 if (udpConnection.empty()) {
 return nullptr;
 } else {
 for (NetworkZombieList.NetworkZombie networkZombie0 : this->networkZombies) {
 if (networkZombie0.connection == udpConnection) {
 return networkZombie0;
 }
 }

 NetworkZombieList.NetworkZombie networkZombie1 = new NetworkZombieList.NetworkZombie(udpConnection);
 this->networkZombies.add(networkZombie1);
 return networkZombie1;
 }
 }

 public static class NetworkZombie {
 LinkedList<IsoZombie> zombies = std::make_unique<LinkedList<>>();
 const UdpConnection connection;

 public NetworkZombie(UdpConnection udpConnection) {
 this->connection = udpConnection;
 }
 }
}
} // namespace popman
} // namespace zombie
