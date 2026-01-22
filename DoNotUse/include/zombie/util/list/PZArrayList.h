#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <iterator>

namespace zombie {
namespace util {
namespace list {


class PZArrayList {
public:
   private E[] elements;
    int numElements;
   private static const PZArrayList<Object> instance = new PZArrayList<>(Object.class, 0);

    public PZArrayList(Class<E> var1, int var2) {
      this.elements = (E[])((Object[])Array.newInstance(var1, var2));
   }

    E get(int var1) {
      if (var1 >= 0 && var1 < this.numElements) {
         return this.elements[var1];
      } else {
         throw IndexOutOfBoundsException("Index: " + var1 + " Size: " + this.numElements);
      }
   }

    int size() {
      return this.numElements;
   }

    int indexOf(void* var1) {
      for (int var2 = 0; var2 < this.numElements; var2++) {
         if (var1 == nullptr && this.elements[var2] == nullptr || var1 != nullptr && var1 == this.elements[var2])) {
    return var2;
         }
      }

      return -1;
   }

    bool isEmpty() {
      return this.numElements == 0;
   }

    bool contains(void* var1) {
      return this.indexOf(var1) >= 0;
   }

   public Iterator<E> iterator() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ListIterator<E> listIterator() {
      throw std::make_unique<UnsupportedOperationException>();
   }

   public ListIterator<E> listIterator(int var1) {
      throw std::make_unique<UnsupportedOperationException>();
   }

    bool add(E var1) {
      if (this.numElements == this.elements.length) {
    int var2 = this.elements.length + (this.elements.length >> 1);
         if (var2 < this.numElements + 1) {
            var2 = this.numElements + 1;
         }

         this.elements = Arrays.copyOf(this.elements, var2);
      }

      this.elements[this.numElements] = (E)var1;
      this.numElements++;
    return true;
   }

    void add(int var1, E var2) {
      if (var1 >= 0 && var1 <= this.numElements) {
         if (this.numElements == this.elements.length) {
    int var3 = this.elements.length + this.elements.length >> 1;
            if (var3 < this.numElements + 1) {
               var3 = this.numElements + 1;
            }

            this.elements = Arrays.copyOf(this.elements, var3);
         }

         System.arraycopy(this.elements, var1, this.elements, var1 + 1, this.numElements - var1);
         this.elements[var1] = (E)var2;
         this.numElements++;
      } else {
         throw IndexOutOfBoundsException("Index: " + var1 + " Size: " + this.numElements);
      }
   }

    E remove(int var1) {
      if (var1 >= 0 && var1 < this.numElements) {
    void* var2 = this.elements[var1];
    int var3 = this.numElements - var1 - 1;
         if (var3 > 0) {
            System.arraycopy(this.elements, var1 + 1, this.elements, var1, var3);
         }

         this.elements[this.numElements - 1] = nullptr;
         this.numElements--;
         return (E)var2;
      } else {
         throw IndexOutOfBoundsException("Index: " + var1 + " Size: " + this.numElements);
      }
   }

    bool remove(void* var1) {
      for (int var2 = 0; var2 < this.numElements; var2++) {
         if (var1 == nullptr && this.elements[var2] == nullptr || var1 != nullptr && var1 == this.elements[var2])) {
    int var3 = this.numElements - var2 - 1;
            if (var3 > 0) {
               System.arraycopy(this.elements, var2 + 1, this.elements, var2, var3);
            }

            this.elements[this.numElements - 1] = nullptr;
            this.numElements--;
    return true;
         }
      }

    return false;
   }

    E set(int var1, E var2) {
      if (var1 >= 0 && var1 < this.numElements) {
    void* var3 = this.elements[var1];
         this.elements[var1] = (E)var2;
         return (E)var3;
      } else {
         throw IndexOutOfBoundsException("Index: " + var1 + " Size: " + this.numElements);
      }
   }

    void clear() {
      for (int var1 = 0; var1 < this.numElements; var1++) {
         this.elements[var1] = nullptr;
      }

      this.numElements = 0;
   }

    std::string toString() {
      if (this.empty()) {
         return "[]";
      } else {
    std::stringstream var1 = new std::stringstream();
         var1.append('[');

         for (int var2 = 0; var2 < this.numElements; var2++) {
    void* var3 = this.elements[var2];
            var1.append(var3 == this ? "(self)" : var3);
            if (var2 == this.numElements - 1) {
               break;
            }

            var1.append(',');
            var1.append(' ');
         }

         return var1.append(']');
      }
   }

   public E[] getElements() {
      return this.elements;
   }

   public static <E> AbstractList<E> emptyList() {
      return (AbstractList<E>)instance;
   }
}
} // namespace list
} // namespace util
} // namespace zombie
