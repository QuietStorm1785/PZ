#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/annotations/GwtIncompatible.h"
#include "com/google/common/base/Preconditions.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class EnumMultiset {
public:
   private transient Class<E> type;
    static const long serialVersionUID = 0L;

   public static <E : public Enum<E>> EnumMultiset<E> create(Class<E> type) {
      return new EnumMultiset<>(type);
   }

   public static <E : public Enum<E>> EnumMultiset<E> create(Iterable<E> elements) {
      Iterator<E> iterator = elements.iterator();
      Preconditions.checkArgument(iterator.hasNext(), "EnumMultiset constructor passed empty Iterable");
      EnumMultiset<E> multiset = new EnumMultiset<>(iterator.next().getDeclaringClass());
      Iterables.addAll(multiset, elements);
    return multiset;
   }

   public static <E : public Enum<E>> EnumMultiset<E> create(Iterable<E> elements, Class<E> type) {
      EnumMultiset<E> result = create(type);
      Iterables.addAll(result, elements);
    return result;
   }

    private EnumMultiset(Class<E> type) {
      super(WellBehavedMap.wrap(new EnumMap<>(type)));
      this.type = type;
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.type);
      Serialization.writeMultiset(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      Class<E> localType = (Class<E>)stream.readObject();
      this.type = localType;
      this.setBackingMap(WellBehavedMap.wrap(new EnumMap<>(this.type)));
      Serialization.populateMultiset(this, stream);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
