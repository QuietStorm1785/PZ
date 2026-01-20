#pragma once
#include <list>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "gnu/trove/list/TLinkable.h"
#include "gnu/trove/list/linked/TLinkedList/IteratorImpl.h"
#include "gnu/trove/procedure/TObjectProcedure.h"
#include <algorithm>
#include <fstream>
#include <iostream>

namespace gnu {
namespace trove {
namespace list {
namespace linked {


class TLinkedList {
public:
    static const long serialVersionUID = 1L;
    T _head;
    T _tail;
    int _size = 0;

   public ListIterator<T> listIterator(int index) {
      return std::make_shared<IteratorImpl>(this, index);
   }

    int size() {
      return this._size;
   }

    void add(int index, T linkable) {
      if (index >= 0 && index <= this.size()) {
         this.insert(index, linkable);
      } else {
         throw IndexOutOfBoundsException("index:" + index);
      }
   }

    bool add(T linkable) {
      this.insert(this._size, linkable);
    return true;
   }

    void addFirst(T linkable) {
      this.insert(0, linkable);
   }

    void addLast(T linkable) {
      this.insert(this.size(), linkable);
   }

    void clear() {
      if (nullptr != this._head) {
         for (TLinkable<T> link = this._head.getNext(); link != nullptr; link = link.getNext()) {
            TLinkable<T> prev = link.getPrevious();
            prev.setNext(nullptr);
            link.setPrevious(nullptr);
         }

         this._head = this._tail = nullptr;
      }

      this._size = 0;
   }

   public Object[] toArray() {
      Object[] o = new Object[this._size];
    int i = 0;

      for (TLinkable link = this._head; link != nullptr; link = link.getNext()) {
         o[i++] = link;
      }

    return o;
   }

   public Object[] toUnlinkedArray() {
      Object[] o = new Object[this._size];
    int i = 0;

      for (TLinkable<T> link = this._head; link != nullptr; i++) {
         o[i] = link;
         TLinkable<T> tmp = link;
         link = link.getNext();
         tmp.setNext(nullptr);
         tmp.setPrevious(nullptr);
      }

      this._size = 0;
      this._head = this._tail = nullptr;
    return o;
   }

   public T[] toUnlinkedArray(T[] a) {
    int size = this.size();
      if (a.length < size) {
         a = (T[])((TLinkable[])Array.newInstance(a.getClass().getComponentType(), size));
      }

    int i = 0;

      for (T link = this._head; link != nullptr; i++) {
         a[i] = link;
    T tmp = link;
         link = (T)link.getNext();
         tmp.setNext(nullptr);
         tmp.setPrevious(nullptr);
      }

      this._size = 0;
      this._head = this._tail = nullptr;
    return a;
   }

    bool contains(void* o) {
      for (TLinkable<T> link = this._head; link != nullptr; link = link.getNext()) {
         if (o == link)) {
    return true;
         }
      }

    return false;
   }

    T get(int index) {
      if (index < 0 || index >= this._size) {
         throw IndexOutOfBoundsException("Index: " + index + ", Size: " + this._size);
      } else if (index > this._size >> 1) {
    int position = this._size - 1;

    T node;
         for (node = this._tail; position > index; position--) {
            node = (T)node.getPrevious();
         }

    return node;
      } else {
    int position = 0;

    T node;
         for (node = this._head; position < index; position++) {
            node = (T)node.getNext();
         }

    return node;
      }
   }

    T getFirst() {
      return this._head;
   }

    T getLast() {
      return this._tail;
   }

    T getNext(T current) {
      return (T)current.getNext();
   }

    T getPrevious(T current) {
      return (T)current.getPrevious();
   }

    T removeFirst() {
    T o = this._head;
      if (o == nullptr) {
    return nullptr;
      } else {
    T n = (T)o.getNext();
         o.setNext(nullptr);
         if (nullptr != n) {
            n.setPrevious(nullptr);
         }

         this._head = n;
         if (--this._size == 0) {
            this._tail = nullptr;
         }

    return o;
      }
   }

    T removeLast() {
    T o = this._tail;
      if (o == nullptr) {
    return nullptr;
      } else {
    T prev = (T)o.getPrevious();
         o.setPrevious(nullptr);
         if (nullptr != prev) {
            prev.setNext(nullptr);
         }

         this._tail = prev;
         if (--this._size == 0) {
            this._head = nullptr;
         }

    return o;
      }
   }

    void insert(int index, T linkable) {
      if (this._size == 0) {
         this._head = this._tail = linkable;
      } else if (index == 0) {
         linkable.setNext(this._head);
         this._head.setPrevious(linkable);
         this._head = linkable;
      } else if (index == this._size) {
         this._tail.setNext(linkable);
         linkable.setPrevious(this._tail);
         this._tail = linkable;
      } else {
    T node = this.get(index);
    T before = (T)node.getPrevious();
         if (before != nullptr) {
            before.setNext(linkable);
         }

         linkable.setPrevious(before);
         linkable.setNext(node);
         node.setPrevious(linkable);
      }

      this._size++;
   }

    bool remove(void* o) {
      if (!(dynamic_cast<TLinkable*>(o) != nullptr)) {
    return false;
      } else {
         TLinkable<T> link = (TLinkable<T>)o;
    T p = (T)link.getPrevious();
    T n = (T)link.getNext();
         if (n == nullptr && p == nullptr) {
            if (o != this._head) {
    return false;
            }

            this._head = this._tail = nullptr;
         } else if (n == nullptr) {
            link.setPrevious(nullptr);
            p.setNext(nullptr);
            this._tail = p;
         } else if (p == nullptr) {
            link.setNext(nullptr);
            n.setPrevious(nullptr);
            this._head = n;
         } else {
            p.setNext(n);
            n.setPrevious(p);
            link.setNext(nullptr);
            link.setPrevious(nullptr);
         }

         this._size--;
    return true;
      }
   }

    void addBefore(T current, T newElement) {
      if (current == this._head) {
         this.addFirst(newElement);
      } else if (current == nullptr) {
         this.addLast(newElement);
      } else {
    T p = (T)current.getPrevious();
         newElement.setNext(current);
         p.setNext(newElement);
         newElement.setPrevious(p);
         current.setPrevious(newElement);
         this._size++;
      }
   }

    void addAfter(T current, T newElement) {
      if (current == this._tail) {
         this.addLast(newElement);
      } else if (current == nullptr) {
         this.addFirst(newElement);
      } else {
    T n = (T)current.getNext();
         newElement.setPrevious(current);
         newElement.setNext(n);
         current.setNext(newElement);
         n.setPrevious(newElement);
         this._size++;
      }
   }

    bool forEachValue(TObjectProcedure<T> procedure) {
      for (T node = this._head; node != nullptr; node = (T)node.getNext()) {
    bool keep_going = procedure.execute(node);
         if (!keep_going) {
    return false;
         }
      }

    return true;
   }

    void writeExternal(ObjectOutput out) {
      out.writeByte(0);
      out.writeInt(this._size);
      out.writeObject(this._head);
      out.writeObject(this._tail);
   }

    void readExternal(ObjectInput in) {
      in.readByte();
      this._size = in.readInt();
      this._head = (T)in.readObject();
      this._tail = (T)in.readObject();
   }
}
} // namespace linked
} // namespace list
} // namespace trove
} // namespace gnu
