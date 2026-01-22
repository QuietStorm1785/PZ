#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace zombie {
namespace savefile {

class ClientPlayerDB {
public:
    bool isLoaded;
   const byte[][] character;
    std::string username;
    std::string server;
    int playerCount;
   const int[] worldVersion;
   const float[] x;
   const float[] y;
   const float[] z;
   const boolean[] isDead;

   public ClientPlayerDB$NetworkCharacterProfile(ClientPlayerDB var1) {
      this.this$0 = var1;
      this.isLoaded = false;
      this.playerCount = 0;
      this.character = new byte[4][];
      this.worldVersion = new int[4];
      this.x = new float[4];
      this.y = new float[4];
      this.z = new float[4];
      this.isDead = new boolean[4];
   }
}
} // namespace savefile
} // namespace zombie
