#pragma once
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "java/awt/Color.h"
#include "java/net/URL.h"
#include <algorithm>

namespace de {
namespace btobastian {
namespace javacord {
namespace entities {
namespace message {
namespace embed {


class Embed {
public:
    virtual ~Embed() = default;
    std::string getTitle();

    std::string getType();

    std::string getDescription();

    URL getUrl();

    Calendar getCreationDate();

    Color getColor();

    EmbedFooter getFooter();

    EmbedImage getImage();

    EmbedThumbnail getThumbnail();

    EmbedVideo getVideo();

    EmbedProvider getProvider();

    EmbedAuthor getAuthor();

   Collection<EmbedField> getFields();
}
} // namespace embed
} // namespace message
} // namespace entities
} // namespace javacord
} // namespace btobastian
} // namespace de
