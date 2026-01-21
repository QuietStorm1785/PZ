#include <memory>
#include <string>
#include "com/google/common/hash/Hashing.h"

namespace com {
namespace google {
namespace common {
namespace hash {

HashFunction Hashing::goodFastHash(int minimumBits) {
    // TODO: Implement goodFastHash
    return nullptr;
}

HashFunction Hashing::murmur3_32(int seed) {
    // TODO: Implement murmur3_32
    return nullptr;
}

HashFunction Hashing::murmur3_32() {
    // TODO: Implement murmur3_32
    return nullptr;
}

HashFunction Hashing::murmur3_128(int seed) {
    // TODO: Implement murmur3_128
    return nullptr;
}

HashFunction Hashing::murmur3_128() {
    // TODO: Implement murmur3_128
    return nullptr;
}

HashFunction Hashing::sipHash24() {
    // TODO: Implement sipHash24
    return nullptr;
}

HashFunction Hashing::sipHash24(long k0, long k1) {
    // TODO: Implement sipHash24
    return nullptr;
}

HashFunction Hashing::md5() {
    // TODO: Implement md5
    return nullptr;
}

HashFunction Hashing::sha1() {
    // TODO: Implement sha1
    return nullptr;
}

HashFunction Hashing::sha256() {
    // TODO: Implement sha256
    return nullptr;
}

HashFunction Hashing::sha384() {
    // TODO: Implement sha384
    return nullptr;
}

HashFunction Hashing::sha512() {
    // TODO: Implement sha512
    return nullptr;
}

HashFunction Hashing::hmacMd5(Key key) {
    // TODO: Implement hmacMd5
    return nullptr;
}

HashFunction Hashing::hmacMd5(byte[] key) {
    // TODO: Implement hmacMd5
    return nullptr;
}

return Hashing::hmacMd5(std::make_shared<SecretKeySpec>((byte[]) {
    // TODO: Implement hmacMd5
    return nullptr;
}

HashFunction Hashing::hmacSha1(Key key) {
    // TODO: Implement hmacSha1
    return nullptr;
}

HashFunction Hashing::hmacSha1(byte[] key) {
    // TODO: Implement hmacSha1
    return nullptr;
}

return Hashing::hmacSha1(std::make_shared<SecretKeySpec>((byte[]) {
    // TODO: Implement hmacSha1
    return nullptr;
}

HashFunction Hashing::hmacSha256(Key key) {
    // TODO: Implement hmacSha256
    return nullptr;
}

HashFunction Hashing::hmacSha256(byte[] key) {
    // TODO: Implement hmacSha256
    return nullptr;
}

return Hashing::hmacSha256(std::make_shared<SecretKeySpec>((byte[]) {
    // TODO: Implement hmacSha256
    return nullptr;
}

HashFunction Hashing::hmacSha512(Key key) {
    // TODO: Implement hmacSha512
    return nullptr;
}

HashFunction Hashing::hmacSha512(byte[] key) {
    // TODO: Implement hmacSha512
    return nullptr;
}

return Hashing::hmacSha512(std::make_shared<SecretKeySpec>((byte[]) {
    // TODO: Implement hmacSha512
    return nullptr;
}

std::string Hashing::hmacToString(const std::string& methodName, Key key) {
    // TODO: Implement hmacToString
    return "";
}

HashFunction Hashing::crc32c() {
    // TODO: Implement crc32c
    return nullptr;
}

HashFunction Hashing::crc32() {
    // TODO: Implement crc32
    return nullptr;
}

HashFunction Hashing::adler32() {
    // TODO: Implement adler32
    return nullptr;
}

HashFunction Hashing::checksumHashFunction(ChecksumType type, const std::string& toString) {
    // TODO: Implement checksumHashFunction
    return nullptr;
}

HashFunction Hashing::farmHashFingerprint64() {
    // TODO: Implement farmHashFingerprint64
    return nullptr;
}

int Hashing::consistentHash(HashCode hashCode, int buckets) {
    // TODO: Implement consistentHash
    return 0;
}

return Hashing::consistentHash() {
    // TODO: Implement consistentHash
    return nullptr;
}

int Hashing::consistentHash(long input, int buckets) {
    // TODO: Implement consistentHash
    return 0;
}

HashCode Hashing::combineOrdered(Iterable<HashCode> hashCodes) {
    // TODO: Implement combineOrdered
    return nullptr;
}

HashCode Hashing::combineUnordered(Iterable<HashCode> hashCodes) {
    // TODO: Implement combineUnordered
    return nullptr;
}

int Hashing::checkPositiveAndMakeMultipleOf32(int bits) {
    // TODO: Implement checkPositiveAndMakeMultipleOf32
    return 0;
}

HashFunction Hashing::concatenating(HashFunction first, HashFunction second, HashFunction... rest) {
    // TODO: Implement concatenating
    return nullptr;
}

HashFunction Hashing::concatenating(Iterable<HashFunction> hashFunctions) {
    // TODO: Implement concatenating
    return nullptr;
}

private Hashing::Hashing() {
    // TODO: Implement Hashing
    return nullptr;
}

} // namespace hash
} // namespace common
} // namespace google
} // namespace com
