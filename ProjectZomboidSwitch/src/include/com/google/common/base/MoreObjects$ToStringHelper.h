#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/MoreObjects/ToStringHelper/ValueHolder.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace base {


class MoreObjects {
public:
    const std::string className;
    const ValueHolder holderHead = std::make_shared<ValueHolder>(nullptr);
    ValueHolder holderTail = this.holderHead;
    bool omitNullValues = false;

   private MoreObjects$ToStringHelper(std::string className) {
      this.className = (std::string)Preconditions.checkNotNull(className);
   }

   public MoreObjects$ToStringHelper omitNullValues() {
      this.omitNullValues = true;
    return this;
   }

   public MoreObjects$ToStringHelper add(std::string name, @Nullable Object value) {
      return this.addHolder(name, value);
   }

   public MoreObjects$ToStringHelper add(std::string name, boolean value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper add(std::string name, char value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper add(std::string name, double value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper add(std::string name, float value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper add(std::string name, int value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper add(std::string name, long value) {
      return this.addHolder(name, std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(@Nullable Object value) {
      return this.addHolder(value);
   }

   public MoreObjects$ToStringHelper addValue(boolean value) {
      return this.addHolder(std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(char value) {
      return this.addHolder(std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(double value) {
      return this.addHolder(std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(float value) {
      return this.addHolder(std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(int value) {
      return this.addHolder(std::string.valueOf(value));
   }

   public MoreObjects$ToStringHelper addValue(long value) {
      return this.addHolder(std::string.valueOf(value));
   }

    std::string toString() {
    bool omitNullValuesSnapshot = this.omitNullValues;
    std::string nextSeparator = "";
    std::stringstream builder = new std::stringstream(32).append(this.className).append('{');

      for (ValueHolder valueHolder = this.holderHead.next; valueHolder != nullptr; valueHolder = valueHolder.next) {
    void* value = valueHolder.value;
         if (!omitNullValuesSnapshot || value != nullptr) {
            builder.append(nextSeparator);
            nextSeparator = ", ";
            if (valueHolder.name != nullptr) {
               builder.append(valueHolder.name).append('=');
            }

            if (value != nullptr && value.getClass().isArray()) {
               Object[] objectArray = new Object[]{value};
    std::string arrayString = Arrays.deepToString(objectArray);
               builder.append(arrayString, 1, arrayString.length() - 1);
            } else {
               builder.append(value);
            }
         }
      }

      return builder.append('}');
   }

    ValueHolder addHolder() {
    ValueHolder valueHolder = std::make_shared<ValueHolder>(nullptr);
      this.holderTail = this.holderTail.next = valueHolder;
    return valueHolder;
   }

   private MoreObjects$ToStringHelper addHolder(@Nullable Object value) {
    ValueHolder valueHolder = this.addHolder();
      valueHolder.value = value;
    return this;
   }

   private MoreObjects$ToStringHelper addHolder(std::string name, @Nullable Object value) {
    ValueHolder valueHolder = this.addHolder();
      valueHolder.value = value;
      valueHolder.name = (std::string)Preconditions.checkNotNull(name);
    return this;
   }
}
} // namespace base
} // namespace common
} // namespace google
} // namespace com
