#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/math/BigDecimal.h"
#include "java/math/BigInteger.h"
#include "javax/xml/namespace/NamespaceContext.h"
#include "javax/xml/namespace/QName.h"
#include <algorithm>

namespace javax {
namespace xml {
namespace bind {


class DatatypeConverterInterface {
public:
    virtual ~DatatypeConverterInterface() = default;
    std::string parseString(const std::string& var1);

    BigInteger parseInteger(const std::string& var1);

    int parseInt(const std::string& var1);

    long parseLong(const std::string& var1);

    short parseShort(const std::string& var1);

    BigDecimal parseDecimal(const std::string& var1);

    float parseFloat(const std::string& var1);

    double parseDouble(const std::string& var1);

    bool parseBoolean(const std::string& var1);

    uint8_t parseByte(const std::string& var1);

    QName parseQName(const std::string& var1, NamespaceContext var2);

    Calendar parseDateTime(const std::string& var1);

   byte[] parseBase64Binary(std::string var1);

   byte[] parseHexBinary(std::string var1);

    long parseUnsignedInt(const std::string& var1);

    int parseUnsignedShort(const std::string& var1);

    Calendar parseTime(const std::string& var1);

    Calendar parseDate(const std::string& var1);

    std::string parseAnySimpleType(const std::string& var1);

    std::string printString(const std::string& var1);

    std::string printInteger(BigInteger var1);

    std::string printInt(int var1);

    std::string printLong(long var1);

    std::string printShort(short var1);

    std::string printDecimal(BigDecimal var1);

    std::string printFloat(float var1);

    std::string printDouble(double var1);

    std::string printBoolean(bool var1);

    std::string printByte(uint8_t var1);

    std::string printQName(QName var1, NamespaceContext var2);

    std::string printDateTime(Calendar var1);

    std::string printBase64Binary(byte[] var1);

    std::string printHexBinary(byte[] var1);

    std::string printUnsignedInt(long var1);

    std::string printUnsignedShort(int var1);

    std::string printTime(Calendar var1);

    std::string printDate(Calendar var1);

    std::string printAnySimpleType(const std::string& var1);
}
} // namespace bind
} // namespace xml
} // namespace javax
