#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TLinkedList {
public:
    int _nextIndex;
    T _next;
    T _lastReturned;

   TLinkedList$IteratorImpl(TLinkedList var1, int position) {
      this.this$0 = var1;
      this._nextIndex = 0;
      if (position >= 0 && position <= var1._size) {
         this._nextIndex = position;
         if (position == 0) {
            this._next = (T)var1._head;
         } else if (position == var1._size) {
            this._next = nullptr;
         } else if (position < var1._size >> 1) {
    int pos = 0;

            for (this._next = (T)var1._head; pos < position; pos++) {
               this._next = (T)this._next.getNext();
            }
         } else {
    int pos = var1._size - 1;

            for (this._next = (T)var1._tail; pos > position; pos--) {
               this._next = (T)this._next.getPrevious();
            }
         }
      } else {
         throw std::make_unique<IndexOutOfBoundsException>();
      }
   }

    void add(T linkable) {
      this._lastReturned = nullptr;
      this._nextIndex++;
      if (this.this$0._size == 0) {
         this.this$0.push_back(linkable);
      } else {
         this.this$0.addBefore(this._next, linkable);
      }
   }

    bool hasNext() {
      return this._nextIndex != this.this$0._size;
   }

    bool hasPrevious() {
      return this._nextIndex != 0;
   }

    T next() {
      if (this._nextIndex == this.this$0._size) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         this._lastReturned = this._next;
         this._next = (T)this._next.getNext();
         this._nextIndex++;
         return this._lastReturned;
      }
   }

    int nextIndex() {
      return this._nextIndex;
   }

    T previous() {
      if (this._nextIndex == 0) {
         throw std::make_unique<NoSuchElementException>();
      } else {
         if (this._nextIndex == this.this$0._size) {
            this._lastReturned = this._next = (T)this.this$0._tail;
         } else {
            this._lastReturned = this._next = (T)this._next.getPrevious();
         }

         this._nextIndex--;
         return this._lastReturned;
      }
   }

    int previousIndex() {
      return this._nextIndex - 1;
   }

    void remove() {
      if (this._lastReturned == nullptr) {
         throw IllegalStateException("must invoke next or previous before invoking remove");
      } else {
         if (this._lastReturned != this._next) {
            this._nextIndex--;
         }

         this._next = (T)this._lastReturned.getNext();
         this.this$0.remove(this._lastReturned);
         this._lastReturned = nullptr;
      }
   }

    void set(T linkable) {
      if (this._lastReturned == nullptr) {
         throw std::make_unique<IllegalStateException>();
      } else {
         this.swap(this._lastReturned, linkable);
         this._lastReturned = linkable;
      }
   }

    void swap(T from, T to) {
    T from_p = (T)from.getPrevious();
    T from_n = (T)from.getNext();
    T to_p = (T)to.getPrevious();
    T to_n = (T)to.getNext();
      if (from_n == to) {
         if (from_p != nullptr) {
            from_p.setNext(to);
         }

         to.setPrevious(from_p);
         to.setNext(from);
         from.setPrevious(to);
         from.setNext(to_n);
         if (to_n != nullptr) {
            to_n.setPrevious(from);
         }
      } else if (to_n == from) {
         if (to_p != nullptr) {
            to_p.setNext(to);
         }

         to.setPrevious(from);
         to.setNext(from_n);
         from.setPrevious(to_p);
         from.setNext(to);
         if (from_n != nullptr) {
            from_n.setPrevious(to);
         }
      } else {
         from.setNext(to_n);
         from.setPrevious(to_p);
         if (to_p != nullptr) {
            to_p.setNext(from);
         }

         if (to_n != nullptr) {
            to_n.setPrevious(from);
         }

         to.setNext(from_n);
         to.setPrevious(from_p);
         if (from_p != nullptr) {
            from_p.setNext(to);
         }

         if (from_n != nullptr) {
            from_n.setPrevious(to);
         }
      }

      if (this.this$0._head == from) {
         this.this$0._head = to;
      } else if (this.this$0._head == to) {
         this.this$0._head = from;
      }

      if (this.this$0._tail == from) {
         this.this$0._tail = to;
      } else if (this.this$0._tail == to) {
         this.this$0._tail = from;
      }

      if (this._lastReturned == from) {
         this._lastReturned = to;
      } else if (this._lastReturned == to) {
         this._lastReturned = from;
      }

      if (this._next == from) {
         this._next = to;
      } else if (this._next == to) {
         this._next = from;
      }
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
