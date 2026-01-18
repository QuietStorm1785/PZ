#pragma once
#include "zombie/util/Pool.h"
#include "zombie/util/PooledObject.h"
#include <algorithm>
#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace zombie {
namespace util {
namespace lambda {
// Decompiled on Sat Jan 17 08:24:00 EST 2026 with Zomboid Decompiler v0.2.3
// using Vineflower.

class Predicates {
public:
public
 static class Params1 {
 public
 static class CallbackStackItem<E, T1>
 extends Predicates.Params1.StackItem<T1> implements Predicate<E> {
 private
 Predicates.Params1.ICallback<E, T1> predicate;
 private
 static Pool<Predicates.Params1.CallbackStackItem<Object, Object>>
 s_pool = new Pool<>(Predicates.Params1.CallbackStackItem::new);

 bool test(E object) { return this->predicate.test((E)object, this->val1); }

 public
 static<E, T1> Predicates.Params1.CallbackStackItem<E, T1>
 alloc(T1 object, Predicates.Params1.ICallback<E, T1> iCallback) {
 Predicates.Params1.CallbackStackItem callbackStackItem = s_pool.alloc();
 callbackStackItem.val1 = (T1)object;
 callbackStackItem.predicate = iCallback;
 return callbackStackItem;
 }

 void onReleased() {
 this->val1 = nullptr;
 this->predicate = nullptr;
 }
 }

 public interface ICallback<E, T1> {
 bool test(E var1, T1 var2);
 }

 private
 static class StackItem<T1> extends PooledObject {
 T1 val1;
 }
 }

 public static class Params2 {
 public
 static class CallbackStackItem<E, T1, T2>
 extends Predicates.Params2.StackItem<T1, T2> implements Predicate<E> {
 private
 Predicates.Params2.ICallback<E, T1, T2> predicate;
 private
 static Pool<Predicates.Params2.CallbackStackItem<Object, Object, Object>>
 s_pool = new Pool<>(Predicates.Params2.CallbackStackItem::new);

 bool test(E object) {
 return this->predicate.test((E)object, this->val1, this->val2);
 }

 public
 static<E, T1, T2> Predicates.Params2.CallbackStackItem<E, T1, T2>
 alloc(T1 object0, T2 object1,
 Predicates.Params2.ICallback<E, T1, T2> iCallback) {
 Predicates.Params2.CallbackStackItem callbackStackItem = s_pool.alloc();
 callbackStackItem.val1 = (T1)object0;
 callbackStackItem.val2 = (T2)object1;
 callbackStackItem.predicate = iCallback;
 return callbackStackItem;
 }

 void onReleased() {
 this->val1 = nullptr;
 this->val2 = nullptr;
 this->predicate = nullptr;
 }
 }

 public interface ICallback<E, T1, T2> {
 bool test(E var1, T1 var2, T2 var3);
 }

 private
 static class StackItem<T1, T2> extends PooledObject {
 T1 val1;
 T2 val2;
 }
 }

 public static class Params3 {
 public
 static class CallbackStackItem<E, T1, T2, T3>
 extends Predicates.Params3.StackItem<T1, T2, T3> implements
 Predicate<E> {
 private
 Predicates.Params3.ICallback<E, T1, T2, T3> predicate;
 private
 static Pool<
 Predicates.Params3.CallbackStackItem<Object, Object, Object, Object>>
 s_pool = new Pool<>(Predicates.Params3.CallbackStackItem::new);

 bool test(E object) {
 return this->predicate.test((E)object, this->val1, this->val2, this->val3);
 }

 public
 static<E, T1, T2, T3> Predicates.Params3.CallbackStackItem<E, T1, T2, T3>
 alloc(T1 object0, T2 object1, T3 object2,
 Predicates.Params3.ICallback<E, T1, T2, T3> iCallback) {
 Predicates.Params3.CallbackStackItem callbackStackItem = s_pool.alloc();
 callbackStackItem.val1 = (T1)object0;
 callbackStackItem.val2 = (T2)object1;
 callbackStackItem.val3 = (T3)object2;
 callbackStackItem.predicate = iCallback;
 return callbackStackItem;
 }

 void onReleased() {
 this->val1 = nullptr;
 this->val2 = nullptr;
 this->val3 = nullptr;
 this->predicate = nullptr;
 }
 }

 public interface ICallback<E, T1, T2, T3> {
 bool test(E var1, T1 var2, T2 var3, T3 var4);
 }

 private
 static class StackItem<T1, T2, T3> extends PooledObject {
 T1 val1;
 T2 val2;
 T3 val3;
 }
 }
}
} // namespace lambda
} // namespace util
} // namespace zombie
