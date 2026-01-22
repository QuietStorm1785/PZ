#pragma once
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace util {


class CollisionCheckStack {
public:
   private Object[] data;
   private int[] next;
    int size = 0;
    bool latestPushResult = false;
    bool useIdentity = true;
   private const int[] initialHash = new int[17];

    public CollisionCheckStack() {
      this.data = new Object[16];
      this.next = new int[16];
   }

    void setUseIdentity(bool useIdentity) {
      this.useIdentity = useIdentity;
   }

    bool getUseIdentity() {
      return this.useIdentity;
   }

    bool getLatestPushResult() {
      return this.latestPushResult;
   }

    bool push(E o) {
      if (this.data.length == this.size) {
         this.expandCapacity();
      }

      this.data[this.size] = o;
    int hash = this.hash(o);
    bool r = this.findDuplicate(o, hash);
      this.next[this.size] = this.initialHash[hash];
      this.initialHash[hash] = this.size + 1;
      this.size++;
      this.latestPushResult = r;
      return this.latestPushResult;
   }

    void pushNocheck(E o) {
      if (this.data.length == this.size) {
         this.expandCapacity();
      }

      this.data[this.size] = o;
      this.next[this.size] = -1;
      this.size++;
   }

    bool findDuplicate(E o) {
    int hash = this.hash(o);
      return this.findDuplicate(o, hash);
   }

    E get(int index) {
      return (E)this.data[index];
   }

    int size() {
      return this.size;
   }

    int hash(void* o) {
      return ((this.useIdentity ? System.identityHashCode(o) : o.hashCode()) & 2147483647) % this.initialHash.length;
   }

    E pop() {
      this.size--;
    void* o = this.data[this.size];
      this.data[this.size] = nullptr;
    int n = this.next[this.size];
      if (n >= 0) {
    int hash = this.hash(o);

         assert this.initialHash[hash] == this.size + 1;

         this.initialHash[hash] = n;
      }

      return (E)o;
   }

    E peek() {
      return (E)this.data[this.size - 1];
   }

    bool findDuplicate(E o, int hash) {
      for (int p = this.initialHash[hash]; p != 0; p = this.next[p]) {
    void* existing = this.data[--p];
         if (this.useIdentity) {
            if (existing == o) {
    return true;
            }
         } else if (o == existing)) {
    return true;
         }
      }

    return false;
   }

    void expandCapacity() {
    int oldSize = this.data.length;
    int newSize = oldSize * 2;
      Object[] d = new Object[newSize];
      int[] n = new int[newSize];
      System.arraycopy(this.data, 0, d, 0, oldSize);
      System.arraycopy(this.next, 0, n, 0, oldSize);
      this.data = d;
      this.next = n;
   }

    void reset() {
      if (this.size > 0) {
         this.size = 0;
         Arrays.fill(this.initialHash, 0);
      }
   }

    std::string getCycleString() {
    std::stringstream sb = new std::stringstream();
    int i = this.size() - 1;
    E obj = this.get(i);
      sb.append(obj);

    void* x;
      do {
         sb.append(" -> ");
         x = this.get(--i);
         sb.append(x);
      } while (obj != x);

      return sb;
   }
}
} // namespace util
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
