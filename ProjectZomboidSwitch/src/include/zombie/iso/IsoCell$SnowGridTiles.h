#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/Rand.h"
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace iso {


class IsoCell {
public:
    uint8_t ID;
    int counter;
   private const std::vector<Texture> textures;

   public IsoCell$SnowGridTiles(IsoCell var1, byte var2) {
      this.this$0 = var1;
      this.ID = -1;
      this.counter = -1;
      this.textures = std::make_unique<std::vector<>>();
      this.ID = var2;
   }

    void add(Texture var1) {
      this.textures.push_back(var1);
   }

    Texture getNext() {
      this.counter++;
      if (this.counter >= this.textures.size()) {
         this.counter = 0;
      }

      return this.textures.get(this.counter);
   }

    Texture get(int var1) {
      return this.textures.get(var1);
   }

    int size() {
      return this.textures.size();
   }

    Texture getRand() {
      return this.textures.get(Rand.Next(4));
   }

    bool contains(Texture var1) {
      return this.textures.contains(var1);
   }

    void resetCounter() {
      this.counter = 0;
   }
}
} // namespace iso
} // namespace zombie
