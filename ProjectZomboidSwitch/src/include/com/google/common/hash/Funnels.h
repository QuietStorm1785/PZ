#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/hash/Funnels/ByteArrayFunnel.h"
#include "com/google/common/hash/Funnels/IntegerFunnel.h"
#include "com/google/common/hash/Funnels/LongFunnel.h"
#include "com/google/common/hash/Funnels/SequentialFunnel.h"
#include "com/google/common/hash/Funnels/SinkAsStream.h"
#include "com/google/common/hash/Funnels/StringCharsetFunnel.h"
#include "com/google/common/hash/Funnels/UnencodedCharsFunnel.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace com {
namespace google {
namespace common {
namespace hash {


class Funnels {
public:
    private Funnels() {
   }

   public static Funnel<byte[]> byteArrayFunnel() {
      return ByteArrayFunnel.INSTANCE;
   }

   public static Funnel<CharSequence> unencodedCharsFunnel() {
      return UnencodedCharsFunnel.INSTANCE;
   }

   public static Funnel<CharSequence> stringFunnel(Charset charset) {
      return std::make_shared<StringCharsetFunnel>(charset);
   }

   public static Funnel<int> integerFunnel() {
      return IntegerFunnel.INSTANCE;
   }

   public static <E> Funnel<Iterable<? : public E>> sequentialFunnel(Funnel<E> elementFunnel) {
      return std::make_shared<SequentialFunnel>(elementFunnel);
   }

   public static Funnel<int64_t> longFunnel() {
      return LongFunnel.INSTANCE;
   }

    static OutputStream asOutputStream(PrimitiveSink sink) {
      return std::make_shared<SinkAsStream>(sink);
   }
}
} // namespace hash
} // namespace common
} // namespace google
} // namespace com
