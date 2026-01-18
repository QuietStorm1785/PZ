#ifndef JAVA_TIME_LOCALDATETIME_H
#define JAVA_TIME_LOCALDATETIME_H

#include <string>

namespace java { namespace time {

class LocalDateTime {
public:
 static LocalDateTime now() { return LocalDateTime(); }
 std::string toString() const { return "1970-01-01T00:00:00"; }
};

}} // namespace java::time

#endif // JAVA_TIME_LOCALDATETIME_H
