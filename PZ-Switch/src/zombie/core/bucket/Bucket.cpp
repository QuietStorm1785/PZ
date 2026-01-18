#include "zombie/core/bucket/Bucket.h"

namespace zombie {
namespace core {
namespace bucket {

public
Bucket::Bucket() {
 // TODO: Implement Bucket
 return nullptr;
}

void Bucket::AddTexture(Path path, Texture texture) {
 // TODO: Implement AddTexture
}

void Bucket::AddTexture(const std::string &string, Texture texture) {
 // TODO: Implement AddTexture
}

void Bucket::Dispose() {
 // TODO: Implement Dispose
}

Texture Bucket::getTexture(Path path) {
 // TODO: Implement getTexture
 return nullptr;
}

Texture Bucket::getTexture(const std::string &string) {
 // TODO: Implement getTexture
 return nullptr;
}

bool Bucket::HasTexture(Path path) {
 // TODO: Implement HasTexture
 return false;
}

bool Bucket::HasTexture(const std::string &string) {
 // TODO: Implement HasTexture
 return false;
}

std::string Bucket::getName() {
 // TODO: Implement getName
 return "";
}

void Bucket::setName(const std::string &string) {
 // TODO: Implement setName
}

void Bucket::forgetTexture(const std::string &string) {
 // TODO: Implement forgetTexture
}

} // namespace bucket
} // namespace core
} // namespace zombie
