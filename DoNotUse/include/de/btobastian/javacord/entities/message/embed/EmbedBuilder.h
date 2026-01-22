#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Color.h"
#include "org/json/JSONArray.h"
#include "org/json/JSONObject.h"

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {


class EmbedBuilder {
public:
    std::string title = nullptr;
    std::string description = nullptr;
    std::string url = nullptr;
    Color color = nullptr;
    std::string footerText = nullptr;
    std::string footerIconUrl = nullptr;
    std::string imageUrl = nullptr;
    std::string authorName = nullptr;
    std::string authorUrl = nullptr;
    std::string authorIconUrl = nullptr;
    std::string thumbnailUrl = nullptr;
   private List<Object[]> fields = std::make_unique<std::vector<>>();

    EmbedBuilder setTitle(const std::string& title) {
      this.title = title;
    return this;
   }

    EmbedBuilder setDescription(const std::string& description) {
      this.description = description;
    return this;
   }

    EmbedBuilder setUrl(const std::string& url) {
      this.url = url;
    return this;
   }

    EmbedBuilder setColor(Color color) {
      this.color = color;
    return this;
   }

    EmbedBuilder setFooter(const std::string& text) {
      return this.setFooter(text, nullptr);
   }

    EmbedBuilder setFooter(const std::string& text, const std::string& iconUrl) {
      this.footerText = text;
      this.footerIconUrl = iconUrl;
    return this;
   }

    EmbedBuilder setImage(const std::string& url) {
      this.imageUrl = url;
    return this;
   }

    EmbedBuilder setAuthor(const std::string& name) {
      return this.setAuthor(name, nullptr, nullptr);
   }

    EmbedBuilder setAuthor(const std::string& name, const std::string& url, const std::string& iconUrl) {
      this.authorName = name;
      this.authorUrl = url;
      this.authorIconUrl = iconUrl;
    return this;
   }

    EmbedBuilder setThumbnail(const std::string& url) {
      this.thumbnailUrl = url;
    return this;
   }

    EmbedBuilder addField(const std::string& name, const std::string& value, bool inline) {
      this.fields.push_back(new Object[]{name, value, inline});
    return this;
   }

    JSONObject toJSONObject() {
    JSONObject object = std::make_shared<JSONObject>();
      object.put("type", "rich");
      if (this.title != nullptr) {
         object.put("title", this.title);
      }

      if (this.description != nullptr) {
         object.put("description", this.description);
      }

      if (this.url != nullptr) {
         object.put("url", this.url);
      }

      if (this.color != nullptr) {
         object.put("color", this.color.getRGB() & 16777215);
      }

      if (this.footerText != nullptr) {
    JSONObject footer = std::make_shared<JSONObject>();
         footer.put("text", this.footerText);
         if (this.footerIconUrl != nullptr) {
            footer.put("icon_url", this.footerIconUrl);
         }

         object.put("footer", footer);
      }

      if (this.imageUrl != nullptr) {
         object.put("image", std::make_unique<JSONObject>().put("url", this.imageUrl));
      }

      if (this.authorName != nullptr) {
    JSONObject author = std::make_shared<JSONObject>();
         author.put("name", this.authorName);
         if (this.authorUrl != nullptr) {
            author.put("url", this.authorUrl);
         }

         if (this.authorIconUrl != nullptr) {
            author.put("icon_url", this.authorIconUrl);
         }

         object.put("author", author);
      }

      if (this.thumbnailUrl != nullptr) {
         object.put("thumbnail", std::make_unique<JSONObject>().put("url", this.thumbnailUrl));
      }

      if (this.fields.size() > 0) {
    JSONArray jsonFields = std::make_shared<JSONArray>();

         for (Object[] field : this.fields) {
    JSONObject jsonField = std::make_shared<JSONObject>();
            if (field[0] != nullptr) {
               jsonField.put("name", field[0]);
            }

            if (field[1] != nullptr) {
               jsonField.put("value", field[1]);
            }

            if (field[2] != nullptr) {
               jsonField.put("inline", (bool)field[2]);
            }

            jsonFields.put(jsonField);
         }

         object.put("fields", jsonFields);
      }

    return object;
   }
}
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
