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


class AnnotationSource {
public:
    virtual ~AnnotationSource() = default;
   <A : public Annotation> A readAnnotation(Class<A> var1);

    bool hasAnnotation(Class<? extends);
}
} // namespace annotation
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
