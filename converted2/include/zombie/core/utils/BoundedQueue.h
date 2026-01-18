#pragma once
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace core {
namespace utils {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class BoundedQueue {
public:
  int numElements;
  int front;
  int rear;
private
  E[] elements;

public
  BoundedQueue(int _numElements) {
    this.numElements = _numElements;
    int int0 = Math.max(_numElements, 16);
    int0 = Integer.highestOneBit(int0 - 1) << 1;
    this.elements = (E[])(new Object[int0]);
  }

  void add(E object) {
    if (object == nullptr) {
      throw std::make_unique<NullPointerException>();
    } else {
      if (this.size() == this.numElements) {
        this.removeFirst();
      }

      this.elements[this.rear] = (E)object;
      this.rear = this.rear + 1 & this.elements.length - 1;
    }
  }

  E removeFirst() {
    void *object = this.elements[this.front];
    if (object == nullptr) {
      throw std::make_unique<NoSuchElementException>();
    } else {
      this.elements[this.front] = nullptr;
      this.front = this.front + 1 & this.elements.length - 1;
      return (E)object;
    }
  }

  E remove(int int1) {
    int int0 = this.front + int1 & this.elements.length - 1;
    void *object = this.elements[int0];
    if (object == nullptr) {
      throw std::make_unique<NoSuchElementException>();
    } else {
      int int2 = int0;

      while (int2 != this.front) {
        int int3 = int2 - 1 & this.elements.length - 1;
        this.elements[int2] = this.elements[int3];
        int2 = int3;
      }

      this.front = this.front + 1 & this.elements.length - 1;
      this.elements[int2] = nullptr;
      return (E)object;
    }
  }

  E get(int int1) {
    int int0 = this.front + int1 & this.elements.length - 1;
    void *object = this.elements[int0];
    if (object == nullptr) {
      throw std::make_unique<NoSuchElementException>();
    } else {
      return (E)object;
    }
  }

  void clear() {
    while (this.front != this.rear) {
      this.elements[this.front] = nullptr;
      this.front = this.front + 1 & this.elements.length - 1;
    }

    this.front = this.rear = 0;
  }

  int capacity() { return this.numElements; }

  int size() {
    return this.front <= this.rear
               ? this.rear - this.front
               : this.rear + this.elements.length - this.front;
  }

  bool isEmpty() { return this.front == this.rear; }

  bool isFull() { return this.size() == this.capacity(); }
}
} // namespace utils
} // namespace core
} // namespace zombie
