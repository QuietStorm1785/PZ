#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/datatransfer/DataFlavor.h"

namespace javax {
namespace activation {


class ActivationDataFlavor : public DataFlavor {
public:
    std::string mimeType = nullptr;
    MimeType mimeObject = nullptr;
    std::string humanPresentableName = nullptr;
    Class representationClass = nullptr;

    public ActivationDataFlavor(Class representationClass, const std::string& mimeType, const std::string& humanPresentableName) {
      super(mimeType, humanPresentableName);
      this.mimeType = mimeType;
      this.humanPresentableName = humanPresentableName;
      this.representationClass = representationClass;
   }

    public ActivationDataFlavor(Class representationClass, const std::string& humanPresentableName) {
      super(representationClass, humanPresentableName);
      this.mimeType = super.getMimeType();
      this.representationClass = representationClass;
      this.humanPresentableName = humanPresentableName;
   }

    public ActivationDataFlavor(const std::string& mimeType, const std::string& humanPresentableName) {
      super(mimeType, humanPresentableName);
      this.mimeType = mimeType;

      try {
         this.representationClass = Class.forName("java.io.InputStream");
      } catch (ClassNotFoundException var4) {
      }

      this.humanPresentableName = humanPresentableName;
   }

    std::string getMimeType() {
      return this.mimeType;
   }

    Class getRepresentationClass() {
      return this.representationClass;
   }

    std::string getHumanPresentableName() {
      return this.humanPresentableName;
   }

    void setHumanPresentableName(const std::string& humanPresentableName) {
      this.humanPresentableName = humanPresentableName;
   }

    bool equals(DataFlavor dataFlavor) {
      return this.isMimeTypeEqual(dataFlavor) && dataFlavor.getRepresentationClass() == this.representationClass;
   }

    bool isMimeTypeEqual(const std::string& mimeType) {
    MimeType mt = nullptr;

      try {
         if (this.mimeObject == nullptr) {
            this.mimeObject = std::make_shared<MimeType>(this.mimeType);
         }

         mt = std::make_shared<MimeType>(mimeType);
      } catch (MimeTypeParseException var4) {
         return this.mimeType.equalsIgnoreCase(mimeType);
      }

      return this.mimeObject.match(mt);
   }

   /** @deprecated */
    std::string normalizeMimeTypeParameter(const std::string& parameterName, const std::string& parameterValue) {
    return parameterValue;
   }

   /** @deprecated */
    std::string normalizeMimeType(const std::string& mimeType) {
    return mimeType;
   }
}
} // namespace activation
} // namespace javax
