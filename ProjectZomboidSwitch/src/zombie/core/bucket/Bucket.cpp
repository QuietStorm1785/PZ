#include <string>
#include "zombie/core/bucket/Bucket.h"

namespace zombie {
namespace core {
namespace bucket {

public Bucket::Bucket() {
    // TODO: Implement Bucket
    return nullptr;
}

void Bucket::AddTexture(Path var1, Texture var2) {
    // TODO: Implement AddTexture
}

void Bucket::AddTexture(const std::string& var1, Texture var2) {
    // TODO: Implement AddTexture
}

void Bucket::Dispose() {
    // TODO: Implement Dispose
}

Texture Bucket::getTexture(Path var1) {
    // TODO: Implement getTexture
    return nullptr;
}

Texture Bucket::getTexture(const std::string& var1) {
    // TODO: Implement getTexture
    return nullptr;
}

bool Bucket::HasTexture(Path var1) {
    // TODO: Implement HasTexture
    return false;
}

bool Bucket::HasTexture(const std::string& var1) {
    // TODO: Implement HasTexture
    return false;
}

std::string Bucket::getName() {
    // TODO: Implement getName
    return "";
}

void Bucket::setName(const std::string& var1) {
    // TODO: Implement setName
}

void Bucket::forgetTexture(const std::string& var1) {
    // TODO: Implement forgetTexture
}

} // namespace bucket
} // namespace core
} // namespace zombie
