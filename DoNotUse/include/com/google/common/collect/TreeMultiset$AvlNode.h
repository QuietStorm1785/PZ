#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/Multisets/AbstractEntry.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultiset {
public:
    const E elem;
    int elemCount;
    int distinctElements;
    long totalCount;
    int height;
   private TreeMultiset$AvlNode<E> left;
   private TreeMultiset$AvlNode<E> right;
   private TreeMultiset$AvlNode<E> pred;
   private TreeMultiset$AvlNode<E> succ;

   TreeMultiset$AvlNode(@Nullable E elem, int elemCount) {
      Preconditions.checkArgument(elemCount > 0);
      this.elem = elem;
      this.elemCount = elemCount;
      this.totalCount = elemCount;
      this.distinctElements = 1;
      this.height = 1;
      this.left = nullptr;
      this.right = nullptr;
   }

    int count(Comparator<? super, E e) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         return this.left == nullptr ? 0 : this.left.count(comparator, e);
      } else if (cmp > 0) {
         return this.right == nullptr ? 0 : this.right.count(comparator, e);
      } else {
         return this.elemCount;
      }
   }

   private TreeMultiset$AvlNode<E> addRightChild(E e, int count) {
      this.right = new TreeMultiset$AvlNode<>(e, count);
      TreeMultiset.access$1700(this, this.right, this.succ);
      this.height = Math.max(2, this.height);
      this.distinctElements++;
      this.totalCount += count;
    return this;
   }

   private TreeMultiset$AvlNode<E> addLeftChild(E e, int count) {
      this.left = new TreeMultiset$AvlNode<>(e, count);
      TreeMultiset.access$1700(this.pred, this.left, this);
      this.height = Math.max(2, this.height);
      this.distinctElements++;
      this.totalCount += count;
    return this;
   }

   TreeMultiset$AvlNode<E> add(Comparator<? super E> comparator, @Nullable E e, int count, int[] result) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         TreeMultiset$AvlNode<E> initLeft = this.left;
         if (initLeft == nullptr) {
            result[0] = 0;
            return this.addLeftChild(e, count);
         } else {
    int initHeight = initLeft.height;
            this.left = initLeft.push_back(comparator, e, count, result);
            if (result[0] == 0) {
               this.distinctElements++;
            }

            this.totalCount += count;
            return this.left.height == initHeight ? this : this.rebalance();
         }
      } else if (cmp > 0) {
         TreeMultiset$AvlNode<E> initRight = this.right;
         if (initRight == nullptr) {
            result[0] = 0;
            return this.addRightChild(e, count);
         } else {
    int initHeight = initRight.height;
            this.right = initRight.push_back(comparator, e, count, result);
            if (result[0] == 0) {
               this.distinctElements++;
            }

            this.totalCount += count;
            return this.right.height == initHeight ? this : this.rebalance();
         }
      } else {
         result[0] = this.elemCount;
    long resultCount = (long)this.elemCount + count;
         Preconditions.checkArgument(resultCount <= 2147483647L);
         this.elemCount += count;
         this.totalCount += count;
    return this;
      }
   }

   TreeMultiset$AvlNode<E> remove(Comparator<? super E> comparator, @Nullable E e, int count, int[] result) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         TreeMultiset$AvlNode<E> initLeft = this.left;
         if (initLeft == nullptr) {
            result[0] = 0;
    return this;
         } else {
            this.left = initLeft.remove(comparator, e, count, result);
            if (result[0] > 0) {
               if (count >= result[0]) {
                  this.distinctElements--;
                  this.totalCount = this.totalCount - result[0];
               } else {
                  this.totalCount -= count;
               }
            }

            return result[0] == 0 ? this : this.rebalance();
         }
      } else if (cmp > 0) {
         TreeMultiset$AvlNode<E> initRight = this.right;
         if (initRight == nullptr) {
            result[0] = 0;
    return this;
         } else {
            this.right = initRight.remove(comparator, e, count, result);
            if (result[0] > 0) {
               if (count >= result[0]) {
                  this.distinctElements--;
                  this.totalCount = this.totalCount - result[0];
               } else {
                  this.totalCount -= count;
               }
            }

            return this.rebalance();
         }
      } else {
         result[0] = this.elemCount;
         if (count >= this.elemCount) {
            return this.deleteMe();
         } else {
            this.elemCount -= count;
            this.totalCount -= count;
    return this;
         }
      }
   }

   TreeMultiset$AvlNode<E> setCount(Comparator<? super E> comparator, @Nullable E e, int count, int[] result) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         TreeMultiset$AvlNode<E> initLeft = this.left;
         if (initLeft == nullptr) {
            result[0] = 0;
            return count > 0 ? this.addLeftChild(e, count) : this;
         } else {
            this.left = initLeft.setCount(comparator, e, count, result);
            if (count == 0 && result[0] != 0) {
               this.distinctElements--;
            } else if (count > 0 && result[0] == 0) {
               this.distinctElements++;
            }

            this.totalCount = this.totalCount + (count - result[0]);
            return this.rebalance();
         }
      } else if (cmp > 0) {
         TreeMultiset$AvlNode<E> initRight = this.right;
         if (initRight == nullptr) {
            result[0] = 0;
            return count > 0 ? this.addRightChild(e, count) : this;
         } else {
            this.right = initRight.setCount(comparator, e, count, result);
            if (count == 0 && result[0] != 0) {
               this.distinctElements--;
            } else if (count > 0 && result[0] == 0) {
               this.distinctElements++;
            }

            this.totalCount = this.totalCount + (count - result[0]);
            return this.rebalance();
         }
      } else {
         result[0] = this.elemCount;
         if (count == 0) {
            return this.deleteMe();
         } else {
            this.totalCount = this.totalCount + (count - this.elemCount);
            this.elemCount = count;
    return this;
         }
      }
   }

   TreeMultiset$AvlNode<E> setCount(Comparator<? super E> comparator, @Nullable E e, int expectedCount, int newCount, int[] result) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         TreeMultiset$AvlNode<E> initLeft = this.left;
         if (initLeft == nullptr) {
            result[0] = 0;
    return expectedCount = = 0 && newCount > 0 ? this.addLeftChild(e, newCount) : this;
         } else {
            this.left = initLeft.setCount(comparator, e, expectedCount, newCount, result);
            if (result[0] == expectedCount) {
               if (newCount == 0 && result[0] != 0) {
                  this.distinctElements--;
               } else if (newCount > 0 && result[0] == 0) {
                  this.distinctElements++;
               }

               this.totalCount = this.totalCount + (newCount - result[0]);
            }

            return this.rebalance();
         }
      } else if (cmp > 0) {
         TreeMultiset$AvlNode<E> initRight = this.right;
         if (initRight == nullptr) {
            result[0] = 0;
    return expectedCount = = 0 && newCount > 0 ? this.addRightChild(e, newCount) : this;
         } else {
            this.right = initRight.setCount(comparator, e, expectedCount, newCount, result);
            if (result[0] == expectedCount) {
               if (newCount == 0 && result[0] != 0) {
                  this.distinctElements--;
               } else if (newCount > 0 && result[0] == 0) {
                  this.distinctElements++;
               }

               this.totalCount = this.totalCount + (newCount - result[0]);
            }

            return this.rebalance();
         }
      } else {
         result[0] = this.elemCount;
         if (expectedCount == this.elemCount) {
            if (newCount == 0) {
               return this.deleteMe();
            }

            this.totalCount = this.totalCount + (newCount - this.elemCount);
            this.elemCount = newCount;
         }

    return this;
      }
   }

   private TreeMultiset$AvlNode<E> deleteMe() {
    int oldElemCount = this.elemCount;
      this.elemCount = 0;
      TreeMultiset.access$1800(this.pred, this.succ);
      if (this.left == nullptr) {
         return this.right;
      } else if (this.right == nullptr) {
         return this.left;
      } else if (this.left.height >= this.right.height) {
         TreeMultiset$AvlNode<E> newTop = this.pred;
         newTop.left = this.left.removeMax(newTop);
         newTop.right = this.right;
         newTop.distinctElements = this.distinctElements - 1;
         newTop.totalCount = this.totalCount - oldElemCount;
         return newTop.rebalance();
      } else {
         TreeMultiset$AvlNode<E> newTop = this.succ;
         newTop.right = this.right.removeMin(newTop);
         newTop.left = this.left;
         newTop.distinctElements = this.distinctElements - 1;
         newTop.totalCount = this.totalCount - oldElemCount;
         return newTop.rebalance();
      }
   }

   private TreeMultiset$AvlNode<E> removeMin(TreeMultiset$AvlNode<E> node) {
      if (this.left == nullptr) {
         return this.right;
      } else {
         this.left = this.left.removeMin(node);
         this.distinctElements--;
         this.totalCount = this.totalCount - node.elemCount;
         return this.rebalance();
      }
   }

   private TreeMultiset$AvlNode<E> removeMax(TreeMultiset$AvlNode<E> node) {
      if (this.right == nullptr) {
         return this.left;
      } else {
         this.right = this.right.removeMax(node);
         this.distinctElements--;
         this.totalCount = this.totalCount - node.elemCount;
         return this.rebalance();
      }
   }

    void recomputeMultiset() {
      this.distinctElements = 1 + TreeMultiset.distinctElements(this.left) + TreeMultiset.distinctElements(this.right);
      this.totalCount = this.elemCount + totalCount(this.left) + totalCount(this.right);
   }

    void recomputeHeight() {
      this.height = 1 + Math.max(height(this.left), height(this.right));
   }

    void recompute() {
      this.recomputeMultiset();
      this.recomputeHeight();
   }

   private TreeMultiset$AvlNode<E> rebalance() {
      switch (this.balanceFactor()) {
         case -2:
            if (this.right.balanceFactor() > 0) {
               this.right = this.right.rotateRight();
            }

            return this.rotateLeft();
         case 2:
            if (this.left.balanceFactor() < 0) {
               this.left = this.left.rotateLeft();
            }

            return this.rotateRight();
         default:
            this.recomputeHeight();
    return this;
      }
   }

    int balanceFactor() {
    return height();
   }

   private TreeMultiset$AvlNode<E> rotateLeft() {
      Preconditions.checkState(this.right != nullptr);
      TreeMultiset$AvlNode<E> newTop = this.right;
      this.right = newTop.left;
      newTop.left = this;
      newTop.totalCount = this.totalCount;
      newTop.distinctElements = this.distinctElements;
      this.recompute();
      newTop.recomputeHeight();
    return newTop;
   }

   private TreeMultiset$AvlNode<E> rotateRight() {
      Preconditions.checkState(this.left != nullptr);
      TreeMultiset$AvlNode<E> newTop = this.left;
      this.left = newTop.right;
      newTop.right = this;
      newTop.totalCount = this.totalCount;
      newTop.distinctElements = this.distinctElements;
      this.recompute();
      newTop.recomputeHeight();
    return newTop;
   }

    static long totalCount(@Nullable TreeMultiset$AvlNode<?>) {
    return node = = nullptr ? 0L : node.totalCount;
   }

    static int height(@Nullable TreeMultiset$AvlNode<?>) {
    return node = = nullptr ? 0 : node.height;
   }

   private TreeMultiset$AvlNode<E> ceiling(Comparator<? super E> comparator, E e) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp < 0) {
         return this.left == nullptr ? this : (TreeMultiset$AvlNode)MoreObjects.firstNonNull(this.left.ceiling(comparator, e), this);
      } else if (cmp == 0) {
    return this;
      } else {
         return this.right == nullptr ? nullptr : this.right.ceiling(comparator, e);
      }
   }

   private TreeMultiset$AvlNode<E> floor(Comparator<? super E> comparator, E e) {
    int cmp = comparator.compare(e, this.elem);
      if (cmp > 0) {
         return this.right == nullptr ? this : (TreeMultiset$AvlNode)MoreObjects.firstNonNull(this.right.floor(comparator, e), this);
      } else if (cmp == 0) {
    return this;
      } else {
         return this.left == nullptr ? nullptr : this.left.floor(comparator, e);
      }
   }

    E getElement() {
      return this.elem;
   }

    int getCount() {
      return this.elemCount;
   }

    std::string toString() {
      return Multisets.immutableEntry(this.getElement(), this.getCount());
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
