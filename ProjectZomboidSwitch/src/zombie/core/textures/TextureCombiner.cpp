#include <vector>
#include "zombie\core\textures/TextureCombiner.h"

namespace zombie {
namespace core {
namespace textures {

void TextureCombiner::init() {
    // TODO: Implement init
}

void TextureCombiner::combineStart() {
    // TODO: Implement combineStart
}

void TextureCombiner::combineEnd() {
    // TODO: Implement combineEnd
}

void TextureCombiner::clear() {
    // TODO: Implement clear
}

void TextureCombiner::overlay(Texture var1) {
    // TODO: Implement overlay
}

Texture TextureCombiner::combine(Texture var1, Texture var2) {
    // TODO: Implement combine
    return nullptr;
}

CombinerFBO TextureCombiner::getFBO(int var1, int var2) {
    // TODO: Implement getFBO
    return nullptr;
}

Texture TextureCombiner::createTexture(int var1, int var2) {
    // TODO: Implement createTexture
    return nullptr;
}

void TextureCombiner::releaseTexture(Texture var1) {
    // TODO: Implement releaseTexture
}

Texture TextureCombiner::combine(std::vector<TextureCombinerCommand> var1) {
    // TODO: Implement combine
    return nullptr;
}

int TextureCombiner::getResultingHeight(std::vector<TextureCombinerCommand> var0) {
    // TODO: Implement getResultingHeight
    return 0;
}

int TextureCombiner::getResultingWidth(std::vector<TextureCombinerCommand> var0) {
    // TODO: Implement getResultingWidth
    return 0;
}

TextureCombinerCommand TextureCombiner::findDominantCommand(std::vector<TextureCombinerCommand> var0, Comparator<TextureCombinerCommand> var1) {
    // TODO: Implement findDominantCommand
    return nullptr;
}

void TextureCombiner::createMipMaps(Texture var1) {
    // TODO: Implement createMipMaps
}

} // namespace textures
} // namespace core
} // namespace zombie
