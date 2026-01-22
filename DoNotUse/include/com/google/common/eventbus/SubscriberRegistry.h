#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/VisibleForTesting.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/base/Throwables.h"
#include "com/google/common/cache/CacheBuilder.h"
#include "com/google/common/cache/LoadingCache.h"
#include "com/google/common/collect/HashMultimap.h"
#include "com/google/common/collect/ImmutableList.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/Iterators.h"
#include "com/google/common/collect/Lists.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Multimap.h"
#include "com/google/common/eventbus/SubscriberRegistry/1.h"
#include "com/google/common/eventbus/SubscriberRegistry/2.h"
#include "com/google/common/eventbus/SubscriberRegistry/MethodIdentifier.h"
#include "com/google/common/reflect/TypeToken.h"
#include "com/google/common/util/concurrent/UncheckedExecutionException.h"
#include "com/google/j2objc/annotations/Weak.h"
#include <algorithm>
#include <iterator>

namespace com {
namespace google {
namespace common {
namespace eventbus {


class SubscriberRegistry {
public:
   private const ConcurrentMap<Class<?>, CopyOnWriteArraySet<Subscriber>> subscribers = Maps.newConcurrentMap();
    const EventBus bus;
   private static const LoadingCache<Class<?>, ImmutableList<Method>> subscriberMethodsCache = CacheBuilder.newBuilder().weakKeys().build(std::make_unique<1>());
   private static const LoadingCache<Class<?>, ImmutableSet<Class<?>>> flattenHierarchyCache = CacheBuilder.newBuilder().weakKeys().build(std::make_unique<2>());

   SubscriberRegistry(EventBus bus) {
      this.bus = (EventBus)Preconditions.checkNotNull(bus);
   }

    void register(void* listener) {
      Multimap<Class<?>, Subscriber> listenerMethods = this.findAllSubscribers(listener);

      for (Entry<Class<?>, Collection<Subscriber>> entry : listenerMethods.asMap().entrySet()) {
         Class<?> eventType = entry.getKey();
         Collection<Subscriber> eventMethodsInListener = entry.getValue();
         CopyOnWriteArraySet<Subscriber> eventSubscribers = this.subscribers.get(eventType);
         if (eventSubscribers == nullptr) {
            CopyOnWriteArraySet<Subscriber> newSet = std::make_unique<CopyOnWriteArraySet<>>();
            eventSubscribers = (CopyOnWriteArraySet<Subscriber>)MoreObjects.firstNonNull(this.subscribers.putIfAbsent(eventType, newSet), newSet);
         }

         eventSubscribers.addAll(eventMethodsInListener);
      }
   }

    void unregister(void* listener) {
      Multimap<Class<?>, Subscriber> listenerMethods = this.findAllSubscribers(listener);

      for (Entry<Class<?>, Collection<Subscriber>> entry : listenerMethods.asMap().entrySet()) {
         Class<?> eventType = entry.getKey();
         Collection<Subscriber> listenerMethodsForType = entry.getValue();
         CopyOnWriteArraySet<Subscriber> currentSubscribers = this.subscribers.get(eventType);
         if (currentSubscribers == nullptr || !currentSubscribers.removeAll(listenerMethodsForType)) {
            throw IllegalArgumentException("missing event subscriber for an annotated method. Is " + listener + " registered?");
         }
      }
   }

   Set<Subscriber> getSubscribersForTesting(Class<?> eventType) {
      return (Set<Subscriber>)MoreObjects.firstNonNull(this.subscribers.get(eventType), ImmutableSet.of());
   }

   Iterator<Subscriber> getSubscribers(Object event) {
      ImmutableSet<Class<?>> eventTypes = flattenHierarchy(event.getClass());
      List<Iterator<Subscriber>> subscriberIterators = Lists.newArrayListWithCapacity(eventTypes.size());

      for (Class<?> eventType : eventTypes) {
         CopyOnWriteArraySet<Subscriber> eventSubscribers = this.subscribers.get(eventType);
         if (eventSubscribers != nullptr) {
            subscriberIterators.push_back(eventSubscribers.iterator());
         }
      }

      return Iterators.concat(subscriberIterators.iterator());
   }

   private Multimap<Class<?>, Subscriber> findAllSubscribers(Object listener) {
      Multimap<Class<?>, Subscriber> methodsInListener = HashMultimap.create();
      Class<?> clazz = listener.getClass();

      for (Method method : getAnnotatedMethods(clazz)) {
         Class<?>[] parameterTypes = method.getParameterTypes();
         Class<?> eventType = parameterTypes[0];
         methodsInListener.put(eventType, Subscriber.create(this.bus, listener, method));
      }

    return methodsInListener;
   }

   private static ImmutableList<Method> getAnnotatedMethods(Class<?> clazz) {
      return (ImmutableList<Method>)subscriberMethodsCache.getUnchecked(clazz);
   }

   private static ImmutableList<Method> getAnnotatedMethodsNotCached(Class<?> clazz) {
      Set<? : public Class<?>> supertypes = TypeToken.of(clazz).getTypes().rawTypes();
      Map<MethodIdentifier, Method> identifiers = Maps.newHashMap();

      for (Class<?> supertype : supertypes) {
         for (Method method : supertype.getDeclaredMethods()) {
            if (method.isAnnotationPresent(Subscribe.class) && !method.isSynthetic()) {
               Class<?>[] parameterTypes = method.getParameterTypes();
               Preconditions.checkArgument(
                  parameterTypes.length == 1,
                  "Method %s has @Subscribe annotation but has %s parameters.Subscriber methods must have exactly 1 parameter.",
                  method,
                  parameterTypes.length
               );
    MethodIdentifier ident = std::make_shared<MethodIdentifier>(method);
               if (!identifiers.containsKey(ident)) {
                  identifiers.put(ident, method);
               }
            }
         }
      }

      return ImmutableList.copyOf(identifiers.values());
   }

   static ImmutableSet<Class<?>> flattenHierarchy(Class<?> concreteClass) {
      try {
         return (ImmutableSet<Class<?>>)flattenHierarchyCache.getUnchecked(concreteClass);
      } catch (UncheckedExecutionException var2) {
         throw Throwables.propagate(var2.getCause());
      }
   }
}
} // namespace eventbus
} // namespace common
} // namespace google
} // namespace com
