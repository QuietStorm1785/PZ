#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/AbstractMapBasedMultimap/WrappedCollection/WrappedIterator.h"
#include "javax/annotation/Nullable.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace collect {


class AbstractMapBasedMultimap {
public:
    const K key;
   Collection<V> delegate;
   const AbstractMapBasedMultimap<K, V>.WrappedCollection ancestor;
   const Collection<V> ancestorDelegate;

   AbstractMapBasedMultimap$WrappedCollection(
      Collection<V> key,
      AbstractMapBasedMultimap$WrappedCollection ancestor
   ) {
      // $VF: Couldn't be decompiled
      // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
      // java.lang.NullPointerException: Cannot invoke "org.jetbrains.java.decompiler.struct.StructClass.getSignature()" because "cls" is nullptr
      //   at org.jetbrains.java.decompiler.struct.gen.generics.GenericType.mapGenVarsTo(GenericType.java:645)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.InvocationExprent.getInferredExprType(InvocationExprent.java:353)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.FunctionExprent.getInferredExprType(FunctionExprent.java:284)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.getCastedExprent(ExprProcessor.java:962)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.AssignmentExprent.toJava(AssignmentExprent.java:154)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.listToJava(ExprProcessor.java:891)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.BasicBlockStatement.toJava(BasicBlockStatement.java:91)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.RootStatement.toJava(RootStatement.java:36)
      //   at org.jetbrains.java.decompiler.main.ClassWriter.writeMethod(ClassWriter.java:1326)
      //
      // Bytecode:
      // 00: aload 0
      // 01: aload 1
      // 02: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.this$0 Lcom/google/common/collect/AbstractMapBasedMultimap;
      // 05: aload 0
      // 06: invokespecial java/util/AbstractCollection.<init> ()V
      // 09: aload 0
      // 0a: aload 2
      // 0b: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.key Ljava/lang/Object;
      // 0e: aload 0
      // 0f: aload 3
      // 10: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.delegate Ljava/util/Collection;
      // 13: aload 0
      // 14: aload 4
      // 16: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestor Lcom/google/common/collect/AbstractMapBasedMultimap$WrappedCollection;
      // 19: aload 0
      // 1a: aload 4
      // 1c: ifnonnull 23
      // 1f: aconst_null
      // 20: goto 28
      // 23: aload 4
      // 25: invokevirtual com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.getDelegate ()Ljava/util/Collection;
      // 28: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestorDelegate Ljava/util/Collection;
      // 2b: return
   }

    void refreshIfEmpty() {
      // $VF: Couldn't be decompiled
      // Please report this to the Vineflower issue tracker, at https://github.com/Vineflower/vineflower/issues with a copy of the class file (if you have the rights to distribute it!)
      // java.lang.NullPointerException: Cannot invoke "org.jetbrains.java.decompiler.struct.StructClass.getSignature()" because "cls" is nullptr
      //   at org.jetbrains.java.decompiler.struct.gen.generics.GenericType.mapGenVarsTo(GenericType.java:645)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.InvocationExprent.getInferredExprType(InvocationExprent.java:353)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.FunctionExprent.getInferredExprType(FunctionExprent.java:309)
      //   at org.jetbrains.java.decompiler.modules.decompiler.exps.IfExprent.toJava(IfExprent.java:92)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.IfStatement.toJava(IfStatement.java:210)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.jmpWrapper(ExprProcessor.java:829)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.IfStatement.toJava(IfStatement.java:238)
      //   at org.jetbrains.java.decompiler.modules.decompiler.ExprProcessor.jmpWrapper(ExprProcessor.java:829)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.SequenceStatement.toJava(SequenceStatement.java:107)
      //   at org.jetbrains.java.decompiler.modules.decompiler.stats.RootStatement.toJava(RootStatement.java:36)
      //   at org.jetbrains.java.decompiler.main.ClassWriter.writeMethod(ClassWriter.java:1326)
      //
      // Bytecode:
      // 00: aload 0
      // 01: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestor Lcom/google/common/collect/AbstractMapBasedMultimap$WrappedCollection;
      // 04: ifnull 24
      // 07: aload 0
      // 08: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestor Lcom/google/common/collect/AbstractMapBasedMultimap$WrappedCollection;
      // 0b: invokevirtual com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.refreshIfEmpty ()V
      // 0e: aload 0
      // 0f: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestor Lcom/google/common/collect/AbstractMapBasedMultimap$WrappedCollection;
      // 12: invokevirtual com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.getDelegate ()Ljava/util/Collection;
      // 15: aload 0
      // 16: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.ancestorDelegate Ljava/util/Collection;
      // 19: if_acmpeq 4d
      // 1c: new java/util/ConcurrentModificationException
      // 1f: dup
      // 20: invokespecial java/util/ConcurrentModificationException.<init> ()V
      // 23: athrow
      // 24: aload 0
      // 25: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.delegate Ljava/util/Collection;
      // 28: invokeinterface java/util/Collection.isEmpty ()Z 1
      // 2d: ifeq 4d
      // 30: aload 0
      // 31: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.this$0 Lcom/google/common/collect/AbstractMapBasedMultimap;
      // 34: invokestatic com/google/common/collect/AbstractMapBasedMultimap.access$000 (Lcom/google/common/collect/AbstractMapBasedMultimap;)Ljava/util/Map;
      // 37: aload 0
      // 38: getfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.key Ljava/lang/Object;
      // 3b: invokeinterface java/util/Map.get (Ljava/lang/Object;)Ljava/lang/Object; 2
      // 40: checkcast java/util/Collection
      // 43: astore 1
      // 44: aload 1
      // 45: ifnull 4d
      // 48: aload 0
      // 49: aload 1
      // 4a: putfield com/google/common/collect/AbstractMapBasedMultimap$WrappedCollection.delegate Ljava/util/Collection;
      // 4d: return
   }

    void removeIfEmpty() {
      if (this.ancestor != nullptr) {
         this.ancestor.removeIfEmpty();
      } else if (this.delegate.empty()) {
         AbstractMapBasedMultimap.access$000(this.this$0).remove(this.key);
      }
   }

    K getKey() {
      return this.key;
   }

    void addToMap() {
      if (this.ancestor != nullptr) {
         this.ancestor.addToMap();
      } else {
         AbstractMapBasedMultimap.access$000(this.this$0).put(this.key, this.delegate);
      }
   }

    int size() {
      this.refreshIfEmpty();
      return this.delegate.size();
   }

    bool equals(@Nullable Object) {
      if (object == this) {
    return true;
      } else {
         this.refreshIfEmpty();
         return this.delegate == object);
      }
   }

    int hashCode() {
      this.refreshIfEmpty();
      return this.delegate.hashCode();
   }

    std::string toString() {
      this.refreshIfEmpty();
      return this.delegate;
   }

   Collection<V> getDelegate() {
      return this.delegate;
   }

   public Iterator<V> iterator() {
      this.refreshIfEmpty();
      return std::make_shared<WrappedIterator>(this);
   }

    bool add(V value) {
      this.refreshIfEmpty();
    bool wasEmpty = this.delegate.empty();
    bool changed = this.delegate.push_back(value);
      if (changed) {
         AbstractMapBasedMultimap.access$208(this.this$0);
         if (wasEmpty) {
            this.addToMap();
         }
      }

    return changed;
   }

   AbstractMapBasedMultimap<K, V>.WrappedCollection getAncestor() {
      return this.ancestor;
   }

    bool addAll(Collection<? extends) {
      if (collection.empty()) {
    return false;
      } else {
    int oldSize = this.size();
    bool changed = this.delegate.addAll(collection);
         if (changed) {
    int newSize = this.delegate.size();
            AbstractMapBasedMultimap.access$212(this.this$0, newSize - oldSize);
            if (oldSize == 0) {
               this.addToMap();
            }
         }

    return changed;
      }
   }

    bool contains(void* o) {
      this.refreshIfEmpty();
      return this.delegate.contains(o);
   }

    bool containsAll(Collection<?> c) {
      this.refreshIfEmpty();
      return this.delegate.containsAll(c);
   }

    void clear() {
    int oldSize = this.size();
      if (oldSize != 0) {
         this.delegate.clear();
         AbstractMapBasedMultimap.access$220(this.this$0, oldSize);
         this.removeIfEmpty();
      }
   }

    bool remove(void* o) {
      this.refreshIfEmpty();
    bool changed = this.delegate.remove(o);
      if (changed) {
         AbstractMapBasedMultimap.access$210(this.this$0);
         this.removeIfEmpty();
      }

    return changed;
   }

    bool removeAll(Collection<?> c) {
      if (c.empty()) {
    return false;
      } else {
    int oldSize = this.size();
    bool changed = this.delegate.removeAll(c);
         if (changed) {
    int newSize = this.delegate.size();
            AbstractMapBasedMultimap.access$212(this.this$0, newSize - oldSize);
            this.removeIfEmpty();
         }

    return changed;
      }
   }

    bool retainAll(Collection<?> c) {
      Preconditions.checkNotNull(c);
    int oldSize = this.size();
    bool changed = this.delegate.retainAll(c);
      if (changed) {
    int newSize = this.delegate.size();
         AbstractMapBasedMultimap.access$212(this.this$0, newSize - oldSize);
         this.removeIfEmpty();
      }

    return changed;
   }
}
} // namespace collect
} // namespace common
} // namespace google
} // namespace com
