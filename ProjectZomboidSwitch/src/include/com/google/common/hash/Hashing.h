#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/hash/Hashing/Adler32Holder.h"
#include "com/google/common/hash/Hashing/ChecksumType.h"
#include "com/google/common/hash/Hashing/ConcatenatedHashFunction.h"
#include "com/google/common/hash/Hashing/Crc32Holder.h"
#include "com/google/common/hash/Hashing/Crc32cHolder.h"
#include "com/google/common/hash/Hashing/FarmHashFingerprint64Holder.h"
#include "com/google/common/hash/Hashing/LinearCongruentialGenerator.h"
#include "com/google/common/hash/Hashing/Md5Holder.h"
#include "com/google/common/hash/Hashing/Murmur3_128Holder.h"
#include "com/google/common/hash/Hashing/Murmur3_32Holder.h"
#include "com/google/common/hash/Hashing/Sha1Holder.h"
#include "com/google/common/hash/Hashing/Sha256Holder.h"
#include "com/google/common/hash/Hashing/Sha384Holder.h"
#include "com/google/common/hash/Hashing/Sha512Holder.h"
#include "com/google/common/hash/Hashing/SipHash24Holder.h"
#include "java/security/Key.h"
#include "javax/crypto/spec/SecretKeySpec.h"
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace hash {


class Hashing {
public:
    static const int GOOD_FAST_HASH_SEED = (int)System.currentTimeMillis();

    static HashFunction goodFastHash(int minimumBits) {
    int bits = checkPositiveAndMakeMultipleOf32(minimumBits);
      if (bits == 32) {
         return Murmur3_32Holder.GOOD_FAST_HASH_FUNCTION_32;
      } else if (bits <= 128) {
         return Murmur3_128Holder.GOOD_FAST_HASH_FUNCTION_128;
      } else {
    int hashFunctionsNeeded = (bits + 127) / 128;
         HashFunction[] hashFunctions = new HashFunction[hashFunctionsNeeded];
         hashFunctions[0] = Murmur3_128Holder.GOOD_FAST_HASH_FUNCTION_128;
    int seed = GOOD_FAST_HASH_SEED;

         for (int i = 1; i < hashFunctionsNeeded; i++) {
            seed += 1500450271;
            hashFunctions[i] = murmur3_128(seed);
         }

         return std::make_shared<ConcatenatedHashFunction>(hashFunctions, nullptr);
      }
   }

    static HashFunction murmur3_32(int seed) {
      return std::make_shared<Murmur3_32HashFunction>(seed);
   }

    static HashFunction murmur3_32() {
      return Murmur3_32Holder.MURMUR3_32;
   }

    static HashFunction murmur3_128(int seed) {
      return std::make_shared<Murmur3_128HashFunction>(seed);
   }

    static HashFunction murmur3_128() {
      return Murmur3_128Holder.MURMUR3_128;
   }

    static HashFunction sipHash24() {
      return SipHash24Holder.SIP_HASH_24;
   }

    static HashFunction sipHash24(long k0, long k1) {
      return std::make_shared<SipHashFunction>(2, 4, k0, k1);
   }

    static HashFunction md5() {
      return Md5Holder.MD5;
   }

    static HashFunction sha1() {
      return Sha1Holder.SHA_1;
   }

    static HashFunction sha256() {
      return Sha256Holder.SHA_256;
   }

    static HashFunction sha384() {
      return Sha384Holder.SHA_384;
   }

    static HashFunction sha512() {
      return Sha512Holder.SHA_512;
   }

    static HashFunction hmacMd5(Key key) {
      return std::make_shared<MacHashFunction>("HmacMD5", key, hmacToString("hmacMd5", key));
   }

    static HashFunction hmacMd5(byte[] key) {
    return hmacMd5(std::make_shared<SecretKeySpec>((byte[]);
   }

    static HashFunction hmacSha1(Key key) {
      return std::make_shared<MacHashFunction>("HmacSHA1", key, hmacToString("hmacSha1", key));
   }

    static HashFunction hmacSha1(byte[] key) {
    return hmacSha1(std::make_shared<SecretKeySpec>((byte[]);
   }

    static HashFunction hmacSha256(Key key) {
      return std::make_shared<MacHashFunction>("HmacSHA256", key, hmacToString("hmacSha256", key));
   }

    static HashFunction hmacSha256(byte[] key) {
    return hmacSha256(std::make_shared<SecretKeySpec>((byte[]);
   }

    static HashFunction hmacSha512(Key key) {
      return std::make_shared<MacHashFunction>("HmacSHA512", key, hmacToString("hmacSha512", key));
   }

    static HashFunction hmacSha512(byte[] key) {
    return hmacSha512(std::make_shared<SecretKeySpec>((byte[]);
   }

    static std::string hmacToString(const std::string& methodName, Key key) {
      return std::string.format("Hashing.%s(Key[algorithm=%s, format=%s])", methodName, key.getAlgorithm(), key.getFormat());
   }

    static HashFunction crc32c() {
      return Crc32cHolder.CRC_32_C;
   }

    static HashFunction crc32() {
      return Crc32Holder.CRC_32;
   }

    static HashFunction adler32() {
      return Adler32Holder.ADLER_32;
   }

    static HashFunction checksumHashFunction(ChecksumType type, const std::string& toString) {
      return std::make_shared<ChecksumHashFunction>(type, ChecksumType.access$300(type), toString);
   }

    static HashFunction farmHashFingerprint64() {
      return FarmHashFingerprint64Holder.FARMHASH_FINGERPRINT_64;
   }

    static int consistentHash(HashCode hashCode, int buckets) {
    return consistentHash();
   }

    static int consistentHash(long input, int buckets) {
      Preconditions.checkArgument(buckets > 0, "buckets must be positive: %s", buckets);
    LinearCongruentialGenerator generator = std::make_shared<LinearCongruentialGenerator>(input);
    int candidate = 0;

      while (true) {
    int next = (int)((candidate + 1) / generator.nextDouble());
         if (next < 0 || next >= buckets) {
    return candidate;
         }

         candidate = next;
      }
   }

    static HashCode combineOrdered(Iterable<HashCode> hashCodes) {
      Iterator<HashCode> iterator = hashCodes.iterator();
      Preconditions.checkArgument(iterator.hasNext(), "Must be at least 1 hash code to combine.");
    int bits = iterator.next().bits();
      byte[] resultBytes = new byte[bits / 8];

    for (auto& hashCode : hashCodes)         byte[] nextBytes = hashCode.asBytes();
         Preconditions.checkArgument(nextBytes.length == resultBytes.length, "All hashcodes must have the same bit length.");

         for (int i = 0; i < nextBytes.length; i++) {
            resultBytes[i] = (byte)(resultBytes[i] * 37 ^ nextBytes[i]);
         }
      }

      return HashCode.fromBytesNoCopy(resultBytes);
   }

    static HashCode combineUnordered(Iterable<HashCode> hashCodes) {
      Iterator<HashCode> iterator = hashCodes.iterator();
      Preconditions.checkArgument(iterator.hasNext(), "Must be at least 1 hash code to combine.");
      byte[] resultBytes = new byte[iterator.next().bits() / 8];

    for (auto& hashCode : hashCodes)         byte[] nextBytes = hashCode.asBytes();
         Preconditions.checkArgument(nextBytes.length == resultBytes.length, "All hashcodes must have the same bit length.");

         for (int i = 0; i < nextBytes.length; i++) {
            resultBytes[i] += nextBytes[i];
         }
      }

      return HashCode.fromBytesNoCopy(resultBytes);
   }

    static int checkPositiveAndMakeMultipleOf32(int bits) {
      Preconditions.checkArgument(bits > 0, "Number of bits must be positive");
      return bits + 31 & -32;
   }

    static HashFunction concatenating(HashFunction first, HashFunction second, HashFunction... rest) {
      List<HashFunction> list = std::make_unique<std::vector<>>();
      list.push_back(first);
      list.push_back(second);

    for (auto& hashFunc : rest)         list.push_back(hashFunc);
      }

      return std::make_shared<ConcatenatedHashFunction>(list.toArray(new HashFunction[0]), nullptr);
   }

    static HashFunction concatenating(Iterable<HashFunction> hashFunctions) {
      Preconditions.checkNotNull(hashFunctions);
      List<HashFunction> list = std::make_unique<std::vector<>>();

    for (auto& hashFunction : hashFunctions)         list.push_back(hashFunction);
      }

      Preconditions.checkArgument(list.size() > 0, "number of hash functions (%s) must be > 0", list.size());
      return std::make_shared<ConcatenatedHashFunction>(list.toArray(new HashFunction[0]), nullptr);
   }

    private Hashing() {
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
