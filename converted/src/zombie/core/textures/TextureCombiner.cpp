#include "zombie/core/textures/TextureCombiner.h"

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

void TextureCombiner::overlay(Texture texture) {
 // TODO: Implement overlay
}

Texture TextureCombiner::combine(Texture texture1, Texture texture0) {
 // TODO: Implement combine
 return nullptr;
}

Texture TextureCombiner::createTexture(int int0, int int1) {
 // TODO: Implement createTexture
 return nullptr;
}

void TextureCombiner::releaseTexture(Texture texture) {
 // TODO: Implement releaseTexture
}

Texture TextureCombiner::combine(ArrayList<TextureCombinerCommand> arrayList0) {
 // TODO: Implement combine
 return nullptr;
}

int TextureCombiner::getResultingHeight(ArrayList<TextureCombinerCommand> arrayList) {
 // TODO: Implement getResultingHeight
 return 0;
}

int TextureCombiner::getResultingWidth(ArrayList<TextureCombinerCommand> arrayList) {
 // TODO: Implement getResultingWidth
 return 0;
}

TextureCombinerCommand TextureCombiner::findDominantCommand(ArrayList<TextureCombinerCommand> arrayList, Comparator<TextureCombinerCommand> comparator) {
 // TODO: Implement findDominantCommand
 return nullptr;
}

void TextureCombiner::createMipMaps(Texture texture) {
 // TODO: Implement createMipMaps
}

} // namespace textures
} // namespace core
} // namespace zombie
