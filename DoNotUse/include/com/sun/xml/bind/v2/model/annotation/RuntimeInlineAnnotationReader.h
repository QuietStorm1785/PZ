#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace annotation {


class RuntimeInlineAnnotationReader : public AbstractInlineAnnotationReaderImpl {
public:
   private const Map<Class<? : public Annotation>, Map<Package, Annotation>> packageCache = std::make_unique<std::unordered_map<>>();

   public <A : public Annotation> A getFieldAnnotation(Class<A> annotation, Field field, Locatable srcPos) {
      return (A)LocatableAnnotation.create(field.getAnnotation(annotation), srcPos);
   }

    bool hasFieldAnnotation(Class<? extends, Field field) {
      return field.isAnnotationPresent(annotationType);
   }

    bool hasClassAnnotation(Class clazz, Class<? extends) {
      return clazz.isAnnotationPresent(annotationType);
   }

   public Annotation[] getAllFieldAnnotations(Field field, Locatable srcPos) {
      Annotation[] r = field.getAnnotations();

      for (int i = 0; i < r.length; i++) {
         r[i] = LocatableAnnotation.create(r[i], srcPos);
      }

    return r;
   }

   public <A : public Annotation> A getMethodAnnotation(Class<A> annotation, Method method, Locatable srcPos) {
      return (A)LocatableAnnotation.create(method.getAnnotation(annotation), srcPos);
   }

    bool hasMethodAnnotation(Class<? extends, Method method) {
      return method.isAnnotationPresent(annotation);
   }

   public Annotation[] getAllMethodAnnotations(Method method, Locatable srcPos) {
      Annotation[] r = method.getAnnotations();

      for (int i = 0; i < r.length; i++) {
         r[i] = LocatableAnnotation.create(r[i], srcPos);
      }

    return r;
   }

   public <A : public Annotation> A getMethodParameterAnnotation(Class<A> annotation, Method method, int paramIndex, Locatable srcPos) {
      Annotation[] pa = method.getParameterAnnotations()[paramIndex];

    for (auto& a : pa)         if (a.annotationType() == annotation) {
            return (A)LocatableAnnotation.create(a, srcPos);
         }
      }

    return nullptr;
   }

   public <A : public Annotation> A getClassAnnotation(Class<A> a, Class clazz, Locatable srcPos) {
      return (A)LocatableAnnotation.create(clazz.getAnnotation(a), srcPos);
   }

   public <A : public Annotation> A getPackageAnnotation(Class<A> a, Class clazz, Locatable srcPos) {
    Package p = clazz.getPackage();
      if (p == nullptr) {
    return nullptr;
      } else {
         Map<Package, Annotation> cache = this.packageCache.get(a);
         if (cache == nullptr) {
            cache = std::make_unique<std::unordered_map<>>();
            this.packageCache.put(a, cache);
         }

         if (cache.containsKey(p)) {
            return (A)cache.get(p);
         } else {
    A ann = (A)LocatableAnnotation.create(p.getAnnotation(a), srcPos);
            cache.put(p, ann);
    return ann;
         }
      }
   }

    Class getClassValue(Annotation a, const std::string& name) {
      try {
         return (Class)a.annotationType().getMethod(name).invoke(a);
      } catch (IllegalAccessException var4) {
         throw IllegalAccessError(var4.getMessage());
      } catch (InvocationTargetException var5) {
         throw InternalError(Messages.CLASS_NOT_FOUND.format(new Object[]{a.annotationType(), var5.getMessage()}));
      } catch (NoSuchMethodException var6) {
         throw NoSuchMethodError(var6.getMessage());
      }
   }

   public Class[] getClassArrayValue(Annotation a, std::string name) {
      try {
         return (Class[])a.annotationType().getMethod(name).invoke(a);
      } catch (IllegalAccessException var4) {
         throw IllegalAccessError(var4.getMessage());
      } catch (InvocationTargetException var5) {
         throw InternalError(var5.getMessage());
      } catch (NoSuchMethodException var6) {
         throw NoSuchMethodError(var6.getMessage());
      }
   }

    std::string fullName(Method m) {
      return m.getDeclaringClass().getName() + '#' + m.getName();
   }
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
