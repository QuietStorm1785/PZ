#pragma once
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <cstdint>
#include "com/google/common/annotations/Beta.h"
#include "com/google/common/annotations/GwtCompatible.h"
#include "com/google/common/base/Ascii.h"
#include "com/google/common/base/CharMatcher.h"
#include "com/google/common/base/Charsets.h"
#include "com/google/common/base/Joiner.h"
#include "com/google/common/base/Joiner/MapJoiner.h"
#include "com/google/common/base/MoreObjects.h"
#include "com/google/common/base/Objects.h"
#include "com/google/common/base/Optional.h"
#include "com/google/common/base/Preconditions.h"
#include "com/google/common/collect/ImmutableListMultimap.h"
#include "com/google/common/collect/ImmutableListMultimap/Builder.h"
#include "com/google/common/collect/ImmutableMultiset.h"
#include "com/google/common/collect/ImmutableSet.h"
#include "com/google/common/collect/Iterables.h"
#include "com/google/common/collect/Maps.h"
#include "com/google/common/collect/Multimap.h"
#include "com/google/common/collect/Multimaps.h"
#include "com/google/common/net/MediaType/1.h"
#include "com/google/common/net/MediaType/2.h"
#include "com/google/common/net/MediaType/Tokenizer.h"
#include "com/google/errorprone/annotations/concurrent/LazyInit.h"
#include "javax/annotation/Nullable.h"
#include "javax/annotation/concurrent/Immutable.h"
#include <algorithm>
#include <filesystem>

namespace com {
namespace google {
namespace common {
namespace net {


class MediaType {
public:
    static const std::string CHARSET_ATTRIBUTE = "charset";
   private static const ImmutableListMultimap<std::string, std::string> UTF_8_CONSTANT_PARAMETERS = ImmutableListMultimap.of(
      "charset", Ascii.toLowerCase(Charsets.UTF_8.name())
   );
   private static const CharMatcher TOKEN_MATCHER = CharMatcher.ascii()
      .and(CharMatcher.javaIsoControl().negate())
      .and(CharMatcher.isNot(' '))
      .and(CharMatcher.noneOf("()<>@,;:\\\"/[]?="));
    static const CharMatcher QUOTED_TEXT_MATCHER = CharMatcher.ascii().and(CharMatcher.noneOf("\"\\\r"));
    static const CharMatcher LINEAR_WHITE_SPACE = CharMatcher.anyOf(" \t\r\n");
    static const std::string APPLICATION_TYPE = "application";
    static const std::string AUDIO_TYPE = "audio";
    static const std::string IMAGE_TYPE = "image";
    static const std::string TEXT_TYPE = "text";
    static const std::string VIDEO_TYPE = "video";
    static const std::string WILDCARD = "*";
   private static const Map<MediaType, MediaType> KNOWN_TYPES = Maps.newHashMap();
    static const MediaType ANY_TYPE = createConstant("*", "*");
    static const MediaType ANY_TEXT_TYPE = createConstant("text", "*");
    static const MediaType ANY_IMAGE_TYPE = createConstant("image", "*");
    static const MediaType ANY_AUDIO_TYPE = createConstant("audio", "*");
    static const MediaType ANY_VIDEO_TYPE = createConstant("video", "*");
    static const MediaType ANY_APPLICATION_TYPE = createConstant("application", "*");
    static const MediaType CACHE_MANIFEST_UTF_8 = createConstantUtf8("text", "cache-manifest");
    static const MediaType CSS_UTF_8 = createConstantUtf8("text", "css");
    static const MediaType CSV_UTF_8 = createConstantUtf8("text", "csv");
    static const MediaType HTML_UTF_8 = createConstantUtf8("text", "html");
    static const MediaType I_CALENDAR_UTF_8 = createConstantUtf8("text", "calendar");
    static const MediaType PLAIN_TEXT_UTF_8 = createConstantUtf8("text", "plain");
    static const MediaType TEXT_JAVASCRIPT_UTF_8 = createConstantUtf8("text", "javascript");
    static const MediaType TSV_UTF_8 = createConstantUtf8("text", "tab-separated-values");
    static const MediaType VCARD_UTF_8 = createConstantUtf8("text", "vcard");
    static const MediaType WML_UTF_8 = createConstantUtf8("text", "vnd.wap.wml");
    static const MediaType XML_UTF_8 = createConstantUtf8("text", "xml");
    static const MediaType VTT_UTF_8 = createConstantUtf8("text", "vtt");
    static const MediaType BMP = createConstant("image", "bmp");
    static const MediaType CRW = createConstant("image", "x-canon-crw");
    static const MediaType GIF = createConstant("image", "gif");
    static const MediaType ICO = createConstant("image", "vnd.microsoft.icon");
    static const MediaType JPEG = createConstant("image", "jpeg");
    static const MediaType PNG = createConstant("image", "png");
    static const MediaType PSD = createConstant("image", "vnd.adobe.photoshop");
    static const MediaType SVG_UTF_8 = createConstantUtf8("image", "svg+xml");
    static const MediaType TIFF = createConstant("image", "tiff");
    static const MediaType WEBP = createConstant("image", "webp");
    static const MediaType MP4_AUDIO = createConstant("audio", "mp4");
    static const MediaType MPEG_AUDIO = createConstant("audio", "mpeg");
    static const MediaType OGG_AUDIO = createConstant("audio", "ogg");
    static const MediaType WEBM_AUDIO = createConstant("audio", "webm");
    static const MediaType L24_AUDIO = createConstant("audio", "l24");
    static const MediaType BASIC_AUDIO = createConstant("audio", "basic");
    static const MediaType AAC_AUDIO = createConstant("audio", "aac");
    static const MediaType VORBIS_AUDIO = createConstant("audio", "vorbis");
    static const MediaType WMA_AUDIO = createConstant("audio", "x-ms-wma");
    static const MediaType WAX_AUDIO = createConstant("audio", "x-ms-wax");
    static const MediaType VND_REAL_AUDIO = createConstant("audio", "vnd.rn-realaudio");
    static const MediaType VND_WAVE_AUDIO = createConstant("audio", "vnd.wave");
    static const MediaType MP4_VIDEO = createConstant("video", "mp4");
    static const MediaType MPEG_VIDEO = createConstant("video", "mpeg");
    static const MediaType OGG_VIDEO = createConstant("video", "ogg");
    static const MediaType QUICKTIME = createConstant("video", "quicktime");
    static const MediaType WEBM_VIDEO = createConstant("video", "webm");
    static const MediaType WMV = createConstant("video", "x-ms-wmv");
    static const MediaType FLV_VIDEO = createConstant("video", "x-flv");
    static const MediaType THREE_GPP_VIDEO = createConstant("video", "3gpp");
    static const MediaType THREE_GPP2_VIDEO = createConstant("video", "3gpp2");
    static const MediaType APPLICATION_XML_UTF_8 = createConstantUtf8("application", "xml");
    static const MediaType ATOM_UTF_8 = createConstantUtf8("application", "atom+xml");
    static const MediaType BZIP2 = createConstant("application", "x-bzip2");
    static const MediaType DART_UTF_8 = createConstantUtf8("application", "dart");
    static const MediaType APPLE_PASSBOOK = createConstant("application", "vnd.apple.pkpass");
    static const MediaType EOT = createConstant("application", "vnd.ms-fontobject");
    static const MediaType EPUB = createConstant("application", "epub+zip");
    static const MediaType FORM_DATA = createConstant("application", "x-www-form-urlencoded");
    static const MediaType KEY_ARCHIVE = createConstant("application", "pkcs12");
    static const MediaType APPLICATION_BINARY = createConstant("application", "binary");
    static const MediaType GZIP = createConstant("application", "x-gzip");
    static const MediaType JAVASCRIPT_UTF_8 = createConstantUtf8("application", "javascript");
    static const MediaType JSON_UTF_8 = createConstantUtf8("application", "json");
    static const MediaType MANIFEST_JSON_UTF_8 = createConstantUtf8("application", "manifest+json");
    static const MediaType KML = createConstant("application", "vnd.google-earth.kml+xml");
    static const MediaType KMZ = createConstant("application", "vnd.google-earth.kmz");
    static const MediaType MBOX = createConstant("application", "mbox");
    static const MediaType APPLE_MOBILE_CONFIG = createConstant("application", "x-apple-aspen-config");
    static const MediaType MICROSOFT_EXCEL = createConstant("application", "vnd.ms-excel");
    static const MediaType MICROSOFT_POWERPOINT = createConstant("application", "vnd.ms-powerpoint");
    static const MediaType MICROSOFT_WORD = createConstant("application", "msword");
    static const MediaType NACL_APPLICATION = createConstant("application", "x-nacl");
    static const MediaType NACL_PORTABLE_APPLICATION = createConstant("application", "x-pnacl");
    static const MediaType OCTET_STREAM = createConstant("application", "octet-stream");
    static const MediaType OGG_CONTAINER = createConstant("application", "ogg");
    static const MediaType OOXML_DOCUMENT = createConstant("application", "vnd.openxmlformats-officedocument.wordprocessingml.document");
    static const MediaType OOXML_PRESENTATION = createConstant("application", "vnd.openxmlformats-officedocument.presentationml.presentation");
    static const MediaType OOXML_SHEET = createConstant("application", "vnd.openxmlformats-officedocument.spreadsheetml.sheet");
    static const MediaType OPENDOCUMENT_GRAPHICS = createConstant("application", "vnd.oasis.opendocument.graphics");
    static const MediaType OPENDOCUMENT_PRESENTATION = createConstant("application", "vnd.oasis.opendocument.presentation");
    static const MediaType OPENDOCUMENT_SPREADSHEET = createConstant("application", "vnd.oasis.opendocument.spreadsheet");
    static const MediaType OPENDOCUMENT_TEXT = createConstant("application", "vnd.oasis.opendocument.text");
    static const MediaType PDF = createConstant("application", "pdf");
    static const MediaType POSTSCRIPT = createConstant("application", "postscript");
    static const MediaType PROTOBUF = createConstant("application", "protobuf");
    static const MediaType RDF_XML_UTF_8 = createConstantUtf8("application", "rdf+xml");
    static const MediaType RTF_UTF_8 = createConstantUtf8("application", "rtf");
    static const MediaType SFNT = createConstant("application", "font-sfnt");
    static const MediaType SHOCKWAVE_FLASH = createConstant("application", "x-shockwave-flash");
    static const MediaType SKETCHUP = createConstant("application", "vnd.sketchup.skp");
    static const MediaType SOAP_XML_UTF_8 = createConstantUtf8("application", "soap+xml");
    static const MediaType TAR = createConstant("application", "x-tar");
    static const MediaType WOFF = createConstant("application", "font-woff");
    static const MediaType WOFF2 = createConstant("application", "font-woff2");
    static const MediaType XHTML_UTF_8 = createConstantUtf8("application", "xhtml+xml");
    static const MediaType XRD_UTF_8 = createConstantUtf8("application", "xrd+xml");
    static const MediaType ZIP = createConstant("application", "zip");
    const std::string type;
    const std::string subtype;
   private const ImmutableListMultimap<std::string, std::string> parameters;
    std::string toString;
    int hashCode;
    static const MapJoiner PARAMETER_JOINER = Joiner.on(";

    static MediaType createConstant(const std::string& type, const std::string& subtype) {
    return addKnownType(std::make_shared<MediaType>(type);
   }

    static MediaType createConstantUtf8(const std::string& type, const std::string& subtype) {
    return addKnownType(std::make_shared<MediaType>(type);
   }

    static MediaType addKnownType(MediaType mediaType) {
      KNOWN_TYPES.put(mediaType, mediaType);
    return mediaType;
   }

    private MediaType(const std::string& type, const std::string& subtype, std::string> parameters) {
      this.type = type;
      this.subtype = subtype;
      this.parameters = parameters;
   }

    std::string type() {
      return this.type;
   }

    std::string subtype() {
      return this.subtype;
   }

   public ImmutableListMultimap<std::string, std::string> parameters() {
      return this.parameters;
   }

   private Map<std::string, ImmutableMultiset<std::string>> parametersAsMap() {
      return Maps.transformValues(this.parameters.asMap(), std::make_shared<1>(this));
   }

   public Optional<Charset> charset() {
      ImmutableSet<std::string> charsetValues = ImmutableSet.copyOf(this.parameters.get("charset"));
      switch (charsetValues.size()) {
         case 0:
            return Optional.absent();
         case 1:
            return Optional.of(Charset.forName((std::string)Iterables.getOnlyElement(charsetValues)));
         default:
            throw IllegalStateException("Multiple charset values defined: " + charsetValues);
      }
   }

    MediaType withoutParameters() {
      return this.parameters.empty() ? this : create(this.type, this.subtype);
   }

    MediaType withParameters(std::string> parameters) {
    return create();
   }

    MediaType withParameter(const std::string& attribute, const std::string& value) {
      Preconditions.checkNotNull(attribute);
      Preconditions.checkNotNull(value);
    std::string normalizedAttribute = normalizeToken(attribute);
      Builder<std::string, std::string> builder = ImmutableListMultimap.builder();

      for (Entry<std::string, std::string> entry : this.parameters.entries()) {
    std::string key = entry.getKey();
         if (!normalizedAttribute == key)) {
            builder.put(key, entry.getValue());
         }
      }

      builder.put(normalizedAttribute, normalizeParameterValue(normalizedAttribute, value));
    MediaType mediaType = std::make_shared<MediaType>(this.type, this.subtype, builder.build());
      return (MediaType)MoreObjects.firstNonNull(KNOWN_TYPES.get(mediaType), mediaType);
   }

    MediaType withCharset(Charset charset) {
      Preconditions.checkNotNull(charset);
      return this.withParameter("charset", charset.name());
   }

    bool hasWildcard() {
      return "*" == this.type) || "*" == this.subtype);
   }

    bool is(MediaType mediaTypeRange) {
      return (mediaTypeRange.type == "*") || mediaTypeRange.type == this.type))
         && (mediaTypeRange.subtype == "*") || mediaTypeRange.subtype == this.subtype))
         && this.parameters.entries().containsAll(mediaTypeRange.parameters.entries());
   }

    static MediaType create(const std::string& type, const std::string& subtype) {
    return create();
   }

    static MediaType createApplicationType(const std::string& subtype) {
    return create();
   }

    static MediaType createAudioType(const std::string& subtype) {
    return create();
   }

    static MediaType createImageType(const std::string& subtype) {
    return create();
   }

    static MediaType createTextType(const std::string& subtype) {
    return create();
   }

    static MediaType createVideoType(const std::string& subtype) {
    return create();
   }

    static MediaType create(const std::string& type, const std::string& subtype, std::string> parameters) {
      Preconditions.checkNotNull(type);
      Preconditions.checkNotNull(subtype);
      Preconditions.checkNotNull(parameters);
    std::string normalizedType = normalizeToken(type);
    std::string normalizedSubtype = normalizeToken(subtype);
      Preconditions.checkArgument(!"*" == normalizedType) || "*" == normalizedSubtype), "A wildcard type cannot be used with a non-wildcard subtype");
      Builder<std::string, std::string> builder = ImmutableListMultimap.builder();

      for (Entry<std::string, std::string> entry : parameters.entries()) {
    std::string attribute = normalizeToken(entry.getKey());
         builder.put(attribute, normalizeParameterValue(attribute, entry.getValue()));
      }

    MediaType mediaType = std::make_shared<MediaType>(normalizedType, normalizedSubtype, builder.build());
      return (MediaType)MoreObjects.firstNonNull(KNOWN_TYPES.get(mediaType), mediaType);
   }

    static std::string normalizeToken(const std::string& token) {
      Preconditions.checkArgument(TOKEN_MATCHER.matchesAllOf(token));
      return Ascii.toLowerCase(token);
   }

    static std::string normalizeParameterValue(const std::string& attribute, const std::string& value) {
      return "charset" == attribute) ? Ascii.toLowerCase(value) : value;
   }

    static MediaType parse(const std::string& input) {
      Preconditions.checkNotNull(input);
    Tokenizer tokenizer = std::make_shared<Tokenizer>(input);

      try {
    std::string type = tokenizer.consumeToken(TOKEN_MATCHER);
         tokenizer.consumeCharacter('/');
    std::string subtype = tokenizer.consumeToken(TOKEN_MATCHER);
         Builder<std::string, std::string> parameters = ImmutableListMultimap.builder();

         while (tokenizer.hasMore()) {
            tokenizer.consumeTokenIfPresent(LINEAR_WHITE_SPACE);
            tokenizer.consumeCharacter(';');
            tokenizer.consumeTokenIfPresent(LINEAR_WHITE_SPACE);
    std::string attribute = tokenizer.consumeToken(TOKEN_MATCHER);
            tokenizer.consumeCharacter('=');
    std::string value;
            if ('"' != tokenizer.previewChar()) {
               value = tokenizer.consumeToken(TOKEN_MATCHER);
            } else {
               tokenizer.consumeCharacter('"');
    std::stringstream valueBuilder = new std::stringstream();

               while ('"' != tokenizer.previewChar()) {
                  if ('\\' == tokenizer.previewChar()) {
                     tokenizer.consumeCharacter('\\');
                     valueBuilder.append(tokenizer.consumeCharacter(CharMatcher.ascii()));
                  } else {
                     valueBuilder.append(tokenizer.consumeToken(QUOTED_TEXT_MATCHER));
                  }
               }

               value = valueBuilder;
               tokenizer.consumeCharacter('"');
            }

            parameters.put(attribute, value);
         }

    return create();
      } catch (IllegalStateException var8) {
         throw IllegalArgumentException("Could not parse '" + input + "'", var8);
      }
   }

    bool equals(@Nullable Object) {
      if (obj == this) {
    return true;
      } else if (!(dynamic_cast<MediaType*>(obj) != nullptr)) {
    return false;
      } else {
    MediaType that = (MediaType)obj;
         return this.type == that.type) && this.subtype == that.subtype) && this.parametersAsMap() == that.parametersAsMap());
      }
   }

    int hashCode() {
    int h = this.hashCode;
      if (h == 0) {
         h = Objects.hashCode(new Object[]{this.type, this.subtype, this.parametersAsMap()});
         this.hashCode = h;
      }

    return h;
   }

    std::string toString() {
    std::string result = this.toString;
      if (result == nullptr) {
         result = this.computeToString();
         this.toString = result;
      }

    return result;
   }

    std::string computeToString() {
    std::stringstream builder = new std::stringstream().append(this.type).append('/').append(this.subtype);
      if (!this.parameters.empty()) {
         builder.append("; ");
         Multimap<std::string, std::string> quotedParameters = Multimaps.transformValues(this.parameters, std::make_shared<2>(this));
         PARAMETER_JOINER.appendTo(builder, quotedParameters.entries());
      }

      return builder;
   }

    static std::string escapeAndQuote(const std::string& value) {
    std::stringstream escaped = new std::stringstream(value.length() + 16).append('"');

      for (int i = 0; i < value.length(); i++) {
    char ch = value.charAt(i);
         if (ch == '\r' || ch == '\\' || ch == '"') {
            escaped.append('\\');
         }

         escaped.append(ch);
      }

      return escaped.append('"');
   }
}
} // namespace net
} // namespace common
} // namespace google
} // namespace com
