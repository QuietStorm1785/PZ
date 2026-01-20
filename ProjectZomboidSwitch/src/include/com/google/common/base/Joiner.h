#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Joiner/1.h"
#include "com/google/common/base/Joiner/2.h"
#include "com/google/common/base/Joiner/3.h"
#include "com/google/common/base/Joiner/MapJoiner.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace base {


class Joiner {
public:
    const std::string separator;

    static Joiner on(const std::string& separator) {
      return std::make_shared<Joiner>(separator);
   }

    static Joiner on(char separator) {
      return std::make_shared<Joiner>(std::string.valueOf(separator));
   }

    private Joiner(const std::string& separator) {
      this.separator = (std::string)Preconditions.checkNotNull(separator);
   }

    private Joiner(Joiner prototype) {
      this.separator = prototype.separator;
   }

   public <A : public Appendable> A appendTo(A appendable, Iterable<?> parts) throws IOException {
      return this.appendTo(appendable, parts.iterator());
   }

   public <A : public Appendable> A appendTo(A appendable, Iterator<?> parts) throws IOException {
      Preconditions.checkNotNull(appendable);
      if (parts.hasNext()) {
         appendable.append(this.toString(parts.next()));

         while (parts.hasNext()) {
            appendable.append(this.separator);
            appendable.append(this.toString(parts.next()));
         }
      }

    return appendable;
   }

   public const <A : public Appendable> A appendTo(A appendable, Object[] parts) throws IOException {
      return this.appendTo(appendable, Arrays.asList(parts));
   }

   public const <A : public Appendable> A appendTo(A appendable, @Nullable Object first, @Nullable Object second, Object... rest) throws IOException {
      return this.appendTo(appendable, iterable(first, second, rest));
   }

    std::stringstream appendTo(std::stringstream builder, Iterable<?> parts) {
      return this.appendTo(builder, parts.iterator());
   }

    std::stringstream appendTo(std::stringstream builder, Iterator<?> parts) {
      try {
         this.appendTo(builder, parts);
    return builder;
      } catch (IOException var4) {
         throw AssertionError(var4);
      }
   }

    std::stringstream appendTo(std::stringstream builder, Object[] parts) {
      return this.appendTo(builder, Arrays.asList(parts));
   }

    std::stringstream appendTo(std::stringstream builder, @Nullable Object, @Nullable Object, Object... rest) {
      return this.appendTo(builder, iterable(first, second, rest));
   }

    std::string join(Iterable<?> parts) {
      return this.join(parts.iterator());
   }

    std::string join(Iterator<?> parts) {
      return this.appendTo(std::make_unique<std::stringstream>(), parts);
   }

    std::string join(Object[] parts) {
      return this.join(Arrays.asList(parts));
   }

    std::string join(@Nullable Object, @Nullable Object, Object... rest) {
      return this.join(iterable(first, second, rest));
   }

    Joiner useForNull(const std::string& nullText) {
      Preconditions.checkNotNull(nullText);
      return std::make_shared<1>(this, this, nullText);
   }

    Joiner skipNulls() {
      return std::make_shared<2>(this, this);
   }

    MapJoiner withKeyValueSeparator(char keyValueSeparator) {
      return this.withKeyValueSeparator(std::string.valueOf(keyValueSeparator));
   }

    MapJoiner withKeyValueSeparator(const std::string& keyValueSeparator) {
      return std::make_shared<MapJoiner>(this, keyValueSeparator, nullptr);
   }

    CharSequence toString(void* part) {
      Preconditions.checkNotNull(part);
      return (CharSequence)(dynamic_cast<CharSequence*>(part) != nullptr ? (CharSequence)part : part);
   }

   private static Iterable<Object> iterable(Object first, Object second, Object[] rest) {
      Preconditions.checkNotNull(rest);
      return std::make_shared<3>(rest, first, second);
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
