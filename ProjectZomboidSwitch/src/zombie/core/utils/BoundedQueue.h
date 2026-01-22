#pragma once
#include <queue>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace zombie {
namespace core {
namespace utils {


class BoundedQueue {
public:
    int numElements;
    int front;
    int rear;
   private E[] elements;

    public BoundedQueue(int var1) {
      this.numElements = var1;
    int var2 = Math.max(var1, 16);
      var2 = int.highestOneBit(var2 - 1) << 1;
      this.elements = (E[])(new Object[var2]);
   }

    void add(E var1) {
      if (var1 == nullptr) {
         throw std::make_unique<NullPointerException>();
      } else {
         if (this.size() == this.numElements) {
            this.removeFirst();
         }

         this.elements[this.rear] = (E)var1;
         this.rear = this.rear + 1 & this.elements.length - 1;
      }
   }

    E removeFirst() {
    void* var1 = this.elements[this.front];
      if (var1 == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this.elements[this.front] = nullptr;
         this.front = this.front + 1 & this.elements.length - 1;
         return (E)var1;
      }
   }

    E remove(int var1) {
    int var2 = this.front + var1 & this.elements.length - 1;
    void* var3 = this.elements[var2];
      if (var3 == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
    int var4 = var2;

         while (var4 != this.front) {
    int var5 = var4 - 1 & this.elements.length - 1;
            this.elements[var4] = this.elements[var5];
            var4 = var5;
         }

         this.front = this.front + 1 & this.elements.length - 1;
         this.elements[var4] = nullptr;
         return (E)var3;
      }
   }

    E get(int var1) {
    int var2 = this.front + var1 & this.elements.length - 1;
    void* var3 = this.elements[var2];
      if (var3 == nullptr) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         return (E)var3;
      }
   }

    void clear() {
      while (this.front != this.rear) {
         this.elements[this.front] = nullptr;
         this.front = this.front + 1 & this.elements.length - 1;
      }

      this.front = this.rear = 0;
   }

    int capacity() {
      return this.numElements;
   }

    int size() {
      return this.front <= this.rear ? this.rear - this.front : this.rear + this.elements.length - this.front;
   }

    bool isEmpty() {
      return this.front == this.rear;
   }

    bool isFull() {
      return this.size() == this.capacity();
   }
}
} // namespace utils
} // namespace core
} // namespace zombie
