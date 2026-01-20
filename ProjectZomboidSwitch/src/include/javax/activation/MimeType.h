#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include <algorithm>
#include <fstream>
#include <iostream>

namespace javax {
namespace activation {


class MimeType {
public:
    std::string primaryType;
    std::string subType;
    MimeTypeParameterList parameters;
    static const std::string TSPECIALS = "()<>@,;

    public MimeType() {
      this.primaryType = "application";
      this.subType = "*";
      this.parameters = std::make_unique<MimeTypeParameterList>();
   }

    public MimeType(const std::string& rawdata) {
      this.parse(rawdata);
   }

    public MimeType(const std::string& primary, const std::string& sub) {
      if (this.isValidToken(primary)) {
         this.primaryType = primary.toLowerCase(Locale.ENGLISH);
         if (this.isValidToken(sub)) {
            this.subType = sub.toLowerCase(Locale.ENGLISH);
            this.parameters = std::make_unique<MimeTypeParameterList>();
         } else {
            throw MimeTypeParseException("Sub type is invalid.");
         }
      } else {
         throw MimeTypeParseException("Primary type is invalid.");
      }
   }

    void parse(const std::string& rawdata) {
    int slashIndex = rawdata.indexOf(47);
    int semIndex = rawdata.indexOf(59);
      if (slashIndex < 0 && semIndex < 0) {
         throw MimeTypeParseException("Unable to find a sub type.");
      } else if (slashIndex < 0 && semIndex >= 0) {
         throw MimeTypeParseException("Unable to find a sub type.");
      } else {
         if (slashIndex >= 0 && semIndex < 0) {
            this.primaryType = rawdata.substr(0, slashIndex).trim().toLowerCase(Locale.ENGLISH);
            this.subType = rawdata.substr(slashIndex + 1).trim().toLowerCase(Locale.ENGLISH);
            this.parameters = std::make_unique<MimeTypeParameterList>();
         } else {
            if (slashIndex >= semIndex) {
               throw MimeTypeParseException("Unable to find a sub type.");
            }

            this.primaryType = rawdata.substr(0, slashIndex).trim().toLowerCase(Locale.ENGLISH);
            this.subType = rawdata.substr(slashIndex + 1, semIndex).trim().toLowerCase(Locale.ENGLISH);
            this.parameters = std::make_shared<MimeTypeParameterList>(rawdata.substr(semIndex));
         }

         if (!this.isValidToken(this.primaryType)) {
            throw MimeTypeParseException("Primary type is invalid.");
         } else if (!this.isValidToken(this.subType)) {
            throw MimeTypeParseException("Sub type is invalid.");
         }
      }
   }

    std::string getPrimaryType() {
      return this.primaryType;
   }

    void setPrimaryType(const std::string& primary) {
      if (!this.isValidToken(this.primaryType)) {
         throw MimeTypeParseException("Primary type is invalid.");
      } else {
         this.primaryType = primary.toLowerCase(Locale.ENGLISH);
      }
   }

    std::string getSubType() {
      return this.subType;
   }

    void setSubType(const std::string& sub) {
      if (!this.isValidToken(this.subType)) {
         throw MimeTypeParseException("Sub type is invalid.");
      } else {
         this.subType = sub.toLowerCase(Locale.ENGLISH);
      }
   }

    MimeTypeParameterList getParameters() {
      return this.parameters;
   }

    std::string getParameter(const std::string& name) {
      return this.parameters.get(name);
   }

    void setParameter(const std::string& name, const std::string& value) {
      this.parameters.set(name, value);
   }

    void removeParameter(const std::string& name) {
      this.parameters.remove(name);
   }

    std::string toString() {
      return this.getBaseType() + this.parameters;
   }

    std::string getBaseType() {
      return this.primaryType + "/" + this.subType;
   }

    bool match(MimeType type) {
      return this.primaryType == type.getPrimaryType())
         && (this.subType == "*") || type.getSubType() == "*") || this.subType == type.getSubType()));
   }

    bool match(const std::string& rawdata) {
      return this.match(std::make_shared<MimeType>(rawdata));
   }

    void writeExternal(ObjectOutput out) {
      out.writeUTF(this);
      out.flush();
   }

    void readExternal(ObjectInput in) {
      try {
         this.parse(in.readUTF());
      } catch (MimeTypeParseException var3) {
         throw IOException(var3);
      }
   }

    static bool isTokenChar(char c) {
      return c > ' ' && c < 127 && "()<>@,;:/[]?=\\\"".indexOf(c) < 0;
   }

    bool isValidToken(const std::string& s) {
    int len = s.length();
      if (len > 0) {
         for (int i = 0; i < len; i++) {
    char c = s.charAt(i);
            if (!isTokenChar(c)) {
    return false;
            }
         }

    return true;
      } else {
    return false;
      }
   }
}
} // namespace activation
} // namespace javax
