#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "zombie/core/textures/Texture.h"

namespace zombie {
namespace gameStates {


class ChooseGameInfo {
public:
    std::string dir;
    Texture thumb;
    std::string title;
   private std::vector<std::string> lotsDir;
    std::string desc;
    bool bFixed2x;

    std::string getDirectory() {
      return this.dir;
   }

    void setDirectory(const std::string& var1) {
      this.dir = var1;
   }

    Texture getThumbnail() {
      return this.thumb;
   }

    void setThumbnail(Texture var1) {
      this.thumb = var1;
   }

    std::string getTitle() {
      return this.title;
   }

    void setTitle(const std::string& var1) {
      this.title = var1;
   }

   public std::vector<std::string> getLotDirectories() {
      return this.lotsDir;
   }

    std::string getDescription() {
      return this.desc;
   }

    void setDescription(const std::string& var1) {
      this.desc = var1;
   }

    bool isFixed2x() {
      return this.bFixed2x;
   }

    void setFixed2x(bool var1) {
      this.bFixed2x = var1;
   }
}
} // namespace gameStates
} // namespace zombie
