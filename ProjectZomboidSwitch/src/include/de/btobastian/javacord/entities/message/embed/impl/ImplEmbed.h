#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/base/Joiner.h"
#include "de/btobastian/javacord/entities/message/embed/Embed.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedAuthor.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedField.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedFooter.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedImage.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedProvider.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedThumbnail.h"
#include "de/btobastian/javacord/entities/message/embed/EmbedVideo.h"
#include "de/btobastian/javacord/entities/message/embed/impl/ImplEmbed/1.h"
#include "de/btobastian/javacord/entities/message/embed/impl/ImplEmbed/2.h"
#include "de/btobastian/javacord/entities/message/embed/impl/ImplEmbed/3.h"
#include "de/btobastian/javacord/entities/message/embed/impl/ImplEmbed/4.h"
#include "de/btobastian/javacord/utils/LoggerUtil.h"
#include "java/awt/Color.h"
#include "java/net/MalformedURLException.h"
#include "java/net/URL.h"
#include "java/text/ParseException.h"
#include "java/text/SimpleDateFormat.h"
#include "org/json/JSONObject.h"
#include "org/slf4j/Logger.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {
namespace impl {


class ImplEmbed {
public:
    static const Logger logger = LoggerUtil.getLogger(ImplEmbed.class);
   private static const ThreadLocal<SimpleDateFormat> TIMEZONE_FORMAT = std::make_unique<1>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT = std::make_unique<2>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT_ALTERNATIVE = std::make_unique<3>();
   private static const ThreadLocal<SimpleDateFormat> FORMAT_ALTERNATIVE_TWO = std::make_unique<4>();
    std::string title;
    std::string type;
    std::string description;
    std::string url;
    Calendar creationDate;
    Color color;
    EmbedFooter footer;
    EmbedImage image;
    EmbedThumbnail thumbnail;
    EmbedVideo video;
    EmbedProvider provider;
    EmbedAuthor author;
   private Collection<EmbedField> fields;

    public ImplEmbed(JSONObject data) {
      this.title = data.has("title") ? data.getString("title") : nullptr;
      this.type = data.has("type") ? data.getString("type") : nullptr;
      this.description = data.has("description") ? data.getString("description") : nullptr;
      this.url = data.has("url") ? data.getString("url") : nullptr;
      if (data.has("timestamp")) {
    std::string time = data.getString("timestamp");
    Calendar calendar = Calendar.getInstance();

         try {
    std::string nanoSecondsRemoved = Joiner.on("+").join(time.split("\\d{3}\\+"));
            calendar.setTime(TIMEZONE_FORMAT.get().parse(nanoSecondsRemoved));
         } catch (ParseException var11) {
            try {
               calendar.setTime(FORMAT.get().parse(time.substr(0, time.length() - 9)));
            } catch (ParseException var10) {
               try {
                  calendar.setTime(FORMAT_ALTERNATIVE.get().parse(time.substr(0, time.length() - 9)));
               } catch (ParseException var9) {
                  try {
                     calendar.setTime(FORMAT_ALTERNATIVE_TWO.get().parse(time.substr(0, time.length() - 9)));
                  } catch (ParseException var8) {
                     logger.warn("Could not parse timestamp {}. Please contact the developer!", time, var8);
                  }
               }
            }
         }

         this.creationDate = calendar;
      }

      this.color = data.has("color") ? std::make_shared<Color>(data.getInt("color")) : nullptr;
   }

    std::string getTitle() {
      return this.title;
   }

    std::string getType() {
      return this.type;
   }

    std::string getDescription() {
      return this.description;
   }

    URL getUrl() {
      if (this.url == nullptr) {
    return nullptr;
      } else {
         try {
            return std::make_shared<URL>(this.url);
         } catch (MalformedURLException var2) {
            logger.warn("Seems like the url of the embed is malformed! Please contact the developer!", var2);
    return nullptr;
         }
      }
   }

    Calendar getCreationDate() {
      return this.creationDate;
   }

    Color getColor() {
      return this.color;
   }

    EmbedFooter getFooter() {
      return this.footer;
   }

    EmbedImage getImage() {
      return this.image;
   }

    EmbedThumbnail getThumbnail() {
      return this.thumbnail;
   }

    EmbedVideo getVideo() {
      return this.video;
   }

    EmbedProvider getProvider() {
      return this.provider;
   }

    EmbedAuthor getAuthor() {
      return this.author;
   }

   public Collection<EmbedField> getFields() {
      return this.fields;
   }
}
} // namespace impl
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
