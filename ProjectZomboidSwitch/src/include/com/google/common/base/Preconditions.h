#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"

namespace com {
namespace google {
namespace common {
namespace base {


class Preconditions {
public:
    private Preconditions() {
   }

    static void checkArgument(bool expression) {
      if (!expression) {
         throw std::make_unique<IllegalArgumentException>();
      }
   }

    static void checkArgument(bool expression, @Nullable Object) {
      if (!expression) {
         throw IllegalArgumentException(std::string.valueOf(errorMessage));
      }
   }

    static void checkArgument(bool expression, @Nullable std::string, @Nullable Object...) {
      if (!expression) {
         throw IllegalArgumentException(format(errorMessageTemplate, errorMessageArgs));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, char p1) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, int p1) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, long p1) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, char p1, char p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, char p1, int p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, char p1, long p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, char p1, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, int p1, char p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, int p1, int p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, int p1, long p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, int p1, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, long p1, char p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, long p1, int p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, long p1, long p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, long p1, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object, char p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object, int p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object, long p2) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkArgument(bool b, @Nullable std::string, @Nullable Object, @Nullable Object, @Nullable Object) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2, p3));
      }
   }

   public static void checkArgument(
      boolean b, @Nullable std::string errorMessageTemplate, @Nullable Object p1, @Nullable Object p2, @Nullable Object p3, @Nullable Object p4
   ) {
      if (!b) {
         throw IllegalArgumentException(format(errorMessageTemplate, p1, p2, p3, p4));
      }
   }

    static void checkState(bool expression) {
      if (!expression) {
         throw std::make_unique<IllegalStateException>();
      }
   }

    static void checkState(bool expression, @Nullable Object) {
      if (!expression) {
         throw IllegalStateException(std::string.valueOf(errorMessage));
      }
   }

    static void checkState(bool expression, @Nullable std::string, @Nullable Object...) {
      if (!expression) {
         throw IllegalStateException(format(errorMessageTemplate, errorMessageArgs));
      }
   }

    static void checkState(bool b, @Nullable std::string, char p1) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1));
      }
   }

    static void checkState(bool b, @Nullable std::string, int p1) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1));
      }
   }

    static void checkState(bool b, @Nullable std::string, long p1) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1));
      }
   }

    static void checkState(bool b, @Nullable std::string, char p1, char p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, char p1, int p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, char p1, long p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, char p1, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, int p1, char p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, int p1, int p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, int p1, long p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, int p1, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, long p1, char p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, long p1, int p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, long p1, long p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, long p1, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object, char p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object, int p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object, long p2) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2));
      }
   }

    static void checkState(bool b, @Nullable std::string, @Nullable Object, @Nullable Object, @Nullable Object) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2, p3));
      }
   }

   public static void checkState(
      boolean b, @Nullable std::string errorMessageTemplate, @Nullable Object p1, @Nullable Object p2, @Nullable Object p3, @Nullable Object p4
   ) {
      if (!b) {
         throw IllegalStateException(format(errorMessageTemplate, p1, p2, p3, p4));
      }
   }

   public static <T> T checkNotNull(T reference) {
      if (reference == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
    return reference;
      }
   }

   public static <T> T checkNotNull(T reference, @Nullable Object errorMessage) {
      if (reference == nullptr) {
         throw NullPointerException(std::string.valueOf(errorMessage));
      } else {
    return reference;
      }
   }

   public static <T> T checkNotNull(T reference, @Nullable std::string errorMessageTemplate, @Nullable Object... errorMessageArgs) {
      if (reference == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, errorMessageArgs));
      } else {
    return reference;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, char p1) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, int p1) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, long p1) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, char p1, char p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, char p1, int p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, char p1, long p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, char p1, @Nullable Object p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, int p1, char p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, int p1, int p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, int p1, long p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, int p1, @Nullable Object p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, long p1, char p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, long p1, int p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, long p1, long p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, long p1, @Nullable Object p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, char p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, int p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, long p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, @Nullable Object p2) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, @Nullable Object p2, @Nullable Object p3) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2, p3));
      } else {
    return obj;
      }
   }

   public static <T> T checkNotNull(
      T obj, @Nullable std::string errorMessageTemplate, @Nullable Object p1, @Nullable Object p2, @Nullable Object p3, @Nullable Object p4
   ) {
      if (obj == nullptr) {
         throw NullPointerException(format(errorMessageTemplate, p1, p2, p3, p4));
      } else {
    return obj;
      }
   }

    static int checkElementIndex(int index, int size) {
    return checkElementIndex();
   }

    static int checkElementIndex(int index, int size, @Nullable std::string) {
      if (index >= 0 && index < size) {
    return index;
      } else {
         throw IndexOutOfBoundsException(badElementIndex(index, size, desc));
      }
   }

    static std::string badElementIndex(int index, int size, const std::string& desc) {
      if (index < 0) {
    return format("%s (%s);
      } else if (size < 0) {
         throw IllegalArgumentException("negative size: " + size);
      } else {
    return format("%s (%s);
      }
   }

    static int checkPositionIndex(int index, int size) {
    return checkPositionIndex();
   }

    static int checkPositionIndex(int index, int size, @Nullable std::string) {
      if (index >= 0 && index <= size) {
    return index;
      } else {
         throw IndexOutOfBoundsException(badPositionIndex(index, size, desc));
      }
   }

    static std::string badPositionIndex(int index, int size, const std::string& desc) {
      if (index < 0) {
    return format("%s (%s);
      } else if (size < 0) {
         throw IllegalArgumentException("negative size: " + size);
      } else {
    return format("%s (%s);
      }
   }

    static void checkPositionIndexes(int start, int end, int size) {
      if (start < 0 || end < start || end > size) {
         throw IndexOutOfBoundsException(badPositionIndexes(start, end, size));
      }
   }

    static std::string badPositionIndexes(int start, int end, int size) {
      if (start < 0 || start > size) {
    return badPositionIndex("start index");
      } else {
         return end >= 0 && end <= size
            ? format("end index (%s) must not be less than start index (%s)", end, start)
            : badPositionIndex(end, size, "end index");
      }
   }

    static std::string format(const std::string& template, @Nullable Object...) {
      template = std::string.valueOf(template);
    std::stringstream builder = new std::stringstream(template.length() + 16 * args.length);
    int templateStart = 0;
    int i = 0;

      while (i < args.length) {
    int placeholderStart = template.indexOf("%s", templateStart);
         if (placeholderStart == -1) {
            break;
         }

         builder.append(template, templateStart, placeholderStart);
         builder.append(args[i++]);
         templateStart = placeholderStart + 2;
      }

      builder.append(template, templateStart, template.length());
      if (i < args.length) {
         builder.append(" [");
         builder.append(args[i++]);

         while (i < args.length) {
            builder.append(", ");
            builder.append(args[i++]);
         }

         builder.append(']');
      }

      return builder;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
