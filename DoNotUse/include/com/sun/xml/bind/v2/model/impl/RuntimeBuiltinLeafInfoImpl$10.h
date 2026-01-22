#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/10/1.h"
#include "com/sun/xml/bind/v2/model/impl/RuntimeBuiltinLeafInfoImpl/PcdataImpl.h"
#include "com/sun/xml/bind/v2/runtime/XMLSerializer.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/Base64Data.h"
#include "com/sun/xml/bind/v2/runtime/unmarshaller/UnmarshallingContext.h"
#include "com/sun/xml/bind/v2/util/ByteArrayOutputStreamEx.h"
#include "java/awt/Graphics.h"
#include "java/awt/Image.h"
#include "java/awt/MediaTracker.h"
#include "java/awt/image/BufferedImage.h"
#include "javax/imageio/ImageIO.h"
#include "javax/imageio/ImageWriter.h"
#include "javax/imageio/stream/ImageOutputStream.h"
#include "javax/xml/bind/helpers/ValidationEventImpl.h"
#include "javax/xml/namespace/QName.h"
#include "org/xml/sax/SAXException.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace com {
namespace sun {
namespace xml {
namespace bind {
namespace v2 {
namespace model {
namespace impl {


class RuntimeBuiltinLeafInfoImpl {
public:
   RuntimeBuiltinLeafInfoImpl$10(Class type, QName... typeNames) {
      super(type, typeNames);
   }

    Image parse(CharSequence text) {
      try {
    InputStream is;
         if (dynamic_cast<Base64Data*>(text) != nullptr) {
            is = ((Base64Data)text).getInputStream();
         } else {
            is = std::make_shared<ByteArrayInputStream>(RuntimeBuiltinLeafInfoImpl.access$100(text));
         }

    BufferedImage var3;
         try {
            var3 = ImageIO.read(is);
         } finally {
            is.close();
         }

    return var3;
      } catch (IOException var8) {
         UnmarshallingContext.getInstance().handleError(var8);
    return nullptr;
      }
   }

    BufferedImage convertToBufferedImage(Image image) {
      if (dynamic_cast<BufferedImage*>(image) != nullptr) {
         return (BufferedImage)image;
      } else {
    MediaTracker tracker = std::make_shared<MediaTracker>(std::make_shared<1>(this));
         tracker.addImage(image, 0);

         try {
            tracker.waitForAll();
         } catch (InterruptedException var5) {
            throw IOException(var5.getMessage());
         }

    BufferedImage bufImage = std::make_shared<BufferedImage>(image.getWidth(nullptr), image.getHeight(nullptr), 2);
    Graphics g = bufImage.createGraphics();
         g.drawImage(image, 0, 0, nullptr);
    return bufImage;
      }
   }

    Base64Data print(Image v) {
    ByteArrayOutputStreamEx imageData = std::make_shared<ByteArrayOutputStreamEx>();
    XMLSerializer xs = XMLSerializer.getInstance();
    std::string mimeType = xs.getXMIMEContentType();
      if (mimeType == nullptr || mimeType.startsWith("image/*")) {
         mimeType = "image/png";
      }

      try {
         Iterator<ImageWriter> itr = ImageIO.getImageWritersByMIMEType(mimeType);
         if (!itr.hasNext()) {
            xs.handleEvent(std::make_shared<ValidationEventImpl>(1, Messages.NO_IMAGE_WRITER.format(new Object[]{mimeType}), xs.getCurrentLocation(nullptr)));
            throw RuntimeException("no encoder for MIME type " + mimeType);
         }

    ImageWriter w = itr.next();
    ImageOutputStream os = ImageIO.createImageOutputStream(imageData);
         w.setOutput(os);
         w.write(this.convertToBufferedImage(v));
         os.close();
         w.dispose();
      } catch (IOException var8) {
         xs.handleError(var8);
         throw RuntimeException(var8);
      }

    Base64Data bd = std::make_shared<Base64Data>();
      imageData.set(bd, mimeType);
    return bd;
   }
}
} // namespace impl
} // namespace model
} // namespace v2
} // namespace bind
} // namespace xml
} // namespace sun
} // namespace com
