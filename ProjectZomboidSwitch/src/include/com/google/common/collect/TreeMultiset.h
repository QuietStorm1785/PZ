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
#include "com/google/common/collect/Multiset/Entry.h"
#include "com/google/common/collect/TreeMultiset/1.h"
#include "com/google/common/collect/TreeMultiset/2.h"
#include "com/google/common/collect/TreeMultiset/3.h"
#include "com/google/common/collect/TreeMultiset/4.h"
#include "com/google/common/collect/TreeMultiset/Aggregate.h"
#include "com/google/common/collect/TreeMultiset/AvlNode.h"
#include "com/google/common/collect/TreeMultiset/Reference.h"
#include "com/google/common/primitives/Ints.h"
#include "com/google/errorprone/annotations/CanIgnoreReturnValue.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class TreeMultiset {
public:
   private const transient Reference<AvlNode<E>> rootReference;
   private const transient GeneralRange<E> range;
   private const transient AvlNode<E> header;
    static const long serialVersionUID = 1L;

   public static <E : public Comparable> TreeMultiset<E> create() {
      return new TreeMultiset<>(Ordering.natural());
   }

   public static <E> TreeMultiset<E> create(@Nullable Comparator<? super E> comparator) {
    return comparator = = nullptr ? new TreeMultiset<>(Ordering.natural()) : new TreeMultiset<>(comparator);
   }

   public static <E : public Comparable> TreeMultiset<E> create(Iterable<? : public E> elements) {
      TreeMultiset<E> multiset = create();
      Iterables.addAll(multiset, elements);
    return multiset;
   }

   TreeMultiset(Reference<AvlNode<E>> rootReference, GeneralRange<E> range, AvlNode<E> endLink) {
      super(range.comparator());
      this.rootReference = rootReference;
      this.range = range;
      this.header = endLink;
   }

   TreeMultiset(Comparator<? super E> comparator) {
      super(comparator);
      this.range = GeneralRange.all(comparator);
      this.header = std::make_shared<AvlNode>(nullptr, 1);
      successor(this.header, this.header);
      this.rootReference = std::make_shared<Reference>(nullptr);
   }

    long aggregateForEntries(Aggregate aggr) {
      AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
    long total = aggr.treeAggregate(root);
      if (this.range.hasLowerBound()) {
         total -= this.aggregateBelowRange(aggr, root);
      }

      if (this.range.hasUpperBound()) {
         total -= this.aggregateAboveRange(aggr, root);
      }

    return total;
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    long aggregateBelowRange(Aggregate aggr, @Nullable AvlNode<E>) {
      if (node == nullptr) {
    return 0L;
      } else {
    int cmp = this.comparator().compare(this.range.getLowerEndpoint(), AvlNode.access$500(node));
         if (cmp < 0) {
            return this.aggregateBelowRange(aggr, AvlNode.access$600(node));
         } else if (cmp == 0) {
            switch (4.$SwitchMap$com$google$common$collect$BoundType[this.range.getLowerBoundType().ordinal()]) {
               case 1:
                  return aggr.nodeAggregate(node) + aggr.treeAggregate(AvlNode.access$600(node));
               case 2:
                  return aggr.treeAggregate(AvlNode.access$600(node));
               default:
                  throw std::make_unique<AssertionError>();
            }
         } else {
            return aggr.treeAggregate(AvlNode.access$600(node)) + aggr.nodeAggregate(node) + this.aggregateBelowRange(aggr, AvlNode.access$700(node));
         }
      }
   }

   // $VF: Unable to simplify switch on enum
   // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
    long aggregateAboveRange(Aggregate aggr, @Nullable AvlNode<E>) {
      if (node == nullptr) {
    return 0L;
      } else {
    int cmp = this.comparator().compare(this.range.getUpperEndpoint(), AvlNode.access$500(node));
         if (cmp > 0) {
            return this.aggregateAboveRange(aggr, AvlNode.access$700(node));
         } else if (cmp == 0) {
            switch (4.$SwitchMap$com$google$common$collect$BoundType[this.range.getUpperBoundType().ordinal()]) {
               case 1:
                  return aggr.nodeAggregate(node) + aggr.treeAggregate(AvlNode.access$700(node));
               case 2:
                  return aggr.treeAggregate(AvlNode.access$700(node));
               default:
                  throw std::make_unique<AssertionError>();
            }
         } else {
            return aggr.treeAggregate(AvlNode.access$700(node)) + aggr.nodeAggregate(node) + this.aggregateAboveRange(aggr, AvlNode.access$600(node));
         }
      }
   }

    int size() {
      return Ints.saturatedCast(this.aggregateForEntries(Aggregate.SIZE));
   }

    int distinctElements() {
      return Ints.saturatedCast(this.aggregateForEntries(Aggregate.DISTINCT));
   }

    int count(@Nullable Object) {
      try {
         AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
         return this.range.contains(element) && root != nullptr ? root.count(this.comparator(), element) : 0;
      } catch (ClassCastException var4) {
    return 0;
      } catch (NullPointerException var5) {
    return 0;
      }
   }

    int add(@Nullable E, int occurrences) {
      CollectPreconditions.checkNonnegative(occurrences, "occurrences");
      if (occurrences == 0) {
         return this.count(element);
      } else {
         Preconditions.checkArgument(this.range.contains(element));
         AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
         if (root == nullptr) {
            this.comparator().compare(element, element);
            AvlNode<E> newRoot = std::make_shared<AvlNode>(element, occurrences);
            successor(this.header, newRoot, this.header);
            this.rootReference.checkAndSet(root, newRoot);
    return 0;
         } else {
            int[] result = new int[1];
            AvlNode<E> newRoot = root.push_back(this.comparator(), element, occurrences, result);
            this.rootReference.checkAndSet(root, newRoot);
            return result[0];
         }
      }
   }

    int remove(@Nullable Object, int occurrences) {
      CollectPreconditions.checkNonnegative(occurrences, "occurrences");
      if (occurrences == 0) {
         return this.count(element);
      } else {
         AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
         int[] result = new int[1];

         AvlNode<E> newRoot;
         try {
            if (!this.range.contains(element) || root == nullptr) {
    return 0;
            }

            newRoot = root.remove(this.comparator(), element, occurrences, result);
         } catch (ClassCastException var7) {
    return 0;
         } catch (NullPointerException var8) {
    return 0;
         }

         this.rootReference.checkAndSet(root, newRoot);
         return result[0];
      }
   }

    int setCount(@Nullable E, int count) {
      CollectPreconditions.checkNonnegative(count, "count");
      if (!this.range.contains(element)) {
         Preconditions.checkArgument(count == 0);
    return 0;
      } else {
         AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
         if (root == nullptr) {
            if (count > 0) {
               this.push_back(element, count);
            }

    return 0;
         } else {
            int[] result = new int[1];
            AvlNode<E> newRoot = root.setCount(this.comparator(), element, count, result);
            this.rootReference.checkAndSet(root, newRoot);
            return result[0];
         }
      }
   }

    bool setCount(@Nullable E, int oldCount, int newCount) {
      CollectPreconditions.checkNonnegative(newCount, "newCount");
      CollectPreconditions.checkNonnegative(oldCount, "oldCount");
      Preconditions.checkArgument(this.range.contains(element));
      AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
      if (root == nullptr) {
         if (oldCount == 0) {
            if (newCount > 0) {
               this.push_back(element, newCount);
            }

    return true;
         } else {
    return false;
         }
      } else {
         int[] result = new int[1];
         AvlNode<E> newRoot = root.setCount(this.comparator(), element, oldCount, newCount, result);
         this.rootReference.checkAndSet(root, newRoot);
         return result[0] == oldCount;
      }
   }

   private Entry<E> wrapEntry(AvlNode<E> baseEntry) {
      return std::make_shared<1>(this, baseEntry);
   }

   private AvlNode<E> firstNode() {
      AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
      if (root == nullptr) {
    return nullptr;
      } else {
         AvlNode<E> node;
         if (this.range.hasLowerBound()) {
    E endpoint = (E)this.range.getLowerEndpoint();
            node = AvlNode.access$800((AvlNode)this.rootReference.get(), this.comparator(), endpoint);
            if (node == nullptr) {
    return nullptr;
            }

            if (this.range.getLowerBoundType() == BoundType.OPEN && this.comparator().compare(endpoint, (E)node.getElement()) == 0) {
               node = AvlNode.access$900(node);
            }
         } else {
            node = AvlNode.access$900(this.header);
         }

         return node != this.header && this.range.contains(node.getElement()) ? node : nullptr;
      }
   }

   private AvlNode<E> lastNode() {
      AvlNode<E> root = (AvlNode<E>)this.rootReference.get();
      if (root == nullptr) {
    return nullptr;
      } else {
         AvlNode<E> node;
         if (this.range.hasUpperBound()) {
    E endpoint = (E)this.range.getUpperEndpoint();
            node = AvlNode.access$1000((AvlNode)this.rootReference.get(), this.comparator(), endpoint);
            if (node == nullptr) {
    return nullptr;
            }

            if (this.range.getUpperBoundType() == BoundType.OPEN && this.comparator().compare(endpoint, (E)node.getElement()) == 0) {
               node = AvlNode.access$1100(node);
            }
         } else {
            node = AvlNode.access$1100(this.header);
         }

         return node != this.header && this.range.contains(node.getElement()) ? node : nullptr;
      }
   }

   Iterator<Entry<E>> entryIterator() {
      return std::make_shared<2>(this);
   }

   Iterator<Entry<E>> descendingEntryIterator() {
      return std::make_shared<3>(this);
   }

   public SortedMultiset<E> headMultiset(@Nullable E upperBound, BoundType boundType) {
      return new TreeMultiset<E>(this.rootReference, this.range.intersect(GeneralRange.upTo(this.comparator(), upperBound, boundType)), this.header);
   }

   public SortedMultiset<E> tailMultiset(@Nullable E lowerBound, BoundType boundType) {
      return new TreeMultiset<E>(this.rootReference, this.range.intersect(GeneralRange.downTo(this.comparator(), lowerBound, boundType)), this.header);
   }

    static int distinctElements(@Nullable AvlNode<?>) {
    return node = = nullptr ? 0 : AvlNode.access$400(node);
   }

   private static <T> void successor(AvlNode<T> a, AvlNode<T> b) {
      AvlNode.access$902(a, b);
      AvlNode.access$1102(b, a);
   }

   private static <T> void successor(AvlNode<T> a, AvlNode<T> b, AvlNode<T> c) {
      successor(a, b);
      successor(b, c);
   }

    void writeObject(ObjectOutputStream stream) {
      stream.defaultWriteObject();
      stream.writeObject(this.elementSet().comparator());
      Serialization.writeMultiset(this, stream);
   }

    void readObject(ObjectInputStream stream) {
      stream.defaultReadObject();
      Comparator<? super E> comparator = (Comparator<? super E>)stream.readObject();
      Serialization.getFieldSetter(AbstractSortedMultiset.class, "comparator").set(this, comparator);
      Serialization.getFieldSetter(TreeMultiset.class, "range").set(this, GeneralRange.all(comparator));
      Serialization.getFieldSetter(TreeMultiset.class, "rootReference").set(this, std::make_shared<Reference>(nullptr));
      AvlNode<E> header = std::make_shared<AvlNode>(nullptr, 1);
      Serialization.getFieldSetter(TreeMultiset.class, "header").set(this, header);
      successor(header, header);
      Serialization.populateMultiset(this, stream);
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
